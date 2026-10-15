// Copyright (c) 2024 Tencent. All rights reserved.
// Author: kleinjia

import { Callback } from '@ohos.base';
import ApplicationStateChangeCallback from '@ohos.app.ability.ApplicationStateChangeCallback'
import common  from '@ohos.app.ability.common';
import { LiteavLog as Log } from './liteav_log';
import appManager from '@ohos.app.ability.appManager';

export class AppStateMonitor {
  private static APP_STATE_UNSET = -1;
  private static APP_STATE_FORGROUND = 0;
  private static APP_STATE_BACKGROUND = 1;

  private static tag = 'AppStateMonitor';
  private static instance: AppStateMonitor;
  private isRunning = false;
  private appContext:common.ApplicationContext | null = null;
  private callback:ApplicationStateChangeCallback | null = null;
  private backgroundState: number = AppStateMonitor.APP_STATE_UNSET;
  private onAppBackgroundStateChanged: Callback<number> | null = null;

  private constructor() {}

  public static getInstance(): AppStateMonitor {
    if (!AppStateMonitor.instance) {
      AppStateMonitor.instance = new AppStateMonitor();
    }
    return AppStateMonitor.instance;
  }

  public on(type: 'onAppBackgroundStateChanged', callback: Callback<number>): void {
    this.onAppBackgroundStateChanged = callback;
  }

  private setAppBackgroundState(backgroundState: number) {
    if (this.backgroundState != backgroundState) {
      this.backgroundState = backgroundState;
      if (this.onAppBackgroundStateChanged) {
        this.onAppBackgroundStateChanged(this.backgroundState);
      }
    }
  }

  public initialize(context: common.ApplicationContext) {
    this.appContext = context;
    this.callback = {
      onApplicationForeground: () => {
        Log.info(AppStateMonitor.tag, 'applicationStateChangeCallback onApplicationForeground');
        this.setAppBackgroundState(AppStateMonitor.APP_STATE_FORGROUND);
      },
      onApplicationBackground: () => {
        Log.info(AppStateMonitor.tag, 'applicationStateChangeCallback onApplicationBackground');
        this.setAppBackgroundState(AppStateMonitor.APP_STATE_BACKGROUND);
      }
    }
  }

  public start(): void {
    if (this.isRunning || !this.appContext || !this.callback) {
      return;
    }
    try {
      this.appContext.getRunningProcessInformation((err, data: Array<appManager.ProcessInformation>) => {
        if (err) {
          Log.error(AppStateMonitor.tag, "getRunningProcessInformation failed, err: " + JSON.stringify(err));
        } else {
          let background: boolean = (data[0].state === appManager.ProcessState.STATE_BACKGROUND);
          if (background) {
            this.callback.onApplicationBackground();
          } else {
            this.callback.onApplicationForeground();
          }
        }
      })
    } catch (error) {
      Log.error(AppStateMonitor.tag, "on applicationStateChange callback failed err: " + error);
    }

    try {
      this.appContext.on('applicationStateChange', this.callback);
      this.isRunning = true;
    } catch (error) {
      Log.error(AppStateMonitor.tag, "on applicationStateChange callback failed err:" + error);
    }
  }

  public stop(): void {
    if (this.isRunning && this.appContext && this.callback) {
      try {
        this.appContext.off('applicationStateChange', this.callback)
        this.isRunning = false;
      } catch (error) {
        Log.error(AppStateMonitor.tag, "off applicationStateChange callback failed err:" + error);
      }
    }
  }

  public getAppBackgroundState(): number {
    return this.backgroundState;
  }
}