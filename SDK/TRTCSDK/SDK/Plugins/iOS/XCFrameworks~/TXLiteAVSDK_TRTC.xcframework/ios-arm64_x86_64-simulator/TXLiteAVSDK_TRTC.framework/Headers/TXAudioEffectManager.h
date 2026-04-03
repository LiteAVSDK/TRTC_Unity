/**
 * Copyright (c) 2021 Tencent. All rights reserved.
 * Module: management class for background music, short audio effects, and voice effects
 * Description: sets background music, short audio effects, and voice effects
 */
#import <Foundation/Foundation.h>
#import "TXLiteAVSymbolExport.h"
NS_ASSUME_NONNULL_BEGIN

/////////////////////////////////////////////////////////////////////////////////
//
//                    Definitions of enumerated values related to audio effects
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 1.1 Reverb effects.
 *
 * Reverb effects can be applied to human voice. Based on acoustic algorithms, they can mimic voice in different environments. The following effects are supported currently:
 * 0: original; 1: karaoke; 2: room; 3: hall; 4: low and deep; 5: resonant; 6: metal; 7: husky; 8: ethereal; 9: studio; 10: melodious; 11: studio2;
 */
typedef NS_ENUM(NSInteger, TXVoiceReverbType) {

    /// disable
    TXVoiceReverbType_0 = 0,

    /// KTV
    TXVoiceReverbType_1 = 1,

    /// small room
    TXVoiceReverbType_2 = 2,

    /// great hall
    TXVoiceReverbType_3 = 3,

    /// deep voice
    TXVoiceReverbType_4 = 4,

    /// loud voice
    TXVoiceReverbType_5 = 5,

    /// metallic sound
    TXVoiceReverbType_6 = 6,

    /// magnetic sound
    TXVoiceReverbType_7 = 7,

    /// ethereal
    TXVoiceReverbType_8 = 8,

    /// studio
    TXVoiceReverbType_9 = 9,

    /// melodious
    TXVoiceReverbType_10 = 10,

    /// studio2
    TXVoiceReverbType_11 = 11,

};

/**
 * 1.2 Voice changing effects.
 *
 * Voice changing effects can be applied to human voice. Based on acoustic algorithms, they change the tone of voice. The following effects are supported currently:
 * 0: original; 1: child; 2: little girl; 3: middle-aged man; 4: metal; 5: nasal; 6: foreign accent; 7: trapped beast; 8: otaku; 9: electric; 10: robot; 11: ethereal; 12: pig king; 13: hulk
 */
typedef NS_ENUM(NSInteger, TXVoiceChangeType) {

    /// disable
    TXVoiceChangeType_0 = 0,

    /// naughty kid
    TXVoiceChangeType_1 = 1,

    /// Lolita
    TXVoiceChangeType_2 = 2,

    /// uncle
    TXVoiceChangeType_3 = 3,

    /// heavy metal
    TXVoiceChangeType_4 = 4,

    /// catch cold
    TXVoiceChangeType_5 = 5,

    /// foreign accent
    TXVoiceChangeType_6 = 6,

    /// caged animal trapped beast
    TXVoiceChangeType_7 = 7,

    /// indoorsman
    TXVoiceChangeType_8 = 8,

    /// strong current
    TXVoiceChangeType_9 = 9,

    /// heavy machinery
    TXVoiceChangeType_10 = 10,

    /// intangible
    TXVoiceChangeType_11 = 11,

    /// pig king
    TXVoiceChangeType_12 = 12,

    /// hulk
    TXVoiceChangeType_13 = 13,

};

/////////////////////////////////////////////////////////////////////////////////
//
//                    Background music preload event callback
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * Background music preload progress.
 */
typedef void (^TXMusicPreloadProgressBlock)(NSInteger progress);

/**
 * Background music preload error.
 *
 * @param errorCode -4001: Failed to open the file, such as invalid data found when processing input, ffmpeg protocol not found, etc; -4002: Decoding failure, such as audio file corruption, inaccessible network audio file server, etc; -4003: The
 * number of preloads exceeded the limit，Please call stopPlayMusic first to release the useless preload；-4005: Invalid path, Please check whether the path you passed points to a legal music file；-4006: Invalid URL, Please use a browser to check
 * whether the URL address you passed in can download the desired music file；-4007: No audio stream, Please confirm whether the file you passed is a legal audio file and whether the file is damaged；-4008: Unsupported format, Please confirm whether
 * the file format you passed is a supported file format. The mobile version supports [mp3, aac, m4a, wav, ogg, mp4, mkv], and the desktop version supports [mp3, aac, m4a, wav, mp4, mkv].
 */
typedef void (^TXMusicPreloadErrorBlock)(NSInteger errorCode);

/////////////////////////////////////////////////////////////////////////////////
//
//                    Callback of playing background music
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * Background music started.
 *
 * Called after the background music starts.
 * @param id music ID.
 * @param errCode 0: Start playing successfully; -4001: Failed to open the file, such as invalid data found when processing input, ffmpeg protocol not found, etc; -4005: Invalid path, Please check whether the path you passed points to a legal music
 * file；-4006: Invalid URL, Please use a browser to check whether the URL address you passed in can download the desired music file. If the operating system is iOS or MacOS, please ensure the use of HTTPS links；-4007: No audio stream, Please
 * confirm whether the file you passed is a legal audio file and whether the file is damaged；-4008: Unsupported format, Please confirm whether the file format you passed is a supported file format. The mobile version supports [mp3, aac, m4a, wav,
 * ogg, mp4, mkv], and the desktop version supports [mp3, aac, m4a, wav, mp4, mkv]; -4009: The number of concurrent BGM playbacks has exceeded the limit. This error occurs when more than 10 BGMs are playing simultaneously. Please check the number of
 * concurrent BGM playbacks.
 */
typedef void (^TXAudioMusicStartBlock)(NSInteger errCode);

/**
 * Playback progress of background music.
 */
typedef void (^TXAudioMusicProgressBlock)(NSInteger progressMs, NSInteger durationMs);

/**
 * Background music ended.
 *
 * Called when the background music playback ends or an error occurs.
 * @param id music ID.
 * @param errCode 0: End of play; -4002: Decoding failure, such as audio file corruption, inaccessible network audio file server, etc.
 */
typedef void (^TXAudioMusicCompleteBlock)(NSInteger errCode);

/////////////////////////////////////////////////////////////////////////////////
//
//                    Background music playback information
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * Background music playback information.
 *
 * The information, including playback ID, file path, and loop times, is passed in the {@link startPlayMusic} API.
 * 1. If you play the same music track multiple times, please use the same ID instead of a separate ID for each playback.
 * 2. If you want to play different music tracks at the same time, use different IDs for them.
 * 3. If you use the same ID to play a music track different from the current one, the SDK will stop the current one before playing the new one.
 */
LITEAV_EXPORT @interface TXAudioMusicParam : NSObject

/// `Field description:` music ID
///@note the SDK supports playing multiple music tracks. IDs are used to distinguish different music tracks and control their start, end, volume, etc.
@property(nonatomic) int32_t ID;

/// `Field description:` absolute path of the music file or url.the mp3,aac,m4a,wav supported.
@property(nonatomic, copy) NSString *path;

/// `Field description:` number of times the music track is looped
///`Valid values:`0 or any positive integer. 0 (default) indicates that the music is played once, 1 twice, and so on.
@property(nonatomic) NSInteger loopCount;

/// `Field description:` whether to send the music to remote users
///`Valid values:``$YES$` (default): remote users can hear the music played locally; `$NO$`: only the local user can hear the music.
@property(nonatomic) BOOL publish;

/// `Field description:` whether the music played is a short music track
///`Valid values:``$YES$`: short music track that needs to be looped; `$NO$` (default): normal-length music track
@property(nonatomic) BOOL isShortFile;

/// `Field description:` the point in time in milliseconds for starting music playback
@property(nonatomic) NSInteger startTimeMS;

/// `Field description:` the point in time in milliseconds for ending music playback. 0 indicates that playback continues till the end of the music track.
@property(nonatomic) NSInteger endTimeMS;

@end

LITEAV_EXPORT @interface TXAudioEffectManager : NSObject

/**
 * You cannot create a `TXAudioEffectManager` object.
 * You need to obtain the object using the {@link getAudioEffectManager} API of `TRTCCloud` or `TXLivePush`.
 */
- (instancetype)init NS_UNAVAILABLE;

/////////////////////////////////////////////////////////////////////////////////
//
//                    Voice effect APIs
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 1.1 Enabling in-ear monitoring.
 *
 * After enabling in-ear monitoring, anchors can hear in earphones their own voice captured by the mic. This is designed for singing scenarios.
 * In-ear monitoring cannot be enabled for Bluetooth earphones. This is because Bluetooth earphones have high latency. Please ask anchors to use wired earphones via a UI reminder.
 * Given that not all phones deliver excellent in-ear monitoring effects, we have blocked this feature on some phones.
 * @param enable `$YES$:` enable; `$NO$`: disable
 * @note In-ear monitoring can be enabled only when earphones are used. Please remind anchors to use wired earphones.
 */
- (void)enableVoiceEarMonitor:(BOOL)enable;

/**
 * 1.2 Setting in-ear monitoring volume.
 *
 * This API is used to set the volume of in-ear monitoring.
 * @param volume Volume. Value range: [0, 150]; default: 100
 * @note The volume of the ear monitor is one of the most important factors affecting the user experience. Considering that different users have different sensitivities to volume, it is strongly recommended to provide a ear monitor volume adjustment
 * slider on the UI interface. The recommended adjustment range is between 0 and 150. The gain effect of 100-150 is very helpful for some Android phones with low recording volume.
 */
- (void)setVoiceEarMonitorVolume:(NSInteger)volume;

/**
 * 1.3 Setting voice reverb effects.
 *
 * This API is used to set reverb effects for human voice. For the effects supported, please see {@link TXVoiceReverbType}.
 * @note Effects become invalid after room exit. If you want to use the same effect after you enter the room again, you need to set the effect again using this API.
 */
- (void)setVoiceReverbType:(TXVoiceReverbType)reverbType;

/**
 * 1.4 Setting voice changing effects.
 *
 * This API is used to set voice changing effects. For the effects supported, please see {@link TXVoiceChangeType}.
 * @note Effects become invalid after room exit. If you want to use the same effect after you enter the room again, you need to set the effect again using this API.
 */
- (void)setVoiceChangerType:(TXVoiceChangeType)changerType;

/**
 * 1.5 Setting speech volume.
 *
 * This API is used to set the volume of speech. It is often used together with the music volume setting API {@link setAllMusicVolume} to balance between the volume of music and speech.
 * @param volume Volume. Value range: [0, 150]; default: 100
 * @note If 100 is still not loud enough for you, you can set the volume to up to 150, but there may be side effects.
 */
- (void)setVoiceVolume:(NSInteger)volume;

/**
 * 1.6 Setting speech pitch.
 *
 * This API is used to set the pitch of speech.
 * @param pitch Ptich，Value range: [-1.0f, 1.0f]; default: 0.0f。
 */
- (void)setVoicePitch:(double)pitch;

/////////////////////////////////////////////////////////////////////////////////
//
//                    Background music APIs
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 2.1 Starting background music.
 *
 * You must assign an ID to each music track so that you can start, stop, or set the volume of music tracks by ID.
 * @param musicParam Music parameter
 * @param startBlock Callback of starting music
 * @param progressBlock Callback of playback progress
 * @param completeBlock Callback of ending music
 * @note
 * 1. If you play the same music track multiple times, please use the same ID instead of a separate ID for each playback.
 * 2. If you want to play different music tracks at the same time, use different IDs for them.
 * 3. If you use the same ID to play a music track different from the current one, the SDK will stop the current one before playing the new one.
 */
- (void)startPlayMusic:(TXAudioMusicParam *)musicParam onStart:(TXAudioMusicStartBlock _Nullable)startBlock onProgress:(TXAudioMusicProgressBlock _Nullable)progressBlock onComplete:(TXAudioMusicCompleteBlock _Nullable)completeBlock;

/**
 * 2.2 Stopping background music.
 *
 * @param id    Music ID
 */
- (void)stopPlayMusic:(int32_t)id;

/**
 * 2.3 Pausing background music.
 *
 * @param id    Music ID
 */
- (void)pausePlayMusic:(int32_t)id;

/**
 * 2.4 Resuming background music.
 *
 * @param id    Music ID
 */
- (void)resumePlayMusic:(int32_t)id;

/**
 * 2.5 Setting the local and remote playback volume of background music.
 *
 * This API is used to set the local and remote playback volume of background music.
 * - Local volume: the volume of music heard by anchors
 * - Remote volume: the volume of music heard by audience
 * @param volume Volume. Value range: [0, 150]; default: 60
 * @note If 100 is still not loud enough for you, you can set the volume to up to 150, but there may be side effects.
 */
- (void)setAllMusicVolume:(NSInteger)volume;

/**
 * 2.6 Setting the remote playback volume of a specific music track.
 *
 * This API is used to control the remote playback volume (the volume heard by audience) of a specific music track.
 * @param id     Music ID
 * @param volume Volume. Value range: [0, 150]; default: 60
 * @note If 100 is still not loud enough for you, you can set the volume to up to 150, but there may be side effects.
 */
- (void)setMusicPublishVolume:(int32_t)id volume:(NSInteger)volume;

/**
 * 2.7 Setting the local playback volume of a specific music track.
 *
 * This API is used to control the local playback volume (the volume heard by anchors) of a specific music track.
 * @param id     Music ID
 * @param volume Volume. Value range: [0, 150]. default: 60
 * @note If 100 is still not loud enough for you, you can set the volume to up to 150, but there may be side effects.
 */
- (void)setMusicPlayoutVolume:(int32_t)id volume:(NSInteger)volume;

/**
 * 2.8 Adjusting the pitch of background music.
 *
 * @param id    Music ID
 * @param pitch Pitch. Value range: floating point numbers in the range of [-1, 1]; default: 0.0f
 */
- (void)setMusicPitch:(int32_t)id pitch:(double)pitch;

/**
 * 2.9 Changing the speed of background music.
 *
 * @param id    Music ID
 * @param speedRate Music speed. Value range: floating point numbers in the range of [0.5, 2]; default: 1.0f
 */
- (void)setMusicSpeedRate:(int32_t)id speedRate:(double)speedRate;

/**
 * 2.10 Getting the playback progress (ms) of background music.
 *
 * @param id    Music ID
 * @return The milliseconds that have passed since playback started. -1 indicates failure to get the the playback progress.
 */
- (NSInteger)getMusicCurrentPosInMS:(int32_t)id;

/**
 * 2.11 Getting the total length (ms) of background music.
 *
 * @param path Path of the music file.
 * @return The length of the specified music file is returned. -1 indicates failure to get the length.
 */
- (NSInteger)getMusicDurationInMS:(NSString *)path;

/**
 * 2.12 Setting the playback progress (ms) of background music.
 *
 * @param id    Music ID
 * @param pts Unit: millisecond
 * @note Do not call this API frequently as the music file may be read and written to each time the API is called, which can be time-consuming.
 *       Wait till users finish dragging the progress bar before you call this API.
 *       The progress bar controller on the UI tends to update the progress at a high frequency as users drag the progress bar. This will result in poor user experience unless you limit the frequency.
 */
- (void)seekMusicToPosInMS:(int32_t)id pts:(NSInteger)pts;

/**
 * 2.13 Adjust the speed change effect of the scratch disc.
 *
 * @param id    Music ID
 * @param scratchSpeedRate Scratch disc speed, the default value is 1.0f, the range is: a floating point number between [-12.0 ~ 12.0], the positive/negative speed value indicates the direction is positive/negative, and the absolute value indicates
 * the speed.
 * @note Precondition preloadMusic succeeds.
 */
- (void)setMusicScratchSpeedRate:(int32_t)id speedRate:(double)scratchSpeedRate;

/**
 * 2.15 Preload background music.
 *
 * You must assign an ID to each music track so that you can start, stop, or set the volume of music tracks by ID.
 * @param musicParam Music parameter
 * @note
 * 1. Preload supports up to 2 preloads with different IDs at the same time, and the preload time does not exceed 10 minutes,you need to call {@link stopPlayMusic} API after use, otherwise the memory will not be released.
 * 2. If the music corresponding to the ID is being played, the preloading fails, and {@link stopPlayMusic} must be called first.
 * 3. When the `musicParam` passed to {@link startPlayMusic} is exactly the same, preloading works.
 */
- (void)preloadMusic:(TXAudioMusicParam *)preloadParam onProgress:(TXMusicPreloadProgressBlock _Nullable)progressBlock onError:(TXMusicPreloadErrorBlock _Nullable)errorBlock;

/**
 * 2.16 Get the number of tracks of background music.
 *
 * @param id  Music ID
 */
- (NSInteger)getMusicTrackCount:(int32_t)id;

/**
 * 2.17 Specify the playback track of background music.
 *
 * @param id    Music ID
 * @param index Specify which track to play (the first track is played by default). Value range [0, total number of tracks).
 * @note The total number of tracks can be obtained through the {@link getMusicTrackCount} interface.
 */
- (void)setMusicTrack:(int32_t)id track:(NSInteger)track;

@end
NS_ASSUME_NONNULL_END
