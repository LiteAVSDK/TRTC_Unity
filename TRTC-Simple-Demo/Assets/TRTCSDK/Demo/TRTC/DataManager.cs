
using System;
using System.Collections.Generic;
using System.Text;
using UnityEngine;
using trtc;

namespace TRTCCUnityDemo {
  public class DataManager {
    public string GetUserID() {
      var randomUserID = Convert.ToString(UnityEngine.Random.Range(10000000, 99999999));
      return PlayerPrefs.GetString("UserID", randomUserID);
    }
    public void SetUserID(string userID) { PlayerPrefs.SetString("UserID", userID); }
    public string GetRoomID() { return Convert.ToString(PlayerPrefs.GetString("RoomID", "8888")); }
    public void SetRoomID(string roomID) {
      PlayerPrefs.SetString("RoomID", Convert.ToString(roomID));
    }

    public int GetNetEnv() { return Convert.ToInt32(PlayerPrefs.GetInt("NetEnv", 0)); }

    public void SetNetEnv(int netEnv) { PlayerPrefs.SetInt("NetEnv", netEnv); }

    public struct VideoResBitrateTable {
      public int defaultBitrate;
      public int minBitrate;
      public int maxBitrate;

      public VideoResBitrateTable(int defaultBitrate, int minBitrate, int maxBitrate) {
        this.defaultBitrate = defaultBitrate;
        this.minBitrate = minBitrate;
        this.maxBitrate = maxBitrate;
      }
    }

    public struct TRTCRenderIndex {
      public int rotationIndex;
      public int fillModeIndex;
      public int mirrorTypeIndex;
      public int streamTypeIndex;

      public TRTCRenderIndex(int rotationIndex,
                             int fillModeIndex,
                             int mirrorTypeIndex,
                             int streamTypeIndex) {
        this.rotationIndex = rotationIndex;
        this.fillModeIndex = fillModeIndex;
        this.mirrorTypeIndex = mirrorTypeIndex;
        this.streamTypeIndex = streamTypeIndex;
      }
    }

    private static DataManager sharedInstance;
    private static readonly System.Object sLock = new System.Object();
    private int mLocalVideostreamTypeIndex = 0;
    private TRTCRenderIndex mTRTCRenderIndex = new TRTCRenderIndex(0, 0, 0, 0);
    private bool mEnableLocalVideoCustomProcess = false;
    public TRTCAppScene appScene { get; set; }

    public delegate void ChangeRoleHandler();
    public event ChangeRoleHandler DoRoleChange;
    private TRTCRoleType _roleType;
    // This field only applies to live broadcast mode
    public TRTCRoleType roleType {
      get { return _roleType; }
      set {
        _roleType = value;
        if (DoRoleChange != null) {
          DoRoleChange();
        }
      }
    }

    public delegate void ChangeVoiceChangerHandler();
    public event ChangeVoiceChangerHandler DoVoiceChange;
    private TXVoiceChangeType _voiceChangeType;
    public TXVoiceChangeType voiceChangeType {
      get { return _voiceChangeType; }
      set {
        _voiceChangeType = value;
        if (DoVoiceChange != null) {
          DoVoiceChange();
        }
      }
    }

    private TRTCAudioQuality _audioQuality = TRTCAudioQuality.TRTCAudioQualityDefault;
    public TRTCAudioQuality audioQuality {
      get { return _audioQuality; }
      set {
        _audioQuality = value;
      }
    }

    public delegate void ChangeEarMonitorVolumeHandler();
    public event ChangeEarMonitorVolumeHandler DoEarMonitorVolumeChange;
    private int _earMonitorVolume;
    public int earMonitorVolume {
      get { return _earMonitorVolume; }
      set {
        _earMonitorVolume = value;
        if (DoEarMonitorVolumeChange != null) {
          DoEarMonitorVolumeChange();
        }
      }
    }
    public delegate void ChangeVideoEncParamHandler();
    public event ChangeVideoEncParamHandler DoVideoEncParamChange;
    private TRTCVideoEncParam _videoEncParam;
    public TRTCVideoEncParam videoEncParam {
      get { return _videoEncParam; }
      set {
        _videoEncParam = value;
        if (DoVideoEncParamChange != null) {
          DoVideoEncParamChange();
        }
      }
    }

    public delegate void ChangeQosParamHandler();
    public event ChangeQosParamHandler DoQosParamChange;
    private TRTCNetworkQosParam _qosParams;
    public TRTCNetworkQosParam qosParams {
      get { return _qosParams; }
      set {
        _qosParams = value;
        if (DoQosParamChange != null) {
          DoQosParamChange();
        }
      }
    }
    private bool _enableAIDenoise = false;
    public bool enableAIDenoise {
      get { return _enableAIDenoise; }
      set {
        _enableAIDenoise = value;
      }
    }
    public bool captureVideo { get; set; }
    public bool muteLocalVideo { get; set; }
    public bool captureAudio { get; set; }
    public bool muteLocalAudio { get; set; }

    private Dictionary<int, VideoResBitrateTable> mVideoResBitrateDict =
        new Dictionary<int, VideoResBitrateTable>();

    private DataManager() {
      mVideoResBitrateDict.Add((int)TRTCVideoResolution.TRTCVideoResolution_120_120,
                               new VideoResBitrateTable(150, 40, 200));
      mVideoResBitrateDict.Add((int)TRTCVideoResolution.TRTCVideoResolution_160_160,
                               new VideoResBitrateTable(250, 40, 300));
      mVideoResBitrateDict.Add((int)TRTCVideoResolution.TRTCVideoResolution_270_270,
                               new VideoResBitrateTable(300, 100, 400));
      mVideoResBitrateDict.Add((int)TRTCVideoResolution.TRTCVideoResolution_480_480,
                               new VideoResBitrateTable(500, 200, 1000));
      mVideoResBitrateDict.Add((int)TRTCVideoResolution.TRTCVideoResolution_160_120,
                               new VideoResBitrateTable(150, 40, 200));
      mVideoResBitrateDict.Add((int)TRTCVideoResolution.TRTCVideoResolution_240_180,
                               new VideoResBitrateTable(200, 80, 300));
      mVideoResBitrateDict.Add((int)TRTCVideoResolution.TRTCVideoResolution_280_210,
                               new VideoResBitrateTable(200, 100, 300));
      mVideoResBitrateDict.Add((int)TRTCVideoResolution.TRTCVideoResolution_320_240,
                               new VideoResBitrateTable(400, 100, 400));
      mVideoResBitrateDict.Add((int)TRTCVideoResolution.TRTCVideoResolution_400_300,
                               new VideoResBitrateTable(400, 200, 800));
      mVideoResBitrateDict.Add((int)TRTCVideoResolution.TRTCVideoResolution_480_360,
                               new VideoResBitrateTable(500, 200, 800));
      mVideoResBitrateDict.Add((int)TRTCVideoResolution.TRTCVideoResolution_640_480,
                               new VideoResBitrateTable(700, 250, 1000));
      mVideoResBitrateDict.Add((int)TRTCVideoResolution.TRTCVideoResolution_960_720,
                               new VideoResBitrateTable(1000, 200, 1600));
      mVideoResBitrateDict.Add((int)TRTCVideoResolution.TRTCVideoResolution_320_180,
                               new VideoResBitrateTable(300, 80, 300));
      mVideoResBitrateDict.Add((int)TRTCVideoResolution.TRTCVideoResolution_480_270,
                               new VideoResBitrateTable(400, 200, 800));
      mVideoResBitrateDict.Add((int)TRTCVideoResolution.TRTCVideoResolution_640_360,
                               new VideoResBitrateTable(600, 200, 1000));
      mVideoResBitrateDict.Add((int)TRTCVideoResolution.TRTCVideoResolution_960_540,
                               new VideoResBitrateTable(900, 400, 1600));
      mVideoResBitrateDict.Add((int)TRTCVideoResolution.TRTCVideoResolution_1280_720,
                               new VideoResBitrateTable(1250, 500, 2000));
      mVideoResBitrateDict.Add((int)TRTCVideoResolution.TRTCVideoResolution_1920_1080,
                               new VideoResBitrateTable(2000, 1000, 3000));

      appScene = TRTCAppScene.TRTCAppSceneVideoCall;
      roleType = TRTCRoleType.TRTCRoleAnchor;

      voiceChangeType = TXVoiceChangeType.TXVoiceChangeType_0;
      earMonitorVolume = 100;
      videoEncParam = new TRTCVideoEncParam() {
        videoResolution = TRTCVideoResolution.TRTCVideoResolution_640_360,
        resMode = TRTCVideoResolutionMode.TRTCVideoResolutionModeLandscape, videoFps = 15,
        videoBitrate = 600, minVideoBitrate = 200
      };

      qosParams = new TRTCNetworkQosParam() {
        preference = TRTCVideoQosPreference.TRTCVideoQosPreferenceSmooth,
        // controlMode = TRTCQosControlMode.TRTCQosControlModeClient
      };

      ResetLocalAVFlag();
    }

    public static DataManager GetInstance() {
      if (sharedInstance == null) {
        lock (sLock) {
          sharedInstance = new DataManager();
        }
      }
      return sharedInstance;
    }

    public VideoResBitrateTable GetBitrateInfo(int resolution) {
      return mVideoResBitrateDict[resolution];
    }

    public void ResetLocalAVFlag() {
      captureVideo = false;
      muteLocalVideo = false;
      captureAudio = false;
      muteLocalAudio = false;
    }

    public void SetLocalVideostreamTypeIndex(int index) { mLocalVideostreamTypeIndex = index; }
    public int GetLocalVideostreamTypeIndex() { return mLocalVideostreamTypeIndex; }

    public void SetTRTCRenderIndex(TRTCRenderIndex RenderIndex) {
      mTRTCRenderIndex.rotationIndex = RenderIndex.rotationIndex;
      mTRTCRenderIndex.fillModeIndex = RenderIndex.fillModeIndex;
      mTRTCRenderIndex.mirrorTypeIndex = RenderIndex.mirrorTypeIndex;
      mTRTCRenderIndex.streamTypeIndex = RenderIndex.streamTypeIndex;
    }

    public TRTCRenderIndex GetTRTCRenderIndex() { return mTRTCRenderIndex; }

    public void SetEnableLocalVideoCustomProcess(bool value) {
      mEnableLocalVideoCustomProcess = value;
    }

    public bool GetBitrateInfoEnableLocalVideoCustomProcess() {
      return mEnableLocalVideoCustomProcess;
    }
  }
}