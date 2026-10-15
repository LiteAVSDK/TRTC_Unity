// Copyright (c) 2024 Tencent. All rights reserved.
// Author: kleinjia

import deviceInfo from '@ohos.deviceInfo';
import hidebug from '@ohos.hidebug';
import { AppStateMonitor } from "./liteav_app_state_monitor"
import { NetworkStateMonitor } from './liteav_network_state_monitor';
import { AppInfo } from "./liteav_app_info"
import common from '@ohos.app.ability.common';
import abilityAccessCtrl from '@ohos.abilityAccessCtrl';
import bundleManager from '@ohos.bundle.bundleManager';

enum MicPermission {
  NotDetermined = 0,
  Denied = 1,
  Allowed = 2,
};

export class LiteavSystemInfo {
  public static nativeInitialize(appContext: common.ApplicationContext): void {
    let hardware = deviceInfo.hardwareModel;
    let manufacture = deviceInfo.manufacture;
    let model = deviceInfo.softwareModel;
    let os_version = deviceInfo.osFullName;
    let os_version_int = deviceInfo.sdkApiVersion;
    this.nativeSetDeviceInfo(hardware, manufacture, model, os_version, os_version_int);

    AppInfo.initialize(appContext);
    this.nativeSetApplicationInfo(AppInfo.getAppName(), AppInfo.getAppPackageName(), AppInfo.getAppVersion());

    AppStateMonitor.getInstance().on('onAppBackgroundStateChanged', async (backgroundState: number) => {
      this.nativeSetAppBackgroundState(backgroundState);
    });
    NetworkStateMonitor.getInstance().on('onNetworkTypeChanged', async (networkType: number) => {
      this.nativeSetNetworkType(networkType);
    });
    AppStateMonitor.getInstance().initialize(appContext);
  }

  public static nativeGetAppMemoryUsage(): number {
    return Number(hidebug.getNativeHeapSize());
  }

  public static nativeListenAppBackgroundState(): void {
    AppStateMonitor.getInstance().start();
    NetworkStateMonitor.getInstance().start();
  }

  public static nativeGetMicPermission(): number {
    try {
      let atManager: abilityAccessCtrl.AtManager = abilityAccessCtrl.createAtManager();
      let tokenID: number = bundleManager.getBundleInfoForSelfSync(bundleManager.BundleFlag.GET_BUNDLE_INFO_WITH_APPLICATION).appInfo.accessTokenId;
      let data: abilityAccessCtrl.GrantStatus = atManager.checkAccessTokenSync(tokenID, 'ohos.permission.MICROPHONE');
      return (data == abilityAccessCtrl.GrantStatus.PERMISSION_GRANTED) ? MicPermission.Allowed : MicPermission.Denied;
    } catch(err) {
      return MicPermission.NotDetermined;
    }
  }

  static nativeSetDeviceInfo(hardware: string, manufacture: string, model: string, osVersion: string, osVersionInt: number): void { }
  static nativeSetApplicationInfo(appName: string, packageName: string, appVersion: string): void { }
  static nativeSetAppBackgroundState(memoryUsage: number): void { }
  static nativeSetNetworkType(memoryUsage: number): void { }
}