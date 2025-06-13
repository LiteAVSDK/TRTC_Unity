// Copyright (c) 2023 Tencent. All rights reserved.
// Author: felixyyan

using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using AOT;
using UnityEngine;

namespace trtc {
  [StructLayout(LayoutKind.Sequential)]
  public struct TRTCInnerMixUser {
    public string userId;

    public string roomId;

    public RECT rect;

    public int zOrder;

    public TRTCVideoStreamType streamType;

    public byte pureAudio;

    public TRTCMixInputType inputType;

    public UInt32 renderMode;

    public UInt32 soundLevel;

    public string image;
  }

  public class TRTCTypeConverter {
    public static TRTCInnerMixUser ConvertTRTCMixUser(TRTCMixUser user) {
      TRTCInnerMixUser innerMixUser = new TRTCInnerMixUser();
      innerMixUser.userId = user.userId;
      innerMixUser.roomId = user.roomId;
      innerMixUser.rect = user.rect;
      innerMixUser.zOrder = user.zOrder;
      innerMixUser.streamType = user.streamType;
      innerMixUser.pureAudio = (byte)(user.pureAudio ? 1 : 0);
      innerMixUser.inputType = user.inputType;
      innerMixUser.renderMode = user.renderMode;
      innerMixUser.soundLevel = user.soundLevel;
      innerMixUser.image = user.image;
      return innerMixUser;
    }

    public static StreamEncoderParam ConvertTRTCStreamEncoderParam(
        TRTCStreamEncoderParam encodeParam) {
      StreamEncoderParam innerEncodeParam = new StreamEncoderParam();
      innerEncodeParam.videoEncodedWidth = encodeParam.videoEncodedWidth;
      innerEncodeParam.videoEncodedHeight = encodeParam.videoEncodedHeight;
      innerEncodeParam.videoEncodedFps = encodeParam.videoEncodedFps;
      innerEncodeParam.videoEncodedGop = encodeParam.videoEncodedGop;
      innerEncodeParam.audioEncodedKbps = encodeParam.audioEncodedKbps;
      innerEncodeParam.audioEncodedSampleRate = encodeParam.audioEncodedSampleRate;
      innerEncodeParam.audioEncodedChannelNum = encodeParam.audioEncodedChannelNum;
      innerEncodeParam.audioEncodedKbps = encodeParam.audioEncodedKbps;
      innerEncodeParam.audioEncodedCodecType = encodeParam.audioEncodedCodecType;
      innerEncodeParam.videoEncodedCodecType = encodeParam.videoEncodedCodecType;
      innerEncodeParam.videoSeiParams = encodeParam.videoSeiParams;
      return innerEncodeParam;
    }

    public static StreamMixingConfig ConvertTRTCStreamMixingConfig(TRTCStreamMixingConfig config) {
      StreamMixingConfig innerMixingConfig = new StreamMixingConfig();
      innerMixingConfig.backgroundColor = config.backgroundColor;
      innerMixingConfig.backgroundImage = config.backgroundImage;
      innerMixingConfig.videoLayoutListSize = config.videoLayoutListSize;
      innerMixingConfig.videoLayoutList =
          Marshal.AllocHGlobal(Marshal.SizeOf(config.videoLayoutList));
      Marshal.StructureToPtr(config.videoLayoutList, innerMixingConfig.videoLayoutList, false);

      innerMixingConfig.audioMixUserListSize = config.audioMixUserListSize;
      innerMixingConfig.audioMixUserList =
          Marshal.AllocHGlobal(Marshal.SizeOf(config.audioMixUserList));
      Marshal.StructureToPtr(config.audioMixUserList, innerMixingConfig.audioMixUserList, false);

      innerMixingConfig.watermarkListSize = config.watermarkListSize;
      innerMixingConfig.watermarkList = Marshal.AllocHGlobal(Marshal.SizeOf(config.watermarkList));
      Marshal.StructureToPtr(config.watermarkList, innerMixingConfig.watermarkList, false);

      return innerMixingConfig;
    }

    public static void ReleaseStreamMixingConfig(StreamMixingConfig config) {
      Marshal.FreeHGlobal(config.videoLayoutList);
      Marshal.FreeHGlobal(config.audioMixUserList);
      Marshal.FreeHGlobal(config.watermarkList);
    }

    public static TranscodingConfig ConvertTRTCTranscodingConfig(TRTCTranscodingConfig config) {
      TranscodingConfig innerTranscodingConfig = new TranscodingConfig();
      innerTranscodingConfig.mode = config.mode;
      innerTranscodingConfig.appId = config.appId;
      innerTranscodingConfig.bizId = config.bizId;
      innerTranscodingConfig.videoWidth = config.videoWidth;
      innerTranscodingConfig.videoHeight = config.videoHeight;
      innerTranscodingConfig.videoBitrate = config.videoBitrate;
      innerTranscodingConfig.videoFramerate = config.videoFramerate;
      innerTranscodingConfig.videoGOP = config.videoGOP;
      innerTranscodingConfig.backgroundColor = config.backgroundColor;
      innerTranscodingConfig.backgroundImage = config.backgroundImage;
      innerTranscodingConfig.audioSampleRate = config.audioSampleRate;
      innerTranscodingConfig.audioBitrate = config.audioBitrate;
      innerTranscodingConfig.audioChannels = config.audioChannels;
      innerTranscodingConfig.audioCodec = config.audioCodec;
      innerTranscodingConfig.mixUsersArraySize = config.mixUsersArraySize;
      innerTranscodingConfig.streamId = config.streamId;
      innerTranscodingConfig.videoSeiParams = config.videoSeiParams;

      return innerTranscodingConfig;
    }
  }
}
