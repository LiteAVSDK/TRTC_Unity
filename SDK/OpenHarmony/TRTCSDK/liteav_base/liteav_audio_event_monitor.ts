// Copyright (c) 2024 Tencent. All rights reserved.
// Author: garyzeng

import audio from '@ohos.multimedia.audio';
import { BusinessError } from "@ohos.base";
import { LiteavLog as Log } from "./liteav_log"
import { Callback } from '@ohos.base';
import ApplicationStateChangeCallback from '@ohos.app.ability.ApplicationStateChangeCallback'
import common  from '@ohos.app.ability.common';
import observer from '@ohos.telephony.observer';
import call from '@ohos.telephony.call';
import appManager from '@ohos.app.ability.appManager';

export class LiteavAudioEventMonitor
{
  private TAG: string = "audio-io";
  private appStateChangeCallback: ApplicationStateChangeCallback = {
    onApplicationForeground: () => {
      Log.info(this.TAG, 'audioevent onAppForeground');
      this.nativeNotifyBackgroundStateChange(0);
    },
    onApplicationBackground: () => {
      Log.info(this.TAG, 'audioevent onAppBackground');
      this.nativeNotifyBackgroundStateChange(1);
    }
  }

  private callStateToString(state: call.CallState): string {
    if (state === call.CallState.CALL_STATE_IDLE) {
      return "Idle";
    } else if (state === call.CallState.CALL_STATE_RINGING) {
      return "Ringing";
    } else if (state === call.CallState.CALL_STATE_OFFHOOK) {
      return "OffHook";
    } else if (state === call.CallState.CALL_STATE_ANSWERED) {
      return "Answered";
    } else {
      return "Unknown" + state.valueOf();
    }
  }

  private callStateChangeCallback: (data: observer.CallStateInfo) => void = (data: observer.CallStateInfo) => {
    Log.info(this.TAG, 'audioevent onCallStateChange to ' + this.callStateToString(data.state));
    this.nativeNotifyTelephoneStateChange(data.state.valueOf());
  }

  nativeStartMonitoring(context: common.ApplicationContext) : void {
    try {
      context.getRunningProcessInformation((err, data: Array<appManager.ProcessInformation>) => {
        if (err) {
          Log.error(this.TAG, "getRunningProcessInformation failed, err: " + JSON.stringify(err));
        } else {
          let background: boolean = (data[0].state === appManager.ProcessState.STATE_BACKGROUND);
          if (background) {
            this.appStateChangeCallback.onApplicationBackground();
          } else {
            this.appStateChangeCallback.onApplicationForeground();
          }
        }
      })
      context.on('applicationStateChange', this.appStateChangeCallback);
    } catch (error) {
      Log.error(this.TAG, "on applicationStateChange callback failed err: " + error);
    }

    try {
      let state = call.getCallStateSync();
      Log.info(this.TAG, 'audioevent onCallStateChange to ' + this.callStateToString(state));
      this.nativeNotifyTelephoneStateChange(state.valueOf());
      observer.on('callStateChange', this.callStateChangeCallback);
    } catch (error) {
      Log.error(this.TAG, "on callStateChange callback failed err: " + error);
    }
  }

  nativeStopMonitoring(context: common.ApplicationContext) : void {
    try {
      context.off('applicationStateChange', this.appStateChangeCallback);
    } catch (error) {
      Log.error(this.TAG, "off applicationStateChange callback failed err:" + error);
    }
    try {
      observer.off('callStateChange', this.callStateChangeCallback);
    } catch (error) {
      Log.error(this.TAG, "off callStateChange callback failed err:", error);
    }
  }

  nativeNotifyBackgroundStateChange(state: number) : void {}
  nativeNotifyTelephoneStateChange(state: number) : void {}
}

