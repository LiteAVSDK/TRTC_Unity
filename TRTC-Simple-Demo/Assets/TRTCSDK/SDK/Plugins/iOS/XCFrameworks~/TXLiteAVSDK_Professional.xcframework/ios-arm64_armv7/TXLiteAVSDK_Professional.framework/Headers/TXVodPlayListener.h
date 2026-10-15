//
// Copyright (c) 2021 Tencent. All rights reserved.

#import <Foundation/Foundation.h>
#import "TXLiveSDKTypeDef.h"
#import "TXVodSDKEventDef.h"
#import "TXVodDef.h"

/////////////////////////////////////////////////////////////////////////////////
//
//                      VOD callback
//
/////////////////////////////////////////////////////////////////////////////////

@class TXVodPlayer;
@protocol TXVodPlayListener <NSObject>

/**
 * vod play event call-back
 */
@required

- (void)onPlayEvent:(TXVodPlayer *)player event:(int)EvtID withParam:(NSDictionary *)param;

/**
 * vod net status call-back
 */
@optional

- (void)onNetStatus:(TXVodPlayer *)player withParam:(NSDictionary *)param;

/**
 * vod Picture-In-Picture call-back
 */
- (void)onPlayer:(TXVodPlayer *)player pictureInPictureStateDidChange:(TX_VOD_PLAYER_PIP_STATE)pipState withParam:(NSDictionary *)param;

/**
 * vod Picture-In-Picture error call-back
 */
- (void)onPlayer:(TXVodPlayer *)player pictureInPictureErrorDidOccur:(TX_VOD_PLAYER_PIP_ERROR_TYPE)errorType withParam:(NSDictionary *)param;

/**
 * vod avplayer airPlay call-back (Only AVPlayer is supported)
 */
- (void)onPlayer:(TXVodPlayer *)player airPlayStateDidChange:(TX_VOD_PLAYER_AIRPLAY_STATE)airPlayState withParam:(NSDictionary *)param;

/**
 * vod avplayer airPlay  error call-back (Only AVPlayer is supported)
 */
- (void)onPlayer:(TXVodPlayer *)player airPlayErrorDidOccur:(TX_VOD_PLAYER_AIRPLAY_ERROR_TYPE)errorType withParam:(NSDictionary *)param;

/**
 * Subtitle data callback
 *
 * @param player  Current player object
 * @param subtitleData  Subtitle data, see the TXVodDef.h file for details
 */
- (void)onPlayer:(TXVodPlayer *)player subtitleData:(TXVodSubtitleData *)subtitleData;

/**
 * Audio frame data callback
 *
 * @param player Current player object
 * @param subtitleData Audio frame data, see TXVodDef.h file for details
 */
- (void)onPlayer:(TXVodPlayer *)player audioFrameData:(TXVodAudioFrameData *)audioFrameData;

@end
