//  Copyright © 2021 Tencent. All rights reserved.

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "TXLiteAVSymbolExport.h"

LITEAV_EXPORT @interface TXImageSprite : NSObject

/**
 * This API is used to set the image sprite URL.
 *
 * @param vttUrl The VTT URL
 * @param images The list of images in the image sprite
 */
- (void)setVTTUrl:(NSURL *)vttUrl imageUrls:(NSArray<NSURL *> *)images;

/**
 * This API is used to get a thumbnail.
 *
 * @param time The time point in seconds
 * @return If acquisition fails, nil will be returned.
 */
- (UIImage *)getThumbnail:(GLfloat)time;

@end
