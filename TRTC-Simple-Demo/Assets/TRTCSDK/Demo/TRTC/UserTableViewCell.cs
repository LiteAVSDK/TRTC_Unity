using System;
using UnityEngine;
using UnityEngine.UI;
using trtc;

namespace TRTCCUnityDemo {
  public class UserTableViewCell : MonoBehaviour {
    public delegate void MuteAudioHandler(string userId, bool mute);
    public delegate void MuteVideoHandler(string userId, TRTCVideoStreamType streamType, bool mute);

    public event MuteAudioHandler DoMuteAudio;
    public event MuteVideoHandler DoMuteVideo;

    public Text TitleText;
    public Text AudioVolumeText;
    public Text StatisText;
    public Button RenderModeBtn;
    public Button AudioBtn;
    public Button VideoBtn;
    public Sprite AudioOnImg;
    public Sprite AudioOffImg;
    public Sprite VideoOnImg;
    public Sprite VideoOffImg;
    public Sprite VideoRenderFillImg;
    public Sprite VideoRenderFitImg;
    public RawImage VideoRender;

    private TRTCRenderParams renderParams = new TRTCRenderParams() {
      fillMode = TRTCVideoFillMode.TRTCVideoFillMode_Fit
    };

    private string userIdStr;
    public string UserIdStr {
      set {
        userIdStr = value;

        if (string.IsNullOrEmpty(userIdStr)) {
          TitleText.text = "me";
          AudioBtn.gameObject.SetActive(true);
          VideoBtn.gameObject.SetActive(true);
        }
        else {
          TitleText.text = userIdStr;
          if (userIdStr == "me_screen") {
            AudioBtn.gameObject.SetActive(false);
            VideoBtn.gameObject.SetActive(false);
            RenderModeBtn.gameObject.SetActive(false);
          }
          else {
            AudioBtn.gameObject.SetActive(streamTypeInt != TRTCVideoStreamType.TRTCVideoStreamTypeSub);
            VideoBtn.gameObject.SetActive(true);
          }
        }
      }
    }

    private TRTCVideoStreamType streamTypeInt;
    public TRTCVideoStreamType StreamTypeInt {
      get { return streamTypeInt; }
      set {
        streamTypeInt = value;
      }
    }

    public bool isAudioMute = false;
    public bool IsAudioMute {
      set {
        isAudioMute = value;
        updateAudioBtn();
      }
    }

    public bool isVideoMute = false;
    public bool IsVideoMute {
      set {
        isVideoMute = value;
        updateVideoBtn();
      }
    }

    private bool isVideoAvailable = false;
    public bool IsVideoAvailable {
      set {
        isVideoAvailable = value;
        VideoRender.gameObject.SetActive(isVideoAvailable);
      }
    }

    public UInt32 AudioVolume {
      set {
        AudioVolumeText.text = string.Format("{0}", value);
      }
    }

    public bool AudioVolumeVisible {
      set {
        AudioVolumeText.gameObject.SetActive(value);
      }
    }

    public string UserStatisText {
      set {
        StatisText.text = value;
      }
    }

    public bool UserStatisVisible {
      set {
        StatisText.gameObject.SetActive(value);
      }
    }

    void Start() {

    }

    void Update() {

    }

    public void CellSwitchRenderMode() {
      if (renderParams.fillMode == TRTCVideoFillMode.TRTCVideoFillMode_Fit) {
        renderParams.fillMode = TRTCVideoFillMode.TRTCVideoFillMode_Fill;
      }
      else {
        renderParams.fillMode = TRTCVideoFillMode.TRTCVideoFillMode_Fit;
      }

      if (string.IsNullOrEmpty(userIdStr)) {
        ITRTCCloud.getTRTCShareInstance().setLocalRenderParams(renderParams);
      }
      else {
        ITRTCCloud.getTRTCShareInstance().setRemoteRenderParams(userIdStr, streamTypeInt, ref renderParams);
      }
    }

    public void CellMuteAudioAction() {
      if (DoMuteAudio != null) {
        DoMuteAudio(userIdStr, !isAudioMute);
      }
      isAudioMute = !isAudioMute;
      updateAudioBtn();
    }

    public void CellMuteVideoAction() {
      if (DoMuteVideo != null) {
        DoMuteVideo(userIdStr, streamTypeInt, !isVideoMute);
      }
      isVideoMute = !isVideoMute;
      updateVideoBtn();
    }

    private void updateAudioBtn() {
      AudioBtn.image.sprite = isAudioMute ? AudioOffImg : AudioOnImg;
    }

    private void updateVideoBtn() {
      VideoBtn.image.sprite = isVideoMute ? VideoOffImg : VideoOnImg;
    }
  }
}