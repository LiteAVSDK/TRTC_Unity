/**
 * Copyright (c) 2021 Tencent. All rights reserved.
 * Module:   V2TXLivePremier @ TXLiteAVSDK
 * Function: V2TXLive High-level interface
 */
#import "V2TXLiveDef.h"
#import "TXLiteAVSymbolExport.h"
NS_ASSUME_NONNULL_BEGIN

/////////////////////////////////////////////////////////////////////////////////
//
//                      V2TXLive High-level interface
//
/////////////////////////////////////////////////////////////////////////////////

@protocol V2TXLivePremierObserver;
@protocol V2TXLivePremier <NSObject>

/**
 * Get the SDK version number
 */
+ (NSString *)getSDKVersionStr;

/**
 * Set V2TXLivePremier callback interface
 */
+ (void)setObserver:(id<V2TXLivePremierObserver>)observer;

/**
 * Set Log configuration information
 */
+ (V2TXLiveCode)setLogConfig:(V2TXLiveLogConfig *)config;

/**
 * Set up SDK access environment
 *
 * @note If your application has no special requirements, please do not call this interface for setting.
 * @param env currently supports two parameters "default" and "GDPR".
 *        - default: In the default environment, the SDK will find the best access point in the world for access.
 *        - GDPR: All audio and video data and quality statistics will not pass through servers in mainland China.
 */
+ (V2TXLiveCode)setEnvironment:(const char *)env;

/**
 * Set SDK authorization license
 *
 * Try and Purchase a License: https://intl.cloud.tencent.com/document/product/1071/38546.
 * @param url the url of licence.
 * @param key the key of licence.
 */
#if TARGET_OS_IPHONE
+ (void)setLicence:(NSString *)url key:(NSString *)key;
#endif

/**
 * Set SDK socks5 proxy config
 *
 * @param host socks5 proxy host.
 * @param port socks5 proxy port.
 * @param username socks5 proxy username.
 * @param password socks5 proxy password.
 * @param config protocol configured with socks5 proxy.
 */
+ (V2TXLiveCode)setSocks5Proxy:(NSString *)host port:(NSInteger)port username:(NSString *)username password:(NSString *)password config:(V2TXLiveSocks5ProxyConfig *)config;

/**
 * Enables/Disables audio capture callback
 *
 * @param enable `YES`: enable; `NO` (**default**): disable.
 * @param format audio frame format.
 * @note This API works only if you call it before {@link startPush}.
 */
+ (V2TXLiveCode)enableAudioCaptureObserver:(BOOL)enable format:(V2TXLiveAudioFrameObserverFormat *)format;

/**
 * Enables/Disables audio playout callback
 *
 * @param enable `YES`: enable; `NO` (**default**): disable.
 * @param format audio frame format.
 */
+ (V2TXLiveCode)enableAudioPlayoutObserver:(BOOL)enable format:(V2TXLiveAudioFrameObserverFormat *)format;

/**
 * Enables/Disables in-ear monitoring callback
 *
 * @param enable `YES`: enable; `NO` (**default**): disable.
 */
+ (V2TXLiveCode)enableVoiceEarMonitorObserver:(BOOL)enable;

/**
 * Set user id
 *
 * @param userId User/device id maintained by the service side itself.
 */
+ (void)setUserId:(NSString *)userId;

/**
 * Call experimental APIs
 *
 * @param jsonStr JSON string describing interface and parameters.
 * @return Return code {@link V2TXLiveCode}.
 *         - V2TXLIVE_OK: successful.
 *         - V2TXLIVE_ERROR_INVALID_PARAMETER: operation failed because of illegal parameter.
 */
+ (V2TXLiveCode)callExperimentalAPI:(NSString *)jsonStr;

@end

/////////////////////////////////////////////////////////////////////////////////
//
//                      V2TXLive Advanced callback interface
//
/////////////////////////////////////////////////////////////////////////////////

@protocol V2TXLivePremierObserver <NSObject>
@optional

/**
 * Custom Log output callback interface
 */
- (void)onLog:(V2TXLiveLogLevel)level log:(NSString *)log;

/**
 * setLicence result callback interface
 *
 * @param result the result of setLicence interface, 0 succeeds, negative number fails.
 * @param reason the reason for failure.
 */
- (void)onLicenceLoaded:(int)result Reason:(NSString *)reason;

/**
 * Raw audio data captured locally
 *
 * @param frame Audio frames in PCM format.
 * @note
 * 1. Please avoid time-consuming operations in this callback function. The SDK processes an audio frame every 20 ms, so if your operation takes more than 20 ms, it will cause audio exceptions.
 * 2. The audio data returned via this callback can be read and modified, but please keep the duration of your operation short.
 * 3. The audio data returned via this callback **does not include** pre-processing effects like background music, audio effects, or reverb, and therefore has a very short delay.
 */
- (void)onCaptureAudioFrame:(V2TXLiveAudioFrame *)frame;

/**
 * Data mixed from each channel before being submitted to the system for playback
 *
 * After you configure the callback of custom audio processing, the SDK will return to you via this callback the data (PCM format) mixed from each channel before it is submitted to the system for playback.
 * - The audio data returned via this callback is in PCM format and has a fixed frame length (time) of 0.02s.
 * - The formula to convert a frame length in seconds to one in bytes is **sample rate * frame length in seconds * number of sound channels * audio bit depth**.
 * - Assume that the audio is recorded on a single channel with a sample rate of 48,000 Hz and audio bit depth of 16 bits, which are the default settings of SDK. The frame length in bytes will be **48000 * 0.02s * 1 * 16 bits = 15360 bits = 1920
 * bytes**.
 * @param frame Audio frames in PCM format.
 * @note
 * 1. Please avoid time-consuming operations in this callback function. The SDK processes an audio frame every 20 ms, so if your operation takes more than 20 ms, it will cause audio exceptions.
 * 2. The audio data returned via this callback can be read and modified, but please keep the duration of your operation short.
 * 3. The audio data returned via this callback is the audio data mixed from each channel before it is played. It does not include the in-ear monitoring data.
 */
- (void)onPlayoutAudioFrame:(V2TXLiveAudioFrame *)frame;

/**
 * In-ear monitoring data
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
- (void)onVoiceEarMonitorAudioFrame:(V2TXLiveAudioFrame *)frame;

@end

LITEAV_EXPORT @interface V2TXLivePremier : NSObject<V2TXLivePremier>

@end

NS_ASSUME_NONNULL_END
