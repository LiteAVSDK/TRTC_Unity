using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Threading;
using UnityEngine;
using UnityEngine.UI;

namespace trtc {
  public enum UnityVideoRenderType {
    None = 0,
    RawImage = 1,
    Renderer = 2,
  };

  public class TRTCUnityVideoFrame {
    private TRTCVideoFrame _frame;
    private readonly ReaderWriterLockSlim _lock = new ReaderWriterLockSlim();

    public TRTCUnityVideoFrame(TRTCVideoFrame frame) {
      _frame = frame;
      _frame.data = AllocNativeMemery((int)frame.length);
      TRTCCloudNative.trtc_cloud_copy_native_memery(_frame.data, frame.data, (int)frame.length);
    }

    public bool TryLock(int timeoutMs = 100) {
      return _lock.TryEnterReadLock(timeoutMs);
    }

    public void ReleaseLock() {
      if (_lock.IsReadLockHeld) {
        _lock.ExitReadLock();
      }
    }

    public TRTCVideoFrame GetFrame() {
      return _frame;
    }

    internal void UpdateFrame(TRTCVideoFrame frame) {
      _lock.EnterWriteLock();
      try {
        if (_frame.length != frame.length) {
          if (_frame.data != IntPtr.Zero) {
            FreeNativeMemery(_frame.data);
          }
          _frame.data = AllocNativeMemery((int)frame.length);
        }
        var newFrame = frame;
        newFrame.data = _frame.data;
        TRTCCloudNative.trtc_cloud_copy_native_memery(newFrame.data, frame.data, (int)frame.length);
        _frame = newFrame;
      }
      finally {
        _lock.ExitWriteLock();
      }
    }

    internal void ReleaseFrame() {
      _lock.EnterWriteLock();
      try {
        if (_frame.data != IntPtr.Zero) {
          FreeNativeMemery(_frame.data);
          _frame.data = IntPtr.Zero;
        }
      }
      finally {
        _lock.ExitWriteLock();
      }
    }

    IntPtr AllocNativeMemery(int size) {
      if (size <= 0) {
        return IntPtr.Zero;
      }
      IntPtr ptr = Marshal.AllocHGlobal(size);
      TRTCLogger.Info("AllocNativeMemery size: " + size + ", ptr: " + ptr);
      return ptr;
    }

    void FreeNativeMemery(IntPtr ptr) {
      TRTCLogger.Info("FreeNativeMemery ptr: " + ptr);
      if (ptr != IntPtr.Zero) {
        Marshal.FreeHGlobal(ptr);
      }
    }
  }

  public interface ITRTCUnityVideoRenderCallback {
    void onRenderVideoFrame(string userId, TRTCVideoStreamType streamType, TRTCUnityVideoFrame frame);
  }

  public class TRTCUnityVideoRenderCallback : ITRTCVideoRenderCallback {
    private static TRTCUnityVideoRenderCallback _instance = null;
    private static readonly object _instanceLock = new object();

    private readonly object _callbacksLock = new object();
    private Dictionary<string, List<ITRTCUnityVideoRenderCallback>> _renderCallbacks = new Dictionary<string, List<ITRTCUnityVideoRenderCallback>>();
    private Dictionary<string, TRTCUnityVideoFrame> _framePool = new Dictionary<string, TRTCUnityVideoFrame>();
    private Dictionary<string, StreamInfo> _registeredStreams = new Dictionary<string, StreamInfo>();

    private struct StreamInfo {
      public string UserId;
      public TRTCVideoStreamType StreamType;
      public TRTCVideoPixelFormat VideoFormat;
      public TRTCVideoBufferType BufferType;
    }

    public static TRTCUnityVideoRenderCallback Instance {
      get {
        if (_instance == null) {
          lock (_instanceLock) {
            if (_instance == null) {
              _instance = new TRTCUnityVideoRenderCallback();
            }
          }
        }
        return _instance;
      }
    }

    private TRTCUnityVideoRenderCallback() {
    }

    private string GetStreamKey(string userId, TRTCVideoStreamType streamType) {
      return $"{userId}_{(int)streamType}";
    }

    public void RegisterRenderCallback(string userId, TRTCVideoStreamType streamType,
        TRTCVideoPixelFormat videoFormat, TRTCVideoBufferType bufferType,
        ITRTCUnityVideoRenderCallback callback) {
      if (callback == null) return;

      string streamKey = GetStreamKey(userId, streamType);

      lock (_callbacksLock) {
        if (!_renderCallbacks.ContainsKey(streamKey)) {
          _renderCallbacks[streamKey] = new List<ITRTCUnityVideoRenderCallback>();
        }

        if (!_renderCallbacks[streamKey].Contains(callback)) {
          _renderCallbacks[streamKey].Add(callback);
        }

        if (_renderCallbacks[streamKey].Count == 1) {
          RegisterToTRTCSDK(userId, streamType, videoFormat, bufferType);

          _registeredStreams[streamKey] = new StreamInfo {
            UserId = userId,
            StreamType = streamType,
            VideoFormat = videoFormat,
            BufferType = bufferType
          };
        }
      }

      int renderCallbackCount = GetRenderCallbackCount(userId, streamType);
      TRTCLogger.Info($"RegisterRenderCallback: {streamKey}, total callback count: {renderCallbackCount}");
    }

    public void UnregisterRenderCallback(string userId, TRTCVideoStreamType streamType,
        ITRTCUnityVideoRenderCallback callback) {
      if (callback == null) return;

      string streamKey = GetStreamKey(userId, streamType);

      lock (_callbacksLock) {
        if (_renderCallbacks.ContainsKey(streamKey)) {
          _renderCallbacks[streamKey].Remove(callback);

          if (_renderCallbacks[streamKey].Count == 0) {
            _renderCallbacks.Remove(streamKey);
            UnregisterFromTRTCSDK(userId, streamType);
            _registeredStreams.Remove(streamKey);
          }
        }

        if (!_renderCallbacks.ContainsKey(streamKey) && _framePool.ContainsKey(streamKey)) {
          _framePool[streamKey].ReleaseFrame();
          _framePool.Remove(streamKey);
        }
      }

      int count = GetRenderCallbackCount(userId, streamType);
      TRTCLogger.Info($"UnregisterRenderCallback: {streamKey}, total callback count: {count}");
    }

    private void RegisterToTRTCSDK(string userId, TRTCVideoStreamType streamType,
            TRTCVideoPixelFormat videoFormat, TRTCVideoBufferType bufferType) {
      ITRTCCloud trtcCloud = ITRTCCloud.getTRTCShareInstance();
      if (trtcCloud == null) return;

      if (string.IsNullOrEmpty(userId)) {
        trtcCloud.setLocalVideoRenderCallback(streamType, videoFormat, bufferType, this);
      }
      else {
        trtcCloud.setRemoteVideoRenderCallback(userId, streamType, videoFormat, bufferType, this);
      }

      TRTCLogger.Info($"RegisterToTRTCSDK: userId={userId}, streamType={streamType}");
    }

    private void UnregisterFromTRTCSDK(string userId, TRTCVideoStreamType streamType) {
      ITRTCCloud trtcCloud = ITRTCCloud.getTRTCShareInstance();
      if (trtcCloud == null) return;

      if (string.IsNullOrEmpty(userId)) {
        trtcCloud.setLocalVideoRenderCallback(streamType, TRTCVideoPixelFormat.TRTCVideoPixelFormat_RGBA32,
                    TRTCVideoBufferType.TRTCVideoBufferType_Buffer, null);
      }
      else {
        trtcCloud.setRemoteVideoRenderCallback(userId, streamType, TRTCVideoPixelFormat.TRTCVideoPixelFormat_RGBA32,
                    TRTCVideoBufferType.TRTCVideoBufferType_Buffer, null);
      }

      TRTCLogger.Info($"UnregisterFromTRTCSDK: userId={userId}, streamType={streamType}");
    }

    public void onRenderVideoFrame(string userId, TRTCVideoStreamType streamType, TRTCVideoFrame frame) {
      List<ITRTCUnityVideoRenderCallback> callbacks = null;

      string streamKey = GetStreamKey(userId, streamType);
      TRTCUnityVideoFrame unityFrame = null;
      lock (_callbacksLock) {
        if (_renderCallbacks.ContainsKey(streamKey)) {
          callbacks = new List<ITRTCUnityVideoRenderCallback>(_renderCallbacks[streamKey]);
          if (!_framePool.ContainsKey(streamKey)) {
            _framePool[streamKey] = new TRTCUnityVideoFrame(frame);
          }
          else {
            _framePool[streamKey].UpdateFrame(frame);
          }
          unityFrame = _framePool[streamKey];
        }
      }

      if (callbacks != null && callbacks.Count > 0 && unityFrame != null) {
        foreach (var callback in callbacks) {
          try {
            callback.onRenderVideoFrame(userId, streamType, unityFrame);
          }
          catch (Exception ex) {
            TRTCLogger.Error($"Error in render callback: {ex.Message}");
          }
        }
      }
    }

    public int GetRenderCallbackCount(string userId, TRTCVideoStreamType streamType) {
      string streamKey = GetStreamKey(userId, streamType);
      lock (_callbacksLock) {
        return _renderCallbacks.ContainsKey(streamKey) ? _renderCallbacks[streamKey].Count : 0;
      }
    }

    public void ClearAllRenders() {
      lock (_callbacksLock) {
        foreach (var streamInfo in _registeredStreams.Values) {
          UnregisterFromTRTCSDK(streamInfo.UserId, streamInfo.StreamType);
        }

        _renderCallbacks.Clear();
        _registeredStreams.Clear();

        foreach (var unityFrame in _framePool.Values) {
          unityFrame.ReleaseFrame();
        }
        _framePool.Clear();
      }

      TRTCLogger.Info("ClearAllRenders completed");
    }
  }

  public class TRTCUnityVideoRender : MonoBehaviour, ITRTCUnityVideoRenderCallback {
    private string _userId = "";
    private TRTCVideoStreamType _streamType = TRTCVideoStreamType.TRTCVideoStreamTypeBig;
    private bool _enable = true;

    private UnityVideoRenderType _videoRenderType = UnityVideoRenderType.None;
    private RawImage _rawImage = null;
    private Renderer _renderer = null;
    private Texture2D _nativeTexture = null;
    private TRTCRenderParams _renderParams;
    private bool _needUpdateLayout = false;
    private bool _streamInfoValid = false;

    private uint _textureWidth = 0;
    private uint _textureHeight = 0;
    private TextureFormat _textureFormat = TextureFormat.RGBA32;
    private TRTCUnityVideoFrame _unityVideoFrame = null;
    private TRTCVideoBufferType _videoBufferType = TRTCVideoBufferType.TRTCVideoBufferType_Buffer;
    private TRTCVideoPixelFormat _videoFormat = TRTCVideoPixelFormat.TRTCVideoPixelFormat_RGBA32;

    private bool _frameUpdated = false;
    public void SetEnable(bool enable) { _enable = enable; }

    public TRTCUnityVideoRender() {
      _renderParams.fillMode = TRTCVideoFillMode.TRTCVideoFillMode_Fit;
    }

    public void SetRenderStreamInfo(string userID, TRTCVideoStreamType streamType) {
      TRTCLogger.Info($"StartRenderStreamInfo userID= {userID}, streamType= {streamType}");
      Clear();
      _userId = userID;
      _streamType = streamType;
      _streamInfoValid = true;

      TRTCUnityVideoRenderCallback.Instance.RegisterRenderCallback(_userId, _streamType, _videoFormat, _videoBufferType, this);
    }

    public void Clear() {
      TRTCLogger.Info($"Clear userID= {_userId}, streamType= {_streamType}, streamInfoValid= {_streamInfoValid}");
      if (!_streamInfoValid) {
        return;
      }

      TRTCUnityVideoRenderCallback.Instance.UnregisterRenderCallback(_userId, _streamType, this);
      _unityVideoFrame = null;
      lock (this) {
        _textureWidth = 0;
        _textureHeight = 0;

        _nativeTexture = null;
        if (_videoRenderType == UnityVideoRenderType.RawImage && _rawImage != null) {
          _rawImage.texture = null;
        }
        else if (_videoRenderType == UnityVideoRenderType.Renderer && _renderer != null) {
          _renderer.material.mainTexture = null;
        }
      }
      _userId = "";
      _streamType = TRTCVideoStreamType.TRTCVideoStreamTypeBig;
      _streamInfoValid = false;
    }

    public void SetRenderParams(TRTCRenderParams renderParams) {
      bool paramsChanged = renderParams.fillMode != _renderParams.fillMode
         || renderParams.mirrorType != _renderParams.mirrorType
         || renderParams.rotation != _renderParams.rotation;
      _renderParams = renderParams;

      if (paramsChanged) {
        _needUpdateLayout = true;
      }
    }

    void Start() {
      _rawImage = GetComponent<RawImage>();
      if (_rawImage != null) {
        _videoRenderType = UnityVideoRenderType.RawImage;
      }
      else {
        _renderer = GetComponent<Renderer>();
        if (_renderer != null) {
          _videoRenderType = UnityVideoRenderType.Renderer;
        }
      }
    }

    void Update() {
      if (_videoRenderType == UnityVideoRenderType.None)
        return;

      if (!_enable || !_frameUpdated || _unityVideoFrame == null)
        return;

      if (!_unityVideoFrame.TryLock(20)) {
        return;
      }

      TRTCVideoFrame videoFrame = _unityVideoFrame.GetFrame();
      if (videoFrame.data == IntPtr.Zero) {
        _frameUpdated = false;
        _unityVideoFrame.ReleaseLock();
        return;
      }

      lock (this) {
        TextureFormat newFormat = TRTCVideoFormatToTextureFormat(videoFrame.videoFormat);
        if (_nativeTexture == null || _textureFormat != newFormat) {
          try {
            _nativeTexture = new Texture2D((int)videoFrame.width, (int)videoFrame.height, newFormat, false);
            _nativeTexture.filterMode = FilterMode.Trilinear;
            _textureFormat = newFormat;
            _textureWidth = videoFrame.width;
            _textureHeight = videoFrame.height;
            _needUpdateLayout = true;

            if (_videoRenderType == UnityVideoRenderType.RawImage && _rawImage != null) {
              _rawImage.texture = _nativeTexture;
            }
            else if (_videoRenderType == UnityVideoRenderType.Renderer && _renderer != null) {
              _renderer.material.mainTexture = _nativeTexture;
            }
          }
          catch (Exception exception) {
            TRTCLogger.Error("VideoRenderCreate Exception: " + exception);
          }
        }
        if (_textureWidth != videoFrame.width || _textureHeight != videoFrame.height) {
          try {
#if UNITY_2021_2_OR_NEWER
            _nativeTexture.Reinitialize((int)videoFrame.width, (int)videoFrame.height);
#else
            _nativeTexture.Resize((int)videoFrame.width, (int)videoFrame.height);
#endif
            _textureWidth = videoFrame.width;
            _textureHeight = videoFrame.height;
            _needUpdateLayout = true;
          }
          catch (Exception exception) {
            TRTCLogger.Error("VideoRenderResize Exception: " + exception);
          }
        }

        if (_needUpdateLayout) {
          if (_textureWidth > 0 && _textureHeight > 0 &&
              _videoRenderType == UnityVideoRenderType.RawImage) {
            RectTransform rectTransform = gameObject.GetComponent<RectTransform>();

            float localRatio = rectTransform.rect.width / rectTransform.rect.height;
            float videoRatio = (float)_textureWidth / (float)_textureHeight;

            float localScaleX = 1.0f;
            float localScaleY = 1.0f;
            if (_renderParams.fillMode == TRTCVideoFillMode.TRTCVideoFillMode_Fit) {
              if (localRatio > videoRatio) {
                localScaleX = videoRatio / localRatio;
                localScaleY = 1.0f;
              }
              else {
                localScaleX = 1.0f;
                localScaleY = localRatio / videoRatio;
              }
            }
            else {
              if (localRatio > videoRatio) {
                localScaleX = 1.0f;
                localScaleY = localRatio / videoRatio;
              }
              else {
                localScaleX = videoRatio / localRatio;
                localScaleY = 1.0f;
              }
            }

            if (_renderParams.mirrorType == TRTCVideoMirrorType.TRTCVideoMirrorType_Enable) {
              rectTransform.localScale = new Vector3(-localScaleX, -localScaleY, 1);
            }
            else {
              rectTransform.localScale = new Vector3(localScaleX, -localScaleY, 1);
            }

            rectTransform.localEulerAngles = new Vector3(0, 0, 360 - ((int)_renderParams.rotation) * 90);
            _needUpdateLayout = false;
          }
        }

        if (_nativeTexture) {
          try {
            _nativeTexture.LoadRawTextureData(videoFrame.data, (int)videoFrame.length);
            _nativeTexture.Apply();
            _frameUpdated = false;
          }
          catch (Exception exception) {
            TRTCLogger.Error("VideoRenderLoad Exception: " + exception);
          }
        }
      }
      _unityVideoFrame.ReleaseLock();
    }

    void OnDestroy() {
      TRTCLogger.Info("Render --- OnDestroy");
      Clear();
    }

    public void onRenderVideoFrame(string userId,
                                   TRTCVideoStreamType streamType,
                                   TRTCUnityVideoFrame frame) {
      if (!_streamInfoValid || _userId != userId || _streamType != streamType || frame == null)
        return;

      _unityVideoFrame = frame;
      _frameUpdated = true;
    }

    private TextureFormat TRTCVideoFormatToTextureFormat(TRTCVideoPixelFormat format) {
      switch (format) {
        case TRTCVideoPixelFormat.TRTCVideoPixelFormat_BGRA32:
          return TextureFormat.BGRA32;
        case TRTCVideoPixelFormat.TRTCVideoPixelFormat_RGBA32:
          return TextureFormat.RGBA32;
        default:
          TRTCLogger.Error("Invalid video format.");
          return TextureFormat.BGRA32;
      }
    }
  }
}