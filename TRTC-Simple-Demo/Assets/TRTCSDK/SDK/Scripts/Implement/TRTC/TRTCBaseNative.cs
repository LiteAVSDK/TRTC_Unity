// Copyright (c) 2023 Tencent. All rights reserved.
// Author: felixyyan

namespace trtc {
  public class TRTCBaseNative {
#if UNITY_ANDROID && !UNITY_EDITOR
    protected const string TRTCLibName = "liteavsdk";
#elif UNITY_OPENHARMONY && !UNITY_EDITOR
    protected const string TRTCLibName = "liteavsdk";
#elif (UNITY_IPHONE || UNITY_WEBGL) && !UNITY_EDITOR
    protected const string TRTCLibName = "__Internal";
#elif UNITY_STANDALONE_WIN || UNITY_EDITOR_WIN
    protected const string TRTCLibName = "liteav";
#else
    protected const string TRTCLibName = "TXLiteAVSDK_TRTC_Mac";
#endif
  }
}