/**
 * Copyright (c) 2021 Tencent. All rights reserved.
 * Module:   TRTCCloud @ TXLiteAVSDK
 * Function: TRTC's main feature API
 * Version: <:Version:>
 */
#import <Foundation/Foundation.h>
#import <VideoToolbox/VideoToolbox.h>
#import "TRTCCloudDelegate.h"
#import "TRTCCloudDef.h"
#import "TXBeautyManager.h"
#import "TXAudioEffectManager.h"
#import "TXDeviceManager.h"

@class AITranscriberManager;

NS_ASSUME_NONNULL_BEGIN
LITEAV_EXPORT @interface TRTCCloud : NSObject

/////////////////////////////////////////////////////////////////////////////////
//
//                    Create Instance And Event Callback
//
/////////////////////////////////////////////////////////////////////////////////
/// @name Create Instance And Event Callback
/// @{

/**
 * 1.1 Create TRTCCloud instance (singleton mode).
 *
 * @note
 * 1. Please use {@link destroySharedInstance} to release the object pointer.
 */
+ (instancetype)sharedInstance;

/**
 * 1.2 Terminate TRTCCloud instance (singleton mode).
 */
+ (void)destroySharedInstance;

/**
 * 1.3 Add TRTC event callback.
 *
 * You can use {@link $TRTCCloudDelegate$} to get various event notifications from the SDK, such as error codes, warning codes, and audio/video status parameters.
 */
- (void)addDelegate:(id<TRTCCloudDelegate>)delegate;

/**
 * 1.4 Remove TRTC event callback.
 */
- (void)removeDelegate:(id<TRTCCloudDelegate>)delegate;

/**
 * 1.5 Set the queue that drives the $TRTCCloudDelegate$ event callback.
 *
 * If you do not specify a `delegateQueue`, the SDK will use `MainQueue` as the queue for driving {@link $TRTCCloudDelegate$} event callbacks by default.
 * In other words, if you do not set the `delegateQueue` attribute, all callback functions in {@link $TRTCCloudDelegate$} will be driven by `MainQueue`.
 * @note If you specify a `delegateQueue`, please do not manipulate the UI in the {@link $TRTCCloudDelegate$} callback function; otherwise, thread safety issues will occur.
 */
@property(nonatomic, strong) dispatch_queue_t delegateQueue;

/////////////////////////////////////////////////////////////////////////////////
//
//                    Room APIs
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 2.1 Enter room.
 *
 * All TRTC users need to enter a room before they can "publish" or "subscribe to" audio/video streams. "Publishing" refers to pushing their own streams to the cloud, and "subscribing to" refers to pulling the streams of other users in the room from
 * the cloud. When calling this API, you need to specify your application scenario ({@link TRTCAppScene}) to get the best audio/video transfer experience. We provide the following four scenarios for your choice:
 * - {@link $TRTCAppSceneVideoCall$}:
 *    Video call scenario. Use cases: [one-to-one video call], [video conferencing with up to 300 participants], [online medical diagnosis], [small class], [video interview], etc.
 *    In this scenario, each room supports up to 300 concurrent online users, and up to 50 of them can speak simultaneously.
 * - {@link $TRTCAppSceneAudioCall$}:
 *    Audio call scenario. Use cases: [one-to-one audio call], [audio conferencing with up to 300 participants], [audio chat], [online Werewolf], etc.
 *    In this scenario, each room supports up to 300 concurrent online users, and up to 50 of them can speak simultaneously.
 * - {@link $TRTCAppSceneLIVE$}:
 *    Live streaming scenario. Use cases: [low-latency video live streaming], [interactive classroom for up to 100,000 participants], [live video competition], [video dating room], [remote training], [large-scale conferencing], etc.
 *    In this scenario, each room supports up to 100,000 concurrent online users, but you should specify the user roles: anchor ({@link TRTCRoleAnchor }) or audience ({@link TRTCRoleAudience }).
 * - {@link $TRTCAppSceneVoiceChatRoom$}:
 *    Audio chat room scenario. Use cases: [Clubhouse], [online karaoke room], [music live room], [FM radio], etc.
 *    In this scenario, each room supports up to 100,000 concurrent online users, but you should specify the user roles: anchor ({@link TRTCRoleAnchor }) or audience ({@link TRTCRoleAudience }).
 * After calling this API, you will receive the `onEnterRoom(result)` callback from {@link $TRTCCloudDelegate$}:
 *  - If room entry succeeded, the `result` parameter will be a positive number (`result` > 0), indicating the time in milliseconds (ms) between function call and room entry.
 *  - If room entry failed, the `result` parameter will be a negative number (`result` < 0), indicating the {@link TXLiteAVError} for room entry failure.
 * @param param Room entry parameter, which is used to specify the user's identity, role, authentication credentials, and other information. For more information, please see {@link TRTCParams}.
 * @param scene Application scenario, which is used to specify the use case. The same {@link TRTCAppScene} should be configured for all users in the same room.
 * @note
 *   1. If `scene` is specified as {@link $TRTCAppSceneLIVE$} or {@link $TRTCAppSceneVoiceChatRoom$}, you must use the `role` field in {@link TRTCParams} to specify the role of the current user in the room.
 *   2. The same `scene` should be configured for all users in the same room.
 *   3. Please try to ensure that {@link enterRoom} and {@link exitRoom} are used in pair; that is, please make sure that "the previous room is exited before the next room is entered"; otherwise, many issues may occur.
 */
- (void)enterRoom:(TRTCParams *)param appScene:(TRTCAppScene)scene;

/**
 * 2.2 Exit room.
 *
 * Calling this API will allow the user to leave the current audio or video room and release the camera, mic, speaker, and other device resources.
 * After resources are released, the SDK will use the `onExitRoom()` callback in {@link $TRTCCloudDelegate$} to notify you.
 * If you need to call {@link enterRoom} again or switch to the SDK of another provider, we recommend you wait until you receive the {@link onExitRoom} callback, so as to avoid the problem of the camera or mic being occupied.
 */
- (void)exitRoom;

/**
 * 2.3 Switch role.
 *
 * This API is used to switch the user role between `anchor` and `audience`.
 * As video live rooms and audio chat rooms need to support an audience of up to 100,000 concurrent online users, the rule "only anchors can publish their audio/video streams" has been set. Therefore, when some users want to publish their streams (so
 * that they can interact with anchors), they need to switch their role to "anchor" first. You can use the `role` field in {@link TRTCParams} during room entry to specify the user role in advance or use the `switchRole` API to switch roles after room
 * entry.
 * @param role Role, which is `anchor` by default:
 * - {@link TRTCRoleAnchor}: anchor, who can publish their audio/video streams. Up to 50 anchors are allowed to publish streams at the same time in one room.
 * - {@link TRTCRoleAudience}: audience, who cannot publish their audio/video streams, but can only watch streams of anchors in the room. If they want to publish their streams, they need to switch to the "anchor" role first through {@link
 * switchRole}. One room supports an audience of up to 100,000 concurrent online users.
 * @note
 * 1. This API is only applicable to two scenarios: live streaming ({@link $TRTCAppSceneLIVE$}) and audio chat room ({@link $TRTCAppSceneVoiceChatRoom$}).
 * 2. If the `scene` you specify in {@link enterRoom} is {@link $TRTCAppSceneVideoCall$} or {@link $TRTCAppSceneAudioCall$}, please do not call this API.
 */
- (void)switchRole:(TRTCRoleType)role;

/**
 * 2.4 Switch role(support permission credential).
 *
 * This API is used to switch the user role between `anchor` and `audience`.
 * As video live rooms and audio chat rooms need to support an audience of up to 100,000 concurrent online users, the rule "only anchors can publish their audio/video streams" has been set. Therefore, when some users want to publish their streams (so
 * that they can interact with anchors), they need to switch their role to "anchor" first. You can use the `role` field in {@link TRTCParams} during room entry to specify the user role in advance or use the `switchRole` API to switch roles after room
 * entry.
 * @param role Role, which is `anchor` by default:
 * - {@link TRTCRoleAnchor}: anchor, who can publish their audio/video streams. Up to 50 anchors are allowed to publish streams at the same time in one room.
 * - {@link TRTCRoleAudience}: audience, who cannot publish their audio/video streams, but can only watch streams of anchors in the room. If they want to publish their streams, they need to switch to the "anchor" role first through {@link
 * switchRole}. One room supports an audience of up to 100,000 concurrent online users.
 * @param privateMapKey Permission credential used for permission control. If you want only users with the specified `userId` values to enter a room or push streams, you need to use `privateMapKey` to restrict the permission.
 * - We recommend you use this parameter only if you have high security requirements. For more information, please see [Enabling Advanced Permission Control](https://www.tencentcloud.com/document/product/647/35157).
 * @note
 * 1. This API is only applicable to two scenarios: live streaming ({@link $TRTCAppSceneLIVE$}) and audio chat room ({@link $TRTCAppSceneVoiceChatRoom$}).
 * 2. If the `scene` you specify in {@link enterRoom} is {@link $TRTCAppSceneVideoCall$} or {@link $TRTCAppSceneAudioCall$}, please do not call this API.
 */
- (void)switchRole:(TRTCRoleType)role privateMapKey:(NSString *)privateMapKey;

/**
 * 2.5 Switch room.
 *
 * This API is used to quickly switch a user from one room to another.
 * - If the user's role is `audience`, calling this API is equivalent to `exitRoom` (current room) + `enterRoom` (new room).
 * - If the user's role is `anchor`, the API will retain the current audio/video publishing status while switching the room; therefore, during the room switch, camera preview and sound capturing will not be interrupted.
 * This API is suitable for the online education scenario where the supervising teacher can perform fast room switch across multiple rooms. In this scenario, using `switchRoom` can get better smoothness and use less code than `exitRoom + enterRoom`.
 * The API call result will be called back through `onSwitchRoom(errCode, errMsg)` in {@link $TRTCCloudDelegate$}.
 * @param config Room parameter. For more information, please see {@link TRTCSwitchRoomConfig}.
 * @note Due to the requirement for compatibility with legacy versions of the SDK, the `config` parameter contains both `roomId` and `strRoomId` parameters. You should pay special attention as detailed below when specifying these two parameters:
 * 1. If you decide to use `strRoomId`, then set `roomId` to 0. If both are specified, `roomId` will be used.
 * 2. All rooms need to use either `strRoomId` or `roomId` at the same time. They cannot be mixed; otherwise, there will be many unexpected bugs.
 */
- (void)switchRoom:(TRTCSwitchRoomConfig *)config;

/**
 * 2.6 Request cross-room call.
 *
 * By default, only users in the same room can make audio/video calls with each other, and the audio/video streams in different rooms are isolated from each other.
 * However, you can publish the audio/video streams of an anchor in another room to the current room by calling this API. At the same time, this API will also publish the local audio/video streams to the target anchor's room.
 * In other words, you can use this API to share the audio/video streams of two anchors in two different rooms, so that the audience in each room can watch the streams of these two anchors. This feature can be used to implement anchor competition.
 * The result of requesting cross-room call will be returned through the {@link onConnectOtherRoom} callback in {@link $TRTCCloudDelegate$}.
 * For example, after anchor A in room "101" uses `connectOtherRoom()` to successfully call anchor B in room "102":
 * - All users in room "101" will receive the `onRemoteUserEnterRoom(B)` and `onUserVideoAvailable(B,$YES$)` event callbacks of anchor B; that is, all users in room "101" can subscribe to the audio/video streams of anchor B.
 * - All users in room "102" will receive the `onRemoteUserEnterRoom(A)` and `onUserVideoAvailable(A,$YES$)` event callbacks of anchor A; that is, all users in room "102" can subscribe to the audio/video streams of anchor A.
 * ![](https://qcloudimg.tencent-cloud.cn/raw/c5e6c72fc163ad5c0b6b7b00e1da55b5.png)
 * For compatibility with subsequent extended fields for cross-room call, parameters in JSON format are used currently.
 * Case 1: numeric room ID
 * If anchor A in room "101" wants to co-anchor with anchor B in room "102", then anchor A needs to pass in {"roomId": 102, "userId": "userB"} when calling this API.
 * Below is the sample code:
 * <pre>
 *   NSMutableDictionaryjsonDict = [[NSMutableDictionary alloc] init];
 *   [jsonDict setObject:@(102) forKey:@"roomId"];
 *   [jsonDict setObject:@"userB" forKey:@"userId"];
 *   NSData* jsonData = [NSJSONSerialization dataWithJSONObject:jsonDict options:NSJSONWritingPrettyPrinted error:nil];
 *   NSString* jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
 *   [trtc connectOtherRoom:jsonString];
 * </pre>
 *
 * Case 2: string room ID
 * If you use a string room ID, please be sure to replace the `roomId` in JSON with `strRoomId`, such as `{"strRoomId": "102", "userId": "userB"}`
 * Below is the sample code:
 * <pre>
 *   NSMutableDictionaryjsonDict = [[NSMutableDictionary alloc] init];
 *   [jsonDict setObject:@"102" forKey:@"strRoomId"];
 *   [jsonDict setObject:@"userB" forKey:@"userId"];
 *   NSData* jsonData = [NSJSONSerialization dataWithJSONObject:jsonDict options:NSJSONWritingPrettyPrinted error:nil];
 *   NSString* jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
 *   [trtc connectOtherRoom:jsonString];
 * </pre>
 *
 * @param param You need to pass in a string parameter in JSON format: `roomId` represents the room ID in numeric format, `strRoomId` represents the room ID in string format, and `userId` represents the user ID of the target anchor.
 */
- (void)connectOtherRoom:(NSString *)param;

/**
 * 2.7 Exit cross-room call.
 *
 * The result will be returned through the `onDisconnectOtherRoom()` callback in {@link $TRTCCloudDelegate$}.
 */
- (void)disconnectOtherRoom;

/**
 * 2.8 Set subscription mode (which must be set before room entry for it to take effect).
 *
 * You can switch between the "automatic subscription" and "manual subscription" modes through this API:
 * - Automatic subscription: this is the default mode, where the user will immediately receive the audio/video streams in the room after room entry, so that the audio will be automatically played back, and the video will be automatically decoded (you
 * still need to bind the rendering control through the `startRemoteView` API).
 * - Manual subscription: after room entry, the user needs to manually call the {@link startRemoteView} API to start subscribing to and decoding the video stream and call the {@link muteRemoteAudio} ($NO$) API to start playing back the audio stream.
 * In most scenarios, users will subscribe to the audio/video streams of all anchors in the room after room entry. Therefore, TRTC adopts the automatic subscription mode by default in order to achieve the best "instant streaming experience".
 * In your application scenario, if there are many audio/video streams being published at the same time in each room, and each user only wants to subscribe to 1–2 streams of them, we recommend you use the "manual subscription" mode to reduce the
 * traffic costs.
 * @param autoRecvAudio $YES$: automatic subscription to audio; $NO$: manual subscription to audio by calling `muteRemoteAudio($NO$)`. Default value: $YES$
 * @param autoRecvVideo $YES$: automatic subscription to video; $NO$: manual subscription to video by calling `startRemoteView`. Default value: $YES$
 * @note
 * 1. The configuration takes effect only if this API is called before room entry (enterRoom).
 * 2. In the automatic subscription mode, if the user does not call {@link startRemoteView} to subscribe to the video stream after room entry, the SDK will automatically stop subscribing to the video stream in order to reduce the traffic consumption.
 */
- (void)setDefaultStreamRecvMode:(BOOL)autoRecvAudio video:(BOOL)autoRecvVideo;

/**
 * 2.9 Create room subinstance (for concurrent multi-room listen/watch).
 *
 * `TRTCCloud` was originally designed to work in the singleton mode, which limited the ability to watch concurrently in multiple rooms.
 * By calling this API, you can create multiple `TRTCCloud` instances, so that you can enter multiple different rooms at the same time to listen/watch audio/video streams.
 * However, it should be noted that your ability to publish audio and video streams in multiple `TRTCCloud` instances will be limited.
 * This feature is mainly used in the "super small class" use case in the online education scenario to break the limit that "only up to 50 users can publish their audio/video streams simultaneously in one TRTC room".
 * Below is the sample code:
 * <pre>
 *     //In the small room that needs interaction, enter the room as an anchor and push audio and video streams
 *     TRTCCloud *mainCloud = [TRTCCloud sharedInstance];
 *     TRTCParams *mainParams = [[TRTCParams alloc] init];
 *     //Fill your params
 *     mainParams.role = TRTCRoleAnchor;
 *     [mainCloud enterRoom:mainParams appScene:TRTCAppSceneLIVE)];
 *     //...
 *     [mainCloud startLocalPreview:YES view:videoView];
 *     [mainCloud startLocalAudio:TRTCAudioQualityDefault];
 *
 *     //In the large room that only needs to watch, enter the room as an audience and pull audio and video streams
 *     TRTCCloud *subCloud = [mainCloud createSubCloud];
 *     TRTCParams *subParams = [[TRTCParams alloc] init];
 *     //Fill your params
 *     subParams.role = TRTCRoleAudience;
 *     [subCloud enterRoom:subParams appScene:TRTCAppSceneLIVE)];
 *     //...
 *     [subCloud startRemoteView:userId streamType:TRTCVideoStreamTypeBig view:videoView];
 *     //...
 *     //Exit from new room and release it.
 *     [subCloud exitRoom];
 *     [mainCloud destroySubCloud:subCloud];
 * </pre>
 *
 * @note
 * 1. The same user can enter multiple rooms with different `roomId` values by using the same `userId`.
 * 2. Two devices cannot use the same `userId` to enter the same room with a specified `roomId`.
 * 3. You can set {@link $TRTCCloudDelegate$} separately for different instances to get their own event notifications.
 * 4. The same user can push streams in multiple `TRTCCloud` instances at the same time, and can also call APIs related to local audio/video in the sub instance. But need to pay attention to:
 *     - Audio needs to be collected by the microphone or custom data at the same time in all instances, and the result of API calls related to the audio device will be based on the last time;
 *     - The result of camera-related API call will be based on the last time: {@link startLocalPreview}.
 * @return `TRTCCloud` subinstance
 */
- (TRTCCloud *)createSubCloud;

/**
 * 2.10 Terminate room subinstance.
 *
 * @param subCloud
 */
- (void)destroySubCloud:(TRTCCloud *)subCloud;

/**
 * 2.11 Change the upstream capability of the cross-room anchor in the current room.
 *
 * By default, after calling the {@link connectOtherRoom} API to make a cross-room call with an anchor in another room, all users in the current room will receive the audio/video streams published by that anchor.
 * You can use this API to limit the upstream capability of the cross-room anchor in the current room, and prohibit or allow the cross-room anchor to publish audio/video/sub-stream. This behavior will affect all users in the room.
 * After disabling a certain upstream capability of the cross-room anchor, all users in the current room will no longer receive the corresponding audio/video stream, and cannot subscribe to the corresponding audio/video.
 * Note that this API can only be called by the anchor who is conducting the cross-room call, and the restrictions set by this API will be reset when the cross-room call is interrupted or the corresponding anchor leaves the room.
 * The result of calling this API will be returned through the `onUpdateOtherRoomForwardMode()` callback in {@link $TRTCCloudDelegate$}.
 * For example, in room "101", there is anchor A and audience B, and in room "102", there is anchor C who publishes audio/video streams normally. Anchor A calls `connectOtherRoom()` to make a cross-room call with anchor C.
 * - At this time, both anchor A and audience B will receive the `onRemoteUserEnterRoom(C)`, `onUserVideoAvailable(C,$YES$)`, and `onUserAudioAvailable(C,$YES$)` event callbacks, and can subscribe to the audio/video streams of anchor C.
 * Later, anchor A calls this API to disable the audio publishing capability of anchor C in the current room.
 * - After that, the audio stream of anchor C will no longer be published to room "101", and both anchor A and audience B will receive the `onUserAudioAvailable(C,$NO$)` event callback, and cannot subscribe to the audio stream of anchor C by calling
 * `muteRemoteAudio(C,$NO$)`.
 * - The video stream of anchor C will not be affected. The other audience members in Room 102 will not be affected and can subscribe to the audio stream of anchor C normally.
 * For compatibility with subsequent extended fields for this call, parameters in JSON format are used currently.
 * Case 1: numeric room ID
 * <pre>
 * {
 *   "roomId":102,
 *   "userId":"userC",
 *   "muteAudio":false,
 *   "muteVideo":true,
 *   "muteSubStream":false
 * }
 * </pre>
 *
 * Case 2: string room ID
 * <pre>
 * {
 *   "strRoomId":"102",
 *   "userId":"userC",
 *   "muteAudio":false,
 *   "muteVideo":true,
 *   "muteSubStream":false
 * }
 * </pre>
 *
 * @param param You need to pass in a string parameter in JSON format: `roomId` represents the room ID in numeric format, `strRoomId` represents the room ID in string format, and `userId` represents the user ID of the target anchor. `muteAudio`,
 * `muteVideo` and `muteSubStream` are optional, representing whether to prohibit or allow the cross-room anchor to publish audio/video/sub-stream.
 */
- (void)updateOtherRoomForwardMode:(NSString *)param;

/////////////////////////////////////////////////////////////////////////////////
//
//                    CDN APIs
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 3.1 Publish a stream.
 *
 * After this API is called, the TRTC server will relay the stream of the local user to a CDN (after transcoding or without transcoding), or transcode and publish the stream to a TRTC room.
 * You can use the {@link TRTCPublishMode} parameter in {@link TRTCPublishTarget} to specify the publishing mode.
 * @param target The publishing destination. You can relay the stream to a CDN (after transcoding or without transcoding) or transcode and publish the stream to a TRTC room. For details, see {@link TRTCPublishTarget}.
 * @param params The encoding settings. This parameter is required if you transcode and publish the stream to a CDN or to a TRTC room. If you relay to a CDN without transcoding, to improve the relaying stability and playback compatibility, we also
 * recommend you set this parameter. For details, see {@link TRTCStreamEncoderParam}.
 * @param config The On-Cloud MixTranscoding settings. This parameter is invalid in the relay-to-CDN mode. It is required if you transcode and publish the stream to a CDN or to a TRTC room. For details, see {@link TRTCStreamMixingConfig}.
 * @note
 * 1. The SDK will send a task ID to you via the {@link onStartPublishMediaStream} callback.
 * 2. You can start a publishing task only once and cannot initiate two tasks that use the same publishing mode and publishing cdn url. Note the task ID returned, which you need to pass to {@link updatePublishMediaStream} to modify the publishing
 * parameters or {@link stopPublishMediaStream} to stop the task.
 * 3. You can specify up to 10 CDN URLs in `target`. You will be charged only once for transcoding even if you relay to multiple CDNs.
 * 4. To avoid causing errors, do not specify the same URLs for different publishing tasks executed at the same time. We recommend you add "sdkappid_roomid_userid_main" to URLs to distinguish them from one another and avoid application conflicts.
 */
- (void)startPublishMediaStream:(TRTCPublishTarget *)target encoderParam:(nullable TRTCStreamEncoderParam *)param mixingConfig:(nullable TRTCStreamMixingConfig *)config;

/**
 * 3.2 Modify publishing parameters.
 *
 * You can use this API to change the parameters of a publishing task initiated by {@link startPublishMediaStream}.
 * @param taskId The task ID returned to you via the {@link onStartPublishMediaStream} callback.
 * @param target The publishing destination. You can relay the stream to a CDN (after transcoding or without transcoding) or transcode and publish the stream to a TRTC room. For details, see {@link TRTCPublishTarget}.
 * @param params The encoding settings. This parameter is required if you transcode and publish the stream to a CDN or to a TRTC room. If you relay to a CDN without transcoding, to improve the relaying stability and playback compatibility, we
 * recommend you set this parameter. For details, see {@link TRTCStreamEncoderParam}.
 * @param config The On-Cloud MixTranscoding settings. This parameter is invalid in the relay-to-CDN mode. It is required if you transcode and publish the stream to a CDN or to a TRTC room. For details, see {@link TRTCStreamMixingConfig}.
 * @note
 * 1. You can use this API to add or remove CDN URLs to publish to (you can publish to up to 10 CDNs at a time). To avoid causing errors, do not specify the same URLs for different tasks executed at the same time.
 * 2. You can use this API to switch a relaying task to transcoding or vice versa. For example, in cross-room communication, you can first call {@link startPublishMediaStream} to relay to a CDN. When the anchor requests cross-room communication, call
 * this API, passing in the task ID to switch the relaying task to a transcoding task. This can ensure that the live stream and CDN playback are not interrupted (you need to keep the encoding parameters consistent).
 * 3. You can not switch output between "only audio", "only video" and "audio and video" for the same task.
 */
- (void)updatePublishMediaStream:(NSString *)taskId publishTarget:(TRTCPublishTarget *)target encoderParam:(nullable TRTCStreamEncoderParam *)param mixingConfig:(nullable TRTCStreamMixingConfig *)config;

/**
 * 3.3 Stop publishing.
 *
 * You can use this API to stop a task initiated by {@link startPublishMediaStream}.
 * @param taskId The task ID returned to you via the {@link onStartPublishMediaStream} callback.
 * @note
 * 1. If the task ID is not saved to your backend, you can call {@link startPublishMediaStream} again when an anchor re-enters the room after abnormal exit. The publishing will fail, but the TRTC backend will return the task ID to you.
 * 2. If `taskId` is left empty, the TRTC backend will end all tasks you started through {@link startPublishMediaStream}. You can leave it empty if you have started only one task or want to stop all publishing tasks started by you.
 */
- (void)stopPublishMediaStream:(NSString *)taskId;

/////////////////////////////////////////////////////////////////////////////////
//
//                    Video APIs
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 4.1 Enable the preview image of local camera (mobile).
 *
 * If this API is called before {@link enterRoom}, the SDK will only enable the camera and wait until {@link enterRoom} is called before starting push.
 * If it is called after {@link enterRoom}, the SDK will enable the camera and automatically start pushing the video stream.
 * When the first camera video frame starts to be rendered, you will receive the `onCameraDidReady` callback in {@link $TRTCCloudDelegate$}.
 * @param frontCamera $YES$: front camera; $NO$: rear camera
 * @param view Control that carries the video image
 * @note If you want to preview the camera image and adjust the beauty filter parameters through `BeautyManager` before going live, you can:
 *  - Scheme 1. Call `startLocalPreview` before calling {@link enterRoom}.
 *  - Scheme 2. Call `startLocalPreview` and `muteLocalVideo($YES$)` after calling {@link enterRoom}.
 */
#if TARGET_OS_IPHONE
- (void)startLocalPreview:(BOOL)frontCamera view:(nullable TXView *)view;
#endif

/**
 * 4.2 Enable the preview image of local camera (desktop).
 *
 * Before this API is called, {@link setCurrentDevice} can be called first to select whether to use the desktop device's built-in camera or an external camera.
 * If this API is called before  {@link enterRoom}, the SDK will only enable the camera and wait until {@link enterRoom} is called before starting push.
 * If it is called after  {@link enterRoom}, the SDK will enable the camera and automatically start pushing the video stream.
 * When the first camera video frame starts to be rendered, you will receive the `onCameraDidReady` callback in {@link $TRTCCloudDelegate$}.
 * @param view Control that carries the video image
 * @note If you want to preview the camera image and adjust the beauty filter parameters through `BeautyManager` before going live, you can:
 *  - Scheme 1. Call `startLocalPreview` before calling {@link enterRoom}.
 *  - Scheme 2. Call `startLocalPreview` and `muteLocalVideo($YES$)` after calling {@link enterRoom}.
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)startLocalPreview:(nullable TXView *)view;
#endif

/**
 * 4.3 Update the preview image of local camera.
 */
- (void)updateLocalView:(nullable TXView *)view;

/**
 * 4.4 Stop camera preview.
 */
- (void)stopLocalPreview;

/**
 * 4.5 Pause/Resume publishing local video stream.
 *
 * This API can pause (or resume) publishing the local video image. After the pause, other users in the same room will not be able to see the local image.
 * This API is equivalent to the two APIs of `startLocalPreview/stopLocalPreview` when TRTCVideoStreamTypeBig is specified, but has higher performance and response speed.
 * The `startLocalPreview/stopLocalPreview` APIs need to enable/disable the camera, which are hardware device-related operations, so they are very time-consuming.
 * In contrast, `muteLocalVideo` only needs to pause or allow the data stream at the software level, so it is more efficient and more suitable for scenarios where frequent enabling/disabling are needed.
 * After local video publishing is paused, other members in the same room will receive the `onUserVideoAvailable(userId, $NO$)` callback notification.
 * After local video publishing is resumed, other members in the same room will receive the `onUserVideoAvailable(userId, $YES$)` callback notification.
 * @param streamType Specify for which video stream to pause (or resume). Only {@link $TRTCVideoStreamTypeBig$} and {@link $TRTCVideoStreamTypeSub$} are supported
 * @param mute $YES$: pause; $NO$: resume
 */
- (void)muteLocalVideo:(TRTCVideoStreamType)streamType mute:(BOOL)mute;

/**
 * 4.6 Set placeholder image during local video pause.
 *
 * When you call `muteLocalVideo($YES$)` to pause the local video image, you can set a placeholder image by calling this API. Then, other users in the room will see this image instead of a black screen.
 * @param image Placeholder image. A null value means that no more video stream data will be sent after {@link muteLocalVideo}. The default value is null.
 * @param fps Frame rate of the placeholder image. Minimum value: 5. Maximum value: 10. Default value: 5
 */
- (void)setVideoMuteImage:(nullable TXImage *)image fps:(NSInteger)fps;

/**
 * 4.7 Subscribe to remote user's video stream and bind video rendering control.
 *
 * Calling this API allows the SDK to pull the video stream of the specified `userId` and render it to the rendering control specified by the `view` parameter. You can set the display mode of the video image through {@link setRemoteRenderParams}.
 * - If you already know the `userId` of a user who has a video stream in the room, you can directly call `startRemoteView` to subscribe to the user's video image.
 * - If you don't know which users in the room are publishing video streams, you can wait for the notification from {@link onUserVideoAvailable} after {@link enterRoom}.
 *
 * Calling this API only starts pulling the video stream, and the image needs to be loaded and buffered at this time. After the buffering is completed, you will receive a notification from {@link onFirstVideoFrame}.
 * @param userId ID of the specified remote user
 * @param streamType Video stream type of the `userId` specified for watching:
 *    - HD big image: {@link $TRTCVideoStreamTypeBig$}
 *    - Smooth small image: {@link $TRTCVideoStreamTypeSmall$} (the remote user should enable dual-channel encoding through {@link $enableEncSmallVideoStream$} for this parameter to take effect)
 *    - Substream image (usually used for screen sharing): {@link $TRTCVideoStreamTypeSub$}
 *
 * @param view Rendering control that carries the video image
 * @note The following requires your attention:
 *  1. The SDK supports watching the big image and substream image or small image and substream image of a `userId` at the same time, but does not support watching the big image and small image at the same time.
 *  2. Only when the specified `userId` enables dual-channel encoding through {@link $enableEncSmallVideoStream$} can the user's small image be viewed.
 *  3. If the small image of the specified `userId` does not exist, the SDK will switch to the big image of the user by default.
 */
- (void)startRemoteView:(NSString *)userId streamType:(TRTCVideoStreamType)streamType view:(nullable TXView *)view;

/**
 * 4.8 Update remote user's video rendering control.
 *
 * This API can be used to update the rendering control of the remote video image. It is often used in interactive scenarios where the display area needs to be switched.
 * @param view Control that carries the video image
 * @param streamType Type of the stream for which to set the preview window (only {@link $TRTCVideoStreamTypeBig$} and {@link $TRTCVideoStreamTypeSub$} are supported)
 * @param userId ID of the specified remote user
 */
- (void)updateRemoteView:(nullable TXView *)view streamType:(TRTCVideoStreamType)streamType forUser:(NSString *)userId;

/**
 * 4.9 Stop subscribing to remote user's video stream and release rendering control.
 *
 * Calling this API will cause the SDK to stop receiving the user's video stream and release the decoding and rendering resources for the stream.
 * @param userId ID of the specified remote user
 * @param streamType Video stream type of the `userId` specified for watching:
 *    - HD big image: {@link $TRTCVideoStreamTypeBig$}
 *    - Smooth small image: {@link $TRTCVideoStreamTypeSmall$}
 *    - Substream image (usually used for screen sharing): {@link $TRTCVideoStreamTypeSub$}
 */
- (void)stopRemoteView:(NSString *)userId streamType:(TRTCVideoStreamType)streamType;

/**
 * 4.10 Stop subscribing to all remote users' video streams and release all rendering resources.
 *
 * Calling this API will cause the SDK to stop receiving all remote video streams and release all decoding and rendering resources.
 * @note If a substream image (screen sharing) is being displayed, it will also be stopped.
 */
- (void)stopAllRemoteView;

/**
 * 4.11 Pause/Resume subscribing to remote user's video stream.
 *
 * This API only pauses/resumes receiving the specified user's video stream but does not release displaying resources; therefore, the video image will freeze at the last frame before it is called.
 * @param userId ID of the specified remote user
 * @param streamType Specify for which video stream to pause (or resume):
 *    - HD big image: {@link $TRTCVideoStreamTypeBig$}
 *    - Smooth small image: {@link $TRTCVideoStreamTypeSmall$}
 *    - Substream image (usually used for screen sharing): {@link $TRTCVideoStreamTypeSub$}
 * @param mute Whether to pause receiving
 * @note This API can be called before room entry ({@link enterRoom}), and the pause status will be reset after room exit ({@link exitRoom}). After calling this API to pause receiving the video stream from a specific user, simply calling the {@link
 * startRemoteView} API will not be able to play the video from that user. You need to call {@link muteRemoteVideoStream}($NO$) or {@link muteAllRemoteVideoStreams}($NO$) to resume it.
 */
- (void)muteRemoteVideoStream:(NSString *)userId streamType:(TRTCVideoStreamType)streamType mute:(BOOL)mute;

/**
 * 4.12 Pause/Resume subscribing to all remote users' video streams.
 *
 * This API only pauses/resumes receiving all users' video streams but does not release displaying resources; therefore, the video image will freeze at the last frame before it is called.
 * @param mute Whether to pause receiving
 * @note This API can be called before room entry ({@link enterRoom}), and the pause status will be reset after room exit ({@link exitRoom}).
 * @note After calling this interface to pause receiving video streams from all users, simply calling the {@link startRemoteView} interface will not be able to play the video from a specific user. You need to call {@link muteRemoteVideoStream}($NO$)
 * or {@link muteAllRemoteVideoStreams}($NO$) to resume it.
 */
- (void)muteAllRemoteVideoStreams:(BOOL)mute;

/**
 * 4.13 Set the encoding parameters of video encoder.
 *
 * This setting can determine the quality of image viewed by remote users, which is also the image quality of on-cloud recording files.
 * @param param It is used to set relevant parameters for the video encoder. For more information, please see {@link TRTCVideoEncParam}.
 * @note Begin from v11.5 version, the encoding output resolution will be aligned according to width 8 and height 2 bytes, and will be adjusted downward, eg: input resolution 540x960, actual encoding output resolution 536x960.
 */
- (void)setVideoEncoderParam:(TRTCVideoEncParam *)param;

/**
 * 4.14 Set network quality control parameters.
 *
 * This setting determines the quality control policy in a poor network environment, such as "image quality preferred" or "smoothness preferred".
 * @param param It is used to set relevant parameters for network quality control. For details, please refer to {@link TRTCNetworkQosParam}.
 */
- (void)setNetworkQosParam:(TRTCNetworkQosParam *)param;

/**
 * 4.15 Set the rendering parameters of local video image.
 *
 * The parameters that can be set include video image rotation angle, fill mode, and mirror mode.
 * @param params Video image rendering parameters. For more information, please see {@link TRTCRenderParams}.
 */
- (void)setLocalRenderParams:(TRTCRenderParams *)params;

/**
 * 4.16 Set the rendering mode of remote video image.
 *
 * The parameters that can be set include video image rotation angle, fill mode, and mirror mode.
 * @param userId ID of the specified remote user
 * @param streamType It can be set to the primary stream image (TRTCVideoStreamTypeBig) or substream image (TRTCVideoStreamTypeSub).
 * @param params Video image rendering parameters. For more information, please see {@link TRTCRenderParams}.
 */
- (void)setRemoteRenderParams:(NSString *)userId streamType:(TRTCVideoStreamType)streamType params:(TRTCRenderParams *)params;

/**
 * 4.20 Enable dual-channel encoding mode with big and small images.
 *
 * In this mode, the current user's encoder will output two channels of video streams, i.e., **HD big image** and **Smooth small image**, at the same time (only one channel of audio stream will be output though).
 * In this way, other users in the room can choose to subscribe to the **HD big image** or **Smooth small image** according to their own network conditions or screen size.
 * @param enable Whether to enable small image encoding. Default value: $NO$
 * @param smallVideoEncParam Video parameters of small image stream
 * @return 0: success; -1: the current big image has been set to a lower quality, and it is not necessary to enable dual-channel encoding
 * @note Dual-channel encoding will consume more CPU resources and network bandwidth; therefore, this feature can be enabled on macOS, Windows, or high-spec tablets, but is not recommended for phones.
 */
- (int)enableEncSmallVideoStream:(BOOL)enable withQuality:(TRTCVideoEncParam *)smallVideoEncParam;

/**
 * 4.21 Switch the big/small image of specified remote user.
 *
 * After an anchor in a room enables dual-channel encoding, the video image that other users in the room subscribe to through {@link startRemoteView} will be **HD big image** by default.
 * You can use this API to select whether the image subscribed to is the big image or small image. The API can take effect before or after {@link startRemoteView} is called.
 * @param userId ID of the specified remote user
 * @param streamType Video stream type, i.e., big image or small image. Default value: big image
 * @note To implement this feature, the target user must have enabled the dual-channel encoding mode through {@link $enableEncSmallVideoStream$}; otherwise, this API will not work.
 */
- (void)setRemoteVideoStreamType:(NSString *)userId type:(TRTCVideoStreamType)streamType;

/**
 * 4.22 Screencapture video.
 *
 * You can use this API to screencapture the local video image or the primary stream image and substream (screen sharing) image of a remote user.
 * @param userId User ID. A null value indicates to screencapture the local video.
 * @param streamType Video stream type, which can be the primary stream image ({@link $TRTCVideoStreamTypeBig$}, generally for camera) or substream image ({@link $TRTCVideoStreamTypeSub$}, generally for screen sharing)
 * @param sourceType Video image source, which can be the video stream image ({@link $TRTCSnapshotSourceTypeStream$}, generally in higher definition) 、the video rendering image ({@link $TRTCSnapshotSourceTypeView$}) or the capture picture ({@link
 * $TRTCSnapshotSourceTypeCapture$}).The captured picture screenshot will be clearer.
 * @note On Windows, only video image from the {@link $TRTCSnapshotSourceTypeStream$} source can be screencaptured currently.
 */
- (void)snapshotVideo:(nullable NSString *)userId type:(TRTCVideoStreamType)streamType sourceType:(TRTCSnapshotSourceType)sourceType completionBlock:(void (^)(TXImage *image))completionBlock;

/**
 * 4.24 Sets perspective correction coordinate points.
 *
 * This function allows you to specify coordinate areas for perspective correction.
 * @param userId userId which corresponding to the target stream. If null value is specified, it indicates that the function is applied to the local stream.
 * @param srcPoints The coordinates of the four vertices of the original stream image area should be passed in the order of top-left, bottom-left, top-right, bottom-right. All coordinates need to be normalized to the [0,1] range based on the render
 * view width and height, or null to stop perspective correction of the corresponding stream.
 * @param dstPoints The coordinates of the four vertices of the target corrected area should be passed in the order of top-left, bottom-left, top-right, bottom-right. All coordinates need to be normalized to the [0,1] range based on the render view
 * width and height, or null to stop perspective correction of the corresponding stream.
 */
- (void)setPerspectiveCorrectionWithUser:(nullable NSString *)userId srcPoints:(nullable NSArray *)srcPoints dstPoints:(nullable NSArray *)dstPoints;

/**
 * 4.25 Set the adaptation mode of gravity sensing (version 11.7 and above).
 *
 * After turning on gravity sensing, if the device on the collection end rotates, the images on the collection end and the audience will be rendered accordingly to ensure that the image in the field of view is always facing up.
 * It only takes effect in the camera capture scene inside the SDK, and only takes effect on the mobile terminal.
 * 1. This interface only works for the collection end. If you only watch the picture in the room, opening this interface is invalid.
 * 2. When the capture device is rotated 90 degrees or 270 degrees, the picture seen by the capture device or the audience may be cropped to maintain proportional coordination.
 * @param mode Gravity sensing mode, see {@link $TRTCGravitySensorAdaptiveMode_Disable$}、{@link $TRTCGravitySensorAdaptiveMode_FillByCenterCrop$} and {@link $TRTCGravitySensorAdaptiveMode_FitWithBlackBorder$} for details, default value: {@link
 * $TRTCGravitySensorAdaptiveMode_Disable$}.
 */
- (void)setGravitySensorAdaptiveMode:(TRTCGravitySensorAdaptiveMode)mode;

/// @}
/////////////////////////////////////////////////////////////////////////////////
//
//                    Audio APIs
//
/////////////////////////////////////////////////////////////////////////////////
/// @name  Audio APIs
/// @{

/**
 * 5.1 Enable local audio capturing and publishing.
 *
 * The SDK does not enable the mic by default. When a user wants to publish the local audio, the user needs to call this API to enable mic capturing and encode and publish the audio to the current room.
 * After local audio capturing and publishing is enabled, other users in the room will receive the {@link onUserAudioAvailable}(userId, $YES$) notification.
 * @param quality Sound quality
 *   - {@link $TRTCAudioQualitySpeech$} - Smooth: mono channel; audio bitrate: 18 Kbps. This is suitable for audio call scenarios, such as online meeting and audio call.
 *   - {@link $TRTCAudioQualityDefault$} - Default: mono channel; audio bitrate: 50 Kbps. This is the default sound quality of the SDK and recommended if there are no special requirements.
 *   - {@link $TRTCAudioQualityMusic$} - HD: dual channel + full band; audio bitrate: 128 Kbps. This is suitable for scenarios where Hi-Fi music transfer is required, such as online karaoke and music live streaming.
 * @note This API will check the mic permission. If the current application does not have permission to use the mic, the SDK will automatically ask the user to grant the mic permission.
 */
- (void)startLocalAudio:(TRTCAudioQuality)quality;

/**
 * 5.2 Stop local audio capturing and publishing.
 *
 * After local audio capturing and publishing is stopped, other users in the room will receive the {@link onUserAudioAvailable}(userId, $NO$) notification.
 */
- (void)stopLocalAudio;

/**
 * 5.3 Pause/Resume publishing local audio stream.
 *
 * After local audio publishing is paused, other users in the room will receive the {@link onUserAudioAvailable}(userId, $NO$) notification.
 * After local audio publishing is resumed, other users in the room will receive the {@link onUserAudioAvailable}(userId, $YES$) notification.
 * Different from {@link stopLocalAudio}, `muteLocalAudio($YES$)` does not release the mic permission; instead, it continues to send mute packets with extremely low bitrate.
 * This is very suitable for scenarios that require on-cloud recording, as video file formats such as MP4 have a high requirement for audio continuity, while an MP4 recording file cannot be played back smoothly if {@link stopLocalAudio} is used.
 * Therefore, `muteLocalAudio` instead of {@link stopLocalAudio} is recommended in scenarios where the requirement for recording file quality is high.
 * @param mute $YES$: mute; $NO$: unmute
 */
- (void)muteLocalAudio:(BOOL)mute;

/**
 * 5.4 Pause/Resume playing back remote audio stream.
 *
 * When you mute the remote audio of a specified user, the SDK will stop playing back the user's audio and pulling the user's audio data.
 * @param userId ID of the specified remote user
 * @param mute $YES$: mute; $NO$: unmute
 * @note This API works when called either before or after room entry ({@link enterRoom}), and the mute status will be reset to `$NO$` after room exit ({@link exitRoom}).
 */
- (void)muteRemoteAudio:(NSString *)userId mute:(BOOL)mute;

/**
 * 5.5 Pause/Resume playing back all remote users' audio streams.
 *
 * When you mute the audio of all remote users, the SDK will stop playing back all their audio streams and pulling all their audio data.
 * @param mute $YES$: mute; $NO$: unmute
 * @note This API works when called either before or after room entry ({@link enterRoom}), and the mute status will be reset to `$NO$` after room exit ({@link exitRoom}).
 */
- (void)muteAllRemoteAudio:(BOOL)mute;

/**
 * 5.6 Set audio route.
 *
 * Setting "audio route" is to determine whether the sound is played back from the speaker or receiver of a mobile device; therefore, this API is only applicable to mobile devices such as phones.
 * Generally, a phone has two speakers: one is the receiver at the top, and the other is the stereo speaker at the bottom.
 * If audio route is set to the receiver, the volume is relatively low, and the sound can be heard clearly only when the phone is put near the ear. This mode has a high level of privacy and is suitable for answering calls.
 * If audio route is set to the speaker, the volume is relatively high, so there is no need to put the phone near the ear. Therefore, this mode can implement the "hands-free" feature.
 * @param route Audio route, i.e., whether the audio is output by speaker or receiver. Default value: {@link $TRTCAudioModeSpeakerphone$}
 */
- (void)setAudioRoute:(TRTCAudioRoute)route;

/**
 * 5.7 Set the audio playback volume of remote user.
 *
 * You can mute the audio of a remote user through `setRemoteAudioVolume(userId, 0)`.
 * @param userId ID of the specified remote user
 * @param volume Volume. 100 is the original volume. Value range: [0,150]. Default value: 100
 * @note If 100 is still not loud enough for you, you can set the volume to up to 150, but there may be side effects.
 */
- (void)setRemoteAudioVolume:(NSString *)userId volume:(int)volume;

/**
 * 5.8 Set the capturing volume of local audio.
 *
 * @param volume Volume. 100 is the original volume. Value range: [0,150]. Default value: 100
 * @note If 100 is still not loud enough for you, you can set the volume to up to 150, but there may be side effects.
 */
- (void)setAudioCaptureVolume:(NSInteger)volume;

/**
 * 5.9 Get the capturing volume of local audio.
 *
 * @return capturing volume
 */
- (NSInteger)getAudioCaptureVolume;

/**
 * 5.10 Set the playback volume of remote audio.
 *
 * This API controls the volume of the sound ultimately delivered by the SDK to the system for playback. It affects the volume of the recorded local audio file but not the volume of in-ear monitoring.
 * @param volume Volume. 100 is the original volume. Value range: [0,150]. Default value: 100
 * @note If 100 is still not loud enough for you, you can set the volume to up to 150, but there may be side effects.
 */
- (void)setAudioPlayoutVolume:(NSInteger)volume;

/**
 * 5.11 Get the playback volume of remote audio.
 */
- (NSInteger)getAudioPlayoutVolume;

/**
 * 5.12 Enable volume reminder.
 *
 * After this feature is enabled, the SDK will return the audio volume assessment information of local user who sends stream and remote users in the {@link onUserVoiceVolume} callback of {@link $TRTCCloudDelegate$}.
 * @note To enable this feature, call this API before calling {@link startLocalAudio}.
 * @param enable Whether to enable the volume prompt. It’s disabled by default.
 * @param params Volume evaluation and other related parameters, please see {@link TRTCAudioVolumeEvaluateParams}
 */
- (void)enableAudioVolumeEvaluation:(BOOL)enable withParams:(TRTCAudioVolumeEvaluateParams *)params;

/**
 * 5.13 Start audio recording.
 *
 * After you call this API, the SDK will selectively record local and remote audio streams (such as local audio, remote audio, background music, and sound effects) into a local file.
 * This API works when called either before or after room entry. If a recording task has not been stopped through {@link stopAudioRecording} before room exit, it will be automatically stopped after room exit.
 * The startup and completion status of the recording will be notified through local recording-related callbacks. See TRTCCloud related callbacks for reference.
 * @param param Recording parameter. For more information, please see {@link TRTCAudioRecordingParams}
 * @return 0: success; -1: audio recording has been started; -2: failed to create file or directory; -3: the audio format of the specified file extension is not supported.
 * @note Since version 11.5, the results of audio recording have been changed to be notified through asynchronous callbacks instead of return values. Please refer to the relevant callbacks of {@link $TRTCCloudDelegate$} .
 */
- (int)startAudioRecording:(TRTCAudioRecordingParams *)param;

/**
 * 5.14 Stop audio recording.
 *
 * If a recording task has not been stopped through this API before room exit, it will be automatically stopped after room exit.
 */
- (void)stopAudioRecording;

/**
 * 5.15 Start local media recording.
 *
 * This API records the audio/video content during live streaming into a local file,and no recording fees for local recording.
 * @param params Recording parameter. For more information, please see {@link TRTCLocalRecordingParams}
 */
- (void)startLocalRecording:(TRTCLocalRecordingParams *)params;

/**
 * 5.16 Stop local media recording.
 *
 * If a recording task has not been stopped through this API before room exit, it will be automatically stopped after room exit.
 */
- (void)stopLocalRecording;

/**
 * 5.17 Set the parallel strategy of remote audio streams.
 *
 * For room with many speakers.
 * @param params Audio parallel parameter. For more information, please see {@link TRTCAudioParallelParams}
 */
- (void)setRemoteAudioParallelParams:(TRTCAudioParallelParams *)params;

/**
 * 5.19 Enable 3D spatial effect.
 *
 * Enable 3D spatial effect. Note that {@link $TRTCAudioQualitySpeech$} smooth or {@link $TRTCAudioQualityDefault$} default audio quality should be used.
 * @param enabled Whether to enable 3D spatial effect. It’s disabled by default.
 */
- (void)enable3DSpatialAudioEffect:(BOOL)enabled;

/**
 * 5.20 Update self position and orientation for 3D spatial effect.
 *
 * Update self position and orientation in the world coordinate system. The SDK will calculate the relative position between self and the remote users according to the parameters of this method, and then render the spatial sound effect.
 * @param position The coordinate of self in the world coordinate system. The three values represent the forward, right and up coordinate values in turn.
 * @param axisForward The unit vector of the forward axis of user coordinate system. The three values represent the forward, right and up coordinate values in turn.
 * @param axisRight The unit vector of the right axis of user coordinate system. The three values represent the forward, right and up coordinate values in turn.
 * @param axisUp The unit vector of the up axis of user coordinate system. The three values represent the forward, right and up coordinate values in turn.
 * @note
 * 1. The length of array should be 3.
 * 2. Please limit the calling frequency appropriately. It's recommended that the interval between two operations be at least 100ms.
 */
- (void)updateSelf3DSpatialPosition:(int[_Nonnull 3])position axisForward:(float[_Nonnull 3])axisForward axisRight:(float[_Nonnull 3])axisRight axisUp:(float[_Nonnull 3])axisUp;

/**
 * 5.21 Update the specified remote user's position for 3D spatial effect.
 *
 * Update the specified remote user's position in the world coordinate system. The SDK will calculate the relative position between self and the remote users according to the parameters of this method, and then render the spatial sound effect.
 * @param userId ID of the specified remote user.
 * @param position The coordinate of self in the world coordinate system. The three values represent the forward, right and up coordinate values in turn.
 * @note
 * 1. The length of array should be 3.
 * 2. Please limit the calling frequency appropriately. It's recommended that the interval between two operations of the same remote user be at least 100ms.
 */
- (void)updateRemote3DSpatialPosition:(NSString *)userId position:(int[_Nonnull 3])position;

/**
 * 5.22 Set the maximum 3D spatial attenuation range for userId's audio stream.
 *
 * After set the range, the specified user's audio stream will attenuate to zero within the range.
 * @param userId ID of the specified user.
 * @param range Maximum attenuation range of the audio stream.
 */
- (void)set3DSpatialReceivingRange:(NSString *)userId range:(NSInteger)range;

/////////////////////////////////////////////////////////////////////////////////
//
//                    Device management APIs
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 6.1 Get device management class (TXDeviceManager).
 *
 * Through device management, you can set the functions of audio and video related hardware devices such as cameras, microphones, and speakers.
 * @return device management class {@link TXDeviceManager}.
 */
- (TXDeviceManager *)getDeviceManager;

/////////////////////////////////////////////////////////////////////////////////
//
//                    Beauty filter and watermark APIs
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 7.1 Get beauty filter management class (TXBeautyManager).
 *
 * You can use the following features with beauty filter management:
 * - Set beauty effects such as "skin smoothing", "brightening", and "rosy skin".
 * - The following features are only supported on iOS/Android.
 * - Set face adjustment effects such as "eye enlarging", "face slimming", "chin slimming", "chin lengthening/shortening", "face shortening", "nose narrowing", "eye brightening", "teeth whitening", "eye bag removal", "wrinkle removal", and "smile
 * line removal".
 * - Set face adjustment effects such as "hairline", "eye distance", "eye corners", "mouth shape", "nose wing", "nose position", "lip thickness", and "face shape".
 * - Set makeup effects such as "eye shadow" and "blush".
 * - Set animated effects such as animated sticker and facial pendant.
 * @return beauty filter management class {@link TXBeautyManager}.
 */
- (TXBeautyManager *)getBeautyManager;

/**
 * 7.2 Add watermark.
 *
 * The watermark position is determined by the `rect` parameter, which is a quadruple in the format of (x, y, width, height).
 * - x: X coordinate of watermark, which is a floating-point number between 0 and 1.
 * - y: Y coordinate of watermark, which is a floating-point number between 0 and 1.
 * - width: width of watermark, which is a floating-point number between 0 and 1.
 * - height: it does not need to be set. The SDK will automatically calculate it according to the watermark image's aspect ratio.
 *
 * Sample parameter:
 * If the encoding resolution of the current video is 540x960, and the `rect` parameter is set to (0.1, 0.1, 0.2, 0.0),
 * then the coordinates of the top-left point of the watermark will be (540 * 0.1, 960 * 0.1), i.e., (54, 96), the watermark width will be `540 * 0.2 = 108 px`, and the watermark height will be calculated automatically by the SDK based on the
 * watermark image's aspect ratio.
 *
 * @param image Watermark image, which must be a PNG image with transparent background
 * @param streamType Specify for which image to set the watermark. For more information, please see {@link TRTCVideoStreamType}.
 * @param rect Unified coordinates of the watermark relative to the encoded resolution. Value range of `x`, `y`, `width`, and `height`: 0–1.
 * @note If you want to set watermarks for both the primary image (generally for the camera) and the substream image (generally for screen sharing), you need to call this API twice with `streamType` set to different values.
 */
- (void)setWatermark:(nullable TXImage *)image streamType:(TRTCVideoStreamType)streamType rect:(CGRect)rect;

/////////////////////////////////////////////////////////////////////////////////
//
//                    Background music and sound effect APIs
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 8.1 Get sound effect management class (TXAudioEffectManager).
 *
 * `TXAudioEffectManager` is a sound effect management API, through which you can implement the following features:
 * - Background music: both online music and local music can be played back with various features such as speed adjustment, pitch adjustment, original voice, accompaniment, and loop.
 * - In-ear monitoring: the sound captured by the mic is played back in the headphones in real time, which is generally used for music live streaming.
 * - Reverb effect: karaoke room, small room, big hall, deep, resonant, and other effects.
 * - Voice changing effect: young girl, middle-aged man, heavy metal, and other effects.
 * - Short sound effect: short sound effect files such as applause and laughter are supported (for files less than 10 seconds in length, please set the `isShortFile` parameter to `$YES$`).
 * @return sound effect management class {@link TXAudioEffectManager}.
 */
- (TXAudioEffectManager *)getAudioEffectManager;

/**
 * 8.2 Enable system audio capturing(iOS not supported).
 *
 * This API captures audio data from the sound card of a macOS computer and mixes it into the current audio data stream of the SDK, so that other users in the room can also hear the sound played back on the current macOS system.
 * In use cases such as video teaching or music live streaming, the teacher can use this feature to let the SDK capture the sound in the video played back by the teacher, so that students in the same room can also hear the sound in the video.
 * @note
 *   1. This feature needs to install a virtual audio device plugin on the user's macOS system. After the installation is completed, the SDK will capture sound from the installed virtual device.
 *   2. The SDK will automatically download the appropriate plugin from the internet for installation, but the download may be slow. If you want to speed up this process, you can package the virtual audio plugin file into the `Resources` directory of
 * your app bundle.
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)startSystemAudioLoopback;
#endif

/**
 * 8.3 Stop system audio capturing(iOS not supported).
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)stopSystemAudioLoopback;
#endif

/**
 * 8.4 Set the volume of system audio capturing.
 *
 * @param volume Set volume. Value range: [0, 150]. Default value: 100
 */
- (void)setSystemAudioLoopbackVolume:(uint32_t)volume;

/////////////////////////////////////////////////////////////////////////////////
//
//                   Real-time Transcription Translation Interface
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 9.1 Get AI transcriber manager (AITranscriberManager).
 *
 * Through AI transcriber manager, you can start/stop real-time transcription service to perform real-time transcription and translation on the audio of specified users.
 * @return AI transcriber manager {@link AITranscriberManager}.
 */
- (AITranscriberManager *)getAITranscriberManager;

/////////////////////////////////////////////////////////////////////////////////
//
//                    Screen sharing APIs
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 10.1 Start in-app screen sharing (for iOS 13.0 and above only).
 *
 * This API captures the real-time screen content of the current application and shares it with other users in the same room. It is applicable to iOS 13.0 and above.
 * If you want to capture the screen content of the entire iOS system (instead of the current application), we recommend you use {@link startScreenCaptureByReplaykit}.
 * Video encoding parameters recommended for screen sharing on iPhone ({@link TRTCVideoEncParam}):
 *  - Resolution (videoResolution): 1280x720
 *  - Frame rate (videoFps): 10 fps
 *  - Bitrate (videoBitrate): 1600 Kbps
 *  - Resolution adaption (enableAdjustRes): NO
 *
 * @param streamType Channel used for screen sharing, which can be the primary stream ({@link $TRTCVideoStreamTypeBig$}) or substream ({@link $TRTCVideoStreamTypeSub$}).
 * @param encParams Video encoding parameters for screen sharing. We recommend you use the above configuration.If you set `encParams` to `nil`, the SDK will use the video encoding parameters you set before calling the {@link startScreenCapture} API.
 */
#if TARGET_OS_IPHONE
- (void)startScreenCaptureInApp:(TRTCVideoStreamType)streamType encParam:(TRTCVideoEncParam *)encParams API_AVAILABLE(ios(13.0));
#endif

/**
 * 10.1 Start system-level screen sharing (for iOS 11.0 and above only).
 *
 * This API supports capturing the screen of the entire iOS system, which can implement system-wide screen sharing similar to VooV Meeting.
 * However, the integration steps are slightly more complicated than those of {@link startScreenCaptureInApp}. You need to implement a ReplayKit extension module for your application.
 * For more information, please see [iOS](https://www.tencentcloud.com/document/product/647/37338)
 * Video encoding parameters recommended for screen sharing on iPhone ({@link TRTCVideoEncParam}):
 *  - Resolution (videoResolution): 1280x720
 *  - Frame rate (videoFps): 10 fps
 *  - Bitrate (videoBitrate): 1600 Kbps
 *  - Resolution adaption (enableAdjustRes): NO
 *
 * @param streamType Channel used for screen sharing, which can be the primary stream ({@link $TRTCVideoStreamTypeBig$}) or substream ({@link $TRTCVideoStreamTypeSub$}).
 * @param encParams Video encoding parameters for screen sharing. We recommend you use the above configuration.
 *        If you set `encParams` to `nil`, the SDK will use the video encoding parameters you set before calling the `startScreenCapture` API.
 * @param appGroup Specify the `Application Group Identifier` shared by your application and the screen sharing process. You can specify this parameter as `nil`, but we recommend you set it as instructed in the documentation for higher reliability.
 */
#if TARGET_OS_IPHONE
- (void)startScreenCaptureByReplaykit:(TRTCVideoStreamType)streamType encParam:(TRTCVideoEncParam *)encParams appGroup:(NSString *)appGroup API_AVAILABLE(ios(11.0));
#endif

/**
 * 10.1 Start screen sharing.
 *
 * This API can capture the content of the entire screen or a specified application and share it with other users in the same room.
 * @param view Parent control of the rendering control, which can be set to a null value, indicating not to display the preview of the shared screen.
 * @param streamType Channel used for screen sharing, which can be the primary stream ({@link $TRTCVideoStreamTypeBig$}) or substream ({@link $TRTCVideoStreamTypeSub$}).
 * @param encParam Image encoding parameters used for screen sharing, which can be set to empty, indicating to let the SDK choose the optimal encoding parameters (such as resolution and bitrate).
 * @note
 * 1. A user can publish at most one primary stream ({@link $TRTCVideoStreamTypeBig$}) and one substream ({@link $TRTCVideoStreamTypeSub$}) at the same time.
 * 2. By default, screen sharing uses the substream image. If you want to use the primary stream for screen sharing, you need to stop camera capturing (through {@link stopLocalPreview}) in advance to avoid conflicts.
 * 3. Only one user can use the substream for screen sharing in the same room at any time; that is, only one user is allowed to enable the substream in the same room at any time.
 * 4. When there is already a user in the room using the substream for screen sharing, calling this API will return the `onError(ERR_SERVER_CENTER_ANOTHER_USER_PUSH_SUB_VIDEO)` callback from {@link $TRTCCloudDelegate$}.
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)startScreenCapture:(nullable NSView *)view streamType:(TRTCVideoStreamType)streamType encParam:(nullable TRTCVideoEncParam *)encParam;
#endif

/**
 * 10.2 Stop screen sharing.
 */
- (int)stopScreenCapture API_AVAILABLE(ios(11.0));

/**
 * 10.3 Pause screen sharing.
 *
 * @note Begin from v11.5 version, paused screen capture will use the last frame to output at a frame rate of 1fps.
 */
- (int)pauseScreenCapture API_AVAILABLE(ios(11.0));

/**
 * 10.4 Resume screen sharing.
 */
- (int)resumeScreenCapture API_AVAILABLE(ios(11.0));

/**
 * 10.5 Enumerate shareable screens and windows (for macOS only).
 *
 * When you integrate the screen sharing feature of a desktop system, you generally need to display a UI for selecting the sharing target, so that users can use the UI to choose whether to share the entire screen or a certain window.
 * Through this API, you can query the IDs, names, and thumbnails of sharable windows on the current system. We provide a default UI implementation in the demo for your reference.
 * @param thumbnailSize Specify the thumbnail size of the window to be obtained. The thumbnail can be drawn on the window selection UI.
 * @param iconSize Specify the icon size of the window to be obtained.
 * @return List of windows (including the screen)
 * @note The returned list contains the screen and the application windows. The screen is the first element in the list. If the user has multiple displays, then each display is a sharing target.
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (NSArray<TRTCScreenCaptureSourceInfo *> *)getScreenCaptureSourcesWithThumbnailSize:(CGSize)thumbnailSize iconSize:(CGSize)iconSize;
#endif

/**
 * 10.6 Select the screen or window to share (for macOS only).
 *
 * After you get the sharable screen and windows through {@link getScreenCaptureSources}, you can call this API to select the target screen or window you want to share.
 * During the screen sharing process, you can also call this API at any time to switch the sharing target.
 * @param screenSource     Specify sharing source
 * @param rect             Specify the area to be captured (set this parameter to `CGRectZero`: when the sharing target is a window, the entire window will be shared, and when the sharing target is the desktop, the entire desktop will be shared)
 * @param capturesCursor   Whether to capture mouse cursor
 * @param highlight        Whether to highlight the window being shared
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)selectScreenCaptureTarget:(TRTCScreenCaptureSourceInfo *)screenSource rect:(CGRect)rect capturesCursor:(BOOL)capturesCursor highlight:(BOOL)highlight;
#endif

/**
 * 10.7 Set the video encoding parameters of screen sharing (i.e., substream) (for desktop and mobile systems).
 *
 * This API can set the image quality of screen sharing (i.e., the substream) viewed by remote users, which is also the image quality of screen sharing in on-cloud recording files.
 * Please note the differences between the following two APIs:
 * - {@link setVideoEncoderParam} is used to set the video encoding parameters of the primary stream image ({@link $TRTCVideoStreamTypeBig$}, generally for camera).
 * - {@link setSubStreamEncoderParam} is used to set the video encoding parameters of the substream image ({@link $TRTCVideoStreamTypeSub$}, generally for screen sharing).
 *
 * @param param Substream encoding parameters. For more information, please see {@link TRTCVideoEncParam}.
 */
- (void)setSubStreamEncoderParam:(TRTCVideoEncParam *)param;

/**
 * 10.8 Set the audio mixing volume of screen sharing (for desktop systems only).
 *
 * The greater the value, the larger the ratio of the screen sharing volume to the mic volume. We recommend you not set a high value for this parameter as a high volume will cover the mic sound.
 * @param volume Set audio mixing volume. Value range: [0, 150]
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)setSubStreamMixVolume:(NSInteger)volume;
#endif

/**
 * 10.9 Add specified windows to the exclusion list of screen sharing (for desktop systems only).
 *
 * The excluded windows will not be shared. This feature is generally used to add a certain application's window to the exclusion list to avoid privacy issues.
 * You can set the filtered windows before starting screen sharing or dynamically add the filtered windows during screen sharing.
 * @param window Window not to be shared
 * @note
 *  1. This API takes effect only if the `type` in {@link TRTCScreenCaptureSourceInfo} is specified as {@link TRTCScreenCaptureSourceTypeScreen}; that is, the feature of excluding specified windows works only when the entire screen is shared.
 *  2. The windows added to the exclusion list through this API will be automatically cleared by the SDK after room exit.
 *  3. On macOS, please pass in the window ID (CGWindowID), which can be obtained through the `sourceId` member in {@link TRTCScreenCaptureSourceInfo}.
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)addExcludedShareWindow:(NSInteger)windowID;
#endif

/**
 * 10.10 Remove specified windows from the exclusion list of screen sharing (for desktop systems only).
 *
 * @param windowID
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)removeExcludedShareWindow:(NSInteger)windowID;
#endif

/**
 * 10.11 Remove all windows from the exclusion list of screen sharing (for desktop systems only).
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)removeAllExcludedShareWindows;
#endif

/**
 * 10.12 Add specified windows to the inclusion list of screen sharing (for desktop systems only).
 *
 * This API takes effect only if the `type` in {@link TRTCScreenCaptureSourceInfo} is specified as {@link TRTCScreenCaptureSourceTypeWindow}; that is, the feature of additionally including specified windows works only when a window is shared.
 * You can call it before or after {@link startScreenCapture}.
 * @param windowID Window to be shared (which is a window handle `HWND` on Windows)
 * @note The windows added to the inclusion list by this method will be automatically cleared by the SDK after room exit.
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)addIncludedShareWindow:(NSInteger)windowID;
#endif

/**
 * 10.13 Remove specified windows from the inclusion list of screen sharing (for desktop systems only).
 *
 * This API takes effect only if the `type` in {@link TRTCScreenCaptureSourceInfo} is specified as {@link TRTCScreenCaptureSourceTypeWindow}.
 * That is, the feature of additionally including specified windows works only when a window is shared.
 * @param windowID Window to be shared (window ID on macOS or HWND on Windows)
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)removeIncludedShareWindow:(NSInteger)windowID;
#endif

/**
 * 10.14 Remove all windows from the inclusion list of screen sharing (for desktop systems only).
 *
 * This API takes effect only if the `type` in {@link TRTCScreenCaptureSourceInfo} is specified as {@link TRTCScreenCaptureSourceTypeWindow}.
 * That is, the feature of additionally including specified windows works only when a window is shared.
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)removeAllIncludedShareWindows;
#endif

/////////////////////////////////////////////////////////////////////////////////
//
//                    Custom capturing and rendering APIs
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 11.1 Enable/Disable custom video capturing mode.
 *
 * After this mode is enabled, the SDK will not run the original video capturing process (i.e., stopping camera data capturing and beauty filter operations) and will retain only the video encoding and sending capabilities.
 * You need to use {@link sendCustomVideoData} to continuously insert the captured video image into the SDK.
 * @param streamType Specify video stream type ({@link $TRTCVideoStreamTypeBig$}: HD big image; {@link $TRTCVideoStreamTypeSub$}: substream image).
 * @param enable Whether to enable. Default value: $NO$
 */
- (void)enableCustomVideoCapture:(TRTCVideoStreamType)streamType enable:(BOOL)enable;

/**
 * 11.2 Deliver captured video frames to SDK.
 *
 * You can use this API to deliver video frames you capture to the SDK, and the SDK will encode and transfer them through its own network module.
 * We recommend you enter the following information for the {@link TRTCVideoFrame} parameter (other fields can be left empty):
 * - pixelFormat: {@link TRTCVideoPixelFormat_NV12} is recommended.
 * - bufferType: {@link TRTCVideoBufferType_PixelBuffer} is recommended.
 * - pixelBuffer: common video data format on iOS/macOS.
 * - data: raw video data format, which is used if `bufferType` is `NSData`.
 * - timestamp (ms): Set it to the timestamp when video frames are captured, which you can obtain by calling {@link generateCustomPTS} after getting a video frame.
 * - width: video image length, which needs to be set if `bufferType` is `NSData`.
 * - height: video image width, which needs to be set if `bufferType` is `NSData`.
 * For more information, please see [Custom Capturing and Rendering](https://www.tencentcloud.com/document/product/647/35158).
 * @param streamType Specify video stream type ({@link $TRTCVideoStreamTypeBig$}: HD big image; {@link $TRTCVideoStreamTypeSub$}: substream image).
 * @param frame Video data. For `bufferType`, {@link TRTCVideoBufferType_PixelBuffer} is recommended; for `pixelFormat`, {@link TRTCVideoPixelFormat_NV12} is recommended. Refer to {@link TRTCVideoFrame} for more supported formats.
 * @note
 * 1. We recommend you call the {@link generateCustomPTS} API to get the `timestamp` value of a video frame immediately after capturing it, so as to achieve the best audio/video sync effect.
 * 2. The video frame rate eventually encoded by the SDK is not determined by the frequency at which you call this API, but by the FPS you set in {@link setVideoEncoderParam}.
 * 3. Please try to keep the calling interval of this API even; otherwise, problems will occur, such as unstable output frame rate of the encoder or out-of-sync audio/video.
 */
- (void)sendCustomVideoData:(TRTCVideoStreamType)streamType frame:(TRTCVideoFrame *)frame;

/**
 * 11.3 Enable custom audio capturing mode.
 *
 * After this mode is enabled, the SDK will not run the original audio capturing process (i.e., stopping mic data capturing) and will retain only the audio encoding and sending capabilities.
 * You need to use {@link sendCustomAudioData} to continuously insert the captured audio data into the SDK.
 * @param enable Whether to enable. Default value: $NO$
 * @note As acoustic echo cancellation (AEC) requires strict control over the audio capturing and playback time, after custom audio capturing is enabled, AEC may fail.
 */
- (void)enableCustomAudioCapture:(BOOL)enable;

/**
 * 11.4 Deliver captured audio data to SDK.
 *
 * We recommend you enter the following information for the {@link TRTCAudioFrame} parameter (other fields can be left empty):
 * - audioFormat: audio data format, which can only be `TRTCAudioFrameFormatPCM`.
 * - data: audio frame buffer. Audio frame data must be in PCM format, and it supports a frame length of 5–100 ms (20 ms is recommended). Length calculation method: **for example, if the sample rate is 48000, then the frame length for mono channel
 * will be `48000 * 0.02s * 1 * 16 bit = 15360 bit = 1920 bytes`.**
 * - sampleRate: sample rate. Valid values: 16000, 24000, 32000, 44100, 48000.
 * - channel: number of channels (if stereo is used, data is interwoven). Valid values: 1: mono channel; 2: dual channel.
 * - timestamp (ms): Set it to the timestamp when audio frames are captured, which you can obtain by calling {@link generateCustomPTS} after getting a audio frame.
 * For more information, please see [Custom Capturing and Rendering](https://www.tencentcloud.com/document/product/647/47635).
 * @param frame Audio data
 * @note Please call this API accurately at intervals of the frame length; otherwise, sound lag may occur due to uneven data delivery intervals.
 */
- (void)sendCustomAudioData:(TRTCAudioFrame *)frame;

/**
 * 11.5 Enable/Disable custom audio track.
 *
 * After this feature is enabled, you can mix a custom audio track into the SDK through this API. With two boolean parameters, you can control whether to play back this track remotely or locally.
 * @param enablePublish Whether the mixed audio track should be played back remotely. Default value: $NO$
 * @param enablePlayout Whether the mixed audio track should be played back locally. Default value: $NO$
 * @note If you specify both `enablePublish` and `enablePlayout` as `$NO$`, the custom audio track will be completely closed.
 */
- (void)enableMixExternalAudioFrame:(BOOL)enablePublish playout:(BOOL)enablePlayout;

/**
 * 11.6 Mix custom audio track into SDK.
 *
 * Before you use this API to mix custom PCM audio into the SDK, you need to first enable custom audio tracks through {@link enableMixExternalAudioFrame}.
 * You are expected to feed audio data into the SDK at an even pace, but we understand that it can be challenging to call an API at absolutely regular intervals.
 * Given this, we have provided a buffer pool in the SDK, which can cache the audio data you pass in to reduce the fluctuations in intervals between API calls.
 * The value returned by this API indicates the size (ms) of the buffer pool. For example, if `50` is returned, it indicates that the buffer pool has 50 ms of audio data. As long as you call this API again within 50 ms, the SDK can make sure that
 * continuous audio data is mixed. If the value returned is `100` or greater, you can wait after an audio frame is played to call the API again. If the value returned is smaller than `100`, then there isn’t enough data in the buffer pool, and you
 * should feed more audio data into the SDK until the data in the buffer pool is above the safety level. Fill the fields in {@link TRTCAudioFrame} as follows (other fields are not required).
 * - `data`: audio frame buffer. Audio frames must be in PCM format. Each frame can be 5-100 ms (20 ms is recommended) in duration. Assume that the sample rate is 48000, and sound channels mono-channel. Then the **frame size would be 48000 x 0.02s x
 * 1 x 16 bit = 15360 bit = 1920 bytes**.
 * - `sampleRate`: sample rate. Valid values: 16000, 24000, 32000, 44100, 48000
 * - `channel`: number of sound channels (if dual-channel is used, data is interleaved). Valid values: `1` (mono-channel); `2` (dual channel)
 * - `timestamp`: timestamp (ms). Set it to the timestamp when audio frames are captured, which you can obtain by calling {@link generateCustomPTS} after getting an audio frame.
 * @param frame Audio data
 * @return If the value returned is `0` or greater, the value represents the current size of the buffer pool; if the value returned is smaller than `0`, it means that an error occurred. `-1` indicates that you didn’t call {@link
 * enableMixExternalAudioFrame} to enable custom audio tracks.
 */
- (int)mixExternalAudioFrame:(TRTCAudioFrame *)frame;

/**
 * 11.7 Set the publish volume and playback volume of mixed custom audio track.
 *
 * @param publishVolume set the publish volume，from 0 to 150, -1 means no change
 * @param playoutVolume set the play volume，from 0 to 150, -1 means no change
 */
- (void)setMixExternalAudioVolume:(NSInteger)publishVolume playoutVolume:(NSInteger)playoutVolume;

/**
 * 11.8 Generate custom capturing timestamp.
 *
 * This API is only suitable for the custom capturing mode and is used to solve the problem of out-of-sync audio/video caused by the inconsistency between the capturing time and delivery time of audio/video frames.
 * When you call APIs such as {@link sendCustomVideoData} or {@link sendCustomAudioData} for custom video or audio capturing, please use this API as instructed below:
 *  1. First, when a video or audio frame is captured, call this API to get the corresponding PTS timestamp.
 *  2. Then, send the video or audio frame to the preprocessing module you use (such as a third-party beauty filter or sound effect component).
 *  3. When you actually call {@link sendCustomVideoData} or {@link sendCustomAudioData} for delivery, assign the PTS timestamp recorded when the frame was captured to the `timestamp` field in {@link TRTCVideoFrame} or {@link TRTCAudioFrame}.
 * @return Timestamp in ms
 */
+ (uint64_t)generateCustomPTS;

/**
 * 11.9 Set video data callback for third-party beauty filters.
 *
 * After this callback is set, the SDK will call back the captured video frames through the `delegate` you set and use them for further processing by a third-party beauty filter component. Then, the SDK will encode and send the processed video
 * frames.
 * @param delegate Custom preprocessing callback. For more information, please see {@link TRTCVideoFrameDelegate}
 * @param pixelFormat Specify the format of the pixel called back. Currently, only {@link TRTCVideoPixelFormat_Texture_2D} is supported
 * @param bufferType Specify the format of the data called back. Currently, only {@link TRTCVideoBufferType_Texture} is supported
 * @return 0: success; values smaller than 0: error(For more information, please see {@link TXLiteAVError})
 */
- (int)setLocalVideoProcessDelegete:(nullable id<TRTCVideoFrameDelegate>)delegate pixelFormat:(TRTCVideoPixelFormat)pixelFormat bufferType:(TRTCVideoBufferType)bufferType;

/**
 * 11.10 Set the callback of custom rendering for local video.
 *
 * After this callback is set, the SDK will skip its own rendering process and call back the captured data. Therefore, you need to complete image rendering on your own.
 * - `pixelFormat` specifies the format of the called back data, such as NV12, I420, and 32BGRA.
 * - `bufferType` specifies the buffer type. `PixelBuffer` has the highest efficiency, while `NSData` makes the SDK perform a memory conversion internally, which will result in extra performance loss.
 * For more information, please see [Custom Capturing and Rendering](https://www.tencentcloud.com/document/product/647/35158).
 * @param delegate    Callback for custom rendering
 * @param pixelFormat Specify the format of the pixel called back
 * @param bufferType PixelBuffer: this can be directly converted to `UIImage` by using `imageWithCVImageBuffer`; NSData: this is memory-mapped video data.
 * @return 0: success; values smaller than 0: error(For more information, please see {@link TXLiteAVError})
 */
- (int)setLocalVideoRenderDelegate:(nullable id<TRTCVideoRenderDelegate>)delegate pixelFormat:(TRTCVideoPixelFormat)pixelFormat bufferType:(TRTCVideoBufferType)bufferType;

/**
 * 11.11 Set the callback of custom rendering for remote video.
 *
 * After this callback is set, the SDK will skip its own rendering process and call back the captured data. Therefore, you need to complete image rendering on your own.
 * - `pixelFormat` specifies the format of the called back data, such as NV12, I420, and 32BGRA.
 * - `bufferType` specifies the buffer type. `PixelBuffer` has the highest efficiency, while `NSData` makes the SDK perform a memory conversion internally, which will result in extra performance loss.
 * For more information, please see [Custom Capturing and Rendering](https://www.tencentcloud.com/document/product/647/35158).
 * @param userId ID of the specified remote user
 * @param delegate  Callback for custom rendering
 * @param pixelFormat Specify the format of the pixel called back
 * @param bufferType PixelBuffer: this can be directly converted to `UIImage` by using `imageWithCVImageBuffer`; NSData: this is memory-mapped video data.
 * @return 0: success; values smaller than 0: error
 * @note Before this API is called, `startRemoteView(nil)` needs to be called to get the video stream of the remote user (`view` can be set to `nil` for this end); otherwise, there will be no data called back.
 */
- (int)setRemoteVideoRenderDelegate:(NSString *)userId delegate:(nullable id<TRTCVideoRenderDelegate>)delegate pixelFormat:(TRTCVideoPixelFormat)pixelFormat bufferType:(TRTCVideoBufferType)bufferType;

/**
 * 11.12 Set custom audio data callback.
 *
 * After this callback is set, the SDK will internally call back the audio data (in PCM format), including:
 * - {@link onCapturedAudioFrame}: callback of the audio data captured by the local mic
 * - {@link onLocalProcessedAudioFrame}: callback of the audio data captured by the local mic and preprocessed by the audio module
 * - {@link $onRemoteUserAudioFrame$}: audio data from each remote user before audio mixing
 * - {@link onMixedPlayAudioFrame}: callback of the audio data that will be played back by the system after audio streams are mixed
 * @note Setting the callback to null indicates to stop the custom audio callback, while setting it to a non-null value indicates to start the custom audio callback.
 */
- (void)setAudioFrameDelegate:(nullable id<TRTCAudioFrameDelegate>)delegate;

/**
 * 11.13 Set the callback format of audio frames captured by local mic.
 *
 * This API is used to set the `AudioFrame` format called back by {@link onCapturedAudioFrame}:
 * - sampleRate: sample rate. Valid values: 16000, 32000, 44100, 48000
 * - channel: number of channels (if stereo is used, data is interwoven). Valid values: 1: mono channel; 2: dual channel
 * - samplesPerCall: number of sample points, which defines the frame length of the callback data. The frame length must be an integer multiple of 10 ms.
 * If you want to calculate the callback frame length in milliseconds, the formula for converting the number of milliseconds into the number of sample points is as follows: number of sample points = number of milliseconds * sample rate / 1000
 * For example, if you want to call back the data of 20 ms frame length with 48000 sample rate, then the number of sample points should be entered as `960 = 20 * 48000 / 1000`.
 * Note that the frame length of the final callback is in bytes, and the calculation formula for converting the number of sample points into the number of bytes is as follows: `number of bytes = number of sample points * number of channels * 2 (bit
 * width)` For example, if the parameters are 48000 sample rate, dual channel, 20 ms frame length, and 960 sample points, then the number of bytes is `3840 = 960 * 2 * 2`
 * @param format Audio data callback format
 * @return 0: success; values smaller than 0: error(For more information, please see {@link TXLiteAVError})
 */
- (int)setCapturedAudioFrameDelegateFormat:(TRTCAudioFrameDelegateFormat *)format;

/**
 * 11.14 Set the callback format of preprocessed local audio frames.
 *
 * This API is used to set the `AudioFrame` format called back by {@link onLocalProcessedAudioFrame}:
 * - sampleRate: sample rate. Valid values: 16000, 32000, 44100, 48000
 * - channel: number of channels (if stereo is used, data is interwoven). Valid values: 1: mono channel; 2: dual channel
 * - samplesPerCall: number of sample points, which defines the frame length of the callback data. The frame length must be an integer multiple of 10 ms.
 * If you want to calculate the callback frame length in milliseconds, the formula for converting the number of milliseconds into the number of sample points is as follows: `number of sample points = number of milliseconds * sample rate / 1000`.
 * For example, if you want to call back the data of 20 ms frame length with 48000 sample rate, then the number of sample points should be entered as `960 = 20 * 48000 / 1000`.
 * Note that the frame length of the final callback is in bytes, and the calculation formula for converting the number of sample points into the number of bytes is as follows: `number of bytes = number of sample points * number of channels * 2 (bit
 * width)`. For example, if the parameters are 48000 sample rate, dual channel, 20 ms frame length, and 960 sample points, then the number of bytes is `3840 = 960 * 2 * 2`.
 * @param format Audio data callback format
 * @return 0: success; values smaller than 0: error(For more information, please see {@link TXLiteAVError})
 */
- (int)setLocalProcessedAudioFrameDelegateFormat:(TRTCAudioFrameDelegateFormat *)format;

/**
 * 11.15 Set the callback format of audio frames to be played back by system.
 *
 * This API is used to set the `AudioFrame` format called back by {@link onMixedPlayAudioFrame}:
 * - sampleRate: sample rate. Valid values: 16000, 32000, 44100, 48000
 * - channel: number of channels (if stereo is used, data is interwoven). Valid values: 1: mono channel; 2: dual channel
 * - samplesPerCall: number of sample points, which defines the frame length of the callback data. The frame length must be an integer multiple of 10 ms.
 * If you want to calculate the callback frame length in milliseconds, the formula for converting the number of milliseconds into the number of sample points is as follows: `number of sample points = number of milliseconds * sample rate / 1000`.
 * For example, if you want to call back the data of 20 ms frame length with 48000 sample rate, then the number of sample points should be entered as `960 = 20 * 48000 / 1000`.
 * Note that the frame length of the final callback is in bytes, and the calculation formula for converting the number of sample points into the number of bytes is as follows: `number of bytes = number of sample points * number of channels * 2 (bit
 * width)`. For example, if the parameters are 48000 sample rate, dual channel, 20 ms frame length, and 960 sample points, then the number of bytes is `3840 = 960 * 2 * 2`.
 * @param format Audio data callback format
 * @return 0: success; values smaller than 0: error(For more information, please see {@link TXLiteAVError})
 */
- (int)setMixedPlayAudioFrameDelegateFormat:(TRTCAudioFrameDelegateFormat *)format;

/**
 * 11.16 Enabling custom audio playback.
 *
 * You can use this API to enable custom audio playback if you want to connect to an external audio device or control the audio playback logic by yourself.
 * After you enable custom audio playback, the SDK will stop using its audio API to play back audio. You need to call {@link getCustomAudioRenderingFrame} to get audio frames and play them by yourself.
 * @param enable Whether to enable custom audio playback. It's disabled by default.
 * @note The parameter must be set before room entry to take effect.
 */
- (void)enableCustomAudioRendering:(BOOL)enable;

/**
 * 11.17 Getting playable audio data.
 *
 * Before calling this API, you need to first enable custom audio playback using {@link enableCustomAudioRendering}.
 * Fill the fields in {@link TRTCAudioFrame} as follows (other fields are not required):
 * - `sampleRate`: sample rate (required). Valid values: 16000, 24000, 32000, 44100, 48000
 * - `channel`: number of sound channels (required). `1`: mono-channel; `2`: dual-channel; if dual-channel is used, data is interleaved.
 * - `data`: the buffer used to get audio data. You need to allocate memory for the buffer based on the duration of an audio frame.
 * The PCM data obtained can have a frame duration of 10 ms or 20 ms. 20 ms is recommended.
 * Assume that the sample rate is 48000, and sound channels mono-channel. The buffer size for a 20 ms audio frame would be `48000 x 0.02s x 1 x 16 bit = 15360 bit = 1920 bytes`.
 * @param audioFrame Audio frames
 * @note
 *   1. You must set `sampleRate` and `channel` in `audioFrame`, and allocate memory for one frame of audio in advance.
 *   2. The SDK will fill the data automatically based on `sampleRate` and `channel`.
 *   3. We recommend that you use the system’s audio playback thread to drive the calling of this API, so that it is called each time the playback of an audio frame is complete.
 */
- (void)getCustomAudioRenderingFrame:(TRTCAudioFrame *)audioFrame;

/////////////////////////////////////////////////////////////////////////////////
//
//                    Custom message sending APIs
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 12.1 Use UDP channel to send custom message to all users in room.
 *
 * This API allows you to use TRTC's UDP channel to broadcast custom data to other users in the current room for signaling transfer.
 * Other users in the room can receive the message through the `onRecvCustomCmdMsg` callback in {@link $TRTCCloudDelegate$}.
 * @param cmdID Message ID. Value range: [1, 10]
 * @param data Message to be sent. The maximum length of one single message is 1 KB.
 * @param reliable Whether reliable sending is enabled. Reliable sending can achieve a higher success rate but with a longer reception delay than unreliable sending.
 * @param ordered Whether orderly sending is enabled, i.e., whether the data packets should be received in the same order in which they are sent; if so, a certain delay will be caused.
 * @return $YES$: sent the message successfully; $NO$: failed to send the message.
 * @note
 * 1. Up to 30 messages can be sent per second to all users in the room (this is not supported for web and mini program currently. this limit is shared with {@link sendSEIMsg}).
 * 2. A packet can contain up to 1 KB of data; if the threshold is exceeded, the packet is very likely to be discarded by the intermediate router or server.(this limit is shared with {@link sendSEIMsg}).
 * 3. A client can send up to 16 KB of data in total per second.
 * 4. `reliable` and `ordered` must be set to the same value (`$YES$` or `$NO$`) and cannot be set to different values currently.
 * 5. We strongly recommend you set different `cmdID` values for messages of different types. This can reduce message delay when orderly sending is required.
 * 6. Currently only the anchor role is supported.
 */
- (BOOL)sendCustomCmdMsg:(NSInteger)cmdID data:(NSData *)data reliable:(BOOL)reliable ordered:(BOOL)ordered;

/**
 * 12.2 Use SEI channel to send custom message to all users in room.
 *
 * This API allows you to use TRTC's SEI channel to broadcast custom data to other users in the current room for signaling transfer.
 * The header of a video frame has a header data block called SEI. This API works by embedding the custom signaling data you want to send in the SEI block and sending it together with the video frame.
 * Therefore, the SEI channel has a better compatibility than {@link sendCustomCmdMsg} as the signaling data can be transferred to the CSS CDN along with the video frame.
 * However, because the data block of the video frame header cannot be too large, we recommend you limit the size of the signaling data to only a few bytes when using this API.
 * The most common use is to embed the custom timestamp into video frames through this API so as to implement a perfect alignment between the message and video image (such as between the teaching material and video signal in the education scenario).
 * Other users in the room can receive the message through the `onRecvSEIMsg` callback in {@link $TRTCCloudDelegate$}.
 * @param data Data to be sent, which can be up to 1 KB (1,000 bytes)
 * @param repeatCount Data sending count
 * @return $YES$: the message is allowed and will be sent with subsequent video frames; $NO$: the message is not allowed to be sent
 * @note This API has the following restrictions:
 * 1. The data will not be instantly sent after this API is called; instead, it will be inserted into the next video frame after the API call.
 * 2. Up to 30 messages can be sent per second to all users in the room (this limit is shared with {@link sendCustomCmdMsg}).
 * 3. Each packet can be up to 1 KB (this limit is shared with {@link sendCustomCmdMsg}). If a large amount of data is sent, the video bitrate will increase, which may reduce the video quality or even cause lagging.
 * 4. Each client can send up to 16 KB of data in total per second (this limit is shared with {@link sendCustomCmdMsg}).
 * 5. If multiple times of sending is required (i.e., `repeatCount` > 1), the data will be inserted into subsequent `repeatCount` video frames in a row for sending, which will increase the video bitrate.
 * 6. If `repeatCount` is greater than 1, the data will be sent for multiple times, and the same message may be received multiple times in the {@link onRecvSEIMsg} callback; therefore, deduplication is required.
 */
- (BOOL)sendSEIMsg:(NSData *)data repeatCount:(int)repeatCount;

/////////////////////////////////////////////////////////////////////////////////
//
//                    Network test APIs
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 13.1 Start network speed test (used before room entry).
 *
 * @param params speed test options
 * @return interface call result, <0: failure
 * @note
 * 1. The speed measurement process will incur a small amount of basic service fees, See [Purchase Guide > Base Services](https://intl.cloud.tencent.com/document/product/647/34610?lang=en&pg=#basic-services).
 * 2. Please perform the Network speed test before room entry, because if performed after room entry, the test will affect the normal audio/video transfer, and its result will be inaccurate due to interference in the room.
 * 3. Only one network speed test task is allowed to run at the same time.
 */
- (int)startSpeedTest:(TRTCSpeedTestParams *)params;

/**
 * 13.2 Stop network speed test.
 */
- (void)stopSpeedTest;

/////////////////////////////////////////////////////////////////////////////////
//
//                    Debugging APIs
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 14.1 Get SDK version information.
 */
+ (NSString *)getSDKVersion;

/**
 * 14.2 Set log output level.
 *
 * @param level For more information, please see {@link TRTCLogLevel}. Default value: {@link TRTCLogLevelNone}
 */
+ (void)setLogLevel:(TRTCLogLevel)level;

/**
 * 14.3 Enable/Disable console log printing.
 *
 * @param enabled Specify whether to enable it, which is disabled by default
 */
+ (void)setConsoleEnabled:(BOOL)enabled;

/**
 * 14.4 Enable/Disable local log compression.
 *
 * If compression is enabled, the log size will significantly reduce, but logs can be read only after being decompressed by the Python script provided by Tencent Cloud.
 * If compression is disabled, logs will be stored in plaintext and can be read directly in Notepad, but will take up more storage capacity.
 * @param enabled Specify whether to enable it, which is enabled by default
 */
+ (void)setLogCompressEnabled:(BOOL)enabled;

/**
 * 14.5 Set local log storage path.
 *
 * You can use this API to change the default storage path of the SDK's local logs, which is as follows:
 * - Windows: C:/Users/[username]/AppData/Roaming/liteav/log, i.e., under `%appdata%/liteav/log`.
 * - iOS or macOS: under `sandbox Documents/log`.
 * - Android: under `/app directory/files/log/liteav/`.
 * @note Please be sure to call this API before all other APIs and make sure that the directory you specify exists and your application has read/write permissions of the directory.
 * @param path Log storage path
 */
+ (void)setLogDirPath:(NSString *)path;

/**
 * 14.6 Set log callback.
 */
+ (void)setLogDelegate:(nullable id<TRTCLogDelegate>)logDelegate;

/**
 * 14.7 Display dashboard.
 *
 * "Dashboard" is a semi-transparent floating layer for debugging information on top of the video rendering control. It is used to display audio/video information and event information to facilitate integration and debugging.
 * @param showType 0: does not display; 1: displays lite edition (only with audio/video information); 2: displays full edition (with audio/video information and event information).
 */
- (void)showDebugView:(NSInteger)showType;

/**
 * 14.8 Set dashboard margin.
 *
 * This API is used to adjust the position of the dashboard in the video rendering control. It must be called before {@link showDebugView} for it to take effect.
 * @param userId User ID
 * @param margin Inner margin of the dashboard. It should be noted that this is based on the percentage of `parentView`. Value range: [0, 1]
 */
- (void)setDebugViewMargin:(NSString *)userId margin:(TXEdgeInsets)margin;

/**
 * 14.9 Call experimental APIs.
 */
- (NSString *)callExperimentalAPI:(NSString *)jsonStr;

/////////////////////////////////////////////////////////////////////////////////
//
//                    Encrypted interface
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 15.1 Enable or disable private encryption of media streams.
 *
 * In scenarios with high security requirements, TRTC recommends that you call the enablePayloadPrivateEncryption method to enable private encryption of media streams before joining a room.
 * After the user exits the room, the SDK will automatically close the private encryption. To re-enable private encryption, you need to call this method before the user joins the room again.
 * @param enabled Whether to enable media stream private encryption.
 * @param config Configure the algorithm and key for private encryption of media streams, please see {@link TRTCPayloadPrivateEncryptionConfig}.
 * @return Interface call result, 0: Method call succeeded, -1: The incoming parameter is invalid, -2: Your subscription has expired. If you want to renew it, Please go to purchase the [TRTC Professional
 * Edition](https://console.trtc.io/subscription/buy/rtc?packType=pro), and [contact us](https://trtc.io/zh/contact) for review before use.
 * @note TRTC has built-in encryption for media streams before transmission. After private encryption of media streams is enabled, it will be re-encrypted with the key and initial vector you pass in.
 */
- (int)enablePayloadPrivateEncryption:(BOOL)enabled params:(TRTCPayloadPrivateEncryptionConfig *)config;

@end
NS_ASSUME_NONNULL_END
#import "DeprecatedTRTCCloud.h"
