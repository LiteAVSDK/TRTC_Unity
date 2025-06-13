// Copyright (c) 2023 Tencent. All rights reserved.
// Author: felixyyan
using UnityEngine;
using System.IO;
using System.Runtime.CompilerServices;

namespace trtc {
  public static class TRTCLogger
  {
    public static void Info(string message, 
                            [CallerFilePath] string filePath = "",
                            [CallerLineNumber] int lineNumber = 0)
    {
      Log(TRTCLogWriteLevel.logInfo, message, filePath, lineNumber);
    }

    public static void Warning(string message,
                              [CallerFilePath] string filePath = "",
                              [CallerLineNumber] int lineNumber = 0)
    {
      Log(TRTCLogWriteLevel.logWarning, message, filePath, lineNumber);
    }

    public static void Error(string message,
                            [CallerFilePath] string filePath = "",
                            [CallerLineNumber] int lineNumber = 0)
    {
      Log(TRTCLogWriteLevel.logError, message, filePath, lineNumber);
    }

    public static void Fatal(string message,
                            [CallerFilePath] string filePath = "",
                            [CallerLineNumber] int lineNumber = 0)
    {
      Log(TRTCLogWriteLevel.logFatal, message, filePath, lineNumber);
    }

    private static void Log(TRTCLogWriteLevel log_write_level,
                            string message,
                            string filePath,
                            int lineNumber)
    {
      string normalizedFilePath = filePath.Replace('\\', '/');
      string fileName = Path.GetFileName(normalizedFilePath);
      string fileNameAndLine = fileName + ":" + lineNumber.ToString();
      TRTCCloudNative.trtc_cloud_write_log(log_write_level, fileNameAndLine, "unity", message);
    }
}
}