// Copyright (c) 2023 Tencent. All rights reserved.
// Author: felixyyan

using UnityEngine;

namespace trtc {
  internal sealed class TRTCCallbackObj {
    private readonly string _gameObjName;
    private readonly TRTCActionQueue _actionQueue = new TRTCActionQueue();

    internal TRTCCallbackObj(string gameObjName) {
      _gameObjName = gameObjName;
      TryDestroy(_gameObjName);

      var callbackObj = new GameObject(_gameObjName) { hideFlags = HideFlags.HideInHierarchy };
      TRTCEventLooper eventLooper = callbackObj.AddComponent<TRTCEventLooper>();
      eventLooper.SetActionQueue(_actionQueue);
      Object.DontDestroyOnLoad(callbackObj);
    }

    internal TRTCActionQueue GetActionQueue() { return _actionQueue; }

    private static void TryDestroy(string gameObjName) {
      try {
        var obj = GameObject.Find(gameObjName);
        if (ReferenceEquals(obj, null)) {
          return;
        }
        Object.Destroy(obj);
      } catch (System.Exception exception) {
        TRTCLogger.Warning($"TryDestroy Invoke {exception}");
      }
    }

    public static void Destroy(TRTCCallbackObj obj) { TryDestroy(obj?._gameObjName); }
  }
}