/**
 * Copyright (c) 2021 Tencent. All rights reserved.
 * Module:   V2TXLiveDef @ TXLiteAVSDK
 * Function: Key type definitions for Tencent Cloud LVB
 */
#import "V2TXLiveCode.h"
#import "TXLiteAVSymbolExport.h"

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
typedef UIView TXView;
typedef UIImage TXImage;
#elif TARGET_OS_MAC
#import <AppKit/AppKit.h>
typedef NSView TXView;
typedef NSImage TXImage;
#endif

/////////////////////////////////////////////////////////////////////////////////
//
//                              Supported protocol
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * Supported protocol, RTMP is not supported on Windows or macOS.
 */
typedef NS_ENUM(NSUInteger, V2TXLiveMode) {

    /// RTMP protocol.
    V2TXLiveMode_RTMP,

    /// TRTC protocol.
    V2TXLiveMode_RTC

};

/////////////////////////////////////////////////////////////////////////////////
//
//           (1) Video type definitions
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * Video resolution.
 */
typedef NS_ENUM(NSInteger, V2TXLiveVideoResolution) {

    ///  Resolution: 160×160. Bitrate range: 100 Kbps to 150 Kbps. Frame rate: 15 fps.
    V2TXLiveVideoResolution160x160,

    ///  Resolution: 270×270. Bitrate range: 200 Kbps to 300 Kbps. Frame rate: 15 fps.
    V2TXLiveVideoResolution270x270,

    ///  Resolution: 480×480. Bitrate range: 350 Kbps to 525 Kbps. Frame rate: 15 fps.
    V2TXLiveVideoResolution480x480,

    ///  Resolution: 320×240. Bitrate range: 250 Kbps to 375 Kbps. Frame rate: 15 fps.
    V2TXLiveVideoResolution320x240,

    ///  Resolution: 480×360. Bitrate range: 400 Kbps to 600 Kbps. Frame rate: 15 fps.
    V2TXLiveVideoResolution480x360,

    ///  Resolution: 640×480. Bitrate range: 600 Kbps to 900 Kbps. Frame rate: 15 fps.
    V2TXLiveVideoResolution640x480,

    ///  Resolution: 320×180. Bitrate range: 250 Kbps to 400 Kbps. Frame rate: 15 fps.
    V2TXLiveVideoResolution320x180,

    ///  Resolution: 480×270. Bitrate range: 350 Kbps to 550 Kbps. Frame rate: 15 fps.
    V2TXLiveVideoResolution480x270,

    ///  Resolution: 640×360. Bitrate range: 500 Kbps to 900 Kbps. Frame rate: 15 fps.
    V2TXLiveVideoResolution640x360,

    ///  Resolution: 960×540. Bitrate range: 800 Kbps to 1500 Kbps. Frame rate: 15 fps.
    V2TXLiveVideoResolution960x540,

    ///  Resolution: 1280×720. Bitrate range: 1000 Kbps to 1800 Kbps. Frame rate: 15 fps.
    V2TXLiveVideoResolution1280x720,

    ///  Resolution: 1920×1080. Bitrate range: 2500 Kbps to 3000 Kbps. Frame rate: 15 fps.
    V2TXLiveVideoResolution1920x1080

};

/**
 * Video aspect ratio mode
 *
 * @info Video aspect ratio mode.
 * @note
 * - Landscape resolution: V2TXLiveVideoResolution640x360 + V2TXLiveVideoResolutionModeLandscape = 640 × 360.
 * - Portrait resolution:  V2TXLiveVideoResolution640x360 + V2TXLiveVideoResolutionModePortrait  = 360 × 640.
 */
typedef NS_ENUM(NSInteger, V2TXLiveVideoResolutionMode) {

    ///  Landscape resolution.
    V2TXLiveVideoResolutionModeLandscape = 0,

    ///  Portrait resolution.
    V2TXLiveVideoResolutionModePortrait = 1,

};

/**
 * Video encoding parameters
 *
 * These settings determine the quality of image viewed by remote users.
 */
LITEAV_EXPORT @interface V2TXLiveVideoEncoderParam : NSObject

///  `Field description:` video resolution.
/// `Recommended value:`
///  - For desktop platforms (Windows and macOS), we recommend you select a resolution of 640x360 or above and select `Landscape` (landscape resolution) for `videoResolutionMode`.
///@note  to use a portrait resolution, please specify `videoResolutionMode` as `Portrait`; for example, when used together with `Portrait`, 640x360 represents 360x640.
@property(nonatomic, assign) V2TXLiveVideoResolution videoResolution;

/// `Field description:` resolution mode (landscape/portrait).
///`Recommended value:` for desktop platforms (Windows and macOS), `Landscape` is recommended.
///@note  to use a portrait resolution, please specify `videoResolutionMode` as `Portrait`; for example, when used together with `Portrait`, 640x360 represents 360x640.
@property(nonatomic, assign) V2TXLiveVideoResolutionMode videoResolutionMode;

/// `Field description:` video capturing frame rate.
///`Recommended value:` 15 or 20 fps. If the frame rate is lower than 5 fps, there will be obvious lagging; if lower than 10 fps but higher than 5 fps, there will be slight lagging; if higher than 20 fps, the bandwidth will be wasted (the frame rate
/// of movies is generally 24 fps).
@property(nonatomic, assign) int videoFps;

/// `Field description:` target video bitrate. The SDK encodes streams at the target video bitrate and will actively reduce the bitrate only in weak network environments.
///`Recommended value:` please see the optimal bitrate for each specification in `V2TXLiveVideoResolution`. You can also slightly increase the optimal bitrate.
///           For example, `V2TXLiveVideoResolution1280x720` corresponds to the target bitrate of 1,200 Kbps. You can also set the bitrate to 1,500 Kbps for higher definition.
///@note  you can set the `videoBitrate` and `minVideoBitrate` parameters at the same time to restrict the SDK's adjustment range of the video bitrate:
///  - If you set `videoBitrate` and `minVideoBitrate` to the same value, it is equivalent to disabling the adaptive adjustment capability of the SDK for the video bitrate.
@property(nonatomic, assign) int videoBitrate;

///  `Field description:` minimum video bitrate. The SDK will reduce the bitrate to as low as the value specified by `minVideoBitrate` to ensure the smoothness only if the network conditions are poor.
///`Recommended value:` you can set the `videoBitrate` and `minVideoBitrate` parameters at the same time to restrict the SDK's adjustment range of the video bitrate:
///  - If you set `videoBitrate` and `minVideoBitrate` to the same value, it is equivalent to disabling the adaptive adjustment capability of the SDK for the video bitrate.
@property(nonatomic, assign) int minVideoBitrate;

- (instancetype _Nonnull)initWith:(V2TXLiveVideoResolution)resolution;

@end

/**
 * Local camera mirror type.
 */
typedef NS_ENUM(NSInteger, V2TXLiveMirrorType) {

    ///  Default mirror type. Images from the front camera are mirrored, and images from the rear camera are not mirrored.
    V2TXLiveMirrorTypeAuto,

    ///  Both the front and rear cameras are switched to the mirror mode.
    V2TXLiveMirrorTypeEnable,

    ///  Both the front and rear cameras are switched to the non-mirror mode.
    V2TXLiveMirrorTypeDisable

};

/**
 * Image fill mode
 */
typedef NS_ENUM(NSInteger, V2TXLiveFillMode) {

    ///  The entire screen is covered by the image, without black edges. If the aspect ratio of the image is different from that of the screen, part of the image will be cropped.
    V2TXLiveFillModeFill,

    ///  The image adapts to the screen and is not cropped. If the aspect ratio of the image is different from that of the screen, black edges will appear.
    V2TXLiveFillModeFit,

    ///  The screen is entirely covered by the image. The image will be stretched if screen and image have different aspect ratios.
    V2TXLiveFillModeScaleFill

};

/**
 * Clockwise rotation of the video image
 */
typedef NS_ENUM(NSInteger, V2TXLiveRotation) {

    ///  No rotation.
    V2TXLiveRotation0,

    ///  Rotate 90 degrees clockwise.
    V2TXLiveRotation90,

    ///  Rotate 180 degrees clockwise.
    V2TXLiveRotation180,

    ///  Rotate 270 degrees clockwise.
    V2TXLiveRotation270

};

/**
 * Pixel format of video frames
 */
typedef NS_ENUM(NSInteger, V2TXLivePixelFormat) {

    ///  Unknown.
    V2TXLivePixelFormatUnknown,

    ///  YUV420P I420.
    V2TXLivePixelFormatI420,

    ///  YUV420SP NV12.
    V2TXLivePixelFormatNV12,

    ///  BGRA8888.
    V2TXLivePixelFormatBGRA32,

    ///  Texture2D.
    V2TXLivePixelFormatTexture2D

};

/**
 * Video data container format
 *
 * @info Video data container format.
 * @note In the custom capture and rendering features, you need to use the following enumerated values to specify the format for containing video data.
 * - PixelBuffer: this is most efficient when used directly. The iOS system provides various APIs to obtain or process PixelBuffer.
 * - NSData: when this is applied to custom rendering, PixelBuffer is copied once to NSData. When it is applied to custom capture, NSData is copied once to PixelBuffer. Therefore, the performance is affected to some extent.
 */
typedef NS_ENUM(NSInteger, V2TXLiveBufferType) {

    ///  Unknown.
    V2TXLiveBufferTypeUnknown,

    ///  This is most efficient when used directly. The iOS system provides various APIs to obtain or process PixelBuffer.
    V2TXLiveBufferTypePixelBuffer,

    ///  The performance is affected to some extent. As the SDK internally processes PixelBuffer directly, type switching between NSData and PixelBuffer results in memory copy overhead.
    V2TXLiveBufferTypeNSData,

    ///  Texture.
    V2TXLiveBufferTypeTexture

};

/**
 * Video frame information
 *
 * @info Video frame information.
 *         V2TXLiveVideoFrame describes the raw data of a video image frame, which can be the image before frame encoding or the image after frame decoding.
 * @note  Used during custom capture and rendering. During custom capture, you need to use V2TXLiveVideoFrame to contain the video frame to be sent. During custom rendering, the video frame contained by V2TXLiveVideoFrame will be returned.
 */
LITEAV_EXPORT @interface V2TXLiveVideoFrame : NSObject

/// `Field description:` Video pixel format.
///`Recommended value:` V2TXLivePixelFormatNV12.
@property(nonatomic, assign) V2TXLivePixelFormat pixelFormat;

/// `Field description:` Video data container format.
///`Recommended value:` V2TXLiveBufferTypePixelBuffer.
@property(nonatomic, assign) V2TXLiveBufferType bufferType;

/// `Field description:` Video data when bufferType is V2TXLiveBufferTypeNSData.
@property(nonatomic, strong, nullable) NSData *data;

///   `Field description:` Video data when bufferType is V2TXLiveBufferTypePixelBuffer.
@property(nonatomic, assign, nullable) CVPixelBufferRef pixelBuffer;

/// `Field description:` Video width.
@property(nonatomic, assign) NSUInteger width;

/// `Field description:` Video height.
@property(nonatomic, assign) NSUInteger height;

/// `Field description:` Clockwise rotation angle of video frames.
@property(nonatomic, assign) V2TXLiveRotation rotation;

/// `Field description:` Texture ID.
@property(nonatomic, assign) GLuint textureId;

@end

/**
 * Picture-in-Picture state
 */
typedef NS_ENUM(NSInteger, V2TXLivePictureInPictureState) {

    /// Undefined.
    V2TXLivePictureInPictureStateUndefined,

    /// An error occurred in Picture-in-Picture mode.
    V2TXLivePictureInPictureStateOccurError,

    /// Picture-in-Picture mode will start.
    V2TXLivePictureInPictureStateWillStart,

    /// Picture-in-Picture mode did start.
    V2TXLivePictureInPictureStateDidStart,

    /// Picture-in-Picture mode will stop.
    V2TXLivePictureInPictureStateWillStop,

    /// Picture-in-Picture mode did stop.
    V2TXLivePictureInPictureStateDidStop,

    /// Picture-in-Picture restore the user interface.
    V2TXLivePictureInPictureStateRestoreUI

};

/////////////////////////////////////////////////////////////////////////////////
//
//          (2) Audio type definitions
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * Audio quality
 */
typedef NS_ENUM(NSInteger, V2TXLiveAudioQuality) {

    ///  Audio: 16k sample rate, mono-channel, 16 Kbps audio raw bitrate. This quality is suitable for scenarios that mainly involve voice calls, such as online meetings and voice calls.
    V2TXLiveAudioQualitySpeech,

    ///  General: 48k sample rate, mono-channel, 50 Kbps audio raw bitrate. This quality is the default audio quality of the SDK. We recommend that you choose this option unless you have special requirements.
    V2TXLiveAudioQualityDefault,

    ///  Music: 48k sample rate, dual-channel + full-band, 128 Kbps audio raw bitrate. This quality is suitable for scenarios that require Hi-Fi music transmission, such as karaoke and music livestreams.
    V2TXLiveAudioQualityMusic

};

/**
 * @brief audio frame
 */
LITEAV_EXPORT @interface V2TXLiveAudioFrame : NSObject

/// `Field description:` audio data.
@property(nonatomic, strong, nullable) NSData *data;

/// `Field description:` audio sample rate.
@property(nonatomic, assign) int sampleRate;

/// `Field description:` number of sound channels.
@property(nonatomic, assign) int channel;

/// Field description: timestamp in ms
@property(nonatomic, assign) uint64_t timestamp;

@end

/**
 *  Audio callback data operation mode
 *
 * SDK provides two modes of operation for audio callback data.
 * - Read-only mode (ReadOnly): Get audio data only from the callback.
 * - ReadWrite mode (ReadWrite): You can get and modify the audio data of the callback.
 */
typedef NS_ENUM(NSInteger, V2TXLiveAudioFrameOperationMode) {

    /// Read-write mode: You can get and modify the audio data of the callback, the default mode.
    V2TXLiveAudioFrameOperationModeReadWrite = 0,

    /// Read-only mode: Get audio data from callback only.
    V2TXLiveAudioFrameOperationModeReadOnly = 1,

};

/**
 * audio callback format
 */
LITEAV_EXPORT @interface V2TXLiveAudioFrameObserverFormat : NSObject

/// `Field description:` sample rate.
///`Recommended value:` default value: 48000 Hz. Valid values: 16000, 32000, 44100, 48000.
@property(nonatomic, assign) int sampleRate;

/// `Field description:` number of sound channels.
///`Recommended value:` default value: 1, which means mono channel. Valid values: 1: mono channel; 2: dual channel.
@property(nonatomic, assign) int channel;

/// `Field description:` number of sample points.
///`Recommended value:` the value must be an integer multiple of sampleRate/100.
@property(nonatomic, assign) int samplesPerCall;

/// `Field description:` audio callback data operation mode.
///`Recommended value:` V2TXLiveAudioFrameOperationModeReadOnly, get audio data from callback only. The modes that can be set are V2TXLiveAudioFrameOperationModeReadOnly, V2TXLiveAudioFrameOperationModeReadWrite.
@property(nonatomic, assign) V2TXLiveAudioFrameOperationMode mode;

@end

/////////////////////////////////////////////////////////////////////////////////
//
//          (3) Definitions of statistical metrics for pushers and players
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * Pusher statistics
 */
LITEAV_EXPORT @interface V2TXLivePusherStatistics : NSObject

/// `Field description:` CPU utilization of the current app (%).
@property(nonatomic, assign) NSUInteger appCpu;

/// `Field description:` CPU utilization of the current system (%).
@property(nonatomic, assign) NSUInteger systemCpu;

/// `Field description:` Video width.
@property(nonatomic, assign) NSUInteger width;

/// `Field description:` Video height.
@property(nonatomic, assign) NSUInteger height;

/// `Field description:` Frame rate (fps).
@property(nonatomic, assign) NSUInteger fps;

/// `Field description:` Video bitrate (Kbps).
@property(nonatomic, assign) NSUInteger videoBitrate;

/// `Field description:` Audio bitrate (Kbps).
@property(nonatomic, assign) NSUInteger audioBitrate;

/// `Field description:` Round-trip delay (ms) from the SDK to cloud.
@property(nonatomic, assign) NSUInteger rtt;

/// `Field description:` upload speed (Kbps).
@property(nonatomic, assign) NSUInteger netSpeed;

@end

/**
 * Player statistics
 */
LITEAV_EXPORT @interface V2TXLivePlayerStatistics : NSObject

/// `Field description:` CPU utilization of the current app (%).
@property(nonatomic, assign) NSUInteger appCpu;

/// `Field description:` CPU utilization of the current system (%).
@property(nonatomic, assign) NSUInteger systemCpu;

/// `Field description:` Video width.
@property(nonatomic, assign) NSUInteger width;

/// `Field description:` Video height.
@property(nonatomic, assign) NSUInteger height;

/// `Field description:` Frame rate (fps).
@property(nonatomic, assign) NSUInteger fps;

/// `Field description:` Video bitrate (Kbps).
@property(nonatomic, assign) NSUInteger videoBitrate;

/// `Field description:` Audio bitrate (Kbps).
@property(nonatomic, assign) NSUInteger audioBitrate;

/// `Field description`: Total packet loss rate (%) of the audio/video stream. Note: Only playback address prefixed with [trtc://] or [webrtc://] are supported.
@property(nonatomic, assign) NSUInteger audioPacketLoss;

/// `Field description`: Total packet loss rate (%) of the audio/video stream. Note: Only playback address prefixed with [trtc://] or [webrtc://] are supported.
@property(nonatomic, assign) NSUInteger videoPacketLoss;

/// `Field description`: Playback delay (ms).
@property(nonatomic, assign) NSUInteger jitterBufferDelay;

/// `Field description`: Cumulative audio playback lag duration (ms).
/// The duration is the block duration within 2s.
@property(nonatomic, assign) NSUInteger audioTotalBlockTime;

/// `Field description`: Audio playback lag rate (%).
/// Audio playback lag rate (audioBlockRate) = cumulative audio playback lag duration (audioTotalBlockTime)/audio playback interval duration (2000ms).
@property(nonatomic, assign) NSUInteger audioBlockRate;

/// `Field description`: Cumulative video playback lag duration (ms).
/// The duration is the block duration within 2s.
@property(nonatomic, assign) NSUInteger videoTotalBlockTime;

/// `Field description`: Video playback lag rate (%).
/// Video playback lag rate (videoBlockRate) = cumulative video playback lag duration (videoTotalBlockTime)/video playback interval duration (2000ms).
@property(nonatomic, assign) NSUInteger videoBlockRate;

/// `Field description:` Round-trip delay (ms) from the SDK to cloud. Note: Only playback address prefixed with [trtc://] or [webrtc://] are supported.
@property(nonatomic, assign) NSUInteger rtt;

/// `Field description:` donwload speed (Kbps).
@property(nonatomic, assign) NSUInteger netSpeed;

@end

/////////////////////////////////////////////////////////////////////////////////
//
//          (4) Definitions of connection-status-related enumerated values
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * Livestream connection status
 */
typedef NS_ENUM(NSInteger, V2TXLivePushStatus) {

    ///  Disconnected from the server.
    V2TXLivePushStatusDisconnected,

    ///  Connecting to the server.
    V2TXLivePushStatusConnecting,

    ///  Connected to the server successfully.
    V2TXLivePushStatusConnectSuccess,

    ///  Reconnecting to the server.
    V2TXLivePushStatusReconnecting,

};

/**
 * Playback mode
 */
typedef NS_ENUM(NSInteger, V2TXAudioRoute) {

    ///  Speaker.
    V2TXAudioModeSpeakerphone,

    ///  Earpiece.
    V2TXAudioModeEarpiece,

};

/**
 * Specify the type of streams to mix
 */
typedef NS_ENUM(NSInteger, V2TXLiveMixInputType) {

    /// Audio and video.
    V2TXLiveMixInputTypeAudioVideo,

    /// Video only.
    V2TXLiveMixInputTypePureVideo,

    ///  Audio only.
    V2TXLiveMixInputTypePureAudio,

};

/**
 * Position of each subimage in On-Cloud MixTranscoding
 */
LITEAV_EXPORT @interface V2TXLiveMixStream : NSObject

/// `Field description:` `userId` of users whose streams are mixed.
@property(nonatomic, copy, nonnull) NSString *userId;

/// `Field description:` push `streamId` of users whose streams are mixed. `nil` indicates the current push `streamId`.
@property(nonatomic, copy, nullable) NSString *streamId;

/// `Field description:` x-axis (absolute pixels) of the image layer.
@property(nonatomic, assign) NSInteger x;

/// `Field description:` y-axis (absolute pixels) of the image layer.
@property(nonatomic, assign) NSInteger y;

/// `Field description:` width (absolute pixels) of the image layer.
@property(nonatomic, assign) NSInteger width;

/// `Field description:` height (absolute pixels) of the image layer.
@property(nonatomic, assign) NSInteger height;

/// `Field description:` layer number (1-15), which must be unique.
@property(nonatomic, assign) NSUInteger zOrder;

/// `Field description:` input type of the live stream.
@property(nonatomic, assign) V2TXLiveMixInputType inputType;

@end

/**
 * Configure On-Cloud MixTranscoding
 */
LITEAV_EXPORT @interface V2TXLiveTranscodingConfig : NSObject

/// `Field description:` width of transcoded video.
///`Recommended value:` 360 px. If audio-only streams are mixed, the mixing result will carry a video stream that shows a canvas background. To avoid this, set both the width and height to 0 px.
@property(nonatomic, assign) NSUInteger videoWidth;

/// `Field description:` height of transcoded video.
///`Recommended value:` 640 px. If audio-only streams are mixed, the mixing result will carry a video stream that shows a canvas background. To avoid this, set both the width and height to 0 px.
@property(nonatomic, assign) NSUInteger videoHeight;

/// `Field description:` bitrate (Kbps) for the resolution of the transcoded video.
///`Recommended value:` if you set it to 0, the backend will calculate a bitrate based on `videoWidth` and `videoHeight`. You can also refer to the remarks for the enumerated value `V2TXLiveVideoResolution`.
@property(nonatomic, assign) NSUInteger videoBitrate;

/// `Field description:` frame rate (fps) for the resolution of the transcoded video.
///`Value range:` (0,30]; default: 15.
@property(nonatomic, assign) NSUInteger videoFramerate;

/// `Field description:` keyframe interval (GOP) for the resolution of the transcoded video.
///`Value range:` [1,8]; default value: 2 (sec).
@property(nonatomic, assign) NSUInteger videoGOP;

/// `Field description:` background color of the mixed video image. The default color is black, and the value is a hex number. For example: "0x61B9F1" represents the RGB color (97,158,241).
///**Default value:** 0x000000 (black)
@property(nonatomic, assign) NSUInteger backgroundColor;

/// `Field description:` background image of the mixed video.
///**Default value:** `nil`, which means that no background image is set.
///@note  you need to first upload the image in **Application Management** > **Function Configuration** > **Material Management** in the [console](https://console.cloud.tencent.com/trtc).
///            You will get an image ID for the image uploaded, which you need to convert to a string and use it as the value of `backgroundImage`.
///            For example, if the image ID is 63, you should set `backgroundImage` to `63`.
@property(nonatomic, copy, nullable) NSString *backgroundImage;

/// `Field description:` audio sample rate of the transcoded stream.
///`Valid values:` 12000 Hz, 16000 Hz, 22050 Hz, 24000 Hz, 32000 Hz, 44100 Hz, 48000 Hz (default).
@property(nonatomic, assign) NSUInteger audioSampleRate;

/// `Field description:` audio bitrate of the transcoded stream.
///`Value range:` [32,192]; default value: 64 (Kbps).
@property(nonatomic, assign) NSUInteger audioBitrate;

/// `Field description:` number of sound channels of the transcoded stream.
///`Valid values:` 1 (default), 2.
@property(nonatomic, assign) NSUInteger audioChannels;

/// `Field description:` position of each channel of subimage.
@property(nonatomic, copy, nonnull) NSArray<V2TXLiveMixStream *> *mixStreams;

/// `Field description:` ID of the live stream pushed to CDN.
///          If you do not set this parameter, the SDK will execute the default logic, that is, it will mix multiple streams in the room into the video stream of the API caller, i.e., A + B => A.
///          If you set this parameter, the SDK will mix multiple streams in the room into the live stream whose ID you have specified, i.e., A + B => C.
/// `Default value`: `nil`, which indicates that multiple streams in the room are mixed into the video stream of the API caller.
@property(nonatomic, copy, nullable) NSString *outputStreamId;

@end

/**
 *  Recording audio and video mode
 */
typedef NS_ENUM(NSUInteger, V2TXLiveRecordMode) {

    /// Both mode: Recording audio and video
    V2TXLiveRecordModeBoth,

};

/**
 * Configure On-LocalRecording
 */
LITEAV_EXPORT @interface V2TXLiveLocalRecordingParams : NSObject

/// `Field description:` The path of the recorded file (required), please ensure that the path has read and write permissions and is legal, otherwise the recorded file cannot be generated.
///`Recommended value:` "yourpath/record/test.mp4". The path needs to be accurate to the file name and format suffix. The format suffix is used to determine the recorded file format. The currently supported format is only MP4.
@property(nonatomic, copy, nonnull) NSString *filePath;

/// `Field description:` Media recording mode.
/// `Default value`: `V2TXLiveRecordModeBoth`, which means recording audio and video at the same time.
@property(nonatomic, assign) V2TXLiveRecordMode recordMode;

/// `Field description:` interval Recording information update frequency (optional), in milliseconds, valid range: 1000-10000.
/// `Default value`: `-1`, which means no callback.
@property(nonatomic, assign) int interval;

@end

/**
 * Protocol configured with socks5 proxy.
 */
LITEAV_EXPORT @interface V2TXLiveSocks5ProxyConfig : NSObject

/// `Field description:` Indicates whether HTTPS is supported.
///`Recommended value:` Default value: true.
@property(nonatomic, assign) BOOL supportHttps;

/// `Field description:` Indicates whether TCP is supported.
///`Recommended value:` Default value: true.
@property(nonatomic, assign) BOOL supportTcp;

/// `Field description:` Indicates whether UDP is supported.
///`Recommended value:` Default value: true.
@property(nonatomic, assign) BOOL supportUdp;

@end

/////////////////////////////////////////////////////////////////////////////////
//
//          (5) Definitions of common configuration components
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * Log level
 */
typedef NS_ENUM(NSInteger, V2TXLiveLogLevel) {

    ///  Output all levels of log.
    V2TXLiveLogLevelAll = 0,

    /// Output DEBUG, INFO, WARNING, ERROR and FATAL level log.
    V2TXLiveLogLevelDebug = 1,

    ///  Output INFO, WARNING, ERROR and FATAL level log.
    V2TXLiveLogLevelInfo = 2,

    ///  Output WARNING, ERROR and FATAL level log.
    V2TXLiveLogLevelWarning = 3,

    ///  Output ERROR and FATAL level log.
    V2TXLiveLogLevelError = 4,

    ///  Only output FATAL level log.
    V2TXLiveLogLevelFatal = 5,

    ///  Does not output any sdk log.
    V2TXLiveLogLevelNULL = 6,

};

/**
 * Log configuration
 */
LITEAV_EXPORT @interface V2TXLiveLogConfig : NSObject

/// `Field description:` Set Log level.
///`Recommended value:` Default value: V2TXLiveLogLevelAll.
@property(nonatomic, assign) V2TXLiveLogLevel logLevel;

/// `Field description:`    Whether to receive the log information to be printed through V2TXLivePremierObserver.
///`Special Instructions:` If you want to implement Log writing by yourself, you can turn on this switch, Log information will be called back to you V2TXLivePremierObserver#onLog.
///`Recommended value:`    Default value: NO.
@property(nonatomic, assign) BOOL enableObserver;

/// `Field description:` Whether to allow the SDK to print Log on the console of the editor (XCoder, Android Studio, Visual Studio, etc.).
///`Recommended value:` Default value: NO.
@property(nonatomic, assign) BOOL enableConsole;

/// `Field description:`    Whether to enable local log file.
///`Special Instructions:` If not for special needs, please do not close the local log file, otherwise the Tencent Cloud technical team will not be able to track and locate problems when they occur.
///`Recommended value:`    Default value: YES.
@property(nonatomic, assign) BOOL enableLogFile;

/// `Field description:` Set the storage directory of the local log, default Log storage location:
///  iOS & Mac: sandbox Documents/log.
@property(nonatomic, copy, nullable) NSString *logPath;

@end

/**
 * Stream information supporting adaptive handover.
 */
LITEAV_EXPORT @interface V2TXLiveStreamInfo : NSObject

/// `Field description:` Video width, default value: 0, means unknown.
@property(nonatomic, assign) int width;

/// `Field description:` Video height, default value: 0, means unknown.
@property(nonatomic, assign) int height;

/// `Field description:` Bitrate in bps, default value: 0, means unknown.
@property(nonatomic, assign) int bitrate;

/// `Field description:` Framerate, default value: 0, means unknown.
@property(nonatomic, assign) float framerate;

/// `Field description:` Stream url.
@property(nonatomic, copy, nullable) NSString *url;

@end
