// Copyright (c) 2024 Tencent. All rights reserved.
// Author: garyzeng

import abilityAccessCtrl, { Context, PermissionRequestResult } from '@ohos.abilityAccessCtrl'
import { BusinessError } from '@ohos.base';
import { LiteavLog as Log } from "./liteav_log"

export class LiteavAudioPermissionRequester
{
  private static TAG: string = "audio-io";
  public static nativeRequestMicPermission(context: Context, callback: (granted: boolean) => void) : void {
    try {
      let atManager: abilityAccessCtrl.AtManager = abilityAccessCtrl.createAtManager();
      atManager.requestPermissionsFromUser(context, ['ohos.permission.MICROPHONE'], (err: BusinessError, data: PermissionRequestResult) => {
        Log.info(LiteavAudioPermissionRequester.TAG, 'request MICROPHONE result=' + JSON.stringify(data));
        if (data.authResults[0] == 0) {
          callback(true);
        } else  {
          callback(false);
        }
      });
    } catch (err) {
      Log.info(LiteavAudioPermissionRequester.TAG, 'request MICROPHONE error=' + err.message);
      callback(false);
    }
  }
}

