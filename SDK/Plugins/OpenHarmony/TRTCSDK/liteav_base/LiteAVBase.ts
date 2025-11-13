import LiteAVSDKNative from 'libliteavsdk.so';
import { Context } from '@ohos.abilityAccessCtrl';
import * as LiteavBase from './liteav_module_entry';

export class LiteAVBase {
  public static setGlobalEnv(envConfig: string): void {
    return LiteAVSDKNative.LiteAVBase.setGlobalEnv(envConfig);
  }

  public static setContext(context: Context): void {
    return LiteavBase.initialize(context);
  }
}
