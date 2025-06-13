// Copyright (c) 2024 Tencent. All rights reserved.
// Author: kleinjia

import { LiteavLog } from './liteav_log';
import { LiteavSystemInfo } from './liteav_system_info';
import { LiteavAudioRoutingManager } from "./liteav_audio_routing_manager";
import { LiteavAudioEventMonitor } from './liteav_audio_event_monitor';
import { LiteavAudioPermissionRequester } from "./liteav_audio_permission_requester";
import { LiteavAppRotationMonitor } from "./liteav_app_rotation_monitor";
import { Context } from '@ohos.abilityAccessCtrl';
import LiteAVSDKNative from 'libliteavsdk.so';


let classes: Record<string, Function> = {};
registerExtraClass(LiteavLog);
registerExtraClass(LiteavSystemInfo);
registerExtraClass(LiteavAudioRoutingManager);
registerExtraClass(LiteavAudioEventMonitor);
registerExtraClass(LiteavAudioPermissionRequester);
registerExtraClass(LiteavAppRotationMonitor);

export function registerExtraClass(func: Function) {
  classes[func.name] = func;
}

export function initialize(context: Context) {
  if (typeof globalThis.getContext === 'function') {
    let contextFromSystem = globalThis.getContext();
    if (contextFromSystem !== null && contextFromSystem !== undefined) {
      context = contextFromSystem;
    }
  }
  if (context === null || context === undefined) {
    throw new Error("UIAbilityContext or UIExtensionContext is needed to initialize LiteAVSDK");
  }
  if (LiteAVSDKNative != undefined && LiteAVSDKNative != null) {
    LiteAVSDKNative.napiOnLoad(context, classes);
  }
}
