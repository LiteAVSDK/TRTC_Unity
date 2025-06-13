// Copyright (c) 2023 Tencent. All rights reserved.
// Author: felixyyan

using System;
using System.Runtime.InteropServices;

namespace trtc {
  public interface ITRTCCloudCallback {
    // 1.1
    void onError(TXLiteAVError errCode, String errMsg, IntPtr arg);

    // 1.2
    void onWarning(TXLiteAVWarning warningCode, String warningMsg, IntPtr arg);

    // 2.1
    void onEnterRoom(int result);

    // 2.2
    void onExitRoom(int reason);

    // 2.3
    void onSwitchRole(TXLiteAVError errCode, String errMsg);

    // 2.4
    void onSwitchRoom(TXLiteAVError errCode, string errMsg);

    // 2.5
    void onConnectOtherRoom(string userId, TXLiteAVError errCode, string errMsg);

    // 2.6
    void onDisconnectOtherRoom(TXLiteAVError errCode, string errMsg);

    // 3.1
    void onRemoteUserEnterRoom(String userId);

    // 3.2
    void onRemoteUserLeaveRoom(String userId, int reason);

    // 3.3
    void onUserVideoAvailable(String userId, bool available);

    // 3.4
    void onUserSubStreamAvailable(String userId, bool available);

    // 3.5
    void onUserAudioAvailable(String userId, bool available);

    // 3.6
    void onFirstVideoFrame(String userId, TRTCVideoStreamType streamType, int width, int height);

    // 3.7
    void onFirstAudioFrame(String userId);

    // 3.8
    void onSendFirstLocalVideoFrame(TRTCVideoStreamType streamType);

    // 3.9
    void onSendFirstLocalAudioFrame();

    // 4.1
    void onNetworkQuality(TRTCQualityInfo localQuality,
                          TRTCQualityInfo[] remoteQuality,
                          UInt32 remoteQualityCount);

    // 4.2
    void onStatistics(TRTCStatistics statis);

    // 4.3
    void onSpeedTestResult(TRTCSpeedTestResult result);

    // 5.1
    void onConnectionLost();

    // 5.2
    void onTryToReconnect();

    // 5.3
    void onConnectionRecovery();

    // 6.1
    void onCameraDidReady();

    // 6.2
    void onMicDidReady();

    // 6.4
    void onUserVoiceVolume(TRTCVolumeInfo[] userVolumes,
                           UInt32 userVolumesCount,
                           UInt32 totalVolume);

    // 6.5
    void onDeviceChange(String deviceId, TRTCDeviceType type, TRTCDeviceState state);

    // 6.9
    void onTestMicVolume(int volume);

    // 6.10
    void onTestSpeakerVolume(int volume);

    // 6.6
    void onAudioDeviceCaptureVolumeChanged(int volume, bool muted);

    // 6.7
    void onAudioDevicePlayoutVolumeChanged(int volume, bool muted);

    // 7.1
    void onRecvCustomCmdMsg(String userId, int cmdID, int seq, byte[] message, int messageSize);

    // 7.2
    void onMissCustomCmdMsg(String userId, int cmdID, int errCode, int missed);

    // 7.3
    void onRecvSEIMsg(String userId, Byte[] message, UInt32 msgSize);

    // 8.1
    void onStartPublishing(int errCode, String errMsg);

    // 8.2
    void onStopPublishing(int errCode, String errMsg);

    // 8.5
    void onSetMixTranscodingConfig(int errCode, String errMsg);

    // 8.6
    void onStartPublishMediaStream(string taskID, int code, string message, string extraInfo);

    // 8.7
    void onUpdatePublishMediaStream(string taskID, int code, string message, string extraInfo);

    // 8.8
    void onStopPublishMediaStream(string taskID, int code, string message, string extraInfo);

    // 8.9
    void onCdnStreamStateChanged(string cdnURL,
                                 int status,
                                 int code,
                                 string message,
                                 string extraInfo);
    // 9.1
    void onScreenCaptureStarted();

    // 9.2
    void onScreenCapturePaused(int reason);

    // 9.3
    void onScreenCaptureResumed(int reason);

    // 9.4
    void onScreenCaptureStoped(int reason);
  }

  public interface ITRTCVideoFrameCallback {
    void onGLContextCreated();

    int onProcessVideoFrame(TRTCVideoFrame srcFrame, TRTCVideoFrame dstFrame);

    void onGLContextDestroy();
  }

  public interface ITRTCVideoRenderCallback {
    void onRenderVideoFrame(string userId, TRTCVideoStreamType streamType, TRTCVideoFrame frame);
  }

  public interface ITRTCAudioFrameCallback {
    void onCapturedRawAudioFrame(TRTCAudioFrame frame);

    void onLocalProcessedAudioFrame(TRTCAudioFrame frame);

    void onPlayAudioFrame(TRTCAudioFrame frame, string userId);

    void onMixedPlayAudioFrame(TRTCAudioFrame frame);
  }

  public interface ITRTCLogCallback {
    void onLog(string log, TRTCLogLevel level, string module);
  }
}