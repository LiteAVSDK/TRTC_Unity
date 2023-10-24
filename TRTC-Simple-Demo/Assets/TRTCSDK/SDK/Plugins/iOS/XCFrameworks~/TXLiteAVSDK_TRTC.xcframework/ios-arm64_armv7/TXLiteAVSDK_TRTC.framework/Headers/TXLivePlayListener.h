/**
 * Copyright (c) 2021 Tencent. All rights reserved.
 * Module:   TXLivePlayListener @ TXLiteAVSDK
 * Function: 腾讯云直播播放的回调通知
 */
#import <Foundation/Foundation.h>
#import "TXLiveSDKTypeDef.h"

@protocol TXLivePlayListener <NSObject>

/**
 * 直播事件通知
 * @param EvtID 参见 TXLiveSDKEventDef.h。
 * @param param 参见 TXLiveSDKTypeDef.h。
 */
- (void)onPlayEvent:(int)evtID withParam:(NSDictionary *)param;

/**
 * 网络状态通知
 * @param param 参见 TXLiveSDKTypeDef.h。
 */
- (void)onNetStatus:(NSDictionary *)param;

@end
