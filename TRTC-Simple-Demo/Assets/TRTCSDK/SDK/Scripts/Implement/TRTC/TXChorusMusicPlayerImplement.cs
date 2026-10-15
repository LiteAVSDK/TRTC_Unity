// Copyright (c) 2024 Tencent. All rights reserved.
// Author: felixyyan

using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
#if UNITY_EDITOR || UNITY_STANDALONE || UNITY_ANDROID || UNITY_IOS || UNITY_OPENHARMONY || UNITY_WEBGL
using AOT;
#endif

namespace trtc {

  public class TXChorusMusicPlayerImplement : IChorusMusicPlayer {
    #region IChorusMusicPlayer callback

    private static readonly Dictionary<IntPtr, IChorusPlayerEventCallback> callbackDic =
        new Dictionary<IntPtr, IChorusPlayerEventCallback>();
    private static readonly object callbackDicLock = new object();

    private static IChorusPlayerEventCallback GetCallback(IntPtr instance) {
      if (instance == IntPtr.Zero) {
        return null;
      }
      IChorusPlayerEventCallback callback;
      lock (callbackDicLock) {
        callbackDic.TryGetValue(instance, out callback);
      }
      return callback;
    }

    private static void AddCallback(IntPtr instance, IChorusPlayerEventCallback callback) {
      if (instance == IntPtr.Zero || callback == null) {
        return;
      }
      lock (callbackDicLock) {
        callbackDic[instance] = callback;
      }
    }

    private static void RemoveCallback(IntPtr instance) {
      if (instance == IntPtr.Zero) {
        return;
      }
      lock (callbackDicLock) {
        if (callbackDic.ContainsKey(instance)) {
          callbackDic.Remove(instance);
        }
      }
    }

    #endregion

    #region static callback

    [MonoPInvokeCallback(typeof(TXChorusMusicPlayerNative.OnErrorHandler))]
    public static void OnErrorHandler(IntPtr instance, int errCode, string errMsg, IntPtr userData) {
      GetCallback(instance)?.onChorusError((ChorusError)errCode, errMsg);
    }

    [MonoPInvokeCallback(typeof(TXChorusMusicPlayerNative.OnRequireLoadMusicHandler))]
    public static void OnRequireLoadMusicHandler(IntPtr instance, string musicId, IntPtr userData) {
      GetCallback(instance)?.onChorusRequireLoadMusic(musicId);
    }

    [MonoPInvokeCallback(typeof(TXChorusMusicPlayerNative.OnMusicLoadProgressHandler))]
    public static void OnMusicLoadProgressHandler(IntPtr instance, string musicId, float progress,
                                                  IntPtr userData) {
      GetCallback(instance)?.onChorusMusicLoadProgress(musicId, progress);
    }

    [MonoPInvokeCallback(typeof(TXChorusMusicPlayerNative.OnMusicLoadSucceedHandler))]
    public static void OnMusicLoadSucceedHandler(IntPtr instance, string musicId, IntPtr userData) {
      GetCallback(instance)?.onChorusMusicLoadSucceed(musicId);
    }

    [MonoPInvokeCallback(typeof(TXChorusMusicPlayerNative.OnStartedHandler))]
    public static void OnStartedHandler(IntPtr instance, IntPtr userData) {
      GetCallback(instance)?.onChorusStarted();
    }

    [MonoPInvokeCallback(typeof(TXChorusMusicPlayerNative.OnPausedHandler))]
    public static void OnPausedHandler(IntPtr instance, IntPtr userData) {
      GetCallback(instance)?.onChorusPaused();
    }

    [MonoPInvokeCallback(typeof(TXChorusMusicPlayerNative.OnResumedHandler))]
    public static void OnResumedHandler(IntPtr instance, IntPtr userData) {
      GetCallback(instance)?.onChorusResumed();
    }

    [MonoPInvokeCallback(typeof(TXChorusMusicPlayerNative.OnStoppedHandler))]
    public static void OnStoppedHandler(IntPtr instance, int reason, IntPtr userData) {
      GetCallback(instance)?.onChorusStopped((ChorusStopReason)reason);
    }

    [MonoPInvokeCallback(typeof(TXChorusMusicPlayerNative.OnMusicProgressUpdatedHandler))]
    public static void OnMusicProgressUpdatedHandler(IntPtr instance, long progressMs, long durationMs,
                                                     IntPtr userData) {
      GetCallback(instance)?.onMusicProgressUpdated(progressMs, durationMs);
    }

    #endregion

    #region delegate 

    private static readonly TXChorusMusicPlayerNative.OnErrorHandler _onErrorHandlerRef = OnErrorHandler;
    private static readonly TXChorusMusicPlayerNative.OnRequireLoadMusicHandler _onRequireLoadMusicHandlerRef =
        OnRequireLoadMusicHandler;
    private static readonly TXChorusMusicPlayerNative.OnMusicLoadProgressHandler _onMusicLoadProgressHandlerRef =
        OnMusicLoadProgressHandler;
    private static readonly TXChorusMusicPlayerNative.OnMusicLoadSucceedHandler _onMusicLoadSucceedHandlerRef =
        OnMusicLoadSucceedHandler;
    private static readonly TXChorusMusicPlayerNative.OnStartedHandler _onStartedHandlerRef = OnStartedHandler;
    private static readonly TXChorusMusicPlayerNative.OnPausedHandler _onPausedHandlerRef = OnPausedHandler;
    private static readonly TXChorusMusicPlayerNative.OnResumedHandler _onResumedHandlerRef = OnResumedHandler;
    private static readonly TXChorusMusicPlayerNative.OnStoppedHandler _onStoppedHandlerRef = OnStoppedHandler;
    private static readonly TXChorusMusicPlayerNative.OnMusicProgressUpdatedHandler
        _onMusicProgressUpdatedHandlerRef = OnMusicProgressUpdatedHandler;

    #endregion

    public static IChorusMusicPlayer create(ITRTCCloud cloud, string roomId,
                                            IChorusPlayerEventCallback callback) {
      return new TXChorusMusicPlayerImplement(cloud, roomId, callback);
    }

    public static void destroy(IChorusMusicPlayer player) {
      if (player == null) {
        return;
      }
      var impl = player as TXChorusMusicPlayerImplement;
      if (impl != null) {
        impl.onDestroy();
      }
    }

    private IntPtr _nativeObj;

    public TXChorusMusicPlayerImplement(ITRTCCloud cloud, string roomId,
                                        IChorusPlayerEventCallback callback) {
      TRTCLogger.Info("TXChorusMusicPlayerImplement constructor");

      if (cloud == null || roomId == null) {
        throw new ArgumentException("cloud or roomId cannot be null");
      }
      var cloudImpl = cloud as TRTCCloudImplement;
      IntPtr cloudPtr = cloudImpl != null ? cloudImpl.GetNativePtr() : IntPtr.Zero;
      if (cloudPtr == IntPtr.Zero) {
        throw new InvalidOperationException("Failed to get native TRTCCloud pointer.");
      }

      _nativeObj = TXChorusMusicPlayerNative.tx_chorus_music_player_create(cloudPtr, roomId);
      if (_nativeObj == IntPtr.Zero) {
        throw new InvalidOperationException("Failed to create native chorus music player instance.");
      }

      try {
        RegisterAllHandlers();

        if (callback != null) {
          AddCallback(_nativeObj, callback);
        }
      }
      catch (Exception) {
        TXChorusMusicPlayerNative.tx_chorus_music_player_destroy(_nativeObj);
        _nativeObj = IntPtr.Zero;
        throw;
      }
    }

    internal void onDestroy() {
      TRTCLogger.Info("TXChorusMusicPlayerImplement Dispose");
      if (_nativeObj == IntPtr.Zero) {
        return;
      }

      UnregisterAllHandlers();
      RemoveCallback(_nativeObj);
      TXChorusMusicPlayerNative.tx_chorus_music_player_destroy(_nativeObj);
      _nativeObj = IntPtr.Zero;
    }

    private void RegisterAllHandlers() {
      if (_nativeObj == IntPtr.Zero) {
        return;
      }

      TXChorusMusicPlayerNative.tx_chorus_music_player_set_on_error_handler(
          _nativeObj, _onErrorHandlerRef, IntPtr.Zero);
      TXChorusMusicPlayerNative.tx_chorus_music_player_set_on_require_load_music_handler(
          _nativeObj, _onRequireLoadMusicHandlerRef, IntPtr.Zero);
      TXChorusMusicPlayerNative.tx_chorus_music_player_set_on_music_load_progress_handler(
          _nativeObj, _onMusicLoadProgressHandlerRef, IntPtr.Zero);
      TXChorusMusicPlayerNative.tx_chorus_music_player_set_on_music_load_succeed_handler(
          _nativeObj, _onMusicLoadSucceedHandlerRef, IntPtr.Zero);
      TXChorusMusicPlayerNative.tx_chorus_music_player_set_on_started_handler(
          _nativeObj, _onStartedHandlerRef, IntPtr.Zero);
      TXChorusMusicPlayerNative.tx_chorus_music_player_set_on_paused_handler(
          _nativeObj, _onPausedHandlerRef, IntPtr.Zero);
      TXChorusMusicPlayerNative.tx_chorus_music_player_set_on_resumed_handler(
          _nativeObj, _onResumedHandlerRef, IntPtr.Zero);
      TXChorusMusicPlayerNative.tx_chorus_music_player_set_on_stopped_handler(
          _nativeObj, _onStoppedHandlerRef, IntPtr.Zero);
      TXChorusMusicPlayerNative.tx_chorus_music_player_set_on_music_progress_updated_handler(
          _nativeObj, _onMusicProgressUpdatedHandlerRef, IntPtr.Zero);
    }

    private void UnregisterAllHandlers() {
      if (_nativeObj == IntPtr.Zero) {
        return;
      }

      TXChorusMusicPlayerNative.tx_chorus_music_player_set_on_error_handler(
          _nativeObj, null, IntPtr.Zero);
      TXChorusMusicPlayerNative.tx_chorus_music_player_set_on_require_load_music_handler(
          _nativeObj, null, IntPtr.Zero);
      TXChorusMusicPlayerNative.tx_chorus_music_player_set_on_music_load_progress_handler(
          _nativeObj, null, IntPtr.Zero);
      TXChorusMusicPlayerNative.tx_chorus_music_player_set_on_music_load_succeed_handler(
          _nativeObj, null, IntPtr.Zero);
      TXChorusMusicPlayerNative.tx_chorus_music_player_set_on_started_handler(
          _nativeObj, null, IntPtr.Zero);
      TXChorusMusicPlayerNative.tx_chorus_music_player_set_on_paused_handler(
          _nativeObj, null, IntPtr.Zero);
      TXChorusMusicPlayerNative.tx_chorus_music_player_set_on_resumed_handler(
          _nativeObj, null, IntPtr.Zero);
      TXChorusMusicPlayerNative.tx_chorus_music_player_set_on_stopped_handler(
          _nativeObj, null, IntPtr.Zero);
      TXChorusMusicPlayerNative.tx_chorus_music_player_set_on_music_progress_updated_handler(
          _nativeObj, null, IntPtr.Zero);
    }

    public override void setChorusRole(ChorusRole role, TRTCParams? trtcParamsForPlayer) {
      if (_nativeObj == IntPtr.Zero) {
        return;
      }

      IntPtr trtcParamsPtr = IntPtr.Zero;
      TRTCParamsInner innerParam = default(TRTCParamsInner);

      if (trtcParamsForPlayer.HasValue) {
        innerParam = TRTCTypeConverter.ConvertTRTCParamsToInner(trtcParamsForPlayer.Value);
        trtcParamsPtr = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(TRTCParamsInner)));
        Marshal.StructureToPtr(innerParam, trtcParamsPtr, false);
      }

      TXChorusMusicPlayerNative.tx_chorus_music_player_set_chorus_role(
          _nativeObj, (int)role, trtcParamsPtr);

      if (trtcParamsPtr != IntPtr.Zero) {
        Marshal.FreeHGlobal(trtcParamsPtr);
        TRTCTypeConverter.FreeTRTCParamsInner(innerParam);
      }
    }

    public override void loadExternalMusic(ChorusExternalMusicParams param) {
      if (_nativeObj == IntPtr.Zero || param == null) {
        return;
      }

      var innerParam = new TXChorusMusicPlayerNative.TXChorusExternalMusicParamsInner();
      using (var musicIdMarshaler = new Utf8StringMarshaler(param.musicId))
      using (var musicUrlMarshaler = new Utf8StringMarshaler(param.musicUrl))
      using (var accompanyUrlMarshaler = new Utf8StringMarshaler(param.accompanyUrl)) {
        innerParam.musicId = musicIdMarshaler.GetUtf8IntPtr();
        innerParam.musicUrl = musicUrlMarshaler.GetUtf8IntPtr();
        innerParam.accompanyUrl = accompanyUrlMarshaler.GetUtf8IntPtr();

        TXChorusMusicPlayerNative.tx_chorus_music_player_load_external_music(
            _nativeObj, innerParam);
      }
    }

    public override void start() {
      if (_nativeObj == IntPtr.Zero) {
        return;
      }
      TXChorusMusicPlayerNative.tx_chorus_music_player_start(_nativeObj);
    }

    public override void stop() {
      if (_nativeObj == IntPtr.Zero) {
        return;
      }
      TXChorusMusicPlayerNative.tx_chorus_music_player_stop(_nativeObj);
    }

    public override void pause() {
      if (_nativeObj == IntPtr.Zero) {
        return;
      }
      TXChorusMusicPlayerNative.tx_chorus_music_player_pause(_nativeObj);
    }

    public override void resume() {
      if (_nativeObj == IntPtr.Zero) {
        return;
      }
      TXChorusMusicPlayerNative.tx_chorus_music_player_resume(_nativeObj);
    }

    public override void seek(long timestampMs) {
      if (_nativeObj == IntPtr.Zero) {
        return;
      }
      TXChorusMusicPlayerNative.tx_chorus_music_player_seek(_nativeObj, timestampMs);
    }

    public override void switchMusicTrack(ChorusMusicTrack track) {
      if (_nativeObj == IntPtr.Zero) {
        return;
      }
      TXChorusMusicPlayerNative.tx_chorus_music_player_switch_music_track(
          _nativeObj, (int)track);
    }

    public override void setPlayoutVolume(int volume) {
      if (_nativeObj == IntPtr.Zero) {
        return;
      }
      TXChorusMusicPlayerNative.tx_chorus_music_player_set_playout_volume(
          _nativeObj, volume);
    }

    public override void setPublishVolume(int volume) {
      if (_nativeObj == IntPtr.Zero) {
        return;
      }
      TXChorusMusicPlayerNative.tx_chorus_music_player_set_publish_volume(
          _nativeObj, volume);
    }

    public override void setMusicPitch(float pitch) {
      if (_nativeObj == IntPtr.Zero) {
        return;
      }
      TXChorusMusicPlayerNative.tx_chorus_music_player_set_music_pitch(_nativeObj, pitch);
    }

    public override void callExperimentalAPI(string jsonStr) {
      if (_nativeObj == IntPtr.Zero) {
        return;
      }
      TXChorusMusicPlayerNative.tx_chorus_music_player_call_experimental_api(
          _nativeObj, jsonStr);
    }
  }
}
