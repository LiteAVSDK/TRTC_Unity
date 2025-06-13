using System;
using UnityEngine;
using UnityEngine.UI;

namespace liteav {
  public enum VideoRenderType {
    None = 0,
    /** The renderer for rendering Raw Image of the UI components. */
    RawImage = 1,
    /** The renderer for rendering 3D GameObject, such as Cube、Cylinder and Plane.*/
    Renderer = 2,
  }
  ;

  public class V2TXLiveVideoRender : MonoBehaviour, V2TXLivePlayerObserver {
    private string _userId = "";
    private bool _enable = true;

    private VideoRenderType _videoRenderType = VideoRenderType.None;
    private RawImage _rawImage = null;
    private Renderer _renderer = null;
    private Texture2D _nativeTexture = null;
    private V2TXLiveFillMode _videoFillMode = V2TXLiveFillMode.V2TXLiveFillModeFit;
    private bool _needUpdateLayout = false;

    private uint _textureWidth = 0;
    private uint _textureHeight = 0;
    private V2TXLiveVideoFrame _videoFrame;
    private UnityEngine.Object _videoFrameLock = new UnityEngine.Object();
    private V2TXLivePixelFormat _videoFormat = V2TXLivePixelFormat.V2TXLivePixelFormatBGRA32;

    public string callbackInfo = "";
    public void SetEnable(bool enable) { _enable = enable; }

    public void Awake() {
#if PLATFORM_ANDROID || PLATFORM_OPENHARMONY
      _videoFormat = V2TXLivePixelFormat.V2TXLivePixelFormatRGBA32;
#endif
    }

    public void SetViewFillMode(V2TXLiveFillMode videoFillMode) {
      if (_videoFillMode != videoFillMode) {
        _videoFillMode = videoFillMode;
        _needUpdateLayout = true;
      }
    }

    public V2TXLiveFillMode GetViewFillMode() { return _videoFillMode; }

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

      if (_enable == false)
        return;

      V2TXLiveVideoFrame videoFrame;
      lock (_videoFrameLock) {
        videoFrame = _videoFrame;
      }

      lock (this) {
        if (_textureWidth != videoFrame.width || _textureHeight != videoFrame.height) {
          _textureWidth = (uint)videoFrame.width;
          _textureHeight = (uint)videoFrame.height;
          _needUpdateLayout = true;

          if (_nativeTexture == null) {
            try {
#if PLATFORM_ANDROID || PLATFORM_OPENHARMONY
              _nativeTexture = new Texture2D((int)_textureWidth, (int)_textureHeight,
                                             TextureFormat.RGBA32, false);
#else
              _nativeTexture = new Texture2D((int)_textureWidth, (int)_textureHeight,
                                             TextureFormat.BGRA32, false);
#endif

              _nativeTexture.filterMode = FilterMode.Trilinear;
              if (_videoRenderType == VideoRenderType.RawImage && _rawImage != null)
                _rawImage.texture = _nativeTexture;
              else if (_videoRenderType == VideoRenderType.Renderer && _renderer != null)
                _renderer.material.mainTexture = _nativeTexture;
            } catch (Exception e) {
              Debug.LogError("VideoRenderCreate Exception e = " + e);
            }
          } else {
            try {
              _nativeTexture.Resize((int)_textureWidth, (int)_textureHeight);
            } catch (Exception e) {
              Debug.LogError("VideoRenderResize Exception e = " + e);
            }
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
            if (_videoFillMode == V2TXLiveFillMode.V2TXLiveFillModeFit) {
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

            rectTransform.localScale = new Vector3(localScaleX, -localScaleY, 1);
            _needUpdateLayout = false;
          }
        }

        if (_nativeTexture) {
          try {
            _nativeTexture.LoadRawTextureData(videoFrame.data);
            _nativeTexture.Apply();
          } catch (Exception e) {
            Debug.LogError("VideoRenderLoad Exception e = " + e);
          }
        }
      }
    }
    void OnDestroy() {
      Debug.Log("Render --- OnDestroy");
      GC.Collect();
    }

    public void Clear() {
      lock (_videoFrameLock) {
        _videoFrame = new V2TXLiveVideoFrame();
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

    public void onError(V2TXLivePlayer player, V2TXLiveCode code, string msg, IntPtr extraInfo) {
      Debug.Log("OnError:" + code.ToString() + " " + msg);
      callbackInfo += "OnError:" + code.ToString() + " " + msg + "\n";
    }

    public void onWarning(V2TXLivePlayer player, V2TXLiveCode code, string msg, IntPtr extraInfo) {
      Debug.Log("OnWarning:" + code.ToString() + " " + msg);
      callbackInfo += "OnWarning:" + code.ToString() + " " + msg + "\n";
    }

    public void onVideoResolutionChanged(V2TXLivePlayer player, int width, int height) {
      Debug.Log("OnVideoResolutionChanged:" + " " + width.ToString() + " " + height.ToString());
      callbackInfo +=
          "OnVideoResolutionChanged:" + " " + width.ToString() + " " + height.ToString() + "\n";
    }

    public void onConnected(V2TXLivePlayer player, IntPtr extraInfo) {
      callbackInfo = "";
      Debug.Log("OnConnected");
      callbackInfo += "onConnected" + " " + "\n";
    }

    public void onVideoPlaying(V2TXLivePlayer player, bool firstPlay, IntPtr extraInfo) {
      Debug.Log("OnVideoPlaying:" + " " + firstPlay.ToString());
      callbackInfo += "OnVideoPlaying:" + " " + firstPlay.ToString() + "\n";
    }

    public void onAudioPlaying(V2TXLivePlayer player, bool firstPlay, IntPtr extraInfo) {
      Debug.Log("OnAudioPlaying" + " " + firstPlay.ToString());
      callbackInfo += "OnAudioPlaying" + " " + firstPlay.ToString() + "\n";
    }

    public void onVideoLoading(V2TXLivePlayer player, IntPtr extraInfo) {
      Debug.Log("OnVideoLoading");
      callbackInfo += "OnVideoLoading" + "\n";
    }

    public void onAudioLoading(V2TXLivePlayer player, IntPtr extraInfo) {
      Debug.Log("OnAudioLoading");
      callbackInfo += "OnAudioLoading" + "\n";
    }

    public void onStatisticsUpdate(V2TXLivePlayer player, V2TXLivePlayerStatistics statistics) {
      Debug.Log("OnStatisticsUpdate:" + "appCpu" + statistics.appCpu.ToString());
      callbackInfo += "OnStatisticsUpdate:" + "appCpu" + statistics.appCpu.ToString() + "\n";
    }

    public void onRenderVideoFrame(V2TXLivePlayer player, V2TXLiveVideoFrame videoFrame) {
      lock (_videoFrameLock) {
        _videoFrame = videoFrame;
      }
    }
    public string GetCallbackInfo() { return callbackInfo; }
  }
}
