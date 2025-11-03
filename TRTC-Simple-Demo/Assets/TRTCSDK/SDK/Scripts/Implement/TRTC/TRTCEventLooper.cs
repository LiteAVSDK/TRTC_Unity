// Copyright (c) 2025 Tencent. All rights reserved.
// Author: kleinjia

using UnityEngine;

namespace trtc
{
  internal sealed class TRTCEventLooper : MonoBehaviour
  {
    private TRTCActionQueue _actionQueue;

    public void SetActionQueue(TRTCActionQueue actionQueue) {
      _actionQueue = actionQueue;
    }

    void Update() {
      _actionQueue?.Update();
    }

    void OnApplicationPause(bool pauseStatus) {
      _actionQueue?.OnApplicationPause(pauseStatus);
    }

    void OnDestroy() {
      _actionQueue?.Destroy();
      _actionQueue = null;
    }
  }
}