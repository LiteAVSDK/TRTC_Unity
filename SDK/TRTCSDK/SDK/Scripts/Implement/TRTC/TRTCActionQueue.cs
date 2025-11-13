// Copyright (c) 2023 Tencent. All rights reserved.
// Author: felixyyan

using System;
using System.Collections.Generic;
using UnityEngine;

namespace trtc {
  internal sealed class TRTCActionQueue
  {
    private readonly Queue<Action> _actions = new Queue<Action>();
    private bool _paused = false;
    private bool _destroyed = false;

    internal void Clear() {
      lock (_actions) {
        _actions.Clear();
      }
    }

    internal void Enqueue(Action action, bool canDrop = false) {
      if (action == null) {
        return;
      }

      if(canDrop && _paused) {
        return;
      }
      lock (_actions) {
        if (!_destroyed) {
          _actions.Enqueue(action);
        }
      }
    }

    private Action Dequeue() {
      Action action = null;
      lock (_actions) {
        if (_actions.Count > 0) {
          action = _actions.Dequeue();
        }
      }

      return action;
    }

    internal void Update() {
        DateTime startTime = DateTime.UtcNow;

        while (true) {
            if (((Int64)(DateTime.UtcNow - startTime).TotalMilliseconds) >= 20) {
                break;
            }

            Action action = Dequeue();
            if (action != null) {
                try {
                    action?.Invoke();
                } catch (Exception exception) {
                    Debug.Log($"TRTCActionQueue Invoke {exception}");
                }
            } else {
                break;
            }
        }
    }

    internal void Destroy() {
      lock (_actions) {
        _destroyed = true;
        _actions.Clear();
      }
    }

    internal void OnApplicationPause(bool pauseStatus) {
      _paused = pauseStatus;
    }
  }
}