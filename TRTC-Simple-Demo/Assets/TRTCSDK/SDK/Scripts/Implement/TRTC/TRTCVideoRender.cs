using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using UnityEngine;
using UnityEngine.UI;
using static TMPro.SpriteAssetUtilities.TexturePacker_JsonArray;

namespace trtc {
  public enum VideoRenderType {
    None = 0,
    /** The renderer for rendering Raw Image of the UI components. */
    RawImage = 1,
    /** The renderer for rendering 3D GameObject, such as Cube、Cylinder and Plane.*/
    Renderer = 2,
  }
  ;

  public class TRTCVideoRender : MonoBehaviour, ITRTCVideoRenderCallback {
    private string _userId = "";
    private TRTCVideoStreamType _streamType = TRTCVideoStreamType.TRTCVideoStreamTypeBig;
    private bool _enable = true;

    private VideoRenderType _videoRenderType = VideoRenderType.None;
    private RawImage _rawImage = null;
    private Renderer _renderer = null;
    private Texture2D _nativeTexture = null;
    private TRTCRenderParams _renderParams;
    private bool _needUpdateLayout = false;

    private uint _textureWidth = 0;
    private uint _textureHeight = 0;
    private TextureFormat _textureFormat = TextureFormat.RGBA32;
    private TRTCVideoFrame _videoFrame;
    private UnityEngine.Object _videoFrameLock = new UnityEngine.Object();
    private TRTCVideoBufferType _videoBufferType = TRTCVideoBufferType.TRTCVideoBufferType_Buffer;
    private TRTCVideoPixelFormat _videoFormat = TRTCVideoPixelFormat.TRTCVideoPixelFormat_RGBA32;
    bool _frameUpdated = false;
    public void SetEnable(bool enable) { _enable = enable; }

    public void Awake() {
    }
    public TRTCVideoRender() {
      _renderParams.fillMode = TRTCVideoFillMode.TRTCVideoFillMode_Fit;
    }

    public void SetForUser(string userID, TRTCVideoStreamType streamType) {
      _userId = userID;
      _streamType = streamType;
      Debug.LogFormat("SetForUser useID={0}, streamType={1}", _userId, _streamType);
      TryRegisterCallback();
    }

    public void setRenderParams(TRTCRenderParams renderParams) {
      if (renderParams.fillMode != _renderParams.fillMode
        || renderParams.mirrorType != _renderParams.mirrorType
        || renderParams.rotation != _renderParams.rotation) {
        _needUpdateLayout = true;
      }
      _renderParams = renderParams;
    }

    private void TryRegisterCallback() {
      ITRTCCloud trtcCloud = ITRTCCloud.getTRTCShareInstance();
      if (trtcCloud == null)
        return;

      if (_userId.Length == 0) {
        trtcCloud.setLocalVideoRenderCallback(_streamType, _videoFormat, _videoBufferType, this);
      } else {
        trtcCloud.setRemoteVideoRenderCallback(_userId, _streamType, _videoFormat,
                                               _videoBufferType, this);
      }
    }

    void Start() {
      _rawImage = GetComponent<RawImage>();
      if (_rawImage != null) {
        _videoRenderType = VideoRenderType.RawImage;
      } else {
        _renderer = GetComponent<Renderer>();
        if (_renderer != null) {
          _videoRenderType = VideoRenderType.Renderer;
        }
      }
    }

    void Update() {
      if (_videoRenderType == VideoRenderType.None)
        return;

      if (!_enable || !_frameUpdated)
        return;

      TRTCVideoFrame videoFrame;
      lock (_videoFrameLock) {
        videoFrame = _videoFrame;
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

            if (_videoRenderType == VideoRenderType.RawImage && _rawImage != null) {
              _rawImage.texture = _nativeTexture;
            } else if (_videoRenderType == VideoRenderType.Renderer && _renderer != null) {
              _renderer.material.mainTexture = _nativeTexture;
            }            
          } catch (Exception e) {
            Debug.LogError("VideoRenderCreate Exception e = " + e);
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
          } catch (Exception e) {
            Debug.LogError("VideoRenderResize Exception e = " + e);
          }
        }

        if (_needUpdateLayout) {
          if (_textureWidth > 0 && _textureHeight > 0 &&
              _videoRenderType == VideoRenderType.RawImage) {
            RectTransform rectTransform = gameObject.GetComponent<RectTransform>();

            float localRatio = rectTransform.rect.width / rectTransform.rect.height;
            float videoRatio = (float)_textureWidth / (float)_textureHeight;

            float localScaleX = 1.0f;
            float localScaleY = 1.0f;
            if (_renderParams.fillMode == TRTCVideoFillMode.TRTCVideoFillMode_Fit) {
              if (localRatio > videoRatio) {
                localScaleX = videoRatio / localRatio;
                localScaleY = 1.0f;
              } else {
                localScaleX = 1.0f;
                localScaleY = localRatio / videoRatio;
              }
            } else {
              if (localRatio > videoRatio) {
                localScaleX = 1.0f;
                localScaleY = localRatio / videoRatio;
              } else {
                localScaleX = videoRatio / localRatio;
                localScaleY = 1.0f;
              }
            }

            if (_renderParams.mirrorType == TRTCVideoMirrorType.TRTCVideoMirrorType_Enable) {
              rectTransform.localScale = new Vector3(-localScaleX, -localScaleY, 1);
            } else {
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
          } catch (Exception e) {
            Debug.LogError("VideoRenderLoad Exception e = " + e);
          }
        }
      }
    }

    void OnDestroy() {
      Debug.Log("Render --- OnDestroy");
      ITRTCCloud trtcCloud = TRTCCloudImplement.queryTRTCShareInstance();
      if (trtcCloud == null)
        return;

      if (_userId != null) {
        if (_userId.Length == 0) {
          trtcCloud.setLocalVideoRenderCallback(
              _streamType, _videoFormat, TRTCVideoBufferType.TRTCVideoBufferType_Buffer, null);
        } else {
          trtcCloud.setRemoteVideoRenderCallback(_userId, _streamType, _videoFormat,
                                                 TRTCVideoBufferType.TRTCVideoBufferType_Buffer,
                                                 null);
        }
      }

      Clear();
    }

    public void Clear() {
      lock (_videoFrameLock) {
        _videoFrame = new TRTCVideoFrame();
      }
      lock (this) {
        _textureWidth = 0;
        _textureHeight = 0;

        _nativeTexture = null;
        if (_videoRenderType == VideoRenderType.RawImage && _rawImage != null) {
          _rawImage.texture = null;
        } else if (_videoRenderType == VideoRenderType.Renderer && _renderer != null) {
          _renderer.material.mainTexture = null;
        }
      }
    }

    public void onRenderVideoFrame(string userId,
                                   TRTCVideoStreamType streamType,
                                   TRTCVideoFrame frame) {
      // Debug.LogFormat("onRenderVideoFormat rotation={0}, w={1}, h={2}", frame.rotation,
      // frame.width, frame.height);
      if (_userId != userId)
        return;

      if (_streamType != streamType)
        return;

      lock (_videoFrameLock) {
        var data = _videoFrame.data;
        if (_videoFrame.length != frame.length) {
          Marshal.FreeHGlobal(_videoFrame.data);
          data = Marshal.AllocHGlobal((int)frame.length);
        }
        _videoFrame = frame;
        _videoFrame.data = data;
        TRTCCloudNative.trtc_cloud_copy_native_memery(_videoFrame.data, frame.data, (int)frame.length);
        _frameUpdated = true;
      }
    }

    private TextureFormat TRTCVideoFormatToTextureFormat(TRTCVideoPixelFormat format) {
      switch (format) {
        case TRTCVideoPixelFormat.TRTCVideoPixelFormat_BGRA32:
          return TextureFormat.BGRA32;
        case TRTCVideoPixelFormat.TRTCVideoPixelFormat_RGBA32:
          return TextureFormat.RGBA32;
        default:
          Debug.Assert(false, "Invalid video format.");
          return TextureFormat.BGRA32;
      }
    }
  }
}
