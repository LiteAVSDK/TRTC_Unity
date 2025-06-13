// Copyright (c) 2023 Tencent. All rights reserved.
// Author: felixyyan

using System;

namespace trtc {
  public enum TXSystemVolumeType {
    TXSystemVolumeTypeAuto = 0,
    TXSystemVolumeTypeMedia = 1,
    TXSystemVolumeTypeVOIP = 2,
  }

  public enum TXAudioRoute {
    TXAudioRouteSpeakerphone = 0,
    TXAudioRouteEarpiece = 1,
  }

  public enum TXMediaDeviceType {
    TXMediaDeviceTypeUnknown = -1,
    TXMediaDeviceTypeMic = 0,
    TXMediaDeviceTypeSpeaker = 1,
    TXMediaDeviceTypeCamera = 2,
  }

  public enum TXMediaDeviceState {
    TXMediaDeviceStateAdd = 0,
    TXMediaDeviceStateRemove = 1,
    TXMediaDeviceStateActive = 2,
    TXMediaDefaultDeviceChanged = 3,
  }

  public enum TXCameraCaptureMode {
    TXCameraResolutionStrategyAuto = 0,
    TXCameraResolutionStrategyPerformance = 1,
    TXCameraResolutionStrategyHighQuality = 2,
    TXCameraCaptureManual = 3,
  }

  [Serializable]
  public struct TXCameraCaptureParam {
    public TXCameraCaptureMode mode;
    public int width;
    public int height;
  }

  [Serializable]
  public struct TXDeviceInfo {
    public String devicePID;
    public String deviceName;
    public String deviceProperties;
  }

  public interface ITXDeviceObserver {
    void onDeviceChanged(String deviceId, TXMediaDeviceType type, TXMediaDeviceState state);
  }

  public abstract class ITXDeviceManager {
    // 1.1
    public abstract bool isFrontCamera();

    // 1.2
    public abstract int switchCamera(bool frontCamera);

    // 1.3
    public abstract double getCameraZoomMaxRatio();

    // 1.4
    public abstract int setCameraZoomRatio(double zoomRatio);

    // 1.5
    public abstract bool isAutoFocusEnabled();

    // 1.6
    public abstract int enableCameraAutoFocus(bool enabled);

    // 1.7
    public abstract int setCameraFocusPosition(int x, int y);

    // 1.8
    public abstract int enableCameraTorch(bool enabled);

    // 1.9
    public abstract int setAudioRoute(TXAudioRoute route);

    // 2.1
    public abstract TXDeviceInfo[] getDevicesList(TXMediaDeviceType type);

    // 2.2
    public abstract int setCurrentDevice(TXMediaDeviceType type, String deviceId);

    // 2.3
    public abstract TXDeviceInfo getCurrentDevice(TXMediaDeviceType type);

    //@deprecated
    public abstract int setSystemVolumeType(TXSystemVolumeType type);
  }
}