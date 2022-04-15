//  Copyright © 2021 Tencent. All rights reserved.

#import <Foundation/Foundation.h>
#if TARGET_OS_OSX
#import <AppKit/AppKit.h>
#else
#import <UIKit/UIKit.h>
#endif
#import "TXBitrateItem.h"
#import "TXLiteAVSymbolExport.h"
#import "TXLivePlayListener.h"
#import "TXLiveSDKEventDef.h"
#import "TXPlayerAuthParams.h"
#import "TXVideoCustomProcessDelegate.h"
#import "TXVodPlayConfig.h"
#import "TXVodPlayListener.h"

LITEAV_EXPORT @interface TXVodPlayer : NSObject

/**
 * 事件回调, 建议使用vodDelegate
 */
@property(nonatomic, weak) id<TXLivePlayListener> delegate __attribute__((deprecated("use vodDelegate instead")));

/**
 * 事件回调
 */
@property(nonatomic, weak) id<TXVodPlayListener> vodDelegate;

/**
 * 视频渲染回调。
 *
 * 仅硬解支持,全平台接口软解硬解均支持
 */
@property(nonatomic, weak) id<TXVideoCustomProcessDelegate> videoProcessDelegate;

/**
 * 是否开启硬件加速
 */
@property(nonatomic, assign) BOOL enableHWAcceleration;

/**
 * 点播配置
 */
@property(nonatomic, copy) TXVodPlayConfig *config;

/**
 * startPlay后是否立即播放，默认YES
 */
@property BOOL isAutoPlay;

/**
 * 加密HLS的token。设置此值后，播放器自动在URL中的文件名之前增加 voddrm.token.TOKEN
 */
@property(nonatomic, strong) NSString *token;

/**
 * setupContainView 创建Video渲染View,该控件承载着视频内容的展示。
 */
#if TARGET_OS_OSX
- (void)setupVideoWidget:(NSView *)view insertIndex:(unsigned int)idx;
#else
- (void)setupVideoWidget:(UIView *)view insertIndex:(unsigned int)idx;
#endif

/**
 * 移除Video渲染View
 */
- (void)removeVideoWidget;

/**
 * 设置播放开始时间
 */
- (void)setStartTime:(CGFloat)startTime;

/**
 * 启动从指定URL播放,此接口的全平台版本没有参数
 *
 * 开始多媒体文件播放 注意此接口的全平台版本没有参数
 * 支持的视频格式包括：mp4、avi、mkv、wmv、m4v。
 * 支持的音频格式包括：mp3、wav、wma、aac。
 */
- (int)startPlay:(NSString *)url;

/**
 * 通过fileid方式播放。
 */
- (int)startPlayWithParams:(TXPlayerAuthParams *)params;

/**
 * 停止播放音视频流
 */
- (int)stopPlay;

/**
 * 是否正在播放
 */
- (bool)isPlaying;

/**
 * 暂停播放
 */
- (void)pause;

/**
 * 继续播放
 */
- (void)resume;

/**
 * 播放跳转到音视频流某个时间
 */
- (int)seek:(float)time;

/**
 * 获取当前播放时间
 */
- (float)currentPlaybackTime;

/**
 * 获取视频总时长
 */
- (float)duration;

/**
 * 可播放时长
 */
- (float)playableDuration;

/**
 * 视频宽度
 */
- (int)width;

/**
 * 视频高度
 */
- (int)height;

/**
 * 设置画面的方向
 *
 * @brief 设置本地图像的顺时针旋转角度
 * @param rotation 支持 TRTCVideoRotation90 、 TRTCVideoRotation180 以及 TRTCVideoRotation270 旋转角度，默认值：TRTCVideoRotation0
 * @note 用于窗口渲染模式
 */
- (void)setRenderRotation:(TX_Enum_Type_HomeOrientation)rotation;

/**
 * 设置画面的裁剪模式
 *
 * @param mode 填充（画面可能会被拉伸裁剪）或适应（画面可能会有黑边），默认值：TRTCVideoFillMode_Fit
 * @note 用于窗口渲染模式
 */
- (void)setRenderMode:(TX_Enum_Type_RenderMode)renderMode;

/**
 * 设置静音
 */
- (void)setMute:(BOOL)bEnable;

/**
 * 设置音量大小
 *
 * @param volume 音量大小，100为原始音量，范围是：[0 ~ 150]，默认值为100
 */
- (void)setAudioPlayoutVolume:(int)volume;

/**
 * snapshotCompletionBlock 通过回调返回当前图像
 */
#if TARGET_OS_OSX
- (void)snapshot:(void (^)(NSImage *))snapshotCompletionBlock;
#else
- (void)snapshot:(void (^)(UIImage *))snapshotCompletionBlock;
#endif

/**
 * 设置播放速率
 *
 * @param rate 播放速度（0.5-2.0）
 */
- (void)setRate:(float)rate;

/**
 * 当播放地址为master playlist，返回支持的码率（清晰度）
 */
- (NSArray<TXBitrateItem *> *)supportedBitrates;

/**
 * 获取当前正在播放的码率索引
 */
- (NSInteger)bitrateIndex;

/**
 * 设置当前正在播放的码率索引，无缝切换清晰度
 * 清晰度切换可能需要等待一小段时间。腾讯云支持多码率HLS分片对齐，保证最佳体验。
 */
- (void)setBitrateIndex:(NSInteger)index;

/**
 * 设置画面镜像
 */
- (void)setMirror:(BOOL)isMirror;

/**
 * 将当前vodPlayer附着至TRTC
 *
 * @param trtcCloud TRTC 实例指针
 * @note 用于辅流推送，绑定后音频播放由TRTC接管
 */
- (void)attachTRTC:(NSObject *)trtcCloud;

/**
 * 将当前vodPlayer和TRTC分离
 */
- (void)detachTRTC;

/**
 * 开始向TRTC发布辅路视频流
 */
- (void)publishVideo;

/**
 * 开始向TRTC发布辅路音频流
 */
- (void)publishAudio;

/**
 * 结束向TRTC发布辅路视频流
 */
- (void)unpublishVideo;

/**
 * 结束向TRTC发布辅路音频流
 */
- (void)unpublishAudio;

/**
 * 是否循环播放
 */
@property(nonatomic, assign) BOOL loop;

/**
 * 获取加固加密播放密钥
 */
+ (NSString *)getEncryptedPlayKey:(NSString *)key;

@end
