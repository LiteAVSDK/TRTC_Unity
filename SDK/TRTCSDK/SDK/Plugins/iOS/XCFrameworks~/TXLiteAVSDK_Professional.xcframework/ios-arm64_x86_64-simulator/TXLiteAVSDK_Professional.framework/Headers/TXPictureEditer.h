// Copyright (c) 2024 Tencent. All rights reserved.
// Author: eddardliu

#import <Foundation/Foundation.h>
#import "TXLiteAVSymbolExport.h"
#import "TXVideoEditerTypeDef.h"

LITEAV_EXPORT @interface TXPictureEditer : NSObject
- (instancetype)init;
/**
 * 设置源图片
 * @param bitmap 要处理的图片
 */
- (void)setPicture:(UIImage *)source;

/**
 * 设置贴纸参数
 * @param pasterList 静态贴纸列表.TXPaster中的startTime，endTime将被忽略
 */
- (void)setPasterList:(NSArray<TXPaster *> *)pasterList;

/**
 * 设置裁剪区域
 */
- (void)setCropRect:(CGRect)rect;

/**
 * 设置输出旋转角取值为
 * @param rotation 取值为:0，90，180，270
 */
- (void)setOutputRotation:(int)rotation;

/**
 * 设置输出图片的填充模式
 * @param txPreviewRenderMode 填充参数 @see TXPreviewRenderMode
 */
- (void)setOutputFillMode:(TXPreviewRenderMode)txPreviewRenderMode;

/**
 * 设置输出图片的size
 */
- (void)setOutputSize:(int)width height:(int)height;

/**
 * 处理图片，结果在回调中返回
 */
- (void)processPicture:(void (^)(UIImage *))completion;
@end
