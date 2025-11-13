//  Copyright © 2020 Tencent. All rights reserved.

#import <Foundation/Foundation.h>
#if TARGET_OS_IPHONE
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#elif TARGET_OS_MAC
#import <OpenGL/OpenGL.h>
#import <OpenGL/gl.h>
#endif

@protocol TXVideoCustomProcessDelegate <NSObject>
@optional
#pragma mark - Pusher & UGC Record
/**
 * 在 OpenGL 线程中回调，在这里可以进行采集图像的二次处理
 * @param texture    纹理 ID。
 * @param width      纹理的宽度。
 * @param height     纹理的高度。
 * @return           返回给 SDK 的纹理。
 * 说明：SDK 回调出来的纹理类型是 GL_TEXTURE_2D，接口返回给 SDK 的纹理类型也必须是 GL_TEXTURE_2D。
 * 该回调在 SDK 美颜之后. 纹理格式为 GL_RGBA。
 */
- (GLuint)onPreProcessTexture:(GLuint)texture width:(CGFloat)width height:(CGFloat)height;

/**
 * 在 OpenGL 线程中回调，可以在这里释放创建的 OpenGL 资源
 */
- (void)onTextureDestoryed;

/**
 * 人脸数据回调（增值版且启用了 pitu 模块才有效）
 * @param points 人脸坐标。
 *  说明：开启 pitu 模块必须是打开动效或大眼瘦脸。此回调在 onPreProcessTexture:width:height: 之前。
 */
- (void)onDetectFacePoints:(NSArray *)points;

#pragma mark - Player
/**
 * 视频渲染对象回调
 * @param pixelBuffer   渲染图像。
 *  说明：渲染图像的数据类型为 config 中设置的 renderPixelFormatType。
 */
- (BOOL)onPlayerPixelBuffer:(CVPixelBufferRef)pixelBuffer;
@end
