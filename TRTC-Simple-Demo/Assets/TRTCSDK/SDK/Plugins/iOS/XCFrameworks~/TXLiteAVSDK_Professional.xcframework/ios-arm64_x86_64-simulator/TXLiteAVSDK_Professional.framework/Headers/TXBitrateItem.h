//  Copyright © 2021 Tencent. All rights reserved.

#import <Foundation/Foundation.h>
#import "TXLiteAVSymbolExport.h"

/**
 * The HLS video bitrate information.
 */
LITEAV_EXPORT @interface TXBitrateItem : NSObject

/// The number of the stream in the m3u8 file.
@property(nonatomic, assign) NSInteger index;

/// The video width of this stream.
@property(nonatomic, assign) NSInteger width;

/// The video height of this stream.
@property(nonatomic, assign) NSInteger height;

/// The video bitrate of this stream.
@property(nonatomic, assign) NSInteger bitrate;

/// The video bandwidth of this stream.
@property(nonatomic, assign) int64_t bandwidth;

@end
