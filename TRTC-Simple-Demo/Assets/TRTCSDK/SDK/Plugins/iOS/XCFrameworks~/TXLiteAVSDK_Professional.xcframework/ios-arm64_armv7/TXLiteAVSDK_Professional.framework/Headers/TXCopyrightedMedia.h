/**
 * Copyright (c) 2023 Tencent. All rights reserved.
 * Module: ysd copyrighted music
 * Function: Used to download copyrighted music data
 * This function is not packaged in the SDK by default. If you want to use the functions in this file, please contact Tencent to provide a separate SDK.
 */
#import <Foundation/Foundation.h>
#import "TXLiteAVSymbolExport.h"
@protocol ITXCSongScore;

/**
 * The authentication parameters of YSD
 */
LITEAV_EXPORT @interface TXCopyrightedMediaYSDAuthParams : NSObject

/// User ID registered in YSD
@property(nonatomic, copy) NSString *userId;

/// User Token
@property(nonatomic, copy) NSString *userToken;

/// Device ID
@property(nonatomic, copy) NSString *deviceId;

/// pID registered in YSD
@property(nonatomic, copy) NSString *appId;

/// Charge mode of YSD, false means it's charged by month
@property(nonatomic, assign) BOOL isChargedOnce;

/// pKey provided from YSD
@property(nonatomic, copy) NSString *appKey;

@end

/**
 * Copyrighted music enumeration value definition
 */
typedef NS_ENUM(NSInteger, TXCopyrightedError) {

    /// success
    ERR_NONE = 0,

    /// User cancel
    ERR_CANCEL = -1,

    /// token expired
    ERR_TOKEN_OVERDUE = -2,

    /// network error
    ERR_NET_FAILED = -3,

    /// Internal error
    ERR_INNER_ERROR = -4,

    /// License verification fails
    ERR_LICENSE_FAILED = -5,

    /// Music downloading
    ERR_MUSIC_IS_DOWNLOADING = -6,

    /// Accompaniment file does not exist
    ERR_ACCOMPANIMENT_NOT_EXIST = -7,

    /// Original song file does not exist
    ERR_ORIGIN_NOT_EXIST = -8,

    /// Lyrics file does not exist
    ERR_LYRIC_NOT_EXIST = -9,

    /// pitch file does not exist
    ERR_MIDI_NOT_EXIST = -10,

    /// prepare score module failed.
    ERR_PREPARE_FAILED = -11,

    /// call score interface, but not prepare.
    ERR_NOT_PREPARE = -12,

    /// origin climax segment not exist.
    ERR_ORIGIN_CLIMAX_SEGMENT_NOT_EXIST = -13,

    /// accompaniment climax segment not exist.
    ERR_ACCOMPANIMENT_CLIMAX_SEGMENT_NOT_EXIST = -14,

    /// climax segment time stamp is not exist.
    ERR_CLIMAX_SEGMENT_TIME_RANGE_NOT_EXIST = -15,

};

/**
 * segment time struct
 */
LITEAV_EXPORT @interface TXClimaxTimeRange : NSObject

/// start time
@property(nonatomic, assign) int startTime;

/// end time
@property(nonatomic, assign) int endTime;

@end

@protocol ITXMusicPreloadCallback <NSObject>
@optional

/**
 * Copyrighted music starts download callback
 */
- (void)onPreloadStart:(NSString *)musicId bitrateDefinition:(NSString *)bitrateDefinition;

/**
 * Copyrighted music download progress callback
 */
- (void)onPreloadProgress:(NSString *)musicId bitrateDefinition:(NSString *)bitrateDefinition progress:(float)progress;

/**
 * Copyrighted music download complete callback
 */
- (void)onPreloadComplete:(NSString *)musicId bitrateDefinition:(NSString *)bitrateDefinition errorCode:(int)errorCode msg:(NSString *)msg;

@end

LITEAV_EXPORT @interface TXCopyrightedMedia : NSObject

/**
 * Get Instance
 */
+ (instancetype)instance;

/**
 * Destroy Instance
 */
+ (void)destroy;

/**
 * 设置 license
 *
 * @param key
 * @param licenseUrl
 */
- (void)setLicense:(NSString *)licenseUrl key:(NSString *)key;

/**
 * Set up YSD authentication parameters
 *
 * @param TXCopyrightedMediaYSDAuthParams 音速达鉴权信息
 */
- (void)setYSDAuthParams:(TXCopyrightedMediaYSDAuthParams *)params;

/**
 * Preload YSD music resources
 *
 * @param musicId YSD music ID
 * @param bitrateDefinition Bit rate, pass null as the default audio bit rate, the general format is: audio/mi:
 * 32,audio/lo: 64,audio/hi: 128
 */
- (void)preloadMusic:(NSString *)musicId bitrateDefinition:(NSString *)bitrateDefinition;

/**
 * Generate music URI
 *
 * App Client Called during playback, passed to trtc for playback. correspondence with preloadMusic
 * @param musicId music Id
 * @param bgmType 0：original singer，1：accompaniment  2:  lyrics  3:  pitch file
 * @param bitrateDefinition Bitrate, pass nil to change the audio default bit rate
 */
- (NSString *)genMusicURI:(NSString *)musicId bgmType:(int)bgmType bitrateDefinition:(NSString *)bitrateDefinition;

/**
 * set music preload callback
 *
 * @param callback preload end object
 */
- (void)setMusicPreloadCallback:(id<ITXMusicPreloadCallback>)callback;

/**
 * Preload music data.
 *
 * @param musicId music Id
 * @param playToken play Token
 * @param bitrateDefinition Bit rate, pass nil as the default audio bit rate, the general format is: audio/mi:
 * 32,audio/lo: 64,audio/hi: 128
 * @param callback callback object
 */
- (void)preloadMusic:(NSString *)musicId bitrateDefinition:(NSString *)bitrateDefinition playToken:(NSString *)playToken;

/**
 * Preload music high light segment data.
 *
 * @param musicId music Id
 * @param playToken play Token
 * @param bitrateDefinition Bit rate, pass nil as the default audio bit rate, the general format is: audio/mi:
 * 32,audio/lo: 64,audio/hi: 128
 * @param callback callback object
 */
- (void)preloadClimaxSegment:(NSString *)musicId bitrateDefinition:(NSString *)bitrateDefinition playToken:(NSString *)playToken;

/**
 * Preload pitch and lyric file.
 *
 * @param musicId music Id
 * @param playToken play Token
 * @param bitrateDefinition Bit rate, pass nil as the default audio bit rate, the general format is: audio/mi:
 * 32,audio/lo: 64,audio/hi: 128
 * @param callback callback object
 */
- (void)preloadPitchAndLyricFile:(NSString *)musicId bitrateDefinition:(NSString *)bitrateDefinition playToken:(NSString *)playToken;

/**
 * Get the start and end time of the climax segment.
 *
 * @param musicId music Id
 * @param bitrateDefinition Bit rate, pass nil as the default audio bit rate, the general format is: audio/mi:
 * 32,audio/lo: 64,audio/hi: 128
 * @param bgmType 4: origin climax segment. 5: accompaniment climax segment
 * Generally, the climax clips downloaded are relatively short. If you use the climax clips for scoring, you need to seek the lyrics file and the scoring file to the corresponding positions.
 * For example, the climax of an original song file starts at 1800ms to 2800ms. Then the two values ​​returned at this time are 1800 and 2800.
 * At this time, when scoring starts, you can seek the scoring and lyrics files to the 1800 position. When the playback reaches the 2800 position, the scoring can be stopped.
 */
- (TXClimaxTimeRange *)getClimaxSegmentTimeRange:(NSString *)musicId bgmType:(int)bgmType bitrateDefinition:(NSString *)bitrateDefinition;

/**
 * cancel preload music data.
 *
 * @param musicId music id
 * @param bitrateDefinition Bit rate, pass nil as the default audio bit rate
 */
- (void)cancelPreloadMusic:(NSString *)musicId bitrateDefinition:(NSString *)bitrateDefinition;

/**
 * Detect if music data has been preloaded
 *
 * @param musicId music id
 * @param bitrateDefinition Bit rate, pass nil as the default audio bit rate
 */
- (BOOL)isMusicPreloaded:(NSString *)musicId bitrateDefinition:(NSString *)bitrateDefinition;

/**
 * clear cache
 */
- (void)clearMusicCache;

/**
 * clear cache by music id.
 *
 * @param musicId music id
 * @param bitrateDefinition Bit rate, pass nil as the default audio bit rate
 */
- (void)clearMusicCache:(NSString *)musicId bitrateDefinition:(NSString *)bitrateDefinition;

/**
 * Set the maximum number of song caches, the default is 100
 *
 * @param maxCount maximum number of songs
 */
- (void)setMusicCacheMaxCount:(int)maxCount;

/**
 * Create song score instance
 *
 * @param sampleRate    sample rate
 * @param channel       channel
 * @param playToken     play token
 * @param noteFilePath  not file path
 * @param lyricFilePath lyric file path
 */
- (id<ITXCSongScore>)createSongScore:(NSString *)musicId sampleRate:(int)sampleRate channel:(int)channel playToken:(NSString *)playToken noteFilePath:(NSString *)noteFilePath lyricFilePath:(NSString *)lyricFilePath;

@end

/**
 * Pitch data struct
 */
LITEAV_EXPORT @interface TXSongScoreNoteItem : NSObject

/// start time
@property(nonatomic, assign) int startTime;

/// duration
@property(nonatomic, assign) int duration;

/// pitch
@property(nonatomic, assign) int noteHeight;

/// end time
@property(nonatomic, assign) int endTime;

@end

@protocol TXCSongScoreDelegate <NSObject>
@optional

/**
 * Output the score of each lyric
 *
 * @param currentScore  score for this sentence
 * @param totalScore    total score
 * @param curIndex      lyric index
 */
- (void)onMIDISCoreUpdate:(NSString *)musicId currentScore:(int)currentScore totalScore:(int)totalScore curIndex:(int)curIndex;

/**
 * Outputs real-time pitch hit.
 *
 * @param isHit         is hit
 * @param timeStamp     current time
 * @param pitch         The user's pitch in the note time range
 *   (The value can be compared with the note pitch, -1 means it is not in the note time range,
 *   greater than -1 means the user pitch)
 * @param viewValue     user's real-time pitch
 */
- (void)onMIDIGroveAndHint:(NSString *)musicId timeStamp:(double)timeStamp isHit:(BOOL)isHit pitch:(float)pitch viewValue:(int)viewValue;

/**
 * Score result callback
 *
 * @param scoreArray    A collection of scores for each lyric
 * @param totalScore    total score
 */
- (void)onMIDIScoreFinish:(NSString *)musicId scoreArray:(NSArray *)scoreArray totalScore:(int)totalScore;

/**
 * prepared callback
 *
 * Indicates the scoring module is ready and can call process interface
 */
- (void)onMIDIScorePrepared:(NSString *)musicId;

/**
 * Error callback
 *
 * @param errCode   {@link TXCopyrightedError}
 * @param errMsg    error message
 */
- (void)onMIDIScoreError:(NSString *)musicId errCode:(int)errCode msg:(NSString *)msg;

@end

@protocol ITXCSongScore <NSObject>

/**
 * Set callback
 *
 * @param callback song score callback
 */
- (void)setDelegate:(id<TXCSongScoreDelegate>)delegate;

/**
 * Init Song score instance
 *
 * success {@link onMIDIScorePrepared} callback
 * fail {@link onMIDIScoreError} callback
 */
- (void)prepare;

/**
 * Stop song score
 */
- (void)finish;

/**
 * destroy
 */
- (void)destroy;

/**
 * Process captured voice pcm data
 *
 * @param pcmData       pcm data
 * @param length        pcm data size
 * @param timeStamp     time stamp
 */
- (void)process:(char *)buffer length:(int)length timeStamp:(double)timeStamp;

/**
 * set key
 *
 * @param shiftKey key
 */
- (void)setKeyShift:(NSInteger)shiftValue;

/**
 * Calculate total score
 *
 * @return total score
 */
- (int)calculateTotalScore;

/**
 * Grove data
 *
 * @param note_item_array Grove data buffer
 * @param array_size Grove data size
 * @return ScoreNoteItem count
 */
- (NSArray<TXSongScoreNoteItem *> *)getAllGrove;

@end
