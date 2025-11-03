using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.Reflection;
#if PLATFORM_ANDROID
using UnityEngine.Android;
#endif
#if PLATFORM_OPENHARMONY
using UnityEngine.OpenHarmony;
#endif

namespace TRTCCUnityDemo {
  public class ApiFuncObj {
    public readonly string FuncName;
    public readonly string FuncDescription;
    public readonly string HandleClickName;
    public ApiFuncObj(string funcName, string handleClickName, string funcDescription) {
      FuncName = funcName;
      HandleClickName = handleClickName;
      FuncDescription = funcDescription;
    }
  }
  public class ApiTestBtnBuilder {
    private Dictionary<string, ApiFuncObj[]> apiList = new Dictionary<string, ApiFuncObj[]>();

    GameObject content;
    Font font;
    ApiTestScript context;
    int x = 80;
    int y = -104;
    int width = 1000;
    int height = 80;
    int step = 90;

    public ApiTestBtnBuilder(GameObject content, Font font, ApiTestScript context) {
      this.content = content;
      this.font = font;
      this.context = context;
      apiList.Add("实例创建销毁相关接口函数", new[] {
        new ApiFuncObj("getTRTCShareInstance", "getTRTCShareInstanceClick", "创建主实例"),
        new ApiFuncObj("destroyTRTCShareInstance", "destroyTRTCShareInstanceClick", "销毁主实例"),
        new ApiFuncObj("createSubCloud", "createSubCloudClick", "创建子实例"),
        new ApiFuncObj("destroySubCloud", "destroySubCloudClick", "销毁子实例")
      });
      apiList.Add("房间相关接口函数", new[] {
        new ApiFuncObj("enterRoom", "enterRoomClick", "进入房间"),
        new ApiFuncObj("exitRoom", "exitRoomClick", "离开房间"),
        new ApiFuncObj("switchRole-audience", "switchRoleAudience", "切换角色-观众"),
        new ApiFuncObj("switchRole-archor", "switchRoleArchor", "切换角色-主播"),

        new ApiFuncObj("ConnectOtherRoom", "ConnectOtherRoomClick", "请求跨房通话-1908-345"),
        new ApiFuncObj("disconnectOtherRoom", "disconnectOtherRoomClick", "关闭跨房连麦"),
        new ApiFuncObj("switchRoom", "switchRoomClick", "切换房间-1907"), 
        new ApiFuncObj("enableSmallVideoStream-true", "enableSmallVideoStreamClick",
                       "开启大小画面双路编码模式"),
        new ApiFuncObj("enableSmallVideoStream-false", "disEnableSmallVideoStreamClick",
                       "关闭大小画面双路编码模式"),
        new ApiFuncObj("setDefaultStreamRecvMode-auto", "setDefaultStreamRecvModeAutoClick",
                       "自动订阅远端音视频(进房前调)"),
        new ApiFuncObj("setDefaultStreamRecvMode-disAuto", "setDefaultStreamRecvModeDisAutoClick",
                       "手动订阅远端音视频(进房前调)")
      });
      apiList.Add("startPublishMediaStream相关接口", new[] {
        new ApiFuncObj("BigStreamToCdn", "TRTCPublishBigStreamToCdnClick", "将主路流推到cdn"),
        new ApiFuncObj("MixStreamToRoom", "TRTCPublishMixStreamToRoomClick", "将当前用户及用户345流推到房间678"),
        new ApiFuncObj("updatePublishMediaStream", "updatePublishMediaStreamClick", "更新发布媒体流"),
        new ApiFuncObj("stopPublishMediaStream", "stopPublishMediaStreamClick", "停止发布媒体流")
      });
      apiList.Add("音频相关接口函数", new[] {
        new ApiFuncObj("startLocalAudio", "startLocalAudioClick", "开启本地音频"),
        new ApiFuncObj("stopLocalAudio", "stopLocalAudioClick", "关闭本地音频"),
        new ApiFuncObj("muteLocalAudio-true", "muteLocalAudioClickTrue", "静音"),
        new ApiFuncObj("muteLocalAudio-false", "muteLocalAudioClickFalse", "取消静音"),
        new ApiFuncObj("muteRemoteAudio-345-true", "muteRemoteAudioClickTrue", "静音远端用户"),
        new ApiFuncObj("muteRemoteAudio-345-false", "muteRemoteAudioClickFalse",
                       "取消静音远端用户"),
        new ApiFuncObj("muteAllRemoteAudio-true", "muteAllRemoteAudioClickTrue", "静音所有用户"),
        new ApiFuncObj("muteAllRemoteAudio-false", "muteAllRemoteAudioClickFalse",
                       "取消静音所有用户"),
        new ApiFuncObj("setRemoteAudioVolume-345-0", "setRemoteAudioVolumeClick0",
                       "设置某个远程用户的播放音量"),
        new ApiFuncObj("setRemoteAudioVolume--345-100", "setRemoteAudioVolumeClick100",
                       "设置某个远程用户的播放音量"),
        new ApiFuncObj("setAudioCaptureVolume-95", "setAudioCaptureVolumeClick", "设置SDK采集音量"),
        new ApiFuncObj("getAudioCaptureVolume", "getAudioCaptureVolumeClick", "获取SDK采集音量"),
        new ApiFuncObj("setAudioPlayoutVolume-98", "setAudioPlayoutVolumeClick", "设置SDK播放音量"),
        new ApiFuncObj("getAudioPlayoutVolume", "getAudioPlayoutVolumeClick", "获取SDK播放音量"),
        new ApiFuncObj("enableMixExternalAudioFrame-true", "enableMixExternalAudioFrameTrue",
                       "开启外部混音"),
        new ApiFuncObj("enableMixExternalAudioFrame-false", "enableMixExternalAudioFrameFalse",
                       "关闭外部混音"),
        new ApiFuncObj("startSystemAudioLoopback", "startSystemAudioLoopbackClick",
                       "开启系统声音采集"),
        new ApiFuncObj("stopSystemAudioLoopback", "stopSystemAudioLoopbackClick",
                       "关闭系统声音采集"),
        new ApiFuncObj("enableAudioVolumeEvaluation-100", "enableAudioVolumeEvaluationClick100",
                       "启用音量大小提示"),
        new ApiFuncObj("enableAudioVolumeEvaluation-0", "enableAudioVolumeEvaluationClick0",
                       "关闭音量大小提示"),
        new ApiFuncObj("startAudioRecording", "startAudioRecordingClick", "开始录音"),
        new ApiFuncObj("stopAudioRecording", "stopAudioRecordingClick", "停止录音"),
        new ApiFuncObj("setCapturedCallbackFormat", "setCapturedAudioFrameCallbackFormatClick", "设置本地麦克风采集音频回调格式"),
        new ApiFuncObj("setLocalProcessedCallbackFormat", "setLocalProcessedAudioFrameCallbackFormatClick", "设置经过前处理后的本地音频回调格式"),
        new ApiFuncObj("setMixedPlayCallbackFormat", "setMixedPlayAudioFrameCallbackFormatClick", "设置最终要由系统播放出的音频回调格式"),
        new ApiFuncObj("setAudioFrameCallback", "setAudioFrameCallbackClick", "音频数据回调"),
        new ApiFuncObj("setRemoteUserAudioFrameCallbackFormat-open", "openSetRemoteUserAudioFrameCallbackFormatClick", "开启修改音频下行数据"),
        new ApiFuncObj("setRemoteUserAudioFrameCallbackFormat-close", "closeSetRemoteUserAudioFrameCallbackFormatClick", "关闭修改音频下行数据"),
      });
      apiList.Add("音乐特效和人声特效", new[] {
        new ApiFuncObj("setVoiceReverbType", "setVoiceReverbTypeClick", "设置人声的混响效果-金属"),
        new ApiFuncObj("setVoiceReverbType", "setVoiceReverbTypeClickDc",
                       "设置人声的混响效果-低沉"),
        new ApiFuncObj("setVoiceReverbType", "setVoiceReverbTypeClickClose", "关闭混响"),
        new ApiFuncObj("startPlayMusic", "startPlayShortMusicClick", "开始播放短音效"),
        new ApiFuncObj("startPlayMusic", "startPlayMusicClick", "开始播放背景音乐"),
        new ApiFuncObj("stopPlayMusic", "stopPlayMusicClick", "停止播放背景音乐"),
        new ApiFuncObj("pausePlayMusic", "pausePlayMusicClcik", "暂停播放背景音乐"),
        new ApiFuncObj("resumePlayMusic", "resumePlayMusicClick", "恢复播放背景音乐"),
        new ApiFuncObj("setMusicPublishVolume", "setMusicPublishVolumeClick0",
                       "背景音乐的远端音量大小0"),
        new ApiFuncObj("setMusicPublishVolume", "setMusicPublishVolumeClick100",
                       "背景音乐的远端音量大小-100"),
        new ApiFuncObj("setMusicPlayoutVolume", "setMusicPlayoutVolumeClick0",
                       "背景音乐的本地音量大小-0"),
        new ApiFuncObj("setMusicPlayoutVolume", "setMusicPlayoutVolumeClick100",
                       "背景音乐的本地音量大小-100"),
        new ApiFuncObj("setAllMusicVolume", "setAllMusicVolumeClick0", "全局背景音乐-0"),
        new ApiFuncObj("setAllMusicVolume", "setAllMusicVolumeClick100", "全局背景音乐-100"),
        new ApiFuncObj("setMusicPitch", "setMusicPitchClickFu", "调整背景音乐的音调高低-负1"),
        new ApiFuncObj("setMusicPitch", "setMusicPitchClick", "调整背景音乐的音调高低-1"),
        new ApiFuncObj("setMusicSpeedRate", "setMusicSpeedRateClick1",
                       "调整背景音乐的变速效果-0.5"),
        new ApiFuncObj("setMusicSpeedRate", "setMusicSpeedRateClick2", "调整背景音乐的变速效果-1"),
        new ApiFuncObj("getMusicCurrentPosInMS", "getMusicCurrentPosInMSClick",
                       "获取背景音乐当前的播放进度"),
        new ApiFuncObj("seekMusicToPosInMS", "seekMusicToPosInMSClick", "设置背景音乐的播放进度"),
        new ApiFuncObj("getMusicDurationInMS", "getMusicDurationInMSClick",
                       "获取景音乐文件的总时长"),
        new ApiFuncObj("setMusicScratchSpeedRate", "setMusicScratchSpeedRateClickB6",
                       "搓碟的变速 -6"),
        new ApiFuncObj("setMusicScratchSpeedRate", "setMusicScratchSpeedRateClickA1",
                       "搓碟的变速 +1 (默认)"),
        new ApiFuncObj("setMusicScratchSpeedRate", "setMusicScratchSpeedRateClickA6",
                       "搓碟的变速 +6 "),
        new ApiFuncObj("setPreloadMusicClick", "setPreloadMusicClick", "设置预加载音乐回调"),
        new ApiFuncObj("setPreloadMusicClick", "setPreloadMusicClickNull", "取消预加载音乐回调"),
        new ApiFuncObj("preloadMusic", "preloadMusicClick", "预加载音乐"),
        new ApiFuncObj("getMusicTrackCount", "getMusicTrackCountClick", "获取背景音乐音轨数量"),
        new ApiFuncObj("setMusicTrack", "setMusicTrackClick", "指定背景音乐的播放音轨"),
        new ApiFuncObj("setVoiceCaptureVolume", "setVoiceCaptureVolumeClick100",
                       "设置语音音量的大小-100"),
        new ApiFuncObj("setVoiceCaptureVolume", "setVoiceCaptureVolumeClick0",
                       "设置语音音量的大小-0"),
        new ApiFuncObj("setVoicePitch", "setVoicePitchClick1", "设置语音音调大小-1"),
        new ApiFuncObj("setVoicePitch", "setVoicePitchClick0", "设置语音音调的大小-0"),
        new ApiFuncObj("playBackGroundMusic", "playBackGroundMusicClick", "播放背景音乐"),
        new ApiFuncObj("stopBackGroundMusic", "stopBackGroundMusicClick", "停止播放背景音乐"),
      });
      apiList.Add("曲库相关接口函数", new[] {
        new ApiFuncObj("setCopyrightedLicense", "setCopyrightedLicenseClick", "设置 license"),
        new ApiFuncObj("setMusicPreloadCallback", "setMusicPreloadCallbackClick",
                       "设置预加载回调函数"),
        new ApiFuncObj("preloadMusic", "preloadCopyrightedMediaMusicClick", "预加载曲库音乐数据"),
        new ApiFuncObj("cancelPreloadMusic", "cancelPreloadMusicClick", "取消预加载音乐数据"),
        new ApiFuncObj("genMusicURI", "genMusicURIClick", "生成音乐"),
        new ApiFuncObj("isMusicPreload", "isMusicPreloadClick", "检测是否已预加载音乐数据"),
        new ApiFuncObj("clearMusicCache", "clearMusicCacheClick", "清理音乐缓存"),
        new ApiFuncObj("setMusicCacheMaxCount", "setMusicCacheMaxCountClick", "设置最大歌曲缓存数目-10"),
      });
      apiList.Add("设备相关接口函数", new[] {
        new ApiFuncObj("isFrontCamera", "isFrontCameraClick", "判断当前是否为前置摄像头"),
        new ApiFuncObj("switchCamera-false", "switchCameraClick", "切换摄像头"),
        new ApiFuncObj("switchCamera-true", "switchCameraTrueClick", "切换摄像头"),
        new ApiFuncObj("getCameraZoomMaxRatio", "getCameraZoomMaxRatioClick",
                       "查询当前摄像头支持的最大缩放比例"),
        new ApiFuncObj("setCameraZoomRatio", "setCameraZoomRatioClick",
                       "设置当前摄像头的缩放比例 3.6"),
        new ApiFuncObj("setCameraZoomRatio9", "setCameraZoomRatio9Click",
                       "设置当前摄像头的缩放比例 9"),
        new ApiFuncObj("isAutoFocusEnabled", "isAutoFocusEnabledClick",
                       "查询是否支持自动识别人脸位置"),
        new ApiFuncObj("enableCameraAutoFocus-true", "enableCameraAutoFocusClick",
                       "设置人脸自动识别"),
        new ApiFuncObj("enableCameraAutoFocus-false", "enableCameraAutoFocusFalseClick",
                       "设置人脸自动识别"),
        new ApiFuncObj("setCameraFocusPosition-10", "setCameraFocusPositionClick",
                       "设置摄像头焦点"),
        new ApiFuncObj("setCameraFocusPosition-100", "setCameraFocusPositionClick100",
                       "设置摄像头焦点"),
        new ApiFuncObj("enableCameraTorch-true", "enableCameraTorchClick", "开关闪光灯"),
        new ApiFuncObj("enableCameraTorch-false", "enableCameraTorchClickFalse", "关闭闪光灯"),
        new ApiFuncObj("setSystemVolumeType", "setSystemVolumeTypeMedia", "系统音量类型-Media"),
        new ApiFuncObj("setSystemVolumeType", "setSystemVolumeTypeVOIP", "系统音量类型-VOIP"),
        new ApiFuncObj("setSystemVolumeType", "setSystemVolumeTypeAuto", "系统音量类型-Auto"),
        new ApiFuncObj("setAudioRoute", "setAudioRouteSpeakerphone", "设置音频路由-扬声器"),
        new ApiFuncObj("setAudioRoute", "setAudioRouteEarpiece", "设置音频路由-听筒"),

        new ApiFuncObj("getDevicesList", "getDevicesListTypeMicClick", "获取设备列表-Mic"),
        new ApiFuncObj("getDevicesList", "getDevicesListTypeSpeakerClick", "获取设备列表-Speaker"),
        new ApiFuncObj("getDevicesList", "getDevicesListTypeCameraClick", "获取设备列表-Camera"),

        new ApiFuncObj("setCurrentDevice", "setCurrentDeviceTypeMicClick",
                       "设置当前要使用的设备-Mic"),
        new ApiFuncObj("setCurrentDevice", "setCurrentDeviceTypeSpeakerClick",
                       "设置当前要使用的设备-Speaker"),
        new ApiFuncObj("setCurrentDevice", "setCurrentDeviceTypeCameraClick",
                       "设置当前要使用的设备-Camera"),

        new ApiFuncObj("getCurrentDevice", "getCurrentDeviceTypeMicClick",
                       "获取当前正在使用的设备-Mic"),
        new ApiFuncObj("getCurrentDevice", "getCurrentDeviceTypeSpeakerClick",
                       "获取当前正在使用的设备-Speaker"),
        new ApiFuncObj("getCurrentDevice", "getCurrentDeviceTypeCameraClick",
                       "获取当前正在使用的设备-Camera"),
      });
      apiList.Add("视频相关接口函数", new[] {
        new ApiFuncObj("startLocalPreview", "startLocalPreviewClick", "开启本地视频的预览画面"),
        new ApiFuncObj("stopLocalPreview", "stopLocalPreviewClick", "停止本地视频采集及预览"),
        new ApiFuncObj("setBeautyStyle-9", "setBeautyStyleClick9",
                       "设置美颜、美白、红润效果级别。"),
        new ApiFuncObj("setBeautyStyle-0", "setBeautyStyleClick0",
                       "设置美颜、美白、红润效果级别。"),
        new ApiFuncObj("setWaterMark", "setWaterMarkClick", "设置水印"),
        new ApiFuncObj("setVideoEncoderMirror-true", "setVideoEncoderMirrorClick",
                       "设置编码器输出的画面镜像模式"),
        new ApiFuncObj("setVideoEncoderMirror-false", "setVideoEncoderMirrorClickFalse",
                       "设置编码器输出的画面镜像模式"),
      });
      apiList.Add("设备和网络测试", new[] {
        new ApiFuncObj("startSpeedTest", "startSpeedTestClick", "开始进行网络测速"),
        new ApiFuncObj("stopSpeedTest", "stopSpeedTestClick", "停止网络测速"),
      });
      apiList.Add("其他", new[] {
        new ApiFuncObj("setLogLevel", "setLogLevelClick", "设置log级别"),
        new ApiFuncObj("setConsoleEnabled", "setConsoleEnabledClick", "启用控制台日志打印"),
        new ApiFuncObj("setLogCompressEnabled-false", "setLogCompressEnabledFalseClick",
                       "禁用Log的本地压缩"),
        new ApiFuncObj("setLogCompressEnabled-true", "setLogCompressEnabledTrueClick",
                       "启用 Log的本地压缩"),
        new ApiFuncObj("setLogDirPath", "setLogDirPathClick", "修改日志保存路径"),
        new ApiFuncObj("sendSEIMsg", "sendSEIMsg", "将小数据量的自定义数据嵌入视频帧中"),
        new ApiFuncObj("sendCustomCmdMsg", "sendCustomCmdMsgClick",
                       "发送自定义消息给房间内所有用户"),
        new ApiFuncObj("getSDKVersion", "getSDKVersionClick", "SDK版本号"),
        new ApiFuncObj("clearLog", "clearLogClick", "清理日志"),
        new ApiFuncObj("GetVideoRenderData", "GetVideoRenderDataClick", "GetVideoRenderData"),
      });

#if PLATFORM_ANDROID || PLATFORM_OPENHARMONY
      if (!Permission.HasUserAuthorizedPermission(Permission.Microphone)) {
        Permission.RequestUserPermission(Permission.Microphone);
      }
      if (!Permission.HasUserAuthorizedPermission(Permission.Camera)) {
        Permission.RequestUserPermission(Permission.Camera);
      }
#endif
    }

    public void init() {
      foreach (var mp in this.apiList) {
        this.addText(mp.Key);
        this.addBtns(mp.Key);
      }
    }
    public void addText(string type) {
      GameObject text = new GameObject("Text", typeof(Text));
      text.transform.SetParent(content.transform);
      Text _text = text.GetComponent<Text>();
      RectTransform textTransform = text.GetComponent<RectTransform>();
      textTransform.pivot = new Vector2(0.0f, 0.5f);
      textTransform.sizeDelta = new Vector2(width, height);
      textTransform.anchorMax = new Vector2(0.01f, 0.5f);
      textTransform.anchorMin = new Vector2(0.01f, 0.5f);
      textTransform.localPosition = new Vector2(x, y);
      textTransform.localScale = new Vector3(1, 1, 1);
      _text.text = type;
      _text.color = Color.black;
      _text.font = font;
      _text.fontSize = 36;
      _text.alignment = TextAnchor.MiddleCenter;

      y = y - step;
    }

    /** 根据函数名，调用类的实例方法
     *
     */
    private static void invokeInstanceFunction(string functionName, ApiTestScript instance) {
      System.Type type = instance.GetType();
      if (type.GetMethod(functionName) != null) {
        type.InvokeMember(
            functionName,
            System.Reflection.BindingFlags.Default | System.Reflection.BindingFlags.InvokeMethod,
            null, instance, new object[] {});
        // lblBtnClickLog.text += Environment.NewLine +"function call  " + functionName + " end";
      } else {
        // lblBtnClickLog.text += Environment.NewLine + "function  " + functionName + " not find";
      }
    }

    public void addBtns(string type) {
      foreach (var item in this.apiList[type]) {
        string strFn = item.FuncName + "(" + item.FuncDescription + ")";
        GameObject obj = insertBtn(strFn, content, font, width, height, x, y);
        Button btn = obj.GetComponent<Button>();

        btn.onClick.AddListener(delegate() {
          string fn = item.HandleClickName;
          // lblBtnClickLog.text += Environment.NewLine + "start call  "+ fn;
          invokeInstanceFunction(fn, context);
        });

        y = y - step;
      }
    }

    public static GameObject
    insertBtn(string name, GameObject canvas, Font font, int width, int height, int x, int y) {
      GameObject button =
          new GameObject("Button", typeof(Button), typeof(RectTransform), typeof(Image));
      GameObject text = new GameObject("Text", typeof(Text));

      RectTransform rectTransform = button.GetComponent<RectTransform>();
      button.transform.SetParent(canvas.transform);
      text.transform.SetParent(rectTransform);
      rectTransform.sizeDelta = new Vector2(width, height);
      rectTransform.pivot = new Vector2(0f, 0.5f);
      rectTransform.SetSizeWithCurrentAnchors(RectTransform.Axis.Horizontal, width);
      rectTransform.anchorMax = new Vector2(0.01f, 0.5f);
      rectTransform.anchorMin = new Vector2(0.01f, 0.5f);
      rectTransform.localPosition = new Vector2(x, y);

      Text _text = text.GetComponent<Text>();
      RectTransform textTransform = text.GetComponent<RectTransform>();
      textTransform.localPosition = new Vector2(0, 0);
      textTransform.SetSizeWithCurrentAnchors(RectTransform.Axis.Horizontal, width);
      textTransform.pivot = new Vector2(0f, 0.5f);
      textTransform.sizeDelta = new Vector2(width, height);
      rectTransform.localScale = new Vector3(1, 1, 1);
      _text.text = name;
      _text.color = Color.black;
      _text.font = font;
      _text.fontSize = 36;
      _text.alignment = TextAnchor.MiddleCenter;

      return button;
    }
  }

}
