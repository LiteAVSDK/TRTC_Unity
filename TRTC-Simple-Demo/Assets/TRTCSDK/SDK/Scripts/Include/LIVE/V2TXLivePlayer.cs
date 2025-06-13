// Copyright (c) 2023 Tencent. All rights reserved.
// Author: makbaktan
using System;
namespace liteav {
  public abstract class V2TXLivePlayer {
    // 1.1
    public static V2TXLivePlayer createLivePlayer() { return new V2TXLivePlayerImplement(); }
    public abstract void setCallback(V2TXLivePlayerObserver callback);

    public abstract int setRenderRotation(V2TXLiveRotation rotation);

    public abstract int startPlay(string url);

    public abstract int enableObserverVideoFrame(bool enable,
                                                 V2TXLivePixelFormat pixelFormat,
                                                 V2TXLiveBufferType bufferType);

    public abstract int stopPlay();

    public abstract int isPlaying();

    public abstract int pauseAudio();

    public abstract int resumeAudio();

    public abstract int pauseVideo();

    public abstract int resumeVideo();

    public abstract int setPlayoutVolume(int volume);

    public abstract void showDebugView(bool isShow);
  }
}
