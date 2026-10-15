// Copyright (c) 2026 Tencent. All rights reserved.
// Author: felixyyan

using System;
using System.Runtime.InteropServices;

namespace trtc {
  public class TXChorusMusicPlayerNative : TRTCBaseNative {
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void OnErrorHandler(IntPtr instance,
                                        int errCode,
                                        string errMsg,
                                        IntPtr userData);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void OnRequireLoadMusicHandler(IntPtr instance,
                                                   string musicId,
                                                   IntPtr userData);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void OnMusicLoadProgressHandler(IntPtr instance,
                                                    string musicId,
                                                    float progress,
                                                    IntPtr userData);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void OnMusicLoadSucceedHandler(IntPtr instance,
                                                   string musicId,
                                                   IntPtr userData);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void OnStartedHandler(IntPtr instance, IntPtr userData);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void OnPausedHandler(IntPtr instance, IntPtr userData);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void OnResumedHandler(IntPtr instance, IntPtr userData);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void OnStoppedHandler(IntPtr instance,
                                          int reason,
                                          IntPtr userData);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void OnMusicProgressUpdatedHandler(IntPtr instance,
                                                       long progressMs,
                                                       long durationMs,
                                                       IntPtr userData);

    [StructLayout(LayoutKind.Sequential)]
    public struct TXChorusExternalMusicParamsInner {
      public IntPtr musicId;
      public IntPtr musicUrl;
      public IntPtr accompanyUrl;
    }

    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr tx_chorus_music_player_create(IntPtr cloud, string roomId);

    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern void tx_chorus_music_player_destroy(IntPtr instance);

    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern void tx_chorus_music_player_set_on_error_handler(
        IntPtr instance, OnErrorHandler handler, IntPtr userData);

    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern void tx_chorus_music_player_set_on_require_load_music_handler(
        IntPtr instance, OnRequireLoadMusicHandler handler, IntPtr userData);

    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern void tx_chorus_music_player_set_on_music_load_progress_handler(
        IntPtr instance, OnMusicLoadProgressHandler handler, IntPtr userData);

    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern void tx_chorus_music_player_set_on_music_load_succeed_handler(
        IntPtr instance, OnMusicLoadSucceedHandler handler, IntPtr userData);

    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern void tx_chorus_music_player_set_on_started_handler(
        IntPtr instance, OnStartedHandler handler, IntPtr userData);

    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern void tx_chorus_music_player_set_on_paused_handler(
        IntPtr instance, OnPausedHandler handler, IntPtr userData);

    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern void tx_chorus_music_player_set_on_resumed_handler(
        IntPtr instance, OnResumedHandler handler, IntPtr userData);

    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern void tx_chorus_music_player_set_on_stopped_handler(
        IntPtr instance, OnStoppedHandler handler, IntPtr userData);

    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern void tx_chorus_music_player_set_on_music_progress_updated_handler(
        IntPtr instance, OnMusicProgressUpdatedHandler handler, IntPtr userData);

    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern int tx_chorus_music_player_set_chorus_role(
        IntPtr instance, int role, IntPtr trtcParams);

    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern int tx_chorus_music_player_load_external_music(
        IntPtr instance, TXChorusExternalMusicParamsInner param);

    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern int tx_chorus_music_player_start(IntPtr instance);

    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern int tx_chorus_music_player_stop(IntPtr instance);

    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern int tx_chorus_music_player_pause(IntPtr instance);

    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern int tx_chorus_music_player_resume(IntPtr instance);

    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern int tx_chorus_music_player_seek(
        IntPtr instance, long timestampMs);

    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern int tx_chorus_music_player_switch_music_track(
        IntPtr instance, int track);

    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern int tx_chorus_music_player_set_playout_volume(
        IntPtr instance, int volume);

    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern int tx_chorus_music_player_set_publish_volume(
        IntPtr instance, int volume);

    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern int tx_chorus_music_player_set_music_pitch(
        IntPtr instance, float pitch);

    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern int tx_chorus_music_player_call_experimental_api(
        IntPtr instance, string jsonStr);
  }
}
