import { Context } from '@ohos.abilityAccessCtrl';
import * as LiteavBase from './liteav_module_entry';

export class LiteAVBase {
  public static setContext(context: Context): void {
    return LiteavBase.initialize(context);
  }
}
