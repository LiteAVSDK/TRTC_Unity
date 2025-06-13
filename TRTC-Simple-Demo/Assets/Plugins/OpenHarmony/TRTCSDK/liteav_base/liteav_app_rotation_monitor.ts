// Copyright (c) 2024 Tencent. All rights reserved.
// Author: finnguan

import { Callback } from '@ohos.base';
import display from '@ohos.display';
import sensor from '@ohos.sensor';
import { LiteavLog as Log } from './liteav_log';

const ORIENTATION_UNKNOWN: number = -1;
const SENSOR_ROTATION_DETECTION_THRESHOLD: number = 30;

export class LiteavAppRotationMonitor {
  private tag = 'AppDisplayMonitor';

  private lastSensorOrientation: number = ORIENTATION_UNKNOWN;
  private sensorRotation: number = 0;
  private displayOrientation: display.Orientation = display.Orientation.PORTRAIT;
  private displayCallback: Callback<number> = (data: number) => {
    this.displayOrientation = display.getDefaultDisplaySync().orientation;
    this.nativeNotifyDisplayOrientationChanged();
  };

  private sensorCallback: Callback<sensor.GravityResponse> = (data: sensor.GravityResponse) => {
    // This calculation method comes from Android.
    let x = data.x;
    let y = data.y;
    let z = data.z;
    let magnitude = x * x + y * y;
    let sensorOrientation: number = 0;
    if (magnitude * 4 >= z * z) {
      let OneEightyOverPi: number = 57.29577957855;
      let angle: number = Math.atan2(y, x) * OneEightyOverPi;
      sensorOrientation = 90 - Math.round(angle);
      // normalize to 0 - 359 range
      while (sensorOrientation >= 360) {
        sensorOrientation -= 360;
      }

      while (sensorOrientation < 0) {
        sensorOrientation += 360;
      }
    }

    if (this.lastSensorOrientation != ORIENTATION_UNKNOWN &&
      Math.abs(sensorOrientation - this.lastSensorOrientation) <=
        SENSOR_ROTATION_DETECTION_THRESHOLD) {
      return;
    }

    this.lastSensorOrientation = sensorOrientation;
    let rotation: number = 0;
    if (sensorOrientation <= 45) {
      rotation = 0;
    } else if (sensorOrientation <= 135) {
      rotation = 90;
    } else if (sensorOrientation <= 225) {
      rotation = 180;
    } else if (sensorOrientation <= 315) {
      rotation = 270;
    }

    if (this.sensorRotation != rotation) {
      this.sensorRotation = rotation;
      this.nativeNotifySensorRotationChanged();
    }
  };

  nativeStart(): void {
    try {
      this.displayOrientation = display.getDefaultDisplaySync().orientation;
      display.on("change", this.displayCallback);
      sensor.on(sensor.SensorId.GRAVITY, this.sensorCallback, { interval: 'ui' });
    } catch (error) {
      Log.error(this.tag, "nativeStart err:" + error);
    }
  }

  nativeStop(): void {
    try {
      display.off("change", this.displayCallback);
      sensor.off(sensor.SensorId.GRAVITY, this.sensorCallback);
    } catch (error) {
      Log.error(this.tag, "nativeStop err:" + error);
    }
  }

  nativeGetCurrentDisplayOrientation(): display.Orientation {
    return this.displayOrientation;
  }

  nativeGetCurrentSensorRotation(): number {
    return this.sensorRotation;
  }

  nativeNotifyDisplayOrientationChanged(): void {
  }

  nativeNotifySensorRotationChanged(): void {
  }
}