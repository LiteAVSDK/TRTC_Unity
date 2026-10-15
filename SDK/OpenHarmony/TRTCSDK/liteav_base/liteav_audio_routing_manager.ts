// Copyright (c) 2024 Tencent. All rights reserved.
// Author: garyzeng

import audio from '@ohos.multimedia.audio';
import { BusinessError } from "@ohos.base";
import { LiteavLog as Log } from "./liteav_log"

export class LiteavAudioRoutingManager
{
  private TAG: string = "audio-io";

  nativeGetOutputDevices() : Array<audio.DeviceType> {
    let return_device_list = new Array<audio.DeviceType>();

    let audioRoutingManager = audio.getAudioManager().getRoutingManager();
    let devices = audioRoutingManager.getDevicesSync(audio.DeviceFlag.OUTPUT_DEVICES_FLAG);
    for (const device of devices) {
      return_device_list.push(device.deviceType);
    }
    return return_device_list;
  }

  nativeGetCurrentOutputDevice() : audio.DeviceType {
    let deviceType: audio.DeviceType = audio.DeviceType.INVALID;
    let audioUsage: audio.StreamUsage = this.nativeGetTrackedAudioUsage();
    try {
      let data = audio.getAudioManager().getRoutingManager().getPreferredOutputDeviceForRendererInfoSync({
        usage: audioUsage,
        rendererFlags: 0
      });
      deviceType = data[0].deviceType;
    } catch (err) {
      Log.error(this.TAG, "Failed to getCurrentOutputDevice " + err);
    }
    return deviceType;
  }

  nativeGetAudioScene() : audio.AudioScene {
    return audio.getAudioManager().getAudioSceneSync();
  }

  nativeCheckAudioSceneUpdate() : void {
    let audioScene = audio.getAudioManager().getAudioSceneSync();
    if (audioScene != this.audioScene) {
      Log.info(this.TAG, "NotifyAudioSceneChange from[" + this.audioScene.toString() + "] to[" + audioScene.toString() + "]");
      this.audioScene = audioScene;
      this.nativeNotifyAudioSceneChange();
    }
  }

  nativeStartMonitoring() : void {
    this.nativeCheckAudioSceneUpdate();
    this.intervalId = setInterval(() => {
      this.nativeCheckAudioSceneUpdate();
    }, 2000);

    this.nativeNotifyTrackedAudioUsageChange();
  }

  nativeStopMonitoring() : void {
    clearInterval(this.intervalId);
    this.intervalId = undefined;

    let audioRoutingManager = audio.getAudioManager().getRoutingManager();
    audioRoutingManager.off('preferOutputDeviceChangeForRendererInfo', this.onPreferOutputDeviceChangeForRendererInfo);
  }

  nativeNotifyTrackedAudioUsageChange(): void {
    let audioRoutingManager = audio.getAudioManager().getRoutingManager();
    audioRoutingManager.off('preferOutputDeviceChangeForRendererInfo', this.onPreferOutputDeviceChangeForRendererInfo);
    audioRoutingManager.on('preferOutputDeviceChangeForRendererInfo', {
      usage: this.nativeGetTrackedAudioUsage(),
      rendererFlags: 0
    }, this.onPreferOutputDeviceChangeForRendererInfo);

    this.onPreferOutputDeviceChangeForRendererInfo();
  }

  private onPreferOutputDeviceChangeForRendererInfo = () => {
    this.nativeNotifyPreferredOutputDeviceChange();
  };

  nativeNotifyAudioSceneChange() : void {}
  nativeNotifyPreferredOutputDeviceChange() : void {}
  nativeGetTrackedAudioUsage() : audio.StreamUsage { return audio.StreamUsage.STREAM_USAGE_UNKNOWN; }

  private audioScene: audio.AudioScene = audio.getAudioManager().getAudioSceneSync();
  private intervalId: number | undefined = undefined;
}

