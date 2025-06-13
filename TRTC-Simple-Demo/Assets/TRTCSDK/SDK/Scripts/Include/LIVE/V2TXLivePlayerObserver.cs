// Copyright (c) 2023 Tencent. All rights reserved.
// Author: makbaktan
using System;

namespace liteav {
  public interface V2TXLivePlayerObserver {
    void onError(V2TXLivePlayer player, V2TXLiveCode code, string msg, IntPtr extraInfo);

    void onWarning(V2TXLivePlayer player, V2TXLiveCode code, string msg, IntPtr extraInfo);

    void onVideoResolutionChanged(V2TXLivePlayer player, int width, int height);

    void onConnected(V2TXLivePlayer player, IntPtr extraInfo);

    void onVideoPlaying(V2TXLivePlayer player, bool firstPlay, IntPtr extraInfo);

    void onAudioPlaying(V2TXLivePlayer player, bool firstPlay, IntPtr extraInfo);

    void onVideoLoading(V2TXLivePlayer player, IntPtr extraInfo);

    void onAudioLoading(V2TXLivePlayer player, IntPtr extraInfo);

    void onStatisticsUpdate(V2TXLivePlayer player, V2TXLivePlayerStatistics statistics);

    void onRenderVideoFrame(V2TXLivePlayer player, V2TXLiveVideoFrame videoFrame);
  }
}
