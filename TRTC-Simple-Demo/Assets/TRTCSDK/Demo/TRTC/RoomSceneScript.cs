using System;
using System.Collections;
using System.Threading;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using trtc;
using LitJson;
using TRTCCUnityDemo;
#if PLATFORM_ANDROID
using UnityEngine.Android;
#endif
#if PLATFORM_OPENHARMONY
using UnityEngine.OpenHarmony;
#endif

namespace TRTCCUnityDemo {
  public class RoomSceneScript : MonoBehaviour, ITRTCCloudCallback {
    public RectTransform mainCanvas;
    public UserTableView userTableView;

    public GameObject settingPrefab;
    public GameObject customCapturePrefab;
    private SettingScript settingScript = null;
    private CustomCaptureScript customCaptureScript = null;

    private Toggle captureVideoToggle;
    private Toggle captureAudioToggle;
    private Toggle muteLocalVideoToggle;
    private Toggle muteLocalAudioToggle;

    private ITRTCCloud mTRTCCloud;
    private AudioSource audio;

    void Start() {
      captureAudioToggle = transform.Find("PanelOperate/Viewport/Content/ToggleMic")
                               .gameObject.GetComponent<Toggle>();
      captureAudioToggle.onValueChanged.AddListener(this.OnToggleMic);

      captureVideoToggle = transform.Find("PanelOperate/Viewport/Content/ToggleCamera")
                               .gameObject.GetComponent<Toggle>();
      captureVideoToggle.onValueChanged.AddListener(this.OnToggleCamera);

      Toggle enableEarMonitorSet =
          transform.Find("PanelOperate/Viewport/Content/ToggleEnableEarMonitor")
              .gameObject.GetComponent<Toggle>();
      enableEarMonitorSet.onValueChanged.AddListener(this.OnToggleEnableEarMonitor);

      muteLocalVideoToggle = transform.Find("PanelOperate/Viewport/Content/ToggleMuteLocalVideo")
                                 .gameObject.GetComponent<Toggle>();
      muteLocalVideoToggle.onValueChanged.AddListener(this.OnToggleMuteLocalVideo);

      muteLocalAudioToggle = transform.Find("PanelOperate/Viewport/Content/ToggleMuteLocalAudio")
                                 .gameObject.GetComponent<Toggle>();
      muteLocalAudioToggle.onValueChanged.AddListener(this.OnToggleMuteLocalAudio);

      Toggle toggleMuteRemoteAudio =
          transform.Find("PanelOperate/Viewport/Content/ToggleMuteRemoteAudio")
              .gameObject.GetComponent<Toggle>();
      toggleMuteRemoteAudio.onValueChanged.AddListener(this.OnToggleMuteRemoteAudio);

      Toggle screenCapture = transform.Find("PanelOperate/Viewport/Content/ToggleScreenCapture")
                                 .gameObject.GetComponent<Toggle>();
      screenCapture.onValueChanged.AddListener(this.OnToggleScreenCapture);

      Toggle playBackground = transform.Find("PanelOperate/Viewport/Content/TogglePlayBackground")
                                  .gameObject.GetComponent<Toggle>();
      playBackground.onValueChanged.AddListener(this.OnTogglePlayBackground);

      Toggle toggleShowConsole = transform.Find("PanelTest/Viewport/Content/ToggleShowConsole")
                                     .gameObject.GetComponent<Toggle>();
      toggleShowConsole.onValueChanged.AddListener(this.OnToggleShowConsole);

      Toggle toggleShowUserVolume =
          transform.Find("PanelTest/Viewport/Content/ToggleShowUserVolume")
              .gameObject.GetComponent<Toggle>();
      toggleShowUserVolume.onValueChanged.AddListener(this.OnToggleShowUserVolume);

      Toggle toggleShowStatis = transform.Find("PanelTest/Viewport/Content/ToggleShowStatis")
                                    .gameObject.GetComponent<Toggle>();
      toggleShowStatis.onValueChanged.AddListener(this.OnToggleShowStatis);

      Toggle toggleSetting = transform.Find("PanelTest/Viewport/Content/ToggleSetting")
                                 .gameObject.GetComponent<Toggle>();
      toggleSetting.onValueChanged.AddListener(this.OnToggleSetting);

      Toggle toggleSendSEIMsg = transform.Find("PanelTest/Viewport/Content/ToggleSendSEIMsg")
                                    .gameObject.GetComponent<Toggle>();
      toggleSendSEIMsg.onValueChanged.AddListener(this.OnToggleSendSEIMsg);

      Toggle toggleSwitchCamera = transform.Find("PanelTest/Viewport/Content/ToggleSwitchCamera")
                                      .gameObject.GetComponent<Toggle>();
      toggleSwitchCamera.onValueChanged.AddListener(this.OnToggleSwitchCamera);

      Toggle beautySet = transform.Find("PanelTest/Viewport/Content/ToggleBeauty")
                             .gameObject.GetComponent<Toggle>();
      beautySet.onValueChanged.AddListener(this.OnToggleBeauty);

      Toggle toggleSetMixTranscodingConfig =
          transform.Find("PanelTest/Viewport/Content/ToggleSetMixTranscodingConfig")
              .gameObject.GetComponent<Toggle>();
      toggleSetMixTranscodingConfig.onValueChanged.AddListener(
          this.OnToggleSetMixTranscodingConfig);

      Toggle toggleSetGSensorMode = transform.Find("PanelTest/Viewport/Content/ToggleGSensorMode")
                                        .gameObject.GetComponent<Toggle>();
      toggleSetGSensorMode.onValueChanged.AddListener(this.OnToggleSetGSensorMode);

      // Toggle toggleStartPublishing =
      // transform.Find("PanelTest/Viewport/Content/ToggleStartPublishing").gameObject.GetComponent<Toggle>();
      // toggleStartPublishing.onValueChanged.AddListener(this.OnTogglePublishing);

      // Toggle toggleCustomCapture =
      // transform.Find("PanelOperate/Viewport/Content/ToggleCustomCapture").gameObject.GetComponent<Toggle>();
      // toggleCustomCapture.onValueChanged.AddListener(this.OnToggleCustomCapture);

      // Toggle videoMirror =
      // transform.Find("PanelOperate/Viewport/Content/VideoMirror").gameObject.GetComponent<Toggle>();
      // videoMirror.onValueChanged.AddListener(this.OnToggleVideoMirror);

      Button leaveRoomButton = transform.Find("BtnLeaveRoom").gameObject.GetComponent<Button>();
      leaveRoomButton.onClick.AddListener(this.OnLeaveRoomClick);

      mTRTCCloud = ITRTCCloud.getTRTCShareInstance();
      mTRTCCloud.addCallback(this);

      var version = mTRTCCloud.getSDKVersion();
      LogManager.Log("trtc sdk version is : " + version);

      var trtcParams =
          new TRTCParams {
            sdkAppId = GenerateTestUserSig.SDKAPPID,
            roomId = uint.Parse(DataManager.GetInstance().GetRoomID())
          };
      trtcParams.strRoomId = trtcParams.roomId.ToString();
      trtcParams.userId = DataManager.GetInstance().GetUserID();
      trtcParams.userSig =
          GenerateTestUserSig.GetInstance().GenTestUserSig(DataManager.GetInstance().GetUserID());

      trtcParams.privateMapKey = "";
      trtcParams.businessInfo = "";
      trtcParams.role = DataManager.GetInstance().roleType;
      var scene = DataManager.GetInstance().appScene;
      mTRTCCloud.enterRoom(ref trtcParams, scene);
      SetLocalAVStatus();
      var videoEncParams = DataManager.GetInstance().videoEncParam;
      mTRTCCloud.setVideoEncoderParam(ref videoEncParams);
      var videoRotation = TRTCVideoRotation.TRTCVideoRotation0;
#if UNITY_IOS && !UNITY_EDITOR
      videoRotation = TRTCVideoRotation.TRTCVideoRotation270;
#endif
      mTRTCCloud.setVideoEncoderRotation(videoRotation);

      var qosParams = DataManager.GetInstance().qosParams;  // 网络流控相关参数设置
      mTRTCCloud.setNetworkQosParam(ref qosParams);

      var videoEncParam = new TRTCVideoEncParam {
        videoResolution = TRTCVideoResolution.TRTCVideoResolution_1280_720,
        resMode = TRTCVideoResolutionMode.TRTCVideoResolutionModeLandscape, videoFps = 10,
        videoBitrate = 1600, minVideoBitrate = 1000
      };
      //  设置屏幕分享编码参数
      mTRTCCloud.setSubStreamEncoderParam(ref videoEncParam);
      LogManager.Log("setSubStreamEncoderParam ");
      // LogManager.Log(
      //     $"Scene:{scene}, Role:{trtcParams.role}, Qos-Prefer:{qosParams.preference},
      //     Qos-CtrlMode:{qosParams.controlMode}");

      LogManager.Log($"Scene:{scene}, Role:{trtcParams.role}, Qos-Prefer:{qosParams.preference}");

      userTableView.DoMuteAudio += OnMuteRemoteAudio;
      userTableView.DoMuteVideo += OnMuteRemoteVideo;
      DataManager.GetInstance().DoRoleChange += OnRoleChanged;
      DataManager.GetInstance().DoVoiceChange += OnVoiceChangeChanged;
      DataManager.GetInstance().DoEarMonitorVolumeChange += OnEarMonitorVolumeChanged;
      DataManager.GetInstance().DoVideoEncParamChange += OnVideoEncParamChanged;
      DataManager.GetInstance().DoQosParamChange += OnQosParamChanged;

#if PLATFORM_ANDROID || PLATFORM_OPENHARMONY
      if (!Permission.HasUserAuthorizedPermission(Permission.Microphone)) {
        Permission.RequestUserPermission(Permission.Microphone);
      }
      if (!Permission.HasUserAuthorizedPermission(Permission.Camera)) {
        Permission.RequestUserPermission(Permission.Camera);
      }
#endif

      audio = BackGroundMusicHelper.getInstanceGroundMusicHelper().getAudioSoucre();
    }

    void OnDestroy() {
      Debug.LogFormat("OnDestroy");
      DataManager.GetInstance().DoRoleChange -= OnRoleChanged;
      DataManager.GetInstance().DoVoiceChange -= OnVoiceChangeChanged;
      DataManager.GetInstance().DoEarMonitorVolumeChange -= OnEarMonitorVolumeChanged;
      DataManager.GetInstance().DoVideoEncParamChange -= OnVideoEncParamChanged;
      DataManager.GetInstance().DoQosParamChange -= OnQosParamChanged;
      userTableView.DoMuteAudio -= OnMuteRemoteAudio;
      userTableView.DoMuteVideo -= OnMuteRemoteVideo;

      mTRTCCloud.removeCallback(this);
      ITRTCCloud.destroyTRTCShareInstance();
      DataManager.GetInstance().ResetLocalAVFlag();
    }

    void OnLeaveRoomClick() {
      LogManager.Log("OnLeaveRoomClick");
      mTRTCCloud.exitRoom();
      DataManager.GetInstance().ResetLocalAVFlag();
    }

    void OnToggleVideoMirror(bool value) {
      if (value) {
        mTRTCCloud.setVideoEncoderMirror(true);
      } else {
        mTRTCCloud.setVideoEncoderMirror(false);
      }
    }

    private void SetLocalAVStatus() {
      TRTCRoleType role = DataManager.GetInstance().roleType;
      bool captureVideo = DataManager.GetInstance().captureVideo;
      bool muteLocalVideo = DataManager.GetInstance().muteLocalVideo;
      bool captureAudio = DataManager.GetInstance().captureAudio;
      bool muteLocalAudio = DataManager.GetInstance().muteLocalAudio;
      bool isAudience = (role == TRTCRoleType.TRTCRoleAudience);
      if (isAudience) {
        captureVideo = false;
        captureAudio = false;
      }

      if (captureVideo) {
        mTRTCCloud.startLocalPreview(true, null);
        userTableView.UpdateVideoAvailable("", TRTCVideoStreamType.TRTCVideoStreamTypeBig, true);
      } else {
        mTRTCCloud.stopLocalPreview();
        userTableView.UpdateVideoAvailable("", TRTCVideoStreamType.TRTCVideoStreamTypeBig, false);
      }

      mTRTCCloud.muteLocalVideo(muteLocalVideo);

      if (captureAudio) {
        mTRTCCloud.startLocalAudio(DataManager.GetInstance().audioQuality);
      } else {
        mTRTCCloud.stopLocalAudio();
      }

      mTRTCCloud.muteLocalAudio(muteLocalAudio);
      captureVideoToggle.interactable = !isAudience;
      captureVideoToggle.SetIsOnWithoutNotify(captureVideo);
      captureAudioToggle.interactable = !isAudience;
      captureAudioToggle.SetIsOnWithoutNotify(captureAudio);
      muteLocalVideoToggle.interactable = !isAudience;
      muteLocalVideoToggle.SetIsOnWithoutNotify(muteLocalVideo);
      // muteLocalAudioToggle.interactable = !isAudience;
      // muteLocalAudioToggle.SetIsOnWithoutNotify(muteLocalAudio);
    }

#region UI Oper

    void OnToggleMic(bool value) {
      LogManager.Log("OnToggleMic: " + value);
      if (value) {
        mTRTCCloud.startLocalAudio(DataManager.GetInstance().audioQuality);
      } else {
        mTRTCCloud.stopLocalAudio();
      }

      DataManager.GetInstance().captureAudio = value;
    }

    void OnToggleCamera(bool value) {
      LogManager.Log("OnToggleCamera: " + value);
      if (value) {
        GameObject videoView = userTableView.GetVideoView("", TRTCVideoStreamType.TRTCVideoStreamTypeBig);
        mTRTCCloud.startLocalPreview(true, videoView);
      } else {
        mTRTCCloud.stopLocalPreview();
      }
      userTableView.UpdateVideoAvailable("", TRTCVideoStreamType.TRTCVideoStreamTypeBig, value);
      DataManager.GetInstance().captureVideo = value;
    }

    void OnToggleEnableEarMonitor(bool value) {
      LogManager.Log("OnToggleEnableEarMonitor enable =" + value);
      mTRTCCloud.getAudioEffectManager().enableVoiceEarMonitor(value);
    }

    void OnToggleMuteLocalVideo(bool value) {
      LogManager.Log("OnToggleMuteLocalVideo: " + value);
      mTRTCCloud.muteLocalVideo(value);
      DataManager.GetInstance().muteLocalVideo = value;
    }

    void OnToggleMuteLocalAudio(bool value) {
      LogManager.Log("OnToggleMuteLocalAudio: " + value);
      mTRTCCloud.muteLocalAudio(value);
      DataManager.GetInstance().muteLocalAudio = value;
    }

    void OnToggleMuteRemoteAudio(bool value) {
      LogManager.Log("OnToggleMuteRemoteAudio: " + value);
      mTRTCCloud.muteAllRemoteAudio(value);
      // mTRTCCloud.enable3DSpatialAudioEffect(value);
    }

    void OnToggleScreenCapture(bool value) {
      if (value) {
        var videoEncParam = new TRTCVideoEncParam {
          videoResolution = TRTCVideoResolution.TRTCVideoResolution_1280_720,
          resMode = TRTCVideoResolutionMode.TRTCVideoResolutionModeLandscape, videoFps = 10,
          videoBitrate = 1600, minVideoBitrate = 1000
        };
#if UNITY_STANDALONE_WIN || UNITY_STANDALONE_OSX
        var thumbnailWidth = 100;
        var thumbnailHeight = 60;
        var sources = mTRTCCloud.getScreenCaptureSources(thumbnailWidth, thumbnailHeight);
        Debug.LogFormat("sources id={0}", sources.Length);
        if (sources.Length > 0) {
          mTRTCCloud.selectScreenCaptureTarget(sources[0], new Rect(0, 0, 0, 0),
                                               new TRTCScreenCaptureProperty());
          userTableView.AddUser("", TRTCVideoStreamType.TRTCVideoStreamTypeSub);
          userTableView.UpdateVideoAvailable("", TRTCVideoStreamType.TRTCVideoStreamTypeSub, true);
          mTRTCCloud.startScreenCapture(
            userTableView.GetVideoView("", TRTCVideoStreamType.TRTCVideoStreamTypeSub),
            TRTCVideoStreamType.TRTCVideoStreamTypeSub, ref videoEncParam);
        }
#elif UNITY_ANDROID || UNITY_OPENHARMONY || UNITY_IOS
        mTRTCCloud.startScreenCapture(
          userTableView.GetVideoView("", TRTCVideoStreamType.TRTCVideoStreamTypeSub),
          TRTCVideoStreamType.TRTCVideoStreamTypeSub,
          ref videoEncParam);
#endif

#if UNITY_IOS && !UNITY_EDITOR
        IosExtensionLauncher.TRTCUnityExtensionLauncher();
#endif
      } else {
        mTRTCCloud.stopScreenCapture();
#if UNITY_STANDALONE_WIN || UNITY_STANDALONE_OSX
        userTableView.UpdateVideoAvailable("", TRTCVideoStreamType.TRTCVideoStreamTypeSub, false);
        userTableView.RemoveUser("", TRTCVideoStreamType.TRTCVideoStreamTypeSub);
#endif
      }
    }

    void OnTogglePlayBackground(bool value) {
      if (value) {
        if (audio && !audio.isPlaying) {
          audio.Play();
        }
      } else {
        if (audio && audio.isPlaying) {
          audio.Stop();
        }
      }
    }

    void OnToggleShowConsole(bool value) {
      transform.Find("LogDisplayView").gameObject.SetActive(value);
    }

    void OnToggleShowUserVolume(bool value) {
      var evaluateParams = new TRTCAudioVolumeEvaluateParams { interval = 300 };
      mTRTCCloud.enableAudioVolumeEvaluation(value, evaluateParams);
      userTableView.UpdateAudioVolumeVisible(value);
    }

    void OnToggleShowStatis(bool value) {
      userTableView.UpdateUserStatisVisible(value);
    }

    void OnToggleSetting(bool value) {
      if (value) {
        var setting = Instantiate(settingPrefab, new Vector3(0, 0, 0), Quaternion.identity);
        setting.transform.SetParent(mainCanvas.transform, false);
        settingScript = setting.GetComponent<SettingScript>();
      } else {
        if (settingScript != null) {
          Transform.Destroy(settingScript.gameObject);
          settingScript = null;
        }
      }
    }

    void OnToggleSendSEIMsg(bool value) {
      if (value) {
        // byte[] seiMsg = new byte[] {2, 0, 0, 0, 0, 0,1,1, 0, 0,1,1};
        byte[] seiMsg = new byte[] { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

        // byte[] seiMsg = m_byteFacialData.ToArray();

        string strInfo = "";
        for (int i = 0; i < seiMsg.Length; i++) {
          strInfo += seiMsg[i].ToString() + ", ";
        }

        LogManager.Log("seiMsg.Length: " + seiMsg.Length);
        LogManager.Log("seiMsg strInfo: " + strInfo);

        var result = mTRTCCloud.sendSEIMsg(seiMsg, seiMsg.Length, 1);

        // string seiMsg = "test sei messagetest sei messagetest sei messagetest sei messagetest sei
        // messagetest sei message"; int msgSize = System.Text.Encoding.UTF8.GetByteCount(seiMsg);
        // LogManager.Log(String.Format("----> sendSEIMsg seiMsg= {0}, msgSize = {1}", seiMsg,
        // msgSize)); mTRTCCloud.sendSEIMsg(System.Text.Encoding.UTF8.GetBytes(seiMsg), msgSize,
        // 30);
      }
    }

    void OnToggleSwitchCamera(bool value) {
      LogManager.Log("OnToggleSwitchCamera: " + value);
#if UNITY_IOS && !UNITY_EDITOR
      if (value) {
        mTRTCCloud.setVideoEncoderRotation(TRTCVideoRotation.TRTCVideoRotation90);
      } else {
        mTRTCCloud.setVideoEncoderRotation(TRTCVideoRotation.TRTCVideoRotation270);
      }
#endif
      mTRTCCloud.getDeviceManager().switchCamera(!value);
    }

    void OnToggleBeauty(bool value) {
      if (value) {
        mTRTCCloud.setBeautyStyle(TRTCBeautyStyle.TRTCBeautyStyleSmooth, 9, 9, 9);
      } else {
        mTRTCCloud.setBeautyStyle(TRTCBeautyStyle.TRTCBeautyStyleSmooth, 0, 0, 0);
      }
    }

    void OnToggleSetMixTranscodingConfig(bool value) {
      TRTCTranscodingConfig transcodingConfig = new TRTCTranscodingConfig();
      transcodingConfig.appId = 1400704311;
      transcodingConfig.bizId = 3891;
      transcodingConfig.videoWidth = 360;
      transcodingConfig.mode = TRTCTranscodingConfigMode.TRTCTranscodingConfigMode_Manual;
      transcodingConfig.videoHeight = 640;
      transcodingConfig.videoFramerate = 15;
      transcodingConfig.videoGOP = 2;
      transcodingConfig.videoBitrate = 1000;
      transcodingConfig.audioBitrate = 64;
      transcodingConfig.audioSampleRate = 48000;
      transcodingConfig.audioChannels = 2;
      // 查看
      // http://liteavapp.qcloud.com/live/streamIdtest.flv
      transcodingConfig.streamId = "streamIdtest";
      TRTCMixUser[] mixUsersArray = new TRTCMixUser[2];
      mixUsersArray[0].userId = DataManager.GetInstance().GetUserID();
      mixUsersArray[0].zOrder = 0;  // zOrder 为0代表主播画面位于最底层
      mixUsersArray[0].streamType = TRTCVideoStreamType.TRTCVideoStreamTypeBig;
      mixUsersArray[0].rect.left = 0;
      mixUsersArray[0].rect.top = 0;
      mixUsersArray[0].rect.right = 360;
      mixUsersArray[0].rect.bottom = 640;
      mixUsersArray[0].soundLevel = 100;

      mixUsersArray[1].userId = "345";
      mixUsersArray[1].zOrder = 3;
      mixUsersArray[1].streamType = TRTCVideoStreamType.TRTCVideoStreamTypeBig;
      mixUsersArray[1].rect.left = 10;         // 仅供参考
      mixUsersArray[1].rect.top = 10;          // 仅供参考
      mixUsersArray[1].rect.right = 10 + 60;   // 仅供参考
      mixUsersArray[1].rect.bottom = 10 + 60;  // 仅供参考
      mixUsersArray[1].roomId =
          DataManager.GetInstance().GetRoomID();  // 本地用户不用填写 roomID，远程需要
      mixUsersArray[1].soundLevel = 100;

      transcodingConfig.mixUsersArray = mixUsersArray;
      transcodingConfig.mixUsersArraySize = 2;
      if (value)
        mTRTCCloud.setMixTranscodingConfig(transcodingConfig);
      else
        mTRTCCloud.setMixTranscodingConfig(null);
    }

    void OnToggleSetGSensorMode(bool value) {
      var data = new JsonData { ["api"] = "setGSensorMode" };
      var param = new JsonData {
        ["StreamType"] = 0,               // 0:big, 1:small, 2:sub
        ["gSensorMode"] = value ? 1 : 0,  // 0:Disable 1:UIAutoLayout, 2:UIFixLayout
      };
      data["params"] = param;
      var api = data.ToJson();
      LogManager.Log($"callExperimentalAPI: {api}");
      mTRTCCloud.callExperimentalAPI(api);
    }

#endregion

#region Setting UI Callback

    void OnMuteRemoteAudio(string userId, bool mute) {
      LogManager.Log("MuteRemoteAudio: " + userId + "-" + mute);
      mTRTCCloud.muteRemoteAudio(userId, mute);
    }

    void OnMuteRemoteVideo(string userId, bool mute) {
      LogManager.Log("MuteRemoteVideo: " + userId + "-" + mute);
      // mTRTCCloud.muteRemoteVideoStream(userId, mute);
    }

    void OnTogglePublishing(bool value) {
      // Toggle toggleStartPublishing =
      // transform.Find("PanelTest/Viewport/Content/ToggleStartPublishing").gameObject.GetComponent<Toggle>();
      // if (value)
      // {
      //     mTRTCCloud.startPublishing("test", TRTCVideoStreamType.TRTCVideoStreamTypeBig);
      // }
      // else
      // {
      //     mTRTCCloud.stopPublishing();
      // }
    }

    void OnToggleCustomCapture(bool value) {
      if (value) {
        var customCapture =
            Instantiate(customCapturePrefab, new Vector3(0, 0, 0), Quaternion.identity);
        customCapture.transform.SetParent(mainCanvas.transform, false);
        customCaptureScript = customCapture.GetComponent<CustomCaptureScript>();
        customCaptureScript.AudioCallback += CustomCaptureAudioCallback;
        customCaptureScript.VideoCallback += CustomCaptureVideoCallback;
      } else {
        if (customCaptureScript != null) {
          Transform.Destroy(customCaptureScript.gameObject);
          customCaptureScript = null;
        }
      }
    }

    void OnRoleChanged() {
      SetLocalAVStatus();
      mTRTCCloud.switchRole(DataManager.GetInstance().roleType);
    }

    void OnVoiceChangeChanged() {
      TXVoiceChangeType type = DataManager.GetInstance().voiceChangeType;
      LogManager.Log("OnVoiceChangeChanged type =" + type);
      mTRTCCloud.getAudioEffectManager().setVoiceChangerType(type);
    }

    void OnEarMonitorVolumeChanged() {
      int volume = DataManager.GetInstance().earMonitorVolume;
      LogManager.Log("OnEarMonitorVolumeChanged volume =" + volume);
      mTRTCCloud.getAudioEffectManager().setVoiceEarMonitorVolume(volume);
    }

    void OnVideoEncParamChanged() {
      TRTCVideoEncParam videoEncParams = DataManager.GetInstance().videoEncParam;
      mTRTCCloud.setVideoEncoderParam(ref videoEncParams);
    }

    void OnQosParamChanged() {
      TRTCNetworkQosParam qosParams = DataManager.GetInstance().qosParams;
      mTRTCCloud.setNetworkQosParam(ref qosParams);
    }

    void CustomCaptureAudioCallback(bool stop) {
      if (!stop) {
        mTRTCCloud.stopLocalAudio();
      } else {
        Toggle toggleMic = transform.Find("PanelOperate/Viewport/Content/ToggleMic")
                               .gameObject.GetComponent<Toggle>();
        if (!toggleMic.isOn) {
          return;
        }

        mTRTCCloud.startLocalAudio(DataManager.GetInstance().audioQuality);
        Toggle toggleMuteLocalAudio =
            transform.Find("PanelOperate/Viewport/Content/ToggleMuteLocalAudio")
                .gameObject.GetComponent<Toggle>();
        if (toggleMuteLocalAudio.isOn) {
          mTRTCCloud.muteLocalAudio(true);
        } else {
          mTRTCCloud.muteLocalAudio(false);
        }
      }
    }

    void CustomCaptureVideoCallback(bool stop) {
      if (!stop) {
        mTRTCCloud.stopLocalPreview();
      } else {
        Toggle toggelCamera = transform.Find("PanelOperate/Viewport/Content/ToggleCamera")
                                  .gameObject.GetComponent<Toggle>();
        if (!toggelCamera.isOn) {
          return;
        }

        mTRTCCloud.startLocalPreview(true, null);

        Toggle toggleMuteLocalVideo =
            transform.Find("PanelOperate/Viewport/Content/ToggleMuteLocalVideo")
                .gameObject.GetComponent<Toggle>();
        if (toggleMuteLocalVideo.isOn) {
          mTRTCCloud.muteLocalVideo(true);
        } else {
          mTRTCCloud.muteLocalVideo(false);
        }
      }
    }

#endregion

#region ITRTCCloudCallback

    public void onError(TXLiteAVError errCode, String errMsg, IntPtr arg) {
      LogManager.Log($"onError {errCode}, {errMsg}");
    }

    public void onWarning(TXLiteAVWarning warningCode, String warningMsg, IntPtr arg) {
      LogManager.Log($"onWarning {warningCode}, {warningMsg}");
    }

    public void onEnterRoom(int result) {
      LogManager.Log($"onEnterRoom {result}");
      userTableView.AddUser("", TRTCVideoStreamType.TRTCVideoStreamTypeBig);
    }

    public void onExitRoom(int reason) {
      LogManager.Log($"onExitRoom {reason}");
      userTableView.RemoveUser("", TRTCVideoStreamType.TRTCVideoStreamTypeBig);
      SceneManager.LoadScene("HomeScene", LoadSceneMode.Single);
    }

    public void onSwitchRole(TXLiteAVError errCode, String errMsg) {
      LogManager.Log($"onSwitchRole {errCode}, {errMsg}");
    }

    public void onRemoteUserEnterRoom(String userId) {
      LogManager.Log(String.Format("onRemoteUserEnterRoom {0}", userId));
    }

    public void onRemoteUserLeaveRoomWeb(String jsonStr) {
      JsonData obj = JsonMapper.ToObject(jsonStr);
      onRemoteUserLeaveRoom(obj["userId"].ToString(), (int)obj["reason"]);
    }

    public void onMicListWeb(String jsonStr) {
      JsonData obj = JsonMapper.ToObject(jsonStr);
      LogManager.Log($"onMicListWeb {obj[0]["deviceId"]}, {obj[0]["deviceName"]}");
    }

    public void onSpeakerListWeb(String jsonStr) {
      JsonData obj = JsonMapper.ToObject(jsonStr);
      LogManager.Log($"onSpeakerListWeb {obj[0]["deviceId"]}, {obj[0]["deviceName"]}");
    }

    public void onCurrentSpeakerWeb(String jsonStr) {
      JsonData obj = JsonMapper.ToObject(jsonStr);
      LogManager.Log($"onCurrentSpeakerWeb {obj["deviceId"]}, {obj["deviceName"]}");
    }

    public void onCurrentMicWeb(String jsonStr) {
      JsonData obj = JsonMapper.ToObject(jsonStr);
      LogManager.Log($"onCurrentMicWeb {obj["deviceId"]}, {obj["deviceName"]}");
    }

    public void onRemoteUserLeaveRoom(String userId, int reason) {
      LogManager.Log($"onRemoteUserLeaveRoom {userId}, {reason}");
      userTableView.RemoveUser(userId, TRTCVideoStreamType.TRTCVideoStreamTypeBig);
    }

    public void onUserVideoAvailable(String userId, bool available) {
      LogManager.Log($"onUserVideoAvailable {userId}, {available}");
      // Important: startRemoteView is needed for receiving video stream.
      if (available) {
        userTableView.AddUser(userId, TRTCVideoStreamType.TRTCVideoStreamTypeBig);
        var videoView = userTableView.GetVideoView(userId, TRTCVideoStreamType.TRTCVideoStreamTypeBig);
        mTRTCCloud.startRemoteView(userId, TRTCVideoStreamType.TRTCVideoStreamTypeBig, videoView);
      } else {
        mTRTCCloud.stopRemoteView(userId, TRTCVideoStreamType.TRTCVideoStreamTypeBig);
      }

      userTableView.UpdateVideoAvailable(userId, TRTCVideoStreamType.TRTCVideoStreamTypeBig,
                                         available);
    }

    public void onUserSubStreamAvailable(String userId, bool available) {
      LogManager.Log($"onUserSubStreamAvailable {userId}, {available}");
      // Important: startRemoteView is needed for receiving video stream.
      if (available) {
        userTableView.AddUser(userId, TRTCVideoStreamType.TRTCVideoStreamTypeSub);
        userTableView.UpdateVideoAvailable(userId, TRTCVideoStreamType.TRTCVideoStreamTypeSub,
                                           true);
        var videoView = userTableView.GetVideoView(userId, TRTCVideoStreamType.TRTCVideoStreamTypeSub);
        mTRTCCloud.startRemoteView(userId, TRTCVideoStreamType.TRTCVideoStreamTypeSub, videoView);
      } else {
        mTRTCCloud.stopRemoteView(userId, TRTCVideoStreamType.TRTCVideoStreamTypeSub);
        userTableView.RemoveUser(userId, TRTCVideoStreamType.TRTCVideoStreamTypeSub);
      }
    }

    public void onUserAudioAvailableWeb(String jsonStr) {
      JsonData obj = JsonMapper.ToObject(jsonStr);
      onUserAudioAvailable(obj["userId"].ToString(), (bool)obj["available"]);
    }

    public void onUserAudioAvailable(String userId, bool available) {
      LogManager.Log($"onUserAudioAvailable {userId}, {available}");
      if (available) {
        userTableView.AddUser(userId, TRTCVideoStreamType.TRTCVideoStreamTypeBig);
      }

      userTableView.UpdateAudioAvailable(userId, TRTCVideoStreamType.TRTCVideoStreamTypeBig,
                                         available);
    }

    public void onFirstVideoFrame(String userId,
                                  TRTCVideoStreamType streamType,
                                  int width,
                                  int height) {
      LogManager.Log($"onFirstVideoFrame {userId}, {streamType}, {width}, {height}");
    }

    public void onFirstAudioFrame(String userId) {
      LogManager.Log($"onFirstAudioFrame {userId}");
    }

    public void onSendFirstLocalVideoFrame(TRTCVideoStreamType streamType) {
      LogManager.Log($"onSendFirstLocalVideoFrame {streamType}");
    }

    public void onSendFirstLocalAudioFrame() {
      LogManager.Log("onSendFirstLocalAudioFrame");
    }

    public void onNetworkQuality(TRTCQualityInfo localQuality,
                                 TRTCQualityInfo[] remoteQuality,
                                 UInt32 remoteQualityCount) {
      LogManager.Log(
          $"onNetworkQuality localQuality = {localQuality.quality}, remoteQualityCount = {remoteQualityCount}");
    }

    public void onStatistics(TRTCStatistics statis) {
      string localStatisText;
      foreach (var local in statis.localStatisticsArray) {
        localStatisText = string.Format(
            "width: {0}\r\nheight: {1}\r\nvideoframerate: {2}\r\nvideoBitrate: {3}\r\naudioSampleRate: {4}\r\naudioBitrate:{5}\r\nstreamType:{6}\r\n",
            local.width, local.height, local.frameRate, local.videoBitrate, local.audioSampleRate,
            local.audioBitrate, local.streamType);
        userTableView.updateUserStatistics("", local.streamType, localStatisText);
      }

      foreach (var remote in statis.remoteStatisticsArray) {
        string remoteStatisText;
        remoteStatisText = string.Format(
            "finalLoss: {7}\r\njitterBufferDelay: {8}\r\nwidth: {0}\r\nheight: {1}\r\nvideoframerate: {2}\r\nvideoBitrate: {3}\r\naudioSampleRate: {4}\r\naudioBitrate:{5}\r\nstreamType:{6}\r\n",
            remote.width, remote.height, remote.frameRate, remote.videoBitrate,
            remote.audioSampleRate, remote.audioBitrate, remote.streamType, remote.finalLoss,
            remote.jitterBufferDelay);
        userTableView.updateUserStatistics(remote.userId, remote.streamType, remoteStatisText);
      }
    }

    public void onConnectionLost() {
      LogManager.Log("onConnectionLost");
    }

    public void onTryToReconnect() {
      LogManager.Log("onTryToReconnect");
    }

    public void onConnectionRecovery() {
      LogManager.Log("onConnectionRecovery");
    }

    public void onCameraDidReady() {
      LogManager.Log("onCameraDidReady");
    }

    public void onMicDidReady() {
      LogManager.Log("onMicDidReady");
    }

    public void onUserVoiceVolume(TRTCVolumeInfo[] userVolumes,
                                  UInt32 userVolumesCount,
                                  UInt32 totalVolume) {
      foreach (TRTCVolumeInfo userVolume in userVolumes) {
        userTableView.UpdateAudioVolume(
            userVolume.userId, TRTCVideoStreamType.TRTCVideoStreamTypeBig, userVolume.volume);
      }
    }

    public void onDeviceChange(String deviceId, TRTCDeviceType type, TRTCDeviceState state) {
      LogManager.Log($"onSwitchRole {deviceId}, {type}, {state}");
    }

    public void onRecvSEIMsg(String userId, Byte[] message, UInt32 msgSize) {
      LogManager.Log("onRecvSEIMsg: " + userId + ", " + msgSize + ", " + msgSize);
      string strInfo = "";
      for (var i = 0; i < msgSize; i++) {
        strInfo += message[i] + ", ";
      }

      LogManager.Log("strInfo: " + strInfo);
    }

    public void onStartPublishing(int err, string errMsg) {
      LogManager.Log($"onStartPublishing {err}, {errMsg}");
    }

    public void onStopPublishing(int err, string errMsg) {
      LogManager.Log($"onStopPublishing {err}, {errMsg}");
    }

    public void onScreenCaptureStarted() {
      LogManager.Log("onScreenCaptureStarted");
    }

    public void onScreenCapturePaused(int reason) {
      LogManager.Log($"onScreenCapturePaused {reason}");
    }

    public void onScreenCaptureResumed(int reason) {
      LogManager.Log($"onScreenCaptureResumed {reason}");
    }

    public void onScreenCaptureStoped(int reason) {
      LogManager.Log($"onScreenCaptureStoped {reason}");
    }

    public void onScreenCaptureCovered() {
      LogManager.Log($"onScreenCaptureCovered ");
    }

    public void onStartPublishCDNStream(int err, string errMsg) {
      LogManager.Log($"onStartPublishCDNStream {err}, {errMsg}");
    }

    public void onStopPublishCDNStream(int err, string errMsg) {
      LogManager.Log($"onStopPublishCDNStream {err}, {errMsg}");
    }

    public void onStartPublishMediaStream(string taskID,
                                          int code,
                                          string message,
                                          string extraInfo) {
      LogManager.Log($"onStartPublishMediaStream taskID: {taskID}, {code}, {message}, {extraInfo}");
    }

    public void onUpdatePublishMediaStream(string taskID,
                                           int code,
                                           string message,
                                           string extraInfo) {
      LogManager.Log(
          $"onUpdatePublishMediaStream taskID: {taskID}, {code}, {message}, {extraInfo}");
    }

    public void onStopPublishMediaStream(string taskID,
                                         int code,
                                         string message,
                                         string extraInfo) {
      LogManager.Log($"onStopPublishMediaStream taskID: {taskID}, {code}, {message}, {extraInfo}");
    }

    public void onCdnStreamStateChanged(string cdnURL,
                                        int status,
                                        int code,
                                        string message,
                                        string extraInfo) {
      LogManager.Log(
          $"onCdnStreamStateChanged cdnURL: {cdnURL}, {status}, {code}, {message}, {extraInfo}");
    }

    public void onConnectOtherRoom(string userId, TXLiteAVError errCode, string errMsg) {
      LogManager.Log($"onConnectOtherRoom {userId}, {errCode}, {errMsg}");
    }

    public void onDisconnectOtherRoom(TXLiteAVError errCode, string errMsg) {
      LogManager.Log($"onDisconnectOtherRoom {errCode}, {errMsg}");
    }

    public void onSwitchRoom(TXLiteAVError errCode, string errMsg) {
      LogManager.Log($"onSwitchRoom {errCode}, {errMsg}");
    }

    public void onSpeedTestResult(TRTCSpeedTestResult result) {
      LogManager.Log($"TRTCSpeedTestResult {result}");
    }

    [Obsolete("use onSpeedTestResult(TRTCSpeedTestResult)")]
    public void onSpeedTest(TRTCSpeedTestResult currentResult, int finishedCount, int totalCount) {
      LogManager.Log($"onSpeedTest {currentResult.upLostRate}, {finishedCount} ,{totalCount}");
    }

    public void onTestMicVolume(int volume) {
      LogManager.Log($"onTestMicVolume {volume}");
    }

    public void onTestSpeakerVolume(int volume) {
      LogManager.Log($"onTestSpeakerVolume {volume}");
    }

    public void onAudioDeviceCaptureVolumeChanged(int volume, bool muted) {
      LogManager.Log($"onAudioDeviceCaptureVolumeChanged {volume} , {muted}");
    }

    public void onAudioDevicePlayoutVolumeChanged(int volume, bool muted) {
      LogManager.Log($"onAudioDevicePlayoutVolumeChanged {volume} , {muted}");
    }

    public void onRecvCustomCmdMsg(string userId,
                                   int cmdID,
                                   int seq,
                                   byte[] message,
                                   int messageSize) {
      string msg = System.Text.Encoding.UTF8.GetString(message, 0, messageSize);
      LogManager.Log(Environment.NewLine + $"onRecvCustomCmdMsg {userId}, {cmdID} ,{msg}");
    }

    public void onMissCustomCmdMsg(string userId, int cmdID, int errCode, int missed) {
      LogManager.Log($"onMissCustomCmdMsg {userId}, {cmdID}");
    }

    public void onSnapshotComplete(string userId,
                                   TRTCVideoStreamType type,
                                   byte[] data,
                                   int length,
                                   int width,
                                   int height,
                                   TRTCVideoPixelFormat format) {
      LogManager.Log($"onSnapshotComplete {userId} , {type}");
    }

    public void onSetMixTranscodingConfig(int errCode, String errMsg) {
      LogManager.Log($"onSetMixTranscodingConfig {errCode} , {errMsg}");
    }

#endregion
  }
}