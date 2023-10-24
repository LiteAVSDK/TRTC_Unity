/**
 * Copyright (c) 2021 Tencent. All rights reserved.
 * Module:   V2TXLivePlayerObserver @ TXLiteAVSDK
 * Function: 腾讯云直播的播放器回调通知
 * <H2>功能
 * 腾讯云直播的播放器回调通知。
 * <H2>介绍
 * 可以接收 {@link V2TXLivePlayer} 播放器的一些回调通知，包括播放器状态、播放音量回调、音视频首帧回调、统计数据、警告和错误信息等。
 */
#import "V2TXLiveDef.h"

NS_ASSUME_NONNULL_BEGIN

@protocol V2TXLivePlayer;

@protocol V2TXLivePlayerObserver <NSObject>

@optional

/////////////////////////////////////////////////////////////////////////////////
//
//                   直播播放器事件回调
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 直播播放器错误通知，播放器出现错误时，会回调该通知
 *
 * @param player    回调该通知的播放器对象。
 * @param code      错误码 {@link V2TXLiveCode}。
 * @param msg       错误信息。
 * @param extraInfo 扩展信息。
 */
- (void)onError:(id<V2TXLivePlayer>)player code:(V2TXLiveCode)code message:(NSString *)msg extraInfo:(NSDictionary *)extraInfo;

/**
 * 直播播放器警告通知
 *
 * @param player    回调该通知的播放器对象。
 * @param code      警告码 {@link V2TXLiveCode}。
 * @param msg       警告信息。
 * @param extraInfo 扩展信息。
 */
- (void)onWarning:(id<V2TXLivePlayer>)player code:(V2TXLiveCode)code message:(NSString *)msg extraInfo:(NSDictionary *)extraInfo;

/**
 * 直播播放器分辨率变化通知
 *
 * @param player    回调该通知的播放器对象。
 * @param width     视频宽。
 * @param height    视频高。
 */
- (void)onVideoResolutionChanged:(id<V2TXLivePlayer>)player width:(NSInteger)width height:(NSInteger)height;

/**
 * 已经成功连接到服务器
 *
 * @param player    回调该通知的播放器对象。
 * @param extraInfo 扩展信息。
 */
- (void)onConnected:(id<V2TXLivePlayer>)player extraInfo:(NSDictionary *)extraInfo;

/**
 * 视频播放事件
 *
 * @param player    回调该通知的播放器对象。
 * @param firstPlay 第一次播放标志。
 * @param extraInfo 扩展信息。
 */
- (void)onVideoPlaying:(id<V2TXLivePlayer>)player firstPlay:(BOOL)firstPlay extraInfo:(NSDictionary *)extraInfo;

/**
 * 音频播放事件
 *
 * @param player    回调该通知的播放器对象。
 * @param firstPlay 第一次播放标志。
 * @param extraInfo 扩展信息。
 */
- (void)onAudioPlaying:(id<V2TXLivePlayer>)player firstPlay:(BOOL)firstPlay extraInfo:(NSDictionary *)extraInfo;

/**
 * 视频加载事件
 *
 * @param player    回调该通知的播放器对象。
 * @param extraInfo 扩展信息。
 */
- (void)onVideoLoading:(id<V2TXLivePlayer>)player extraInfo:(NSDictionary *)extraInfo;

/**
 * 音频加载事件
 *
 * @param player    回调该通知的播放器对象。
 * @param extraInfo 扩展信息。
 */
- (void)onAudioLoading:(id<V2TXLivePlayer>)player extraInfo:(NSDictionary *)extraInfo;

/**
 * 播放器音量大小回调
 *
 * @param player 回调该通知的播放器对象。
 * @param volume 音量大小。
 * @note  调用 {@link enableVolumeEvaluation} 开启播放音量大小提示之后，会收到这个回调通知。
 */
- (void)onPlayoutVolumeUpdate:(id<V2TXLivePlayer>)player volume:(NSInteger)volume;

/**
 * 直播播放器统计数据回调
 *
 * @param player     回调该通知的播放器对象。
 * @param statistics 播放器统计数据 {@link V2TXLivePlayerStatistics}。
 */
- (void)onStatisticsUpdate:(id<V2TXLivePlayer>)player statistics:(V2TXLivePlayerStatistics *)statistics;

/**
 * 截图回调
 *
 * @note  调用 {@link snapshot} 截图之后，会收到这个回调通知。
 * @param player 回调该通知的播放器对象。
 * @param image  已截取的视频画面。
 */
- (void)onSnapshotComplete:(id<V2TXLivePlayer>)player image:(nullable TXImage *)image;

/**
 * 自定义视频渲染回调
 *
 * @param player     回调该通知的播放器对象。
 * @param videoFrame 视频帧数据 {@link V2TXLiveVideoFrame}。
 * @note  需要您调用 {@link enableObserveVideoFrame} 开启回调开关。
 */
- (void)onRenderVideoFrame:(id<V2TXLivePlayer>)player frame:(V2TXLiveVideoFrame *)videoFrame;

/**
 * 音频数据回调
 *
 * @param player     回调该通知的播放器对象。
 * @param audioFrame 音频帧数据 {@link V2TXLiveAudioFrame}。
 * @note  需要您调用 {@link enableObserveAudioFrame} 开启回调开关。请在当前回调中使用 audioFrame 的 data。
 */
- (void)onPlayoutAudioFrame:(id<V2TXLivePlayer>)player frame:(V2TXLiveAudioFrame *)audioFrame;

/**
 * 收到 SEI 消息的回调，发送端通过 {@link V2TXLivePusher} 中的 `sendSeiMessage` 来发送 SEI 消息
 *
 * @note  调用 {@link V2TXLivePlayer} 中的 `enableReceiveSeiMessage` 开启接收 SEI 消息之后，会收到这个回调通知。
 * @param player         回调该通知的播放器对象。
 * @param payloadType    回调数据的SEI payloadType。
 * @param data           数据。
 */
- (void)onReceiveSeiMessage:(id<V2TXLivePlayer>)player payloadType:(int)payloadType data:(NSData *)data;

/**
 * 分辨率无缝切换回调
 *
 * @note  调用 {@link V2TXLivePlayer} 中的 `switchStream` 切换分辨率，会收到这个回调通知。
 * @param player 回调该通知的播放器对象。
 * @param url    切换的播放地址。
 * @param code   状态码，0：成功，-1：切换超时，-2：切换失败，服务端错误，-3：切换失败，客户端错误。
 */
- (void)onStreamSwitched:(id<V2TXLivePlayer>)player url:(NSString *)url code:(NSInteger)code;

/**
 * 画中画状态变更回调
 *
 * @note  调用 {@link V2TXLivePlayer} 中的 `enablePictureInPicture` 开启画中画之后，会收到这个回调通知。
 * @param player    回调该通知的播放器对象。
 * @param state     画中画的状态。
 * @param extraInfo 扩展信息。
 */
- (void)onPictureInPictureStateUpdate:(id<V2TXLivePlayer>)player state:(V2TXLivePictureInPictureState)state message:(NSString *)msg extraInfo:(NSDictionary *)extraInfo;

@end

NS_ASSUME_NONNULL_END
