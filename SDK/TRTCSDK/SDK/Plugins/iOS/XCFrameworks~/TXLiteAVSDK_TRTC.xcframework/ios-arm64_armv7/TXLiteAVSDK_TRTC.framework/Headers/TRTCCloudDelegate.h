/**
 * Copyright (c) 2021 Tencent. All rights reserved.
 * Module:   TRTCCloudDelegate @ TXLiteAVSDK
 * Function: event callback APIs for TRTC’s video call feature
 */
#import <Foundation/Foundation.h>
#import "TRTCCloudDef.h"
#import "TXLiteAVCode.h"

NS_ASSUME_NONNULL_BEGIN

@class TRTCCloud;
@class TRTCStatistics;

@protocol TRTCCloudDelegate <NSObject>
@optional

/////////////////////////////////////////////////////////////////////////////////
//
//                    Error and warning events
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 1.1 Error event callback.
 *
 * Error event, which indicates that the SDK threw an irrecoverable error such as room entry failure or failure to start device
 * For more information, see [Error Codes](https://intl.cloud.tencent.com/document/product/647/35135).
 * @param errCode Error code
 * @param errMsg Error message
 * @param extInfo Extended field. Certain error codes may carry extra information for troubleshooting.
 */
- (void)onError:(TXLiteAVError)errCode errMsg:(nullable NSString *)errMsg extInfo:(nullable NSDictionary *)extInfo;

/**
 * 1.2 Warning event callback.
 *
 * Warning event, which indicates that the SDK threw an error requiring attention, such as video lag or high CPU usage
 * For more information, see [Error Codes](https://intl.cloud.tencent.com/document/product/647/35135).
 * @param warningCode Warning code
 * @param warningMsg Warning message
 * @param extInfo Extended field. Certain warning codes may carry extra information for troubleshooting.
 */
- (void)onWarning:(TXLiteAVWarning)warningCode warningMsg:(nullable NSString *)warningMsg extInfo:(nullable NSDictionary *)extInfo;

/////////////////////////////////////////////////////////////////////////////////
//
//                    Room event callback
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 2.1 Whether room entry is successful.
 *
 * After calling the {@link enterRoom} API in `TRTCCloud` to enter a room, you will receive the `onEnterRoom(result)` callback from `TRTCCloudDelegate`.
 *  - If room entry succeeded, `result` will be a positive number (`result` > 0), indicating the time in milliseconds (ms) the room entry takes.
 *  - If room entry failed, `result` will be a negative number (result < 0), indicating the error code for the failure.
 *  For more information on the error codes for room entry failure, see [Error Codes](https://intl.cloud.tencent.com/document/product/647/35135).
 * @note
 * 1. In TRTC versions below 6.6, the `onEnterRoom(result)` callback is returned only if room entry succeeds, and the {@link onError} callback is returned if room entry fails.
 * 2. In TRTC 6.6 and above, the `onEnterRoom(result)` callback is returned regardless of whether room entry succeeds or fails, and the {@link onError} callback is also returned if room entry fails.
 * @param result If `result` is greater than 0, it indicates the time (in ms) the room entry takes; if `result` is less than 0, it represents the error code for room entry.
 */
- (void)onEnterRoom:(NSInteger)result;

/**
 * 2.2 Room exit.
 *
 * Calling the {@link exitRoom} API in `TRTCCloud` will trigger the execution of room exit-related logic, such as releasing resources of audio/video devices and codecs.
 * After all resources occupied by the SDK are released, the SDK will return the `onExitRoom()` callback.
 * If you need to call {@link enterRoom} again or switch to another audio/video SDK, please wait until you receive the `onExitRoom()` callback.
 * Otherwise, you may encounter problems such as the camera or mic being occupied.
 * @param reason Reason for room exit. `0`: the user called `exitRoom` to exit the room; `1`: the user was removed from the room by the server; `2`: the room was dismissed; `3`: the server status was abnormal.
 */
- (void)onExitRoom:(NSInteger)reason;

/**
 * 2.3 Role switching.
 *
 * You can call the {@link switchRole} API in `TRTCCloud` to switch between the anchor and audience roles. This is accompanied by a line switching process.
 * After the switching, the SDK will return the `onSwitchRole()` event callback.
 * @param errCode Error code. `ERR_NULL` indicates a successful switch. For more information, please see [Error Codes](https://intl.cloud.tencent.com/document/product/647/35135).
 * @param errMsg  Error message
 */
- (void)onSwitchRole:(TXLiteAVError)errCode errMsg:(nullable NSString *)errMsg;

/**
 * 2.4 Result of room switching.
 *
 * You can call the {@link switchRoom} API in `TRTCCloud` to switch from one room to another.
 * After the switching, the SDK will return the `onSwitchRoom()` event callback.
 * @param errCode Error code. `ERR_NULL` indicates a successful switch. For more information, please see [Error Codes](https://intl.cloud.tencent.com/document/product/647/35124).
 * @param errMsg  Error message
 */
- (void)onSwitchRoom:(TXLiteAVError)errCode errMsg:(nullable NSString *)errMsg;

/**
 * 2.5 Result of requesting cross-room call.
 *
 * You can call the {@link connectOtherRoom} API in `TRTCCloud` to establish a video call with the anchor of another room. This is the “anchor competition” feature.
 * The caller will receive the `onConnectOtherRoom()` callback, which can be used to determine whether the cross-room call is successful.
 * @param userId  The user ID of the anchor (in another room) to be called
 * @param errCode Error code. `ERR_NULL` indicates that cross-room connection is established successfully. For more information, please see [Error Codes](https://intl.cloud.tencent.com/document/product/647/35135).
 * @param errMsg  Error message
 */
- (void)onConnectOtherRoom:(NSString *)userId errCode:(TXLiteAVError)errCode errMsg:(nullable NSString *)errMsg;

/**
 * 2.6 Result of ending cross-room call.
 *
 * You can call the {@link disConnectOtherRoom} API in `TRTCCloud` to end a video call with the anchor of another room. This is the “anchor competition” feature.
 * The caller will receive the `onDisconnectOtherRoom()` callback to determine whether the cross-room call has been successfully disconnected.
 * @param errCode Error code. `ERR_NULL` indicates that the cross-room call has been successfully disconnected. For more information, please see [Error Codes](https://intl.cloud.tencent.com/document/product/647/35135).
 * @param errMsg  Error message
 */
- (void)onDisconnectOtherRoom:(TXLiteAVError)errCode errMsg:(nullable NSString *)errMsg;

/**
 * 2.7 Result of changing the upstream capability of the cross-room anchor.
 *
 * You can call the {@link updateOtherRoomForwardMode} API in `TRTCCloud` to limit the upstream capability of the cross-room anchor in the current room, and prohibit or allow the cross-room anchor to publish audio/video/sub-stream. This behavior will
 * affect all users in the room. The caller will receive the `onUpdateOtherRoomForwardMode()` callback to determine whether the changing upstream capability of the cross-room anchor is successful.
 * @param errCode Error code. `ERR_NULL` indicates that upstream capability of the cross-room anchor is changed successfully. For more information, please see [Error Codes](https://intl.cloud.tencent.com/document/product/647/35135).
 * @param errMsg  Error message
 */
- (void)onUpdateOtherRoomForwardMode:(TXLiteAVError)errCode errMsg:(nullable NSString *)errMsg;

/////////////////////////////////////////////////////////////////////////////////
//
//                    User event callback
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 3.1 A user entered the room.
 *
 * Due to performance concerns, this callback works differently in different scenarios (i.e., `AppScene`, which you can specify by setting the second parameter when calling {@link enterRoom}).
 *  - Live streaming scenarios ({@link TRTCAppSceneLIVE} or {@link TRTCAppSceneVoiceChatRoom}): in live streaming scenarios, a user is either in the role of an anchor or audience. The callback is returned only when an anchor enters the room.
 *  - Call scenarios ({@link TRTCAppSceneVideoCall} or {@link TRTCAppSceneAudioCall}): in call scenarios, the concept of roles does not apply (all users can be considered as anchors), and the callback is returned when any user enters the room.
 * @param userId User ID of the remote user
 * @note
 * 1. The `onRemoteUserEnterRoom` callback indicates that a user entered the room, but it does not necessarily mean that the user enabled audio or video.
 * 2. If you want to know whether a user enabled video, we recommend you use the {@link onUserVideoAvailable} callback.
 */
- (void)onRemoteUserEnterRoom:(NSString *)userId;

/**
 * 3.2 A user exited the room.
 *
 * As with {@link onRemoteUserEnterRoom}, this callback works differently in different scenarios (i.e., `AppScene`, which you can specify by setting the second parameter when calling {@link enterRoom}).
 *  - Live streaming scenarios ({@link TRTCAppSceneLIVE} or {@link TRTCAppSceneVoiceChatRoom}): the callback is triggered only when an anchor exits the room.
 *  - Call scenarios ({@link TRTCAppSceneVideoCall} or {@link TRTCAppSceneAudioCall}): in call scenarios, the concept of roles does not apply, and the callback is returned when any user exits the room.
 * @param userId User ID of the remote user
 * @param reason Reason for room exit. `0`: the user exited the room voluntarily; `1`: the user exited the room due to timeout; `2`: the user was removed from the room; `3`: the anchor user exited the room due to switch to audience.
 */
- (void)onRemoteUserLeaveRoom:(NSString *)userId reason:(NSInteger)reason;

/**
 * 3.3 A remote user published/unpublished primary stream video.
 *
 * The primary stream is usually used for camera images. If you receive the `onUserVideoAvailable(userId, YES)` callback, it indicates that the user has available primary stream video.
 * You can then call {@link startRemoteView} to subscribe to the remote user’s video. If the subscription is successful, you will receive the `onFirstVideoFrame(userid)` callback, which indicates that the first video frame of the user is rendered.
 * If you receive the `onUserVideoAvailable(userId, NO)` callback, it indicates that the video of the remote user is disabled, which may be because the user called {@link muteLocalVideo} or {@link stopLocalPreview}.
 * @param userId User ID of the remote user
 * @param available Whether the user published (or unpublished) primary stream video. `YES`: published; `NO`: unpublished
 */
- (void)onUserVideoAvailable:(NSString *)userId available:(BOOL)available;

/**
 * 3.4 A remote user published/unpublished substream video.
 *
 * The substream is usually used for screen sharing images. If you receive the `onUserSubStreamAvailable(userId, YES)` callback, it indicates that the user has available substream video.
 * You can then call {@link startRemoteView} to subscribe to the remote user’s video. If the subscription is successful, you will receive the `onFirstVideoFrame(userid)` callback, which indicates that the first frame of the user is rendered.
 * @param userId User ID of the remote user
 * @param available Whether the user published (or unpublished) substream video. `YES`: published; `NO`: unpublished
 * @note The API used to display substream images is {@link startRemoteView}, not {@link startRemoteSubStreamView}, {@link startRemoteSubStreamView} is deprecated.
 */
- (void)onUserSubStreamAvailable:(NSString *)userId available:(BOOL)available;

/**
 * 3.5 A remote user published/unpublished audio.
 *
 * If you receive the `onUserAudioAvailable(userId, YES)` callback, it indicates that the user published audio.
 * - In auto-subscription mode, the SDK will play the user’s audio automatically.
 * - In manual subscription mode, you can call {@link muteRemoteAudio}(userid, NO) to play the user’s audio.
 * @param userId User ID of the remote user
 * @param available Whether the user published (or unpublished) audio. `YES`: published; `NO`: unpublished
 * @note The auto-subscription mode is used by default. You can switch to the manual subscription mode by calling {@link setDefaultStreamRecvMode}, but it must be called before room entry for the switch to take effect.
 */
- (void)onUserAudioAvailable:(NSString *)userId available:(BOOL)available;

/**
 * 3.6 The SDK started rendering the first video frame of the local or a remote user.
 *
 * The SDK returns this event callback when it starts rendering your first video frame or that of a remote user. The `userId` in the callback can help you determine whether the frame is yours or a remote user’s.
 * - If `userId` is empty, it indicates that the SDK has started rendering your first video frame. The precondition is that you have called {@link startLocalPreview} or {@link startScreenCapture}.
 * - If `userId` is not empty, it indicates that the SDK has started rendering the first video frame of a remote user. The precondition is that you have called {@link startRemoteView} to subscribe to the user’s video.
 * @param userId The user ID of the local or a remote user. If it is empty, it indicates that the first local video frame is available; if it is not empty, it indicates that the first video frame of a remote user is available.
 * @param streamType Video stream type. The primary stream (`Main`) is usually used for camera images, and the substream (`Sub`) for screen sharing images.
 * @param width  Video width
 * @param height Video height
 * @note
 * 1. The callback of the first local video frame being rendered is triggered only after you call {@link startLocalPreview} or {@link startScreenCapture}.
 * 2. The callback of the first video frame of a remote user being rendered is triggered only after you call {@link startRemoteView} or {@link startRemoteSubStreamView}.
 */
- (void)onFirstVideoFrame:(NSString *)userId streamType:(TRTCVideoStreamType)streamType width:(int)width height:(int)height;

/**
 * 3.7 The SDK started playing the first audio frame of a remote user.
 *
 * The SDK returns this callback when it plays the first audio frame of a remote user. The callback is not returned for the playing of the first audio frame of the local user.
 * @param userId User ID of the remote user
 */
- (void)onFirstAudioFrame:(NSString *)userId;

/**
 * 3.8 The first local video frame was published.
 *
 * After you enter a room and call {@link startLocalPreview} or {@link startScreenCapture} to enable local video capturing (whichever happens first),
 * the SDK will start video encoding and publish the local video data via its network module to the cloud.
 * It returns the `onSendFirstLocalVideoFrame` callback after publishing the first local video frame.
 * @param streamType Video stream type. The primary stream (`Main`) is usually used for camera images, and the substream (`Sub`) for screen sharing images.
 */
- (void)onSendFirstLocalVideoFrame:(TRTCVideoStreamType)streamType;

/**
 * 3.9 The first local audio frame was published.
 *
 * After you enter a room and call {@link startLocalAudio} to enable audio capturing (whichever happens first),
 * the SDK will start audio encoding and publish the local audio data via its network module to the cloud.
 * The SDK returns the `onSendFirstLocalAudioFrame` callback after sending the first local audio frame.
 */
- (void)onSendFirstLocalAudioFrame;

/**
 * 3.10 Change of remote video status.
 *
 * You can use this callback to get the status (`Playing`, `Loading`, or `Stopped`) of the video of each remote user and display it on the UI.
 * @param userId User ID
 * @param streamType Video stream type. The primary stream (`Main`) is usually used for camera images, and the substream (`Sub`) for screen sharing images.
 * @param status Video status, which may be `Playing`, `Loading`, or `Stopped`
 * @param reason Reason for the change of status
 * @param extraInfo Extra information
 */
- (void)onRemoteVideoStatusUpdated:(NSString *)userId streamType:(TRTCVideoStreamType)streamType streamStatus:(TRTCAVStatusType)status reason:(TRTCAVStatusChangeReason)reason extrainfo:(nullable NSDictionary *)extrainfo;

/**
 * 3.11 Change of remote audio status.
 *
 * You can use this callback to get the status (`Playing`, `Loading`, or `Stopped`) of the audio of each remote user and display it on the UI.
 * @param userId User ID
 * @param status Audio status, which may be `Playing`, `Loading`, or `Stopped`
 * @param reason Reason for the change of status
 * @param extraInfo Extra information
 */
- (void)onRemoteAudioStatusUpdated:(NSString *)userId streamStatus:(TRTCAVStatusType)status reason:(TRTCAVStatusChangeReason)reason extrainfo:(nullable NSDictionary *)extrainfo;

/**
 * 3.12 Change of remote video size.
 *
 * If you receive the `onUserVideoSizeChanged(userId, streamType, newWidth, newHeight)` callback, it indicates that the user changed the video size. It may be triggered by {@link setVideoEncoderParam} or {@link setSubStreamEncoderParam}.
 * @param userId User ID
 * @param streamType Video stream type. The primary stream (`Main`) is usually used for camera images, and the substream (`Sub`) for screen sharing images.
 * @param newWidth Video width
 * @param newHeight Video height
 */
- (void)onUserVideoSizeChanged:(NSString *)userId streamType:(TRTCVideoStreamType)streamType newWidth:(int)newWidth newHeight:(int)newHeight;

/////////////////////////////////////////////////////////////////////////////////
//
//                    Callback of statistics on network and technical metrics
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 4.1 Real-time network quality statistics.
 *
 * This callback is returned every 2 seconds and notifies you of the upstream and downstream network quality detected by the SDK.
 * The SDK uses a built-in proprietary algorithm to assess the current latency, bandwidth, and stability of the network and returns a result.
 * If the result is `1` (excellent), it means that the current network conditions are excellent; if it is `6` (down), it means that the current network conditions are too bad to support TRTC calls.
 * @param localQuality Upstream network quality
 * @param remoteQuality Downstream network quality, it refers to the data quality finally measured on the local side after the data flow passes through a complete transmission link of "remote ->cloud ->local". Therefore, the downlink network quality
 * here represents the joint impact of the remote uplink and the local downlink.
 * @note The uplink quality of remote users cannot be determined independently through this interface.
 */
- (void)onNetworkQuality:(TRTCQualityInfo *)localQuality remoteQuality:(NSArray<TRTCQualityInfo *> *)remoteQuality;

/**
 * 4.2 Real-time statistics on technical metrics.
 *
 * This callback is returned every 2 seconds and notifies you of the statistics on technical metrics related to video, audio, and network. The metrics are listed in {@link TRTCStatistics}:
 * - Video statistics: video resolution (`resolution`), frame rate (`FPS`), bitrate (`bitrate`), etc.
 * - Audio statistics: audio sample rate (`samplerate`), number of audio channels (`channel`), bitrate (`bitrate`), etc.
 * - Network statistics: the round trip time (`rtt`) between the SDK and the cloud (SDK -> Cloud -> SDK), package loss rate (`loss`), upstream traffic (`sentBytes`), downstream traffic (`receivedBytes`), etc.
 * @param statistics Statistics, including local statistics and the statistics of remote users. For details, please see {@link TRTCStatistics}.
 * @note If you want to learn about only the current network quality and do not want to spend much time analyzing the statistics returned by this callback, we recommend you use {@link onNetworkQuality}.
 */
- (void)onStatistics:(TRTCStatistics *)statistics;

/**
 * 4.3 Callback of network speed test.
 *
 * The callback is triggered by {@link startSpeedTest}.
 * @param result Speed test data, including loss rates, rtt and bandwidth rates, please refer to {@link TRTCSpeedTestResult} for details.
 */
- (void)onSpeedTestResult:(TRTCSpeedTestResult *)result;

/////////////////////////////////////////////////////////////////////////////////
//
//                    Callback of connection to the cloud
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 5.1 The SDK was disconnected from the cloud.
 *
 * The SDK returns this callback when it is disconnected from the cloud, which may be caused by network unavailability or change of network, for example, when the user walks into an elevator.
 * After returning this callback, the SDK will attempt to reconnect to the cloud, and will return the {@link onTryToReconnect} callback. When it is reconnected, it will return the {@link onConnectionRecovery} callback.
 * In other words, the SDK proceeds from one event to the next in the following order:
 * ![](https://qcloudimg.tencent-cloud.cn/raw/fb3c40a4fca55b0010d385cf3b2472cd.png)
 */
- (void)onConnectionLost;

/**
 * 5.2 The SDK is reconnecting to the cloud.
 *
 * When the SDK is disconnected from the cloud, it returns the {@link onConnectionLost} callback. It then attempts to reconnect and returns this callback ({@link onTryToReconnect}). After it is reconnected, it returns the {@link onConnectionRecovery}
 * callback.
 */
- (void)onTryToReconnect;

/**
 * 5.3 The SDK is reconnected to the cloud.
 *
 * When the SDK is disconnected from the cloud, it returns the {@link onConnectionLost} callback. It then attempts to reconnect and returns the {@link onTryToReconnect} callback. After it is reconnected, it returns this callback ({@link
 * onConnectionRecovery}).
 */
- (void)onConnectionRecovery;

/////////////////////////////////////////////////////////////////////////////////
//
//                    Callback of hardware events
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 6.1 The camera is ready.
 *
 * After you call {@link startLocalPreview}, the SDK will try to start the camera and return this callback if the camera is started.
 * If it fails to start the camera, it’s probably because the application does not have access to the camera or the camera is being used.
 * You can capture the {@link onError} callback to learn about the exception and let users know via UI messages.
 */
- (void)onCameraDidReady;

/**
 * 6.2 The mic is ready.
 *
 * After you call {@link startLocalAudio}, the SDK will try to start the mic and return this callback if the mic is started.
 * If it fails to start the mic, it’s probably because the application does not have access to the mic or the mic is being used.
 * You can capture the {@link onError} callback to learn about the exception and let users know via UI messages.
 */
- (void)onMicDidReady;

/**
 * 6.3 The audio route changed (for mobile devices only).
 *
 * Audio route is the route (speaker or receiver) through which audio is played.
 * - When audio is played through the receiver, the volume is relatively low, and the sound can be heard only when the phone is put near the ear. This mode has a high level of privacy and is suitable for answering calls.
 * - When audio is played through the speaker, the volume is relatively high, and there is no need to put the phone near the ear. This mode enables the "hands-free" feature.
 * - When audio is played through the wired earphone.
 * - When audio is played through the bluetooth earphone.
 * - When audio is played through the USB sound card.
 * @param route Audio route, i.e., the route (speaker or receiver) through which audio is played
 * @param fromRoute The audio route used before the change
 */
#if TARGET_OS_IPHONE
- (void)onAudioRouteChanged:(TRTCAudioRoute)route fromRoute:(TRTCAudioRoute)fromRoute;
#endif

/**
 * 6.4 Volume.
 *
 * The SDK can assess the volume of each channel and return this callback on a regular basis. You can display, for example, a waveform or volume bar on the UI based on the statistics returned.
 * You need to first call {@link enableAudioVolumeEvaluation} to enable the feature and set the interval for the callback.
 * Note that the SDK returns this callback at the specified interval regardless of whether someone is speaking in the room.
 * @param userVolumes An array that represents the volume of all users who are speaking in the room. Value range: [0, 100]
 * @param totalVolume The total volume of all remote users. Value range: [0, 100]
 * @note `userVolumes` is an array. If `userId` is empty, the elements in the array represent the volume of the local user’s audio. Otherwise, they represent the volume of a remote user’s audio.
 */
- (void)onUserVoiceVolume:(NSArray<TRTCVolumeInfo *> *)userVolumes totalVolume:(NSInteger)totalVolume;

/**
 * 6.5 The status of a local device changed (for desktop OS only).
 *
 * The SDK returns this callback when a local device (camera, mic, or speaker) is connected or disconnected.
 * @param deviceId Device ID
 * @param deviceType Device type
 * @param state Device status. `0`: disconnected; `1`: connected
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)onDevice:(NSString *)deviceId type:(TRTCMediaDeviceType)deviceType stateChanged:(NSInteger)state;
#endif

/**
 * 6.6 The capturing volume of the mic changed.
 *
 * On desktop OS such as macOS and Windows, users can set the capturing volume of the mic in the audio control panel.
 * The higher volume a user sets, the higher the volume of raw audio captured by the mic.
 * On some keyboards and laptops, users can also mute the mic by pressing a key (whose icon is a crossed out mic).
 * When users set the mic capturing volume via the UI or a keyboard shortcut, the SDK will return this callback.
 * @param volume System audio capturing volume, which users can set in the audio control panel. Value range: [0, 100]
 * @param muted Whether the mic is muted. `YES`: muted; `NO`: unmuted
 * @note You need to call {@link enableAudioVolumeEvaluation} and set the callback interval (`interval` > 0) to enable the callback. To disable the callback, set `interval` to `0`.
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)onAudioDeviceCaptureVolumeChanged:(NSInteger)volume muted:(BOOL)muted;
#endif

/**
 * 6.7 The playback volume changed.
 *
 * On desktop OS such as macOS and Windows, users can set the system’s playback volume in the audio control panel.
 * On some keyboards and laptops, users can also mute the speaker by pressing a key (whose icon is a crossed out speaker).
 * When users set the system’s playback volume via the UI or a keyboard shortcut, the SDK will return this callback.
 * @param volume The system playback volume, which users can set in the audio control panel. Value range: 0-100
 * @param muted Whether the speaker is muted. `YES`: muted; `NO`: unmuted
 * @note You need to call {@link enableAudioVolumeEvaluation} and set the callback interval (`interval` > 0) to enable the callback. To disable the callback, set `interval` to `0`.
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)onAudioDevicePlayoutVolumeChanged:(NSInteger)volume muted:(BOOL)muted;
#endif

/**
 * 6.8 Whether system audio capturing is enabled successfully (for desktop OS only).
 *
 * On macOS, you can call {@link startSystemAudioLoopback} to install an audio driver and have the SDK capture the audio played back by the system.
 * On Windows systems, you can use {@link startSystemAudioLoopback} to have the SDK capture the audio played back by the system.
 * In use cases such as video teaching and music live streaming, the teacher can use this feature to let the SDK capture the sound of the video played by his or her computer, so that students in the room can hear the sound too.
 * The SDK returns this callback after trying to enable system audio capturing. To determine whether it is actually enabled, pay attention to the error parameter in the callback.
 * @param err If it is `ERR_NULL`, system audio capturing is enabled successfully. Otherwise, it is not. For more information, please see [Error Codes](https://intl.cloud.tencent.com/document/product/647/35135).
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)onSystemAudioLoopbackError:(TXLiteAVError)err;
#endif

/////////////////////////////////////////////////////////////////////////////////
//
//                    Callback of the receipt of a custom message
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 7.1 Receipt of custom message.
 *
 * When a user in a room uses {@link sendCustomCmdMsg} to send a custom message, other users in the room can receive the message through the `onRecvCustomCmdMsg` callback.
 *
 * @param userId User ID
 * @param cmdID Command ID
 * @param seq   Message serial number
 * @param message Message data
 */
- (void)onRecvCustomCmdMsgUserId:(NSString *)userId cmdID:(NSInteger)cmdID seq:(UInt32)seq message:(NSData *)message;

/**
 * 7.2 Loss of custom message.
 *
 * When you use {@link sendCustomCmdMsg} to send a custom UDP message, even if you enable reliable transfer (by setting `reliable` to `YES`), there is still a chance of message loss. Reliable transfer only helps maintain a low probability of message
 * loss, which meets the reliability requirements in most cases. If the sender sets `reliable` to `YES`, the SDK will use this callback to notify the recipient of the number of custom messages lost during a specified time period (usually 5s) in the
 * past.
 * @param userId User ID
 * @param cmdID Command ID
 * @param errCode Error code
 * @param missed Number of lost messages
 * @note The recipient receives this callback only if the sender sets `reliable` to `YES`.
 */
- (void)onMissCustomCmdMsgUserId:(NSString *)userId cmdID:(NSInteger)cmdID errCode:(NSInteger)errCode missed:(NSInteger)missed;

/**
 * 7.3 Receipt of SEI message.
 *
 * If a user in the room uses {@link sendSEIMsg} to send an SEI message via video frames, other users in the room can receive the message through the `onRecvSEIMsg` callback.
 *
 * @param userId User ID
 * @param message  Data
 */
- (void)onRecvSEIMsg:(NSString *)userId message:(NSData *)message;

/////////////////////////////////////////////////////////////////////////////////
//
//                    CDN event callback
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 8.1 Started publishing to Tencent Cloud CSS CDN.
 *
 * When you call {@link startPublishing} to publish streams to Tencent Cloud CSS CDN, the SDK will sync the command to the CVM immediately.
 * The SDK will then receive the execution result from the CVM and return the result to you via this callback.
 *
 * @param err `0`: successful; other values: failed. For more information, please see [Error Codes](https://intl.cloud.tencent.com/document/product/647/35135).
 * @param errMsg Error message
 */
- (void)onStartPublishing:(int)err errMsg:(NSString *)errMsg;

/**
 * 8.2 Stopped publishing to Tencent Cloud CSS CDN.
 *
 * When you call {@link stopPublishing} to stop publishing streams to Tencent Cloud CSS CDN, the SDK will sync the command to the CVM immediately.
 * The SDK will then receive the execution result from the CVM and return the result to you via this callback.
 * @param err `0`: successful; other values: failed. For more information, please see [Error Codes](https://intl.cloud.tencent.com/document/product/647/35135).
 * @param errMsg Error message
 */
- (void)onStopPublishing:(int)err errMsg:(NSString *)errMsg;

/**
 * 8.3 Started publishing to non-Tencent Cloud’s live streaming CDN.
 *
 * When you call {@link startPublishCDNStream} to start publishing streams to a non-Tencent Cloud’s live streaming CDN, the SDK will sync the command to the CVM immediately.
 * The SDK will then receive the execution result from the CVM and return the result to you via this callback.
 * @param err `0`: successful; other values: failed. For more information, please see [Error Codes](https://intl.cloud.tencent.com/document/product/647/35135).
 * @param errMsg Error message
 * @note If you receive a callback that the command is executed successfully, it only means that your command was sent to Tencent Cloud’s backend server. If the CDN vendor does not accept your streams, the publishing will still fail.
 */
- (void)onStartPublishCDNStream:(int)err errMsg:(NSString *)errMsg;

/**
 * 8.4 Stopped publishing to non-Tencent Cloud’s live streaming CDN.
 *
 * When you call {@link stopPublishCDNStream} to stop publishing to a non-Tencent Cloud’s live streaming CDN, the SDK will sync the command to the CVM immediately.
 * The SDK will then receive the execution result from the CVM and return the result to you via this callback.
 * @param err `0`: successful; other values: failed. For more information, please see [Error Codes](https://intl.cloud.tencent.com/document/product/647/35135).
 * @param errMsg Error message
 */
- (void)onStopPublishCDNStream:(int)err errMsg:(NSString *)errMsg;

/**
 * 8.5 Set the layout and transcoding parameters for On-Cloud MixTranscoding.
 *
 * When you call {@link setMixTranscodingConfig} to modify the layout and transcoding parameters for On-Cloud MixTranscoding, the SDK will sync the command to the CVM immediately.
 * The SDK will then receive the execution result from the CVM and return the result to you via this callback.
 * @param err `0`: successful; other values: failed. For more information, please see [Error Codes](https://intl.cloud.tencent.com/document/product/647/35135).
 * @param errMsg Error message
 */
- (void)onSetMixTranscodingConfig:(int)err errMsg:(NSString *)errMsg;

/**
 * 8.6 Callback for starting to publish.
 *
 * When you call {@link startPublishMediaStream} to publish a stream to the TRTC backend, the SDK will immediately update the command to the cloud server.
 * The SDK will then receive the publishing result from the cloud server and will send the result to you via this callback.
 * @param taskId: If a request is successful, a task ID will be returned via the callback. You need to provide this task ID when you call {@link updatePublishMediaStream} to modify publishing parameters or {@link stopPublishMediaStream} to stop
 * publishing.
 * @param code: `0`: Successful; other values: Failed. For more information, please see [Error Codes](https://intl.cloud.tencent.com/document/product/647/35135).
 * @param message: The callback information.
 * @param extraInfo: Additional information. For some error codes, there may be additional information to help you troubleshoot the issues.
 * If the code return value is ERR_SERVER_PROCESS_FAILED, it means the server failed to process your request. You can use "error_code" as the key to retrieve the error code returned by the server. The specific error codes and recommended actions are
 * as follows:
 * - 2000: Parameter error. Check the request parameters.
 * - 2001: Live streaming service is not enabled. Enable it in the Live streaming console.
 * - 2021: Third-party retweet service is not enabled. Contact product support to enable it.
 * - 3000: Internal server error. Retry is recommended.
 * - 4006: Concurrency conflict with the same task. The server is still processing the previous startPublishMediaStream task. Retry after a delay is recommended.
 * - 4007: The same task has already been successfully started using startPublishMediaStream. Use the returned taskId to call the updatePublishMediaStream API to update the task.
 * - 5001: Resource constraints. Retry after a delay is recommended.
 */
- (void)onStartPublishMediaStream:(NSString *)taskId code:(int)code message:(NSString *)message extraInfo:(nullable NSDictionary *)extraInfo;

/**
 * 8.7 Callback for modifying publishing parameters.
 *
 * When you call {@link updatePublishMediaStream} to modify publishing parameters, the SDK will immediately update the command to the cloud server.
 * The SDK will then receive the modification result from the cloud server and will send the result to you via this callback.
 * @param taskId: The task ID you pass in when calling {@link updatePublishMediaStream}, which is used to identify a request.
 * @param code: `0`: Successful; other values: Failed. For more information, please see [Error Codes](https://intl.cloud.tencent.com/document/product/647/35135).
 * @param message: The callback information.
 * @param extraInfo: Additional information. For some error codes, there may be additional information to help you troubleshoot the issues.
 * If the code return value is ERR_SERVER_PROCESS_FAILED, it means the server failed to process your request. You can use "error_code" as the key to retrieve the error code returned by the server. The specific error codes and recommended solutions
 * are as follows:
 * - 2000: Parameter error. Check the request parameters.
 * - 2001: Live streaming service is not enabled. Enable it in the Live Streaming Console.
 * - 2002: Task not found. Restart the task by calling the startPublishMediaStream API.
 * - 2018: Concurrent requests are out of order. Retry with the latest streaming parameters.
 * - 2021: Third-party retweet service is not enabled. Contact product support to enable it.
 * - 3000: Internal server error. Retry.
 * - 4003: Task is exiting. Stop the task by calling the stopPublishMediaStream API first, then restart it by calling the startPublishMediaStream API.
 */
- (void)onUpdatePublishMediaStream:(NSString *)taskId code:(int)code message:(NSString *)message extraInfo:(nullable NSDictionary *)extraInfo;

/**
 * 8.8 Callback for stopping publishing.
 *
 * When you call {@link stopPublishMediaStream} to stop publishing, the SDK will immediately update the command to the cloud server.
 * The SDK will then receive the modification result from the cloud server and will send the result to you via this callback.
 * @param taskId: The task ID you pass in when calling {@link stopPublishMediaStream}, which is used to identify a request.
 * @param code: `0`: Successful; other values: Failed. For more information, please see [Error Codes](https://intl.cloud.tencent.com/document/product/647/35135).
 * @param message: The callback information.
 * @param extraInfo: Additional information. For some error codes, there may be additional information to help you troubleshoot the issues.
 * If the code return value is ERR_SERVER_PROCESS_FAILED, it means the server was unable to process your request. You can use "error_code" as the key to retrieve the error code returned by the server. The specific error codes and recommended actions
 * are as follows:
 * - 2000: Parameter error. Please check the request parameters.
 * - 2002: Task not found. No action required.
 * - 3000: Internal server error. Please retry.
 * - 4003: Task is exiting. No action required.
 */
- (void)onStopPublishMediaStream:(NSString *)taskId code:(int)code message:(NSString *)message extraInfo:(nullable NSDictionary *)extraInfo;

/**
 * 8.9 Callback for change of RTMP/RTMPS publishing status.
 *
 * When you call {@link startPublishMediaStream} to publish a stream to the TRTC backend, the SDK will immediately update the command to the cloud server.
 * If you set the publishing destination ({@link TRTCPublishTarget}) to the URL of Tencent Cloud or a third-party CDN, you will be notified of the RTMP/RTMPS publishing status via this callback.
 * @param cdnUrl: The URL you specify in {@link TRTCPublishTarget} when you call {@link startPublishMediaStream}.
 * @param status: The publishing status.
 *  - 0: The publishing has not started yet or has ended. This value will be returned after you call {@link stopPublishMediaStream}.
 *  - 1: The TRTC server is connecting to the CDN server. If the first attempt fails, the TRTC backend will retry multiple times and will return this value via the callback (every five seconds). After publishing succeeds, the value `2` will be
 * returned. If a server error occurs or publishing is still unsuccessful after 60 seconds, the value `4` will be returned.
 *  - 2: The TRTC server is publishing to the CDN. This value will be returned if the publishing succeeds.
 *  - 3: The TRTC server is disconnected from the CDN server and is reconnecting. If a CDN error occurs or publishing is interrupted, the TRTC backend will try to reconnect and resume publishing and will return this value via the callback (every five
 * seconds). After publishing resumes, the value `2` will be returned. If a server error occurs or the attempt to resume publishing is still unsuccessful after 60 seconds, the value `4` will be returned.
 *  - 4: The TRTC server is disconnected from the CDN server and failed to reconnect within the timeout period. In this case, the publishing is deemed to have failed. You can call {@link updatePublishMediaStream} to try again.
 *  - 5: The TRTC server is disconnecting from the CDN server. After you call {@link stopPublishMediaStream}, the SDK will return this value first and then the value `0`.
 * @param code: The publishing result. `0`: Successful; other values: Failed. For more information, please see [Error Codes](https://intl.cloud.tencent.com/document/product/647/35135).
 * @param message: The publishing information.
 * @param extraInfo: Additional information. For some error codes, there may be additional information to help you troubleshoot the issues.
 */
- (void)onCdnStreamStateChanged:(NSString *)cdnUrl status:(int)status code:(int)code msg:(NSString *)msg extraInfo:(nullable NSDictionary *)info;

/////////////////////////////////////////////////////////////////////////////////
//
//                    Screen sharing event callback
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 9.1 Screen sharing started.
 *
 * The SDK returns this callback when you call {@link startScreenCapture} and other APIs to start screen sharing.
 */
- (void)onScreenCaptureStarted;

/**
 * 9.2 Screen sharing was paused.
 *
 * The SDK returns this callback when you call {@link pauseScreenCapture} to pause screen sharing.
 * @param reason Reason.
 * - `0`: the user paused screen sharing.
 * - `1`: screen sharing was paused because the shared window became invisible(Mac). screen sharing was paused because setting parameters(Windows).
 * - `2`: screen sharing was paused because the shared window became minimum(only for Windows).
 * - `3`: screen sharing was paused because the shared window became invisible(only for Windows).
 * - `4`: screen sharing was paused because the system operation(only for iOS).
 */
- (void)onScreenCapturePaused:(int)reason;

/**
 * 9.3 Screen sharing was resumed.
 *
 * The SDK returns this callback when you call {@link resumeScreenCapture} to resume screen sharing.
 * @param reason Reason.
 * - `0`: the user resumed screen sharing.
 * - `1`: screen sharing was resumed automatically after the shared window became visible again(Mac). screen sharing was resumed automatically after setting parameters(Windows).
 * - `2`: screen sharing was resumed automatically after the shared window became minimize recovery(only for Windows).
 * - `3`: screen sharing was resumed automatically after the shared window became visible again(only for Windows).
 * - `4`: screen sharing was resumed because the system operation(only for iOS).
 */
- (void)onScreenCaptureResumed:(int)reason;

/**
 * 9.4 Screen sharing stopped.
 *
 * The SDK returns this callback when you call {@link stopScreenCapture} to stop screen sharing.
 * @param reason Reason. `0`: the user stopped screen sharing; `1`: screen sharing stopped because the shared window was closed.
 */
- (void)onScreenCaptureStoped:(int)reason;

/////////////////////////////////////////////////////////////////////////////////
//
//                    Callback of local recording and screenshot events
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 10.1 Local recording started.
 *
 * When you call {@link startLocalRecording} to start local recording, the SDK returns this callback to notify you whether recording is started successfully.
 * @param errCode status.
 *               -  0: successful.
 *               - -1: failed.
 *               - -2: unsupported format.
 *               - -6: recording has been started. Stop recording first.
 *               - -7: recording file already exists and needs to be deleted.
 *               - -8: recording directory does not have the write permission. Please check the directory permission.
 * @param storagePath Storage path of recording file
 */
- (void)onLocalRecordBegin:(NSInteger)errCode storagePath:(NSString *)storagePath;

/**
 * 10.2 Local media is being recorded.
 *
 * The SDK returns this callback regularly after local recording is started successfully via the calling of {@link startLocalRecording}.
 * You can capture this callback to stay up to date with the status of the recording task.
 * You can set the callback interval when calling {@link startLocalRecording}.
 *
 * @param duration Cumulative duration of recording, in milliseconds
 * @param storagePath Storage path of recording file
 */
- (void)onLocalRecording:(NSInteger)duration storagePath:(NSString *)storagePath;

/**
 * 10.3 Record fragment finished.
 *
 * When fragment recording is enabled, this callback will be invoked when each fragment file is finished.
 * @param storagePath Storage path of the fragment.
 */
- (void)onLocalRecordFragment:(NSString *)storagePath;

/**
 * 10.4 Local recording stopped.
 *
 * When you call {@link stopLocalRecording} to stop local recording, the SDK returns this callback to notify you of the recording result.
 * @param errCode status
 *               -  0: successful.
 *               - -1: failed.
 *               - -2: Switching resolution or horizontal and vertical screen causes the recording to stop.
 *               - -3: recording duration is too short or no video or audio data is received. Check the recording duration or whether audio or video capture is enabled.
 * @param storagePath Storage path of recording file
 */
- (void)onLocalRecordComplete:(NSInteger)errCode storagePath:(NSString *)storagePath;

/////////////////////////////////////////////////////////////////////////////////
//
//                    Callback of debugging events
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 11.1 Callback of experimental APIs.
 */
- (void)onExperimentalEvent:(NSString *)eventName params:(nullable NSString *)params;

/// @}
/////////////////////////////////////////////////////////////////////////////////
//
//                    Disused callbacks (please use the new ones)
//
/////////////////////////////////////////////////////////////////////////////////
/// @name  Disused callbacks (please use the new ones)
/// @{

/**
 * An anchor entered the room (disused).
 *
 * @deprecated This callback is not recommended in the new version. Please use {@link onRemoteUserEnterRoom} instead.
 */
- (void)onUserEnter:(NSString *)userId __attribute__((deprecated("use onRemoteUserLeaveRoom instead")));

/**
 * An anchor left the room (disused).
 *
 * @deprecated This callback is not recommended in the new version. Please use {@link onRemoteUserLeaveRoom} instead.
 */
- (void)onUserExit:(NSString *)userId reason:(NSInteger)reason __attribute__((deprecated("use onRemoteUserLeaveRoom instead")));

/**
 * Audio effects ended (disused).
 *
 * @deprecated This callback is not recommended in the new version. Please use {@link TXAudioEffectManager} instead.
 * Audio effects and background music can be started using the same API ({@link startPlayMusic}) now instead of separate ones.
 */
- (void)onAudioEffectFinished:(int)effectId code:(int)code __attribute__((deprecated("use TXAudioEffectManager.startPlayMusic instead")));

@end

/////////////////////////////////////////////////////////////////////////////////
//
//                    Callback of custom video processing
//
/////////////////////////////////////////////////////////////////////////////////

@protocol TRTCVideoRenderDelegate <NSObject>

/**
 * Custom video rendering.
 *
 * If you have configured the callback of custom rendering for local or remote video, the SDK will return to you via this callback video frames that are otherwise sent to the rendering control, so that you can customize rendering.
 * @param frame Video frames to be rendered
 * @param userId `userId` of the video source. This parameter can be ignored if the callback is for local video ({@link setLocalVideoRenderDelegate}).
 * @param streamType Stream type. The primary stream (`Main`) is usually used for camera images, and the substream (`Sub`) for screen sharing images.
 */
@optional
- (void)onRenderVideoFrame:(TRTCVideoFrame *_Nonnull)frame userId:(NSString *__nullable)userId streamType:(TRTCVideoStreamType)streamType;

@end

@protocol TRTCVideoFrameDelegate <NSObject>

/**
 * An OpenGL context was created in the SDK.
 */
@optional
- (void)onGLContextCreated;

/**
 * Video processing by third-party beauty filters.
 *
 * If you use a third-party beauty filter component, you need to configure this callback in `TRTCCloud` to have the SDK return to you video frames that are otherwise pre-processed by TRTC.
 * You can then send the video frames to the third-party beauty filter component for processing. As the data returned can be read and modified, the result of processing can be synced to TRTC for subsequent encoding and publishing.
 * Case 1: the beauty filter component generates new textures
 * If the beauty filter component you use generates a frame of new texture (for the processed image) during image processing, please set `dstFrame.textureId` to the ID of the new texture in the callback function.
 * <pre>
 * uint32_t onProcessVideoFrame(TRTCVideoFrame * _Nonnull)srcFrame dstFrame:(TRTCVideoFrame * _Nonnull)dstFrame{
 *     self.frameID += 1;
 *     dstFrame.pixelBuffer = [[FURenderer shareRenderer] renderPixelBuffer:srcFrame.pixelBuffer
 *                                                              withFrameId:self.frameID
 *                                                                    items:self.renderItems
 *                                                                itemCount:self.renderItems.count];
 *     return 0;
 * }
 * </pre>
 *
 * Case 2: you need to provide target textures to the beauty filter component
 * If the third-party beauty filter component you use does not generate new textures and you need to manually set an input texture and an output texture for the component, you can consider the following scheme:
 * <pre>
 * uint32_t onProcessVideoFrame(TRTCVideoFrame * _Nonnull)srcFrame dstFrame:(TRTCVideoFrame * _Nonnull)dstFrame{
 *     thirdparty_process(srcFrame.textureId, srcFrame.width, srcFrame.height, dstFrame.textureId);
 *     return 0;
 * }
 * </pre>
 *
 * @param srcFrame Used to carry images captured by TRTC via the camera
 * @param dstFrame Used to receive video images processed by third-party beauty filters
 * @note Currently, only the OpenGL texture scheme is supported(PC supports TRTCVideoBufferType_Buffer format Only)
 */
@optional
- (uint32_t)onProcessVideoFrame:(TRTCVideoFrame *_Nonnull)srcFrame dstFrame:(TRTCVideoFrame *_Nonnull)dstFrame;

/**
 * The OpenGL context in the SDK was destroyed.
 */
@optional
- (void)onGLContextDestory;

@end

/// @}
/////////////////////////////////////////////////////////////////////////////////
//
//                    Callback of custom audio processing
//
/////////////////////////////////////////////////////////////////////////////////
/// @name Callback of custom audio processing
/// @{

@protocol TRTCAudioFrameDelegate <NSObject>
@optional

/**
 * Audio data captured by the local mic and pre-processed by the audio module.
 *
 * After you configure the callback of custom audio processing, the SDK will return via this callback the data captured and pre-processed (ANS, AEC, and AGC) in PCM format.
 * - The audio returned is in PCM format and has a fixed frame length (time) of 0.02s.
 * - The formula to convert a frame length in seconds to one in bytes is **sample rate * frame length in seconds * number of sound channels * audio bit depth**.
 * - Assume that the audio is recorded on a single channel with a sample rate of 48,000 Hz and audio bit depth of 16 bits, which are the default settings of TRTC. The frame length in bytes will be **48000 * 0.02s * 1 * 16 bits = 15360 bits = 1920
 * bytes**.
 * @param frame Audio frames in PCM format
 * @note
 * 1. Please avoid time-consuming operations in this callback function. The SDK processes an audio frame every 20 ms, so if your operation takes more than 20 ms, it will cause audio exceptions.
 * 2. The audio data returned via this callback can be read and modified, but please keep the duration of your operation short.
 * 3. The audio data is returned via this callback after ANS, AEC and AGC, but it **does not include** pre-processing effects like background music, audio effects, or reverb, and therefore has a short delay.
 */
- (void)onCapturedAudioFrame:(TRTCAudioFrame *)frame;

/**
 * Audio data captured by the local mic, pre-processed by the audio module, effect-processed and BGM-mixed.
 *
 * After you configure the callback of custom audio processing, the SDK will return via this callback the data captured, pre-processed (ANS, AEC, and AGC), effect-processed and BGM-mixed in PCM format, before it is submitted to the network module for
 * encoding.
 * - The audio data returned via this callback is in PCM format and has a fixed frame length (time) of 0.02s.
 * - The formula to convert a frame length in seconds to one in bytes is **sample rate * frame length in seconds * number of sound channels * audio bit depth**.
 * - Assume that the audio is recorded on a single channel with a sample rate of 48,000 Hz and audio bit depth of 16 bits, which are the default settings of TRTC. The frame length in bytes will be **48000 * 0.02s * 1 * 16 bits = 15360 bits = 1920
 * bytes**. Instructions: You could write data to the `TRTCAudioFrame.extraData` filed, in order to achieve the purpose of transmitting signaling. Because the data block of the audio frame header cannot be too large, we recommend you limit the size
 * of the signaling data to only a few bytes when using this API. If extra data more than 100 bytes, it won't be sent. Other users in the room can receive the message through the `TRTCAudioFrame.extraData` in `onRemoteUserAudioFrame` callback in
 * {@link TRTCAudioFrameDelegate}.
 * @param frame Audio frames in PCM format
 * @note
 * 1. Please avoid time-consuming operations in this callback function. The SDK processes an audio frame every 20 ms, so if your operation takes more than 20 ms, it will cause audio exceptions.
 * 2. The audio data returned via this callback can be read and modified, but please keep the duration of your operation short.
 * 3. Audio data is returned via this callback after ANS, AEC, AGC, effect-processing and BGM-mixing, and therefore the delay is longer than that with {@link onCapturedAudioFrame}.
 */
- (void)onLocalProcessedAudioFrame:(TRTCAudioFrame *)frame;

/**
 * Audio data of each remote user before audio mixing.
 *
 * After you configure the callback of custom audio processing, the SDK will return via this callback the raw audio data (PCM format) of each remote user before mixing.
 * - The audio data returned via this callback is in PCM format and has a fixed frame length (time) of 0.02s.
 * - The formula to convert a frame length in seconds to one in bytes is **sample rate * frame length in seconds * number of sound channels * audio bit depth**.
 * - Assume that the audio is recorded on a single channel with a sample rate of 48,000 Hz and audio bit depth of 16 bits, which are the default settings of TRTC. The frame length in bytes will be **48000 * 0.02s * 1 * 16 bits = 15360 bits = 1920
 * bytes**.
 * @param frame Audio frames in PCM format
 * @param userId User ID
 * @note The audio data returned via this callback can be read but not modified.
 */
- (void)onRemoteUserAudioFrame:(TRTCAudioFrame *)frame userId:(NSString *)userId;

/**
 * Data mixed from each channel before being submitted to the system for playback.
 *
 * After you configure the callback of custom audio processing, the SDK will return to you via this callback the data (PCM format) mixed from each channel before it is submitted to the system for playback.
 * - The audio data returned via this callback is in PCM format and has a fixed frame length (time) of 0.02s.
 * - The formula to convert a frame length in seconds to one in bytes is **sample rate * frame length in seconds * number of sound channels * audio bit depth**.
 * - Assume that the audio is recorded on a single channel with a sample rate of 48,000 Hz and audio bit depth of 16 bits, which are the default settings of TRTC. The frame length in bytes will be **48000 * 0.02s * 1 * 16 bits = 15360 bits = 1920
 * bytes**.
 * @param frame Audio frames in PCM format
 * @note
 * 1. Please avoid time-consuming operations in this callback function. The SDK processes an audio frame every 20 ms, so if your operation takes more than 20 ms, it will cause audio exceptions.
 * 2. The audio data returned via this callback can be read and modified, but please keep the duration of your operation short.
 * 3. The audio data returned via this callback is the audio data mixed from each channel before it is played. It does not include the in-ear monitoring data.
 */
- (void)onMixedPlayAudioFrame:(TRTCAudioFrame *)frame;

/**
 * Data mixed from all the captured and to-be-played audio in the SDK.
 *
 * After you configure the callback of custom audio processing, the SDK will return via this callback the data (PCM format) mixed from all captured and to-be-played audio in the SDK, so that you can customize recording.
 * - The audio data returned via this callback is in PCM format and has a fixed frame length (time) of 0.02s.
 * - The formula to convert a frame length in seconds to one in bytes is **sample rate * frame length in seconds * number of sound channels * audio bit depth**.
 * - Assume that the audio is recorded on a single channel with a sample rate of 48,000 Hz and audio bit depth of 16 bits, which are the default settings of TRTC. The frame length in bytes will be **48000 * 0.02s * 1 * 16 bits = 15360 bits = 1920
 * bytes**.
 * @param frame Audio frames in PCM format
 * @note
 * 1. This data returned via this callback is mixed from all audio in the SDK, including local audio after pre-processing (ANS, AEC, and AGC), special effects application, and music mixing, as well as all remote audio, but it does not include the
 * in-ear monitoring data.
 * 2. The audio data returned via this callback cannot be modified.
 */
- (void)onMixedAllAudioFrame:(TRTCAudioFrame *)frame;

/**
 * In-ear monitoring data.
 *
 * After you configure the callback of custom audio processing, the SDK will return to you via this callback the in-ear monitoring data (PCM format) before it is submitted to the system for playback.
 * - The audio returned is in PCM format and has a not-fixed frame length (time).
 * - The formula to convert a frame length in seconds to one in bytes is **sample rate * frame length in seconds * number of sound channels * audio bit depth**.
 * - Assume that the audio is recorded on a single channel with a sample rate of 48,000 Hz and audio bit depth of 16 bits, which are the default settings of TRTC. The length of 0.02s frame in bytes will be **48000 * 0.02s * 1 * 16 bits = 15360 bits =
 * 1920 bytes**.
 * @param frame Audio frames in PCM format
 * @note
 * 1. Please avoid time-consuming operations in this callback function, or it will cause audio exceptions.
 * 2. The audio data returned via this callback can be read and modified, but please keep the duration of your operation short.
 */
- (void)onVoiceEarMonitorAudioFrame:(TRTCAudioFrame *)frame;

@end

/////////////////////////////////////////////////////////////////////////////////
//
//                    Other event callbacks
//
/////////////////////////////////////////////////////////////////////////////////

@protocol TRTCLogDelegate <NSObject>
@optional

/**
 * Printing of local log.
 *
 * If you want to capture the local log printing event, you can configure the log callback to have the SDK return to you via this callback all logs that are to be printed.
 * @param log Log content
 * @param level Log level. For more information, please see {@link TRTC_LOG_LEVEL}.
 * @param module Reserved field, which is not defined at the moment and has a fixed value of `TXLiteAVSDK`.
 */
- (void)onLog:(nullable NSString *)log LogLevel:(TRTCLogLevel)level WhichModule:(nullable NSString *)module;

@end
NS_ASSUME_NONNULL_END
