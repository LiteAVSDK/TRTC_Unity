/**
 * Copyright (c) 2021 Tencent. All rights reserved.
 * Module:   V2TXLivePlayer @ TXLiteAVSDK
 * Function: Tencent Cloud live player
 * <H2>Function
 * Tencent Cloud Live Player.
 * It is mainly responsible for pulling audio and video data from the specified live stream address, decoding and rendering locally.
 * <H2>Introduce
 * The player includes the following capabilities:
 * - Support RTMP, HTTP-FLV, HLS, TRTC, WebRTC protocols.
 * - Screen capture, you can capture the video screen of the current live stream.
 * - Delay adjustment, you can set the minimum and maximum time for automatic adjustment of the player cache.
 * - Customized video data processing, you can process the video data in the live stream according to the needs of the project, and then render and play it.
 */
#import "V2TXLivePlayerObserver.h"
#import "TXLiteAVSymbolExport.h"

@protocol V2TXLivePlayer <NSObject>

/////////////////////////////////////////////////////////////////////////////////
//
//                   V2TXLivePlayer Interface
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * Sets the player callback
 *
 * By setting the callback, you can listen to some callback events of V2TXLivePlayer,
 * including the player status, playback volume callback, first frame audio/video callback, statistics, warnings, and error messages.
 * @param observer Callback target of the player. For more information, see {@link V2TXLivePlayerObserver}.
 */
- (void)setObserver:(id<V2TXLivePlayerObserver>)observer;

/**
 * Sets the rendering view of the player. This control is responsible for presenting the video content
 *
 * @param view Player rendering view.
 * @return Return code {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 */
- (V2TXLiveCode)setRenderView:(TXView *)view;

/**
 * Sets the rotation angle of the player view
 *
 * @param rotation Rotation angle of the view {@link V2TXLiveRotation}.
 *         - V2TXLiveRotation0 **Default**: 0 degrees, which means the view is not rotated.
 *         - V2TXLiveRotation90:  rotate 90 degrees clockwise.
 *         - V2TXLiveRotation180: rotate 180 degrees clockwise.
 *         - V2TXLiveRotation270: rotate 270 degrees clockwise.
 * @return Return code {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 */
- (V2TXLiveCode)setRenderRotation:(V2TXLiveRotation)rotation;

/**
 * Sets the fill mode of the view
 *
 * @param mode Fill mode of the view {@link V2TXLiveFillMode}.
 *         - V2TXLiveFillModeFill: **Default**: fill the screen with the image without leaving any black edges. If the aspect ratio of the view is different from that of the screen, part of the view will be cropped.
 *         - V2TXLiveFillModeFit  make the view fit the screen without cropping. If the aspect ratio of the view is different from that of the screen, black edges will appear.
 *         - V2TXLiveFillModeScaleFill  fill the screen with the stretched image, thus the length and width may not change proportionally.
 * @return Return code {@link V2TXLiveCode}
 *         - V2TXLIVE_OK: successful
 */
- (V2TXLiveCode)setRenderFillMode:(V2TXLiveFillMode)mode;

/**
 * Sets the mirror mode of the player view
 *
 * If you turn on this switch, You can watch the video in the mirror mode.
 * @param enable Whether to enable the mirror mode of the player view. **Default**: NO.
 * @return Return code {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 */
- (V2TXLiveCode)setRenderMirrorMode:(bool)enable;

/**
 * Starts playing the audio and video streams
 *
 * @note Starting from version 10.7, the Licence needs to be set through {@link setLicence} or {@link setLicence} before it can be played successfully, otherwise the playback will fail (black screen), and it can only be set once globally. Live
 * Licence, UGC Licence, and Player Licence can all be used. If you have not obtained the above Licence, you can  [purchase](https://www.tencentcloud.com/document/product/1071/38546) the official licence.
 * @param url URL of the audio and video streams to be played. The RTMP, HTTP-FLV and TRTC streaming protocols are supported.
 * @return Return code {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: operation succeeded. The player starts connecting to the URL and playing the audio and video streams.
 *         - V2TXLIVE_ERROR_INVALID_PARAMETER: operation failed. The URL is invalid.
 *         - V2TXLIVE_ERROR_REFUSED: operation failed. Duplicate streamId, please ensure that no other player or pusher is using this streamId now.
 *         - V2TXLIVE_ERROR_INVALID_LICENSE: The licence is invalid and the playback fails.
 */
- (V2TXLiveCode)startLivePlay:(NSString *)url;

/**
 * Stops playing the audio and video streams
 *
 * @return Return code {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 */
- (V2TXLiveCode)stopPlay;

/**
 * Indicates whether the player is playing the audio and video streams
 *
 * @return Indicates whether the player is playing the audio and video streams.
 *         - 1: yes.
 *         - 0: no.
 */
- (int)isPlaying;

/**
 * Pauses the audio stream of the player
 *
 * @return Return code {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 */
- (V2TXLiveCode)pauseAudio;

/**
 * Resumes the audio stream of the player
 *
 * @return Return code {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 */
- (V2TXLiveCode)resumeAudio;

/**
 * Pauses the video stream of the player
 *
 * @return Return code {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 */
- (V2TXLiveCode)pauseVideo;

/**
 * Resumes the video stream of the player
 *
 * @return Return code {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 */
- (V2TXLiveCode)resumeVideo;

/**
 * Sets the volume
 *
 * @param volume Volume. Valid range: 0 - 100. **Default**: 100.
 * @return Return code {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 */
- (V2TXLiveCode)setPlayoutVolume:(NSUInteger)volume;

/**
 * Set the minimum time and maximum time (unit: s) for auto adjustment of the player cache
 *
 * @param minTime Minimum time for auto cache adjustment. The value must be greater than 0. **Default**: 1.
 * @param maxTime Maximum time for auto cache adjustment. The value must be greater than 0. **Default**: 5.
 * @return Return code {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 *         - V2TXLIVE_ERROR_INVALID_PARAMETER: operation failed. MinTime and maxTime must be greater than 0.
 *         - V2TXLIVE_ERROR_REFUSED: operation failed. Change of cache is not suppoted when playing.
 */
- (V2TXLiveCode)setCacheParams:(CGFloat)minTime maxTime:(CGFloat)maxTime;

/**
 * Seamlessly switch live stream urls, supporting  FLV and LEB protocols
 *
 * @param newUrl New pull address.
 */
- (V2TXLiveCode)switchStream:(NSString *)newUrl;

/**
 * Get Stream lnfo List
 */
- (NSArray<V2TXLiveStreamInfo *> *)getStreamList;

/**
 * Enables playback volume update
 *
 * After this feature is enabled, you can obtain the SDK’s volume evaluation through the {@link onPlayoutVolumeUpdate} callback.
 * @param intervalMs Interval for triggering the volume callback. The unit is ms. The minimum interval is 100 ms. If the value is equal to or smaller than 0, the callback is disabled. We recommend that you set this parameter to 300 ms. **Default**:
 * 0.
 * @return Return code {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 */
- (V2TXLiveCode)enableVolumeEvaluation:(NSUInteger)intervalMs;

/**
 * Captures the video view in the playback process
 *
 * @return Return code {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 *         - V2TXLIVE_ERROR_REFUSED: playback is stopped, the snapshot operation cannot be called.
 */
- (V2TXLiveCode)snapshot;

/**
 * Turn on/off the monitoring callback of the video frame
 *
 * The SDK will no longer render the video after you turn on this switch. You can get the video frame through V2TXLivePlayerObserver and execute custom rendering logic.
 * @param enable      Whether to enable custom rendering. **Default**: NO.
 * @param pixelFormat Video pixel format for custom rendering callback {@link V2TXLivePixelFormat}。
 * @param bufferType  Video data format for custom rendering callback {@link V2TXLiveBufferType}。
 * @return Return code {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 *         - V2TXLIVE_ERROR_NOT_SUPPORTED: the pixel format or data format is not supported.
 */
- (V2TXLiveCode)enableObserveVideoFrame:(BOOL)enable pixelFormat:(V2TXLivePixelFormat)pixelFormat bufferType:(V2TXLiveBufferType)bufferType;

/**
 * Turn on/off the monitoring callback of the audio frame
 *
 * if you turn on this switch, You can get the audio frame through V2TXLivePlayerObserver and execute custom logic.
 * @param enable Whether to enable the callback of the audio frame. **Default**: NO.
 * @return Return code {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 */
- (V2TXLiveCode)enableObserveAudioFrame:(BOOL)enable;

/**
 * Enables the receiving of SEI messages
 *
 * @param enable `YES`: enable; `NO` (**default**): disable.
 * @param payloadType The payload type of SEI messages. Valid values: `5`, `242`, `243`, please be consistent with the payload type of the sender.
 * @return Return code {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 */
- (V2TXLiveCode)enableReceiveSeiMessage:(BOOL)enable payloadType:(int)payloadType;

/**
 * Enables Picture-in-Picture mode
 *
 * @param enable `YES`: enable; `NO` (**default**): disable.
 * @return Return code {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 * @note This API works only on iOS.
 */
- (V2TXLiveCode)enablePictureInPicture:(BOOL)enable;

/**
 * Indicates whether the debug view of the player video status information is displayed
 *
 * @param isShow Specifies whether to display the debug view. **Default**: NO.
 */
- (void)showDebugView:(BOOL)isShow;

/**
 * Calls the advanced API of V2TXLivePlayer
 *
 * @note  This API is used to call some advanced features.
 * @param key   Key of the advanced API, please see {@link V2TXLiveProperty}.
 * @param value Parameter needed to call the advanced API corresponding to the key.
 * @return Return code {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 *         - V2TXLIVE_ERROR_INVALID_PARAMETER: operation failed. The key cannot be nil.
 */
- (V2TXLiveCode)setProperty:(NSString *)key value:(NSObject *)value;

/**
 * Start recording audio and video stream
 *
 * @param  {@link V2TXLiveLocalRecordingParams}.
 * @return Return code for {@link V2TXLiveCode}.
 *          - `V2TXLIVE_OK`: successful.
 *          - `V2TXLIVE_ERROR_INVALID_PARAMETER` : The parameter is invalid, such as filePath is empty.
 *          - `V2TXLIVE_ERROR_REFUSED`: API refuse, you must first call startLivePlay to start playing streaming.
 * @note   The recording can only be started after the play stream is started, and it is invalid to start the recording in the non-play state.
 *       - Do not dynamically switch soft/hard decoding during the recording process, as there is a high probability that the generated video will be abnormal.
 */
- (V2TXLiveCode)startLocalRecording:(V2TXLiveLocalRecordingParams *)params;

/**
 * Stop recording audio and video stream
 *
 * @note  When the play stream is stopped, if the video is still being recorded, the SDK will automatically end the recording.
 */
- (void)stopLocalRecording;

@end

LITEAV_EXPORT @interface V2TXLivePlayer : NSObject<V2TXLivePlayer>

@end
