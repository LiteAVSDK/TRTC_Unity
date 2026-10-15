// Copyright (c) 2026 Tencent. All rights reserved.
// Author: binderli

import audio from '@ohos.multimedia.audio';
import { BusinessError } from '@ohos.base';
import deviceInfo from '@ohos.deviceInfo';
import { LiteavLog as Log } from "./liteav_log"

export class LiteavAudioHardwareEarMonitor {


  nativeIsAudioLoopbackSupported(): boolean {
    return false;
  }

  nativeCreateAudioLoopback(): void {
  }




  nativeStartEarMonitor(): void {
  }


  nativeStopEarMonitor(): void {
  }


  nativeSetEarMonitorVolume(volume: number) {
  }

  nativeSetReverbPreset(preset: number) {
  }

  nativeSetEqualizerPreset(preset: number) {
  }



}