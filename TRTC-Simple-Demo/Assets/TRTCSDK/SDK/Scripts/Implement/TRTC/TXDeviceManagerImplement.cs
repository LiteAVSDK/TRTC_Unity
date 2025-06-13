// Copyright (c) 2023 Tencent. All rights reserved.
// Author: felixyyan

using System;

namespace trtc {
  public class TXDeviceManagerImplement : ITXDeviceManager {
    private IntPtr _nativeObj;
    private const UInt32 _deviceInfoLen = 1024;
    public TXDeviceManagerImplement(IntPtr nativeObj) { _nativeObj = nativeObj; }

    public void DestroyNativeObj() { _nativeObj = IntPtr.Zero; }

    // 1.1
    public override bool isFrontCamera() {
      return TXDeviceManagerNative.tx_device_manager_is_front_camera(_nativeObj);
    }

    // 1.2
    public override int switchCamera(bool frontCamera) {
      return TXDeviceManagerNative.tx_device_manager_switch_camera(_nativeObj, frontCamera);
    }

    // 1.3
    public override double getCameraZoomMaxRatio() {
      return (double)TXDeviceManagerNative.tx_device_manager_get_camera_zoom_max_ratio(_nativeObj);
    }

    // 1.4
    public override int setCameraZoomRatio(double zoomRatio) {
      return TXDeviceManagerNative.tx_device_manager_set_camera_zoom_ratio(_nativeObj,
                                                                           (float)zoomRatio);
    }

    // 1.5
    public override bool isAutoFocusEnabled() {
      return TXDeviceManagerNative.tx_device_manager_is_audio_focus_enabled(_nativeObj);
    }

    // 1.6
    public override int enableCameraAutoFocus(bool enabled) {
      return TXDeviceManagerNative.tx_device_manager_enable_camera_auto_focus(_nativeObj, enabled);
    }

    // 1.7
    public override int setCameraFocusPosition(int x, int y) {
      return TXDeviceManagerNative.tx_device_manager_set_camera_focus_position(_nativeObj, x, y);
    }

    // 1.8
    public override int enableCameraTorch(bool enabled) {
      return TXDeviceManagerNative.tx_device_manager_enable_camera_torch(_nativeObj, enabled);
    }

    public override int setAudioRoute(TXAudioRoute route) {
      return TXDeviceManagerNative.tx_device_manager_set_audio_route(_nativeObj, route);
    }

    // 2.1
    public override TXDeviceInfo[] getDevicesList(TXMediaDeviceType type) {
      int count = TXDeviceManagerNative.tx_device_manager_get_device_count(_nativeObj, type);
      if (count <= 0) {
        return new TXDeviceInfo[0];
      }

      TXDeviceInfo[] deviceInfos = new TXDeviceInfo[count];
      DeviceInfo inner_deviceInfo = new DeviceInfo();
      for (int i = 0; i < count; i++) {
        inner_deviceInfo.devicePIDLen = _deviceInfoLen;
        inner_deviceInfo.deviceNameLen = _deviceInfoLen;
        inner_deviceInfo.devicePropertiesLen = _deviceInfoLen;
        inner_deviceInfo.deviceName = new string(' ', (int)inner_deviceInfo.deviceNameLen);
        inner_deviceInfo.devicePID = new string(' ', (int)inner_deviceInfo.devicePIDLen);
        inner_deviceInfo.deviceProperties =
            new string(' ', (int)inner_deviceInfo.devicePropertiesLen);
        TXDeviceManagerNative.tx_device_manager_get_device_info(_nativeObj, type, i,
                                                                ref inner_deviceInfo);
        deviceInfos[i].deviceName = inner_deviceInfo.deviceName;
        deviceInfos[i].devicePID = inner_deviceInfo.devicePID;
        deviceInfos[i].deviceProperties = inner_deviceInfo.deviceProperties;
      }

      return deviceInfos;
    }

    // 2.2
    public override int setCurrentDevice(TXMediaDeviceType type, String deviceId) {
      return TXDeviceManagerNative.tx_device_manager_set_current_device(_nativeObj, type, deviceId);
    }

    // 2.3
    public override TXDeviceInfo getCurrentDevice(TXMediaDeviceType type) {
      DeviceInfo inner_deviceInfo = new DeviceInfo();

      inner_deviceInfo.devicePIDLen = _deviceInfoLen;
      inner_deviceInfo.deviceNameLen = _deviceInfoLen;
      inner_deviceInfo.devicePropertiesLen = _deviceInfoLen;
      inner_deviceInfo.deviceName = new string(' ', (int)inner_deviceInfo.deviceNameLen);
      inner_deviceInfo.devicePID = new string(' ', (int)inner_deviceInfo.deviceNameLen);
      inner_deviceInfo.deviceProperties =
          new string(' ', (int)inner_deviceInfo.devicePropertiesLen);

      TXDeviceManagerNative.tx_device_manager_get_current_device(_nativeObj, type,
                                                                 ref inner_deviceInfo);
      TXDeviceInfo deviceInfo = new TXDeviceInfo();
      deviceInfo.deviceName = inner_deviceInfo.deviceName;
      deviceInfo.devicePID = inner_deviceInfo.devicePID;
      deviceInfo.deviceProperties = inner_deviceInfo.deviceProperties;

      return deviceInfo;
    }

    // 2.4
    public override int setSystemVolumeType(TXSystemVolumeType type) {
#if UNITY_IPHONE || UNITY_ANDROID || UNITY_OPENHARMONY
      return TXDeviceManagerNative.tx_device_manager_set_system_volume_type(_nativeObj, type);
#endif
      return -1;
    }
  }
}