//  Copyright © 2022 Tencent. All rights reserved.

#import <Foundation/Foundation.h>
#import "TXLiteAVSymbolExport.h"
#import "TXPlayerAuthParams.h"

NS_ASSUME_NONNULL_BEGIN

@protocol TXVodPreloadManagerDelegate <NSObject>

@optional

/**
 * Start the download (this method is called back after the chain change is successful and before the download is started)
 *
 * @param taskID The download task ID
 * @param fileId The fileId of the downloaded video. When caching in URL mode, this parameter is nil
 * @param url The download task URL
 * @param param Additional parameters
 */
- (void)onStart:(int)taskID fileId:(NSString *)fileId url:(NSString *)url param:(NSDictionary *)param;

/**
 * The callback for download completion.
 *
 * @param taskID The download task ID
 * @param url The download task URL
 */
- (void)onComplete:(int)taskID url:(NSString *)url;

/**
 * The callback for download error.
 *
 * @param taskID The download task ID
 * @param url The download task URL
 * @param error The error message of the download failure
 */
- (void)onError:(int)taskID url:(NSString *)url error:(NSError *)error;

@end

LITEAV_EXPORT @interface TXVodPreloadManager : NSObject

/**
 * This API is used to get the video predownloading singleton object.
 */
+ (instancetype)sharedManager;

/**
 * This API is used to start predownloading.
 * 【attention】Set the player engine cache directory [TXPlayerGlobalSetting  setCacheFolderPath: ] and cache size [ TXPlayerGlobalSetting setMaxCacheSizeMB:] before starting predownloading. Such settings are global and must be consistent with those
 * of the player; otherwise, the player cache will become invalid.
 *
 * @param requestURL  The predownload URL
 * @param preloadSizeMB    The size of the data to be predownloaded in MB
 * @param preferredResolution  The preferred resolution of `long` type. Sample value: TXVodPlayConfig.VIDEO_RESOLUTION_720X1280. If multi-resolution is not supported or not needed, pass in `-1`.
 * @param delegate/listener The callback
 * @return The task ID, which can be used to stop predownloading by calling [ TXVodPreloadManager stopPreload ].
 */
- (int)startPreload:(NSString *)requestURL preloadSize:(float)preloadSizeMB preferredResolution:(long)preferredResolution delegate:(id<TXVodPreloadManagerDelegate>)delegate;

/**
 * Start pre-download (this method blocks the calling thread)
 * 【attention】Set the player engine cache directory [TXPlayerGlobalSetting  setCacheFolderPath: ] and cache size [ TXPlayerGlobalSetting setMaxCacheSizeMB:] before starting predownloading. Such settings are global and must be consistent with those
 * of the player; otherwise, the player cache will become invalid.
 *
 * @param params   Pre-downloaded video data
 * @param preloadSizeMB   The size of the data to be predownloaded in MB
 * @param preferredResolution  The preferred resolution of `long` type. Sample value: TXVodPlayConfig.VIDEO_RESOLUTION_720X1280. If multi-resolution is not supported or not needed, pass in `-1`.
 * @param delegate  listener The callback
 * @return The task ID, which can be used to stop predownloading by calling [ TXVodPreloadManager stopPreload ].
 */
- (int)startPreloadWithModel:(TXPlayerAuthParams *)params preloadSize:(float)preloadSizeMB preferredResolution:(long)preferredResolution delegate:(id<TXVodPreloadManagerDelegate>)delegate;

/**
 *  This API is used to stop predownloading.
 *
 * @param taskID The task ID, which is obtained from the returned value of {@link TXVodPreloadManager#startPreload}.
 */
- (void)stopPreload:(int)taskID;

@end

NS_ASSUME_NONNULL_END
