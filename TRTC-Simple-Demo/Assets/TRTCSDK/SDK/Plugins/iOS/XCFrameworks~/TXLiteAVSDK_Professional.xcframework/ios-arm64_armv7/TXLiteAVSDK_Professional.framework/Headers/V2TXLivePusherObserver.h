/**
 * Copyright (c) 2021 Tencent. All rights reserved.
 * Module:   V2TXLivePusherObserver @ TXLiteAVSDK
 * Function: Tencent Cloud live pusher callback notification
 * <H2>Function
 * Callback notification for push streaming of Tencent Cloud Live.
 * <H2>Introduce
 * You can receive some push notifications from the {@link V2TXLivePusher} pusher, including the connection status of the pusher, callback of the first frame of audio and video, statistical data, warning and error messages, etc.
 */
#import "V2TXLiveDef.h"

NS_ASSUME_NONNULL_BEGIN

@protocol V2TXLivePusherObserver <NSObject>

@optional

/////////////////////////////////////////////////////////////////////////////////
//
//                   Live pusher Event Callback
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * Live pusher error notification, which is called back when the pusher encounters an error
 *
 * @param code      Error code {@link V2TXLiveCode}.
 * @param msg       Error message.
 * @param extraInfo Extended information.
 */
- (void)onError:(V2TXLiveCode)code message:(NSString *)msg extraInfo:(NSDictionary *)extraInfo;

/**
 * Live pusher warning notification
 *
 * @param code      Warning code {@link V2TXLiveCode}.
 * @param msg       Warning message.
 * @param extraInfo Extended information.
 */
- (void)onWarning:(V2TXLiveCode)code message:(NSString *)msg extraInfo:(NSDictionary *)extraInfo;

/**
 * Callback notification indicating that collection of the first audio frame is complete
 */
- (void)onCaptureFirstAudioFrame;

/**
 * Callback notification indicating that collection of the first video frame is complete
 */
- (void)onCaptureFirstVideoFrame;

/**
 * Microphone-collected volume callback
 *
 * @note  This callback notification is received after {@link enableVolumeEvaluation} is called.
 * @param volume Current volume value for collection.
 */
- (void)onMicrophoneVolumeUpdate:(NSInteger)volume;

/**
 * Callback notification of the pusher connection status
 *
 * @param status    Pusher connection status {@link V2TXLivePushStatus} .
 * @param msg       Connection status message.
 * @param extraInfo Extended information.
 */
- (void)onPushStatusUpdate:(V2TXLivePushStatus)status message:(NSString *)msg extraInfo:(NSDictionary *)extraInfo;

/**
 * Live pusher statistics callback
 *
 * @param statistics Pusher statistics {@link V2TXLivePusherStatistics} .
 */
- (void)onStatisticsUpdate:(V2TXLivePusherStatistics *)statistics;

/**
 * Screenshot callback
 *
 * @note This callback notification will be received after calling {@link snapshot} .
 * @param image Captured video image.
 */
- (void)onSnapshotComplete:(nullable TXImage *)image;

/**
 * Callback of created the OpenGL context in the SDK
 */
- (void)onGLContextCreated;

/**
 * Audio data captured by the local mic, pre-processed by the audio module, effect-processed and BGM-mixed
 *
 * After you configure the callback of custom audio processing, the SDK will return via this callback the data captured, pre-processed (ANS, AEC, and AGC), effect-processed and BGM-mixed in PCM format, before it is submitted to the network module for
 * encoding.
 * - The audio data returned via this callback is in PCM format and has a fixed frame length (time) of 0.02s.
 * - The formula to convert a frame length in seconds to one in bytes is **sample rate * frame length in seconds * number of sound channels * audio bit depth**.
 * - Assume that the audio is recorded on a single channel with a sample rate of 48,000 Hz and audio bit depth of 16 bits, which are the default settings of TRTC. The frame length in bytes will be **48000 * 0.02s * 1 * 16 bits = 15360 bits = 1920
 * bytes**.
 * @param frame Audio frames in PCM format
 * @note
 * 1. Please avoid time-consuming operations in this callback function. The SDK processes an audio frame every 20 ms, so if your operation takes more than 20 ms, it will cause audio exceptions.
 * 2. The audio data returned via this callback can be read and modified, but please keep the duration of your operation short.
 */
- (void)onProcessAudioFrame:(V2TXLiveAudioFrame *)frame;

/**
 * Custom video processing callback
 *
 * @note You will receive this callback only after you call {@link enableCustomVideoProcess}
 *       to enable custom video processing.
 * **Case 1:** The beauty filter component generates new textures.
 * If the beauty filter component you use generates a new texture frame (for the processed image) during image processing, please set `dstFrame.textureId` to a new texture ID in the callback API.
 * <pre>
 *   - (void) onProcessVideoFrame:(V2TXLiveVideoFrame * _Nonnull)srcFrame dstFrame:(V2TXLiveVideoFrame * _Nonnull)dstFrame
 *   {
 *       GLuint dstTextureId = renderItemWithTexture(srcFrame.textureId, srcFrame.width, srcFrame.height);
 *       dstFrame.textureId = dstTextureId;
 *       return 0;
 *   }
 * </pre>
 * **Case 2:** The third-party beauty filter component doesn’t generate new textures.
 * If the third-party beauty filter component you use does not generate new textures and you need to manually set an input texture and an output texture for the component, please consider the following scheme:
 * <pre>
 *   - (void) onProcessVideoFrame:(V2TXLiveVideoFrame * _Nonnull)srcFrame dstFrame:(V2TXLiveVideoFrame * _Nonnull)dstFrame
 *   {
 *       thirdparty_process(srcFrame.textureId, srcFrame.width, srcFrame.height, dstFrame.textureId);
 *       return 0;
 *   }
 * </pre>
 * @param srcFrame For images before processing.
 * @param dstFrame For images after processing.
 */
- (void)onProcessVideoFrame:(V2TXLiveVideoFrame *_Nonnull)srcFrame dstFrame:(V2TXLiveVideoFrame *_Nonnull)dstFrame;

/**
 * Callback of destroying the OpenGL context in the SDK
 */
- (void)onGLContextDestroyed;

/**
 * Callback of setting On-Cloud MixTranscoding parameters, which corresponds to the {@link setMixTranscodingConfig} API
 *
 * @param code 0: successful; other values: failed.
 * @param msg Error message.
 */
- (void)onSetMixTranscodingConfig:(V2TXLiveCode)code message:(NSString *)msg;

/**
 * The SDK returns this callback when you call {@link startScreenCapture} and other APIs to start screen sharing.
 */
- (void)onScreenCaptureStarted;

/**
 * The SDK returns this callback when you call {@link stopScreenCapture} to stop screen sharing
 *
 * @param Reason for stop.
 *               - `0`: Screen capture stopped by user.
 *               - `1`: On iOS platform means the screen recording is interrupted by the system; Mac, Windows means the screen sharing window is closed.
 *               - `2`: On windows platform indicates that the display screen status of screen sharing is changed (such as the interface is pulled out, the projection mode is changed, etc.); other platforms do not throw.
 */
- (void)onScreenCaptureStopped:(int)reason;

/**
 * The SDK returns this callback when you call {@link startLocalRecording} to start local recording.
 * Notify whether the recording task has started successfully.
 *
 * @param code status.
 *               -  0: successful.
 *               - -1: failed.
 *               - -2: unsupported format.
 *               - -6: recording has been started. Stop recording first.
 *               - -7: recording file already exists and needs to be deleted.
 *               - -8: recording directory does not have the write permission. Please check the directory permission.
 * @param storagePath recording filePath.
 */
- (void)onLocalRecordBegin:(NSInteger)errCode storagePath:(NSString *)storagePath;

/**
 * The SDK returns this callback when you call {@link startLocalRecording} to start local recording, which means recording task in progress.
 * The SDK returns this callback at a certain interval, [Default]: Do not returns this callback.
 * You can set a callback interval when {@link startLocalRecording}.
 *
 * @param durationMs   recording duration.
 * @param storagePath  recording filePath.
 */
- (void)onLocalRecording:(NSInteger)durationMs storagePath:(NSString *)storagePath;

/**
 * The SDK returns this callback when you call {@link stopLocalRecording} to start local recording.
 * Notify whether the recording task has stopped successfully.
 *
 * @param code status
 *               -  0: successful.
 *               - -1: failed.
 *               - -2: Switching resolution or horizontal and vertical screen causes the recording to stop.
 *               - -3: recording duration is too short or no video or audio data is received. Check the recording duration or whether audio or video capture is enabled.
 * @param storagePath recording filePath.
 */
- (void)onLocalRecordComplete:(NSInteger)errCode storagePath:(NSString *)storagePath;

/**
 * After calling {@link enableVoiceActivityDetection} to turn on voice activity detection, you will receive this callback notification when the anchor starts or stops speaking.
 *
 * @param active The voice starts or stops.
 */
- (void)onVoiceActivityDetectionUpdate:(BOOL)active;

@end

NS_ASSUME_NONNULL_END
