// Copyright (c) 2023 Tencent. All rights reserved.
// Author: felixyyan

using System;
using System.Runtime.InteropServices;

namespace trtc {
  public class TXDeviceManagerNative : TRTCBaseNative {
    // 1.1
    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern bool tx_device_manager_is_front_camera(IntPtr instance);

    // 1.2
    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern int tx_device_manager_switch_camera(IntPtr instance, bool front_camera);

    // 1.3
    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern float tx_device_manager_get_camera_zoom_max_ratio(IntPtr instance);

    // 1.4
    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern int tx_device_manager_set_camera_zoom_ratio(IntPtr instance,
                                                                     float zoom_ratio);

    // 1.5
    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern bool tx_device_manager_is_audio_focus_enabled(IntPtr instance);

    // 1.6
    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern int tx_device_manager_enable_camera_auto_focus(IntPtr instance,
                                                                        bool enabled);

    // 1.7
    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern int tx_device_manager_set_camera_focus_position(IntPtr instance,
                                                                         float x,
                                                                         float y);

    // 1.8
    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern int tx_device_manager_enable_camera_torch(IntPtr instance, bool enabled);

    // 1.9
    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern int tx_device_manager_set_audio_route(IntPtr instance, TXAudioRoute route);

    // 2.1
    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern int tx_device_manager_get_device_count(IntPtr instance,
                                                                TXMediaDeviceType type);

    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern int tx_device_manager_get_device_info(IntPtr instance,
                                                               TXMediaDeviceType type,
                                                               int index,
                                                               ref DeviceInfo deviceinfo);

    // 2.2
    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern int tx_device_manager_set_current_device(
        IntPtr instance,
        TXMediaDeviceType type,
        [MarshalAs(UnmanagedType.LPStr)] string deviceId);

    // 2.3
    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern int tx_device_manager_get_current_device(IntPtr instance,
                                                                  TXMediaDeviceType type,
                                                                  ref DeviceInfo deviceInfo);
    // 2.4
    [DllImport(TRTCLibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern int tx_device_manager_set_system_volume_type(IntPtr instance,
                                                                       TXSystemVolumeType volumeType);
  }
}