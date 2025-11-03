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
      innerMixingConfig.videoLayoutListSize = 0;
      innerMixingConfig.audioMixUserListSize = 0;
      innerMixingConfig.watermarkListSize = 0;

      if (config.videoLayoutList != null && config.videoLayoutList.Length > 0) {
        VideoLayout[] videoLayoutList = new VideoLayout[config.videoLayoutList.Length];
        for (int i = 0; i < config.videoLayoutList.Length; i++) {
          videoLayoutList[i].rect = config.videoLayoutList[i].rect;
          videoLayoutList[i].zOrder = config.videoLayoutList[i].zOrder;
          videoLayoutList[i].fillMode = config.videoLayoutList[i].fillMode;
          videoLayoutList[i].backgroundColor = config.videoLayoutList[i].backgroundColor;
          videoLayoutList[i].placeHolderImage = config.videoLayoutList[i].placeHolderImage;
          videoLayoutList[i].fixedVideoStreamType = config.videoLayoutList[i].fixedVideoStreamType;
          videoLayoutList[i].fixedVideoUser = Marshal.AllocHGlobal(Marshal.SizeOf(config.videoLayoutList[i].fixedVideoUser));
          Marshal.StructureToPtr(config.videoLayoutList[i].fixedVideoUser, videoLayoutList[i].fixedVideoUser, false);
        }

        innerMixingConfig.videoLayoutListSize = (UInt32)config.videoLayoutList.Length;
        innerMixingConfig.videoLayoutList = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(VideoLayout)) * (int)innerMixingConfig.videoLayoutListSize);
        for (int i = 0; i < innerMixingConfig.videoLayoutListSize; i++) {
          IntPtr ptr = new IntPtr(innerMixingConfig.videoLayoutList.ToInt64() + i * Marshal.SizeOf(typeof(VideoLayout)));
          Marshal.StructureToPtr(videoLayoutList[i], ptr, false);
        }
      }
      else {
        innerMixingConfig.videoLayoutList = IntPtr.Zero;
      }

      if (config.audioMixUserList != null && config.audioMixUserList.Length > 0) {
        innerMixingConfig.audioMixUserListSize = (UInt32)config.audioMixUserList.Length;
        innerMixingConfig.audioMixUserList = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(TRTCMixUser)) * (int)innerMixingConfig.audioMixUserListSize);
        for (int i = 0; i < innerMixingConfig.audioMixUserListSize; i++) {
          IntPtr ptr = new IntPtr(innerMixingConfig.audioMixUserList.ToInt64() + i * Marshal.SizeOf(typeof(TRTCMixUser)));
          Marshal.StructureToPtr(config.audioMixUserList[i], ptr, false);
        }
      } else {
        innerMixingConfig.audioMixUserList = IntPtr.Zero;
      }

      if (config.watermarkList != null && config.watermarkList.Length > 0) {
        innerMixingConfig.watermarkListSize = (UInt32)config.watermarkList.Length;
        innerMixingConfig.watermarkList = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(TRTCWaterMark)) * (int)innerMixingConfig.watermarkListSize);
        for (int i = 0; i < innerMixingConfig.watermarkListSize; i++) {
          IntPtr ptr = new IntPtr(innerMixingConfig.watermarkList.ToInt64() + i * Marshal.SizeOf(typeof(TRTCWaterMark)));
          Marshal.StructureToPtr(config.watermarkList[i], ptr, false);
        }
      } else {
        innerMixingConfig.watermarkList = IntPtr.Zero;
      }

      return innerMixingConfig;
    }

    public static void ReleaseStreamMixingConfig(StreamMixingConfig config) {
      for (int i = 0; i < config.videoLayoutListSize; i++) {
        IntPtr ptr = new IntPtr(config.videoLayoutList.ToInt64() + i * Marshal.SizeOf(typeof(VideoLayout)));
        VideoLayout layout = (VideoLayout)Marshal.PtrToStructure(ptr, typeof(VideoLayout));
        Marshal.FreeHGlobal(layout.fixedVideoUser);
        Marshal.DestroyStructure(ptr, typeof(VideoLayout));
      }
      Marshal.FreeHGlobal(config.videoLayoutList);

      for (int i = 0; i < config.audioMixUserListSize; i++) {
        IntPtr ptr = new IntPtr(config.audioMixUserList.ToInt64() + i * Marshal.SizeOf(typeof(TRTCMixUser)));
        Marshal.DestroyStructure(ptr, typeof(TRTCMixUser));
      }
      Marshal.FreeHGlobal(config.audioMixUserList);

      for (int i = 0; i < config.watermarkListSize; i++) {
        IntPtr ptr = new IntPtr(config.watermarkList.ToInt64() + i * Marshal.SizeOf(typeof(TRTCWaterMark)));
        Marshal.DestroyStructure(ptr, typeof(TRTCWaterMark));
      }
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
