//  Copyright © 2022 Tencent. All rights reserved.

#import <Foundation/Foundation.h>
#import "TXLiteAVSymbolExport.h"

NS_ASSUME_NONNULL_BEGIN

LITEAV_EXPORT @interface TXPlayerGlobalSetting : NSObject

/**
 * This API is used to set the cache directory of the player engine.
 * After setting, this directory will be first read and written during predownloading and player use.
 *
 * @param  cacheFolder  The path of the cache directory. nil indicates to disable caching.
 */
+ (void)setCacheFolderPath:(NSString *)cacheFolder;

/**
 * This API is used to get the cache directory of the player engine.
 *
 * @return  The cache directory path
 */
+ (NSString *)cacheFolderPath;

/**
 * This API is used to the maximum cache size of the player engine.
 * After setting, the backend will clear files in the cache directory automatically according to the set value.
 *
 * @param maxCacheSizeMB The maximum cache size in MB
 */
+ (void)setMaxCacheSize:(NSInteger)maxCacheSizeMB;

/**
 * This API is used to get the configured maximum cache size of the player engine.
 *
 * @return  The maximum cache size
 */
+ (NSInteger)maxCacheSize;

+ (id)getOptions:(NSNumber *)featureId;

/**
 * Enable flexible license verification for the player. After enabling, the first two license verification attempts during player startup will be automatically passed.
 *
 * @param value  --YES: Enable flexible validation. --NO: Disable flexible validation.
 */
+ (void)setLicenseFlexibleValid:(BOOL)value;

/**
 * This API is used to set Tencent Cloud PlayCGI Host Address List.
 *
 * @param hosts The host address list to be set, such as "playvideo.qcloud.com". When initiating a PlayCGI request, the passed-in hosts addresses are used in sequence.
 *              If a request fails on a certain host, it will automatically switch to the next host and retry the request.
 */
+ (void)setPlayCGIHosts:(NSArray<NSString *> *)hosts;

@end

NS_ASSUME_NONNULL_END
