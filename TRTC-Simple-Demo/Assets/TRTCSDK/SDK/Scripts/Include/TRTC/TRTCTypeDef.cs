// Copyright (c) 2023 Tencent. All rights reserved.
// Author: felixyyan

using System;

namespace trtc {

  public struct RECT {
    public int left;
    public int top;
    public int right;
    public int bottom;
  }

  // 1.1
  public enum TRTCVideoResolution {
    TRTCVideoResolution_120_120 = 1,
    TRTCVideoResolution_160_160 = 3,
    TRTCVideoResolution_270_270 = 5,
    TRTCVideoResolution_480_480 = 7,
    TRTCVideoResolution_160_120 = 50,
    TRTCVideoResolution_240_180 = 52,
    TRTCVideoResolution_280_210 = 54,
    TRTCVideoResolution_320_240 = 56,
    TRTCVideoResolution_400_300 = 58,
    TRTCVideoResolution_480_360 = 60,
    TRTCVideoResolution_640_480 = 62,
    TRTCVideoResolution_960_720 = 64,
    TRTCVideoResolution_160_90 = 100,
    TRTCVideoResolution_256_144 = 102,
    TRTCVideoResolution_320_180 = 104,
    TRTCVideoResolution_480_270 = 106,
    TRTCVideoResolution_640_360 = 108,
    TRTCVideoResolution_960_540 = 110,
    TRTCVideoResolution_1280_720 = 112,
    TRTCVideoResolution_1920_1080 = 114,
  }

  // 1.2
  public enum TRTCVideoResolutionMode {
    TRTCVideoResolutionModeLandscape = 0,
    TRTCVideoResolutionModePortrait = 1,
  }

  // 1.3
  public enum TRTCVideoStreamType {
    TRTCVideoStreamTypeBig = 0,
    TRTCVideoStreamTypeSmall = 1,
    TRTCVideoStreamTypeSub = 2,
  }

  // 1.4
  public enum TRTCVideoFillMode {
    TRTCVideoFillMode_Fill = 0,
    TRTCVideoFillMode_Fit = 1,
  }

  // 1.5
  public enum TRTCVideoRotation {
    TRTCVideoRotation0 = 0,
    TRTCVideoRotation90 = 1,
    TRTCVideoRotation180 = 2,
    TRTCVideoRotation270 = 3,
  }

  // 1.6
  public enum TRTCBeautyStyle {
    TRTCBeautyStyleSmooth = 0,
    TRTCBeautyStyleNature = 1,
  }

  // 1.7
  public enum TRTCVideoPixelFormat {
    TRTCVideoPixelFormat_Unknown = 0,
    TRTCVideoPixelFormat_I420 = 1,
    TRTCVideoPixelFormat_Texture_2D = 2,
    TRTCVideoPixelFormat_BGRA32 = 3,
    TRTCVideoPixelFormat_RGBA32 = 5,
  }

  // 1.8
  public enum TRTCVideoBufferType {
    TRTCVideoBufferType_Unknown = 0,
    TRTCVideoBufferType_Buffer = 1,
    TRTCVideoBufferType_Texture = 3,
  }

  // 1.9
  public enum TRTCVideoMirrorType {
    TRTCVideoMirrorType_Auto = 0,
    TRTCVideoMirrorType_Enable = 1,
    TRTCVideoMirrorType_Disable = 2,
  }

  // 1.10
  public enum TRTCSnapshotSourceType {
    TRTCSnapshotSourceTypeStream = 0,
    TRTCSnapshotSourceTypeView = 1,
  }

  // 2.1
  public enum TRTCAppScene {
    TRTCAppSceneVideoCall = 0,
    TRTCAppSceneLIVE = 1,
    TRTCAppSceneAudioCall = 2,
    TRTCAppSceneVoiceChatRoom = 3,
  }

  // 2.2
  public enum TRTCRoleType {
    TRTCRoleAnchor = 20,
    TRTCRoleAudience = 21,
  }

  // 2.3
  [Obsolete]
  public enum TRTCQosControlMode {
    TRTCQosControlModeClient = 0,
    TRTCQosControlModeServer = 1,
  }

  // 2.4
  public enum TRTCVideoQosPreference {
    TRTCVideoQosPreferenceSmooth = 1,
    TRTCVideoQosPreferenceClear = 2,
  }

  // 2.5
  public enum TRTCQuality {
    TRTCQuality_Unknown = 0,
    TRTCQuality_Excellent = 1,
    TRTCQuality_Good = 2,
    TRTCQuality_Poor = 3,
    TRTCQuality_Bad = 4,
    TRTCQuality_Vbad = 5,
    TRTCQuality_Down = 6,
  }

  // 2.6
  public enum TRTCAVStatusType {
    TRTCAVStatusStopped = 0,
    TRTCAVStatusPlaying = 1,
    TRTCAVStatusLoading = 2,
  }

  // 2.7
  public enum TRTCAVStatusChangeReason {
    TRTCAVStatusChangeReasonInternal = 0,
    TRTCAVStatusChangeReasonBufferingBegin = 1,
    TRTCAVStatusChangeReasonBufferingEnd = 2,
    TRTCAVStatusChangeReasonLocalStarted = 3,
    TRTCAVStatusChangeReasonLocalStopped = 4,
    TRTCAVStatusChangeReasonRemoteStarted = 5,
    TRTCAVStatusChangeReasonRemoteStopped = 6,
  }

  // 3.2
  public enum TRTCAudioQuality {
    TRTCAudioQualitySpeech = 1,
    TRTCAudioQualityDefault = 2,
    TRTCAudioQualityMusic = 3,
  }

  // 3.7
  public enum TRTCAudioFrameFormat {
    TRTCAudioFrameFormatNone = 0,
    TRTCAudioFrameFormatPCM = 1,
  }

 // 3.9
  public enum TRTCAudioFrameOperationMode {
    TRTCAudioFrameOperationModeReadWrite = 0,
    TRTCAudioFrameOperationModeReadOnly = 1,
  }

  // 4.1
  public enum TRTCLogLevel {
    TRTCLogLevelVerbose = 0,
    TRTCLogLevelDebug = 1,
    TRTCLogLevelInfo = 2,
    TRTCLogLevelWarn = 3,
    TRTCLogLevelError = 4,
    TRTCLogLevelFatal = 5,
    TRTCLogLevelNone = 6,
  }

  // 4.3
  public enum TRTCScreenCaptureSourceType {
    TRTCScreenCaptureSourceTypeUnknown = -1,
    TRTCScreenCaptureSourceTypeWindow = 0,
    TRTCScreenCaptureSourceTypeScreen = 1,
    TRTCScreenCaptureSourceTypeCustom = 2,
  }

  // 4.4
  public enum TRTCTranscodingConfigMode {
    TRTCTranscodingConfigMode_Unknown = 0,
    TRTCTranscodingConfigMode_Manual = 1,
    TRTCTranscodingConfigMode_Template_PureAudio = 2,
    TRTCTranscodingConfigMode_Template_PresetLayout = 3,
    TRTCTranscodingConfigMode_Template_ScreenSharing = 4,
  }

  // 4.5
  public enum TRTCLocalRecordType {
    TRTCLocalRecordType_Audio = 0,
    TRTCLocalRecordType_Video = 1,
    TRTCLocalRecordType_Both = 2,
  }

  // 4.6
  public enum TRTCMixInputType {
    TRTCMixInputTypeUndefined = 0,
    TRTCMixInputTypeAudioVideo = 1,
    TRTCMixInputTypePureVideo = 2,
    TRTCMixInputTypePureAudio = 3,
    TRTCMixInputTypeWatermark = 4,
  }

  // todo fix-api
  // 4.7
  public enum TRTCDeviceType {
    TRTCDeviceTypeUnknow = -1,
    TRTCDeviceTypeMic = 0,
    TRTCDeviceTypeSpeaker = 1,
    TRTCDeviceTypeCamera = 2,
  }

  // 4.8
  public enum TRTCWaterMarkSrcType {
    TRTCWaterMarkSrcTypeFile = 0,
    TRTCWaterMarkSrcTypeBGRA32 = 1,
    TRTCWaterMarkSrcTypeRGBA32 = 2,
  }

  // 4.9
  public enum TRTCDeviceState {
    TRTCDeviceStateAdd = 0,
    TRTCDeviceStateRemove = 1,
    TRTCDeviceStateActive = 2,
  }

  // 4.11
  public enum TRTCAudioRecordingContent {
    TRTCAudioRecordingContentAll = 0,
    TRTCAudioRecordingContentLocal = 1,
    TRTCAudioRecordingContentRemote = 2,
  }

  // 4.12
  public enum TRTCPublishMode {
    TRTCPublishModeUnknown = 0,
    TRTCPublishBigStreamToCdn = 1,
    TRTCPublishSubStreamToCdn = 2,
    TRTCPublishMixStreamToCdn = 3,
    TRTCPublishMixStreamToRoom = 4,
  }

  // 4.13
  public enum TRTCEncryptionAlgorithm {
    /// AES GCM 128。
    TRTCEncryptionAlgorithmAes128Gcm = 0,
    /// AES GCM 256。
    TRTCEncryptionAlgorithmAes256Gcm = 1,
  }

  // 4.14
  public enum TRTCSpeedTestScene {
    TRTCSpeedTestScene_DelayTesting = 1,
    TRTCSpeedTestScene_DelayAndBandwidthTesting = 2,
    TRTCSpeedTestScene_OnlineChorusTesting = 3,
  }

  // 5.1
  public struct TRTCParams {
    public UInt32 sdkAppId;
    public String userId;
    public String userSig;
    public UInt32 roomId;
    public String strRoomId;
    public TRTCRoleType role;
    public String streamId;
    public String userDefineRecordId;
    public String privateMapKey;
    public String businessInfo;
  }

  // 5.2
  public struct TRTCVideoEncParam {
    public TRTCVideoResolution videoResolution;
    public TRTCVideoResolutionMode resMode;
    public UInt32 videoFps;
    public UInt32 videoBitrate;
    public UInt32 minVideoBitrate;
    public bool enableAdjustRes;
  }

  // 5.3
  public struct TRTCNetworkQosParam {
    public TRTCVideoQosPreference preference;
    public TRTCQosControlMode controlMode;
  }

  // 5.4
  public struct TRTCRenderParams {
    public TRTCVideoRotation rotation;
    public TRTCVideoFillMode fillMode;
    public TRTCVideoMirrorType mirrorType;
  }

  // 5.5
  [Serializable]
  public struct TRTCQualityInfo {
    public String userId;
    public TRTCQuality quality;
  }

  // 5.6
  [Serializable]
  public struct TRTCVolumeInfo {
    public String userId;
    public UInt32 volume;
    public Int32 vad;
    public float pitch;
    public float[] spectrumData;
  }

  // 5.7
  public struct TRTCSpeedTestParams {
    public int sdkAppId;
    public string userId;
    public string userSig;
    public int expectedUpBandwidth;
    public int expectedDownBandwidth;
    public TRTCSpeedTestScene scene;
  }

  // 5.8
  [Serializable]
  public struct TRTCSpeedTestResult {
    public bool success;
    public String errMsg;
    public String ip;
    public TRTCQuality quality;
    public float upLostRate;
    public float downLostRate;
    public int rtt;
    public int availableUpBandwidth;
    public int availableDownBandwidth;
    public int upJitter;
    public int downJitter;
  }

  // 5.10
  public struct TRTCVideoFrame {
    public TRTCVideoPixelFormat videoFormat;
    public TRTCVideoBufferType bufferType;
    public int textureId;
    public IntPtr data;
    public UInt32 length;
    public UInt32 width;
    public UInt32 height;
    public UInt64 timestamp;
    public TRTCVideoRotation rotation;
  }

  // 5.11
  public struct TRTCAudioFrame {
    public TRTCAudioFrameFormat audioFormat;
    public byte[] data;
    public UInt32 length;
    public UInt32 sampleRate;
    public UInt32 channel;
    public UInt64 timestamp;
    public byte[] extraData;
    public UInt32 extraDatalength;
  }

  // 5.12
  public struct TRTCMixUser {
    public string userId;
    public string roomId;
    public RECT rect;
    public int zOrder;
    public TRTCVideoStreamType streamType;
    public bool pureAudio;
    public TRTCMixInputType inputType;
    public UInt32 renderMode;
    public UInt32 soundLevel;
    public string image;
  }

  // 5.13
  public struct TRTCTranscodingConfig {
    public TRTCTranscodingConfigMode mode;
    public UInt32 appId;
    public UInt32 bizId;
    public UInt32 videoWidth;
    public UInt32 videoHeight;
    public UInt32 videoBitrate;
    public UInt32 videoFramerate;
    public UInt32 videoGOP;
    public UInt32 backgroundColor;
    public string backgroundImage;
    public UInt32 audioSampleRate;
    public UInt32 audioBitrate;
    public UInt32 audioChannels;
    public UInt32 audioCodec;
    public TRTCMixUser[] mixUsersArray;
    public UInt32 mixUsersArraySize;
    public string streamId;
    public string videoSeiParams;
  }

  // 5.14
  public struct TRTCPublishCDNParam {
    public UInt32 appId;
    public UInt32 bizId;
    public String url;
    public String streamId;
  }

  // 5.15
  public struct TRTCAudioRecordingParams {
    public String filePath;
    public TRTCAudioRecordingContent recordingContent;
    public int maxDurationPerFile;
  }

  // 5.16
  public struct TRTCLocalRecordingParams {
    public String filePath;
    public TRTCLocalRecordType recordType;
    public int interval;
    public int maxDurationPerFile;
  }

  // 5.18
  public struct TRTCSwitchRoomConfig {
    public int roomId;
    public string strRoomId;
    public string userSig;
    public string privateMapKey;
  }

  // 5.19
  public struct TRTCAudioFrameCallbackFormat {
    public int sampleRate;
    public int channel;
    public int samplesPerCall;
    public TRTCAudioFrameOperationMode mode;
  };

  // 5.20
  public struct TRTCImageBuffer {
    public byte[] buffer;
    public int length;
    public int width;
    public int height;
  }

  // 5.21
  public struct TRTCScreenCaptureSourceInfo {
    public TRTCScreenCaptureSourceType type;
    public IntPtr sourceId;
    public String sourceName;
    public TRTCImageBuffer thumbBGRA;
    public TRTCImageBuffer iconBGRA;
    public bool isMinimizeWindow;
    public bool isMainScreen;
    public int x;
    public int y;
    public uint width;
    public uint height;
  }

  // 5.23
  public class TRTCScreenCaptureProperty {
    public bool enableCaptureMouse = true;
    public bool enableHighLight = true;
    public bool enableHighPerformance = true;
    public int highLightColor;
    public int highLightWidth;
    public bool enableCaptureChildWindow;
  }

  // 5.25
  public struct TRTCUserParam {
    public string userId;
    public UInt32 intRoomId;
    public string strRoomId;
  }

  // 5.26
  public struct TRTCPublishCdnUrl {
    public string rtmpUrl;
    public bool isInternalLine;
  }

  // 5.27
  public struct TRTCPublishTarget {
    public TRTCPublishMode mode;
    public TRTCPublishCdnUrl[] cdnUrlList;
    public UInt32 cdnUrlListSize;
    public TRTCUserParam mixStreamIdentity;
  }

  // 5.28
  public struct TRTCVideoLayout {
    public RECT rect;
    public int zOrder;
    public TRTCVideoFillMode fillMode;
    public UInt32 backgroundColor;
    public string placeHolderImage;
    public IntPtr fixedVideoUser;
    public TRTCVideoStreamType fixedVideoStreamType;
  }

  // 5.29
  public struct TRTCWaterMark {
    public string watermarkUrl;
    public RECT rect;
    public int zOrder;
  }

  // 5.30
  public struct TRTCStreamEncoderParam {
    public UInt32 videoEncodedWidth;
    public UInt32 videoEncodedHeight;
    public UInt32 videoEncodedFps;
    public UInt32 videoEncodedGop;
    public UInt32 videoEncodedKbps;
    public UInt32 audioEncodedSampleRate;
    public UInt32 audioEncodedChannelNum;
    public UInt32 audioEncodedKbps;
    public UInt32 audioEncodedCodecType;
    public UInt32 videoEncodedCodecType;
    public string videoSeiParams;
  }

  // 5.31
  public struct TRTCStreamMixingConfig {
    public UInt32 backgroundColor;
    public string backgroundImage;
    public TRTCVideoLayout videoLayoutList;
    public UInt32 videoLayoutListSize;
    public TRTCUserParam audioMixUserList;
    public UInt32 audioMixUserListSize;
    public TRTCWaterMark watermarkList;
    public UInt32 watermarkListSize;
  }

  // 5.33
  public struct TRTCAudioVolumeEvaluateParams {
    public uint interval;
    public bool enableVadDetection;
    public bool enablePitchCalculation;
    public bool enableSpectrumCalculation;
  }
}