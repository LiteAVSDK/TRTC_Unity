/**
 * Copyright (c) 2021 Tencent. All rights reserved.
 * Module:   V2TXLiveProperty @ TXLiteAVSDK
 * Function: V2TXLive setProperty 支持的 key
 */
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#define V2PropertyType NSString*

/// 开启/关闭硬件加速【RTMP协议，拉流】。
/// 默认值：true。
/// Value：true/false。
FOUNDATION_EXTERN V2PropertyType kV2EnableHardwareAcceleration;

/// 设置重连次数,【RTMP协议，拉流】。
/// 默认值：3。
/// Value：int。
FOUNDATION_EXTERN V2PropertyType kV2MaxNumberOfReconnection;

/// 设置重连间隔【RTMP协议，拉流】。
/// 单位：秒。
/// 默认值：3。
/// Value：int。
FOUNDATION_EXTERN V2PropertyType kV2SecondsBetweenReconnection;

/// 设置自定义编码参数【RTMP/RTC协议，推流】。
/// Value：JSON 字符串。
/// 例如：
/// {
///    "videoWidth":360,
///    "videoHeight":640,
///    "videoFps":15,
///    "videoBitrate":1000,
///    "minVideoBitrate":1000
/// }
FOUNDATION_EXTERN V2PropertyType kV2SetVideoQualityEx;

/// 设定播放请求头【FLV，拉流】。
/// Value：JSON 字符串。
/// 例如：
/// {
///    "headers": [
///        {
///            "key": "key1",
///            "value": "value1"
///        },
///        {
///            "key": "key2",
///            "value": "value2"
///        }
///    ]
/// }
FOUNDATION_EXTERN V2PropertyType kV2SetHeaders;

/// 是否清理最后一帧。
/// 默认值：true。
/// Value：true/false。
FOUNDATION_EXTERN V2PropertyType kV2ClearLastImage;

/// 设置推流 Meta 信息【RTMP，推流】。
/// Value：JSON 字符串。
/// 例如：
/// {
///    "metadata": [
///        {
///            "key": "key1",
///            "value": "value1"
///        },
///        {
///            "key": "key2",
///            "value": "value2"
///        }
///    ]
/// }
FOUNDATION_EXTERN V2PropertyType kV2SetMetaData;

/// 开启/关闭 Hevc 编码【RTMP/RTC协议，推流】。
/// 默认值：false。
/// Value：true/false。
FOUNDATION_EXTERN V2PropertyType kV2EnableHevcEncode;

/// 开启/关闭 IP 复用【FLV，拉流】。
/// 默认值：false。
/// Value：true/false。
FOUNDATION_EXTERN V2PropertyType kV2EnableIPMultiplexing;

@interface V2TXLiveProperty : NSObject

@end

NS_ASSUME_NONNULL_END
