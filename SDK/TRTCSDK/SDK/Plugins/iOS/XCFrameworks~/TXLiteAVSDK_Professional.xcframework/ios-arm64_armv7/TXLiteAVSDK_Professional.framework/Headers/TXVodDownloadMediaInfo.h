/**
 * Copyright (c) 2021 Tencent. All rights reserved.
 */
#import <Foundation/Foundation.h>
#import "TXLiteAVSymbolExport.h"
#import "TXVodDownloadDataSource.h"

/**
 * Download status
 */
typedef NS_ENUM(NSInteger, TXVodDownloadMediaInfoState) {

    /// Initialization state
    TXVodDownloadMediaInfoStateInit = 0,

    /// Start state
    TXVodDownloadMediaInfoStateStart = 1,

    /// Stop state
    TXVodDownloadMediaInfoStateStop = 2,

    /// Error state
    TXVodDownloadMediaInfoStateError = 3,

    /// Finish state
    TXVodDownloadMediaInfoStateFinish = 4,
};

LITEAV_EXPORT @interface TXVodDownloadMediaInfo : NSObject

/**
 * The download object specified by`fileid`, which is optional.
 */
@property(nonatomic, strong) TXVodDownloadDataSource *dataSource;

/**
 * The download URL. When downloading with private encryption, please use the fileid object to download
 */
@property(nonatomic, copy) NSString *url;

/**
 * The account name
 */
@property(nonatomic, copy) NSString *userName;

/**
 * The duration. Returns a value in seconds
 */
@property(nonatomic, assign) int duration;

/**
 * The playable duration. Returns a value in seconds
 */
@property(nonatomic, assign) int playableDuration;

/**
 * The total file size in bytes
 */
@property(nonatomic, assign) long size;

/**
 * The size of the downloaded part in bytes
 */
@property(nonatomic, assign) long downloadSize;

/**
 * The total number of segments
 */
@property(nonatomic, assign) int segments;

/**
 * The number of downloaded segments
 */
@property(nonatomic, assign) int downloadSegments;

/**
 * The progress
 */
@property(nonatomic, assign) float progress;

/**
 * The playback path, which can be passed in to TXVodPlayer for playback.
 *
 * @discussion When this parameter is used for playing local video , it needs to be obtained through  getDownloadMediaInfoList  or getDownloadMediaInfo: interface, and cannot be saved privately
 */
@property(nonatomic, copy) NSString *playPath;

/**
 * The download speed in B/s
 */
@property(nonatomic, assign) int speed;

/**
 * download status
 */
@property(nonatomic, assign) TXVodDownloadMediaInfoState downloadState;

/**
 * prefer clarity. When querying the playback status, it needs to be consistent with when downloading. The default value is 720P
 */
@property(nonatomic, assign) long preferredResolution;

/**
 * determine whether the resource is damaged, such as being deleted after downloading, etc.The default value is NO
 */
@property(nonatomic, assign) BOOL isResourceBroken;

/**
 * Whether the download is complete
 */
- (BOOL)isDownloadFinished;

@end
