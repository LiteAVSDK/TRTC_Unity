//
//  Copyright © 2022 Tencent. All rights reserved.
//
//  Module: V2TXLive
//

/// @defgroup V2TXLiveProperty_ios V2TXLiveProperty
/// V2TXLive setProperty 支持的 key
///
/// @{
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#define V2PropertyType NSString*

/// 开启/关闭硬件加速【RTMP协议，拉流】
/// 默认值：true
/// Value：true/false
FOUNDATION_EXTERN V2PropertyType kV2EnableHardwareAcceleration;

/// 设置重连次数,【RTMP协议，拉流】
/// 默认值：3
/// Value：int
FOUNDATION_EXTERN V2PropertyType kV2MaxNumberOfReconnection;

/// 设置重连间隔【RTMP协议，拉流】
/// 单位：秒
/// 默认值：3
/// Value：int
FOUNDATION_EXTERN V2PropertyType kV2SecondsBetweenReconnection;

/// 设置自定义编码参数【RTMP/RTC协议，推流】
/// Value：JSON 字符串
/// 例如：
/// ```json
///{
///    "videoWidth":360,
///    "videoHeight":640,
///    "videoFps":15,
///   "videoBitrate":1000,
///   "minVideoBitrate":1000
///}
///```
FOUNDATION_EXTERN V2PropertyType kV2SetVideoQualityEx;

@interface V2TXLiveProperty : NSObject

@end

NS_ASSUME_NONNULL_END
/// @}
