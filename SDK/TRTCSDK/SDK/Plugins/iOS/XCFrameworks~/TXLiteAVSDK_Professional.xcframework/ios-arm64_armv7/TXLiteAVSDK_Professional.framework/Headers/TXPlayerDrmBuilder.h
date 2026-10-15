/**
 * Copyright (c) 2021 Tencent. All rights reserved.
 */
#import <Foundation/Foundation.h>
#import "TXLiteAVSymbolExport.h"

/**
 * The VOD DRM constructor.
 */
LITEAV_EXPORT @interface TXPlayerDrmBuilder : NSObject

/// The certificate provider URL.
@property(nonatomic, strong) NSString *deviceCertificateUrl;

/// The URL of the decryption key.
@property(nonatomic, strong) NSString *keyLicenseUrl;

/// The playback URL.
@property(nonatomic, strong) NSString *playUrl;

/**
 * Initialize DRM object
 *
 * @param certificateUrl the certificate provider URL.
 * @param licenseUrl the URL of the decryption key.
 * @param videoUrl the playback URL.
 * @return return the DRM object
 */
- (instancetype)initWithDeviceCertificateUrl:(NSString *)certificateUrl licenseUrl:(NSString *)licenseUrl videoUrl:(NSString *)videoUrl;

@end
