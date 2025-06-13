// Copyright (c) 2023 Tencent. All rights reserved.
// Author: felixyyan

using System;
using UnityEngine;

namespace trtc {
  public abstract class ITRTCCloud {
    public static string PLUGIN_VERSION = "12.4.0.17861_274";

    // 1.1
    public static ITRTCCloud getTRTCShareInstance() {
      return TRTCCloudImplement.getShareInstance();
    }

    // 1.2
    public static void destroyTRTCShareInstance() { TRTCCloudImplement.destroyShareInstance(); }

    // 1.3
    public abstract void addCallback(ITRTCCloudCallback callback);

    // 1.4
    public abstract void removeCallback(ITRTCCloudCallback callback);

    // 2.1
    public abstract void enterRoom(ref TRTCParams param, TRTCAppScene scene);

    // 2.2
    public abstract void exitRoom();

    public abstract void exitRoom(bool stopLocalVideo, bool stopLocalAudio);

    // 2.3
    public abstract void switchRole(TRTCRoleType role);

    // 2.5
    public abstract void switchRoom(TRTCSwitchRoomConfig config);

    // 2.6
    public abstract void connectOtherRoom(string jsonParams);

    // 2.7
    public abstract void disconnectOtherRoom();

    // 2.8
    public abstract void setDefaultStreamRecvMode(bool autoRecvAudio, bool autoRecvVideo);

    // 2.9
    public abstract ITRTCCloud createSubCloud();

    // 2.10
    public abstract void destroySubCloud(ITRTCCloud subCloud);

    // 3.1
    public abstract void startPublishing(string streamId, TRTCVideoStreamType streamType);

    // 3.2
    public abstract void stopPublishing();

    // 3.5
    public abstract void setMixTranscodingConfig(TRTCTranscodingConfig? config);

    // 3.6
    public abstract void startPublishMediaStream(ref TRTCPublishTarget target,
                                                 ref TRTCStreamEncoderParam param,
                                                 ref TRTCStreamMixingConfig config);

    // 3.7
    public abstract void updatePublishMediaStream(string taskId,
                                                  ref TRTCPublishTarget target,
                                                  ref TRTCStreamEncoderParam param,
                                                  ref TRTCStreamMixingConfig config);

    // 3.8
    public abstract void stopPublishMediaStream(string taskId);

    // 4.1
    public abstract void startLocalPreview(bool frontCamera, GameObject view);

    // 4.4
    public abstract void stopLocalPreview();

    // 4.5
    public abstract void muteLocalVideo(TRTCVideoStreamType streamType, bool mute);

    // 4.7
    public abstract void startRemoteView(string userId,
                                         TRTCVideoStreamType streamType,
                                         GameObject view);

    // 4.9
    public abstract void stopRemoteView(string userId, TRTCVideoStreamType streamType);

    // 4.10
    public abstract void stopAllRemoteView();

    // 4.13
    public abstract void setVideoEncoderParam(ref TRTCVideoEncParam param);

    // 4.14
    public abstract void setNetworkQosParam(ref TRTCNetworkQosParam param);

    // 4.15
    public abstract void setLocalRenderParams(TRTCRenderParams renderParams);

    // 4.16
    public abstract void setRemoteRenderParams(string userId,
                                               TRTCVideoStreamType streamType,
                                               ref TRTCRenderParams renderParams);

    // 4.17
    public abstract void setVideoEncoderRotation(TRTCVideoRotation rotation);

    // 4.18
    public abstract void setVideoEncoderMirror(bool mirror);

    // 4.20
    public abstract void enableSmallVideoStream(bool enable, ref TRTCVideoEncParam smallVideoParam);

    // 4.21
    public abstract void setRemoteVideoStreamType(string userId, TRTCVideoStreamType type);

    // 5.1
    public abstract void startLocalAudio(TRTCAudioQuality quality);

    // 5.2
    public abstract void stopLocalAudio();

    // 5.3
    public abstract void muteLocalAudio(bool mute);

    // 5.4
    public abstract void muteRemoteAudio(string userId, bool mute);

    // 5.5
    public abstract void muteAllRemoteAudio(bool mute);

    // 5.7
    public abstract void setRemoteAudioVolume(string userId, int volume);

    // 5.8
    public abstract void setAudioCaptureVolume(int volume);

    // 5.9
    public abstract int getAudioCaptureVolume();

    // 5.10
    public abstract void setAudioPlayoutVolume(int volume);

    // 5.11
    public abstract int getAudioPlayoutVolume();

    // 5.12
    public abstract void enableAudioVolumeEvaluation(bool enable,
                                                     TRTCAudioVolumeEvaluateParams evaluateParams);

    // 5.15
    public abstract void startLocalRecording(ref TRTCLocalRecordingParams localRecordingParams);

    // 5.16
    public abstract void stopLocalRecording();

    // 6.1
    public abstract ITXDeviceManager getDeviceManager();

    // 7.1
    public abstract void setBeautyStyle(TRTCBeautyStyle style,
                                        uint beauty,
                                        uint white,
                                        uint ruddiness);

    // 7.2
    public abstract void setWaterMark(TRTCVideoStreamType streamType,
                                      string srcData,
                                      TRTCWaterMarkSrcType srcType,
                                      uint nWidth,
                                      uint nHeight,
                                      float xOffset,
                                      float yOffset,
                                      float fWidthRatio,
                                      bool isVisibleOnLocalPreview = false);

    // 8.1
    public abstract ITXAudioEffectManager getAudioEffectManager();

    // 8.2
    public abstract void startSystemAudioLoopback(string deviceName);

    // 8.3
    public abstract void stopSystemAudioLoopback();

    // 9.1
    public abstract void startScreenCapture(GameObject view, TRTCVideoStreamType type, ref TRTCVideoEncParam param);

    // 9.2
    public abstract void stopScreenCapture();

    // 9.3
    public abstract void pauseScreenCapture();

    // 9.4
    public abstract void resumeScreenCapture();

    // 9.5
    public abstract TRTCScreenCaptureSourceInfo[] getScreenCaptureSources(int thumbnailWidth,
                                                                          int thumbnailHeight);

    // 9.6
    public abstract void selectScreenCaptureTarget(TRTCScreenCaptureSourceInfo source,
                                                   Rect captureRect,
                                                   TRTCScreenCaptureProperty property);

    // 9.7
    public abstract void setSubStreamEncoderParam(ref TRTCVideoEncParam param);

    // 10.1
    public abstract void enableCustomVideoCapture(TRTCVideoStreamType streamType, bool enable);

    // 10.2
    public abstract void sendCustomVideoData(TRTCVideoStreamType streamType, TRTCVideoFrame frame);

    // 10.3
    public abstract void enableCustomAudioCapture(bool enable);

    // 10.4
    public abstract void sendCustomAudioData(TRTCAudioFrame frame);

    // 10.5
    public abstract void enableMixExternalAudioFrame(bool enablePublish, bool enablePlayout);

    // 10.9.1
    public abstract int enableLocalVideoCustomProcess(bool enable,
                                                      TRTCVideoPixelFormat pixelFormat,
                                                      TRTCVideoBufferType bufferType);

    // 10.9.2
    public abstract void setLocalVideoCustomProcessCallback(ITRTCVideoFrameCallback callback);

    // 10.10
    public abstract int setLocalVideoRenderCallback(TRTCVideoStreamType streamType,
                                                    TRTCVideoPixelFormat pixelFormat,
                                                    TRTCVideoBufferType bufferType,
                                                    ITRTCVideoRenderCallback callback);
    // 10.11
    public abstract int setRemoteVideoRenderCallback(string userId,
                                                     TRTCVideoStreamType streamType,
                                                     TRTCVideoPixelFormat pixelFormat,
                                                     TRTCVideoBufferType bufferType,
                                                     ITRTCVideoRenderCallback callback);

    // 10.12
    public abstract int setAudioFrameCallback(ITRTCAudioFrameCallback callback);

    // 10.13
    public abstract int setCapturedAudioFrameCallbackFormat(TRTCAudioFrameCallbackFormat format);

    // 10.14
    public abstract int setLocalProcessedAudioFrameCallbackFormat(TRTCAudioFrameCallbackFormat format);
    
    // 10.15
    public abstract int setMixedPlayAudioFrameCallbackFormat(TRTCAudioFrameCallbackFormat format);

    // 11.1
    public abstract bool sendCustomCmdMsg(int cmdId,
                                          byte[] data,
                                          int dataSize,
                                          bool reliable,
                                          bool ordered);

    // 11.2
    public abstract bool sendSEIMsg(byte[] data, int dataSize, int repeatCount);

    // 12.1
    public abstract void startSpeedTest(TRTCSpeedTestParams testParams);

    // 12.2
    public abstract void stopSpeedTest();

    // 13.0
    public abstract string getScriptVersion();

    // 13.1
    public abstract string getSDKVersion();

    // 13.2
    public abstract void setLogLevel(TRTCLogLevel level);

    // 13.3
    public abstract void setConsoleEnabled(bool enabled);

    // 13.4
    public abstract void setLogCompressEnabled(bool enabled);

    // 13.5
    public abstract void setLogDirPath(string path);

    // 13.6
    public abstract void setLogCallback(ITRTCLogCallback callback);

    // 13.9
    public abstract void callExperimentalAPI(string jsonStr);

    // 4.5
    [Obsolete("use muteLocalVideo(TRTCVideoStreamType,bool)")]
    public abstract void muteLocalVideo(bool mute);

    // 5.12
    [Obsolete("use enableAudioVolumeEvaluation(bool,TRTCAudioVolumeEvaluateParams)")]
    public abstract void enableAudioVolumeEvaluation(uint interval);

    // 10.2
    [Obsolete("use sendCustomVideoData(TRTCVideoStreamType,TRTCVideoFrame)")]
    public abstract void sendCustomVideoData(TRTCVideoFrame frame);

    // 12.1
    [Obsolete("startSpeedTest(TRTCSpeedTestParams)")]
    public abstract void startSpeedTest(int sdkAppId, string userId, string userSig);
  }
}
