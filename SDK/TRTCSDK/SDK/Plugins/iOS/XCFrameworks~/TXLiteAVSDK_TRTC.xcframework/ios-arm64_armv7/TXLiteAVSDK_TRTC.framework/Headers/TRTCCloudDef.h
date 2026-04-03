/**
 * Copyright (c) 2021 Tencent. All rights reserved.
 * Module: TRTC key class definition
 * Description: definitions of enumerated and constant values such as resolution and quality level
 */
#import <Foundation/Foundation.h>
#import "TXLiteAVSymbolExport.h"

/////////////////////////////////////////////////////////////////////////////////
//
//                    Rendering control
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * [VIEW] Rendering control that renders the video image
 * 1. ObjectiveC interface in iOS and MAC
 * There are many APIs in TRTC that need to manipulate the video image, for which you should specify the video rendering control.
 * - On iOS, you can directly use `UIView` as the video rendering control, and the SDK will draw the video image on the `UIView` you provide.
 * - On macOS, you can directly use `NSView` as the video rendering control, and the SDK will draw the video image on the `NSView` you provide.
 * Below is the sample code:
 * UIView *videoView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 360, 640)];
 * [self.view addSubview:videoView];
 * [trtcCloud startLocalPreview:YES view:_localView];
 * 2. On Android, you can use the `TXCloudVideoView` provided by us as the video rendering control, which supports two rendering schemes: `SurfaceView` and `TextureView`.
 * - When rendering the local video image, `TXCloudVideoView` uses `SurfaceView` preferably. This scheme has better performance, but it does not support animation or transformation effects on the `View`.
 * - When rendering the remote video image, `TXCloudVideoView` uses `TextureView` preferably. This scheme is highly flexible and supports animation and transformation effects.
 * If you want to force the use of a certain scheme, you can write the code as follows:
 * Usage 1. Force the use of `TextureView`:
 * TXCloudVideoView localView = findViewById(R.id.trtc_tc_cloud_view_main);
 * localView.addVideoView(new TextureView(context));
 * mTRTCCloud.startLocalPreview(true, localView);
 * Usage 2. Force the use of `SurfaceView`:
 * SurfaceView surfaceView = new SurfaceView(this);
 * TXCloudVideoView localView = new TXCloudVideoView(surfaceView);
 * mTRTCCloud.startLocalPreview(true, localView);
 * 3. On HarmoryOS, XComponent can be used as the video rendering control directly. SDK will draw the video image on the XComponent whose id is passed through video interface.
 *
 * 4. All platform with C++
 * As the all-platform C++ APIs need to use a unified parameter type, you should uniformly convert the rendering controls into pointers in `TXView` type when calling these APIs:
 * - iOS: you can use the `UIView` object as the rendering control. When calling the C++ APIs, please pass in the pointer to the `UIView` object (which needs to be forcibly converted to the `void*` type).
 * - macOS: you can use the `NSView` object as the rendering control. When calling the C++ APIs, please pass in the pointer to the `NSView` object (which needs to be forcibly converted to the `void*` type).
 * - Android: when calling the C++ APIs, please pass in the `jobject` pointer to the `TXCloudVideoView` object (which needs to be forcibly converted to the `void*` type).
 * - Windows: you can use the window handle `HWND` as the rendering control. When calling the C++ APIs, you need to forcibly convert the `HWND` to `void*` type.
 * - Harmony: you can use XCompent as the rendering control. When calling the C++ APIs, you need to forcibly convert the ID of XComponent 'char*' to 'void*' type.
 * Code sample 1. Use the all-platform C++ APIs under QT
 * QWidget *videoView;
 * // The relevant code for setting the videoView is omitted here...
 * getTRTCShareInstance()->startLocalPreview(reinterpret_cast<TXView>(videoView->winId()));
 * Code sample 2. Call the all-platform C++ APIs through JNI on Android
 * native void nativeStartLocalPreview(String userId, int streamType, TXCloudVideoView view);
 * //...
 * Java_com_example_test_MainActivity_nativeStartRemoteView(JNIEnv *env, jobject thiz, jstring user_id, jint stream_type, jobject view) {
 *     const char *user_id_chars = env->GetStringUTFChars(user_id, nullptr);
 *     trtc_cloud->startRemoteView(user_id_chars, (trtc::TRTCVideoStreamType)stream_type, view);
 *     env->ReleaseStringUTFChars(user_id, user_id_chars);
 * }
 */
#if TARGET_OS_IPHONE || TARGET_OS_SIMULATOR
#import <UIKit/UIKit.h>
typedef UIView TXView;
typedef UIImage TXImage;
typedef UIEdgeInsets TXEdgeInsets;
#elif TARGET_OS_MAC
#import <AppKit/AppKit.h>
typedef NSView TXView;
typedef NSImage TXImage;
typedef NSEdgeInsets TXEdgeInsets;
#endif
#import "TXDeviceManager.h"

/////////////////////////////////////////////////////////////////////////////////
//
//                    Definitions of video enumerated values
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 1.1 Video resolution.
 *
 * Here, only the landscape resolution (e.g., 640x360) is defined. If the portrait resolution (e.g., 360x640) needs to be used, `Portrait` must be selected for {@link TRTCVideoResolutionMode}.
 */
typedef NS_ENUM(NSInteger, TRTCVideoResolution) {

    /// Aspect ratio: 1:1; resolution: 120x120; recommended bitrate (VideoCall): 80 Kbps; recommended bitrate (LIVE): 120 Kbps.
    TRTCVideoResolution_120_120 = 1,

    /// Aspect ratio: 1:1; resolution: 160x160; recommended bitrate (VideoCall): 100 Kbps; recommended bitrate (LIVE): 150 Kbps.
    TRTCVideoResolution_160_160 = 3,

    /// Aspect ratio: 1:1; resolution: 270x270; recommended bitrate (VideoCall): 200 Kbps; recommended bitrate (LIVE): 300 Kbps.
    TRTCVideoResolution_270_270 = 5,

    /// Aspect ratio: 1:1; resolution: 480x480; recommended bitrate (VideoCall): 350 Kbps; recommended bitrate (LIVE): 500 Kbps.
    TRTCVideoResolution_480_480 = 7,

    /// Aspect ratio: 4:3; resolution: 160x120; recommended bitrate (VideoCall): 100 Kbps; recommended bitrate (LIVE): 150 Kbps.
    TRTCVideoResolution_160_120 = 50,

    /// Aspect ratio: 4:3; resolution: 240x180; recommended bitrate (VideoCall): 150 Kbps; recommended bitrate (LIVE): 250 Kbps.
    TRTCVideoResolution_240_180 = 52,

    /// Aspect ratio: 4:3; resolution: 280x210; recommended bitrate (VideoCall): 200 Kbps; recommended bitrate (LIVE): 300 Kbps.
    TRTCVideoResolution_280_210 = 54,

    /// Aspect ratio: 4:3; resolution: 320x240; recommended bitrate (VideoCall): 250 Kbps; recommended bitrate (LIVE): 375 Kbps.
    TRTCVideoResolution_320_240 = 56,

    /// Aspect ratio: 4:3; resolution: 400x300; recommended bitrate (VideoCall): 300 Kbps; recommended bitrate (LIVE): 450 Kbps.
    TRTCVideoResolution_400_300 = 58,

    /// Aspect ratio: 4:3; resolution: 480x360; recommended bitrate (VideoCall): 400 Kbps; recommended bitrate (LIVE): 600 Kbps.
    TRTCVideoResolution_480_360 = 60,

    /// Aspect ratio: 4:3; resolution: 640x480; recommended bitrate (VideoCall): 600 Kbps; recommended bitrate (LIVE): 900 Kbps.
    TRTCVideoResolution_640_480 = 62,

    /// Aspect ratio: 4:3; resolution: 960x720; recommended bitrate (VideoCall): 1000kbps; recommended bitrate (LIVE): 1500kbps。
    TRTCVideoResolution_960_720 = 64,

    /// Aspect ratio: 16:9; resolution: 160x90; recommended bitrate (VideoCall): 150 Kbps; recommended bitrate (LIVE): 250 Kbps.
    TRTCVideoResolution_160_90 = 100,

    /// Aspect ratio: 16:9; resolution: 256x144; recommended bitrate (VideoCall): 200 Kbps; recommended bitrate (LIVE): 300 Kbps.
    TRTCVideoResolution_256_144 = 102,

    /// Aspect ratio: 16:9; resolution: 320x180; recommended bitrate (VideoCall): 250 Kbps; recommended bitrate (LIVE): 400 Kbps.
    TRTCVideoResolution_320_180 = 104,

    /// Aspect ratio: 16:9; resolution: 480x270; recommended bitrate (VideoCall): 350 Kbps; recommended bitrate (LIVE): 550 Kbps.
    TRTCVideoResolution_480_270 = 106,

    /// Aspect ratio: 16:9; resolution: 640x360; recommended bitrate (VideoCall): 500 Kbps; recommended bitrate (LIVE): 900 Kbps.
    TRTCVideoResolution_640_360 = 108,

    /// Aspect ratio: 16:9; resolution: 960x540; recommended bitrate (VideoCall): 850 Kbps; recommended bitrate (LIVE): 1300 Kbps.
    TRTCVideoResolution_960_540 = 110,

    /// Aspect ratio: 16:9; resolution: 1280x720; recommended bitrate (VideoCall): 1200 Kbps; recommended bitrate (LIVE): 1800 Kbps.
    TRTCVideoResolution_1280_720 = 112,

    /// Aspect ratio: 16:9; resolution: 1920x1080; recommended bitrate (VideoCall): 2000 Kbps; recommended bitrate (LIVE): 3000 Kbps.
    TRTCVideoResolution_1920_1080 = 114,

};

/**
 * 1.2 Video aspect ratio mode.
 *
 * Only the landscape resolution (e.g., 640x360) is defined in `TRTCVideoResolution`. If the portrait resolution (e.g., 360x640) needs to be used, `Portrait` must be selected for `TRTCVideoResolutionMode`.
 */
typedef NS_ENUM(NSInteger, TRTCVideoResolutionMode) {

    /// Landscape resolution, such as `TRTCVideoResolution_640_360 + TRTCVideoResolutionModeLandscape = 640x360`.
    TRTCVideoResolutionModeLandscape = 0,

    /// Portrait resolution, such as `TRTCVideoResolution_640_360 + TRTCVideoResolutionModePortrait = 360x640`.
    TRTCVideoResolutionModePortrait = 1,

};

/**
 * 1.3 Video stream type.
 *
 * TRTC provides three different video streams, including:
 *  - HD big image: it is generally used to transfer video data from the camera.
 *  - Smooth small image: it has the same content as the big image, but with lower resolution and bitrate and thus lower definition.
 *  - Substream image: it is generally used for screen sharing. Only one user in the room is allowed to publish the substream video image at any time, while other users must wait for this user to close the substream before they can publish their own
 * substream.
 * @note The SDK does not support enabling the smooth small image alone, which must be enabled together with the big image. It will automatically set the resolution and bitrate of the small image.
 */
typedef NS_ENUM(NSInteger, TRTCVideoStreamType) {

    /// HD big image: it is generally used to transfer video data from the camera.
    TRTCVideoStreamTypeBig = 0,

    /// Smooth small image: it has the same content as the big image, but with lower resolution and bitrate and thus lower definition.
    TRTCVideoStreamTypeSmall = 1,

    /// Substream image: it is generally used for screen sharing. Only one user in the room is allowed to publish the substream video image at any time, while other users must wait for this user to close the substream before they can publish their
    /// own substream.
    TRTCVideoStreamTypeSub = 2,

};

/**
 * 1.4 Video image fill mode.
 *
 * If the aspect ratio of the video display area is not equal to that of the video image, you need to specify the fill mode:
 */
typedef NS_ENUM(NSInteger, TRTCVideoFillMode) {

    /// Fill mode: the video image will be centered and scaled to fill the entire display area, where parts that exceed the area will be cropped. The displayed image may be incomplete in this mode.
    TRTCVideoFillMode_Fill = 0,

    /// Fit mode: the video image will be scaled based on its long side to fit the display area, where the short side will be filled with black bars. The displayed image is complete in this mode, but there may be black bars.
    TRTCVideoFillMode_Fit = 1,

    /// Scale-to-fill mode: This means that regardless of the aspect ratio of the image, it will be stretched or compressed to completely fill the display area. In this mode, the aspect ratio of the image may be altered, leading to distortion in the
    /// rendered image.
    TRTCVideoFillMode_ScaleFill = 2,

};

/**
 * 1.5 Video image rotation direction.
 *
 * TRTC provides rotation angle setting APIs for local and remote images. The following rotation angles are all clockwise.
 */
typedef NS_ENUM(NSInteger, TRTCVideoRotation) {

    /// No rotation
    TRTCVideoRotation_0 = 0,

    /// Clockwise rotation by 90 degrees
    TRTCVideoRotation_90 = 1,

    /// Clockwise rotation by 180 degrees
    TRTCVideoRotation_180 = 2,

    /// Clockwise rotation by 270 degrees
    TRTCVideoRotation_270 = 3,

};

/**
 * 1.6 Beauty (skin smoothing) filter algorithm.
 *
 * TRTC has multiple built-in skin smoothing algorithms. You can select the one most suitable for your product.
 */
typedef NS_ENUM(NSInteger, TRTCBeautyStyle) {

    /// Smooth style, which uses a more radical algorithm for more obvious effect and is suitable for show live streaming.
    TRTCBeautyStyleSmooth = 0,

    /// Natural style, which retains more facial details for more natural effect and is suitable for most live streaming use cases.
    TRTCBeautyStyleNature = 1,

    /// Pitu style, which is provided by YouTu Lab. Its skin smoothing effect is between the smooth style and the natural style, that is, it retains more skin details than the smooth style and has a higher skin smoothing degree than the natural
    /// style.
    TRTCBeautyStylePitu = 2,

};

/**
 * 1.7 Video pixel format.
 *
 * TRTC provides custom video capturing and rendering features.
 * - For the custom capturing feature, you can use the following enumerated values to describe the pixel format of the video you capture.
 * - For the custom rendering feature, you can specify the pixel format of the video you expect the SDK to call back.
 */
typedef NS_ENUM(NSInteger, TRTCVideoPixelFormat) {

    /// Undefined format
    TRTCVideoPixelFormat_Unknown = 0,

    /// YUV420P (I420) format
    TRTCVideoPixelFormat_I420 = 1,

    /// OpenGL 2D texture format
    TRTCVideoPixelFormat_Texture_2D = 7,

    /// BGRA32 format
    TRTCVideoPixelFormat_32BGRA = 6,

    /// YUV420SP (NV12) format
    TRTCVideoPixelFormat_NV12 = 5,

};

/**
 * 1.8 Video data transfer method.
 *
 * For custom capturing and rendering features, you need to use the following enumerated values to specify the method of transferring video data:
 * - Method 1. This method uses memory buffer to transfer video data. It is efficient on iOS but inefficient on Android. It is the only method supported on Windows currently.
 * - Method 2. This method uses texture to transfer video data. It is efficient on both iOS and Android but is not supported on Windows. To use this method, you should have a general familiarity with OpenGL programming.
 */
typedef NS_ENUM(NSInteger, TRTCVideoBufferType) {

    /// Undefined transfer method
    TRTCVideoBufferType_Unknown = 0,

    /// Use `PixelBuffer` to transfer video data.
    TRTCVideoBufferType_PixelBuffer = 1,

    /// Use memory buffer to transfer video data. iOS: more compact memory block in `NSData` type after additional processing; Android: `byte[]` for Java layer.
    /// This transfer method has a lower efficiency than other methods.
    TRTCVideoBufferType_NSData = 2,

    /// Use OpenGL texture to transfer video data
    TRTCVideoBufferType_Texture = 3,

};

/**
 * 1.9 Video mirror type.
 *
 * Video mirroring refers to the left-to-right flipping of the video image, especially for the local camera preview image. After mirroring is enabled, it can bring anchors a familiar "look into the mirror" experience.
 */
typedef NS_ENUM(NSUInteger, TRTCVideoMirrorType) {

    /// Auto mode: mirror the front camera's image but not the rear camera's image (for mobile devices only).
    TRTCVideoMirrorTypeAuto = 0,

    /// Mirror the images of both the front and rear cameras.
    TRTCVideoMirrorTypeEnable = 1,

    /// Disable mirroring for both the front and rear cameras.
    TRTCVideoMirrorTypeDisable = 2,

};

/**
 * Old version of TRTCVideoMirrorType, reserved for compatibility with older interface.
 */
typedef NS_ENUM(NSUInteger, TRTCLocalVideoMirrorType) {
    TRTCLocalVideoMirrorType_Auto = TRTCVideoMirrorTypeAuto,
    TRTCLocalVideoMirrorType_Enable = TRTCVideoMirrorTypeEnable,
    TRTCLocalVideoMirrorType_Disable = TRTCVideoMirrorTypeDisable,
} __attribute__((deprecated("use TRTCVideoMirrorType instead")));

/**
 * 1.10 Data source of local video screenshot.
 *
 * The SDK can take screenshots from the following two data sources and save them as local files:
 * - Video stream: the SDK screencaptures the native video content from the video stream. The screenshots are not controlled by the display of the rendering control.
 * - Rendering layer: the SDK screencaptures the displayed video content from the rendering control, which can achieve the effect of WYSIWYG, but if the display area is too small, the screenshots will also be very small.
 */
typedef NS_ENUM(NSUInteger, TRTCSnapshotSourceType) {

    /// The SDK screencaptures the native video content from the video stream. The screenshots are not controlled by the display of the rendering control.
    TRTCSnapshotSourceTypeStream = 0,

    /// The SDK screencaptures the displayed video content from the rendering control, which can achieve the effect of WYSIWYG, but if the display area is too small, the screenshots will also be very small.
    TRTCSnapshotSourceTypeView = 1,

    /// The SDK screencaptures the capture video content from the capture control, which can capture the captured high-definition screenshots.
    TRTCSnapshotSourceTypeCapture = 2,

};

/////////////////////////////////////////////////////////////////////////////////
//
//                    Definitions of network enumerated values
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 2.1 Use cases.
 *
 * TRTC features targeted optimizations for common audio/video application scenarios to meet the differentiated requirements in various verticals. The main scenarios can be divided into the following two categories:
 * - Live streaming scenario (LIVE): including `LIVE` (audio + video) and `VoiceChatRoom` (pure audio).
 *   In the live streaming scenario, users are divided into two roles: "anchor" and "audience". A single room can sustain up to 100,000 concurrent online users. This is suitable for live streaming to a large audience.
 * - Real-Time scenario (RTC): including `VideoCall` (audio + video) and `AudioCall` (pure audio).
 *   In the real-time scenario, there is no role difference between users, but a single room can sustain only up to 300 concurrent online users. This is suitable for small-scale real-time communication.
 */
typedef NS_ENUM(NSInteger, TRTCAppScene) {

    /// In the video call scenario, 720p and 1080p HD image quality is supported. A single room can sustain up to 300 concurrent online users, and up to 50 of them can speak simultaneously.
    /// Use cases: [one-to-one video call], [video conferencing with up to 300 participants], [online medical diagnosis], [small class], [video interview], etc.
    TRTCAppSceneVideoCall = 0,

    /// In the interactive video live streaming scenario, mic can be turned on/off smoothly without waiting for switchover, and the anchor latency is as low as less than 300 ms. Live streaming to hundreds of thousands of concurrent users in the
    /// audience role is supported with the playback latency down to 1,000 ms.
    /// Use cases: [low-latency interactive live streaming], [big class], [anchor competition], [video dating room], [online interactive classroom], [remote training], [large-scale conferencing], etc.
    ///@note In this scenario, you must use the `role` field in `TRTCParams` to specify the role of the current user.
    TRTCAppSceneLIVE = 1,

    /// Audio call scenario, where the `SPEECH` sound quality is used by default. A single room can sustain up to 300 concurrent online users, and up to 50 of them can speak simultaneously.
    /// Use cases: [one-to-one audio call], [audio conferencing with up to 300 participants], [audio chat], [online Werewolf], etc.
    TRTCAppSceneAudioCall = 2,

    /// In the interactive audio live streaming scenario, mic can be turned on/off smoothly without waiting for switchover, and the anchor latency is as low as less than 300 ms. Live streaming to hundreds of thousands of concurrent users in the
    /// audience role is supported with the playback latency down to 1,000 ms.
    /// Use cases: [audio club], [online karaoke room], [music live room], [FM radio], etc.
    ///@note In this scenario, you must use the `role` field in `TRTCParams` to specify the role of the current user.
    TRTCAppSceneVoiceChatRoom = 3,

};

/**
 * 2.2 Role.
 *
 * Role is applicable only to live streaming scenarios (`TRTCAppSceneLIVE` and `TRTCAppSceneVoiceChatRoom`). Users are divided into two roles:
 * - Anchor, who can publish their audio/video streams. There is a limit on the number of anchors. Up to 50 anchors are allowed to publish streams at the same time in one room.
 * - Audience, who can only listen to or watch audio/video streams of anchors in the room. If they want to publish their streams, they need to switch to the "anchor" role first through {@link switchRole}. One room can sustain up to 100,000 concurrent
 * online users in the audience role.
 */
typedef NS_ENUM(NSInteger, TRTCRoleType) {

    /// An anchor can publish their audio/video streams. There is a limit on the number of anchors. Up to 50 anchors are allowed to publish streams at the same time in one room.
    TRTCRoleAnchor = 20,

    /// Audience can only listen to or watch audio/video streams of anchors in the room. If they want to publish their streams, they need to switch to the "anchor" role first through {@link switchRole}. One room can sustain up to 100,000 concurrent
    /// online users in the audience role.
    TRTCRoleAudience = 21,

};

/**
 * 2.3 QoS control mode (disused).
 */
typedef NS_ENUM(NSInteger, TRTCQosControlMode) {

    /// Client-based control, which is for internal debugging of SDK and shall not be used by users.
    TRTCQosControlModeClient = 0,

    /// On-cloud control, which is the default and recommended mode.
    TRTCQosControlModeServer = 1,

};

/**
 * 2.4 Image quality preference.
 *
 * TRTC has two control modes in weak network environments: "ensuring clarity" and "ensuring smoothness". Both modes will give priority to the transfer of audio data.
 */
typedef NS_ENUM(NSInteger, TRTCVideoQosPreference) {

    /// Ensuring smoothness: in this mode, when the current network is unable to transfer a clear and smooth video image, the smoothness of the image will be given priority, but there will be blurs.
    TRTCVideoQosPreferenceSmooth = 1,

    /// Ensuring clarity (default value): in this mode, when the current network is unable to transfer a clear and smooth video image, the clarity of the image will be given priority, but there will be lags.
    TRTCVideoQosPreferenceClear = 2,

};

/**
 * 2.5 Network quality.
 *
 * TRTC evaluates the current network quality once every two seconds. The evaluation results are divided into six levels: `Excellent` indicates the best, and `Down` indicates the worst.
 */
typedef NS_ENUM(NSInteger, TRTCQuality) {

    /// Undefined
    TRTCQuality_Unknown = 0,

    /// The current network is excellent
    TRTCQuality_Excellent = 1,

    /// The current network is good
    TRTCQuality_Good = 2,

    /// The current network is fair
    TRTCQuality_Poor = 3,

    /// The current network is bad
    TRTCQuality_Bad = 4,

    /// The current network is very bad
    TRTCQuality_Vbad = 5,

    /// The current network cannot meet the minimum requirements of TRTC
    TRTCQuality_Down = 6,

};

/**
 * 2.6 Audio/Video playback status.
 *
 * This enumerated type is used in the audio status changed API {@link onRemoteAudioStatusUpdated} and the video status changed API {@link onRemoteVideoStatusUpdated} to specify the current audio/video status.
 */
typedef NS_ENUM(NSUInteger, TRTCAVStatusType) {

    /// Stopped
    TRTCAVStatusStopped = 0,

    /// Playing
    TRTCAVStatusPlaying = 1,

    /// Loading
    TRTCAVStatusLoading = 2,

};

/**
 * 2.7 Reasons for playback status changes.
 *
 * This enumerated type is used in the audio status changed API {@link onRemoteAudioStatusUpdated} and the video status changed API {@link onRemoteVideoStatusUpdated} to specify the reason for the current audio/video status change.
 */
typedef NS_ENUM(NSUInteger, TRTCAVStatusChangeReason) {

    /// Default value
    TRTCAVStatusChangeReasonInternal = 0,

    /// The stream enters the `Loading` state due to network congestion
    TRTCAVStatusChangeReasonBufferingBegin = 1,

    /// The stream enters the `Playing` state after network recovery
    TRTCAVStatusChangeReasonBufferingEnd = 2,

    /// As a start-related API was directly called locally, the stream enters the `Playing` state
    TRTCAVStatusChangeReasonLocalStarted = 3,

    /// As a stop-related API was directly called locally, the stream enters the `Stopped` state
    TRTCAVStatusChangeReasonLocalStopped = 4,

    /// As the remote user started (or resumed) publishing the audio or video stream, the stream enters the `Loading` or `Playing` state
    TRTCAVStatusChangeReasonRemoteStarted = 5,

    /// As the remote user stopped (or paused) publishing the audio or video stream, the stream enters the "Stopped" state
    TRTCAVStatusChangeReasonRemoteStopped = 6,

};

/////////////////////////////////////////////////////////////////////////////////
//
//                    Definitions of audio enumerated values
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 3.1 Audio sample rate.
 *
 * The audio sample rate is used to measure the audio fidelity. A higher sample rate indicates higher fidelity. If there is music in the use case, `TRTCAudioSampleRate48000` is recommended.
 */
typedef NS_ENUM(NSInteger, TRTCAudioSampleRate) {

    /// 16 kHz sample rate
    TRTCAudioSampleRate16000 = 16000,

    /// 32 kHz sample rate
    TRTCAudioSampleRate32000 = 32000,

    /// 44.1 kHz sample rate
    TRTCAudioSampleRate44100 = 44100,

    /// 48 kHz sample rate
    TRTCAudioSampleRate48000 = 48000,

};

/**
 * 3.2 Sound quality.
 *
 * TRTC provides three well-tuned modes to meet the differentiated requirements for sound quality in various verticals:
 * - Speech mode (Speech): it is suitable for application scenarios that focus on human communication. In this mode, the audio transfer is more resistant, and TRTC uses various voice processing technologies to ensure the optimal smoothness even in
 * weak network environments.
 * - Music mode (Music): it is suitable for scenarios with demanding requirements for music. In this mode, the amount of transferred audio data is very large, and TRTC uses various technologies to ensure that the high-fidelity details of music
 * signals can be restored in each frequency band.
 * - Default mode (Default): it is between `Speech` and `Music`. In this mode, the reproduction of music is better than that in `Speech` mode, and the amount of transferred data is much lower than that in `Music` mode; therefore, this mode has good
 * adaptability to various scenarios.
 */
typedef NS_ENUM(NSInteger, TRTCAudioQuality) {

    /// Speech mode: mono channel; bitrate: 18 Kbps. This mode has the best resistance among all modes and is suitable for audio call scenarios, such as online meeting and audio call.
    TRTCAudioQualitySpeech = 1,

    /// Default mode: mono channel; bitrate: 50 Kbps. This mode is between the speech mode and the music mode as the default mode in the SDK and is recommended.
    TRTCAudioQualityDefault = 2,

    /// Music mode: full-band stereo; bitrate: 128 Kbps. This mode is suitable for scenarios where Hi-Fi music transfer is required, such as online karaoke and music live streaming.
    TRTCAudioQualityMusic = 3,

};

/**
 * 3.3 Audio route (i.e., audio playback mode).
 *
 * "Audio route" determines whether the sound is played back from the speaker or receiver of a mobile device; therefore, this API is applicable only to mobile devices such as phones.
 * Generally, a phone has two speakers: one is the receiver at the top, and the other is the stereo speaker at the bottom.
 * - If the audio route is set to the receiver, the volume is relatively low, and the sound can be heard clearly only when the phone is put near the ear. This mode has a high level of privacy and is suitable for answering calls.
 * - If the audio route is set to the speaker, the volume is relatively high, so there is no need to put the phone near the ear. Therefore, this mode can implement the "hands-free" feature.
 */
typedef NS_ENUM(NSInteger, TRTCAudioRoute) {

    /// Unknown：default router.
    TRTCAudioModeUnknown = -1,

    /// Speakerphone: the speaker at the bottom is used for playback (hands-free). With relatively high volume, it is used to play music out loud.
    TRTCAudioModeSpeakerphone = 0,

    /// Earpiece: the receiver at the top is used for playback. With relatively low volume, it is suitable for call scenarios that require privacy.
    TRTCAudioModeEarpiece = 1,

    /// WiredHeadset：play using wired headphones.
    TRTCAudioModeWiredHeadset = 2,

    /// BluetoothHeadset：play with bluetooth headphones.
    TRTCAudioModeBluetoothHeadset = 3,

    /// SoundCard：play using a USB sound card.
    TRTCAudioModeSoundCard = 4,

};

/**
 * 3.4 Audio reverb mode.
 *
 * This enumerated value is used to set the audio reverb mode in the live streaming scenario and is often used in show live streaming.
 */
typedef NS_ENUM(NSInteger, TRTCReverbType) {

    /// Disable reverb
    TRTCReverbType_0 = 0,

    /// KTV
    TRTCReverbType_1 = 1,

    /// Small room
    TRTCReverbType_2 = 2,

    /// Hall
    TRTCReverbType_3 = 3,

    /// Deep
    TRTCReverbType_4 = 4,

    /// Resonant
    TRTCReverbType_5 = 5,

    /// Metallic
    TRTCReverbType_6 = 6,

    /// Husky
    TRTCReverbType_7 = 7,

};

/**
 * 3.5 Voice changing type.
 *
 * This enumerated value is used to set the voice changing mode in the live streaming scenario and is often used in show live streaming.
 */
typedef NS_ENUM(NSInteger, TRTCVoiceChangerType) {

    /// Disable voice changing
    TRTCVoiceChangerType_0 = 0,

    /// Child
    TRTCVoiceChangerType_1 = 1,

    /// Girl
    TRTCVoiceChangerType_2 = 2,

    /// Middle-Aged man
    TRTCVoiceChangerType_3 = 3,

    /// Heavy metal
    TRTCVoiceChangerType_4 = 4,

    /// Nasal
    TRTCVoiceChangerType_5 = 5,

    /// Punk
    TRTCVoiceChangerType_6 = 6,

    /// Trapped beast
    TRTCVoiceChangerType_7 = 7,

    /// Otaku
    TRTCVoiceChangerType_8 = 8,

    /// Electronic
    TRTCVoiceChangerType_9 = 9,

    /// Robot
    TRTCVoiceChangerType_10 = 10,

    /// Ethereal
    TRTCVoiceChangerType_11 = 11,

};

/**
 * 3.6 System volume type (only for mobile devices).
 *
 * Smartphones usually have two types of system volume: call volume and media volume.
 * - Call volume is designed for call scenarios. It comes with acoustic echo cancellation (AEC) and supports audio capturing by Bluetooth earphones, but its sound quality is average.
 *            If you cannot turn the volume down to 0 (i.e., mute the phone) using the volume buttons, then your phone is using call volume.
 * - Media volume is designed for media scenarios such as music playback. AEC does not work when media volume is used, and Bluetooth earphones cannot be used for audio capturing. However, media volume delivers better music listening experience.
 *            If you are able to mute your phone using the volume buttons, then your phone is using media volume.
 * The SDK offers three system volume control modes: auto, call volume, and media volume.
 */
typedef NS_ENUM(NSInteger, TRTCSystemVolumeType) {

    /// Auto:
    /// In the auto mode, call volume is used for anchors, and media volume for audience. This mode is suitable for live streaming scenarios.
    /// If the scenario you select during `enterRoom` is `TRTCAppSceneLIVE` or `TRTCAppSceneVoiceChatRoom`, the SDK will automatically use this mode.
    TRTCSystemVolumeTypeAuto = 0,

    /// Media volume:
    /// In this mode, media volume is used in all scenarios. It is rarely used, mainly suitable for music scenarios with demanding requirements on audio quality.
    /// Use this mode if most of your users use peripheral devices such as audio cards. Otherwise, it is not recommended.
    TRTCSystemVolumeTypeMedia = 1,

    /// Call volume:
    /// In this mode, the audio module does not change its work mode when users switch between anchors and audience, enabling seamless mic on/off. This mode is suitable for scenarios where users need to switch frequently between anchors and audience.
    /// If the scenario you select during `enterRoom` is `TRTCAppSceneVideoCall` or `TRTCAppSceneAudioCall`, the SDK will automatically use this mode.
    TRTCSystemVolumeTypeVOIP = 2,

};

/**
 * 3.9 Audio callback data operation mode.
 *
 * TRTC provides two modes of operation for audio callback data.
 * - Read-only mode (ReadOnly): Get audio data only from the callback.
 * - ReadWrite mode (ReadWrite): You can get and modify the audio data of the callback.
 */
typedef NS_ENUM(NSInteger, TRTCAudioFrameOperationMode) {

    /// Read-write mode: You can get and modify the audio data of the callback, the default mode.
    TRTCAudioFrameOperationModeReadWrite = 0,

    /// Read-only mode: Get audio data from callback only.
    TRTCAudioFrameOperationModeReadOnly = 1,

};

/////////////////////////////////////////////////////////////////////////////////
//
//                      Definitions of other enumerated values
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 4.1 Log level.
 *
 * Different log levels indicate different levels of details and number of logs. We recommend you set the log level to `TRTCLogLevelInfo` generally.
 */
typedef NS_ENUM(NSInteger, TRTCLogLevel) {

    /// Output logs at all levels
    TRTCLogLevelVerbose = 0,

    /// Output logs at the DEBUG, INFO, WARNING, ERROR, and FATAL levels
    TRTCLogLevelDebug = 1,

    /// Output logs at the INFO, WARNING, ERROR, and FATAL levels
    TRTCLogLevelInfo = 2,

    /// Output logs at the WARNING, ERROR, and FATAL levels
    TRTCLogLevelWarn = 3,

    /// Output logs at the ERROR and FATAL levels
    TRTCLogLevelError = 4,

    /// Output logs at the FATAL level
    TRTCLogLevelFatal = 5,

    /// Do not output any SDK logs
    TRTCLogLevelNone = 6,

};

/**
 * 4.2 G-sensor switch (for mobile devices only).
 *
 * @deprecated Begin from v11.7 version，it is recommended to use the new gravity sensing enumeration {@link TRTCGravitySensorAdaptiveMode}.
 */
typedef NS_ENUM(NSInteger, TRTCGSensorMode) {

    /// Do not adapt to G-sensor orientation
    /// This mode is the default value for desktop platforms. In this mode, the video image published by the current user is not affected by the change of the G-sensor orientation.
    TRTCGSensorMode_Disable = 0,

    /// Adapt to G-sensor orientation
    /// This mode is the default value on mobile platforms. In this mode, the video image published by the current user is adjusted according to the G-sensor orientation, while the orientation of the local preview image remains unchanged.
    /// One of the adaptation modes currently supported by the SDK is as follows: when the phone or tablet is upside down, in order to ensure that the screen orientation seen by the remote user is normal, the SDK will automatically rotate the
    /// published video image by 180 degrees.
    /// If the UI layer of your application has enabled G-sensor adaption, we recommend you use the `UIFixLayout` mode.
    TRTCGSensorMode_UIAutoLayout = 1,

    /// Adapt to G-sensor orientation
    /// In this mode, the video image published by the current user is adjusted according to the G-sensor orientation, and the local preview image will also be rotated accordingly.
    /// One of the features currently supported is as follows: when the phone or tablet is upside down, in order to ensure that the screen orientation seen by the remote user is normal, the SDK will automatically rotate the published video image by
    /// 180 degrees.
    /// If the UI layer of your application doesn't support G-sensor adaption, but you want the video image in the SDK to adapt to the G-sensor orientation, we recommend you use the `UIFixLayout` mode.
    ///@deprecated Begin from v11.5 version, it no longer supports TRTCGSensorMode_UIFixLayout and only supports the above two modes.
    TRTCGSensorMode_UIFixLayout = 2,

};

/**
 * 4.3 Screen sharing target type (for desktops only).
 */
typedef NS_ENUM(NSInteger, TRTCScreenCaptureSourceType) {

    /// Undefined
    TRTCScreenCaptureSourceTypeUnknown = -1,

    /// The screen sharing target is the window of an application
    TRTCScreenCaptureSourceTypeWindow = 0,

    /// The screen sharing target is the entire screen
    TRTCScreenCaptureSourceTypeScreen = 1,

};

/**
 * 4.4 Layout mode of On-Cloud MixTranscoding.
 *
 * TRTC's On-Cloud MixTranscoding service can mix multiple audio/video streams in the room into one stream. Therefore, you need to specify the layout scheme of the video images. The following layout modes are provided:
 */
typedef NS_ENUM(NSInteger, TRTCTranscodingConfigMode) {

    /// Undefined
    TRTCTranscodingConfigMode_Unknown = 0,

    /// Manual layout mode
    /// In this mode, you need to specify the precise position of each video image. This mode has the highest degree of freedom, but its ease of use is the worst:
    /// - You need to enter all the parameters in {@link TRTCTranscodingConfig}, including the position coordinates of each video image (TRTCMixUser).
    ///- You need to listen on the {@link onUserVideoAvailable} and {@link onUserAudioAvailable} event callbacks in {@link TRTCCloudDelegate} and constantly adjust the `mixUsers` parameter according to the audio/video status of each user with mic on
    /// in the current room.
    TRTCTranscodingConfigMode_Manual = 1,

    /// Pure audio mode
    /// This mode is suitable for pure audio scenarios such as audio call (AudioCall) and audio chat room (VoiceChatRoom).
    /// - You only need to set it once through the {@link setMixTranscodingConfig} API after room entry, and then the SDK will automatically mix the audio of all mic-on users in the room into the current user's live stream.
    ///- You don't need to set the `mixUsers` parameter in {@link TRTCTranscodingConfig}; instead, you only need to set the `audioSampleRate`, `audioBitrate` and `audioChannels` parameters.
    TRTCTranscodingConfigMode_Template_PureAudio = 2,

    /// Preset layout mode
    /// This is the most popular layout mode, because it allows you to set the position of each video image in advance through placeholders, and then the SDK automatically adjusts it dynamically according to the number of video images in the room.
    /// In this mode, you still need to set the `mixUsers` parameter, but you can set `userId` as a "placeholder". Placeholder values include:
    ///  - "$PLACE_HOLDER_REMOTE$": image of remote user. Multiple images can be set.
    /// - "$PLACE_HOLDER_LOCAL_MAIN$": local camera image. Only one image can be set.
    /// - "$PLACE_HOLDER_LOCAL_SUB$": local screen sharing image. Only one image can be set.
    /// In this mode, you don't need to listen on the {@link onUserVideoAvailable} and {@link onUserAudioAvailable} callbacks in {@link TRTCCloudDelegate} to make real-time adjustments.
    /// Instead, you only need to call {@link setMixTranscodingConfig} once after successful room entry. Then, the SDK will automatically populate the placeholders you set with real `userId` values.
    TRTCTranscodingConfigMode_Template_PresetLayout = 3,

    /// Screen sharing mode
    /// This mode is suitable for screen sharing-based use cases such as online education and supported only by the SDKs for Windows and macOS.
    /// In this mode, the SDK will first build a canvas according to the target resolution you set (through the `videoWidth` and `videoHeight` parameters).
    /// - Before the teacher enables screen sharing, the SDK will scale up the teacher's camera image and draw it onto the canvas.
    ///- After the teacher enables screen sharing, the SDK will draw the video image shared on the screen onto the same canvas.
    /// The purpose of this layout mode is to ensure consistency in the output resolution of the mixtranscoding module and avoid problems with blurred screen during course replay and webpage playback (web players don't support adjustable resolution).
    /// Meanwhile, the audio of mic-on students will be mixed into the teacher's audio/video stream by default.
    /// Video content is primarily the shared screen in teaching mode, and it is a waste of bandwidth to transfer camera image and screen image at the same time.
    /// Therefore, the recommended practice is to directly draw the camera image onto the current screen through the {@link setLocalVideoRenderCallback} API.
    /// In this mode, you don't need to set the `mixUsers` parameter in {@link TRTCTranscodingConfig}, and the SDK will not mix students' images so as not to interfere with the screen sharing effect.
    /// You can set width x height in {@link TRTCTranscodingConfig} to 0 px x 0 px, and the SDK will automatically calculate a suitable resolution based on the aspect ratio of the user's current screen.
    /// - If the teacher's current screen width is less than or equal to 1920 px, the SDK will use the actual resolution of the teacher's current screen.
    ///- If the teacher's current screen width is greater than 1920 px, the SDK will select one of the three resolutions of 1920x1080 (16:9), 1920x1200 (16:10), and 1920x1440 (4:3) according to the current screen aspect ratio.
    TRTCTranscodingConfigMode_Template_ScreenSharing = 4,

};

/**
 * 4.5 Media recording type.
 *
 * This enumerated type is used in the local media recording API {@link startLocalRecording} to specify whether to record audio/video files or pure audio files.
 */
typedef NS_ENUM(NSUInteger, TRTCRecordType) {

    /// Record audio only
    TRTCRecordTypeAudio = 0,

    /// Record video only
    TRTCRecordTypeVideo = 1,

    /// Record both audio and video
    TRTCRecordTypeBoth = 2,

};

/**
 * 4.6 Stream mix input type.
 */
typedef NS_ENUM(NSUInteger, TRTCMixInputType) {

    /// Default.
    /// Considering the compatibility with older versions, if you specify the inputType as Undefined, the SDK will determine the stream mix input type according to the value of the `pureAudio` parameter
    TRTCMixInputTypeUndefined = 0,

    /// Mix both audio and video
    TRTCMixInputTypeAudioVideo = 1,

    /// Mix video only
    TRTCMixInputTypePureVideo = 2,

    /// Mix audio only
    TRTCMixInputTypePureAudio = 3,

    /// Mix watermark
    /// In this case, you don't need to specify the `userId` parameter, but you need to specify the `image` parameter. It is recommended to use png format.
    TRTCMixInputTypeWatermark = 4,

};

/**
 * 4.7 Device type (for desktop platforms only).
 *
 * This enumerated value is used to define three types of audio/video devices, namely, camera, mic, and speaker, so that the same device management API can control the three different types of devices.
 * Starting from v8.0, TRTC redefines `TXMediaDeviceType` in `TXDeviceManager` to replace `TRTCMediaDeviceType` on legacy versions.
 * Only the definition of `TRTCMediaDeviceType` is retained here for compatibility with customer code on legacy versions.
 */
#if TARGET_OS_MAC && !TARGET_OS_IPHONE
typedef NS_ENUM(NSInteger, TRTCMediaDeviceType) {
    TRTCMediaDeviceTypeUnknown = -1,     ///< undefined device type
    TRTCMediaDeviceTypeAudioInput = 0,   ///< microphone
    TRTCMediaDeviceTypeAudioOutput = 1,  ///< speaker
    TRTCMediaDeviceTypeVideoCamera = 2,  ///< camera
    TRTCMediaDeviceTypeVideoWindow = 3,  ///< windows(for screen share)
    TRTCMediaDeviceTypeVideoScreen = 4,  ///< screen (for screen share)
} __attribute__((deprecated("use TXDeviceManager#TXMediaDeviceType instead")));

typedef TXMediaDeviceInfo TRTCMediaDeviceInfo __attribute__((deprecated("use TXDeviceManager#TXMediaDeviceInfo instead")));
#endif

/**
 * 4.11 Audio recording content type.
 *
 * This enumerated type is used in the audio recording API {@link startAudioRecording} to specify the content of the recorded audio.
 */
typedef NS_ENUM(NSUInteger, TRTCAudioRecordingContent) {

    /// Record both local and remote audio
    TRTCAudioRecordingContentAll = 0,

    /// Record local audio only
    TRTCAudioRecordingContentLocal = 1,

    /// Record remote audio only
    TRTCAudioRecordingContentRemote = 2,

};

/**
 * 4.12 The publishing mode.
 *
 * This enum type is used by the publishing API {@link startPublishMediaStream}.
 * TRTC can mix multiple streams in a room and publish the mixed stream to a CDN or to a TRTC room. It can also publish the stream of the local user to Tencent Cloud or a third-party CDN.
 * You can specify one of the following publishing modes to use:
 */
typedef NS_ENUM(NSUInteger, TRTCPublishMode) {

    /// Undefined
    TRTCPublishModeUnknown = 0,

    /// Use this parameter to publish the primary stream ({@link TRTCVideoStreamTypeBig}) in the room to Tencent Cloud or a third-party CDN (only RTMP is supported).
    TRTCPublishBigStreamToCdn = 1,

    /// Use this parameter to publish the substream ({@link TRTCVideoStreamTypeSub}) in the room to Tencent Cloud or a third-party CDN (only RTMP is supported).
    TRTCPublishSubStreamToCdn = 2,

    /// Use this parameter together with the encoding parameter {@link TRTCStreamEncoderParam} and On-Cloud MixTranscoding parameter {@link TRTCStreamMixingConfig} to transcode the streams you specify and publish the mixed stream to Tencent Cloud or
    /// a third-party CDN (only RTMP is supported).
    TRTCPublishMixStreamToCdn = 3,

    /// Use this parameter together with the encoding parameter {@link TRTCStreamEncoderParam} and On-Cloud MixTranscoding parameter {@link TRTCStreamMixingConfig} to transcode the streams you specify and publish the mixed stream to the room you
    /// specify.
    /// - Use `TRTCUser` in {@link TRTCPublishTarget} to specify the robot that publishes the transcoded stream to a TRTC room.
    TRTCPublishMixStreamToRoom = 4,

};

/**
 * 4.13 Encryption Algorithm.
 *
 * This enumeration type is used for media stream private encryption algorithm selection.
 */
typedef NS_ENUM(NSUInteger, TRTCEncryptionAlgorithm) {

    /// AES GCM 128。
    TRTCEncryptionAlgorithmAes128Gcm = 0,

    /// AES GCM 256。
    TRTCEncryptionAlgorithmAes256Gcm = 1,

};

/**
 * 4.14 Speed Test Scene.
 *
 * This enumeration type is used for speed test scene selection.
 */
typedef NS_ENUM(NSUInteger, TRTCSpeedTestScene) {

    /// Delay testing.
    TRTCSpeedTestScene_DelayTesting = 1,

    /// Delay and bandwidth testing.
    TRTCSpeedTestScene_DelayAndBandwidthTesting = 2,

    /// Online chorus testing.
    TRTCSpeedTestScene_OnlineChorusTesting = 3,

};

/**
 * 4.15 Set the adaptation mode of gravity sensing (only applicable to mobile terminals).
 *
 * Begin from v11.7 version，It only takes effect when the camera capture scene inside SDK is used.
 */
typedef NS_ENUM(NSInteger, TRTCGravitySensorAdaptiveMode) {

    /// Turn off the gravity sensor and make a decision based on the current acquisition resolution and the set encoding resolution. If the two are inconsistent, rotate 90 degrees to ensure the maximum frame.
    TRTCGravitySensorAdaptiveMode_Disable = 0,

    /// Turn on the gravity sensor to always ensure that the remote screen image is positive. When the intermediate process needs to deal with inconsistent resolutions, use the center cropping mode.
    TRTCGravitySensorAdaptiveMode_FillByCenterCrop = 1,

    /// Turn on the gravity sensor to always ensure that the remote screen image is positive. When the resolution needs to be processed inconsistently in the intermediate process, use the superimposed black border mode.
    TRTCGravitySensorAdaptiveMode_FitWithBlackBorder = 2,

};

/////////////////////////////////////////////////////////////////////////////////
//
//                      Definitions of core TRTC classes
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 5.1 Room entry parameters.
 *
 * As the room entry parameters in the TRTC SDK, these parameters must be correctly set so that the user can successfully enter the audio/video room specified by `roomId` or `strRoomId`.
 * For historical reasons, TRTC supports two types of room IDs: `roomId` and `strRoomId`.
 * Note: do not mix `roomId` and `strRoomId`, because they are not interchangeable. For example, the number `123` and the string `123` are two completely different rooms in TRTC.
 */
LITEAV_EXPORT @interface TRTCParams : NSObject

/// Field description: application ID, which is required. Tencent Cloud generates bills based on `sdkAppId`.
/// Recommended value: the ID can be obtained on the account information page in the [TRTC console](https://console.cloud.tencent.com/rav/) after the corresponding application is created.
@property(nonatomic, assign) UInt32 sdkAppId;

/// Field description: user ID, which is required. It is the `userId` of the local user in UTF-8 encoding and acts as the username.
/// Recommended value: if the ID of a user in your account system is "mike", `userId` can be set to "mike".
@property(nonatomic, copy, nonnull) NSString *userId;

/// Field description: user signature, which is required. It is the authentication signature corresponding to the current `userId` and acts as the login password for Tencent Cloud services.
/// Recommended value: for the calculation method, please see [UserSig](https://www.tencentcloud.com/document/product/647/35166).
@property(nonatomic, copy, nonnull) NSString *userSig;

/// Field description: numeric room ID. Users (userId) in the same room can see one another and make audio/video calls.
/// Recommended value: value range: 1–4294967294.
///@note `roomId` and `strRoomId` are mutually exclusive. If you decide to use `strRoomId`, then `roomId` should be entered as 0. If both are entered, `roomId` will be used.
///@note do not mix `roomId` and `strRoomId`, because they are not interchangeable. For example, the number `123` and the string `123` are two completely different rooms in TRTC.
@property(nonatomic, assign) UInt32 roomId;

/// Field description: string-type room ID. Users (userId) in the same room can see one another and make audio/video calls.
///@note `roomId` and `strRoomId` are mutually exclusive. If you decide to use `strRoomId`, then `roomId` should be entered as 0. If both are entered, `roomId` will be used.
///@note do not mix `roomId` and `strRoomId`, because they are not interchangeable. For example, the number `123` and the string `123` are two completely different rooms in TRTC.
/// Recommended value: the length limit is 64 bytes. The following 89 characters are supported:
///  - Uppercase and lowercase letters (a–z and A–Z)
/// - Digits (0–9)
/// - Space, "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", "{", "}", "|", "~", and ",".
@property(nonatomic, copy, nonnull) NSString *strRoomId;

/// Field description: role in the live streaming scenario, which is applicable only to the live streaming scenario ({@link TRTCAppSceneLIVE} or {@link TRTCAppSceneVoiceChatRoom}) but doesn't take effect in the call scenario.
/// Recommended value: default value: anchor ({@link TRTCRoleAnchor}).
@property(nonatomic, assign) TRTCRoleType role;

/// Field description: specified `streamId` in Tencent Cloud CSS, which is optional. After setting this field, you can play back the user's audio/video stream on Tencent Cloud CSS CDN through a standard pull scheme (FLV or HLS).
/// Recommended value: this parameter can contain up to 64 bytes and can be left empty. We recommend you use `sdkappid_roomid_userid_main` as the `streamid`, which is easier to identify and will not cause conflicts in your multiple applications.
///@note to use Tencent Cloud CSS CDN, you need to enable the auto-relayed live streaming feature on the "Function Configuration" page in the [console](https://console.cloud.tencent.com/trtc/) first.
/// For more information, please see [Relay to CDN](https://www.tencentcloud.com/document/product/647/47858).
@property(nonatomic, copy, nullable) NSString *streamId;

/// Field description: on-cloud recording field, which is optional and used to specify whether to record the user's audio/video stream in the cloud.
/// For more information, please see [On-Cloud Recording](https://www.tencentcloud.com/document/product/647/45169).
/// Recommended value: it can contain up to 64 bytes. Letters (a–z and A–Z), digits (0–9), underscores, and hyphens are allowed.
/// Scheme 1. Manual recording
/// 1. Enable on-cloud recording in "Application Management" > "On-cloud Recording Configuration" in the [console](https://console.cloud.tencent.com/trtc).
/// 2. Set "Recording Mode" to "Manual Recording".
/// 3. After manual recording is set, in a TRTC room, only users with the `userDefineRecordId` parameter set will have video recording files in the cloud, while users without this parameter set will not.
/// 4. The recording file will be named in the format of "userDefineRecordId_start time_end time" in the cloud.
/// Scheme 2. Auto-recording
/// 1. You need to enable on-cloud recording in "Application Management" > "On-cloud Recording Configuration" in the [console](https://console.cloud.tencent.com/trtc).
/// 2. Set "Recording Mode" to "Auto-recording".
/// 3. After auto-recording is set, any user who upstreams audio/video in a TRTC room will have a video recording file in the cloud.
/// 4. The file will be named in the format of "userDefineRecordId_start time_end time". If `userDefineRecordId` is not specified, the file will be named in the format of "streamId_start time_end time".
@property(nonatomic, copy, nullable) NSString *userDefineRecordId;

/// Field description: permission credential used for permission control, which is optional. If you want only users with the specified `userId` values to enter a room, you need to use `privateMapKey` to restrict the permission.
/// Recommended value: we recommend you use this parameter only if you have high security requirements. For more information, please see [Enabling Advanced Permission Control](https://www.tencentcloud.com/document/product/647/35157).
@property(nonatomic, copy, nullable) NSString *privateMapKey;

/// Field description: business data, which is optional. This field is needed only by some advanced features.
/// Recommended value: do not set this field on your own.
@property(nonatomic, copy, nullable) NSString *bussInfo;

@end

/**
 * 5.2 Video encoding parameters.
 *
 * These settings determine the quality of image viewed by remote users as well as the image quality of recorded video files in the cloud.
 */
LITEAV_EXPORT @interface TRTCVideoEncParam : NSObject

/// Field description: video resolution
/// Recommended value
///  - For mobile video call, we recommend you select a resolution of 360x640 or below and select `Portrait` (portrait resolution) for `resMode`.
/// - For mobile live streaming, we recommend you select a resolution of 540x960 and select `Portrait` (portrait resolution) for `resMode`.
/// - For desktop platforms (Windows and macOS), we recommend you select a resolution of 640x360 or above and select `Landscape` (landscape resolution) for `resMode`.
///@note to use a portrait resolution, please specify `resMode` as `Portrait`; for example, when used together with `Portrait`, 640x360 represents 360x640.
@property(nonatomic, assign) TRTCVideoResolution videoResolution;

/// Field description: resolution mode (landscape/portrait)
/// Recommended value: for mobile platforms (iOS and Android), `Portrait` is recommended; for desktop platforms (Windows and macOS), `Landscape` is recommended.
///@note to use a portrait resolution, please specify `resMode` as `Portrait`; for example, when used together with `Portrait`, 640x360 represents 360x640.
@property(nonatomic, assign) TRTCVideoResolutionMode resMode;

/// Field description: video capturing frame rate
/// Recommended value: 15 or 20 fps. If the frame rate is lower than 5 fps, there will be obvious lagging; if lower than 10 fps but higher than 5 fps, there will be slight lagging; if higher than 20 fps, the bandwidth will be wasted (the frame rate
/// of movies is generally 24 fps).
///@note the front cameras on certain Android phones do not support a capturing frame rate higher than 15 fps. For some Android phones that focus on beautification features, the capturing frame rate of the front cameras may be lower than 10 fps.
@property(nonatomic, assign) int videoFps;

/// Field description: target video bitrate. The SDK encodes streams at the target video bitrate and will actively reduce the bitrate only in weak network environments.
/// Recommended value: please see the optimal bitrate for each specification in `TRTCVideoResolution`. You can also slightly increase the optimal bitrate.
///           For example, `TRTCVideoResolution_1280_720` corresponds to the target bitrate of 1,200 Kbps. You can also set the bitrate to 1,500 Kbps for higher definition.
///@note you can set the `videoBitrate` and `minVideoBitrate` parameters at the same time to restrict the SDK's adjustment range of the video bitrate:
///  - If you want to "ensure clarity while allowing lag in weak network environments", you can set `minVideoBitrate` to 60% of `videoBitrate`.
/// - If you want to "ensure smoothness while allowing blur in weak network environments", you can set `minVideoBitrate` to a low value, for example, 100 Kbps.
/// - If you set `videoBitrate` and `minVideoBitrate` to the same value, it is equivalent to disabling the adaptive adjustment capability of the SDK for the video bitrate.
@property(nonatomic, assign) int videoBitrate;

/// Field description: minimum video bitrate. The SDK will reduce the bitrate to as low as the value specified by `minVideoBitrate` to ensure the smoothness only if the network conditions are poor.
/// Note: default value: 0, indicating that a reasonable value of the lowest bitrate will be automatically calculated by the SDK according to the resolution you specify.
/// Recommended value: you can set the `videoBitrate` and `minVideoBitrate` parameters at the same time to restrict the SDK's adjustment range of the video bitrate:
///  - If you want to "ensure clarity while allowing lag in weak network environments", you can set `minVideoBitrate` to 60% of `videoBitrate`.
/// - If you want to "ensure smoothness while allowing blur in weak network environments", you can set `minVideoBitrate` to a low value, for example, 100 Kbps.
/// - If you set `videoBitrate` and `minVideoBitrate` to the same value, it is equivalent to disabling the adaptive adjustment capability of the SDK for the video bitrate.
@property(nonatomic, assign) int minVideoBitrate;

/// Field description: whether to allow dynamic resolution adjustment. Once enabled, this field will affect on-cloud recording.
/// Recommended value: this feature is suitable for scenarios that don't require on-cloud recording. After it is enabled, the SDK will intelligently select a suitable resolution according to the current network conditions to avoid the inefficient
/// encoding mode of "large resolution + small bitrate".
///@note default value: NO. If you need on-cloud recording, please do not enable this feature, because if the video resolution changes, the MP4 file recorded in the cloud cannot be played back normally by common players.
@property(nonatomic, assign) BOOL enableAdjustRes;

@end

/**
 * 5.3 Network QoS control parameter set.
 *
 * Network QoS control parameter. The settings determine the QoS control policy of the SDK in weak network conditions (e.g., whether to "ensure clarity" or "ensure smoothness").
 */
LITEAV_EXPORT @interface TRTCNetworkQosParam : NSObject

/// Field description: whether to ensure smoothness or clarity
/// Recommended value: ensuring clarity
///@note this parameter mainly affects the audio/video performance of TRTC in weak network environments:
///  - Ensuring smoothness: in this mode, when the current network is unable to transfer a clear and smooth video image, the smoothness of the image will be given priority, but there will be blurs. See {@link TRTCVideoQosPreferenceSmooth}
/// - Ensuring clarity (default value): in this mode, when the current network is unable to transfer a clear and smooth video image, the clarity of the image will be given priority, but there will be lags. See {@link TRTCVideoQosPreferenceClear}
@property(nonatomic, assign) TRTCVideoQosPreference preference;

/// Field description: QoS control mode (disused)
/// Recommended value: on-cloud control
///@note please set the on-cloud control mode (TRTCQosControlModeServer).
@property(nonatomic, assign) TRTCQosControlMode controlMode;

@end

/**
 * 5.4 Rendering parameters of video image.
 *
 * You can use these parameters to control the video image rotation angle, fill mode, and mirror mode.
 */
LITEAV_EXPORT @interface TRTCRenderParams : NSObject

/// Field description: clockwise image rotation angle
/// Recommended value: rotation angles of 90, 180, and 270 degrees are supported. Default value: {@link TRTCVideoRotation_0}
@property(nonatomic) TRTCVideoRotation rotation;

/// Field description: image fill mode
/// Recommended value: fill (the image may be stretched or cropped) or fit (there may be black bars in unmatched areas). Default value: {@link TRTCVideoFillMode_Fill}
@property(nonatomic) TRTCVideoFillMode fillMode;

/// Field description: image mirror mode
/// Recommended value: default value: {@link TRTCVideoMirrorTypeAuto}
@property(nonatomic) TRTCVideoMirrorType mirrorType;

@end

/**
 * 5.5 Network quality.
 *
 * This indicates the quality of the network. You can use it to display the network quality of each user on the UI.
 */
LITEAV_EXPORT @interface TRTCQualityInfo : NSObject

/// User ID
@property(nonatomic, copy, nullable) NSString *userId;

/// Network quality
@property(nonatomic, assign) TRTCQuality quality;

@end

/**
 * 5.6 Volume.
 *
 * This indicates the audio volume value. You can use it to display the volume of each user in the UI.
 */
LITEAV_EXPORT @interface TRTCVolumeInfo : NSObject

/// `userId` of the speaker. An empty value indicates the local user.
@property(nonatomic, copy, nullable) NSString *userId;

/// Volume of the speaker. Value range: 0–100.
@property(assign, nonatomic) NSUInteger volume;

/// Vad result of the local user. 0: not speech 1: speech.
@property(assign, nonatomic) NSInteger vad;

/// The local user's vocal frequency (unit: Hz), the value range is [0 - 4000]. For remote users, this value is always 0.
@property(assign, nonatomic) float pitch;

/// Audio spectrum data, which divides the sound frequency into 256 frequency domains, spectrumData records the energy value of each frequency domain,
/// The value range of each energy value is [-300, 0] in dBFS.
///@note The local spectrum is calculated using the audio data before encoding, which will be affected by the capture volume, BGM, etc.; the remote spectrum is calculated using the received audio data, and operations such as adjusting the remote
/// playback volume locally will not affect it.
@property(nonatomic, strong, nullable) NSArray<NSNumber *> *spectrumData;

@end

/**
 * 5.7 Network speed testing parameters.
 *
 * You can test the network speed through the {@link startSpeedTest:} interface before the user enters the room (this API cannot be called during a call).
 */
LITEAV_EXPORT @interface TRTCSpeedTestParams : NSObject

/// Application identification, please refer to the relevant instructions in {@link TRTCParams}.
@property(nonatomic) uint32_t sdkAppId;

/// User identification, please refer to the relevant instructions in {@link TRTCParams}.
@property(nonatomic, copy, nonnull) NSString *userId;

/// User signature, please refer to the relevant instructions in {@link TRTCParams}.
@property(nonatomic, copy, nonnull) NSString *userSig;

/// Expected upstream bandwidth (kbps, value range: 10 to 5000, no uplink bandwidth test when it is 0).
///@note When the parameter `scene` is set to {@link TRTCSpeedTestScene_OnlineChorusTesting}, in order to obtain more accurate information such as `rtt / jitter`, the value range is limited to [10, 1000].
@property(nonatomic) NSInteger expectedUpBandwidth;

/// Expected downstream bandwidth (kbps, value range: 10 to 5000, no downlink bandwidth test when it is 0).
///@note When the parameter `scene` is set to {@link TRTCSpeedTestScene_OnlineChorusTesting}, in order to obtain more accurate information such as `rtt / jitter`, the value range is limited to [10, 1000].
@property(nonatomic) NSInteger expectedDownBandwidth;

/// Speed test scene.
@property(nonatomic, assign) TRTCSpeedTestScene scene;

@end

/**
 * 5.8 Network speed test result.
 *
 * The {@link startSpeedTest:} API can be used to test the network speed before a user enters a room (this API cannot be called during a call).
 */
LITEAV_EXPORT @interface TRTCSpeedTestResult : NSObject

/// Whether the network speed test is successful.
@property(nonatomic) BOOL success;

/// Error message for network speed test.
@property(nonatomic, copy, nonnull) NSString *errMsg;

/// Server IP address.
@property(nonatomic, copy, nonnull) NSString *ip;

/// Network quality, which is tested and calculated based on the internal evaluation algorithm. For more information, please see {@link TRTCQuality}
@property(nonatomic) TRTCQuality quality;

/// Upstream packet loss rate between 0 and 1.0. For example, 0.3 indicates that 3 data packets may be lost in every 10 packets sent to the server.
@property(nonatomic) float upLostRate;

/// Downstream packet loss rate between 0 and 1.0. For example, 0.2 indicates that 2 data packets may be lost in every 10 packets received from the server.
@property(nonatomic) float downLostRate;

/// Delay in milliseconds, which is the round-trip time between the current device and TRTC server. The smaller the value, the better. The normal value range is 10–100 ms.
@property(nonatomic) uint32_t rtt;

/// Upstream bandwidth (in kbps, -1: invalid value).
@property(nonatomic) NSInteger availableUpBandwidth;

/// Downstream bandwidth (in kbps, -1: invalid value).
@property(nonatomic) NSInteger availableDownBandwidth;

/// Uplink data packet jitter (ms) refers to the stability of data communication in the user's current network environment. The smaller the value, the better. The normal value range is [0, 100]. -1 means that the speed test failed to obtain an
/// effective value. Generally, the Jitter of the WiFi network will be slightly larger than that of the 4G/5G environment.
@property(nonatomic) NSInteger upJitter;

/// Downlink data packet jitter (ms) refers to the stability of data communication in the user's current network environment. The smaller the value, the better. The normal value range is [0, 100]. -1 means that the speed test failed to obtain an
/// effective value. Generally, the Jitter of the WiFi network will be slightly larger than that of the 4G/5G environment.
@property(nonatomic) NSInteger downJitter;

@end

/**
 * 5.10 Video frame information.
 *
 * `TRTCVideoFrame` is used to describe the raw data of a frame of the video image, which is the image data before frame encoding or after frame decoding.
 */
LITEAV_EXPORT @interface TRTCVideoFrame : NSObject

/// Field description: video pixel format
@property(nonatomic, assign) TRTCVideoPixelFormat pixelFormat;

/// Field description: video data structure type
@property(nonatomic, assign) TRTCVideoBufferType bufferType;

/// Field description: video data when `bufferType` is {@link TRTCVideoBufferType_PixelBuffer}, which carries the `PixelBuffer` unique to iOS.
@property(nonatomic, assign, nullable) CVPixelBufferRef pixelBuffer;

/// Field description: video data when `bufferType` is {@link TRTCVideoBufferType_NSData}, which carries the memory data blocks in `NSData` type.
@property(nonatomic, retain, nullable) NSData *data;

/// Field description: video texture ID, i.e., video data when `bufferType` is {@link TRTCVideoBufferType_Texture}, which carries the texture data used for OpenGL rendering.
@property(nonatomic, assign) GLuint textureId;

/// Field description: video width
/// Recommended value: please enter the width of the video data passed in.
@property(nonatomic, assign) uint32_t width;

/// Field description: video height
/// Recommended value: please enter the height of the video data passed in.
@property(nonatomic, assign) uint32_t height;

/// Field description: video frame timestamp in milliseconds
/// Recommended value: this parameter can be set to 0 for custom video capturing. In this case, the SDK will automatically set the `timestamp` field. However, please "evenly" set the calling interval of {@link sendCustomVideoData}.
@property(nonatomic, assign) uint64_t timestamp;

/// Field description: clockwise rotation angle of video pixels
@property(nonatomic, assign) TRTCVideoRotation rotation;

@end

/**
 * 5.11 Audio frame data.
 */
LITEAV_EXPORT @interface TRTCAudioFrame : NSObject

/// Field description: audio data
@property(nonatomic, retain, nonnull) NSData *data;

/// Field description: sample rate
@property(nonatomic, assign) TRTCAudioSampleRate sampleRate;

/// Field description: number of sound channels
@property(nonatomic, assign) int channels;

/// Field description: timestamp in ms
@property(nonatomic, assign) uint64_t timestamp;

/// Field description: extra data in audio frame, message sent by remote users through {@link onLocalProcessedAudioFrame} that add to audio frame will be callback through this field.
@property(nonatomic, retain, nullable) NSData *extraData;

@end

/**
 * 5.12 Description information of each video image in On-Cloud MixTranscoding.
 *
 * `TRTCMixUser` is used to specify the location, size, layer, and stream type of each video image in On-Cloud MixTranscoding.
 */
LITEAV_EXPORT @interface TRTCMixUser : NSObject

/// Field description: user ID
@property(nonatomic, copy, nonnull) NSString *userId;

/// Field description: ID of the room where this audio/video stream is located (an empty value indicates the local room ID)
@property(nonatomic, copy, nullable) NSString *roomID;

/// Field description: specify the coordinate area of this video image in px
@property(nonatomic, assign) CGRect rect;

/// Field description: specify the level of this video image (value range: [1, 15]; the value must be unique)
@property(nonatomic, assign) int zOrder;

/// Field description: specify whether this video image is the primary stream image ({@link TRTCVideoStreamTypeBig}) or substream image ({@link TRTCVideoStreamTypeSub}).
@property(nonatomic) TRTCVideoStreamType streamType;

/// Field description: specify whether this stream mixes audio only
/// Recommended value: default value: NO
///@note this field has been disused. We recommend you use the new field `inputType` introduced in v8.5.
@property(nonatomic, assign) BOOL pureAudio;

/// Field description: specify the mixed content of this stream (audio only, video only, audio and video, or watermark).
/// Recommended value: default value: {@link TRTCMixInputTypeUndefined}.
///@note
/// - When specifying `inputType` as {@link TRTCMixInputTypeUndefined} and specifying `pureAudio` to YES, it is equivalent to setting `inputType` to `TRTCMixInputTypePureAudio`.
///- When specifying `inputType` as {@link TRTCMixInputTypeUndefined} and specifying `pureAudio` to NO, it is equivalent to setting `inputType` to `TRTCMixInputTypeAudioVideo`.
///- When specifying `inputType` as {@link TRTCMixInputTypeWatermark}, you don't need to specify the `userId` field, but you need to specify the `image` field.
@property(nonatomic, assign) TRTCMixInputType inputType;

/// Field description: specify the display mode of this stream.
/// Recommended value: default value: 0. 0 is cropping, 1 is zooming, 2 is zooming and displaying black background.
///@note image doesn't support setting `renderMode` temporarily, the default display mode is forced stretch.
@property(nonatomic, assign) int renderMode;

/// Field description: specify the target volumn level of On-Cloud MixTranscoding. (value range: 0-100)
/// Recommended value: default value: 100.
@property(nonatomic, assign) int soundLevel;

/// Field description: specify the placeholder or watermark image. The placeholder image will be displayed when there is no upstream video.A watermark image is a semi-transparent image posted in the mixed image, and this image will always be overlaid
/// on the mixed image.
/// - When the `inputType` field is set to {@link TRTCMixInputTypePureAudio}, the image is a placeholder image, and you need to specify `userId`.
///- When the `inputType` field is set to {@link TRTCMixInputTypeWatermark}, the image is a watermark image, and you don't need to specify `userId`.
/// Recommended value: default value: null, indicating not to set the placeholder or watermark image.
///@note TRTC's backend service will mix the image specified by the URL address into the final stream.URL link length is limited to 512 bytes. The image size is limited to 10MB.Support png, jpg, jpeg, bmp format. Take effects iff the `inputType`
/// field is set to {@link TRTCMixInputTypePureAudio} or {@link TRTCMixInputTypeWatermark}.
@property(nonatomic, copy, nullable) NSString *image;

@end

/**
 * 5.13 Layout and transcoding parameters of On-Cloud MixTranscoding.
 *
 * These parameters are used to specify the layout position information of each video image and the encoding parameters of mixtranscoding during On-Cloud MixTranscoding.
 */
LITEAV_EXPORT @interface TRTCTranscodingConfig : NSObject

/// Field description: layout mode
/// Recommended value: please choose a value according to your business needs. The preset mode has better applicability.
@property(nonatomic, assign) TRTCTranscodingConfigMode mode;

/// Field description: `appId` of Tencent Cloud CSS
/// Recommended value: please click `Application Management` > `Application Information` in the [TRTC console](https://console.cloud.tencent.com/trtc) and get the `appId` in `Relayed Live Streaming Info`.
///@note applications created on or after January 9, 2020 do not need to fill in this field.
@property(nonatomic) int appId;

/// Field description: `bizId` of Tencent Cloud CSS
/// Recommended value: please click `Application Management` > `Application Information` in the [TRTC console](https://console.cloud.tencent.com/trtc) and get the `bizId` in `Relayed Live Streaming Info`.
///@note applications created on or after January 9, 2020 do not need to fill in this field.
@property(nonatomic) int bizId;

/// Field description: specify the target resolution (width) of On-Cloud MixTranscoding
/// Recommended value: 360 px. If you only mix audio streams, please set both `width` and `height` to 0; otherwise, there will be a black background in the live stream after mixtranscoding.
@property(nonatomic, assign) int videoWidth;

/// Field description: specify the target resolution (height) of On-Cloud MixTranscoding
/// Recommended value: 640 px. If you only mix audio streams, please set both `width` and `height` to 0; otherwise, there will be a black background in the live stream after mixtranscoding.
@property(nonatomic, assign) int videoHeight;

/// Field description: specify the target video bitrate (Kbps) of On-Cloud MixTranscoding
/// Recommended value: if you enter 0, TRTC will estimate a reasonable bitrate value based on `videoWidth` and `videoHeight`. You can also refer to the recommended bitrate value in the video resolution enumeration definition (in the comment section).
@property(nonatomic, assign) int videoBitrate;

/// Field description: specify the target video frame rate (fps) of On-Cloud MixTranscoding
/// Recommended value: default value: 15 fps. Value range: (0,30].
@property(nonatomic, assign) int videoFramerate;

/// Field description: specify the target video keyframe interval (GOP) of On-Cloud MixTranscoding
/// Recommended value: default value: 2 (in seconds). Value range: [1,8].
@property(nonatomic, assign) int videoGOP;

/// Field description: specify the background color of the mixed video image.
/// Recommended value: default value: 0x000000, which means black and is in the format of hex number; for example: "0x61B9F1" represents the RGB color (97,158,241).
@property(nonatomic, assign) int backgroundColor;

/// Field description: specify the background image of the mixed video image.
///**Recommended value: default value: null, indicating not to set the background image.
///@note TRTC's backend service will mix the image specified by the URL address into the final stream.URL link length is limited to 512 bytes. The image size is limited to 10MB.Support png, jpg, jpeg, bmp format.
@property(nonatomic, copy, nullable) NSString *backgroundImage;

/// Field description: specify the target audio sample rate of On-Cloud MixTranscoding
/// Recommended value: default value: 48000 Hz. Valid values: 12000 Hz, 16000 Hz, 22050 Hz, 24000 Hz, 32000 Hz, 44100 Hz, 48000 Hz.
@property(nonatomic, assign) int audioSampleRate;

/// Field description: specify the target audio bitrate of On-Cloud MixTranscoding
/// Recommended value: default value: 64 Kbps. Value range: [32,192].
@property(nonatomic, assign) int audioBitrate;

/// Field description: specify the number of sound channels of On-Cloud MixTranscoding
/// Recommended value: default value: 1, which means mono channel. Valid values: 1: mono channel; 2: dual channel.
@property(nonatomic, assign) int audioChannels;

/// Field description: specify the audio encoding type of On-Cloud MixTranscoding
/// Recommended value: default value: 0, which means LC-AAC. Valid values: 0:  LC-AAC; 1: HE-AAC; 2: HE-AACv2.
///@note
/// - HE-AAC and HE-AACv2 only support [48000, 44100, 32000, 24000, 16000]  sample rate.
///- HE-AACv2  only support dual channel.
///- HE-AAC and HE-AACv2 take effects iff the output streamId is specified.
@property(nonatomic, assign) int audioCodec;

/// Field description: specify the position, size, layer, and stream type of each video image in On-Cloud MixTranscoding
/// Recommended value: this field is an array in `TRTCMixUser` type, where each element represents the information of a video image.
@property(nonatomic, copy, nonnull) NSArray<TRTCMixUser *> *mixUsers;

/// Field description: ID of the live stream output to CDN
/// Recommended value: default value: null, that is, the audio/video streams in the room will be mixed into the audio/video stream of the caller of this API.
///    - If you don't set this parameter, the SDK will execute the default logic, that is, it will mix the multiple audio/video streams in the room into the audio/video stream of the caller of this API, i.e., A + B => A.
///    - If you set this parameter, the SDK will mix the audio/video streams in the room into the live stream you specify, i.e., A + B => C (C is the `streamId` you specify).
@property(nonatomic, copy, nullable) NSString *streamId;

/// Field description: SEI parameters. default value: null
///@note the parameter is passed in the form of a JSON string. Here is an example to use it:
/// ```json
///{
///  "payLoadContent":"xxx",
///  "payloadType":5,
///  "payloadUuid":"1234567890abcdef1234567890abcdef",
///  "interval":1000,
///  "followIdr":false
///}
///```
/// The currently supported fields and their meanings are as follows:
/// - payloadContent: Required. The payload content of the passthrough SEI, which cannot be empty.
///- payloadType: Required. The type of the SEI message, with a value range of 5 or an integer within the range of [100, 254] (excluding 244, which is an internally defined timestamp SEI).
///- payloadUuid: Required when payloadType is 5, and ignored in other cases. The value must be a 32-digit hexadecimal number.
///- interval: Optional, default is 1000. The sending interval of the SEI, in milliseconds.
///- followIdr: Optional, default is false. When this value is true, the SEI will be ensured to be carried when sending a key frame, otherwise it is not guaranteed.
@property(nonatomic, copy, nullable) NSString *videoSeiParams;

@end

/**
 * 5.14 Push parameters required to be set when publishing audio/video streams to non-Tencent Cloud CDN.
 *
 * TRTC's backend service supports publishing audio/video streams to third-party live CDN service providers through the standard RTMP protocol.
 * If you use the Tencent Cloud CSS CDN service, you don't need to care about this parameter; instead, just use the {@link startPublish} API.
 */
LITEAV_EXPORT @interface TRTCPublishCDNParam : NSObject

/// Field description: `appId` of Tencent Cloud CSS
/// Recommended value: please click `Application Management` > `Application Information` in the [TRTC console](https://console.cloud.tencent.com/trtc) and get the `appId` in `Relayed Live Streaming Info`.
@property(nonatomic) int appId;

/// Field description: `bizId` of Tencent Cloud CSS
/// Recommended value: please click `Application Management` > `Application Information` in the [TRTC console](https://console.cloud.tencent.com/trtc) and get the `bizId` in `Relayed Live Streaming Info`.
@property(nonatomic) int bizId;

/// Field description: specify the push address (in RTMP format) of this audio/video stream at the third-party live streaming service provider
/// Recommended value: the push URL rules vary greatly by service provider. Please enter a valid push URL according to the requirements of the target service provider. TRTC's backend server will push audio/video streams in the standard format to the
/// third-party service provider according to the URL you enter.
///@note the push URL must be in RTMP format and meet the specifications of your target live streaming service provider; otherwise, the target service provider will reject the push requests from TRTC's backend service.
@property(nonatomic, strong, nonnull) NSString *url;

/// Field description: specify the push address (in RTMP format) of this audio/video stream at the third-party live streaming service provider
/// Recommended value: default value: null,that is, the audio/video streams in the room will be pushed to the target service provider of the caller of this API.
@property(nonatomic, strong, nonnull) NSString *streamId;

@end

/**
 * 5.15 Local audio file recording parameters.
 *
 * This parameter is used to specify the recording parameters in the audio recording API {@link startAudioRecording}.
 */
LITEAV_EXPORT @interface TRTCAudioRecordingParams : NSObject

/// Field description: storage path of the audio recording file, which is required.
///@note this path must be accurate to the file name and extension. The extension determines the format of the audio recording file. Currently, supported formats include PCM, WAV, and AAC.
/// For example, if you specify the path as `mypath/record/audio.aac`, it means that you want the SDK to generate an audio recording file in AAC format.Please specify a valid path with read/write permissions; otherwise, the audio recording file
/// cannot be generated.
@property(nonatomic, strong, nonnull) NSString *filePath;

/// Field description: Audio recording content type.
/// Note: Record all local and remote audio by default.
@property(nonatomic, assign) TRTCAudioRecordingContent recordingContent;

/// Field description: `maxDurationPerFile` is the max duration of each recorded file segments, in milliseconds, with a minimum value of 10000. The default value is 0, indicating no segmentation.
@property(nonatomic, assign) int maxDurationPerFile;

@end

/**
 * 5.16 Local media file recording parameters.
 *
 * This parameter is used to specify the recording parameters in the local media file recording API {@link startLocalRecording}.
 * The {@link startLocalRecording} API is an enhanced version of the {@link startAudioRecording} API. The former can record video files, while the latter can only record audio files.
 */
LITEAV_EXPORT @interface TRTCLocalRecordingParams : NSObject

/// Field description: address of the recording file, which is required. Please ensure that the path is valid with read/write permissions; otherwise, the recording file cannot be generated.
///@note this path must be accurate to the file name and extension. The extension determines the format of the recording file. Currently, only the MP4 format is supported.
///           For example, if you specify the path as `mypath/record/test.mp4`, it means that you want the SDK to generate a local video file in MP4 format.
///           Please specify a valid path with read/write permissions; otherwise, the recording file cannot be generated.
@property(nonatomic, copy, nonnull) NSString *filePath;

/// Field description: media recording type, which is `TRTCRecordTypeBoth` by default, indicating to record both audio and video.
@property(nonatomic, assign) TRTCRecordType recordType;

/// Field description: `interval` is the update frequency of the recording information in milliseconds. Value range: [1000, 10000]. Default value: -1, indicating not to call back
@property(nonatomic, assign) int interval;

/// Field description: `maxDurationPerFile` is the max duration of each recorded file segments, in milliseconds, with a minimum value of 10000. The default value is 0, indicating no segmentation.
@property(nonatomic, assign) int maxDurationPerFile;

@end

/**
 * 5.17 Sound effect parameter (disused).
 *
 * "Sound effects" in TRTC refer to some short audio files (usually only a few seconds), such as "applause" and "laughter".
 * This parameter is used to specify the path and number of playback times of a sound effect file (short audio file) in the sound effect playback API {@link TRTCCloud#playAudioEffect} on legacy versions.
 * After v7.3, the sound effect API has been replaced by a new {@link TXAudioEffectManager#startPlayMusic} API.
 * When you specify the {@link TXAudioMusicParam} parameter of `startPlayMusic`, if `isShortFile` is set to `YES`, the file is a "sound effect" file.
 */
LITEAV_EXPORT @interface TRTCAudioEffectParam : NSObject

+ (_Nonnull instancetype)new __attribute__((unavailable("Use -initWith:(int)effectId path:(NSString * )path instead")));
- (_Nonnull instancetype)init __attribute__((unavailable("Use -initWith:(int)effectId path:(NSString *)path instead")));

/// Field description: sound effect ID
/// Note: the SDK supports playing multiple sound effects. IDs are used to distinguish different sound effects and control their start, end, volume, etc.
@property(nonatomic, assign) int effectId;

/// Field description: sound effect file path. Supported file formats include AAC, MP3, and M4A.
@property(nonatomic, copy, nonnull) NSString *path;

/// Field description: number of times the sound effect is looped
/// Valid values: 0 or any positive integer. 0 (default) indicates that the sound effect is played once, 1 twice, and so on.
@property(nonatomic, assign) int loopCount;

/// Field description: whether the sound effect is upstreamed
/// Recommended value: YES: when the sound effect is played back locally, it will be upstreamed to the cloud and can be heard by remote users. NO: the sound effect will not be upstreamed to the cloud and can only be heard locally. Default value: NO
@property(nonatomic, assign) BOOL publish;

/// Field description: sound effect volume
/// Recommended value: value range: 0–100. Default value: 100
@property(nonatomic, assign) int volume;

- (_Nonnull instancetype)initWith:(int)effectId path:(NSString *_Nonnull)path;

@end

/**
 * 5.18 Room switch parameter.
 *
 * This parameter is used for the room switch API {@link switchRoom}, which can quickly switch a user from one room to another.
 */
LITEAV_EXPORT @interface TRTCSwitchRoomConfig : NSObject

/// Field description: numeric room ID, which is optional. Users in the same room can see one another and make audio/video calls.
/// Recommended value: value range: 1–4294967294.
///@note either `roomId` or `strRoomId` must be entered. If both are entered, `roomId` will be used.
@property(nonatomic, assign) UInt32 roomId;

/// Field description: string-type room ID, which is optional. Users in the same room can see one another and make audio/video calls.
///@note either `roomId` or `strRoomId` must be entered. If both are entered, `roomId` will be used.
@property(nonatomic, copy, nullable) NSString *strRoomId;

/// Field description: user signature, which is optional. It is the authentication signature corresponding to the current `userId` and acts as the login password.
///           If you don't specify the newly calculated `userSig` during room switch, the SDK will continue to use the `userSig` you specified during room entry (enterRoom).
///           This requires you to ensure that the old `userSig` is still within the validity period allowed by the signature at the moment of room switch; otherwise, room switch will fail.
/// Recommended value: for the calculation method, please see [UserSig](https://www.tencentcloud.com/document/product/647/35166).
@property(nonatomic, copy, nullable) NSString *userSig;

/// Field description: permission credential used for permission control, which is optional. If you want only users with the specified `userId` values to enter a room, you need to use `privateMapKey` to restrict the permission.
/// Recommended value: we recommend you use this parameter only if you have high security requirements. For more information, please see [Enabling Advanced Permission Control](https://www.tencentcloud.com/document/product/647/35157).
@property(nonatomic, copy, nullable) NSString *privateMapKey;

@end

/**
 * 5.19 Format parameter of custom audio callback.
 *
 * This parameter is used to set the relevant format (including sample rate and number of channels) of the audio data called back by the SDK in the APIs related to custom audio callback.
 */
LITEAV_EXPORT @interface TRTCAudioFrameDelegateFormat : NSObject

/// Field description: sample rate
/// Recommended value: default value: 48000 Hz. Valid values: 16000, 32000, 44100, 48000.
@property(nonatomic, assign) TRTCAudioSampleRate sampleRate;

/// Field description: number of sound channels
/// Recommended value: default value: 1, which means mono channel. Valid values: 1: mono channel; 2: dual channel.
@property(nonatomic, assign) int channels;

/// Field description: number of sample points
/// Recommended value: the value must be an integer multiple of `sampleRate/100`.
@property(nonatomic, assign) int samplesPerCall;

/// Field description: audio callback data operation mode
/// Recommended value: {@link TRTCAudioFrameOperationModeReadOnly}, get audio data from callback only. The modes that can be set are {@link TRTCAudioFrameOperationModeReadOnly}, {@link TRTCAudioFrameOperationModeReadWrite}.
@property(nonatomic, assign) TRTCAudioFrameOperationMode mode;

@end

/**
 * 5.21 Screen sharing target information (for desktop systems only).
 *
 * When users share the screen, they can choose to share the entire desktop or only the window of a certain program.
 * `TRTCScreenCaptureSourceInfo` is used to describe the information of the target to be shared, including ID, name, and thumbnail. The fields in this structure are read-only.
 */
#if TARGET_OS_MAC && !TARGET_OS_IPHONE
LITEAV_EXPORT @interface TRTCScreenCaptureSourceInfo : NSObject

/// Field description: capturing source type (i.e., whether to share the entire screen or a certain window)
@property(assign, nonatomic) TRTCScreenCaptureSourceType type;

/// Field description: capturing source ID. For a window, this field indicates a window ID; for a screen, this field indicates a display ID.
@property(copy, nonatomic, nullable) NSString *sourceId;

/// Field description: capturing source name (encoded in UTF-8)
@property(copy, nonatomic, nullable) NSString *sourceName;

/// Field description: extended window information
@property(nonatomic, strong, nullable) NSDictionary *extInfo;

/// Field description: thumbnail of the shared window
@property(nonatomic, readonly, nullable) NSImage *thumbnail;

/// Field description: icon of the shared window
@property(nonatomic, readonly, nullable) NSImage *icon;

@end
#endif

/**
 * 5.24 parameter of the parallel strategy of remote audio streams.
 *
 * This parameter is used to set the parallel strategy of remote audio streams.
 */
LITEAV_EXPORT @interface TRTCAudioParallelParams : NSObject

/// Field description: Max number of remote audio streams. Default value: 0
/// - if maxCount > 0 and the number of people in the room is more than `maxCount`，SDK will select `maxCount` of remote audio streams in real time, which can reduce performance cost greatly.
///- if maxCount = 0，SDK won't limit the number of remote audio streams, which may cause performance cost when there are many speakers in one room.
@property(assign, nonatomic) UInt32 maxCount;

/// Field description: Users included that must be able to play.
///@note A list of user IDs. These users must be able to play and do not participate in smart selection.
/// The number of `incluseUsers` must be less than `maxCount`. Otherwise, the setting of the parallel strategy of remote audio streams is invalid.
///`incluseUsers` is valid when `maxCount` > 0. When `incluseUsers` takes effect, the max number of remote audio streams is (`maxCount` - the number of valid users in `incluseUsers`).
@property(nonatomic, strong, nullable) NSArray<NSString *> *includeUsers;

@end

/**
 * 5.25 The users whose streams to publish.
 *
 * You can use this parameter together with the publishing destination parameter {@link TRTCPublishTarget} and On-Cloud MixTranscoding parameter {@link TRTCStreamMixingConfig} to transcode the streams you specify and publish the mixed stream to the
 * destination you specify.
 */
LITEAV_EXPORT @interface TRTCUser : NSObject<NSCopying>

/// /**Description**: UTF-8-encoded user ID (required)
///**Value:** For example, if the ID of a user in your account system is "mike", set it to `mike`.
@property(nonatomic, copy, nonnull) NSString *userId;

/// **Description:** Numeric room ID. The room ID must be of the same type as that in {@link TRTCParams}.
///**Value:** Value range: 1-4294967294
///**Note:** You cannot use both `intRoomId` and `strRoomId`. If you specify `strRoomId`, you need to set `intRoomId` to `0`. If you set both, only `intRoomId` will be used.
@property(nonatomic, assign) UInt32 intRoomId;

/// **Description:** String-type room ID. The room ID must be of the same type as that in {@link TRTCParams}.
///**Note:** You cannot use both `intRoomId` and `strRoomId`. If you specify `roomId`, you need to leave `strRoomId` empty. If you set both, only `intRoomId` will be used.
///**Value:** 64 bytes or shorter; supports the following character set (89 characters):
///  - Uppercase and lowercase letters (a-z and A-Z)
/// - Numbers (0-9)
/// - Space, "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", "{", "}", "|", "~", ","
@property(nonatomic, copy, nullable) NSString *strRoomId;

@end

/**
 * 5.26 The destination URL when you publish to Tencent Cloud or a third-party CDN.
 *
 * This enum type is used by the publishing destination parameter {@link TRTCPublishTarget} of the publishing API {@link startPublishMediaStream}.
 */
LITEAV_EXPORT @interface TRTCPublishCdnUrl : NSObject<NSCopying>

/// **Description:** The destination URL (RTMP) when you publish to Tencent Cloud or a third-party CDN.
///**Value:** The URLs of different CDN providers may vary greatly in format. Please enter a valid URL as required by your service provider. TRTC's backend server will push audio/video streams in the standard format to the URL you provide.
///**Note:** The URL must be in RTMP format. It must also meet the requirements of your service provider, or your service provider may reject push requests from the TRTC backend.
@property(nonatomic, copy, nonnull) NSString *rtmpUrl;

/// **Description:** Whether to publish to Tencent Cloud
///**Value:** The default value is `true`.
///**Note:** If the destination URL you set is provided by Tencent Cloud, set this parameter to `true`, and you will not be charged relaying fees.
@property(nonatomic, assign) BOOL isInternalLine;

@end

/**
 * 5.27 The publishing destination.
 *
 * This enum type is used by the publishing API {@link startPublishMediaStream}.
 */
LITEAV_EXPORT @interface TRTCPublishTarget : NSObject

/// `Description:` The publishing mode.
///`Value:` You can relay streams to a CDN, transcode streams, or publish streams to an RTC room. Select the mode that fits your needs.
///@note If you need to use more than one publishing mode, you can call {@link startPublishMediaStream} multiple times and set `TRTCPublishTarget` to a different value each time.You can use one mode each time you call the {@link
/// startPublishMediaStream}) API. To modify the configuration, call {@link updatePublishCDNStream}.
@property(nonatomic) TRTCPublishMode mode;

/// `Description:` The destination URLs (RTMP) when you publish to Tencent Cloud or third-party CDNs.
///`Note:` You don’t need to set this parameter if you set the publishing mode to {@link TRTCPublishMixStreamToRoom}.
@property(nonatomic, copy, nullable) NSArray<TRTCPublishCdnUrl *> *cdnUrlList;

/// `Description:` The information of the robot that publishes the transcoded stream to a TRTC room.
///`Note:` You need to set this parameter only if you set the publishing mode to {@link TRTCPublishMixStreamToRoom}`.
///`Note:` After you set this parameter, the stream will be pushed to the room you specify. We recommend you set it to a special user ID to distinguish the robot from the anchor who enters the room via the TRTC SDK.
///`Note:` Users whose streams are transcoded cannot subscribe to the transcoded stream.
///`Note:` If you set the subscription mode ({@link setDefaultStreamRecvMode}) to manual before room entry, you need to manage the streams to receive by yourself (normally, if you receive the transcoded stream, you need to unsubscribe from the
/// streams that are transcoded). `Note:` If you set the subscription mode ({@link setDefaultStreamRecvMode}) to auto before room entry, users whose streams are not transcoded will receive the transcoded stream automatically and will unsubscribe from
/// the users whose streams are transcoded. You call {@link muteRemoteVideoStream} and {@link muteRemoteAudio} to unsubscribe from the transcoded stream.
@property(nonatomic, copy, nullable) TRTCUser *mixStreamIdentity;

@end

/**
 * 5.28 The video layout of the transcoded stream.
 *
 * This enum type is used by the On-Cloud MixTranscoding parameter {@link TRTCStreamMixingConfig} of the publishing API {@link startPublishMediaStream}.
 * You can use this parameter to specify the position, size, layer, and stream type of each video in the transcoded stream.
 */
LITEAV_EXPORT @interface TRTCVideoLayout : NSObject<NSCopying>

/// `Description:` The coordinates (in pixels) of the video.
@property(nonatomic, assign) CGRect rect;

/// `Description:` The layer of the video, which must be unique. Value range: 0-15.
@property(nonatomic, assign) int zOrder;

/// `Description:` The rendering mode.
///`Value:` The rendering mode may be fill (the image may be stretched or cropped) or fit (there may be black bars). Default value: {@link TRTCVideoFillMode_Fill}.
@property(nonatomic) TRTCVideoFillMode fillMode;

/// `Description:` The background color of the mixed stream.
///`Value:` The value must be a hex number. For example, "0x61B9F1" represents the RGB color value (97,158,241). Default value: 0x000000 (black).
@property(nonatomic, assign) int backgroundColor;

/// `Description:` The URL of the placeholder image. If a user sends only audio, the image specified by the URL will be mixed during On-Cloud MixTranscoding.
///`Value:` This parameter is left empty by default, which means no placeholder image will be used.
///@note
///    - You need to specify the `userId` parameter in `fixedVideoUser`.
///   - The URL can be 512 bytes long at most, and the image must not exceed 2 MB.
///   - The image can be in PNG, JPG, JPEG, or BMP format. We recommend you use a semitransparent image in PNG format.
@property(nonatomic, copy, nullable) NSString *placeHolderImage;

/// `Description:` The users whose streams are transcoded.
///@note If you do not specify {@link TRTCUser} (`userId`, `intRoomId`, `strRoomId`), the TRTC backend will automatically mix the streams of anchors who are sending audio/video in the room according to the video layout you specify.
@property(nonatomic, copy, nullable) TRTCUser *fixedVideoUser;

/// `Description:` Whether the video is the primary stream ({@link TRTCVideoStreamTypeBig}) or substream ({@link TRTCVideoStreamTypeSub}).
@property(nonatomic) TRTCVideoStreamType fixedVideoStreamType;

@end

/**
 * 5.29 The watermark layout.
 *
 * This enum type is used by the On-Cloud MixTranscoding parameter {@link TRTCStreamMixingConfig} of the publishing API {@link startPublishMediaStream}.
 */
LITEAV_EXPORT @interface TRTCWatermark : NSObject<NSCopying>

/// `Description:` The URL of the watermark image. The image specified by the URL will be mixed during On-Cloud MixTranscoding.
///@note
///    - The URL can be 512 bytes long at most, and the image must not exceed 2 MB.
///   - The image can be in PNG, JPG, JPEG, or BMP format. We recommend you use a semitransparent image in PNG format.
@property(nonatomic, copy, nonnull) NSString *watermarkUrl;

/// `Description:` The coordinates (in pixels) of the watermark.
@property(nonatomic, assign) CGRect rect;

/// `Description:` The layer of the watermark, which must be unique. Value range: 0-15.
@property(nonatomic, assign) int zOrder;

@end

/**
 * 5.30 The encoding parameters.
 *
 * `Description:` This enum type is used by the publishing API {@link startPublishMediaStream}.
 * `Note:` This parameter is required if you set the publishing mode to `TRTCPublish_MixStream_ToCdn` or `TRTCPublish_MixStream_ToRoom` in {@link TRTCPublishTarget}.
 * `Note:` If you use the relay to CDN feature (the publishing mode set to `RTCPublish_BigStream_ToCdn` or `TRTCPublish_SubStream_ToCdn`), to improve the relaying stability and playback compatibility, we also recommend you set this parameter.
 */
LITEAV_EXPORT @interface TRTCStreamEncoderParam : NSObject

/// `Description:` The resolution (width) of the stream to publish.
///`Value:` Recommended value: 368. If you mix only audio streams, to avoid displaying a black video in the transcoded stream, set both `width` and `height` to `0`.
@property(nonatomic, assign) int videoEncodedWidth;

/// `Description:` The resolution (height) of the stream to publish.
///`Value:` Recommended value: 640. If you mix only audio streams, to avoid displaying a black video in the transcoded stream, set both `width` and `height` to `0`.
@property(nonatomic, assign) int videoEncodedHeight;

/// `Description:` The frame rate (fps) of the stream to publish.
///`Value:` Value range: (0,30]. Default: 20.
@property(nonatomic, assign) int videoEncodedFPS;

/// `Description:` The keyframe interval (GOP) of the stream to publish.
///`Value:` Value range: [1,5]. Default: 3 (seconds).
@property(nonatomic, assign) int videoEncodedGOP;

/// `Description:` The video bitrate (Kbps) of the stream to publish.
///`Value:` If you set this parameter to `0`, TRTC will work out a bitrate based on `videoWidth` and `videoHeight`. For details, refer to the recommended bitrates for the constants of the resolution enum type (see comment).
@property(nonatomic, assign) int videoEncodedKbps;

/// `Description:` The audio sample rate of the stream to publish.
///`Value:` Valid values: [48000, 44100, 32000, 24000, 16000, 8000]. Default: 48000 (Hz).
@property(nonatomic, assign) int audioEncodedSampleRate;

/// `Description:` The sound channels of the stream to publish.
///`Value:` Valid values: 1 (mono channel); 2 (dual-channel). Default: 1.
@property(nonatomic, assign) int audioEncodedChannelNum;

/// `Description:` The audio bitrate (Kbps) of the stream to publish.
///`Value:` Value range: [32,192]. Default: 50.
@property(nonatomic, assign) int audioEncodedKbps;

/// `Description:` The audio codec of the stream to publish.
///`Value:` Valid values: 0 (LC-AAC); 1 (HE-AAC); 2 (HE-AACv2). Default: 0.
///@note
///  - The audio sample rates supported by HE-AAC and HE-AACv2 are 48000, 44100, 32000, 24000, and 16000.
/// - When HE-AACv2 is used, the output stream can only be dual-channel.
@property(nonatomic, assign) int audioEncodedCodecType;

/// `Description:` The video codec of the stream to publish.
///`Value:` Valid values: 0 (H264); 1 (H265). Default: 0.
@property(nonatomic, assign) int videoEncodedCodecType;

/// `Description:` SEI parameters. Default: null
///`Note:` the parameter is passed in the form of a JSON string. Here is an example to use it:
/// ```json
///{
///  "payLoadContent":"xxx",
///  "payloadType":5,
///  "payloadUuid":"1234567890abcdef1234567890abcdef",
///  "interval":1000,
///  "followIdr":false
///}
///```
/// The currently supported fields and their meanings are as follows:
/// - payloadContent: Required. The payload content of the passthrough SEI, which cannot be empty.
///- payloadType: Required. The type of the SEI message, with a value range of 5 or an integer within the range of [100, 254] (excluding 244, which is an internally defined timestamp SEI).
///- payloadUuid: Required when payloadType is 5, and ignored in other cases. The value must be a 32-digit hexadecimal number.
///- interval: Optional, default is 1000. The sending interval of the SEI, in milliseconds.
///- followIdr: Optional, default is false. When this value is true, the SEI will be ensured to be carried when sending a key frame, otherwise it is not guaranteed.
@property(nonatomic, copy, nullable) NSString *videoSeiParams;

@end

/**
 * 5.31 The transcoding parameters.
 *
 * This enum type is used by the publishing API {@link startPublishMediaStream}.
 * You can use this parameter to specify the video layout and input audio information for On-Cloud MixTranscoding.
 */
LITEAV_EXPORT @interface TRTCStreamMixingConfig : NSObject

/// `Description:` The background color of the mixed stream.
///`Value:` The value must be a hex number. For example, "0x61B9F1" represents the RGB color value (97,158,241). Default value: 0x000000 (black).
@property(nonatomic, assign) int backgroundColor;

/// `Description:` The URL of the background image of the mixed stream. The image specified by the URL will be mixed during On-Cloud MixTranscoding.
///`Value:` This parameter is left empty by default, which means no background image will be used.
///@note
///    - The URL can be 512 bytes long at most, and the image must not exceed 2 MB.
///   - The image can be in PNG, JPG, JPEG, or BMP format. We recommend you use a semitransparent image in PNG format.
@property(nonatomic, copy, nullable) NSString *backgroundImage;

/// `Description:` The position, size, layer, and stream type of each video in On-Cloud MixTranscoding.
///`Value:` This parameter is an array. Each `TRTCVideoLayout` element in the array indicates the information of a video in On-Cloud MixTranscoding.
@property(nonatomic, copy, nullable) NSArray<TRTCVideoLayout *> *videoLayoutList;

/// `Description:` The information of each audio stream to mix.
///`Value:` This parameter is an array. Each `TRTCUser` element in the array indicates the information of an audio stream.
///@note If you do not specify this array, the TRTC backend will automatically mix all streams of the anchors who are sending audio in the room according to the audio encode param {@link TRTCStreamEncoderParam} you specify (currently only supports up
/// to 16 audio and video inputs).
@property(nonatomic, copy, nullable) NSArray<TRTCUser *> *audioMixUserList;

/// `Description:` The position, size, and layer of each watermark image in On-Cloud MixTranscoding.
///`Value:` This parameter is an array. Each `TRTCWatermark` element in the array indicates the information of a watermark.
@property(nonatomic, copy, nullable) NSArray<TRTCWatermark *> *watermarkList;

@end

/**
 * 5.32 Media Stream Private Encryption Configuration.
 *
 * This configuration is used to set the algorithm and key for media stream private encryption.
 */
LITEAV_EXPORT @interface TRTCPayloadPrivateEncryptionConfig : NSObject<NSCopying>

/// `Description:` Encryption algorithm, the default is {@link TRTCEncryptionAlgorithmAes128Gcm}.
@property(nonatomic, assign) TRTCEncryptionAlgorithm encryptionAlgorithm;

/// `Description:` encryption key, string type.
///`Value:` If the encryption algorithm is {@link TRTCEncryptionAlgorithmAes128Gcm}, the key length must be 16 bytes;
///         if the encryption algorithm is {@link TRTCEncryptionAlgorithmAes256Gcm}, the key length must be 32 bytes.
@property(nonatomic, copy, nonnull) NSString *encryptionKey;

/// `Description:` Salt, initialization vector for encryption.
///`Value:` It is necessary to ensure that the array filled in this parameter is not empty, not all 0 and the data length is 32 bytes.
@property(nonatomic, strong, nonnull) NSData *encryptionSalt;

@end

/**
 * 5.33 Volume evaluation and other related parameter settings.
 *
 * This setting is used to enable vocal detection and sound spectrum calculation.
 */
LITEAV_EXPORT @interface TRTCAudioVolumeEvaluateParams : NSObject<NSCopying>

/// `Description:` Set the trigger interval of the {@link onUserVoiceVolume} callback, the unit is milliseconds, the minimum interval is 100ms, if it is less than or equal to 0, the callback will be closed.
///`Value:` Recommended value: 300, in milliseconds.
///@note When the interval is greater than 0, the volume prompt will be enabled by default, no additional setting is required.
@property(nonatomic, assign) NSUInteger interval;

/// `Description:` Whether to enable local voice detection.
///@note Call before startLocalAudio.
@property(nonatomic, assign) BOOL enableVadDetection;

/// `Description:` Whether to enable local vocal frequency calculation.
@property(nonatomic, assign) BOOL enablePitchCalculation;

/// `Description:` Whether to enable sound spectrum calculation.
@property(nonatomic, assign) BOOL enableSpectrumCalculation;

@end
