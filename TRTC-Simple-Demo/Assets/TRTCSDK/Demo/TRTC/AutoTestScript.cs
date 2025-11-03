using System.Collections;
using UnityEngine;
using trtc;
using System;
using System.IO;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using System.Threading;
using LitJson;
using System.Runtime.InteropServices;

namespace TRTCCUnityDemo {
  public class AutoTestScript : MonoBehaviour,
                               ITRTCCloudCallback,
                               ITRTCAudioFrameCallback,
                               ITXMusicPreloadObserver {
    // 主线程上下文
    SynchronizationContext mainSyncContext;

    private string LogForBtnClick = "";
    private string mTaskId = "";
    private bool mApplicationPause = false;
    public InputField mRoomInputFieId;
    public InputField mUserIdInputFieId;
    private Button mStartTestBtn;
    private Button mStopTestBtn;
    private Button mExitBtn;
    private Toggle mToggleEnableAudioCallback;

    private DateTime mEnterRoomTime = DateTime.MinValue;
    private bool mIsEnterRoom = false;
    private DateTime mExitRoomTime = DateTime.MinValue;
    private bool mIsTest = false;
    private bool mIsRegisterAudioCallback = true;

    private ITRTCCloud mTRTCCloud;
    private ITXAudioEffectManager mTXAudioEffectManager;
    private ITXDeviceManager mTXDeviceManager;

    void Start() {
      // 获取主线程上下文
      mainSyncContext = SynchronizationContext.Current;
      init();
      CopyResources();
    }

    public void Update() {
      if(mIsTest == false) {
        return;
      }

      if(mIsEnterRoom && ((Int64)(DateTime.UtcNow - mEnterRoomTime).TotalSeconds) >= 20) {
        StopTest();
      }

      if(!mIsEnterRoom && mExitRoomTime != DateTime.MinValue && ((Int64)(DateTime.UtcNow - mExitRoomTime).TotalSeconds) >= 2) {
       StartTest();
      }
    }

    private void init() {
      mRoomInputFieId = transform.Find("roomManage/roomPanel/inputRoomID").GetComponent<InputField>();
      if (mRoomInputFieId != null) {
        mRoomInputFieId.text = DataManager.GetInstance().GetRoomID();
      }

      mUserIdInputFieId = transform.Find("roomManage/roomPanel/InputUserId").GetComponent<InputField>();
      if (mUserIdInputFieId != null) {
        mUserIdInputFieId.text = DataManager.GetInstance().GetUserID();
      }

      mStartTestBtn = transform.Find("roomManage/roomPanel/btnStartTest").gameObject.GetComponent<Button>();
      if (mStartTestBtn) {
        mStartTestBtn.onClick.AddListener(this.OnStartTestClick);
      }

      mStopTestBtn = transform.Find("roomManage/roomPanel/btnStopTest").gameObject.GetComponent<Button>();
      if (mStopTestBtn) {
        mStopTestBtn.onClick.AddListener(this.OnStopTestClick);
      }

      mExitBtn = transform.Find("roomManage/roomPanel/btnExit").gameObject.GetComponent<Button>();
      mExitBtn.onClick.AddListener(
          () => { SceneManager.LoadScene("HomeScene", LoadSceneMode.Single); });

      mToggleEnableAudioCallback = transform.Find("roomManage/roomPanel/ToggleEnableAudioCallback").gameObject.GetComponent<Toggle>();
      mToggleEnableAudioCallback.onValueChanged.AddListener(this.OnToggleEnableAudioCallback);
    }

    private void initTrtc() {
      PrintfTestApiLog($"start getTRTCShareInstance test");
      mTRTCCloud = ITRTCCloud.getTRTCShareInstance();
      mTXAudioEffectManager = mTRTCCloud?.getAudioEffectManager();
      mTXDeviceManager = mTRTCCloud?.getDeviceManager();
    }

    private void RegisterTestCallback() {
      mTRTCCloud?.addCallback(this);
      if (mIsRegisterAudioCallback) {
        PrintfTestApiLog($"enableAudioVolumeEvaluation 100 ms test");
        mTRTCCloud?.enableAudioVolumeEvaluation(100);
        PrintfTestApiLog($"setAudioFrameCallback test");
        mTRTCCloud?.setAudioFrameCallback(this);
      } else {
        PrintfTestApiLog($"disenableAudioVolumeEvaluation");
        mTRTCCloud?.enableAudioVolumeEvaluation(0);
        PrintfTestApiLog($"setAudioFrameCallback test");
        mTRTCCloud?.setAudioFrameCallback(null);
      }
      
    }

    private void StartTest() {
      initTrtc();
      RegisterTestCallback();
      enterRoomTest();
      startPlayMusicTest();
      mExitRoomTime = DateTime.MinValue;
    }

    private void OnStartTestClick() {
      if(mIsTest == true) {
         PrintfTestApiLog($"test have started");
      }
      StartTest();
      mIsTest = true;
    }

    private void StopTest() {
      PrintfTestApiLog($"start destroyTRTCShareInstance test");
      ITRTCCloud.destroyTRTCShareInstance();
      startPlayMusicTest();
      mTRTCCloud = null;
      mTXAudioEffectManager = null;
      mTXDeviceManager = null;
      mIsEnterRoom = false;
      mExitRoomTime = DateTime.UtcNow;
    }

    private void OnStopTestClick() {
      mIsTest = false;
      StopTest();
    }

    private void OnToggleEnableAudioCallback(bool isEnable) {
     mIsRegisterAudioCallback = isEnable;
    }
    
    private void CopyResources() {
      StartCoroutine(CopyFileFromAssetsToPersistent("16_1_audio.pcm"));
      StartCoroutine(CopyFileFromAssetsToPersistent("48_1_audio.pcm"));
      StartCoroutine(CopyFileFromAssetsToPersistent("48_1_audio.pcm"));
      StartCoroutine(CopyFileFromAssetsToPersistent("click.mp3"));
    }

    private IEnumerator CopyFileFromAssetsToPersistent(string fileName) {
      var fromPath = Application.streamingAssetsPath + "/" + fileName;
      var toPath = Application.persistentDataPath + "/" + fileName;
      return CopyFile(fromPath, toPath);
    }

    private IEnumerator CopyFile(string fromPath, string toPath) {
      if (!File.Exists(toPath)) {
        Debug.Log("copying from " + fromPath + " to " + toPath);
#if (UNITY_ANDROID || UNITY_OPENHARMONY) && !UNITY_EDITOR
        WWW www1 = new WWW(fromPath);
        yield return www1;
        File.WriteAllBytes(toPath, www1.bytes);
        Debug.Log("file copy done");
        www1.Dispose();
        www1 = null;
#else
        File.WriteAllBytes(toPath, File.ReadAllBytes(fromPath));
#endif
      }

      yield return null;
    }

    void OnDestroy() {
      mTRTCCloud?.removeCallback(this);
      ITRTCCloud.destroyTRTCShareInstance();
      DataManager.GetInstance().ResetLocalAVFlag();
    }

#region ITRTCCloudCallback

    public void onRecvCustomCmdMsg(string userId,
                                   int cmdID,
                                   int seq,
                                   byte[] message,
                                   int messageSize) {
      string msg = System.Text.Encoding.UTF8.GetString(message, 0, messageSize);
      PrintfTestCallbackLog($"onRecvCustomCmdMsg {userId}, {cmdID} ,{msg}");
    }

    public void onMissCustomCmdMsg(string userId, int cmdID, int errCode, int missed) {
      PrintfTestCallbackLog($"onMissCustomCmdMsg {userId}, {cmdID}");
    }

    public void onError(TXLiteAVError errCode, String errMsg, IntPtr arg) {
      PrintfTestCallbackLog($"onError {errCode}, {errMsg}");
    }

    public void onWarning(TXLiteAVWarning warningCode, String warningMsg, IntPtr arg) {
      PrintfTestCallbackLog($"onWarning {warningCode}, {warningMsg}");
    }

    public void onEnterRoom(int result) {
      PrintfTestCallbackLog($"onEnterRoom {result}");
       mainSyncContext.Post((object state) => {
        startLocalAudioTest();
        mEnterRoomTime = DateTime.UtcNow;
        mIsEnterRoom = true;
      }, "");
    }

    public void onExitRoom(int reason) {
      PrintfTestCallbackLog($"onExitRoom {reason}");
    }

    public void onSwitchRole(TXLiteAVError errCode, String errMsg) {
      PrintfTestCallbackLog($"onSwitchRole {errCode}, {errMsg}");
    }

    public void onRemoteUserEnterRoom(String userId) {
      PrintfTestCallbackLog($"onRemoteUserEnterRoom {userId}");
    }

    public void onRemoteUserLeaveRoom(String userId, int reason) {
      PrintfTestCallbackLog($"onRemoteUserLeaveRoom {userId}, {reason}");
    }

    public void onUserVideoAvailable(String userId, bool available) {
      PrintfTestCallbackLog($"onUserVideoAvailable {userId}, {available}");
    }

    public void onUserSubStreamAvailable(string userId, bool available) {
      PrintfTestCallbackLog($"onUserSubStreamAvailable {userId}, {available}");
    }

    public void onUserAudioAvailable(String userId, bool available) {
      PrintfTestCallbackLog($"onUserAudioAvailable {userId}, {available}");
    }

    public void onFirstVideoFrame(String userId,
                                  TRTCVideoStreamType streamType,
                                  int width,
                                  int height) {
      PrintfTestCallbackLog($"onFirstVideoFrame {userId}, {streamType}, {width}, {height}");
    }

    public void onFirstAudioFrame(String userId) {
      PrintfTestCallbackLog($"onFirstAudioFrame {userId}");
    }

    public void onSendFirstLocalVideoFrame(TRTCVideoStreamType streamType) {
      PrintfTestCallbackLog($"onSendFirstLocalVideoFrame {streamType}");
    }

    public void onSendFirstLocalAudioFrame() {
      PrintfTestCallbackLog($"onSendFirstLocalAudioFrame");
    }

    public void onNetworkQuality(TRTCQualityInfo localQuality,
                                 TRTCQualityInfo[] remoteQuality,
                                 UInt32 remoteQualityCount) {
    }

    public void onStatistics(TRTCStatistics statis) {
      PrintfTestCallbackLog($"onStatistics callback");
    }

    public void onConnectionLost() {
      PrintfTestCallbackLog($"onConnectionLost");
    }

    public void onTryToReconnect() {
      PrintfTestCallbackLog($"onTryToReconnect");
    }

    public void onConnectionRecovery() {
      PrintfTestCallbackLog($"onConnectionRecovery");
    }

    public void onCameraDidReady() {
      PrintfTestCallbackLog($"onCameraDidReady");
    }

    public void onMicDidReady() {
      PrintfTestCallbackLog($"onMicDidReady");
    }

     public void onAudioRouteChanged(TRTCAudioRoute newRoute, TRTCAudioRoute oldRoute) {
       PrintfTestCallbackLog($"onAudioRouteChanged newRoute: " + newRoute + ", oldRoute: " + oldRoute);
    }

    public void onUserVoiceVolume(TRTCVolumeInfo[] userVolumes,
                                  UInt32 userVolumesCount,
                                  UInt32 totalVolume) {
      PrintfTestCallbackLog($"totalVolume= {totalVolume}");
    }

    public void onDeviceChange(String deviceId, TRTCDeviceType type, TRTCDeviceState state) {
      PrintfTestCallbackLog($"onSwitchRole {deviceId}, {type}, {state}");
    }

    public void onRecvSEIMsg(String userId, Byte[] message, UInt32 msgSize) {
      string seiMessage = System.Text.Encoding.UTF8.GetString(message, 0, (int)msgSize);
      PrintfTestCallbackLog($"onRecvSEIMsg {userId}, {seiMessage}, {msgSize}");
    }

    public void onStartPublishing(int err, string errMsg) {
      PrintfTestCallbackLog($"onStartPublishing {err}, {errMsg}");
    }

    public void onStopPublishing(int err, string errMsg) {
      PrintfTestCallbackLog($"onStopPublishing {err}, {errMsg}");
    }

    public void onStartPublishCDNStream(int err, string errMsg) {
      PrintfTestCallbackLog($"onStartPublishCDNStream {err}, {errMsg}");
    }

    public void onStopPublishCDNStream(int err, string errMsg) {
      PrintfTestCallbackLog($"onStopPublishCDNStream {err}, {errMsg}");
    }

    public void onStartPublishMediaStream(string taskID,
                                          int code,
                                          string message,
                                          string extraInfo) {
      mTaskId = taskID;
      PrintfTestCallbackLog(
          $"onStartPublishMediaStream taskID: {taskID}, {code}, {message}, {extraInfo}");
    }

    public void onUpdatePublishMediaStream(string taskID,
                                           int code,
                                           string message,
                                           string extraInfo) {
      PrintfTestCallbackLog(
          $"0nUpdatePublishMediaStream taskID: {taskID}, {code}, {message}, {extraInfo}");
    }

    public void onStopPublishMediaStream(string taskID,
                                         int code,
                                         string message,
                                         string extraInfo) {
      mTaskId = "";
      PrintfTestCallbackLog(
          $"onStopPublishMediaStream taskID: {taskID}, {code}, {message}, {extraInfo}");
    }

    public void onCdnStreamStateChanged(string cdnURL,
                                        int status,
                                        int code,
                                        string message,
                                        string extraInfo) {
      PrintfTestCallbackLog(
          $"onCdnStreamStateChanged cdnURL: {cdnURL}, {status}, {code}, {message}, {extraInfo}");
    }

    public void onConnectOtherRoom(string userId, TXLiteAVError errCode, string errMsg) {
      PrintfTestCallbackLog($"onConnectOtherRoom {userId}, {errCode}, {errMsg}");
    }

    public void onDisconnectOtherRoom(TXLiteAVError errCode, string errMsg) {
      PrintfTestCallbackLog($"onDisconnectOtherRoom {errCode}, {errMsg}");
    }

    public void onSwitchRoom(TXLiteAVError errCode, string errMsg) {
      PrintfTestCallbackLog($"onSwitchRoom {errCode}, {errMsg}");
    }

    public void onSpeedTestResult(TRTCSpeedTestResult result) {
      PrintfTestCallbackLog(
          $"onSpeedTestResult :{result.success}, errMsg: {result.errMsg},\n ip :{result.ip}, quality: {result.quality}, upLostRate :{result.upLostRate},\n downLostRate: {result.downLostRate}, rtt :{result.rtt}, availableUpBandwidth: {result.availableUpBandwidth},\n availableDownBandwidth :{result.availableDownBandwidth}, upJitter: {result.upJitter}, downJitter: {result.downJitter}");
    }

    [Obsolete("use onSpeedTestResult(TRTCSpeedTestResult)")]
    public void onSpeedTest(TRTCSpeedTestResult currentResult, int finishedCount, int totalCount) {}

    public void onTestMicVolume(int volume) {
      PrintfTestCallbackLog($"onTestMicVolume {volume}");
    }

    public void onTestSpeakerVolume(int volume) {
      PrintfTestCallbackLog($"onTestSpeakerVolume {volume}");
    }

    public void onAudioDeviceCaptureVolumeChanged(int volume, bool muted) {
      PrintfTestCallbackLog($"onAudioDeviceCaptureVolumeChanged {volume} , {muted}");
    }

    public void onAudioDevicePlayoutVolumeChanged(int volume, bool muted) {
      PrintfTestCallbackLog($"onAudioDevicePlayoutVolumeChanged {volume} , {muted}");
    }

    public void onSetMixTranscodingConfig(int errCode, String errMsg) {
      PrintfTestCallbackLog($"onSetMixTranscodingConfig {errCode} , {errMsg}");
    }

    public void onScreenCaptureStarted() {
      PrintfTestCallbackLog($"onScreenCaptureStarted");
    }

    public void onScreenCapturePaused(int reason) {
      PrintfTestCallbackLog($"onScreenCapturePaused {reason}");
    }

    public void onScreenCaptureResumed(int reason) {
      PrintfTestCallbackLog($"onScreenCaptureResumed {reason}");
    }

    public void onScreenCaptureStoped(int reason) {
      PrintfTestCallbackLog($"onScreenCaptureStoped {reason}");
    }

    public void onScreenCaptureCovered() {
      PrintfTestCallbackLog($"onScreenCaptureCovered ");
    }

#endregion



#region ITRTCAudioFrameCallback

    public void onCapturedRawAudioFrame(TRTCAudioFrame frame) {
      if(mApplicationPause) {
        return;
      }
      mainSyncContext.Post((object state) => {
        PrintfTestCallbackLog(
            $"onCapturedRawAudioFrame channel={frame.channel}, audioFormat={frame.audioFormat}, " +
            $"sampleRate={frame.sampleRate}, timestamp={frame.timestamp}");
      }, "");
    }

    public void onLocalProcessedAudioFrame(TRTCAudioFrame frame) {
      if(mApplicationPause) {
        return;
      }
      mainSyncContext.Post((object state) => {
        PrintfTestCallbackLog(
            $"onLocalProcessedAudioFrame channel={frame.channel}, audioFormat={frame.audioFormat}, " +
            $"sampleRate={frame.sampleRate}, timestamp={frame.timestamp}");
      }, "");
    }

    public void onMixedPlayAudioFrame(TRTCAudioFrame frame) {
      if(mApplicationPause) {
        return;
      }
      mainSyncContext.Post((object state) => {
        PrintfTestCallbackLog(
            $"onMixedPlayAudioFrame channel={frame.channel}, audioFormat={frame.audioFormat}, " +
            $"sampleRate={frame.sampleRate}, timestamp={frame.timestamp}");
      }, "");
    }

    public void onPlayAudioFrame(TRTCAudioFrame frame, string userId) {
      if(mApplicationPause) {
        return;
      }
      mainSyncContext.Post((object state) => {
        PrintfTestCallbackLog(
            $"onPlayAudioFrame channel={frame.channel}, audioFormat={frame.audioFormat}, " +
            $"sampleRate={frame.sampleRate}, timestamp={frame.timestamp}");
      }, "");
    }

    public void onLoadProgress(int id, int progress) {
      if(mApplicationPause) {
        return;
      }
      mainSyncContext.Post((object state) => {
        PrintfTestCallbackLog($"ITXMusicPreloadObserver onLoadProgress {id}, {progress}");
      }, "");
    }

    public void onLoadError(int id, int errorCode) {
      if(mApplicationPause) {
        return;
      }
      mainSyncContext.Post((object state) => {
        PrintfTestCallbackLog($"ITXMusicPreloadObserver onLoadError {id}, {errorCode}");
      }, "");
    }

    void OnApplicationPause(bool pauseStatus) {
      mApplicationPause = pauseStatus;
    }

#endregion

#region UI
    [SerializeField]
    private Text lblBtnClickLog;
    [SerializeField]
    private Text lblCallBackLog;

    private int logCountForBtnClick = 0;
    private string logStringForBtnClick = "";

    private void PrintfTestApiLog(string log) {
      if (logCountForBtnClick > 50) {
        logCountForBtnClick = 0;
        logStringForBtnClick = "";
      }

      logCountForBtnClick++;
      logStringForBtnClick += Environment.NewLine + log;
      lblBtnClickLog.text = logStringForBtnClick;
    }

    private int logCountForCallback = 0;
    private string logStringForCallback = "";

    private void PrintfTestCallbackLog(string log) {
      if(lblCallBackLog == null) {
        return;
      }

      if (logCountForCallback > 100) {
        logCountForCallback = 0;
        logStringForCallback = "";
      }

      logCountForCallback++;
      logStringForCallback += Environment.NewLine + log;
      lblCallBackLog.text = logStringForCallback;
    }

#endregion

    class MusicPlayObserver : ITXMusicPlayObserver {
      private AutoTestScript _testScript;
      private int _observerId;
      private SynchronizationContext _mainContext;

      public MusicPlayObserver(AutoTestScript script, SynchronizationContext context) {
        _testScript = script;
        _mainContext = context;
        _observerId = new System.Random().Next();
      }

      public void onStart(int id, int errCode) {
        _mainContext.Post((object state) => {
          _testScript.PrintfTestCallbackLog(
              $"playmusic {_observerId} onStart {id}, {errCode}");
        }, "");
      }

      public void onPlayProgress(int id, long curPtsMS, long durationMS) {
        _mainContext.Post((object state) => {
          _testScript.PrintfTestCallbackLog(
              $"playmusic {_observerId}  onPlayProgress {id}, {durationMS} ,{curPtsMS}");
          ;
        }, "");
      }

      public void onComplete(int id, int errCode) {
        _mainContext.Post((object state) => {
          _testScript.PrintfTestCallbackLog(
              $"playmusic {_observerId}  onComplete {id}, {errCode}");
        }, "");
      }
    }

    public void enterRoomTest() {
      TRTCParams trtcParams = new TRTCParams();
      trtcParams.sdkAppId = GenerateTestUserSig.SDKAPPID;
      DataManager.GetInstance().SetRoomID(mRoomInputFieId.text);
      DataManager.GetInstance().SetUserID(mUserIdInputFieId.text);
      trtcParams.roomId = uint.Parse(DataManager.GetInstance().GetRoomID());
      trtcParams.strRoomId = DataManager.GetInstance().GetRoomID();
      trtcParams.userId = DataManager.GetInstance().GetUserID();
      trtcParams.userSig =
          GenerateTestUserSig.GetInstance().GenTestUserSig(DataManager.GetInstance().GetUserID());
      // 如果您有进房权限保护的需求，则参考文档{https://cloud.tencent.com/document/product/647/32240}完成该功能。
      // 在有权限进房的用户中的下面字段中添加在服务器获取到的privateMapKey。
      trtcParams.privateMapKey = "";
      trtcParams.businessInfo = "";
      trtcParams.role = TRTCRoleType.TRTCRoleAnchor;
      TRTCAppScene scene = TRTCAppScene.TRTCAppSceneLIVE;
      mTRTCCloud?.enterRoom(ref trtcParams, scene);
      TRTCNetworkQosParam qosParams = DataManager.GetInstance().qosParams;  // 网络流控相关参数设置
      mTRTCCloud?.setNetworkQosParam(ref qosParams);
      DataManager.GetInstance().SetUserID(mUserIdInputFieId.text);
      DataManager.GetInstance().SetRoomID(mRoomInputFieId.text);
      PrintfTestApiLog("start enter room test");
    }

    // 音频相关接口函数
    public void startLocalAudioTest() {
      mTRTCCloud?.startLocalAudio(TRTCAudioQuality.TRTCAudioQualityDefault);
      PrintfTestApiLog($"startLocalAudio test");
    }

    public void stopLocalAudioTest() {
      mTRTCCloud?.stopLocalAudio();
      PrintfTestApiLog($"stopLocalAudio test");
    }

    public void startPlayMusicTest() {
      mTXAudioEffectManager ?.setMusicObserver(13, new MusicPlayObserver(this, mainSyncContext));

      var musicParam = new AudioMusicParam {
        id = 13,
        publish = true,
        loopCount = 20,
        startTimeMS = 10,
        endTimeMS = 30000,
        path =
            "https://imgcache.qq.com/operation/dianshi/other/daoxiang.72c46ee085f15dc72603b0ba154409879cbeb15e.mp3"
      };
      mTXAudioEffectManager?.startPlayMusic(musicParam);
     
    }

    public void stopPlayMusicTest() {
      mTXAudioEffectManager?.stopPlayMusic(13);
      PrintfTestApiLog($"stopPlayMusic test");
    }
  }
}