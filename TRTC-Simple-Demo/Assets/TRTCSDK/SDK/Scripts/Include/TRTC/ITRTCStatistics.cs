// Copyright (c) 2023 Tencent. All rights reserved.
// Author: felixyyan

using System;

namespace trtc {
  [Serializable]
  public struct TRTCLocalStatistics {
    public UInt32 width;
    public UInt32 height;
    public UInt32 frameRate;
    public UInt32 videoBitrate;
    public UInt32 audioSampleRate;
    public UInt32 audioBitrate;
    public TRTCVideoStreamType streamType;
    public UInt32 audioCaptureState;
  }

  [Serializable]
  public struct TRTCRemoteStatistics {
    public String userId;
    public UInt32 audioPacketLoss;
    public UInt32 videoPacketLoss;
    public UInt32 width;
    public UInt32 height;
    public UInt32 frameRate;
    public UInt32 videoBitrate;
    public UInt32 audioSampleRate;
    public UInt32 audioBitrate;
    public UInt32 jitterBufferDelay;
    public UInt32 point2PointDelay;
    public UInt32 audioTotalBlockTime;
    public UInt32 audioBlockRate;
    public UInt32 videoTotalBlockTime;
    public UInt32 videoBlockRate;
    public UInt32 finalLoss;
    public UInt32 remoteNetworkUplinkLoss;
    public UInt32 remoteNetworkRTT;
    public TRTCVideoStreamType streamType;
  }

  [Serializable]
  public struct TRTCStatistics {
    public UInt32 appCpu;
    public UInt32 systemCpu;
    public UInt32 systemMemoryInMB;
    public UInt32 systemMemoryUsageInMB;
    public UInt32 appMemoryUsageInMB;
    public UInt32 upLoss;
    public UInt32 downLoss;
    public UInt32 rtt;
    public UInt32 gatewayRtt;
    public UInt32 sentBytes;
    public UInt32 receivedBytes;
    public TRTCLocalStatistics[] localStatisticsArray;
    [Obsolete("Use localStatisticsArray to obtain the value of localStatisticsArraySize")]
    public UInt32 localStatisticsArraySize;
    public TRTCRemoteStatistics[] remoteStatisticsArray;
    [Obsolete("Use remoteStatisticsArray to obtain the value of remoteStatisticsArraySize")]
    public UInt32 remoteStatisticsArraySize;
  }
}
