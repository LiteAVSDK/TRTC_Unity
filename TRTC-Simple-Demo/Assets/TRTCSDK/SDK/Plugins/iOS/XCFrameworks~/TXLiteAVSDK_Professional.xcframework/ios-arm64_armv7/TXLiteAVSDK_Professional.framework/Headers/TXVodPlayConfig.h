//  Copyright © 2021 Tencent. All rights reserved.

#import <Foundation/Foundation.h>
#import "TXLiteAVSymbolExport.h"

/**
 * 'INDEX_AUTO' is  the configuration parameter of the  adaptive bit rate playback function
 */
LITEAV_EXPORT extern NSInteger const INDEX_AUTO;

/**
 * Audio normalization preset parameter: audio normalization, off
 */
LITEAV_EXPORT extern float const AUDIO_NORMALIZATION_OFF;

/**
 * Audio normalization preset parameter: audio normalization, standard loudness
 */
LITEAV_EXPORT extern float const AUDIO_NORMALIZATION_STANDARD;

/**
 * Audio normalization preset parameter: audio normalization, low loudness
 */
LITEAV_EXPORT extern float const AUDIO_NORMALIZATION_LOW;

/**
 * Audio normalization preset parameter: audio normalization, high loudness
 */
LITEAV_EXPORT extern float const AUDIO_NORMALIZATION_HIGH;

/**
 * MP4 encrypted playback levels
 */
typedef NS_ENUM(NSInteger, TX_Enum_MP4EncryptionLevel) {

    /// No encryption
    MP4_ENCRYPTION_LEVEL_NONE = 0,

    /// Level 1 (online encryption)
    MP4_ENCRYPTION_LEVEL_L1 = 1,

    /// Level 2 (local encryption)
    MP4_ENCRYPTION_LEVEL_L2 = 2,
};

/**
 * Player type definition
 */
typedef NS_ENUM(NSInteger, TX_Enum_PlayerType) {

    /// Based on System player.
    PLAYER_AVPLAYER = 0,

    /// Based On FFmepg, Soft decoder is supported，Better compatibility.
    PLAYER_THUMB_PLAYER = 1,
};

/**
 * Video Resolution type definition
 */
typedef NS_ENUM(NSInteger, TX_Enum_VideoResolution) {

    /// RESOLUTION 720X1280
    VIDEO_RESOLUTION_720X1280 = 720 * 1280,

    /// RESOLUTION 1080X1920
    VIDEO_RESOLUTION_1080X1920 = 1080 * 1920,

    /// RESOLUTION 1440X2560
    VIDEO_RESOLUTION_1440X2560 = 1440 * 2560,

    /// RESOLUTION  2160X3840
    VIDEO_RESOLUTION_2160X3840 = 2160 * 3840,
};

/**
 * MediaType(Using the adaptive bit rate playback function, you need to set the specific HLS code stream to be vod/live media assets, and the Auto type is not supported temporarily.)
 */
typedef NS_ENUM(NSInteger, TX_Enum_MediaType) {

    /// AUTO Type
    MEDIA_TYPE_AUTO = 0,

    /// VOD Type
    MEDIA_TYPE_HLS_VOD = 1,

    /// LIVE Type
    MEDIA_TYPE_HLS_LIVE = 2,

    /// MP4 Type
    MEDIA_TYPE_FILE_VOD = 3,

    /// DASH Type
    MEDIA_TYPE_DASH_VOD = 4,
};

/**
 * The output type of video frame
 */
typedef NS_ENUM(NSInteger, TX_Enum_Video_Pixel_Format) {

    /// Undefined
    TX_VIDEO_PIXEL_FORMAT_NONE = 0,

    /// Direct original video format
    TX_VIDEO_PIXEL_FORMAT_VideoToolbox = 1,

    /// RGBA format (Apple does not recommend using RGBA, please use BGRA format instead)
    TX_VIDEO_PIXEL_FORMAT_RGBA DEPRECATED_ATTRIBUTE = 2,

    /// BGRA format
    TX_VIDEO_PIXEL_FORMAT_BGRA = 3,
};

/**
 * VOD player config
 */
LITEAV_EXPORT @interface TXVodPlayConfig : NSObject

@property(nonatomic, assign) int connectRetryCount;

/// Player connection retry interval: unit second, the minimum value is 3, the maximum value is 30, the default value is 3.
@property(nonatomic, assign) int connectRetryInterval;

/// Timeout time: in seconds, default 10s.
@property NSTimeInterval timeout;

/// The video format of the video render object callback.kCVPixelFormatType_32BGRA、kCVPixelFormatType_420YpCbCr8BiPlanarFullRange、kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange are supported.
@property(nonatomic, assign) OSType playerPixelFormatType DEPRECATED_MSG_ATTRIBUTE("Use videoFrameFormatType instead.");

/// The video format of the video rendering object callback, the default value is TX_VIDEO_PIXEL_FORMAT_NONE
@property(nonatomic, assign) TX_Enum_Video_Pixel_Format videoFrameFormatType;

/// Whether to keep the last frame when stopPlay, the default value is NO.
@property(nonatomic, assign) BOOL keepLastFrameWhenStop;

/// The duration of the data to be loaded in the first buffer, in ms, the default value is 100ms.
@property(nonatomic, assign) int firstStartPlayBufferTime;

/// When buffering (secondary buffering caused by insufficient buffered data, or drag buffering caused by seek), the minimum length of data to be buffered to end the buffering, in ms, the default value is 250ms.
@property(nonatomic, assign) int nextStartPlayBufferTime;

/// Video cache directory, MP4 on demand, HLS valid
///@note The cache directory should be a separate directory, the SDK may clear the files in it.
@property NSString *cacheFolderPath DEPRECATED_MSG_ATTRIBUTE("Use TXPlayerGlobalSetting##setCacheFolderPath instead.");

/// Maximum number of cached files.
@property int maxCacheItems DEPRECATED_MSG_ATTRIBUTE("Use TXPlayerGlobalSetting##setMaxCacheSizeMB instead.");

/// Player type.
@property NSInteger playerType;

/// customize HTTP Headers
@property NSDictionary *headers;

///  Whether to seek accurately, the default is YES. After enabling the precision seek, the seek time is 200ms longer on average
@property BOOL enableAccurateSeek;

/// When playing MP4 files, if set to YES, it will automatically rotate according to the rotation angle in the file. The rotation angle is available in the EVT_VIDEO_CHANGE_ROTATION event. Default YES.
@property BOOL autoRotate;

/// Switch bit rate smoothly. Default NO.
@property BOOL smoothSwitchBitrate;

/// Set the progress callback interval.
/**
 * Set the progress callback interval, in milliseconds. If not set, the SDK will call back once every 500 milliseconds by default.
 */
@property NSTimeInterval progressInterval;

/// Maximum cached size in MB This setting affects playableDuration, the larger the setting, the more cached in advance.
@property float maxBufferSize;

/// Maximum preload size in MB This setting affects playableDuration. This flag affects  the first I Fame time coast
@property float maxPreloadSize;

/// encryption key
@property NSString *overlayKey;

/// encryption Iv
@property NSString *overlayIv;

/// Set MP4 encryption playback mode.
/// MP4_ENCRYPTION_LEVEL_NONE: Playback without encryption.
/// MP4_ENCRYPTION_LEVEL_L1: Online encryption for MP4 playback.
/// MP4_ENCRYPTION_LEVEL_L2: Local encryption for MP4 playback.
@property(nonatomic, assign) TX_Enum_MP4EncryptionLevel encryptedMp4Level;

/// display processing flag
/// set the render display post-processing flag, including super resolution、VR and other functions. To use these functions, you need to set this flag, and it's NO by default
@property(nonatomic, assign) BOOL enableRenderProcess;

/// When Hls has multiple programs, the optimal program is selected according to the set preferredResolution to start broadcasting. PreferredResolution is the product of width and height. The effective value of the configuration is an integer >=-1.
/// The default value is -1. The playback kernel understands that priority should be used. For configuration with lower-level information, the program with the closest arithmetic distance will be matched from the program less than this value. The
/// priority is bitrateIndex > mPreferredBitrate > mPreferredResolution
@property(nonatomic, assign) long preferredResolution;

/// Set media type.
/// Note: For adaptive bit rate playback, the specific type must be specified temporarily. For example, for adaptive playback of HLS live broadcast resources, MEDIA_TYPE_HLS_LIVE type must be passed in
@property(nonatomic, assign) TX_Enum_MediaType mediaType;

/// Set some special configuration that you don't have to know about.
@property NSDictionary *extInfoMap;  // Set some special configuration that you don't have to know about

/// The name of the audio track that is loaded first when starting playback. Supported by the premium version of the player starting from version 12.3.
@property(nonatomic, copy) NSString *preferAudioTrack;

@end
