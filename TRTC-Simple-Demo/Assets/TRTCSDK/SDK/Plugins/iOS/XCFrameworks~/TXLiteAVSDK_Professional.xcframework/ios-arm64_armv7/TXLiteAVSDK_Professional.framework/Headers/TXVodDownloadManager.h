/**
 * Copyright (c) 2021 Tencent. All rights reserved.
 * Author: ianyanzhang
 */
#import <Foundation/Foundation.h>
#import "TXPlayerAuthParams.h"
#import "TXLiteAVSymbolExport.h"
#import "TXPlayerDrmBuilder.h"
#import "TXVodDownloadDataSource.h"
#import "TXVodDownloadMediaInfo.h"

/**
 * The download error code
 */
typedef NS_ENUM(NSInteger, TXDownloadError) {

    TXDownloadSuccess = 0,

    /// Failed to authenticate the `fileid`.
    TXDownloadAuthFaild = -5001,

    /// The file with the specified resolution does not exist.
    TXDownloadNoFile = -5003,

    /// The format is not supported.
    TXDownloadFormatError = -5004,

    /// The network was disconnected.
    TXDownloadDisconnet = -5005,

    /// Failed to get the HLS decryption key.
    TXDownloadHlsKeyError = -5006,

    /// Failed to access the download directory.
    TXDownloadPathError = -5007,

    /// The authentication information fails, such as the signature expires or the request was invalid
    TXDownload403Forbidden = -5008,
};

@protocol TXVodDownloadDelegate <NSObject>

/**
 * Download started.
 */
- (void)onDownloadStart:(TXVodDownloadMediaInfo *)mediaInfo;

/**
 * The download progress
 */
- (void)onDownloadProgress:(TXVodDownloadMediaInfo *)mediaInfo;

/**
 * Download stopped.
 */
- (void)onDownloadStop:(TXVodDownloadMediaInfo *)mediaInfo;

/**
 * Download was completed.
 */
- (void)onDownloadFinish:(TXVodDownloadMediaInfo *)mediaInfo;

/**
 * Download error
 */
- (void)onDownloadError:(TXVodDownloadMediaInfo *)mediaInfo errorCode:(TXDownloadError)code errorMsg:(NSString *)msg;

/**
 * Send the decryption key to the player for verification if the HLS file to be downloaded is encrypted.
 *
 * @param mediaInfo The download object
 * @param url The URL
 * @param data The server response
 * @return 0：The decryption key is correct, and file download continues; otherwise, a download error (the SDK failed to get the decryption key) will be reported.
 */
- (int)hlsKeyVerify:(TXVodDownloadMediaInfo *)mediaInfo url:(NSString *)url data:(NSData *)data;

@end

LITEAV_EXPORT @interface TXVodDownloadManager : NSObject

/**
 * The download task callback
 */
@property(nonatomic, weak) id<TXVodDownloadDelegate> delegate;

/**
 * Set the httpHeader
 */
@property(nonatomic, strong) NSDictionary *headers;

/**
 * Whether to support private encryption mode (set to NO when configured as a system player, set to YES for self-developed players), the default setting is YES
 */
@property(nonatomic, assign) BOOL supportPrivateEncryptMode;

/**
 * The global singleton API
 */
+ (TXVodDownloadManager *)shareInstance;

/**
 * Set the root directory for downloaded files
 *
 * @discussion The directory set via 'TXPlayerGlobalSetting #setCacheFolderPath' takes precedence over the setting here
 * @param path The directory path. If it doesn't exist, it will be created automatically.
 * @warning This parameter must be configured before download starts; otherwise, download will fail.
 */
- (void)setDownloadPath:(NSString *)path;

/**
 * The downloaded file
 *
 * @param source The download source
 * @return The download object will be returned if the request succeeds; otherwise, `nil` will be returned.
 */
- (TXVodDownloadMediaInfo *)startDownload:(TXVodDownloadDataSource *)source;

/**
 * Download a file
 *
 * @param username  Account name, optional parameter,  if not passed, the default is "default"
 * @param url Download address, a required parameter, otherwise the download will fail
 * @return The download object will be returned if the request succeeds; otherwise, `nil` will be returned.
 */
- (TXVodDownloadMediaInfo *)startDownload:(NSString *)username url:(NSString *)url;

/**
 * Download a file
 *
 * @param url  Download address, a required parameter, otherwise the download will fail
 * @param resolution  Preference resolution, multi-definition url is a mandatory parameter, and the value is width x height of preference resolution (for example, 720p is passed in 921600=1280*720), single-definition is passed in -1
 * @param username  Account name, optional parameter, if not passed, the default is "default"
 * @return The download object will be returned if the request succeeds; otherwise, `nil` will be returned.
 */
- (TXVodDownloadMediaInfo *)startDownloadUrl:(NSString *)url resolution:(long)resolution userName:(NSString *)username;

/**
 * Download a file
 *
 * @param drmBuilder Drm download object, refer to TXPlayerDrmBuilder.h
 * @param resolution Preference resolution, multi-definition url is a mandatory parameter, and the value is width x height of preference resolution (for example, 720p is passed in 921600=1280*720), single-definition is passed in -1
 * @param username Account name, optional parameter,  if not passed, the default is "default"
 * @return The download object will be returned if the request succeeds; otherwise, `nil` will be returned.
 */
- (TXVodDownloadMediaInfo *)startDownloadDrm:(TXPlayerDrmBuilder *)drmBuilder resolution:(long)resolution userName:(NSString *)username;

/**
 * Stop download
 *
 * @param media The object for which download stopped
 */
- (void)stopDownload:(TXVodDownloadMediaInfo *)media;

/**
 * Delete the file generated by download.
 *
 * @param playPath the path of the object to be deleted. This parameter can be obtained through the object property of TXVodDownloadMediaInfo
 * @return `NO` will be returned if the file is being downloaded and cannot be deleted.
 */
- (BOOL)deleteDownloadFile:(NSString *)playPath;

/**
 * Delete the download information.
 *
 * @param downloadMediaInfo downloadMediaInfo
 * @return `NO` will be returned if the file is being downloaded and cannot be deleted.
 */
- (BOOL)deleteDownloadMediaInfo:(TXVodDownloadMediaInfo *)downloadMediaInfo;

/**
 * Get the download list. To obtain download information, call this interface to ensure that the download task parameters have been created before via startDownload, startDownloadUrl or startDownloadDrm.
 *
 * @return the list of download media info
 */
- (NSArray<TXVodDownloadMediaInfo *> *)getDownloadMediaInfoList;

/**
 * Get the download information.
 *
 * @param media media
 * @return The download object will be returned if the request succeeds; otherwise, `nil` will be returned.
 */
- (TXVodDownloadMediaInfo *)getDownloadMediaInfo:(TXVodDownloadMediaInfo *)media DEPRECATED_MSG_ATTRIBUTE("No longer supported, use getDownloadMediaInfo##fileId##qualityId##userName or getDownloadMediaInfo##resolution##userName instead.");

/**
 * Get the download information. To obtain download information, call this interface to ensure that the download task parameters have been created before via startDownload, startDownloadUrl or startDownloadDrm.
 *
 * @param appId appId
 * @param fileId fileId
 * @param qualityId Video quality Id{ constant value defined by TXVodDownloadDataSource#TXVodQuality}
 * @param username  Account name, optional parameter,  if not passed, the default is "default"
 * @return The download object will be returned if the request succeeds; otherwise, `nil` will be returned.
 */
- (TXVodDownloadMediaInfo *)getDownloadMediaInfo:(int)appId fileId:(NSString *)fileId qualityId:(int)qualityId userName:(NSString *)userName;

/**
 * Get the download information. To obtain download information, call this interface to ensure that the download task parameters have been created before via startDownload, startDownloadUrl or startDownloadDrm.
 *
 * @param url  Download address, a required parameter, otherwise the download will fail
 * @param preferredResolution Must be the same as the preferred definition value passed in during downloading, if not passed in during downloading, pass in "-1" here
 * @param userName It must be consistent with the account name passed in when downloading. If it is not passed in when downloading, pass in an empty string here is ""
 * @return The download object will be returned if the request succeeds; otherwise, `nil` will be returned.
 */
- (TXVodDownloadMediaInfo *)getDownloadMediaInfo:(NSString *)url resolution:(long)preferredResolution userName:(NSString *)userName;

/**
 * Get the `overlayKey` and `overlayIv` for HLS EXT-X-KEY encryption and decryption.
 *
 * @param appId appId
 * @param userName Account name, it must be consistent with the account name passed in when downloading
 * @param fileId fileId
 * @param qualityId Video quality Id{ constant value defined by @link TXVodQuality}
 */
- (NSString *)getOverlayKeyIv:(int)appId userName:(NSString *)userName fileId:(NSString *)fileId qualityId:(int)qualityId DEPRECATED_MSG_ATTRIBUTE("No longer supported");

/**
 * Perform encryption
 *
 * @param originHexStr originHexStr
 */
+ (NSString *)encryptHexStringHls:(NSString *)originHexStr;

@end
