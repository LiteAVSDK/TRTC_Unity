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
using System.Text;
using System.Collections.Generic;

namespace TRTCCUnityDemo {
  public class ApiTestScript : MonoBehaviour,
                               ITRTCCloudCallback,
                               ITRTCVideoRenderCallback,
                               ITRTCAudioFrameCallback,
                               ITXMusicPreloadObserver,
                               ITXCopyrightedMediaCallback 
                               {
    // 主线程上下文
    SynchronizationContext mainSyncContext;

    private string LogForBtnClick = "";
    private string mTaskId = "";
    private AudioSource audio;
    private bool mApplicationPause = false;
    private string musicPath = "https://imgcache.qq.com/operation/dianshi/other/daoxiang.72c46ee085f15dc72603b0ba154409879cbeb15e.mp3";
    private bool bModifyRemoteUserAudioFrame = false;
    private bool bModifyCapturedAudioFrame = false;
    private bool bModifylocalProcessedAudioFrame = false;
    private bool bModifyMixedPlayAudioFrame = false;
#region ITRTCCloudCallback

    public void onRecvCustomCmdMsg(string userId,
                                   int cmdID,
                                   int seq,
                                   byte[] message,
                                   int messageSize) {
      string msg = System.Text.Encoding.UTF8.GetString(message, 0, messageSize);
      AppLogToCallback($"onRecvCustomCmdMsg {userId}, {cmdID} ,{msg}");
    }

    public void onMissCustomCmdMsg(string userId, int cmdID, int errCode, int missed) {
      AppLogToCallback($"onMissCustomCmdMsg {userId}, {cmdID}");
    }

    public void onError(TXLiteAVError errCode, String errMsg, IntPtr arg) {
      AppLogToCallback($"onError {errCode}, {errMsg}");
    }

    public void onWarning(TXLiteAVWarning warningCode, String warningMsg, IntPtr arg) {
      AppLogToCallback($"onWarning {warningCode}, {warningMsg}");
    }

    public void onEnterRoom(int result) {
      AppLogToCallback($"onEnterRoom {result}");
    }

    public void onExitRoom(int reason) {
      AppLogToCallback($"onExitRoom {reason}");
    }

    public void onSwitchRole(TXLiteAVError errCode, String errMsg) {
      AppLogToCallback($"onSwitchRole {errCode}, {errMsg}");
    }

    public void onRemoteUserEnterRoom(String userId) {
      AppLogToCallback($"onRemoteUserEnterRoom {userId}");
    }

    public void onRemoteUserLeaveRoom(String userId, int reason) {
      AppLogToCallback($"onRemoteUserLeaveRoom {userId}, {reason}");
    }

    public void onUserVideoAvailable(String userId, bool available) {
      AppLogToCallback($"onUserVideoAvailable {userId}, {available}");
      // Important: startRemoteView is needed for receiving video stream.
      if (available) {
        getTRTCCloudInstance()?.startRemoteView(userId, TRTCVideoStreamType.TRTCVideoStreamTypeBig,
                                                null);
      } else {
        getTRTCCloudInstance()?.stopRemoteView(userId, TRTCVideoStreamType.TRTCVideoStreamTypeBig);
      }
    }

    public void onUserSubStreamAvailable(string userId, bool available) {
      AppLogToCallback($"onUserSubStreamAvailable {userId}, {available}");
    }

    public void onUserAudioAvailable(String userId, bool available) {
      AppLogToCallback($"onUserAudioAvailable {userId}, {available}");
    }

    public void onFirstVideoFrame(String userId,
                                  TRTCVideoStreamType streamType,
                                  int width,
                                  int height) {
      AppLogToCallback($"onFirstVideoFrame {userId}, {streamType}, {width}, {height}");
    }

    public void onFirstAudioFrame(String userId) {
      AppLogToCallback($"onFirstAudioFrame {userId}");
    }

    public void onSendFirstLocalVideoFrame(TRTCVideoStreamType streamType) {
      AppLogToCallback($"onSendFirstLocalVideoFrame {streamType}");
    }

    public void onSendFirstLocalAudioFrame() {
      AppLogToCallback($"onSendFirstLocalAudioFrame");
    }

    public void onNetworkQuality(TRTCQualityInfo localQuality,
                                 TRTCQualityInfo[] remoteQuality,
                                 UInt32 remoteQualityCount) {
      // lblCallbakLog.text += Environment.NewLine + String.Format("onNetworkQuality {0}, {1}, {2}",
      // localQuality, remoteQuality, remoteQualityCount);
    }

    public void onStatistics(TRTCStatistics statis) {
      // foreach (TRTCLocalStatistics local in statis.localStatisticsArray) {
      //   if (local.streamType == TRTCVideoStreamType.TRTCVideoStreamTypeBig) {
      //     AppLogToCallback(
      //         $"width: {local.width}\r\nheight: {local.height}\r\nvideoframerate: {local.frameRate}\r\n" +
      //         $"videoBitrate: {local.videoBitrate}\r\naudioSampleRate: {local.audioSampleRate}\r\n" +
      //         $"audioBitrate:{local.audioBitrate}\r\nstreamType:{local.streamType}\r\n");
      //   }
      // }

      // foreach (TRTCRemoteStatistics remote in statis.remoteStatisticsArray) {
      //   if (remote.streamType == TRTCVideoStreamType.TRTCVideoStreamTypeBig) {
      //     AppLogToCallback(
      //         $"finalLoss: {remote.finalLoss}\r\njitterBufferDelay: {remote.jitterBufferDelay}\r\n" +
      //         $"width: {remote.width}\r\nheight: {remote.height}\r\n" +
      //         $"videoframerate: {remote.frameRate}\r\nvideoBitrate: {remote.videoBitrate}\r\n" +
      //         $"audioSampleRate: {remote.audioSampleRate}\r\naudioBitrate:{remote.audioBitrate}\r\n" +
      //         $"streamType:{remote.streamType}\r\n");
      //   }
      // }
    }

    public void onConnectionLost() {
      AppLogToCallback($"onConnectionLost");
    }

    public void onTryToReconnect() {
      AppLogToCallback($"onTryToReconnect");
    }

    public void onConnectionRecovery() {
      AppLogToCallback($"onConnectionRecovery");
    }

    public void onCameraDidReady() {
      AppLogToCallback($"onCameraDidReady");
    }

    public void onMicDidReady() {
      AppLogToCallback($"onMicDidReady");
    }

    public void onAudioRouteChanged(TRTCAudioRoute newRoute, TRTCAudioRoute oldRoute) {
       AppLogToCallback($"onAudioRouteChanged newRoute: " + newRoute + ", oldRoute: " + oldRoute);
    }


    public void onUserVoiceVolume(TRTCVolumeInfo[] userVolumes,
                                  UInt32 userVolumesCount,
                                  UInt32 totalVolume) {
      AppLogToCallback($"totalVolume= {totalVolume}");
    }

    public void onDeviceChange(String deviceId, TRTCDeviceType type, TRTCDeviceState state) {
      AppLogToCallback($"onSwitchRole {deviceId}, {type}, {state}");
    }

    public void onRecvSEIMsg(String userId, Byte[] message, UInt32 msgSize) {
      string seiMessage = System.Text.Encoding.UTF8.GetString(message, 0, (int)msgSize);
      AppLogToCallback($"onRecvSEIMsg {userId}, {seiMessage}, {msgSize}");
    }

    public void onStartPublishing(int err, string errMsg) {
      AppLogToCallback($"onStartPublishing {err}, {errMsg}");
    }

    public void onStopPublishing(int err, string errMsg) {
      AppLogToCallback($"onStopPublishing {err}, {errMsg}");
    }

    public void onStartPublishCDNStream(int err, string errMsg) {
      AppLogToCallback($"onStartPublishCDNStream {err}, {errMsg}");
    }

    public void onStopPublishCDNStream(int err, string errMsg) {
      AppLogToCallback($"onStopPublishCDNStream {err}, {errMsg}");
    }

    public void onStartPublishMediaStream(string taskID,
                                          int code,
                                          string message,
                                          string extraInfo) {
      mTaskId = taskID;
      AppLogToCallback(
          $"onStartPublishMediaStream taskID: {taskID}, {code}, {message}, {extraInfo}");
    }

    public void onUpdatePublishMediaStream(string taskID,
                                           int code,
                                           string message,
                                           string extraInfo) {
      AppLogToCallback(
          $"0nUpdatePublishMediaStream taskID: {taskID}, {code}, {message}, {extraInfo}");
    }

    public void onStopPublishMediaStream(string taskID,
                                         int code,
                                         string message,
                                         string extraInfo) {
      mTaskId = "";
      AppLogToCallback(
          $"onStopPublishMediaStream taskID: {taskID}, {code}, {message}, {extraInfo}");
    }

    public void onCdnStreamStateChanged(string cdnURL,
                                        int status,
                                        int code,
                                        string message,
                                        string extraInfo) {
      AppLogToCallback(
          $"onCdnStreamStateChanged cdnURL: {cdnURL}, {status}, {code}, {message}, {extraInfo}");
    }

    public void onConnectOtherRoom(string userId, TXLiteAVError errCode, string errMsg) {
      AppLogToCallback($"onConnectOtherRoom {userId}, {errCode}, {errMsg}");
    }

    public void onDisconnectOtherRoom(TXLiteAVError errCode, string errMsg) {
      AppLogToCallback($"onDisconnectOtherRoom {errCode}, {errMsg}");
    }

    public void onSwitchRoom(TXLiteAVError errCode, string errMsg) {
      AppLogToCallback($"onSwitchRoom {errCode}, {errMsg}");
    }

    public void onSpeedTestResult(TRTCSpeedTestResult result) {
      AppLogToCallback(
          $"onSpeedTestResult :{result.success}, errMsg: {result.errMsg},\n ip :{result.ip}, quality: {result.quality}, upLostRate :{result.upLostRate},\n downLostRate: {result.downLostRate}, rtt :{result.rtt}, availableUpBandwidth: {result.availableUpBandwidth},\n availableDownBandwidth :{result.availableDownBandwidth}, upJitter: {result.upJitter}, downJitter: {result.downJitter}");
    }

    [Obsolete("use onSpeedTestResult(TRTCSpeedTestResult)")]
    public void onSpeedTest(TRTCSpeedTestResult currentResult, int finishedCount, int totalCount) {}

    public void onTestMicVolume(int volume) {
      AppLogToCallback($"onTestMicVolume {volume}");
    }

    public void onTestSpeakerVolume(int volume) {
      AppLogToCallback($"onTestSpeakerVolume {volume}");
    }

    public void onAudioDeviceCaptureVolumeChanged(int volume, bool muted) {
      AppLogToCallback($"onAudioDeviceCaptureVolumeChanged {volume} , {muted}");
    }

    public void onAudioDevicePlayoutVolumeChanged(int volume, bool muted) {
      AppLogToCallback($"onAudioDevicePlayoutVolumeChanged {volume} , {muted}");
    }

    public void onSetMixTranscodingConfig(int errCode, String errMsg) {
      AppLogToCallback($"onSetMixTranscodingConfig {errCode} , {errMsg}");
    }

    public void onScreenCaptureStarted() {
      AppLogToCallback($"onScreenCaptureStarted");
    }

    public void onScreenCapturePaused(int reason) {
      AppLogToCallback($"onScreenCapturePaused {reason}");
    }

    public void onScreenCaptureResumed(int reason) {
      AppLogToCallback($"onScreenCaptureResumed {reason}");
    }

    public void onScreenCaptureStoped(int reason) {
      AppLogToCallback($"onScreenCaptureStoped {reason}");
    }

    public void onScreenCaptureCovered() {
      AppLogToCallback($"onScreenCaptureCovered ");
    }

#endregion

#region ITRTCAudioFrameCallback
    public byte[] modifyPcmVolume(byte[] pcmData) {
      if (pcmData == null || pcmData.Length == 0) {
        return null;
      }
      if (pcmData.Length % 2 != 0) {
        return null;
      }  

      short[] samples = new short[pcmData.Length / 2];
      Buffer.BlockCopy(pcmData, 0, samples, 0, pcmData.Length);
      for (int i = 0; i < samples.Length; i++) {
          samples[i] = (short)(samples[i] / 3);
      }

      byte[] result = new byte[pcmData.Length];
      Buffer.BlockCopy(samples, 0, result, 0, result.Length);

      return result;
    }

    public void onCapturedRawAudioFrame(TRTCAudioFrame frame) {
      if(mApplicationPause) {
        return;
      }

      if(bModifyCapturedAudioFrame) {
        byte[] pcmData = modifyPcmVolume(frame.data);
        if(pcmData != null && pcmData.Length > 0) {
          Array.Copy(pcmData, frame.data, frame.length);
        }
      }

      mainSyncContext.Post((object state) => {
        AppLogToCallback(
            $"onCapturedRawAudioFrame channel={frame.channel}, audioFormat={frame.audioFormat}, " +
            $"sampleRate={frame.sampleRate}, timestamp={frame.timestamp}");
      }, "");
    }

    public void onLocalProcessedAudioFrame(TRTCAudioFrame frame) {
      if(bModifylocalProcessedAudioFrame) {
        byte[] pcmData = modifyPcmVolume(frame.data);
        if(pcmData != null && pcmData.Length > 0) {
          Array.Copy(pcmData, frame.data, frame.length);
        }
      }

      if(mApplicationPause) {
        return;
      }
      mainSyncContext.Post((object state) => {
        AppLogToCallback(
            $"onLocalProcessedAudioFrame channel={frame.channel}, audioFormat={frame.audioFormat}, " +
            $"sampleRate={frame.sampleRate}, timestamp={frame.timestamp}");
      }, "");
    }

    public void onMixedPlayAudioFrame(TRTCAudioFrame frame) {
      if(bModifyMixedPlayAudioFrame) {
        byte[] pcmData = modifyPcmVolume(frame.data);
        if(pcmData != null && pcmData.Length > 0) {
          Array.Copy(pcmData, frame.data, frame.length);
        }
      }
      
      if(mApplicationPause) {
        return;
      }
      mainSyncContext.Post((object state) => {
        AppLogToCallback(
            $"onMixedPlayAudioFrame channel={frame.channel}, audioFormat={frame.audioFormat}, " +
            $"sampleRate={frame.sampleRate}, timestamp={frame.timestamp}");
      }, "");
    }

    public void onPlayAudioFrame(TRTCAudioFrame frame, string userId) {
      if(bModifyRemoteUserAudioFrame) {
        byte[] pcmData = modifyPcmVolume(frame.data);
        if(pcmData != null && pcmData.Length > 0) {
          Array.Copy(pcmData, frame.data, frame.length);
        }
      }

      if(mApplicationPause) {
        return;
      }
      mainSyncContext.Post((object state) => {
        AppLogToCallback(
            $"onPlayAudioFrame channel={frame.channel}, audioFormat={frame.audioFormat}, " +
            $"sampleRate={frame.sampleRate}, timestamp={frame.timestamp}");
      }, "");
    }

    public void onLoadProgress(int id, int progress) {
      if(mApplicationPause) {
        return;
      }
      mainSyncContext.Post((object state) => {
        AppLogToCallback($"ITXMusicPreloadObserver onLoadProgress {id}, {progress}");
      }, "");
    }

    public void onLoadError(int id, int errorCode) {
      if(mApplicationPause) {
        return;
      }
      mainSyncContext.Post((object state) => {
        AppLogToCallback($"ITXMusicPreloadObserver onLoadError {id}, {errorCode}");
      }, "");
    }

    void OnApplicationPause(bool pauseStatus) {
      mApplicationPause = pauseStatus;
    }

#endregion

#region ITXCopyrightedMediaCallback
    public void onPreloadStart(string musicId, string bitrateDefinition) {
      if(mApplicationPause) {
        return;
      }
       mainSyncContext.Post((object state) => {
          AppLogToCallback($"onPreloadStart musicId={musicId}, bitrateDefinition={bitrateDefinition}");
        }, "");
    }

    public void onPreloadProgress(string musicId, string bitrateDefinition, float progress) {
      if(mApplicationPause) {
        return;
      }
      mainSyncContext.Post((object state) => {
          AppLogToCallback($"onPreloadProgress musicId={musicId}, bitrateDefinition={bitrateDefinition}, progress={progress}");
        }, "");
      
    }
    public void onPreloadComplete(string musicId, string bitrateDefinition, int errorCode, string msg) {
      if(mApplicationPause) {
        return;
      }
      mainSyncContext.Post((object state) => {
          AppLogToCallback($"onPreloadComplete musicId={musicId}, bitrateDefinition={bitrateDefinition}, errorCode={errorCode}");
        }, "");
    }
#endregion

#region UI

    [SerializeField]
    private InputField inputRoomID;
    [SerializeField]
    private InputField inputUserId;
    [SerializeField]
    private InputField inputParam;
    [SerializeField]
    private InputField inputMusicID;
    [SerializeField]
    private InputField inputBitrate;
    [SerializeField]
    private InputField inputBgmType;
    [SerializeField]
    private Text lblBtnClickLog;
    [SerializeField]
    private Text lblCallBackLog;

    // public UserTableView userTableView;
    [SerializeField]
    private Canvas canvas;
    [SerializeField]
    private GameObject content;
    [SerializeField]
    private Font font;

    private int logCountForBtnClick = 0;
    private string logStringForBtnClick = "";

    private void AppLogToBtnClick(string log) {
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

    private void AppLogToCallback(string log) {
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
      private ApiTestScript _testScript;
      private int _observerId;
      private SynchronizationContext _mainContext;

      public MusicPlayObserver(ApiTestScript script, SynchronizationContext context) {
        _testScript = script;
        _mainContext = context;
        _observerId = new System.Random().Next();
      }

      public void onStart(int id, int errCode) {
        _mainContext.Post((object state) => {
          _testScript.AppLogToCallback(
              $"ITXMusicPlayObserver {_observerId} onStart {id}, {errCode}");
        }, "");
      }

      public void onPlayProgress(int id, long curPtsMS, long durationMS) {
        _mainContext.Post((object state) => {
          _testScript.AppLogToCallback(
              $"ITXMusicPlayObserver {_observerId}  onPlayProgress {id}, {durationMS} ,{curPtsMS}");
          ;
        }, "");
      }

      public void onComplete(int id, int errCode) {
        _mainContext.Post((object state) => {
          _testScript.AppLogToCallback(
              $"ITXMusicPlayObserver {_observerId}  onComplete {id}, {errCode}");
        }, "");
      }
    }

    class MusicPreloadObserver : ITXMusicPreloadObserver {
      private readonly ApiTestScript _testScript;
      private readonly SynchronizationContext _mainContext;

      public MusicPreloadObserver(ApiTestScript script, SynchronizationContext context) {
        _testScript = script;
        _mainContext = context;
      }

      public void onLoadProgress(int id, int progress) {
        _mainContext.Post((object state) => {
          _testScript.AppLogToCallback($"ITXMusicPreloadObserver onLoadProgress {id}, {progress}");
        }, "");
      }

      public void onLoadError(int id, int error) {
        _mainContext.Post((object state) => {
          _testScript.AppLogToCallback($"ITXMusicPreloadObserver onLoadError {id}, {error}");
        }, "");
      }
    }

#region trtc

    private ITRTCCloud mTRTCCloud;
    private ITRTCCloud mTRTCSubCloud;
    private ITXAudioEffectManager mTXAudioEffectManager;
    private ITXDeviceManager mTXDeviceManager;
    private ITXCopyrightedMedia mTXCopyrightedMedia;

    private TRTCVideoStreamType _streamType = TRTCVideoStreamType.TRTCVideoStreamTypeBig;
    private bool _enable = true;

    private VideoRenderType _videoRenderType = VideoRenderType.None;
    private TRTCVideoPixelFormat _videoFormat = TRTCVideoPixelFormat.TRTCVideoPixelFormat_BGRA32;
    private List<int> mAudioChannelList = new List<int> { 16000, 32000, 44100, 48000};
    private Dropdown mTrtcCloudDropdown;
    private Dropdown mSampleRateDropdown;
    private Dropdown mAudioChannelDropdown;
    private Dropdown mAudioOnlyReadDropdown;
    


#endregion

    void Start() {
      // 获取主线程上下文
      mainSyncContext = SynchronizationContext.Current;
      createBtns();
      initTrtc();
      CopyResources();
      musicPath = "https://imgcache.qq.com/operation/dianshi/other/daoxiang.72c46ee085f15dc72603b0ba154409879cbeb15e.mp3";
      audio = BackGroundMusicHelper.getInstanceGroundMusicHelper().getAudioSoucre();
      GameObject trtcCloudobj = transform.Find("Left/roomPanel/dropdownInstance").gameObject;
      if (trtcCloudobj != null) {
        mTrtcCloudDropdown = trtcCloudobj.GetComponent<Dropdown>();
      }
      GameObject sampleRateObj = transform.Find("Left/roomPanel/dropdownSampleRate").gameObject;
      if (sampleRateObj != null) {
        mSampleRateDropdown = sampleRateObj.GetComponent<Dropdown>();
        foreach (int value in mAudioChannelList)
        {
          mSampleRateDropdown.options.Add(new Dropdown.OptionData(value.ToString())); 
        }
      }
      GameObject audioChannelObj = transform.Find("Left/roomPanel/dropdownAudioChannel").gameObject;
      if (audioChannelObj != null) {
        mAudioChannelDropdown = audioChannelObj.GetComponent<Dropdown>();
      }

      GameObject audioOnlyReadObj = transform.Find("Left/roomPanel/dropdownAudioOnlyRead").gameObject;
      if (audioOnlyReadObj != null) {
        mAudioOnlyReadDropdown = audioOnlyReadObj.GetComponent<Dropdown>();
      }
    }

    private int getAudioSampleRate() {
      if(mSampleRateDropdown) {
        return mAudioChannelList[mSampleRateDropdown.value];
      }

      return 16000;
    }

    private int getAudioChannel() {
      if(mAudioChannelDropdown) {
        return mAudioChannelDropdown.value + 1;
      }

      return 1;
    }

    private TRTCAudioFrameOperationMode getAudioDataOperationmode() {
      if(mAudioOnlyReadDropdown) {
        if(mAudioOnlyReadDropdown.value == 0) {
          return TRTCAudioFrameOperationMode.TRTCAudioFrameOperationModeReadWrite;
        } else {
          return TRTCAudioFrameOperationMode.TRTCAudioFrameOperationModeReadOnly;
        }
      }

      return TRTCAudioFrameOperationMode.TRTCAudioFrameOperationModeReadWrite;
    }



    public void Awake() {
#if PLATFORM_ANDROID
      _videoFormat = TRTCVideoPixelFormat.TRTCVideoPixelFormat_RGBA32;
#endif
    }

    private void createBtns() {
      var builder = new ApiTestBtnBuilder(content, font, this);
      builder.init();
      inputRoomID.text = DataManager.GetInstance().GetRoomID();
      inputUserId.text = DataManager.GetInstance().GetUserID();
      var enterRoomBtn =
          transform.Find("Left/roomPanel/btnLogin").gameObject.GetComponent<Button>();
      enterRoomBtn.onClick.AddListener(() => {
        DataManager.GetInstance().SetUserID(inputUserId.text);
        DataManager.GetInstance().SetRoomID(inputRoomID.text);
        SceneManager.LoadScene("RoomScene", LoadSceneMode.Single);
      });

      var exitBtn = transform.Find("Left/roomPanel/btnExit").gameObject.GetComponent<Button>();
      exitBtn.onClick.AddListener(
          () => { SceneManager.LoadScene("HomeScene", LoadSceneMode.Single); });
    }

    private void initTrtc() {
      mTRTCCloud = ITRTCCloud.getTRTCShareInstance();
      mTRTCCloud.addCallback(this);
      mTRTCSubCloud = mTRTCCloud.createSubCloud();
      mTRTCSubCloud.addCallback(this);
      mTXAudioEffectManager = mTRTCCloud.getAudioEffectManager();
      mTXDeviceManager = mTRTCCloud.getDeviceManager();
      mTXCopyrightedMedia = ITXCopyrightedMedia.createCopyRightMedia();
    }

    private ITRTCCloud getTRTCCloudInstance() {
      if (!mTrtcCloudDropdown || mTrtcCloudDropdown.value == 0) {
        return mTRTCCloud;
      }
      return mTRTCSubCloud;
    }

    private ITXAudioEffectManager getAudioEffectManager() {
      return getTRTCCloudInstance()?.getAudioEffectManager();
    }

    private ITXDeviceManager getDeviceManager() {
      return getTRTCCloudInstance()?.getDeviceManager();
    }

    IntPtr mNativeTextureData = Marshal.AllocHGlobal(4000 * 3000 * 4);
    bool isVideoRenderDataClick = false;

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
      mTXCopyrightedMedia?.destroyCopyRightMedia();
      mTRTCCloud?.removeCallback(this);
      ITRTCCloud.destroyTRTCShareInstance();
      DataManager.GetInstance().ResetLocalAVFlag();
      Marshal.FreeHGlobal(mNativeTextureData);
    }

#region btn click

    public void onRenderVideoFrame(string userId,
                                   TRTCVideoStreamType streamType,
                                   TRTCVideoFrame frame) {}

    public void GetVideoRenderDataClick() {
      int width = 0;
      int height = 0;
      int length = 0;
      int mTextureRotation = 0;
      string _userId = "";
      isVideoRenderDataClick = true;
      // mTRTCCloud.GetVideoRenderData("", ref mTextureRotation, ref width, ref height, ref length,
      //                               false);

      AppLogToBtnClick(
          $"width = {width}, height={height}, length={length}，data={mNativeTextureData.ToString()}");
    }
    public void getTRTCShareInstanceClick() {
      if (mTRTCCloud != null) {
        AppLogToBtnClick("TRTCShareInstance have create, not create");
        return;
      }
      mTRTCCloud = ITRTCCloud.getTRTCShareInstance();
      mTRTCCloud.addCallback(this);
      mTXAudioEffectManager = mTRTCCloud.getAudioEffectManager();
      mTXDeviceManager = mTRTCCloud.getDeviceManager();
      AppLogToBtnClick("TRTCShareInstance create success");

      mTRTCSubCloud = mTRTCCloud?.createSubCloud();
      mTRTCSubCloud?.addCallback(this);
    }

    public void destroyTRTCShareInstanceClick() {
      AppLogToBtnClick("destroyTRTCShareInstanceClick");
      mTRTCCloud?.removeCallback(this);
      ITRTCCloud.destroyTRTCShareInstance();
      mTRTCCloud = null;
    }

    public void createSubCloudClick() {
      if (mTRTCCloud == null) {
        AppLogToBtnClick("createSubCloud fail, ShareInstance is null ");
        return;
      }
      if (mTRTCSubCloud != null) {
        AppLogToBtnClick("SubCloud have create, not create");
        return;
      }
      mTRTCSubCloud = mTRTCCloud?.createSubCloud();
      mTRTCSubCloud?.addCallback(this);
      AppLogToBtnClick("SubCloud  create success");
    }
    public void destroySubCloudClick() {
      AppLogToBtnClick("destroySubCloudClick");
      mTRTCSubCloud?.removeCallback(this);
      mTRTCCloud?.destroySubCloud(mTRTCSubCloud);
      mTRTCSubCloud = null;
    }

    public void enterRoomClick() {
      TRTCParams trtcParams = new TRTCParams();
      trtcParams.sdkAppId = GenerateTestUserSig.SDKAPPID;
      DataManager.GetInstance().SetRoomID(inputRoomID.text);
      DataManager.GetInstance().SetUserID(inputUserId.text);
      trtcParams.roomId = uint.Parse(DataManager.GetInstance().GetRoomID());
      trtcParams.strRoomId = DataManager.GetInstance().GetRoomID();
      trtcParams.userId = DataManager.GetInstance().GetUserID();
      trtcParams.userSig =
          GenerateTestUserSig.GetInstance().GenTestUserSig(DataManager.GetInstance().GetUserID());
      // 如果您有进房权限保护的需求，则参考文档{https://cloud.tencent.com/document/product/647/32240}完成该功能。
      // 在有权限进房的用户中的下面字段中添加在服务器获取到的privateMapKey。
      trtcParams.privateMapKey = "";
      trtcParams.businessInfo = "";
      // trtcParams.role = DataManager.GetInstance().roleType;
      trtcParams.role = TRTCRoleType.TRTCRoleAnchor;
      // TRTCAppScene scene = DataManager.GetInstance().appScene;
      TRTCAppScene scene = TRTCAppScene.TRTCAppSceneLIVE;
      getTRTCCloudInstance()?.enterRoom(ref trtcParams, scene);
      TRTCNetworkQosParam qosParams = DataManager.GetInstance().qosParams;  // 网络流控相关参数设置
      getTRTCCloudInstance()?.setNetworkQosParam(ref qosParams);
      // AppLogToBtnClick($"Scene:{scene}, Role:{trtcParams.role}, " +
      //                  $"Qos-Prefer:{qosParams.preference},
      //                  Qos-CtrlMode:{qosParams.controlMode}");
      AppLogToBtnClick($"Scene:{scene}, Role:{trtcParams.role}, " +
                       $"Qos-Prefer:{qosParams.preference}");
    }

    public void exitRoomClick() {
      getTRTCCloudInstance()?.exitRoom();
      DataManager.GetInstance().ResetLocalAVFlag();
      TRTCVideoEncParam videoEncParams = DataManager.GetInstance().videoEncParam;
      getTRTCCloudInstance()?.setVideoEncoderParam(ref videoEncParams);
      AppLogToBtnClick($"exitRoomClick");
    }

    public void switchRoleClick() {
      getTRTCCloudInstance()?.switchRole(DataManager.GetInstance().roleType);
      AppLogToBtnClick($"switchRole = {DataManager.GetInstance().roleType}");
    }

    public void switchRoleAudience() {
      getTRTCCloudInstance()?.switchRole(TRTCRoleType.TRTCRoleAudience);
      AppLogToBtnClick($"switchRole = TRTCRoleAudience");
    }

    public void switchRoleArchor() {
      getTRTCCloudInstance()?.switchRole(TRTCRoleType.TRTCRoleAnchor);
      AppLogToBtnClick($"switchRole = TRTCRoleAnchor");
    }

    public void ConnectOtherRoomClick() {
      JsonData jsonObj = new JsonData();
      jsonObj["roomId"] = 1908;
      jsonObj["userId"] = "345";
      string jsonData = JsonMapper.ToJson(jsonObj);
      getTRTCCloudInstance()?.connectOtherRoom(jsonData);
      AppLogToBtnClick($"connectOtherRoom = {jsonData}");
    }

    public void disconnectOtherRoomClick() {
      getTRTCCloudInstance()?.disconnectOtherRoom();
      AppLogToBtnClick($"disconnectOtherRoom");
    }

    public void sendSEIMsg() {
      if (getTRTCCloudInstance() == null) {
        return;
      }
      string seiMsg = "test sei message";
      int seiSize = System.Text.Encoding.UTF8.GetByteCount(seiMsg);
      bool result = getTRTCCloudInstance().sendSEIMsg(System.Text.Encoding.UTF8.GetBytes(seiMsg),
                                                      seiSize, 30);
      AppLogToBtnClick($"sendSEIMsg = {result} ,seiSize={seiSize}");
    }

    public void setLogLevelClick() {
      getTRTCCloudInstance()?.setLogLevel(TRTCLogLevel.TRTCLogLevelVerbose);
      AppLogToBtnClick($"setLogLevelClick TRTCLogLevelVerbose");
    }

    public void setConsoleEnabledClick() {
      getTRTCCloudInstance()?.setConsoleEnabled(true);
      AppLogToBtnClick($"setConsoleEnabledClick");
    }

    public void setLogCompressEnabledFalseClick() {
      getTRTCCloudInstance()?.setLogCompressEnabled(false);
      AppLogToBtnClick($"setLogCompressEnabledFalseClick");
    }

    public void setLogCompressEnabledTrueClick() {
      getTRTCCloudInstance()?.setLogCompressEnabled(true);
      AppLogToBtnClick($"setLogCompressEnabledTrueClick");
    }

    public void setLogDirPathClick() {
      string currentDirectory = System.IO.Directory.GetCurrentDirectory();
      getTRTCCloudInstance()?.setLogDirPath(currentDirectory);
      AppLogToBtnClick($"setLogDirPathClick = {currentDirectory}");
    }

    public void sendCustomCmdMsgClick() {
      if (getTRTCCloudInstance() == null) {
        return;
      }
      string cmdMsg = "test Custom CMD";
      bool result = getTRTCCloudInstance().sendCustomCmdMsg(
          01, System.Text.Encoding.Default.GetBytes(cmdMsg),
          System.Text.Encoding.Default.GetByteCount(cmdMsg), false, false);
      AppLogToBtnClick($"sendCustomCmdMsg = {result}");
    }

    public void switchRoomClick() {
      TRTCSwitchRoomConfig mConfig =
          new TRTCSwitchRoomConfig { roomId = 1907,
                                     userSig = GenerateTestUserSig.GetInstance().GenTestUserSig(
                                         DataManager.GetInstance().GetUserID()) };
      // mConfig.privateMapKey = "";
      getTRTCCloudInstance()?.switchRoom(mConfig);
      AppLogToBtnClick($"switchRoom 1907");
    }

    public void TRTCPublishBigStreamToCdnClick() {
      var mTarget =
          new TRTCPublishTarget { cdnUrlListSize = 1, cdnUrlList = new TRTCPublishCdnUrl[1] };
      mTarget.cdnUrlList[0].rtmpUrl = inputParam.text;
      mTarget.cdnUrlList[0].isInternalLine = true;
      mTarget.mode = TRTCPublishMode.TRTCPublishBigStreamToCdn;
      mTarget.mixStreamIdentity.strRoomId = DataManager.GetInstance().GetRoomID();
      mTarget.mixStreamIdentity.userId = "3243";

      var mStreamEncoderParam = new TRTCStreamEncoderParam {
        videoEncodedWidth = 1280,
        videoEncodedHeight = 720,
        videoEncodedFps = 20,
        videoEncodedGop = 3,
        videoEncodedKbps = 0,
        audioEncodedChannelNum = 2,
        audioEncodedSampleRate = 48000,
        audioEncodedKbps = 50
      };

      var mStreamMixingConfig = new TRTCStreamMixingConfig();
      getTRTCCloudInstance()?.startPublishMediaStream(ref mTarget, ref mStreamEncoderParam,
                                                      ref mStreamMixingConfig);
      
      AppLogToBtnClick($"TRTCPublishBigStreamToCdnClick");
    }
    
    public void TRTCPublishMixStreamToRoomClick() {
      var mTarget =
           new TRTCPublishTarget { cdnUrlListSize = 1, cdnUrlList = new TRTCPublishCdnUrl[1] };
      mTarget.mode = TRTCPublishMode.TRTCPublishMixStreamToRoom;
      mTarget.mixStreamIdentity.strRoomId = "";
      mTarget.mixStreamIdentity.userId = "600000";
      mTarget.mixStreamIdentity.intRoomId = 678;

      var mStreamEncoderParam = new TRTCStreamEncoderParam {
        videoEncodedWidth = 640,
        videoEncodedHeight = 640,
        videoEncodedFps = 20,
        videoEncodedGop = 3,
        videoEncodedKbps = 0,
        audioEncodedChannelNum = 2,
        audioEncodedSampleRate = 48000,
        audioEncodedKbps = 50
      };

      var mStreamMixingConfig = new TRTCStreamMixingConfig();
      int videoLayoutListSize = 2;
      mStreamMixingConfig.watermarkList = new TRTCWaterMark[1];
      mStreamMixingConfig.videoLayoutList = new TRTCVideoLayout[videoLayoutListSize];
      for (int i = 0; i < videoLayoutListSize; i++) {
        mStreamMixingConfig.videoLayoutList[i].fillMode = TRTCVideoFillMode.TRTCVideoFillMode_Fill;
        mStreamMixingConfig.videoLayoutList[i].zOrder = i + 1;
        mStreamMixingConfig.videoLayoutList[i].backgroundColor = 0xFFFFFF;
      }


      mStreamMixingConfig.videoLayoutList[0].rect.left = 0;
      mStreamMixingConfig.videoLayoutList[0].rect.top = 0;
      mStreamMixingConfig.videoLayoutList[0].rect.right = 640;
      mStreamMixingConfig.videoLayoutList[0].rect.bottom = 300;

      mStreamMixingConfig.videoLayoutList[1].rect.left = 0;
      mStreamMixingConfig.videoLayoutList[1].rect.top = 301;
      mStreamMixingConfig.videoLayoutList[1].rect.right = 640;
      mStreamMixingConfig.videoLayoutList[1].rect.bottom = 640;

      mStreamMixingConfig.videoLayoutList[0].fixedVideoUser = new TRTCUserParam {
        userId = DataManager.GetInstance().GetUserID(),
        intRoomId = (uint)int.Parse(DataManager.GetInstance().GetRoomID()),
        strRoomId = "0"
      };
      mStreamMixingConfig.videoLayoutList[1].fixedVideoUser = new TRTCUserParam {
        userId = "345",
        intRoomId = (uint)int.Parse(DataManager.GetInstance().GetRoomID()),
        strRoomId = "0"
      };
      mStreamMixingConfig.videoLayoutList[0].fixedVideoStreamType = TRTCVideoStreamType.TRTCVideoStreamTypeBig;
      mStreamMixingConfig.videoLayoutList[1].fixedVideoStreamType = TRTCVideoStreamType.TRTCVideoStreamTypeBig;

      mStreamMixingConfig.watermarkList[0].watermarkUrl = "https://liteav.sdk.qcloud.com/app/res/picture/tools_app/trtc_mix_stream_bg_1.jpg";
      mStreamMixingConfig.watermarkList[0].rect.left = 10;
      mStreamMixingConfig.watermarkList[0].rect.top = 10;
      mStreamMixingConfig.watermarkList[0].rect.right = 200;
      mStreamMixingConfig.watermarkList[0].rect.bottom = 300;

      getTRTCCloudInstance()?.startPublishMediaStream(ref mTarget, ref mStreamEncoderParam,
                                                      ref mStreamMixingConfig);
      AppLogToBtnClick($"TRTCPublishMixStreamToRoomClick");
    }

    public void updatePublishMediaStreamClick() {
      if (mTaskId == "") {
        AppLogToBtnClick($"updatePublishMediaStreamClick fail,mTaskId is empty");
        return;
      }
     var mTarget = new TRTCPublishTarget { cdnUrlListSize = 1, cdnUrlList = new TRTCPublishCdnUrl[1] };
      mTarget.mode = TRTCPublishMode.TRTCPublishMixStreamToRoom;
      mTarget.mixStreamIdentity.strRoomId = "";
      mTarget.mixStreamIdentity.userId = "600000";
      mTarget.mixStreamIdentity.intRoomId = 678;

      var mStreamEncoderParam = new TRTCStreamEncoderParam {
        videoEncodedWidth = 640,
        videoEncodedHeight = 640,
        videoEncodedFps = 20,
        videoEncodedGop = 3,
        videoEncodedKbps = 0,
        audioEncodedChannelNum = 2,
        audioEncodedSampleRate = 48000,
        audioEncodedKbps = 50
      };

      var mStreamMixingConfig = new TRTCStreamMixingConfig();
      int videoLayoutListSize = 2;
      mStreamMixingConfig.watermarkList = new TRTCWaterMark[1];
      mStreamMixingConfig.videoLayoutList = new TRTCVideoLayout[videoLayoutListSize];
      for (int i = 0; i < videoLayoutListSize; i++) {
        mStreamMixingConfig.videoLayoutList[i].fillMode = TRTCVideoFillMode.TRTCVideoFillMode_Fill;
        mStreamMixingConfig.videoLayoutList[i].zOrder = i + 1;
        mStreamMixingConfig.videoLayoutList[i].backgroundColor = 0xFFFFFF;
      }


      mStreamMixingConfig.videoLayoutList[0].rect.left = 0;
      mStreamMixingConfig.videoLayoutList[0].rect.top = 0;
      mStreamMixingConfig.videoLayoutList[0].rect.right = 640;
      mStreamMixingConfig.videoLayoutList[0].rect.bottom = 500;
      mStreamMixingConfig.videoLayoutList[0].fixedVideoUser = new TRTCUserParam {
        userId = DataManager.GetInstance().GetUserID(),
        intRoomId = (uint)int.Parse(DataManager.GetInstance().GetRoomID()),
        strRoomId = "0"
      };
      mStreamMixingConfig.videoLayoutList[0].fixedVideoStreamType = TRTCVideoStreamType.TRTCVideoStreamTypeBig;

      mStreamMixingConfig.watermarkList[0].watermarkUrl = "https://liteav.sdk.qcloud.com/app/res/picture/tools_app/trtc_mix_stream_bg_1.jpg";
      mStreamMixingConfig.watermarkList[0].rect.left = 10;
      mStreamMixingConfig.watermarkList[0].rect.top = 10;
      mStreamMixingConfig.watermarkList[0].rect.right = 300;
      mStreamMixingConfig.watermarkList[0].rect.bottom = 200;

      getTRTCCloudInstance()?.updatePublishMediaStream(mTaskId, ref mTarget, ref mStreamEncoderParam,
                                                      ref mStreamMixingConfig);
      AppLogToBtnClick($"updatePublishMediaStreamClick");
      
    }




    public void stopPublishMediaStreamClick() {
      getTRTCCloudInstance()?.stopPublishMediaStream(mTaskId);
      AppLogToBtnClick($"stopPublishCDNStream");
    }

    // 音频相关接口函数
    public void startLocalAudioClick() {
      getTRTCCloudInstance()?.muteLocalVideo(false);
      getTRTCCloudInstance()?.startLocalAudio(TRTCAudioQuality.TRTCAudioQualityDefault);
      AppLogToBtnClick($"startLocalAudio");
    }

    public void startSystemAudioLoopbackClick() {
      getTRTCCloudInstance()?.startSystemAudioLoopback("");
      AppLogToBtnClick($"startSystemAudioLoopbackClick");
    }

    public void stopSystemAudioLoopbackClick() {
      getTRTCCloudInstance()?.stopSystemAudioLoopback();
      AppLogToBtnClick($"stopSystemAudioLoopbackClick");
    }

    public void stopLocalAudioClick() {
      getTRTCCloudInstance()?.stopLocalAudio();
      AppLogToBtnClick($"stopLocalAudio");
    }

    public void muteLocalAudioClickTrue() {
      getTRTCCloudInstance()?.muteLocalAudio(true);
      AppLogToBtnClick($"muteLocalAudio true");
    }

    public void muteLocalAudioClickFalse() {
      getTRTCCloudInstance()?.muteLocalAudio(false);
      AppLogToBtnClick($"muteLocalAudio false");
    }

    public void muteRemoteAudioClickTrue() {
      getTRTCCloudInstance()?.muteRemoteAudio("345", true);
      AppLogToBtnClick($"muteRemoteAudio 345 true");
    }

    public void muteRemoteAudioClickFalse() {
      getTRTCCloudInstance()?.muteRemoteAudio("345", false);
      AppLogToBtnClick($"muteRemoteAudio 345 false");
    }

    public void muteAllRemoteAudioClickTrue() {
      getTRTCCloudInstance()?.muteAllRemoteAudio(true);
      AppLogToBtnClick($"muteAllRemoteAudio true");
    }

    public void muteAllRemoteAudioClickFalse() {
      getTRTCCloudInstance()?.muteAllRemoteAudio(false);
      AppLogToBtnClick($"muteAllRemoteAudio false");
    }

    public void setRemoteAudioVolumeClick0() {
      getTRTCCloudInstance()?.setRemoteAudioVolume("345", 0);
      AppLogToBtnClick($"setRemoteAudioVolume 345 0");
    }

    public void setRemoteAudioVolumeClick100() {
      getTRTCCloudInstance()?.setRemoteAudioVolume("345", 100);
      AppLogToBtnClick($"setRemoteAudioVolume 345 100");
    }

    public void setAudioCaptureVolumeClick() {
      getTRTCCloudInstance()?.setAudioCaptureVolume(95);
      AppLogToBtnClick($"setRemoteAudioVolume 95");
    }

    public void getAudioCaptureVolumeClick() {
      if (getTRTCCloudInstance() == null) {
        return;
      }
      int volume = getTRTCCloudInstance().getAudioCaptureVolume();
      AppLogToBtnClick($"CaptureVolume={volume}");
    }

    public void setAudioPlayoutVolumeClick() {
      getTRTCCloudInstance()?.setAudioPlayoutVolume(98);
      AppLogToBtnClick($"setAudioPlayoutVolume 98");
    }

    public void getAudioPlayoutVolumeClick() {
      if (getTRTCCloudInstance() == null) {
        return;
      }
      int volume = getTRTCCloudInstance().getAudioPlayoutVolume();
      AppLogToBtnClick($"PlayVolume={volume}");
    }

    public void enableMixExternalAudioFrameTrue() {
      getTRTCCloudInstance()?.enableMixExternalAudioFrame(true, true);
      AppLogToBtnClick($"enableMixExternalAudioFrame true - true");
    }

    public void enableMixExternalAudioFrameFalse() {
      getTRTCCloudInstance()?.enableMixExternalAudioFrame(false, false);
      AppLogToBtnClick($"enableMixExternalAudioFrame false - false");
    }

    public void enableAudioVolumeEvaluationClick100() {
      getTRTCCloudInstance()?.enableAudioVolumeEvaluation(100);
      AppLogToBtnClick($"enableAudioVolumeEvaluation 100 MS");
    }

    public void enableAudioVolumeEvaluationClick0() {
      getTRTCCloudInstance()?.enableAudioVolumeEvaluation(0);
      AppLogToBtnClick($"enableAudioVolumeEvaluation 0");
    }

    public void startAudioRecordingClick() {
      TRTCLocalRecordingParams localRecordingParams = new TRTCLocalRecordingParams();
      localRecordingParams.filePath = Application.persistentDataPath + "/audio.aac";

      localRecordingParams.recordType = TRTCLocalRecordType.TRTCLocalRecordType_Audio;
      getTRTCCloudInstance()?.startLocalRecording(ref localRecordingParams);

      AppLogToBtnClick($"audioRecording");
    }

    public void stopAudioRecordingClick() {
      getTRTCCloudInstance()?.stopLocalRecording();
      AppLogToBtnClick($"stopAudioRecording");
    }

    public void setCapturedAudioFrameCallbackFormatClick() {
      TRTCAudioFrameCallbackFormat audioFormat = new TRTCAudioFrameCallbackFormat();
      audioFormat.sampleRate = getAudioSampleRate();
      audioFormat.channel = getAudioChannel();
      audioFormat.samplesPerCall = 20 * getAudioSampleRate() / 1000;
      audioFormat.mode = getAudioDataOperationmode();
      if(audioFormat.mode == TRTCAudioFrameOperationMode.TRTCAudioFrameOperationModeReadWrite) {
        bModifyCapturedAudioFrame = true;
      } else {
        bModifyCapturedAudioFrame = false;
      }
      
      getTRTCCloudInstance()?.setCapturedAudioFrameCallbackFormat(audioFormat);
      AppLogToBtnClick($"setCapturedAudioFrameCallbackFormat");
    }

    public void setLocalProcessedAudioFrameCallbackFormatClick() {
      TRTCAudioFrameCallbackFormat audioFormat = new TRTCAudioFrameCallbackFormat();
      audioFormat.sampleRate = getAudioSampleRate();
      audioFormat.channel = getAudioChannel();
      audioFormat.samplesPerCall = 20 * getAudioSampleRate() / 1000;
      audioFormat.mode = getAudioDataOperationmode();
       audioFormat.mode = getAudioDataOperationmode();
      if(audioFormat.mode == TRTCAudioFrameOperationMode.TRTCAudioFrameOperationModeReadWrite) {
        bModifylocalProcessedAudioFrame = true;
      } else {
        bModifylocalProcessedAudioFrame = false;
      }
      getTRTCCloudInstance()?.setLocalProcessedAudioFrameCallbackFormat(audioFormat);
      AppLogToBtnClick($"setLocalProcessedAudioFrameCallbackFormat");
    }

    public void setMixedPlayAudioFrameCallbackFormatClick() {
      TRTCAudioFrameCallbackFormat audioFormat = new TRTCAudioFrameCallbackFormat();
      audioFormat.sampleRate = getAudioSampleRate();
      audioFormat.channel = getAudioChannel();
      audioFormat.samplesPerCall = 20 * getAudioSampleRate() / 1000;
      audioFormat.mode = getAudioDataOperationmode();
       audioFormat.mode = getAudioDataOperationmode();
      if(audioFormat.mode == TRTCAudioFrameOperationMode.TRTCAudioFrameOperationModeReadWrite) {
        bModifyMixedPlayAudioFrame = true;
      } else {
        bModifyMixedPlayAudioFrame = false;
      }
      getTRTCCloudInstance()?.setMixedPlayAudioFrameCallbackFormat(audioFormat);
      AppLogToBtnClick($"setMixedPlayAudioFrameCallbackFormat");
    }

    public void setAudioFrameCallbackClick() {
      AppLogToBtnClick($"setAudioFrameCallbackClick");
      getTRTCCloudInstance()?.setAudioFrameCallback(this);
    }

    public void openSetRemoteUserAudioFrameCallbackFormatClick () {
      AppLogToBtnClick($"openSetRemoteUserAudioFrameCallbackFormatClick");
      bModifyRemoteUserAudioFrame = true;
      var data = new JsonData { ["api"] = "setRemoteUserAudioFrameCallbackFormat" };
      var param = new JsonData {
        ["mode"] = 0,
      };
      data["params"] = param;
      var api = data.ToJson();
      getTRTCCloudInstance()?.callExperimentalAPI(api);
    }

    public void closeSetRemoteUserAudioFrameCallbackFormatClick () {
      AppLogToBtnClick($"closeSetRemoteUserAudioFrameCallbackFormatClick");
      bModifyRemoteUserAudioFrame = false;
      var data = new JsonData { ["api"] = "setRemoteUserAudioFrameCallbackFormat" };
      var param = new JsonData {
        ["mode"] = 1,
      };
      data["params"] = param;
      var api = data.ToJson();
      getTRTCCloudInstance()?.callExperimentalAPI(api);
    }

    public void setVoiceReverbTypeClick() {
      getAudioEffectManager()?.setVoiceReverbType(TXVoiceReverbType.TXVoiceReverbType_6);
      AppLogToBtnClick($"setVoiceReverbType 6");
    }

    public void setVoiceReverbTypeClickDc() {
      getAudioEffectManager()?.setVoiceReverbType(TXVoiceReverbType.TXVoiceReverbType_4);
      AppLogToBtnClick($"setVoiceReverbType 4");
    }

    public void setVoiceReverbTypeClickClose() {
      getAudioEffectManager()?.setVoiceReverbType(TXVoiceReverbType.TXVoiceReverbType_0);
      AppLogToBtnClick($"setVoiceReverbType 0");
    }

    public void startPlayShortMusicClick() {
      getAudioEffectManager()?.setMusicObserver(11, new MusicPlayObserver(this, mainSyncContext));
      var musicParam =
          new AudioMusicParam { id = 11, publish = true,
                                path = Application.persistentDataPath + "/" + "click.mp3" };
      getAudioEffectManager()?.startPlayMusic(musicParam);
      AppLogToBtnClick($"startPlayMusic click.mp3");
    }

    public void startPlayMusicClick() {
      getAudioEffectManager()?.setMusicObserver(13, new MusicPlayObserver(this, mainSyncContext));
      var musicParam = new AudioMusicParam {
        id = 13,
        publish = true,
        loopCount = 20,
        startTimeMS = 10,
        endTimeMS = 300000,
        path = musicPath
      };
      getAudioEffectManager()?.startPlayMusic(musicParam);
      AppLogToBtnClick($"startPlayMusic {musicPath}");
    }

    public void stopPlayMusicClick() {
      getAudioEffectManager()?.stopPlayMusic(13);
      AppLogToBtnClick($"stopPlayMusic");
    }

    public void pausePlayMusicClcik() {
      getAudioEffectManager()?.pausePlayMusic(13);
      AppLogToBtnClick($"pausePlayMusic");
    }

    public void resumePlayMusicClick() {
      getAudioEffectManager()?.resumePlayMusic(13);
      AppLogToBtnClick($"resumePlayMusic");
    }

    public void setMusicPublishVolumeClick0() {
      getAudioEffectManager()?.setMusicPublishVolume(13, 0);
      AppLogToBtnClick($"setMusicPublishVolume = 0");
    }

    public void setMusicPublishVolumeClick100() {
      getAudioEffectManager()?.setMusicPublishVolume(13, 100);
      AppLogToBtnClick($"setMusicPublishVolume = 100");
    }

    public void setMusicPlayoutVolumeClick() {
      getAudioEffectManager()?.setMusicPlayoutVolume(13, 88);
      AppLogToBtnClick($"setMusicPlayoutVolume = 88");
    }

    public void setMusicPlayoutVolumeClick0() {
      getAudioEffectManager()?.setMusicPlayoutVolume(13, 0);
      AppLogToBtnClick($"setMusicPlayoutVolume = 0");
    }

    public void setMusicPlayoutVolumeClick100() {
      getAudioEffectManager()?.setMusicPlayoutVolume(13, 100);
      AppLogToBtnClick($"setMusicPlayoutVolume = 100");
    }

    public void setAllMusicVolumeClick0() {
      getAudioEffectManager()?.setAllMusicVolume(0);
      AppLogToBtnClick($"setAllMusicVolume = 0");
    }

    public void setAllMusicVolumeClick100() {
      getAudioEffectManager()?.setAllMusicVolume(100);
      AppLogToBtnClick($"setAllMusicVolume = 100");
    }

    public void setMusicPitchClick() {
      getAudioEffectManager()?.setMusicPitch(13, 1);
      AppLogToBtnClick($"setMusicPitch = 1");
    }

    public void setMusicPitchClickFu() {
      getAudioEffectManager()?.setMusicPitch(13, -1);
      AppLogToBtnClick($"setMusicPitch = -1");
    }

    public void setMusicSpeedRateClick1() {
      getAudioEffectManager()?.setMusicSpeedRate(13, 0.5);
      AppLogToBtnClick($"setMusicSpeedRate = 0.5");
    }

    public void setMusicSpeedRateClick2() {
      getAudioEffectManager()?.setMusicSpeedRate(13, 1);
      AppLogToBtnClick($"setMusicSpeedRate = 1");
    }

    public void getMusicCurrentPosInMSClick() {
      if (getAudioEffectManager() == null) {
        return;
      }
      int result = getAudioEffectManager().getMusicCurrentPosInMS(13);
      AppLogToBtnClick($"getMusicCurrentPosInMS = {result}");
    }

    public void seekMusicToPosInMSClick() {
      getAudioEffectManager()?.seekMusicToPosInMS(13, 500);
      AppLogToBtnClick($"seekMusicToPosInMS = 500");
    }

    public void getMusicDurationInMSClick() {
      if (getAudioEffectManager() == null) {
        return;
      }
      String path =
          "https://imgcache.qq.com/operation/dianshi/other/daoxiang.72c46ee085f15dc72603b0ba154409879cbeb15e.mp3";
      int result = getAudioEffectManager().getMusicDurationInMS(path);
      AppLogToBtnClick($"getMusicDurationInMS = {result}");
    }

    public void setMusicScratchSpeedRateClickB6() {
      getAudioEffectManager()?.setMusicScratchSpeedRate(13, -6.0f);
      AppLogToBtnClick($"setMusicScratchSpeedRate = -6.0");
    }

    public void setMusicScratchSpeedRateClickA1() {
      getAudioEffectManager()?.setMusicScratchSpeedRate(13, 1.0f);
      AppLogToBtnClick($"setMusicScratchSpeedRate = 1.0");
    }

    public void setMusicScratchSpeedRateClickA6() {
      getAudioEffectManager()?.setMusicScratchSpeedRate(13, +6.0f);
      AppLogToBtnClick($"setMusicScratchSpeedRate = 6.0");
    }

    public void setPreloadMusicClick() {
      lblBtnClickLog.text += Environment.NewLine + "setPreloadObserver(this)";
      getAudioEffectManager()?.setPreloadObserver(this);
    }

    public void setPreloadMusicClickNull() {
      lblBtnClickLog.text += Environment.NewLine + "setPreloadObserver(null)";
      getAudioEffectManager()?.setPreloadObserver(null);
    }

    public void preloadMusicClick() {
      lblBtnClickLog.text += Environment.NewLine + "preloadMusic";

      var musicParam = new AudioMusicParam {
        id = 13,
        publish = true,
        loopCount = 20,
        startTimeMS = 10,
        endTimeMS = 30000,
        path =
            "https://imgcache.qq.com/operation/dianshi/other/daoxiang.72c46ee085f15dc72603b0ba154409879cbeb15e.mp3"
      };
      getAudioEffectManager()?.preloadMusic(musicParam);
    }

    public void getMusicTrackCountClick() {
      if (getAudioEffectManager() == null) {
        return;
      }
      int result = getAudioEffectManager().getMusicTrackCount(13);
      AppLogToBtnClick($"getMusicTrackCountClick = {result}");
    }

    public void setMusicTrackClick() {
      getAudioEffectManager()?.setMusicTrack(13, 0);
      AppLogToBtnClick($"setMusicTrackClick trackIndex: 0");
    }

    public void setVoiceCaptureVolumeClick100() {
      getAudioEffectManager()?.setVoiceCaptureVolume(100);
      AppLogToBtnClick($"setVoiceCaptureVolume 100");
    }

    public void setVoiceCaptureVolumeClick0() {
      getAudioEffectManager()?.setVoiceCaptureVolume(0);
      AppLogToBtnClick($"setVoiceCaptureVolume 0");
    }

    public void setVoicePitchClick1() {
      getAudioEffectManager()?.setVoicePitch(1.0);
      AppLogToBtnClick($"setVoicePitch 1.0");
    }

    public void setVoicePitchClick0() {
      getAudioEffectManager()?.setVoicePitch(0.0);
      AppLogToBtnClick($"setVoicePitch 0.0");
    }

    public void playBackGroundMusicClick() {
      if (audio && !audio.isPlaying) {
        audio.Play();
      }

      AppLogToBtnClick($"playBackGroundMusic");
    }

    public void stopBackGroundMusicClick() {
      if (audio && audio.isPlaying) {
        audio.Stop();
      }

      AppLogToBtnClick($"stopBackGroundMusic");
    }

    // 设备相关接口函数
    public void isFrontCameraClick() {
      if (getDeviceManager() == null) {
        return;
      }
      bool isFront = getDeviceManager().isFrontCamera();
      AppLogToBtnClick($"isFrontCamera = {isFront}");
    }

    public void switchCameraClick() {
      getDeviceManager()?.switchCamera(false);
      AppLogToBtnClick($"switchCamera false");
    }

    public void switchCameraTrueClick() {
      getDeviceManager()?.switchCamera(true);
      AppLogToBtnClick($"switchCamera true");
    }

    public void getCameraZoomMaxRatioClick() {
      if (getDeviceManager() == null) {
        return;
      }
      double ratio = getDeviceManager().getCameraZoomMaxRatio();
      AppLogToBtnClick($"getCameraZoomMaxRatio {ratio}");
    }

    public void setCameraZoomRatioClick() {
      getDeviceManager()?.setCameraZoomRatio(3.6);
      AppLogToBtnClick($"setCameraZoomRatio = 3.6");
    }

    public void setCameraZoomRatio9Click() {
      getDeviceManager()?.setCameraZoomRatio(9);
      AppLogToBtnClick($"setCameraZoomRatio = 9");
    }

    public void isAutoFocusEnabledClick() {
      if (getDeviceManager() == null) {
        return;
      }
      bool isAutoFocusEnabled = getDeviceManager().isAutoFocusEnabled();
      AppLogToBtnClick($"isAutoFocusEnabled = {isAutoFocusEnabled}");
    }

    public void enableCameraAutoFocusClick() {
      if (getDeviceManager() == null) {
        return;
      }
      int AutoFocus = getDeviceManager().enableCameraAutoFocus(true);
      AppLogToBtnClick($"AutoFocus true = {AutoFocus}");
    }

    public void enableCameraAutoFocusFalseClick() {
      if (getDeviceManager() == null) {
        return;
      }
      int AutoFocus = getDeviceManager().enableCameraAutoFocus(false);
      AppLogToBtnClick($"AutoFocus false = {AutoFocus}");
    }

    public void setCameraFocusPositionClick() {
      if (getDeviceManager() == null) {
        return;
      }
      int FocusPosition = getDeviceManager().setCameraFocusPosition(10, 10);
      AppLogToBtnClick($"FocusPosition 10, 10 = {FocusPosition}");
    }

    public void setCameraFocusPositionClick100() {
      if (getDeviceManager() == null) {
        return;
      }
      int FocusPosition = getDeviceManager().setCameraFocusPosition(100, 100);
      AppLogToBtnClick($"setCameraFocusPosition 100, 100 = {FocusPosition}");
    }

    public void enableCameraTorchClick() {
      if (getDeviceManager() == null) {
        return;
      }
      int result = getDeviceManager().enableCameraTorch(true);
      AppLogToBtnClick($"enableCameraTorch true = {result}");
    }

    public void enableCameraTorchClickFalse() {
      if (getDeviceManager() == null) {
        return;
      }
      int result = getDeviceManager().enableCameraTorch(false);
      AppLogToBtnClick($"enableCameraTorch false = {result}");
    }

    public void setSystemVolumeTypeMedia() {
      if (getDeviceManager() == null) {
        return;
      }
      int result =
          getDeviceManager().setSystemVolumeType(TXSystemVolumeType.TXSystemVolumeTypeMedia);
      AppLogToBtnClick($"setSystemVolumeType TXSystemVolumeTypeMedia = {result}");
    }

    public void setSystemVolumeTypeVOIP() {
      if (getDeviceManager() == null) {
        return;
      }
      int result =
          getDeviceManager().setSystemVolumeType(TXSystemVolumeType.TXSystemVolumeTypeVOIP);
      AppLogToBtnClick($"setSystemVolumeType TXSystemVolumeTypeVOIP = {result}");
    }

    public void setSystemVolumeTypeAuto() {
      if (getDeviceManager() == null) {
        return;
      }
      int result =
          getDeviceManager().setSystemVolumeType(TXSystemVolumeType.TXSystemVolumeTypeAuto);
      AppLogToBtnClick($"setSystemVolumeType TXSystemVolumeTypeAuto = {result}");
    }

    public void setAudioRouteSpeakerphone() {
      if (getDeviceManager() == null) {
        return;
      }
      int result = getDeviceManager().setAudioRoute(TXAudioRoute.TXAudioRouteSpeakerphone);
      AppLogToBtnClick($"setAudioRoute TXAudioRouteSpeakerphone = {result}");
    }

    public void setAudioRouteEarpiece() {
      if (getDeviceManager() == null) {
        return;
      }
      int result = getDeviceManager().setAudioRoute(TXAudioRoute.TXAudioRouteEarpiece);
      AppLogToBtnClick($"setAudioRoute TXAudioRouteEarpiece = {result}");
    }

    public void getDevicesListTypeMicClick() {
      if (getDeviceManager() == null) {
        return;
      }
      TXDeviceInfo[] deviceinfo =
          getDeviceManager().getDevicesList(TXMediaDeviceType.TXMediaDeviceTypeMic);
      if (deviceinfo.Length == 0) {
        AppLogToBtnClick($"getDevicesList TypeMic is null");
        return;
      }

      for (int i = 0; i < deviceinfo.Length; i++) {
        AppLogToBtnClick(
            $"getDevicesList TypeMic seq:{i}, devicePID: {deviceinfo[i].devicePID}, deviceName: {deviceinfo[i].deviceName}, deviceProperties: {deviceinfo[i].deviceProperties}");
      }
    }

    public void getDevicesListTypeSpeakerClick() {
      if (getDeviceManager() == null) {
        return;
      }
      TXDeviceInfo[] deviceinfo =
          getDeviceManager().getDevicesList(TXMediaDeviceType.TXMediaDeviceTypeSpeaker);
      if (deviceinfo.Length == 0) {
        AppLogToBtnClick($"getDevicesList TypeSpeaker is null");
        return;
      }

      for (int i = 0; i < deviceinfo.Length; i++) {
        AppLogToBtnClick(
            $"getDevicesList TypeSpeaker seq:{i}, devicePID: {deviceinfo[i].devicePID}, deviceName: {deviceinfo[i].deviceName}, deviceProperties: {deviceinfo[i].deviceProperties}");
      }
    }

    public void getDevicesListTypeCameraClick() {
      if (getDeviceManager() == null) {
        return;
      }
      TXDeviceInfo[] deviceinfo =
          getDeviceManager().getDevicesList(TXMediaDeviceType.TXMediaDeviceTypeCamera);
      if (deviceinfo.Length == 0) {
        AppLogToBtnClick($"getDevicesList TypeCamera is null");
        return;
      }

      for (int i = 0; i < deviceinfo.Length; i++) {
        AppLogToBtnClick(
            $"getDevicesList TypeCamera seq:{i}, devicePID: {deviceinfo[i].devicePID}, deviceName: {deviceinfo[i].deviceName}, deviceProperties: {deviceinfo[i].deviceProperties}");
      }
    }

    public void setCurrentDeviceTypeMicClick() {
      if (getDeviceManager() == null) {
        return;
      }
      TXDeviceInfo[] deviceinfo =
          getDeviceManager().getDevicesList(TXMediaDeviceType.TXMediaDeviceTypeMic);
      if (deviceinfo.Length == 0) {
        AppLogToBtnClick($"setCurrentDevice TXMediaDeviceTypeMic device is null");
        return;
      }

      for (int i = 0; i < deviceinfo.Length; i++) {
        getDeviceManager().setCurrentDevice(TXMediaDeviceType.TXMediaDeviceTypeMic,
                                            deviceinfo[i].devicePID);
        AppLogToBtnClick(
            $"setCurrentDevice TXMediaDeviceTypeMic devicePID: {deviceinfo[i].devicePID}");
        return;
      }
    }

    public void setCurrentDeviceTypeSpeakerClick() {
      if (getDeviceManager() == null) {
        return;
      }
      TXDeviceInfo[] deviceinfo =
          getDeviceManager().getDevicesList(TXMediaDeviceType.TXMediaDeviceTypeSpeaker);
      if (deviceinfo.Length == 0) {
        AppLogToBtnClick($"setCurrentDevice TXMediaDeviceTypeSpeaker device is null");
        return;
      }

      for (int i = 0; i < deviceinfo.Length; i++) {
        getDeviceManager().setCurrentDevice(TXMediaDeviceType.TXMediaDeviceTypeSpeaker,
                                            deviceinfo[i].devicePID);
        AppLogToBtnClick(
            $"setCurrentDevice TXMediaDeviceTypeSpeaker devicePID: {deviceinfo[i].devicePID}");
        return;
      }
    }

    public void setCurrentDeviceTypeCameraClick() {
      if (getDeviceManager() == null) {
        return;
      }
      TXDeviceInfo[] deviceinfo =
          getDeviceManager().getDevicesList(TXMediaDeviceType.TXMediaDeviceTypeCamera);
      if (deviceinfo.Length == 0) {
        AppLogToBtnClick($"setCurrentDevice TXMediaDeviceTypeCamera device is null");
        return;
      }

      for (int i = 0; i < deviceinfo.Length; i++) {
        getDeviceManager().setCurrentDevice(TXMediaDeviceType.TXMediaDeviceTypeCamera,
                                            deviceinfo[i].devicePID);
        AppLogToBtnClick(
            $"setCurrentDevice TXMediaDeviceTypeCamera devicePID: {deviceinfo[i].devicePID}");
        return;
      }
    }

    public void getCurrentDeviceTypeMicClick() {
      if (getDeviceManager() == null) {
        return;
      }
      TXDeviceInfo deviceinfo =
          getDeviceManager().getCurrentDevice(TXMediaDeviceType.TXMediaDeviceTypeMic);

      AppLogToBtnClick(
          $"getCurrentDevice TypeMic devicePID: {deviceinfo.devicePID}, deviceName: {deviceinfo.deviceName}, deviceProperties: {deviceinfo.deviceProperties}");
    }

    public void getCurrentDeviceTypeSpeakerClick() {
      TXDeviceInfo deviceinfo =
          getDeviceManager().getCurrentDevice(TXMediaDeviceType.TXMediaDeviceTypeSpeaker);

      AppLogToBtnClick(
          $"getCurrentDevice TypeSpeaker devicePID: {deviceinfo.devicePID}, deviceName: {deviceinfo.deviceName}, deviceProperties: {deviceinfo.deviceProperties}");
    }

    public void getCurrentDeviceTypeCameraClick() {
      TXDeviceInfo deviceinfo =
          getDeviceManager().getCurrentDevice(TXMediaDeviceType.TXMediaDeviceTypeCamera);

      AppLogToBtnClick(
          $"getCurrentDevice TypeCamera devicePID: {deviceinfo.devicePID}, deviceName: {deviceinfo.deviceName}, deviceProperties: {deviceinfo.deviceProperties}");
    }

    // 视频相关接口函数
    public void startLocalPreviewClick() {
      getTRTCCloudInstance()?.startLocalPreview(false, null);
      AppLogToBtnClick($"startLocalPreview false");
    }

    public void stopLocalPreviewClick() {
      getTRTCCloudInstance()?.stopLocalPreview();
      AppLogToBtnClick($"stopLocalPreview");
    }

    public void setBeautyStyleClick9() {
      getTRTCCloudInstance()?.setBeautyStyle(TRTCBeautyStyle.TRTCBeautyStyleSmooth, 9, 9, 9);
      AppLogToBtnClick($"setBeautyStyle 9-9-9");
    }

    public void setBeautyStyleClick0() {
      getTRTCCloudInstance()?.setBeautyStyle(TRTCBeautyStyle.TRTCBeautyStyleSmooth, 0, 0, 0);
      AppLogToBtnClick($"setBeautyStyle 0-0-0");
    }

    public void setWaterMarkClick() {
      string mTestPath = Application.streamingAssetsPath + "/watermark_img.png";
      getTRTCCloudInstance()?.setWaterMark(TRTCVideoStreamType.TRTCVideoStreamTypeBig, mTestPath,
                                           TRTCWaterMarkSrcType.TRTCWaterMarkSrcTypeFile, 1000,
                                           1000, 0, 0, 0.5f);
      AppLogToBtnClick($"setWaterMark");
    }

    public void setVideoEncoderMirrorClick() {
      getTRTCCloudInstance()?.setVideoEncoderMirror(true);
      AppLogToBtnClick($"setVideoEncoderMirror true");
    }

    public void setVideoEncoderMirrorClickFalse() {
      getTRTCCloudInstance()?.setVideoEncoderMirror(false);
      AppLogToBtnClick($"setVideoEncoderMirror false");
    }

    //  曲库相关接口函数测试
    public void setCopyrightedLicenseClick() {
      if(mTXCopyrightedMedia == null) {
        AppLogToBtnClick($"setCopyrightedLicense mTXCopyrightedMedia is null");
        return;
      }
      int ret = mTXCopyrightedMedia.setCopyrightedLicense(GenerateTestUserSig.COPYRIGHTMEDIAKEY, GenerateTestUserSig.COPYRIGHTMEDIALICENSEURL);
      AppLogToBtnClick($"setCopyrightedLicense ret = {ret}");
    }
    public void genMusicURIClick() {
       if(mTXCopyrightedMedia == null) {
        AppLogToBtnClick($"genMusicURIClick mTXCopyrightedMedia is null");
        return;
      }

      int len = 4096;
      IntPtr outData = Marshal.AllocHGlobal(len);
      for (int i = 0; i < len; i++) {
        Marshal.WriteByte(outData, i, 0);
      }

      bool ret = false;
      int bgmType = 0;
      if(!int.TryParse(inputBgmType.text, out bgmType) || bgmType < 0) {
        bgmType = 0;
      }

      Debug.Log($"genMusicURIClick bgmType = {bgmType}");
      ret = mTXCopyrightedMedia.genMusicURI(inputMusicID.text, bgmType, inputBitrate.text, outData,  len);
      string outDataResult = Marshal.PtrToStringAnsi(outData);

      StringBuilder musicUrlBuilder = new StringBuilder();
      musicUrlBuilder.Append(outDataResult);
      musicUrlBuilder.Append("&ptoken=");
      musicUrlBuilder.Append(inputParam.text);

      musicPath = musicUrlBuilder.ToString(); 
      AppLogToBtnClick($"genMusicURIClick ret={ret}");
      AppLogToBtnClick($"genMusicURI outDataResult={outDataResult}");
      
      Marshal.FreeHGlobal(outData);
    }

    public void setMusicPreloadCallbackClick() {
      if(mTXCopyrightedMedia == null) {
        AppLogToBtnClick($"setMusicPreloadCallbackClick mTXCopyrightedMedia is null");
        return;
      }
      mTXCopyrightedMedia.setMusicPreloadCallback(this);
      AppLogToBtnClick($"setMusicPreloadCallbackClick true");
    }

    public void preloadCopyrightedMediaMusicClick() {
      if(mTXCopyrightedMedia == null) {
        AppLogToBtnClick($"preloadCopyrightedMediaMusicClick mTXCopyrightedMedia is null");
        return;
      }
      int ret = mTXCopyrightedMedia.preloadMusic(inputMusicID.text, inputBitrate.text, inputParam.text);
      AppLogToBtnClick($"preloadCopyrightedMediaMusicClick ret = {ret}");
    }

    public void cancelPreloadMusicClick() {
      if(mTXCopyrightedMedia == null) {
        AppLogToBtnClick($"cancelPreloadMusicClick mTXCopyrightedMedia is null");
        return;
      }
      int ret = mTXCopyrightedMedia.cancelPreloadMusic(inputMusicID.text, inputBitrate.text);
      AppLogToBtnClick($"cancelPreloadMusicClick ret = {ret}");
    }

    public void isMusicPreloadClick() {
      if(mTXCopyrightedMedia == null) {
        AppLogToBtnClick($"isMusicPreloadClick mTXCopyrightedMedia is null");
        return;
      }
      bool ret = mTXCopyrightedMedia.isMusicPreload(inputMusicID.text, inputBitrate.text);
      AppLogToBtnClick($"isMusicPreloadClick ret = {ret}");
    }

    public void clearMusicCacheClick() {
      if(mTXCopyrightedMedia == null) {
        AppLogToBtnClick($"clearMusicCacheClick mTXCopyrightedMedia is null");
        return;
      }
      int ret = mTXCopyrightedMedia.clearMusicCache();
      musicPath = "https://imgcache.qq.com/operation/dianshi/other/daoxiang.72c46ee085f15dc72603b0ba154409879cbeb15e.mp3";
      AppLogToBtnClick($"clearMusicCacheClick ret = {ret}");
    }

    public void setMusicCacheMaxCountClick() {
      if(mTXCopyrightedMedia == null) {
        AppLogToBtnClick($"setMusicCacheMaxCountClick mTXCopyrightedMedia is null");
        return;
      }
      int ret = mTXCopyrightedMedia.setMusicCacheMaxCount(10);
      AppLogToBtnClick($"setMusicCacheMaxCountClick 10 ret = {ret}");
    }

    // 设备和网络测试
    public void startSpeedTestClick() {
      getTRTCCloudInstance()?.startSpeedTest(
          GenerateTestUserSig.SDKAPPID, DataManager.GetInstance().GetUserID(),
          GenerateTestUserSig.GetInstance().GenTestUserSig(DataManager.GetInstance().GetUserID()));
      AppLogToBtnClick($"startSpeedTest");
    }

    public void stopSpeedTestClick() {
      getTRTCCloudInstance()?.stopSpeedTest();
      AppLogToBtnClick($"stopSpeedTest");
    }

    // other
    public void getSDKVersionClick() {
      if (getTRTCCloudInstance() == null) {
        return;
      }
      string version = getTRTCCloudInstance().getSDKVersion();
      AppLogToBtnClick($"version= {version}");
    }

    public void clearLogClick() {
      logCountForCallback = 0;
      logStringForCallback = "";
      lblCallBackLog.text = logStringForCallback;

      logCountForBtnClick = 0;
      logStringForBtnClick = "";
      lblBtnClickLog.text = logStringForBtnClick;
    }

    public void enableSmallVideoStreamClick() {
      TRTCVideoEncParam smallVideoEncParam = new TRTCVideoEncParam() {
        videoResolution = TRTCVideoResolution.TRTCVideoResolution_240_180,
        resMode = TRTCVideoResolutionMode.TRTCVideoResolutionModeLandscape, videoFps = 15,
        videoBitrate = 400, minVideoBitrate = 200
      };
      getTRTCCloudInstance()?.enableSmallVideoStream(true, ref smallVideoEncParam);
      AppLogToBtnClick($"enableSmallVideoStream true");
    }

    public void disEnableSmallVideoStreamClick() {
      TRTCVideoEncParam smallVideoEncParam = new TRTCVideoEncParam() {
        videoResolution = TRTCVideoResolution.TRTCVideoResolution_240_180,
        resMode = TRTCVideoResolutionMode.TRTCVideoResolutionModeLandscape, videoFps = 15,
        videoBitrate = 400, minVideoBitrate = 200
      };
      getTRTCCloudInstance()?.enableSmallVideoStream(false, ref smallVideoEncParam);
      AppLogToBtnClick($"enableSmallVideoStream false");
    }

    public void setDefaultStreamRecvModeAutoClick() {
      getTRTCCloudInstance()?.setDefaultStreamRecvMode(true, true);
      AppLogToBtnClick($"setDefaultStreamRecvMode true");
    }

    public void setDefaultStreamRecvModeDisAutoClick() {
      getTRTCCloudInstance()?.setDefaultStreamRecvMode(false, false);
      AppLogToBtnClick($"setDefaultStreamRecvMode false");
    }

#endregion
  }
}