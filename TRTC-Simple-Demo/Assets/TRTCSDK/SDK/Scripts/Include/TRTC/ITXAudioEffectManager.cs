// Copyright (c) 2023 Tencent. All rights reserved.

using System;

namespace trtc {
  // 1.1
  public enum TXVoiceReverbType {
    TXVoiceReverbType_0 = 0,
    TXVoiceReverbType_1 = 1,
    TXVoiceReverbType_2 = 2,
    TXVoiceReverbType_3 = 3,
    TXVoiceReverbType_4 = 4,
    TXVoiceReverbType_5 = 5,
    TXVoiceReverbType_6 = 6,
    TXVoiceReverbType_7 = 7,
    TXVoiceReverbType_8 = 8,
    TXVoiceReverbType_9 = 9,
    TXVoiceReverbType_10 = 10,
    TXVoiceReverbType_11 = 11,
  }

  // 1.2
  public enum TXVoiceChangeType {
    TXVoiceChangeType_0 = 0,
    TXVoiceChangeType_1 = 1,
    TXVoiceChangeType_2 = 2,
    TXVoiceChangeType_3 = 3,
    TXVoiceChangeType_4 = 4,
    TXVoiceChangeType_5 = 5,
    TXVoiceChangeType_6 = 6,
    TXVoiceChangeType_7 = 7,
    TXVoiceChangeType_8 = 8,
    TXVoiceChangeType_9 = 9,
    TXVoiceChangeType_10 = 10,
    TXVoiceChangeType_11 = 11,
  }

  public interface ITXMusicPreloadObserver {
    void onLoadProgress(int musicId, int progress);
    void onLoadError(int musicId, int errCode);
  }

  public interface ITXMusicPlayObserver {
    void onStart(int musicId, int errCode);
    void onPlayProgress(int musicId, long curPtsMS, long durationMS);
    void onComplete(int musicId, int errCode);
  }

  public struct AudioMusicParam {
    public int id;
    public String path;
    public int loopCount;
    public bool publish;
    public bool isShortFile;
    public int startTimeMS;
    public int endTimeMS;
  }

  public abstract class ITXAudioEffectManager {
    // 1.1
    public abstract void enableVoiceEarMonitor(bool enable);

    // 1.2
    public abstract void setVoiceEarMonitorVolume(int volume);

    // 1.3
    public abstract void setVoiceReverbType(TXVoiceReverbType reverbType);

    // 1.4
    public abstract void setVoiceChangerType(TXVoiceChangeType changerType);

    // 1.5
    public abstract void setVoiceCaptureVolume(int volume);

    // 1.6
    public abstract void setVoicePitch(double pitch);

    // 2.0
    public abstract void setMusicObserver(int musicId, ITXMusicPlayObserver observer);

    // 2.1
    public abstract void startPlayMusic(AudioMusicParam musicParam);

    // 2.2
    public abstract void stopPlayMusic(int musicId);

    // 2.3
    public abstract void pausePlayMusic(int musicId);

    // 2.4
    public abstract void resumePlayMusic(int musicId);

    // 2.5
    public abstract void setAllMusicVolume(int volume);

    // 2.6
    public abstract void setMusicPublishVolume(int musicId, int volume);

    // 2.7
    public abstract void setMusicPlayoutVolume(int musicId, int volume);

    // 2.8
    public abstract void setMusicPitch(int musicId, double pitch);

    // 2.9
    public abstract void setMusicSpeedRate(int musicId, double speedRate);

    // 2.10
    public abstract int getMusicCurrentPosInMS(int musicId);

    // 2.11
    public abstract int getMusicDurationInMS(string path);

    // 2.12
    public abstract void seekMusicToPosInTime(int musicId, int pts);

    // 2.13
    public abstract void setMusicScratchSpeedRate(int musicId, float scratchSpeedRate);

    // 2.14
    public abstract void setPreloadObserver(ITXMusicPreloadObserver observer);

    // 2.15
    public abstract void preloadMusic(AudioMusicParam preloadParam);

    // 2.16
    public abstract int getMusicTrackCount(int musicId);

    // 2.17
    public abstract void setMusicTrack(int musicId, int trackIndex);

    [Obsolete("use seekMusicToPosInTime(int, int)")]
    public abstract void seekMusicToPosInMS(int musicId, int pts);
  }
}