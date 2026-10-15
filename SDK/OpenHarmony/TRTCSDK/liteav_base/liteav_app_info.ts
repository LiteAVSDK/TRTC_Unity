// Copyright (c) 2024 Tencent. All rights reserved.
// Author: kleinjia

import bundleManager from '@ohos.bundle.bundleManager';
import common from '@ohos.app.ability.common';
import { LiteavLog as Log } from './liteav_log';

export class AppInfo {
  private static appName: string = "";
  private static appPackageName: string = "";
  private static appVersion: string = "";

  public static initialize(appContext: common.ApplicationContext): void {
    let bundleFlags = bundleManager.BundleFlag.GET_BUNDLE_INFO_WITH_APPLICATION;
    try {
      let bundleInfo = bundleManager.getBundleInfoForSelfSync(bundleFlags);
      AppInfo.appName = appContext.resourceManager.getStringSync(bundleInfo.appInfo.labelId);
      AppInfo.appPackageName = bundleInfo.name;
      AppInfo.appVersion = bundleInfo.versionName;
    } catch (err) {
      Log.error('AppInfo', "getBundleInfoForSelf err:" + err);
    }
  }

  public static getAppName(): string {
    return AppInfo.appName;
  }

  public static getAppPackageName(): string {
    return AppInfo.appPackageName;
  }

  public static getAppVersion(): string {
    return AppInfo.appVersion;
  }
}