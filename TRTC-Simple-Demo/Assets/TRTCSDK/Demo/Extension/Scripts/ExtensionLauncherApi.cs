// Copyright (c) 2023 Tencent. All rights reserved.
// Author: felixyyan

using System.Runtime.InteropServices;
using UnityEngine;

namespace trtc {
  public class ExtensionLauncher {
#if UNITY_ANDROID && !UNITY_EDITOR
        public static void TRTCUnityExtensionLauncher()
        {
            var MediaServiceHelper = new AndroidJavaClass("com.tencent.trtc.unity.TRTCMediaServiceHelper");

            var androidJavaClass = new AndroidJavaClass("com.unity3d.player.UnityPlayer");
            var androidJavaObject = androidJavaClass.GetStatic<AndroidJavaObject>("currentActivity");
            MediaServiceHelper.CallStatic("launchService", androidJavaObject);
        }
#endif
  }
}