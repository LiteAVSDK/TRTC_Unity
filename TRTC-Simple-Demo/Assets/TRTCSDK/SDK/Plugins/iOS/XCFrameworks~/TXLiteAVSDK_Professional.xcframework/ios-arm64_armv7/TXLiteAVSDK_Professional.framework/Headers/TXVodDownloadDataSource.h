/**
 * Copyright (c) 2021 Tencent. All rights reserved.
 */
#import <Foundation/Foundation.h>
#import "TXLiteAVSymbolExport.h"
#import "TXPlayerAuthParams.h"

/**
 * The definition of the downloaded video
 */
typedef NS_ENUM(NSInteger, TXVodQuality) {

    /// Original
    TXVodQualityOD = 0,

    /// LD
    TXVodQualityFLU,

    /// SD
    TXVodQualitySD,

    /// HD
    TXVodQualityHD,

    /// FHD
    TXVodQualityFHD,

    /// 2K
    TXVodQuality2K,

    /// 4K
    TXVodQuality4K,

    /// LD 240p
    TXVodQuality240P = 240,

    /// LD 360p
    TXVodQuality360P = 360,

    /// SD 480p
    TXVodQuality480P = 480,

    /// SD 540p
    TXVodQuality540P = 540,

    /// HD 720p
    TXVodQuality720P = 720,

    /// FHD 1080p
    TXVodQuality1080p = 1080,
};

/**
 * The download source through `fileid`
 */
LITEAV_EXPORT @interface TXVodDownloadDataSource : NSObject

/// The `fileid` information.This parameter is only used to be compatible with the old version (V2) VOD file download
@property(nonatomic, strong) TXPlayerAuthParams *auth;

/// The download definition, which is the high definition by default. When obtaining download information, this parameter needs to be consistent with the parameter used when downloading videos
@property(nonatomic, assign) TXVodQuality quality;

/// Enter the token if the address is encrypted.
@property(nonatomic, copy) NSString *token;

/// The definition template. If the backend performs transcoding with a custom template, enter the template name here. If both `templateName` and `quality` are set, `templateName` will prevail.
@property(nonatomic, copy) NSString *templateName;

/// The file ID
@property(nonatomic, copy) NSString *fileId;

/// The signature information
@property(nonatomic, copy) NSString *pSign;

/// The application's `appId`, which is required.
@property(nonatomic, assign) int appId;

/// The account name, the default value is `default`
@property(nonatomic, copy) NSString *userName;

/// The HLS EXT-X-KEY encryption and decryption parameters
@property(nonatomic, copy) NSString *overlayKey;

@property(nonatomic, copy) NSString *overlayIv;

@end
