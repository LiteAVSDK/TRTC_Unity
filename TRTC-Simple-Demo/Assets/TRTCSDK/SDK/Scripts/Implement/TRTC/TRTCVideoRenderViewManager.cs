// Copyright (c) 2024 Tencent. All rights reserved.
// Author: bardshang

using System.Collections.Generic;
using UnityEngine;

namespace trtc {

  public class TRTCVideoRenderViewManager {
    private UnityEngine.Object _viewMapLock = new UnityEngine.Object();
    static TRTCVideoRenderViewManager _sInstance = new TRTCVideoRenderViewManager();
    private Dictionary<RenderKey, GameObject> _videoRenderViewMap = new Dictionary<RenderKey, GameObject>();

    public static TRTCVideoRenderViewManager getInstance() {
      return _sInstance;
    }


    private TRTCVideoRenderViewManager(){}


    ~TRTCVideoRenderViewManager() {
      Destroy();
    }

    private void Destroy() {
      removeAllVideoRenderView();
    }
    public void addVideoRenderView(GameObject view, string userID, TRTCVideoStreamType streamType) {
      lock (_viewMapLock) {
        RenderKey key = new RenderKey(userID, streamType);
        if (_videoRenderViewMap.ContainsKey(key)) {
          GameObject oldView = _videoRenderViewMap[key];
          if (oldView == view) {
            return;
          }
          releaseVideoRender(oldView);
          _videoRenderViewMap.Remove(key);
        }

        TRTCVideoRender render = view.AddComponent<TRTCVideoRender>();
        render.SetForUser(userID, streamType);
        _videoRenderViewMap[key] = view;
      }
    }

    public void removeVideoRenderView(string userID, TRTCVideoStreamType streamType) {
      lock (_viewMapLock) {
        RenderKey key = new RenderKey(userID, streamType);
        if (_videoRenderViewMap.ContainsKey(key)) {
          releaseVideoRender(_videoRenderViewMap[key]);
          _videoRenderViewMap.Remove(key);
        }
      }
    }

    public void removeAllRemoteVideoRenderView() {
      lock (_viewMapLock) {
        List<RenderKey> keysToRemove = new List<RenderKey>();
        foreach (var key in _videoRenderViewMap.Keys) {
          if (!string.IsNullOrEmpty(key.UserId)) {
            keysToRemove.Add(key);
          }
        }

        foreach (var key in keysToRemove) {
          _videoRenderViewMap.Remove(key);
        }
      }
    }

    public void removeAllVideoRenderView() {
      lock (_viewMapLock) {
        foreach (var item in _videoRenderViewMap.Values) {
          releaseVideoRender(item);
        }
        _videoRenderViewMap.Clear();
      }
    }

    public void setVideoRenderParams(string userID, TRTCVideoStreamType streamType, TRTCRenderParams renderParams) {
      lock (_viewMapLock) {
        RenderKey key = new RenderKey(userID, streamType);
        if (_videoRenderViewMap.ContainsKey(key)) {
          TRTCVideoRender render = _videoRenderViewMap[key].GetComponent<TRTCVideoRender>();
          render.setRenderParams(renderParams);
        }
      }
    }

    private void releaseVideoRender(GameObject view) {
      if (!view) {
        return;
      }
      var render = view.GetComponent<TRTCVideoRender>();
      if (render) {
        GameObject.Destroy(render);
      }
    }

  }
}