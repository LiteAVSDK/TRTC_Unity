// Copyright (c) 2023 Tencent. All rights reserved.
// Author: felixyyan

using System;

namespace trtc {

  public interface ITXCopyrightedMediaCallback {
    void onPreloadStart(string musicId, string bitrateDefinition);
    void onPreloadProgress(string musicId, string bitrateDefinition, float progress);
    void onPreloadComplete(string musicId, string bitrateDefinition, int errorCode, string msg);
  }

  public abstract class ITXCopyrightedMedia {
    public static ITXCopyrightedMedia createCopyRightMedia() {return new TXCopyrightedMediaImplement();}
    public abstract void destroyCopyRightMedia();
    public abstract int setCopyrightedLicense(string key, string licenseUrl);
    public abstract bool genMusicURI(string musicId, int bgmType, string bitrateDefinition, IntPtr outData, int outDataSize);
    public abstract void setMusicPreloadCallback(ITXCopyrightedMediaCallback callback);
    public abstract int preloadMusic(string musicId, string bitrateDefinition, string playToken);
    public abstract int cancelPreloadMusic(string musicId, string bitrateDefinition);
    public abstract bool isMusicPreload(string musicId, string bitrateDefinition);
    public abstract int clearMusicCache();
    public abstract int setMusicCacheMaxCount(int maxCount);
  }
}