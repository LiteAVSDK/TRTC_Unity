// Copyright (c) 2025 Tencent. All rights reserved.

#import <Foundation/Foundation.h>
#import "TXUGCRecordTypeDef.h"

NS_ASSUME_NONNULL_BEGIN

/// @defgroup TXUGCAudioRecorderListener_ios TXUGCAudioRecorderListener
/// 短视频录制回调定义
/// @{
LITEAV_EXPORT @protocol TXUGCAudioRecorderListener<NSObject>

/**
 * 短视频录制进度
 * @param milliSecond 以毫秒为单位的播放的时间
 */
@optional
- (void)onRecordProgress:(NSInteger)milliSecond;

/**
 * 短视频录制完成
 * @param result 返回码及错误原因
 * @see TXUGCRecordResult
 */
@optional
- (void)onRecordComplete:(TXUGCRecordResult*)result;

@end

/// @}

NS_ASSUME_NONNULL_END
