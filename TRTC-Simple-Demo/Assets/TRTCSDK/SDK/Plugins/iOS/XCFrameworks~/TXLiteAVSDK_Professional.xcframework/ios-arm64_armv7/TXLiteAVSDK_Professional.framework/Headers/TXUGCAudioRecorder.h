// Copyright (c) 2025 Tencent. All rights reserved.

#import <AVFoundation/AVFoundation.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "TXUGCAudioRecorderListener.h"
#import "TXUGCRecordTypeDef.h"

NS_ASSUME_NONNULL_BEGIN

/// @defgroup TXUGCRecorder_ios TXUGCAudioRecorder
/// 短视频录制类
/// @{
LITEAV_EXPORT @interface TXUGCAudioRecorder : NSObject

/// 音频录制的委托对象
/// @see TXUGCAudioRecorderListener
@property(nonatomic, weak) id<TXUGCAudioRecorderListener> recordDelegate;

/// @name 实例化

/// 获取单例
+ (TXUGCAudioRecorder *)shareInstance;

/**
  开始录制音频
 */
- (TXUGCStartAudioRecordResultCode)startRecord:(NSString *)videoPath
                                        config:(TXUGCAudioConfig *)config;

/**
 * 结束录制短视频
 */
- (int)stopRecord;

@end
/// @}

NS_ASSUME_NONNULL_END
