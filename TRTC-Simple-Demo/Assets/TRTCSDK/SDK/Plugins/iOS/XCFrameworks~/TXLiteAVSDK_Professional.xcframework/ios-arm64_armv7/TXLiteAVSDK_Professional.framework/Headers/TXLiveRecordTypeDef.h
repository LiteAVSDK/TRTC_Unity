// Copyright (c) 2021 Tencent. All rights reserved.

#import <Foundation/Foundation.h>
#import "TXLiveSDKTypeDef.h"

/// PlayRecord 录制类型定义。
typedef NS_ENUM(NSInteger, TXRecordType) {
  /// 视频源为正在播放的视频流。
  RECORD_TYPE_STREAM_SOURCE = 1,
};

/// 录制结果错误码定义。
typedef NS_ENUM(NSInteger, TXRecordResultCode) {
  /// 录制成功（业务层主动结束录制）。
  RECORD_RESULT_OK = 0,
  /// 录制成功（ sdk 自动结束录制，可能原因：1，app 进入后台，2，app 被闹钟或电话打断，3，网络断连接）。
  RECORD_RESULT_OK_INTERRUPT = 1,
  /// 录制失败。
  RECORD_RESULT_FAILED = 1001,
};

/// 录制结果。
LITEAV_EXPORT @interface TXRecordResult : NSObject
/// 错误码。
@property(nonatomic, assign) TXRecordResultCode retCode;
/// 错误描述信息。
@property(nonatomic, strong) NSString* descMsg;
/// 视频文件 path。
@property(nonatomic, strong) NSString* videoPath;
/// 视频封面。
@property(nonatomic, strong) TXImage* coverImage;
@end
