using System.Collections;
using System.Collections.Generic;
using System;
using UnityEngine;
using UnityEngine.UI;
using LitJson;
using trtc;

namespace TRTCCUnityDemo {
  public class SettingScript : MonoBehaviour {
    public Toggle sceneVideoCallToggle;
    public Toggle sceneLiveToggle;

    public Toggle roleAnchorToggle;
    public Toggle roleAudienceToggle;

    public Toggle preferSmoothToggle;
    public Toggle preferClearToggle;

    public Toggle ctrlClientToggle;
    public Toggle ctrlServerToggle;
    public Toggle enableAIDenoiseToggle;
    public Dropdown voiceChangerDropDown;
    public Dropdown audioQualityDropDown;
    public Slider earMonitorVolumeSlider;

    public Dropdown resolutionDropDown;
    public Dropdown fpsDropDown;
    public Dropdown directionDropDown;
    public Slider bitrateSlider;
    public Text curBitrateText;

    public Dropdown rotationDropDown;
    public Dropdown fillModeDropDown;
    public Dropdown mirrorTypeDropDown;
    public Dropdown streamTypeDropDown;
    private ITRTCCloud mTRTCCloud;
    private TRTCVideoStreamType mStreamType;
    private Dropdown mLocalVideoStreamTypeDropDown;
    private Toggle mEnableLocalVideoCustomToggle;

    private TRTCRenderParams mRenderParam = new TRTCRenderParams();
    private DataManager.TRTCRenderIndex mRenderIndex = new DataManager.TRTCRenderIndex(0, 0, 0, 0);

    void Start() {
      mTRTCCloud = ITRTCCloud.getTRTCShareInstance();
      SetUpScene();
      SetUpRole();
      SetUpNetworkQos();
      SetUpVoiceChanger();
      SetupAudioQuality();
      SetupEarMonitorVolume();
      SetUpResolution();
      SetUpFps();
      SetUpDirection();
      SetUpBitrate();
      SetupRemoteVideoSetting();
      SetupLocalVideoStream();
      SetupEnableLocalVideoCustom();
    }

    private void SetUpScene() {
      if (DataManager.GetInstance().appScene == TRTCAppScene.TRTCAppSceneVideoCall) {
        sceneVideoCallToggle.isOn = true;
      } else {
        sceneLiveToggle.isOn = true;
      }
      sceneVideoCallToggle.onValueChanged.AddListener(this.SceneVideoCallToggleValueChanged);
      sceneLiveToggle.onValueChanged.AddListener(this.SceneLiveToggleValueChanged);
    }

    private void SetUpRole() {
      if (DataManager.GetInstance().roleType == TRTCRoleType.TRTCRoleAnchor) {
        roleAnchorToggle.isOn = true;
      } else {
        roleAudienceToggle.isOn = true;
      }
      roleAnchorToggle.onValueChanged.AddListener(this.RoleAnchorToggleValueChanged);
      roleAudienceToggle.onValueChanged.AddListener(this.RoleAudienceToggleValueChanged);

      roleAudienceToggle.interactable = !sceneVideoCallToggle.isOn;
    }

    private void SetUpNetworkQos() {
      TRTCNetworkQosParam param = DataManager.GetInstance().qosParams;

      if (param.preference == TRTCVideoQosPreference.TRTCVideoQosPreferenceSmooth) {
        preferSmoothToggle.isOn = true;
      } else {
        preferClearToggle.isOn = true;
      }

      // if (param.controlMode == TRTCQosControlMode.TRTCQosControlModeClient)
      //{
      //     ctrlClientToggle.isOn = true;
      // }
      // else
      //{
      //     ctrlServerToggle.isOn = true;
      // }

      preferSmoothToggle.onValueChanged.AddListener(this.PreferSmoothToggleValueChanged);
      preferClearToggle.onValueChanged.AddListener(this.PreferClearToggleValueChanged);
      ctrlClientToggle.onValueChanged.AddListener(this.CtrlClientToggleValueChanged);
      ctrlServerToggle.onValueChanged.AddListener(this.CtrlServerToggleValueChanged);
      enableAIDenoiseToggle.onValueChanged.AddListener(this.EnableAIDenoiseToggleValueChanged);
    }
    private void SetUpVoiceChanger() {
      List<string> resNames = new List<string>(
          new string[] { "0 - Original", "1 - Child", "2 - Little girl", "3 - Middle-aged man",
                         "4 - Metal", "5 - Nasal", "6 - Punk", "7 - Beast", "8 - Fat boy",
                         "9 - Electric", "10 - Robot", "11 - Ethereal" });
      TXVoiceChangeType curType = DataManager.GetInstance().voiceChangeType;
      int curIndex = 0;
      switch (curType) {
        case TXVoiceChangeType.TXVoiceChangeType_0:
          curIndex = 0;
          break;
        case TXVoiceChangeType.TXVoiceChangeType_1:
          curIndex = 1;
          break;
        case TXVoiceChangeType.TXVoiceChangeType_2:
          curIndex = 2;
          break;
        case TXVoiceChangeType.TXVoiceChangeType_3:
          curIndex = 3;
          break;
        case TXVoiceChangeType.TXVoiceChangeType_4:
          curIndex = 4;
          break;
        case TXVoiceChangeType.TXVoiceChangeType_5:
          curIndex = 5;
          break;
        case TXVoiceChangeType.TXVoiceChangeType_6:
          curIndex = 6;
          break;
        case TXVoiceChangeType.TXVoiceChangeType_7:
          curIndex = 7;
          break;
        case TXVoiceChangeType.TXVoiceChangeType_8:
          curIndex = 8;
          break;
        case TXVoiceChangeType.TXVoiceChangeType_9:
          curIndex = 9;
          break;
        case TXVoiceChangeType.TXVoiceChangeType_10:
          curIndex = 10;
          break;
        case TXVoiceChangeType.TXVoiceChangeType_11:
          curIndex = 11;
          break;
      }
      voiceChangerDropDown.AddOptions(resNames);
      voiceChangerDropDown.value = curIndex;
      voiceChangerDropDown.onValueChanged.AddListener(this.VoiceChangerDropDownValueChanged);
    }

    private void SetupAudioQuality() {
      TRTCAudioQuality curType = DataManager.GetInstance().audioQuality;
      audioQualityDropDown.value = (int)curType - 1;
      audioQualityDropDown.onValueChanged.AddListener(this.AudioQualityDropDownValueChanged);
    }

    private void SetupEarMonitorVolume() {
      earMonitorVolumeSlider.maxValue = 150;
      earMonitorVolumeSlider.minValue = 0;
      earMonitorVolumeSlider.value = DataManager.GetInstance().earMonitorVolume;
      ;
      earMonitorVolumeSlider.onValueChanged.AddListener(this.EarMonitorVolumeSliderValueChanged);
    }

    private void SetUpResolution() {
      List<string> resNames = new List<string>(
          new string[] { "120 x 120", "160 x 160", "270 x 270", "480 x 480", "160 x 120",
                         "240 x 180", "280 x 210", "320 x 240", "400 x 300", "480 x 360",
                         "640 x 480", "960 x 720", "320 x 180", "480 x 270", "640 x 360",
                         "960 x 540", "1280 x 720", "1920 x 1080" });
      TRTCVideoResolution curResolution = DataManager.GetInstance().videoEncParam.videoResolution;
      int curIndex = 0;
      switch (curResolution) {
        case TRTCVideoResolution.TRTCVideoResolution_120_120:
          curIndex = 0;
          break;
        case TRTCVideoResolution.TRTCVideoResolution_160_160:
          curIndex = 1;
          break;
        case TRTCVideoResolution.TRTCVideoResolution_270_270:
          curIndex = 2;
          break;
        case TRTCVideoResolution.TRTCVideoResolution_480_480:
          curIndex = 3;
          break;
        case TRTCVideoResolution.TRTCVideoResolution_160_120:
          curIndex = 4;
          break;
        case TRTCVideoResolution.TRTCVideoResolution_240_180:
          curIndex = 5;
          break;
        case TRTCVideoResolution.TRTCVideoResolution_280_210:
          curIndex = 6;
          break;
        case TRTCVideoResolution.TRTCVideoResolution_320_240:
          curIndex = 7;
          break;
        case TRTCVideoResolution.TRTCVideoResolution_400_300:
          curIndex = 8;
          break;
        case TRTCVideoResolution.TRTCVideoResolution_480_360:
          curIndex = 9;
          break;
        case TRTCVideoResolution.TRTCVideoResolution_640_480:
          curIndex = 10;
          break;
        case TRTCVideoResolution.TRTCVideoResolution_960_720:
          curIndex = 11;
          break;
        case TRTCVideoResolution.TRTCVideoResolution_320_180:
          curIndex = 12;
          break;
        case TRTCVideoResolution.TRTCVideoResolution_480_270:
          curIndex = 13;
          break;
        case TRTCVideoResolution.TRTCVideoResolution_640_360:
          curIndex = 14;
          break;
        case TRTCVideoResolution.TRTCVideoResolution_960_540:
          curIndex = 15;
          break;
        case TRTCVideoResolution.TRTCVideoResolution_1280_720:
          curIndex = 16;
          break;
        case TRTCVideoResolution.TRTCVideoResolution_1920_1080:
          curIndex = 17;
          break;
      }
      resolutionDropDown.AddOptions(resNames);
      resolutionDropDown.value = curIndex;
      resolutionDropDown.onValueChanged.AddListener(this.ResolutionDropDownValueChanged);
    }

    private void SetUpFps() {
      List<string> fpsNames = new List<string>(new string[] { "15 fps", "20 fps", "24 fps" });
      fpsDropDown.AddOptions(fpsNames);
      uint fps = DataManager.GetInstance().videoEncParam.videoFps;
      int curIndex = 0;
      switch (fps) {
        case 15:
          curIndex = 0;
          break;
        case 20:
          curIndex = 1;
          break;
        case 24:
          curIndex = 2;
          break;
      }
      fpsDropDown.value = curIndex;
      fpsDropDown.onValueChanged.AddListener(this.FpsDropDownValueChanged);
    }

    private void SetUpDirection() {
      List<string> directionNames =
          new List<string>(new string[] { "Horizontal screen mode", "Vertical screen mode" });
      directionDropDown.AddOptions(directionNames);
      int curIndex = 0;
      if (DataManager.GetInstance().videoEncParam.resMode ==
          TRTCVideoResolutionMode.TRTCVideoResolutionModeLandscape) {
        curIndex = 0;
      } else {
        curIndex = 1;
      }
      directionDropDown.value = curIndex;
      directionDropDown.onValueChanged.AddListener(this.DirectionDropDownValueChanged);
    }

    private void SetUpBitrate() {
      TRTCVideoEncParam param = DataManager.GetInstance().videoEncParam;
      bitrateSlider.minValue = param.minVideoBitrate;
      bitrateSlider.value = param.videoBitrate;

      DataManager.VideoResBitrateTable bitrateInfo =
          DataManager.GetInstance().GetBitrateInfo((int)param.videoResolution);
      bitrateSlider.maxValue = bitrateInfo.maxBitrate;

      bitrateSlider.onValueChanged.AddListener(this.BitrateSliderValueChanged);

      curBitrateText.text = param.videoBitrate.ToString() + "kps";
    }

    public void SetupRemoteVideoSetting() {
      mRenderParam.rotation = TRTCVideoRotation.TRTCVideoRotation0;
      mRenderParam.fillMode = TRTCVideoFillMode.TRTCVideoFillMode_Fit;
      mRenderParam.mirrorType = TRTCVideoMirrorType.TRTCVideoMirrorType_Disable;
      mStreamType = TRTCVideoStreamType.TRTCVideoStreamTypeBig;
      GameObject rotationObj =
          transform.Find("remoteVideoPanel/rotationPanel/rotationDropdown").gameObject;
      mRenderIndex = DataManager.GetInstance().GetTRTCRenderIndex();
      if (rotationObj != null) {
        rotationDropDown = rotationObj.GetComponent<Dropdown>();
        rotationDropDown.onValueChanged.AddListener(this.rotationDropDownValueChanged);
        rotationDropDown.value = mRenderIndex.rotationIndex;
      }

      GameObject fillModeObj =
          transform.Find("remoteVideoPanel/fillModePanel/fillModeDropdown").gameObject;
      if (fillModeObj != null) {
        fillModeDropDown = fillModeObj.GetComponent<Dropdown>();

        fillModeDropDown.value = mRenderIndex.fillModeIndex;

        fillModeDropDown.onValueChanged.AddListener(this.fillModeDropDownValueChanged);
      }

      GameObject mirrorTypeObj =
          transform.Find("remoteVideoPanel/mirrorTypePanel/mirrorTypeDropdown").gameObject;
      if (mirrorTypeObj != null) {
        mirrorTypeDropDown = mirrorTypeObj.GetComponent<Dropdown>();
        mirrorTypeDropDown.value = mRenderIndex.mirrorTypeIndex;
        mirrorTypeDropDown.onValueChanged.AddListener(this.mirrorTypeDropDownValueChanged);
      }

      GameObject streamTypeObj =
          transform.Find("remoteVideoPanel/streamTypePanel/streamTypeDropdown").gameObject;
      if (streamTypeObj != null) {
        streamTypeDropDown = streamTypeObj.GetComponent<Dropdown>();
        streamTypeDropDown.value = mRenderIndex.streamTypeIndex;
        streamTypeDropDown.onValueChanged.AddListener(this.streamTypeDropDownValueChanged);
      }
    }

    private void rotationDropDownValueChanged(int value) {
      switch (value) {
        case 0:
          mRenderParam.rotation = TRTCVideoRotation.TRTCVideoRotation0;
          break;
        case 1:
          mRenderParam.rotation = TRTCVideoRotation.TRTCVideoRotation90;
          break;
        case 2:
          mRenderParam.rotation = TRTCVideoRotation.TRTCVideoRotation180;
          break;
        case 3:
          mRenderParam.rotation = TRTCVideoRotation.TRTCVideoRotation270;
          break;
        default:
          mRenderParam.rotation = TRTCVideoRotation.TRTCVideoRotation0;
          break;
      }
      mRenderIndex.rotationIndex = value;
      DataManager.GetInstance().SetTRTCRenderIndex(mRenderIndex);
      mTRTCCloud.setRemoteRenderParams("345", mStreamType, ref mRenderParam);
    }

    private void fillModeDropDownValueChanged(int value) {
      switch (value) {
        case 0:
          mRenderParam.fillMode = TRTCVideoFillMode.TRTCVideoFillMode_Fit;
          break;
        case 1:
          mRenderParam.fillMode = TRTCVideoFillMode.TRTCVideoFillMode_Fill;
          break;
        default:
          mRenderParam.fillMode = TRTCVideoFillMode.TRTCVideoFillMode_Fit;
          break;
      }
      mRenderIndex.fillModeIndex = value;
      DataManager.GetInstance().SetTRTCRenderIndex(mRenderIndex);
      mTRTCCloud.setRemoteRenderParams("345", mStreamType, ref mRenderParam);
    }

    private void mirrorTypeDropDownValueChanged(int value) {
      switch (value) {
        case 0:
          mRenderParam.mirrorType = TRTCVideoMirrorType.TRTCVideoMirrorType_Disable;
          break;
        case 1:
          mRenderParam.mirrorType = TRTCVideoMirrorType.TRTCVideoMirrorType_Auto;
          break;
        case 2:
          mRenderParam.mirrorType = TRTCVideoMirrorType.TRTCVideoMirrorType_Enable;
          break;
        default:
          mRenderParam.mirrorType = TRTCVideoMirrorType.TRTCVideoMirrorType_Disable;
          break;
      }
      mRenderIndex.mirrorTypeIndex = value;
      DataManager.GetInstance().SetTRTCRenderIndex(mRenderIndex);
      mTRTCCloud.setRemoteRenderParams("345", mStreamType, ref mRenderParam);
    }

    private void streamTypeDropDownValueChanged(int value) {
      switch (value) {
        case 0:
          mStreamType = TRTCVideoStreamType.TRTCVideoStreamTypeBig;
          break;
        case 1:
          mStreamType = TRTCVideoStreamType.TRTCVideoStreamTypeSmall;
          break;
        case 2:
          mStreamType = TRTCVideoStreamType.TRTCVideoStreamTypeSub;
          break;
        default:
          mStreamType = TRTCVideoStreamType.TRTCVideoStreamTypeBig;
          break;
      }
      mRenderIndex.streamTypeIndex = value;
      DataManager.GetInstance().SetTRTCRenderIndex(mRenderIndex);
      mTRTCCloud.setRemoteRenderParams("345", mStreamType, ref mRenderParam);
    }

    private void SetupEnableLocalVideoCustom() {
      GameObject enableLocalVideoCustomToggleObj =
          transform.Find("videoPanel/enableLocalVideoCustomToggle").gameObject;

      if (enableLocalVideoCustomToggleObj != null) {
        mEnableLocalVideoCustomToggle = enableLocalVideoCustomToggleObj.GetComponent<Toggle>();
        mEnableLocalVideoCustomToggle.isOn =
            DataManager.GetInstance().GetBitrateInfoEnableLocalVideoCustomProcess();
        mEnableLocalVideoCustomToggle.onValueChanged.AddListener(delegate(bool value) {
          mTRTCCloud.enableLocalVideoCustomProcess(value,
                                                   TRTCVideoPixelFormat.TRTCVideoPixelFormat_I420,
                                                   TRTCVideoBufferType.TRTCVideoBufferType_Buffer);
          DataManager.GetInstance().SetEnableLocalVideoCustomProcess(value);
        });
      }
    }

    private void SetupLocalVideoStream() {
      GameObject videoStreamTypeObj =
          transform.Find("videoPanel/streamTypePanel/streamTypeDropdown").gameObject;

      if (videoStreamTypeObj != null) {
        mLocalVideoStreamTypeDropDown = videoStreamTypeObj.GetComponent<Dropdown>();
      }

      mLocalVideoStreamTypeDropDown.value =
          DataManager.GetInstance().GetLocalVideostreamTypeIndex();

      mLocalVideoStreamTypeDropDown.onValueChanged.AddListener(
          this.localVideoStreamDropDownValueChanged);
    }

    private void localVideoStreamDropDownValueChanged(int value) {
      TRTCVideoStreamType streamType;
      switch (value) {
        case 0:
          streamType = TRTCVideoStreamType.TRTCVideoStreamTypeBig;
          break;
        case 1:
          streamType = TRTCVideoStreamType.TRTCVideoStreamTypeSmall;
          break;
        case 2:
          streamType = TRTCVideoStreamType.TRTCVideoStreamTypeSub;
          break;
        default:
          streamType = TRTCVideoStreamType.TRTCVideoStreamTypeBig;
          break;
      }

      DataManager.GetInstance().SetLocalVideostreamTypeIndex(value);

      mTRTCCloud.setRemoteVideoStreamType("345", streamType);
    }

    private void SceneVideoCallToggleValueChanged(bool value) {
      if (value) {
        DataManager.GetInstance().appScene = TRTCAppScene.TRTCAppSceneVideoCall;
        roleAnchorToggle.isOn = true;
        roleAudienceToggle.interactable = false;
      }
    }

    private void SceneLiveToggleValueChanged(bool value) {
      if (value) {
        DataManager.GetInstance().appScene = TRTCAppScene.TRTCAppSceneLIVE;
        roleAudienceToggle.interactable = true;
      }
    }

    private void RoleAnchorToggleValueChanged(bool value) {
      if (value) {
        DataManager.GetInstance().roleType = TRTCRoleType.TRTCRoleAnchor;
      }
    }

    private void RoleAudienceToggleValueChanged(bool value) {
      if (value) {
        DataManager.GetInstance().roleType = TRTCRoleType.TRTCRoleAudience;
      }
    }

    private void PreferSmoothToggleValueChanged(bool value) {
      if (value) {
        TRTCNetworkQosParam param = DataManager.GetInstance().qosParams;
        param.preference = TRTCVideoQosPreference.TRTCVideoQosPreferenceSmooth;
        DataManager.GetInstance().qosParams = param;
      }
    }

    private void PreferClearToggleValueChanged(bool value) {
      TRTCNetworkQosParam param = DataManager.GetInstance().qosParams;
      param.preference = TRTCVideoQosPreference.TRTCVideoQosPreferenceClear;
      DataManager.GetInstance().qosParams = param;
    }

    private void CtrlClientToggleValueChanged(bool value) {
      TRTCNetworkQosParam param = DataManager.GetInstance().qosParams;
      // param.controlMode = TRTCQosControlMode.TRTCQosControlModeClient;
      DataManager.GetInstance().qosParams = param;
    }

    private void CtrlServerToggleValueChanged(bool value) {
      TRTCNetworkQosParam param = DataManager.GetInstance().qosParams;
      // param.controlMode = TRTCQosControlMode.TRTCQosControlModeServer;
      DataManager.GetInstance().qosParams = param;
    }

    private void EnableAIDenoiseToggleValueChanged(bool value) {
      DataManager.GetInstance().enableAIDenoise = value;
      var data = new JsonData { ["api"] = "enableAIDenoise" };
      var param = new JsonData {
        ["enable"] = value,
      };
      data["params"] = param;
      mTRTCCloud?.callExperimentalAPI(data.ToJson());
    }

    private void VoiceChangerDropDownValueChanged(int value) {
      TXVoiceChangeType type = DataManager.GetInstance().voiceChangeType;
      switch (value) {
        case 0:
          type = TXVoiceChangeType.TXVoiceChangeType_0;
          break;
        case 1:
          type = TXVoiceChangeType.TXVoiceChangeType_1;
          break;
        case 2:
          type = TXVoiceChangeType.TXVoiceChangeType_2;
          break;
        case 3:
          type = TXVoiceChangeType.TXVoiceChangeType_3;
          break;
        case 4:
          type = TXVoiceChangeType.TXVoiceChangeType_4;
          break;
        case 5:
          type = TXVoiceChangeType.TXVoiceChangeType_5;
          break;
        case 6:
          type = TXVoiceChangeType.TXVoiceChangeType_6;
          break;
        case 7:
          type = TXVoiceChangeType.TXVoiceChangeType_7;
          break;
        case 8:
          type = TXVoiceChangeType.TXVoiceChangeType_8;
          break;
        case 9:
          type = TXVoiceChangeType.TXVoiceChangeType_9;
          break;
        case 10:
          type = TXVoiceChangeType.TXVoiceChangeType_10;
          break;
        case 11:
          type = TXVoiceChangeType.TXVoiceChangeType_11;
          break;
      }
      DataManager.GetInstance().voiceChangeType = type;
    }

    private void AudioQualityDropDownValueChanged(int value) {
       DataManager.GetInstance().audioQuality = (TRTCAudioQuality)Enum.ToObject(typeof(TRTCAudioQuality), value + 1);
    }

    private void EarMonitorVolumeSliderValueChanged(float value) {
      int volume = (int)value;
      DataManager.GetInstance().earMonitorVolume = volume;
    }
    private void ResolutionDropDownValueChanged(int value) {
      TRTCVideoEncParam param = DataManager.GetInstance().videoEncParam;
      switch (value) {
        case 0:
          param.videoResolution = TRTCVideoResolution.TRTCVideoResolution_120_120;
          break;
        case 1:
          param.videoResolution = TRTCVideoResolution.TRTCVideoResolution_160_160;
          break;
        case 2:
          param.videoResolution = TRTCVideoResolution.TRTCVideoResolution_270_270;
          break;
        case 3:
          param.videoResolution = TRTCVideoResolution.TRTCVideoResolution_480_480;
          break;
        case 4:
          param.videoResolution = TRTCVideoResolution.TRTCVideoResolution_160_120;
          break;
        case 5:
          param.videoResolution = TRTCVideoResolution.TRTCVideoResolution_240_180;
          break;
        case 6:
          param.videoResolution = TRTCVideoResolution.TRTCVideoResolution_280_210;
          break;
        case 7:
          param.videoResolution = TRTCVideoResolution.TRTCVideoResolution_320_240;
          break;
        case 8:
          param.videoResolution = TRTCVideoResolution.TRTCVideoResolution_400_300;
          break;
        case 9:
          param.videoResolution = TRTCVideoResolution.TRTCVideoResolution_480_360;
          break;
        case 10:
          param.videoResolution = TRTCVideoResolution.TRTCVideoResolution_640_480;
          break;
        case 11:
          param.videoResolution = TRTCVideoResolution.TRTCVideoResolution_960_720;
          break;
        case 12:
          param.videoResolution = TRTCVideoResolution.TRTCVideoResolution_320_180;
          break;
        case 13:
          param.videoResolution = TRTCVideoResolution.TRTCVideoResolution_480_270;
          break;
        case 14:
          param.videoResolution = TRTCVideoResolution.TRTCVideoResolution_640_360;
          break;
        case 15:
          param.videoResolution = TRTCVideoResolution.TRTCVideoResolution_960_540;
          break;
        case 16:
          param.videoResolution = TRTCVideoResolution.TRTCVideoResolution_1280_720;
          break;
        case 17:
          param.videoResolution = TRTCVideoResolution.TRTCVideoResolution_1920_1080;
          break;
      }

      DataManager.VideoResBitrateTable bitrateInfo =
          DataManager.GetInstance().GetBitrateInfo((int)param.videoResolution);
      param.minVideoBitrate = (uint)bitrateInfo.minBitrate;
      if (param.videoBitrate > bitrateInfo.maxBitrate ||
          param.videoBitrate < bitrateInfo.minBitrate) {
        param.videoBitrate = (uint)bitrateInfo.defaultBitrate;
        curBitrateText.text = param.videoBitrate.ToString() + "kps";
      }
      bitrateSlider.minValue = bitrateInfo.minBitrate;
      bitrateSlider.maxValue = bitrateInfo.maxBitrate;
      bitrateSlider.value = param.videoBitrate;

      DataManager.GetInstance().videoEncParam = param;
    }

    private void FpsDropDownValueChanged(int value) {
      TRTCVideoEncParam param = DataManager.GetInstance().videoEncParam;
      switch (value) {
        case 0:
          param.videoFps = 15;
          break;
        case 1:
          param.videoFps = 20;
          break;
        case 2:
          param.videoFps = 24;
          break;
      }

      DataManager.GetInstance().videoEncParam = param;
    }

    private void DirectionDropDownValueChanged(int value) {
      TRTCVideoEncParam param = DataManager.GetInstance().videoEncParam;
      switch (value) {
        case 0:
          param.resMode = TRTCVideoResolutionMode.TRTCVideoResolutionModeLandscape;
          break;
        case 1:
          param.resMode = TRTCVideoResolutionMode.TRTCVideoResolutionModePortrait;
          break;
      }

      DataManager.GetInstance().videoEncParam = param;
    }

    private void BitrateSliderValueChanged(float value) {
      TRTCVideoEncParam param = DataManager.GetInstance().videoEncParam;
      param.videoBitrate = (uint)value;
      DataManager.GetInstance().videoEncParam = param;

      curBitrateText.text = param.videoBitrate.ToString() + "kps";
    }

    public void OnBackClick() { Destroy(this.gameObject); }
  }
}