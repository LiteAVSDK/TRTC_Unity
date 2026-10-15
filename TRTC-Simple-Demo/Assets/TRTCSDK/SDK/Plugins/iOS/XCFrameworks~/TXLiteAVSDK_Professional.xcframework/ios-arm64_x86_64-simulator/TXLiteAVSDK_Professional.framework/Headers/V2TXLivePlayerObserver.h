/**
 * Copyright (c) 2021 Tencent. All rights reserved.
 * Module:   V2TXLivePlayerObserver @ TXLiteAVSDK
 * Function: Tencent Cloud live player callback notification
 * <H2>Function
 * Player callback notification for Tencent Cloud Live.
 * <H2>Introduce
 * You can receive some callback notifications from the {@link V2TXLivePlayer} player, including player status, playback volume callback, audio and video first frame callback, statistical data, warning and error messages, etc.
 */
#import "V2TXLiveDef.h"

NS_ASSUME_NONNULL_BEGIN

@protocol V2TXLivePlayer;

@protocol V2TXLivePlayerObserver <NSObject>

@optional

/////////////////////////////////////////////////////////////////////////////////
//
//                    Live Player Event Callback
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * live player error notification, which is called back when the player encounters an error
 *
 * @param player    Player object that calls back this notification.
 * @param code      Error code {@link V2TXLiveCode}.
 * @param msg       Error message.
 * @param extraInfo Extended information.
 */
- (void)onError:(id<V2TXLivePlayer>)player code:(V2TXLiveCode)code message:(NSString *)msg extraInfo:(NSDictionary *)extraInfo;

/**
 * live player warning notification
 *
 * @param player    Player object that calls back this notification.
 * @param code      Warning code {@link V2TXLiveCode}.
 * @param msg       Warning message.
 * @param extraInfo Extended information.
 */
- (void)onWarning:(id<V2TXLivePlayer>)player code:(V2TXLiveCode)code message:(NSString *)msg extraInfo:(NSDictionary *)extraInfo;

/**
 * live player resolution change notification
 *
 * @param player    Player object that calls back this notification.
 * @param width     Video width.
 * @param height    Video height.
 */
- (void)onVideoResolutionChanged:(id<V2TXLivePlayer>)player width:(NSInteger)width height:(NSInteger)height;

/**
 * live player has successfully connected to the server notification
 *
 * @param player    Player object that calls back this notification.
 * @param extraInfo Extended information.
 */
- (void)onConnected:(id<V2TXLivePlayer>)player extraInfo:(NSDictionary *)extraInfo;

/**
 * Video playback event
 *
 * @param player    Player object that calls back this notification.
 * @param firstPlay Play for the first time.
 * @param extraInfo Extended information.
 */
- (void)onVideoPlaying:(id<V2TXLivePlayer>)player firstPlay:(BOOL)firstPlay extraInfo:(NSDictionary *)extraInfo;

/**
 * Audio playback event
 *
 * @param player    Player object that calls back this notification.
 * @param firstPlay Play for the first time.
 * @param extraInfo Extended information.
 */
- (void)onAudioPlaying:(id<V2TXLivePlayer>)player firstPlay:(BOOL)firstPlay extraInfo:(NSDictionary *)extraInfo;

/**
 * Video loading event
 *
 * @param player    Player object that calls back this notification.
 * @param extraInfo Extended information.
 */
- (void)onVideoLoading:(id<V2TXLivePlayer>)player extraInfo:(NSDictionary *)extraInfo;

/**
 * Audio loading event
 *
 * @param player    Player object that calls back this notification.
 * @param extraInfo Extended information.
 */
- (void)onAudioLoading:(id<V2TXLivePlayer>)player extraInfo:(NSDictionary *)extraInfo;

/**
 * Player playback volume callback
 *
 * @note  This callback notification is received after {@link enableVolumeEvaluation} is called to enable playback volume display.
 * @param player Player object that calls back this notification.
 * @param volume Current playback volume.
 */
- (void)onPlayoutVolumeUpdate:(id<V2TXLivePlayer>)player volume:(NSInteger)volume;

/**
 * Live player statistics callback
 *
 * @param player     Player object that calls back this notification.
 * @param statistics Player statistics {@link V2TXLivePlayerStatistics}.
 */
- (void)onStatisticsUpdate:(id<V2TXLivePlayer>)player statistics:(V2TXLivePlayerStatistics *)statistics;

/**
 * Screenshot callback
 *
 * @note  This callback notification is received after {@link snapshot} is called to snapshot.
 * @param player Player object that calls back this notification.
 * @param image  Captured video image.
 */
- (void)onSnapshotComplete:(id<V2TXLivePlayer>)player image:(nullable TXImage *)image;

/**
 * Custom video rendering callback
 *
 * @note  Need you call {@link enableObserveVideoFrame} to turn on the callback switch.
 * @param player     Player object that calls back this notification.
 * @param videoFrame Video frame data {@link V2TXLiveVideoFrame}.
 */
- (void)onRenderVideoFrame:(id<V2TXLivePlayer>)player frame:(V2TXLiveVideoFrame *)videoFrame;

/**
 * Audio Data callback
 *
 * @note  Need you call {@link enableObserveAudioFrame} to turn on the callback switch. Please use the data of audioFrame in the current callback.
 * @param player     Player object that calls back this notification.
 * @param aduioFrame Audio frame data {@link V2TXLiveAudioFrame}.
 */
- (void)onPlayoutAudioFrame:(id<V2TXLivePlayer>)player frame:(V2TXLiveAudioFrame *)audioFrame;

/**
 * Callback of receiving an SEI message. The sender calls `sendSeiMessage` in {@link V2TXLivePusher} to send an SEI
 * message
 *
 * @note You will receive this callback after calling `enableReceiveSeiMessage` in {@link V2TXLivePlayer} to enable the receiving of SEI.
 * @param player         Player object that calls back this notification.
 * @param payloadType    The payload type of the received SEI message.
 * @param data           sei message data.
 */
- (void)onReceiveSeiMessage:(id<V2TXLivePlayer>)player payloadType:(int)payloadType data:(NSData *)data;

/**
 * Resolution stream switch callback
 *
 * @note  This callback notification is received after {@link switchStream} is called to switch stream.
 * @param player Player object that calls back this notification.
 * @param code   Status code, 0:success, -1:timeout, -2:failed, server error, -3:failed, client error.
 * @param url    Switched playback address.
 */
- (void)onStreamSwitched:(id<V2TXLivePlayer>)player url:(NSString *)url code:(NSInteger)code;

/**
 * Picture-in-Picture state change callback
 *
 * @note  This callback notification is received after {@link enablePictureInPicture} is called to enable Picture-in-Picture.
 * @param player    Player object that calls back this notification.
 * @param state     Picture-in-Picture state。
 * @param extraInfo Extended information.
 */
- (void)onPictureInPictureStateUpdate:(id<V2TXLivePlayer>)player state:(V2TXLivePictureInPictureState)state message:(NSString *)msg extraInfo:(NSDictionary *)extraInfo;

/**
 * The SDK returns this callback when you call {@link startLocalRecording} to start local recording.
 * Notify whether the recording task has started successfully.
 *
 * @param player Player object that calls back this notification.
 * @param code status.
 *               -  0: successful.
 *               - -1: failed.
 *               - -2: unsupported format.
 *               - -6: recording has been started. Stop recording first.
 *               - -7: recording file already exists and needs to be deleted.
 *               - -8: recording directory does not have the write permission. Please check the directory permission.
 * @param storagePath recording filePath.
 */
- (void)onLocalRecordBegin:(id<V2TXLivePlayer>)player errCode:(NSInteger)errCode storagePath:(NSString *)storagePath;

/**
 * The SDK returns this callback when you call {@link startLocalRecording} to start local recording, which means recording task in progress.
 * The SDK returns this callback at a certain interval, [Default]: Do not returns this callback.
 * You can set a callback interval when {@link startLocalRecording}.
 *
 * @param player Player object that calls back this notification.
 * @param durationMs   recording duration.
 * @param storagePath  recording filePath.
 */
- (void)onLocalRecording:(id<V2TXLivePlayer>)player durationMs:(NSInteger)durationMs storagePath:(NSString *)storagePath;

/**
 * The SDK returns this callback when you call {@link stopLocalRecording} to start local recording.
 * Notify whether the recording task has stopped successfully.
 *
 * @param player Player object that calls back this notification.
 * @param code status
 *               -  0: successful.
 *               - -1: failed.
 *               - -2: Switching resolution or horizontal and vertical screen causes the recording to stop.
 *               - -3: recording duration is too short or no video or audio data is received. Check the recording duration or whether audio or video capture is enabled.
 * @param storagePath recording filePath.
 */
- (void)onLocalRecordComplete:(id<V2TXLivePlayer>)player errCode:(NSInteger)errCode storagePath:(NSString *)storagePath;

@end

NS_ASSUME_NONNULL_END
