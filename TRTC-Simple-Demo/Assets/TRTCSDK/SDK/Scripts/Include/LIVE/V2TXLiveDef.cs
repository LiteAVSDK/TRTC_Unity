// Copyright (c) 2023 Tencent. All rights reserved.
// Author: makbaktan
namespace liteav {
  public struct V2TXLivePlayerStatistics {
    public int appCpu;
    public int systemCpu;
    public int width;
    public int height;
    public int fps;
    public int videoBitrate;
    public int audioBitrate;
    public int audioPacketLoss;
    public int videoPacketLoss;
    public int jitterBufferDelay;
    public int audioTotalBlockTime;
    public int audioBlockRate;
    public int videoTotalBlockTime;
    public int videoBlockRate;
    public int rtt;
    public int netSpeed;
  }
  public struct V2TXLiveVideoFrame {
    public V2TXLivePixelFormat pixelFormat;
    public V2TXLiveBufferType bufferType;
    public byte[] data;
    public int length;
    public int width;
    public int height;
    public V2TXLiveRotation rotation;
  }
  public struct V2TXLiveAudioFrame {
    public byte[] data;
    public int length;
    public int sampleRate;
    public int channel;
  }

  public enum V2TXLiveRotation {
    V2TXLiveRotation0,
    V2TXLiveRotation90,
    V2TXLiveRotation180,
    V2TXLiveRotation270
  }
  public enum V2TXLiveFillMode {
    V2TXLiveFillModeFill,
    V2TXLiveFillModeFit,
    V2TXLiveFillModeScaleFill
  }
  public enum V2TXLivePixelFormat {
    V2TXLivePixelFormatUnknown,
    V2TXLivePixelFormatI420,
    V2TXLivePixelFormatBGRA32,
    V2TXLivePixelFormatRGBA32
  }
  public enum V2TXLiveBufferType { V2TXLiveBufferTypeUnknown, V2TXLiveBufferTypeByteBuffer }
  ;
}