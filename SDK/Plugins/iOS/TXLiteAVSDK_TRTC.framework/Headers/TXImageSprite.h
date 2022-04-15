//  Copyright © 2021 Tencent. All rights reserved.

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "TXLiteAVSymbolExport.h"

/// 雪碧图解析工具
LITEAV_EXPORT @interface TXImageSprite : NSObject

/**
 * 设置雪碧图地址
 * @param vttUrl VTT链接
 * @param images 雪碧图大图列表
 */
- (void)setVTTUrl:(NSURL *)vttUrl imageUrls:(NSArray<NSURL *> *)images;

/**
 * 获取缩略图
 * @param time 时间点，单位秒
 * @return 获取失败返回nil
 */
- (UIImage *)getThumbnail:(GLfloat)time;

@end
