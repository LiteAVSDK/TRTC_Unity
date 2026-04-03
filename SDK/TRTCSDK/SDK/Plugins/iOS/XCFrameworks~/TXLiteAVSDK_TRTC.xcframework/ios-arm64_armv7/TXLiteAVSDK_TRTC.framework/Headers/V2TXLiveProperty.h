/**
 * Copyright (c) 2021 Tencent. All rights reserved.
 * Module:   V2TXLiveProperty @ TXLiteAVSDK
 * Function: Keys supported by V2TXLive setProperty
 */
#import <Foundation/Foundation.h>
#import "TXLiteAVSymbolExport.h"

NS_ASSUME_NONNULL_BEGIN

#define V2PropertyType NSString*

///  Enable/Disable hardware acceleration[RTMP, Player].
/// Default value: true.
/// Value: true/false.
LITEAV_EXPORT FOUNDATION_EXTERN V2PropertyType kV2EnableHardwareAcceleration;

///  Set the number of reconnections[RTMP, Player].
/// Default value: 3.
/// Value: int.
LITEAV_EXPORT FOUNDATION_EXTERN V2PropertyType kV2MaxNumberOfReconnection;

///  Set reconnection interval[RTMP, Player].
/// Unit: second.
/// Default value: 3.
/// Value: int.
LITEAV_EXPORT FOUNDATION_EXTERN V2PropertyType kV2SecondsBetweenReconnection;

///  Set custom encoding parameters[RTMP/RTC，Pusher].
/// Value: JSON string.
/// Example:
///    {
///        "videoWidth":360,
///        "videoHeight":640,
///        "videoFps":15,
///        "videoBitrate":1000,
///        "minVideoBitrate":1000
///    }
LITEAV_EXPORT FOUNDATION_EXTERN V2PropertyType kV2SetVideoQualityEx;

///  Set play request headers[FLV，Player].
/// Value：JSON string.
/// Example:
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
LITEAV_EXPORT FOUNDATION_EXTERN V2PropertyType kV2SetHeaders;

///  Enable/Disable clear the last image.
/// Default value: true.
/// Value: true/false.
LITEAV_EXPORT FOUNDATION_EXTERN V2PropertyType kV2ClearLastImage;

///  Set Push Meta Info[RTMP, Pusher].
/// Value：JSON string.
/// Example:
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
LITEAV_EXPORT FOUNDATION_EXTERN V2PropertyType kV2SetMetaData;

///  Enable/Disable Hevc Encode[RTMP/RTC, Pusher].
/// Default value: false.
/// Value: true/false.
LITEAV_EXPORT FOUNDATION_EXTERN V2PropertyType kV2EnableHevcEncode;

///  Enable/Disable IP Multiplexing[FLV，Player].
/// Default value: false.
/// Value: true/false.
LITEAV_EXPORT FOUNDATION_EXTERN V2PropertyType kV2EnableIPMultiplexing;

@interface V2TXLiveProperty : NSObject

@end

NS_ASSUME_NONNULL_END
