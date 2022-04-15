//  Copyright © 2021 Tencent. All rights reserved.

#import <Foundation/Foundation.h>
#import "TXLiteAVSymbolExport.h"

/// @addtogroup TXVodPlayConfig_ios
/// @{

/// HLS多码率信息
LITEAV_EXPORT @interface TXBitrateItem : NSObject

@property(nonatomic, assign) NSInteger index;    ///< m3u8 文件中的序号
@property(nonatomic, assign) NSInteger width;    ///< 此流的视频宽度
@property(nonatomic, assign) NSInteger height;   ///< 此流的视频高度
@property(nonatomic, assign) NSInteger bitrate;  ///< 此流的视频码率

@end
/// @}
