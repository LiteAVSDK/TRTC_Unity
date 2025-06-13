using System;
using liteav;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;
public class LivePlayerSceneScript : MonoBehaviour {
  private V2TXLivePlayer _mV2TXLive = null;
  private string _url = "webrtc://liteavapp.qcloud.com/live/liteavdemoplayerstreamid";
  public Slider volumeSlider;
  public InputField inputField;
  public Text callbackText;
  public RawImage rawImage = null;
  public Image image = null;
  private V2TXLiveFillMode _videoFillMode = V2TXLiveFillMode.V2TXLiveFillModeFill;
  private V2TXLiveRotation _videoRotation = V2TXLiveRotation.V2TXLiveRotation0;

  public V2TXLiveVideoRender VideoRender;
  public V2TXLiveVideoRender VideoImageRender;

  public Toggle toggleDebugShow;

  public void StartPlay() {
    Debug.Log("StartPlay");
    _mV2TXLive.startPlay(_url);
#if PLATFORM_ANDROID
    Debug.Log("PLATFORM_ANDROID");
    int res =
        _mV2TXLive.enableObserverVideoFrame(true, V2TXLivePixelFormat.V2TXLivePixelFormatRGBA32,
                                            V2TXLiveBufferType.V2TXLiveBufferTypeByteBuffer);
    Debug.Log("PLATFORM_ANDROID res :" + res.ToString());
#else
    Debug.Log("PLATFORM_ALL");
    int res =
        _mV2TXLive.enableObserverVideoFrame(true, V2TXLivePixelFormat.V2TXLivePixelFormatBGRA32,
                                            V2TXLiveBufferType.V2TXLiveBufferTypeByteBuffer);
    Debug.Log("PLATFORM_ANDROID res :" + res.ToString());
#endif
  }
  public void StopPlay() {
    _mV2TXLive.stopPlay();
  }
  public void PausePlay() {
    _mV2TXLive.pauseAudio();
    _mV2TXLive.pauseVideo();
  }
  public void ResumePlay() {
    _mV2TXLive.resumeAudio();
    _mV2TXLive.resumeVideo();
  }
  public void ChangeRotation() {
    _videoRotation += 1;
    if ((int)_videoRotation > 3) {
      _videoRotation = 0;
    }
    _mV2TXLive.setRenderRotation(_videoRotation);
  }
  public void SliderChanged(float volume) {
    if (_mV2TXLive == null) {
      return;
    }
    _mV2TXLive.setPlayoutVolume((int)volume);
  }
  public void BackMaue() { SceneManager.LoadScene("HomeScene", LoadSceneMode.Single); }
  public void ChangeFillMode() {
    _videoFillMode += 1;
    if ((int)_videoFillMode >= 2) {
      _videoFillMode = 0;
    }
    Debug.Log("ChangeFillMode " + _videoFillMode.ToString());
    //_mV2TXLive.setRenderFillMode(_videoFillMode);
  }
  public void Awake() {
#if UNITY_ANDROID || UNITY_OPENHARMONY || UNITY_IOS
    Debug.Log("v2tx_live_premier_set_license ANDROID OR IOS");
    V2TXLivePremier.setLicense(
        "use your own url",
        "use your own key");
#endif
    Debug.Log("mV2TXLive = V2TXLivePlayer.CreatorLivePlayer();");
    _mV2TXLive = V2TXLivePlayer.createLivePlayer();
  }
  public void Start() {
    VideoRender.SetViewFillMode(_videoFillMode);
    VideoRender.gameObject.SetActive(true);
    VideoRender.GetComponent<V2TXLiveVideoRender>().Clear();
    _mV2TXLive.setCallback(VideoRender);
    volumeSlider.onValueChanged.AddListener(SliderChanged);
    inputField.onEndEdit.AddListener(ChangeUrl);
    toggleDebugShow.onValueChanged.AddListener(delegate(bool isOn) { ToggleValueChanged(isOn); });
  }
  public void ChangeUrl(string text) {
    this._url = text;
    Debug.Log("curUrl:" + text);
  }
  public void ToggleValueChanged(bool isShow) {
    if (_mV2TXLive == null) {
      return;
    }
    _mV2TXLive.showDebugView(isShow);
  }

  public void Update() {
    string curInfo = VideoRender.GetCallbackInfo();
    callbackText.text = curInfo;
  }
  void OnDestroy() { GC.Collect(); }
}
