/**
 * Copyright (c) 2021 Tencent. All rights reserved.
 * Module:   V2TXLivePusher @ TXLiteAVSDK
 * Function: Tencent Cloud live pusher
 * <H2>Function
 * Tencent Cloud Live Pusher
 * <H2>Introduce
 * It is mainly responsible for encoding the local audio and video images and pushing them to the specified streaming address, supporting any streaming server.
 * Flowmakers include the following capabilities:
 * - Customized video capture, allowing you to customize your own audio and video data sources according to project needs.
 * - Beautification, filters, stickers, including multiple sets of beautification and microdermabrasion algorithms (natural & smooth) and a variety of color space filters (support custom filters).
 * - Qos flow control technology, with uplink network adaptive capability, can adjust the amount of audio and video data in real time according to the specific conditions of the host network.
 * - Face shape adjustment, animation pendants, support face shape fine-tuning and animation pendant effects based on Youtu AI face recognition technology such as big eyes, thin face, nose augmentation, etc. You only need to purchase Youtu License to
 * easily achieve rich live broadcast effects.
 */
#import "TXAudioEffectManager.h"
#import "TXBeautyManager.h"
#import "TXDeviceManager.h"
#import "V2TXLivePusherObserver.h"
#import "TXLiteAVSymbolExport.h"

@protocol V2TXLivePusher <NSObject>

/////////////////////////////////////////////////////////////////////////////////
//
//                    LivePusher Interface
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * Sets the pusher callback
 *
 * By setting the callback, you can listen to some callback events of V2TXLivePusher,
 * including the pusher status, volume callback, statistics, warnings, and error messages.
 * @param observer Callback target of the pusher. For more information, see {@link V2TXLivePusherObserver}.
 */
- (void)setObserver:(id<V2TXLivePusherObserver>)observer;

/**
 * Sets the local camera preview
 *
 * Images collected by the local camera will be eventually displayed on the view that is passed in after it is overlaid by multiple effects, such as beauty filters, facial feature adjustments, and filters.
 * @param view Local camera preview.
 * @return Return code for {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 */
- (V2TXLiveCode)setRenderView:(TXView *)view;

/**
 * Sets the view mirror of the local camera
 *
 * Local cameras are divided into the front camera and the rear camera. By default, images from the front camera are mirrored, and images from the rear camera are not mirrored. Here, you can modify the default mirror type of the front or rear camera.
 * @param mirrorType Mirror type of the camera {@link V2TXLiveMirrorType}.
 *         - V2TXLiveMirrorTypeAuto `Default`: default mirror type. In this case, images from the front camera are mirrored, and images from the rear camera are not mirrored.
 *         - V2TXLiveMirrorTypeEnable:  both the front camera and rear camera are switched to mirror mode.
 *         - V2TXLiveMirrorTypeDisable: both the front camera and rear camera are switched to non-mirror mode.
 * @return Return code for {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 */
- (V2TXLiveCode)setRenderMirror:(V2TXLiveMirrorType)mirrorType;

/**
 * Sets the video encoder mirror
 *
 * @note  The encoder mirror only influences video effects on the audience side.
 * @param mirror Specifies whether the mirrored images are viewed.
 *         - NO `Default`: non-mirrored images are viewed on the player side.
 *         - YES: mirrored images are viewed on the player side.
 * @return Return code for {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 */
- (V2TXLiveCode)setEncoderMirror:(BOOL)mirror;

/**
 * Sets the rotation angle of the view
 *
 * @param rotation Rotation angle of the view {@link V2TXLiveRotation}.
 *         - V2TXLiveRotation0  `Default`: 0 degrees, which means the view is not rotated.
 *         - V2TXLiveRotation90:  rotate 90 degrees clockwise.
 *         - V2TXLiveRotation180: rotate 180 degrees clockwise.
 *         - V2TXLiveRotation270: rotate 270 degrees clockwise.
 * @return Return code for {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 * @note  Only the view is rotated, and images that are pushed are not affected.
 */
- (V2TXLiveCode)setRenderRotation:(V2TXLiveRotation)rotation;

/**
 * Sets the fill mode of the local video image
 *
 * @param mode Fill mode of the view {@link V2TXLiveFillMode}.
 *         - V2TXLiveFillModeFill: **Default**: fill the screen with the image without leaving any black edges. If the aspect ratio of the view is different from that of the screen, part of the view will be cropped.
 *         - V2TXLiveFillModeFit  make the view fit the screen without cropping. If the aspect ratio of the view is different from that of the screen, black edges will appear.
 *         - V2TXLiveFillModeScaleFill  fill the screen with the stretched image, thus the length and width may not change proportionally.
 * @return Return code {@link V2TXLiveCode}
 *         - V2TXLIVE_OK: successful
 */
- (V2TXLiveCode)setRenderFillMode:(V2TXLiveFillMode)mode;

#if TARGET_OS_IPHONE

/**
 * Enables the local camera
 *
 * @param frontCamera Specifies whether to switch to the front camera.
 *         - YES `Default`: switch to the front camera.
 *         - NO: switch to the rear camera.
 * @return Return code for {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 * @note startVirtualCamera, startCamera, startScreenCapture, if use the same Pusher instance, only one can publish. To switch between different capture sources, first stop the previous capture source, and then start the next capture source to ensure
 * that start and stop of the same capture source are called in pairs. eg: when the capture source is switched from Camera to VirtualCamera, the call sequence is startCamera -> stopCamera -> startVirtualCamera.
 */
- (V2TXLiveCode)startCamera:(BOOL)frontCamera;
#else

/**
 * Enables the local camera
 *
 * @param cameraId camera id.
 * @return Return code for {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 * @note startVirtualCamera, startCamera, startScreenCapture, if use the same Pusher instance, only one can publish. To switch between different capture sources, first stop the previous capture source, and then start the next capture source to ensure
 * that start and stop of the same capture source are called in pairs. eg: when the capture source is switched from Camera to VirtualCamera, the call sequence is startCamera -> stopCamera -> startVirtualCamera.
 */
- (V2TXLiveCode)startCamera:(NSString *)cameraId;
#endif

/**
 * Disables the local camera
 *
 * @return Return code for {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 */
- (V2TXLiveCode)stopCamera;

/**
 * Enables the local microphone
 *
 * @return Return code for {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 */
- (V2TXLiveCode)startMicrophone;

/**
 * Disables the microphone
 *
 * @return Return code for {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 */
- (V2TXLiveCode)stopMicrophone;

/**
 * Enables the image streaming
 *
 * @param image image.
 * @return Return code for {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 * @note startVirtualCamera, startCamera, startScreenCapture, if use the same Pusher instance, only one can publish. To switch between different capture sources, first stop the previous capture source, and then start the next capture source to ensure
 * that start and stop of the same capture source are called in pairs. eg: when the capture source is switched from Camera to VirtualCamera, the call sequence is startCamera -> stopCamera -> startVirtualCamera.
 */
- (V2TXLiveCode)startVirtualCamera:(TXImage *)image;

/**
 * Disables the image streaming
 *
 * @return Return code for {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 */
- (V2TXLiveCode)stopVirtualCamera;

#if TARGET_OS_IPHONE

/**
 * Enables video capturing
 *
 * @param appGroup The Application Group Identifier shared by the main App and Broadcast can be specified as nil. It is worth noting that the function will be more reliable according to the document guidelines.
 * @return Return code for {@link V2TXLiveCode}.
 *         - V2TXLIVE_ERROR_NOT_SUPPORTED: this feature is not supported.
 * @info The iOS system currently does not support the use of this API to enable video capture.
 *         iOS Broadcast Upload Extension must be used to enable video capture.
 *         Then, [enableCustomVideoCapture]{@link enableCustomVideoCapture} is called to enable custom video capture.
 *         Finally, [sendCustomVideoFrame]{@link sendCustomVideoFrame} is called to send video data collected in Broadcast Upload Extension.
 * @note startVirtualCamera, startCamera, startScreenCapture, if use the same Pusher instance, only one can publish. To switch between different capture sources, first stop the previous capture source, and then start the next capture source to ensure
 * that start and stop of the same capture source are called in pairs. eg: when the capture source is switched from Camera to ScreenCapture, the call sequence is startCamera -> stopCamera -> startScreenCapture.
 */
- (V2TXLiveCode)startScreenCapture:(NSString *)appGroup;
#endif

/**
 * Disables video capture
 *
 * @return Return code for {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 */
- (V2TXLiveCode)stopScreenCapture;

/**
 * Mute local audio
 *
 * After muting the local audio, the SDK will not continue to collect the microphone sound,
 * The difference from **stopMicrophone** is **pauseAudio** does not stop sending audio data, instead continue to send silent packets with a very low bit rate.
 * Due to video file formats such as MP4, the continuity of the audio is very demanding. Using **stopMicrophone** will cause the recorded MP4 to be difficult to play.
 * Therefore, in scenes that require high recording quality, it is recommended to choose **pauseAudio** to record MP4 files with better compatibility.
 * @return Return code for {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 */
- (V2TXLiveCode)pauseAudio;

/**
 * Resume the audio stream of the pusher
 *
 * @return Return code for {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 */
- (V2TXLiveCode)resumeAudio;

/**
 * Pause the video stream of the pusher
 *
 * @return Return code for {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 */
- (V2TXLiveCode)pauseVideo;

/**
 * Resume the video stream of the pusher
 *
 * @return Return code for {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 */
- (V2TXLiveCode)resumeVideo;

/**
 * Starts pushing the audio and video data
 *
 * @param url Push URL, which can be any push server.
 * @return Return code for {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: operation succeeded. The pusher starts connecting to the target push URL.
 *         - V2TXLIVE_ERROR_INVALID_PARAMETER: operation failed. The URL is invalid.
 *         - V2TXLIVE_ERROR_INVALID_LICENSE: operation failed. The license is invalid and authentication failed.
 *         - V2TXLIVE_ERROR_REFUSED: operation failed. Duplicate streamId, please ensure that no other player or pusher is using this streamId now.
 */
- (V2TXLiveCode)startPush:(NSString *)url;

/**
 * Stops pushing the audio and video data
 *
 * @return Return code for {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 */
- (V2TXLiveCode)stopPush;

/**
 * Indicates whether the pusher is currently pushing streams
 *
 * @return Indicates whether the pusher is pushing streams.
 *         - 1: yes.
 *         - 0: no.
 */
- (int)isPushing;

/**
 * Sets the audio quality for pushing
 *
 * @param quality Audio quality {@link V2TXLiveAudioQuality}.
 *         - V2TXLiveAudioQualityDefault `Default`: universal.
 *         - V2TXLiveAudioQualitySpeech: speech.
 *         - V2TXLiveAudioQualityMusic:  music.
 * @return Return code for {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 *         - V2TXLIVE_ERROR_REFUSED: the audio quality cannot be adjusted in the pushing process.
 */
- (V2TXLiveCode)setAudioQuality:(V2TXLiveAudioQuality)quality;

/**
 * Set the video encoding parameters for pushing
 *
 * @param param  video encoding parameters {@link V2TXLiveVideoEncoderParam}.
 * @return Return code for {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 */
- (V2TXLiveCode)setVideoQuality:(V2TXLiveVideoEncoderParam *)param;

/**
 * Obtains the audio effect manager
 *
 * With the audio effect manager, you can use the following features:
 * - Adjust the volume of human voice collected by the microphone.
 * - Set the reverb and voice changing effects.
 * - Start the headphone monitor, and set the volume of the headphone monitor.
 * - Add the BGM, and adjust the playback effect of BGM.
 * please see {@link TXAudioEffectManager}
 */
- (TXAudioEffectManager *)getAudioEffectManager;

/**
 * Obtains the beauty manager
 *
 * With the beauty manager, you can use the following features:
 * - Set the following cosmetic effects: beauty style, whitening, ruddy, big eyes, slim face, V-shape face, chin, short face, small nose, bright eyes, white teeth, remove eye bags, remove wrinkles, remove laugh lines.
 * - Adjust the hairline, eye spacing, eye corners, mouth shape, nose wings, nose position, lip thickness, and face shape.
 * - Set animated effects such as face widgets (materials).
 * - Add makeup effects.
 * - Recognize gestures.
 * please see  {@link TXBeautyManager}
 */
- (TXBeautyManager *)getBeautyManager;

/**
 * Obtains the video device manager
 *
 * With the device manager, you can use the following features:
 * - Switch between the front and rear cameras.
 * - Set the auto focus.
 * - Adjust the camera magnification.
 * - Turn the flash on or off.
 * - Switch between the earphone and speaker.
 * - Modify the volume type (media volume or conversation volume).
 * please see {@link TXDeviceManager}
 */
- (TXDeviceManager *)getDeviceManager;

/**
 * Captures the local view in the pushing process
 *
 * @return Return code for {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 *         - V2TXLIVE_ERROR_REFUSED: pushing is stopped, and the snapshot operation cannot be called.
 */
- (V2TXLiveCode)snapshot;

/**
 * Sets the pusher watermark image. By default, the watermark is disabled
 *
 * @param image Watermark image. If the value is nil, it is equivalent to disabling the watermark.
 * @param x     Display position of the watermark. Valid range: 0 - 1.
 * @param y     Display position of the watermark. Valid range: 0 - 1.
 * @param scale Scaling ratio of the watermark. Valid range: 0 - 1.
 * @return Return code for {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 */
- (V2TXLiveCode)setWatermark:(TXImage *)image x:(float)x y:(float)y scale:(float)scale;

/**
 * Enables volume update
 *
 * After this feature is enabled, you can obtain the volume evaluation through the {@link onMicrophoneVolumeUpdate} callback.
 * @param intervalMs Interval for triggering the volume callback. The unit is ms. The minimum interval is 100 ms. If the value is equal to or smaller than 0, the callback is disabled. We recommend that you set this parameter to 300 ms. `Default`: 0.
 * @return Return code for {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 */
- (V2TXLiveCode)enableVolumeEvaluation:(NSUInteger)intervalMs;

/**
 * Enables or disables custom video processing
 *
 * @param enable `YES`: enable; `NO`: disable (**default**).
 * @param pixelFormat Pixel format of callbacks.
 * @param bufferType Data format of callbacks.
 * @return Return code for {@link V2TXLiveCode}.
 *         - `V2TXLIVE_OK`: successful.
 *         - `V2TXLIVE_ERROR_NOT_SUPPORTED`: unsupported format.
 * @note Supported format combinations:
 *         V2TXLivePixelFormatTexture2D+V2TXLiveBufferTypeTexture
 *         V2TXLivePixelFormatNV12+V2TXLiveBufferTypePixelBuffer
 *         V2TXLivePixelFormatBGRA32+V2TXLiveBufferTypePixelBuffer
 */
- (V2TXLiveCode)enableCustomVideoProcess:(BOOL)enable pixelFormat:(V2TXLivePixelFormat)pixelFormat bufferType:(V2TXLiveBufferType)bufferType;

/**
 * Enables or disables custom video capture
 *
 * In the custom video capture mode, the SDK no longer captures images from cameras. Only the encoding and sending capabilities are retained.
 * @param enable `YES`: enable custom video capture; `NO` (**default**): disable custom video capture.
 * @return Return code for {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 * @note  This API takes effect only when it is called before {@link startPush}.
 */
- (V2TXLiveCode)enableCustomVideoCapture:(BOOL)enable;

/**
 * Turn on/off custom audio capture
 *
 *  @brief Turn on/off custom audio capture.
 *         In the custom audio capture mode, the SDK no longer collects sound from the microphone, and only retains the encoding and sending capabilities.
 *  @note   It needs to be called before {@link startPush} to take effect.
 *  @param enable YES: Open custom capture; NO: Close custom capture.`Default value`: `NO`.
 *  @return Return code for {@link V2TXLiveCode}.
 *          - `V2TXLIVE_OK`: successful.
 */
- (V2TXLiveCode)enableCustomAudioCapture:(BOOL)enable;

/**
 * Sends the collected video data to the SDK in the custom video capture mode
 *
 * In the custom video capture mode, the SDK no longer captures images from cameras. Only the encoding and sending capabilities are retained.
 * You can pack collected SampleBuffer packets into V2TXLiveVideoFrame and periodically send them through this API.
 * @param videoFrame Video frames sent to the SDK {@link V2TXLiveVideoFrame}.
 * @return Return code for {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 *         - V2TXLIVE_ERROR_INVALID_PARAMETER: The video frames fail to be sent because they are invalid.
 * @note  You must call {@link enableCustomVideoCapture} to enable custom video capture before {@link startPush} .
 */
- (V2TXLiveCode)sendCustomVideoFrame:(V2TXLiveVideoFrame *)videoFrame;

/**
 * In the custom audio collection mode, send the collected audio data to the SDK
 *
 * @param audioFrame Audio frame data sent to SDK {@link V2TXLiveAudioFrame}.
 * @return Return code for {@link V2TXLiveCode}.
 *          - `V2TXLIVE_OK`: successful.
 *          - `V2TXLIVE_ERROR_INVALID_PARAMETER`:  The audio frames fail to be sent because they are invalid.
 * @info In the custom audio collection mode, the collected audio data is sent to the SDK. The SDK no longer collects microphone data, and only retains the encoding and sending functions.
 * @note   You need to call {@link enableCustomAudioCapture(boolean)} before {@link startPush} to enable custom capture.
 */
- (V2TXLiveCode)sendCustomAudioFrame:(V2TXLiveAudioFrame *)audioFrame;

/**
 * Enables/Disables audio process callback
 *
 * @param enable `YES`: enable; `NO` (**default**): disable.
 * @param format audio frame format.
 * @note This API works only if you call it before {@link startPush}.
 */
- (V2TXLiveCode)enableAudioProcessObserver:(BOOL)enable format:(V2TXLiveAudioFrameObserverFormat *)format;

/**
 * Use SEI channel to send custom message
 *
 * The player end {@link V2TXLivePlayer} can receive the message via `onReceiveSeiMessage` callback in {@link V2TXLivePlayerObserver}.
 * @param payloadType Payload type. Valid values: `5`, `242`, `242` recommended.
 * @param data Data to be sent.
 * @return Return code for {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 */
- (V2TXLiveCode)sendSeiMessage:(int)payloadType data:(NSData *)data;

/**
 * Indicates whether the debug view of the pusher video status information is displayed
 *
 * @param isShow Specifies whether to display the debug view. `Default`: NO.
 */
- (void)showDebugView:(BOOL)isShow;

/**
 * Calls the advanced API of V2TXLivePusher
 *
 * @param key   Key of the advanced API, please see {@link V2TXLiveProperty}.
 * @param value Parameter needed to call the advanced API corresponding to the key.
 * @return Return code for {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 *         - V2TXLIVE_ERROR_INVALID_PARAMETER: operation failed. The key cannot be nil.
 * @note  This API is used to call some advanced features.
 */
- (V2TXLiveCode)setProperty:(NSString *)key value:(NSObject *)value;

/**
 * Calls the advanced API of V2TXLivePusher
 *
 * @param key   Key of the advanced API.
 * @return Return value.
 */
- (NSString *)getProperty:(NSString *)key;

/**
 * Sets On-Cloud MixTranscoding parameters
 *
 * If you have enabled relayed push on the "Function Configuration" page of the [TRTC console](https://console.cloud.tencent.com/trtc/),
 * then each stream in a room will have a default [CDN address](https://www.tencentcloud.com/document/product/647/35242).
 * There may be multiple anchors in a room, each sending their own video and audio, but CDN audience needs only one live stream.
 * Therefore, you need to mix multiple audio/video streams into one standard live stream, which requires mixing and transcoding.
 * When you call the `setMixTranscodingConfig()` API, the SDK will send a command to the Tencent Cloud transcoding server to combine multiple audio/video streams in the room into one stream.
 * You can use the `mixUsers` parameter to set the position of each channel of image and specify whether to mix only audio. You can also set the encoding parameters of the mixed stream, including `videoWidth`, `videoHeight`, and `videoBitrate`.
 * <pre>
 * **Image 1** => decoding ====> \
 *                                  \
 * **Image 2**=> decoding =>  image mixing => encoding => **mixed image**
 *                                  /
 * **Image 3** => decoding ====> /
 *
 * **Audio 1** => decoding ====> \
 *                                  \
 * **Audio 2** => decoding => audio mixing => encoding => **mixed audio**
 *                                  /
 * **Audio 3** => decoding ====> /
 * </pre>
 * For more information, please see [On-Cloud MixTranscoding](https://cloud.tencent.com/document/product/647/16827).
 * @param config Please see the description of {@link V2TXLiveTranscodingConfig} in `V2TXLiveDef.h`. Passing in `nil` will cancel On-Cloud MixTranscoding.
 * @return Return code for {@link V2TXLiveCode}.
 *         - `V2TXLIVE_OK`: successful.
 *         - `V2TXLIVE_ERROR_REFUSED`: failed to set On-Cloud MixTranscoding parameters as stream pushing has not started.
 * @note Notes:
 * - On-Cloud MixTranscoding will increase the delay of CDN live streaming by about 1-2 seconds.
 * - If you call this API, the streams of co-anchors will be mixed into your stream or the `streamId` specified in `config`.
 * - If you are still in the room but do not need to mix streams anymore, make sure that you pass in `nil` to cancel On-Cloud MixTranscoding. The On-Cloud MixTranscoding module starts working the moment you enable On-Cloud MixTranscoding. You may
 * incur additional costs if you do not cancel it in a timely manner.
 * - When you leave the room, mixing will be canceled automatically.
 */
- (V2TXLiveCode)setMixTranscodingConfig:(V2TXLiveTranscodingConfig *)config;

/**
 * Start recording audio and video stream
 *
 * @param  {@link V2TXLiveLocalRecordingParams}.
 * @return Return code for {@link V2TXLiveCode}.
 *          - `V2TXLIVE_OK`: successful.
 *          - `V2TXLIVE_ERROR_INVALID_PARAMETER` : The parameter is invalid, such as filePath is empty.
 *          - `V2TXLIVE_ERROR_REFUSED`: API refuse, you must first call startPush to start publishing streaming.
 * @note   The recording can only be started after the push stream is started, and it is invalid to start the recording in the non-push state.
 *       - Do not dynamically switch the resolution and soft/hard editing during the recording process, as there is a high probability that the generated video will be abnormal.
 */
- (V2TXLiveCode)startLocalRecording:(V2TXLiveLocalRecordingParams *)params;

/**
 * Stop recording audio and video stream
 *
 * @note  When the push stream is stopped, if the video is still being recorded, the SDK will automatically end the recording.
 */
- (void)stopLocalRecording;

/**
 * Enable voice activity detection
 *
 * @note  After turning on, you can get the start and stop of voice activities in the {@link OnVoiceActivityDetectionUpdate} callback
 */
- (void)enableVoiceActivityDetection:(BOOL)enable;

@end

LITEAV_EXPORT @interface V2TXLivePusher : NSObject<V2TXLivePusher>

/**
 * init pusher
 *
 * @param liveMode push protocol type: RTMP/ROOM protocol, default: RTMP.
 */
- (instancetype)initWithLiveMode:(V2TXLiveMode)liveMode NS_DESIGNATED_INITIALIZER;

+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)init NS_UNAVAILABLE;

@end
