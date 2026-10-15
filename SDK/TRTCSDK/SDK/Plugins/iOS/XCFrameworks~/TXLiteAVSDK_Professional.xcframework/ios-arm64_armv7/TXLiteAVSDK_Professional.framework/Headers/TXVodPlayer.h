//  Copyright © 2021 Tencent. All rights reserved.

#import <TargetConditionals.h>
#import <Foundation/Foundation.h>
#if TARGET_OS_OSX
#import <AppKit/AppKit.h>
#else
#import <UIKit/UIKit.h>
#endif
#import "TXLivePlayListener.h"
#import "TXVodPlayListener.h"
#import "TXVodPlayConfig.h"
#import "TXVideoCustomProcessDelegate.h"
#import "TXBitrateItem.h"
#import "TXPlayerAuthParams.h"
#import "TXPlayerDrmBuilder.h"
#import "TXLiteAVSymbolExport.h"
#import "TXTrackInfo.h"
#import "TXPlayerSubtitleRenderModel.h"

/////////////////////////////////////////////////////////////////////////////////
//
//                    VOD player interface
//
/////////////////////////////////////////////////////////////////////////////////

LITEAV_EXPORT @interface TXVodPlayer : NSObject

/**
 * Set event delegate
 */
@property(nonatomic, weak) id<TXLivePlayListener> delegate DEPRECATED_MSG_ATTRIBUTE("Use vodDelegate instead.");

/**
 * Set event delegate
 */
@property(nonatomic, weak) id<TXVodPlayListener> vodDelegate;

/**
 * Video rendering callback.
 *
 * both hard solution and soft solution are supported on all platform interfaces.
 */
@property(nonatomic, weak) id<TXVideoCustomProcessDelegate> videoProcessDelegate;

/**
 * Enable hardware acceleration for decoder
 */
@property(nonatomic, assign) BOOL enableHWAcceleration;

/**
 * Player Config
 */
@property(nonatomic, copy) TXVodPlayConfig *config;

/**
 * Auto play the video
 */
@property BOOL isAutoPlay;

/**
 * HLS encrypt token, voddrm.token.TOKEN will be added as prefix for URL
 */
@property(nonatomic, strong) NSString *token;

/**
 * Set view for video rendering
 */
#if TARGET_OS_OSX
- (void)setupVideoWidget:(NSView *)view insertIndex:(unsigned int)idx;
#else
- (void)setupVideoWidget:(UIView *)view insertIndex:(unsigned int)idx;
#endif

/**
 * Remove render view
 */
- (void)removeVideoWidget;

/**
 * Set start time
 */
- (void)setStartTime:(CGFloat)startTime;

/**
 * Start playback from the specified URL, the full platform version of this interface has no parameters
 * @note Starting from version 10.7, the Licence needs to be set through {@link TXLiveBase#setLicence} before it can be played successfully, otherwise the playback will fail (black screen), and it can only be set once globally. Live Licence, UGC
 * Licence, and Player Licence can all be used. If you have not obtained the above Licence, you can [quickly apply for a beta Licence for free](https://cloud.tencent.com/act/event/License) To play, the official licence needs to be
 * [purchased](https://cloud.tencent.com/document/product/881/74588#.E8.B4.AD.E4.B9.B0.E5.B9.B6.E6.96.B0.E5.BB.BA.E6.AD.A3.E5.BC.8F.E7.89.88-license).
 *
 * Start multimedia file playback Note that the full platform version of this interface has no parameters
 * Supported video formats include: mp4, mkv, mov.
 * Supported audio formats include: opus, aac.
 * @note You can call {@link preload} to preload first and then call start, or you can skip preload and call start directly.
 */
- (int)startVodPlay:(NSString *)url;

/**
 * Start a standard Fairplay drm playback with the specified drmBuilder
 *
 * Start a standard Fairplay drm playback with the specified drmBuilder. Note that the drmBuilder is the drm playback information
 */
- (int)startPlayDrm:(TXPlayerDrmBuilder *)drmBuilder;

/**
 * Start play with TXPlayerAuthParams
 * @note Starting from version 10.7, the Licence needs to be set through {@link TXLiveBase#setLicence} before it can be played successfully, otherwise the playback will fail (black screen), and it can only be set once globally. Live Licence, UGC
 * Licence, and Player Licence can all be used. If you have not obtained the above Licence, you can `quickly apply for a beta Licence for free` To play, the official licence needs to be `purchased`.
 */
- (int)startVodPlayWithParams:(TXPlayerAuthParams *)params;

/**
 * Stop play
 */
- (int)stopPlay;

/**
 * Check if video is playing
 */
- (bool)isPlaying;

/**
 * Pause play
 */
- (void)pause;

/**
 * Resume play
 */
- (void)resume;

/**
 * Seek to timestamp of the video
 */
- (int)seek:(float)time;

/**
 * Seek to timestamp of the video
 * Note: This interface is supported starting from version 11.8
 *
 * @param time Video stream time point, unit second (s), accurate to 3 digits after the decimal point
 * @param isAccurateSeek Is it accurate
 *         -- YES: Represents precise Seek, which must find the current time point, which will be more time-consuming.
 *         -- NO：Represents non-accurate Seek, that is, looking for the previous I frame
 */
- (void)seek:(float)time accurateSeek:(BOOL)isAccurateSeek;

/**
 * Seek to PDT time of the video
 */
- (void)seekToPdtTime:(long long)pdtTimeMs;

/**
 * Get current play timestamp
 */
- (float)currentPlaybackTime;

/**
 * Get video duration
 */
- (float)duration;

/**
 * Get playable duration
 */
- (float)playableDuration;

/**
 * Set video render width
 */
- (int)width;

/**
 * Set video render height
 */
- (int)height;

/**
 * Set the orientation of the rendered picture
 *
 * @info Set the clockwise rotation angle of the local image.
 * @param rotation Support TRTCVideoRotation90 、 TRTCVideoRotation180 and TRTCVideoRotation270 default is TRTCVideoRotation0.
 * @note For windowed rendering mode.
 */
- (void)setRenderRotation:(TX_Enum_Type_HomeOrientation)rotation;

/**
 * Set video render fill mode
 *
 * @param mode Fill (the picture may be stretched and cropped) or fit (the picture may have black borders),default: TRTCVideoFillMode_Fit
 * @note For windowed rendering mode.
 */
- (void)setRenderMode:(TX_Enum_Type_RenderMode)renderMode;

/**
 * Mute the audio
 */
- (void)setMute:(BOOL)bEnable;

/**
 * Set the audio volume
 *
 * @param volume Volume level, 100 is the original volume, the range is: [0 ~ 150], the default value is 100.
 */
- (void)setAudioPlayoutVolume:(int)volume;

/**
 * Set the volume normalization, loudness range: -70～0(LUFS). Note: Only effective for the player premium.
 *
 * @param value off is AUDIO_NORMALIZATION_OFF (TXVodPlayConfig.h), on(standard) is AUDIO_NORMALIZATION_STANDARD (TXVodPlayConfig.h)
 */
- (void)setAudioNormalization:(float)value;

/**
 * Snapshot the current video frame to image
 */
#if TARGET_OS_OSX
- (void)snapshot:(void (^)(NSImage *))snapshotCompletionBlock;
#else
- (void)snapshot:(void (^)(UIImage *))snapshotCompletionBlock;
#endif

/**
 * Set play rate
 *
 * @param rate Play speed
 */
- (void)setRate:(float)rate;

/**
 * Return the supported bitrates for master playlist
 */
- (NSArray<TXBitrateItem *> *)supportedBitrates;

/**
 * Return the current bitrate index
 */
- (NSInteger)bitrateIndex;

/**
 * Set playing bitrate index
 */
- (void)setBitrateIndex:(NSInteger)index;

/**
 * Set video render mirror mode
 */
- (void)setMirror:(BOOL)isMirror;

/**
 * Attach the vod player to some TRTCCloud instance
 *
 * @param trtcCloud TRTC instance
 * @note It is used for auxiliary stream push. After binding, the audio playback is taken over by TRTC.
 */
- (void)attachTRTC:(NSObject *)trtcCloud;

/**
 * Detach the vod player to some TRTCCloud instance
 */
- (void)detachTRTC;

/**
 * Publish the video stream to attached TRTCCloud instance
 */
- (void)publishVideo;

/**
 * Publish the audio stream to attached TRTCCloud instance
 */
- (void)publishAudio;

/**
 * Unpublish the video stream to attached TRTCCloud instance
 */
- (void)unpublishVideo;

/**
 * Unpublish the audio stream to attached TRTCCloud instance
 */
- (void)unpublishAudio;

/**
 * Enable loop
 */
@property(nonatomic, assign) BOOL loop;

/**
 * Get key for encrypted play
 */
+ (NSString *)getEncryptedPlayKey:(NSString *)key;

/**
 * ```
 * Whether the seamless switching Picture In Picture function is supported (to determine whether the advanced print-in-picture function can be used). To use the seamless switching Picture In Picture function, the current device needs to support the
 * Picture In Picture function and turn on the automatic Picture In Picture function (Settings-General- Picture-in-picture - Automatically turn on picture-in-picture) and activate the advanced version license
 * ```
 */
+ (BOOL)isSupportPictureInPicture;

/**
 * ```
 * Whether to support automatic switching Picture-In-Picture function ("automatic picture-in-picture" function).To use the automatic picture-in-picture switching function, the current device needs to support the picture-in-picture function, turn on
 * the automatic picture-in-picture function (settings-general-picture-in-picture-automatically turn on picture-in-picture) and open the advanced license permission
 * ```
 */
+ (BOOL)isSupportSeamlessPictureInPicture;

/**
 * ```
 * The seamless switching Picture In Picture function is an advanced picture-in-picture function and requires an advanced license. After integrating the advanced picture-in-picture function and enabling permissions, this interface will be enabled by
 * default and no further settings are required.
 * ```
 *
 * @param enabled Whether the seamless picture-in-picture function is allowed, YES means it is allowed, NO means it is not allowed, the default is NO
 */
+ (void)setPictureInPictureSeamlessEnabled:(BOOL)enabled DEPRECATED_MSG_ATTRIBUTE("Deprecated ");

/**
 * Automatic start of Picture In Picture control switch. Automatic start of Picture In Picture function is an advanced version of Picture In Picture capability and requires opening of the advanced version license
 *
 * @param enabled Whether the automatic picture-in-picture function is allowed, YES means it is allowed, NO means it is not allowed, the default is NO
 */
- (void)setAutoPictureInPictureEnabled:(BOOL)enabled;

/**
 * enter Picture-In-Picture. This method needs to be called after Prepared
 */
- (void)enterPictureInPicture;

/**
 * exit Picture-In-Picture
 */
- (void)exitPictureInPicture;

/**
 * add external subtitles
 *
 * @param url  subtitle address
 * @param name  the name of the subtitle. If you add multiple subtitles, please set the subtitle name to a different name to distinguish it, otherwise it may lead to wrong subtitle selection
 * @param mimeType  the type of subtitle, only supports VTT and SRT format, see TXVodSDKEventDef.h for details
 */
- (void)addSubtitleSource:(NSString *)url name:(NSString *)name mimeType:(TX_VOD_PLAYER_SUBTITLE_MIME_TYPE)mimeType;

/**
 * add external audio track sources
 *
 * @param url  external audio track source address
 * @param name  the name of external audio track source。If you add multiple audio track sources, please set the audio track name to a different name to distinguish it, otherwise it may lead to wrong audio track selection
 */
- (void)addAudioTrackSource:(NSString *)url name:(NSString *)name;

/**
 * select track
 *
 * @param trackIndex   the index of track
 */
- (void)selectTrack:(NSInteger)trackIndex;

/**
 * deselect track
 *
 * @param trackIndex  the index of track
 */
- (void)deselectTrack:(NSInteger)trackIndex;

/**
 * return to list of subtitle track information
 */
- (NSArray<TXTrackInfo *> *)getSubtitleTrackInfo;

/**
 * return the list of audio track information
 */
- (NSArray<TXTrackInfo *> *)getAudioTrackInfo;

/**
 * Set the subtitle style information, you can update the subtitle style before and after playback
 *
 * @param renderModel Subtitle style configuration information {@link TXPlayerSubtitleRenderModel}.
 */
- (void)setSubtitleStyle:(TXPlayerSubtitleRenderModel *)renderModel;

/**
 * Set Extent Option Info
 */
- (void)setExtentOptionInfo:(NSDictionary<NSString *, id> *)extInfo;

/**
 * Set adaptive playback switchable maximum bitrate
 *
 * @param autoMaxBitrate adaptive playback switchable maximum bitrate
 */
- (void)setAutoMaxBitrate:(NSInteger)autoMaxBitrate;

@end
