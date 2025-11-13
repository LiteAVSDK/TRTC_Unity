// Copyright (c) 2024 Tencent. All rights reserved.
// Author: kleinjia

import util from '@ohos.util';
import hilog from '@ohos.hilog';

export class LiteavLog {
  private static LOG_LEVEL_DEBUG = 1;
  private static LOG_LEVEL_INFO = 2;
  private static LOG_LEVEL_WARN = 3;
  private static LOG_LEVEL_ERROR = 4;
  private static LOG_LEVEL_FATAL = 5;

  public static debug(tag: string, messageTemplate: string, ...args: Object[]): void {
    const formattedMessage = util.format(messageTemplate, ...args);
    this.nativeWriteLogToNative(LiteavLog.LOG_LEVEL_DEBUG, tag, formattedMessage);
  }

  public static info(tag: string, messageTemplate: string, ...args: Object[]): void {
    const formattedMessage = util.format(messageTemplate, ...args);
    this.nativeWriteLogToNative(LiteavLog.LOG_LEVEL_INFO, tag, formattedMessage);
  }

  public static warn(tag: string, messageTemplate: string, ...args: Object[]): void {
    const formattedMessage = util.format(messageTemplate, ...args);
    this.nativeWriteLogToNative(LiteavLog.LOG_LEVEL_WARN, tag, formattedMessage);
  }

  public static error(tag: string, messageTemplate: string, ...args: Object[]): void {
    const formattedMessage = util.format(messageTemplate, ...args);
    this.nativeWriteLogToNative(LiteavLog.LOG_LEVEL_ERROR, tag, formattedMessage);
  }

  public static fatal(tag: string, messageTemplate: string, ...args:Object[]): void {
    const formattedMessage = util.format(messageTemplate, ...args);
    this.nativeWriteLogToNative(LiteavLog.LOG_LEVEL_FATAL, tag, formattedMessage);
  }

  static nativeWriteLogToNative(level: number, tag: string, message: string) : void {
    if (level === LiteavLog.LOG_LEVEL_DEBUG) {
      hilog.debug(0, tag, message);
    } else if (level === LiteavLog.LOG_LEVEL_INFO) {
      hilog.info(0, tag, message);
    } else if (level === LiteavLog.LOG_LEVEL_WARN) {
      hilog.warn(0, tag, message);
    } else if (level === LiteavLog.LOG_LEVEL_ERROR) {
      hilog.error(0, tag, message);
    } else if (level === LiteavLog.LOG_LEVEL_FATAL) {
      hilog.fatal(0, tag, message);
    }
  }
}