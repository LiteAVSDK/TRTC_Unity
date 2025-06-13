// Copyright (c) 2023 Tencent. All rights reserved.
// Author: felixyyan

using UnityEngine;

namespace trtc {
  internal sealed class TRTCCallbackObj {
    private readonly string _gameObjName;
    private readonly TRTCActionQueue _actionQueue;

    internal TRTCCallbackObj(string gameObjName) {
      _gameObjName = gameObjName;
      TryDestroy(_gameObjName);

      var callbackObj = new GameObject(_gameObjName) { hideFlags = HideFlags.HideInHierarchy };
      _actionQueue = callbackObj.AddComponent<TRTCActionQueue>();
      Object.DontDestroyOnLoad(callbackObj);
    }

    internal TRTCActionQueue GetActionQueue() { return _actionQueue; }

    private static void TryDestroy(string gameObjName) {
      try {
        var obj = GameObject.Find(gameObjName);
        if (ReferenceEquals(obj, null)) {
          return;
        }
        var queue = obj.GetComponent<TRTCActionQueue>();
        if (null != queue) {
          queue.Destroy();
        }
        Object.Destroy(obj);
      } catch (System.Exception exception) {
        TRTCLogger.Warning($"TryDestroy Invoke {exception}");
      }
    }

    public static void Destroy(TRTCCallbackObj obj) { TryDestroy(obj?._gameObjName); }
  }
}