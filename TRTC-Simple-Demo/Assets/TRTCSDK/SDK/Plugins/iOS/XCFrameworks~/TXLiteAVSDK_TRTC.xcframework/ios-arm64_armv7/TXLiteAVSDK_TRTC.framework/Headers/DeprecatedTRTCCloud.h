/**
 * Copyright (c) 2022 Tencent. All rights reserved.
 * Module:   DeprecatedTRTCCloud @ TXLiteAVSDK
 * Function: TRTC 废弃接口
 */
#import "TRTCCloudDef.h"
#import "TRTCCloud.h"

NS_ASSUME_NONNULL_BEGIN
@interface TRTCCloud (deprecated)

/////////////////////////////////////////////////////////////////////////////////
//
//                    弃用接口（建议使用对应的新接口）
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 设置美颜、美白以及红润效果级别
 *
 * @deprecated v6.9 版本开始不推荐使用，建议使用 {@link getBeautyManager} 替代之。
 */
- (void)setBeautyStyle:(TRTCBeautyStyle)beautyStyle beautyLevel:(NSInteger)beautyLevel whitenessLevel:(NSInteger)whitenessLevel ruddinessLevel:(NSInteger)ruddinessLevel __attribute__((deprecated("use getBeautyManager instead")));

/**
 * 设置大眼级别
 *
 * @deprecated v6.9 版本开始不推荐使用，建议使用 {@link getBeautyManager} 替代之。
 */
#if TARGET_OS_IPHONE
- (void)setEyeScaleLevel:(float)eyeScaleLevel __attribute__((deprecated("use getBeautyManager instead")));
#endif

/**
 * 设置瘦脸级别
 *
 * @deprecated v6.9 版本开始不推荐使用，建议使用 {@link getBeautyManager} 替代之。
 */
#if TARGET_OS_IPHONE
- (void)setFaceScaleLevel:(float)faceScaleLevel __attribute__((deprecated("use getBeautyManager instead")));
#endif

/**
 * 设置 V 脸级别
 *
 * @deprecated v6.9 版本开始不推荐使用，建议使用 {@link getBeautyManager} 替代之。
 */
#if TARGET_OS_IPHONE
- (void)setFaceVLevel:(float)faceVLevel __attribute__((deprecated("use getBeautyManager instead")));
#endif

/**
 * 设置下巴拉伸或收缩幅度
 *
 * @deprecated v6.9 版本开始不推荐使用，建议使用 {@link getBeautyManager} 替代之。
 */
#if TARGET_OS_IPHONE
- (void)setChinLevel:(float)chinLevel __attribute__((deprecated("use getBeautyManager instead")));
#endif

/**
 * 设置短脸级别
 *
 * @deprecated v6.9 版本开始不推荐使用，建议使用 {@link getBeautyManager} 替代之。
 */
#if TARGET_OS_IPHONE
- (void)setFaceShortLevel:(float)faceShortlevel __attribute__((deprecated("use getBeautyManager instead")));
#endif

/**
 * 设置瘦鼻级别
 *
 * @deprecated v6.9 版本开始不推荐使用，建议使用 {@link getBeautyManager} 替代之。
 */
#if TARGET_OS_IPHONE
- (void)setNoseSlimLevel:(float)noseSlimLevel __attribute__((deprecated("use getBeautyManager instead")));
#endif

/**
 * 设置动效贴纸
 *
 * @deprecated v6.9 版本开始不推荐使用，建议使用 {@link getBeautyManager} 替代之。
 */
#if TARGET_OS_IPHONE
- (void)selectMotionTmpl:(NSString *)tmplPath __attribute__((deprecated("use getBeautyManager instead")));
#endif

/**
 * 设置动效静音
 *
 * @deprecated v6.9 版本开始不推荐使用，建议使用 {@link getBeautyManager} 替代之。
 */
#if TARGET_OS_IPHONE
- (void)setMotionMute:(BOOL)motionMute __attribute__((deprecated("use getBeautyManager instead")));
#endif

/**
 * 设置色彩滤镜效果
 *
 * @deprecated v7.2 版本开始不推荐使用，建议使用 {@link getBeautyManager} 替代之。
 */
- (void)setFilter:(TXImage *)image __attribute__((deprecated("use getBeautyManager instead")));

/**
 * 设置色彩滤镜浓度
 *
 * @deprecated v7.2 版本开始不推荐使用，建议使用 {@link getBeautyManager} 替代之。
 */
- (void)setFilterConcentration:(float)concentration __attribute__((deprecated("use getBeautyManager instead")));

/**
 * 设置绿幕背景视频
 *
 * @deprecated v7.2 版本开始不推荐使用，建议使用 {@link getBeautyManager} 替代之。
 */
- (void)setGreenScreenFile:(NSURL *)file __attribute__((deprecated("use getBeautyManager instead")));

/**
 * 设置混响效果
 *
 * @deprecated v7.3 版本开始不推荐使用，建议使用 {@link TXAudioEffectManager} 中的 {@link setVoiceReverbType} 替代之。
 */
- (void)setReverbType:(TRTCReverbType)reverbType __attribute__((deprecated("use TXAudioEffectManager#setVoiceReverbType instead")));

/**
 * 设置变声类型
 *
 * @deprecated v7.3 版本开始不推荐使用，建议使用 {@link TXAudioEffectManager} 中的 {@link setVoiceChangerType} 替代之。
 */
- (void)setVoiceChangerType:(TRTCVoiceChangerType)voiceChangerType __attribute__((deprecated("use TXAudioEffectManager#setVoiceChangerType instead")));

/**
 * 开启（或关闭）耳返
 *
 * @deprecated v7.3 版本开始不推荐使用，建议使用 {@link TXAudioEffectManager} 中的 {@link setVoiceEarMonitor} 替代之。
 */
#if TARGET_OS_IPHONE
- (void)enableAudioEarMonitoring:(BOOL)enable __attribute__((deprecated("use TXAudioEffectManager#setVoiceEarMonitor instead")));
#endif

/**
 * 启用音量大小提示
 *
 * @deprecated v10.1 版本开始不推荐使用，建议使用 {@link enableAudioVolumeEvaluation}(enable, params) 替代之。
 */
- (void)enableAudioVolumeEvaluation:(NSUInteger)interval __attribute__((deprecated("use enableAudioVolumeEvaluation:withParams: instead")));

/**
 * 启用音量大小提示
 *
 * @deprecated v11.2 版本开始不推荐使用，建议使用 {@link enableAudioVolumeEvaluation}(enable, params) 替代之。
 */
- (void)enableAudioVolumeEvaluation:(NSUInteger)interval enable_vad:(BOOL)enable_vad __attribute__((deprecated("use enableAudioVolumeEvaluation:withParams: instead")));

/**
 * 切换摄像头
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link TXDeviceManager} 中的 {@link switchCamera} 接口替代之。
 */
#if TARGET_OS_IPHONE
- (void)switchCamera __attribute__((deprecated("use TXDeviceManager#switchCamera instead")));
#endif

/**
 * 查询当前摄像头是否支持缩放
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link TXDeviceManager} 中的 {@link isCameraZoomSupported} 接口替代之。
 */
#if TARGET_OS_IPHONE
- (BOOL)isCameraZoomSupported __attribute__((deprecated("use TXDeviceManager#isCameraZoomSupported instead")));
#endif

/**
 * 设置摄像头缩放倍数（焦距）
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link TXDeviceManager} 中的 {@link setCameraZoomRatio} 接口替代之。
 */
#if TARGET_OS_IPHONE
- (void)setZoom:(CGFloat)distance __attribute__((deprecated("use TXDeviceManager#setCameraZoomRatio instead")));
#endif

/**
 * 查询是否支持开关闪光灯
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link TXDeviceManager} 中的 {@link isCameraTorchSupported} 接口替代之。
 */
#if TARGET_OS_IPHONE
- (BOOL)isCameraTorchSupported __attribute__((deprecated("use TXDeviceManager#isCameraTorchSupported instead")));
#endif

/**
 * 开关/关闭闪光灯
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link TXDeviceManager} 中的 {@link enableCameraTorch} 接口替代之。
 */
#if TARGET_OS_IPHONE
- (BOOL)enbaleTorch:(BOOL)enable __attribute__((deprecated("use TXDeviceManager#enableCameraTorch instead")));
#endif

/**
 * 查询摄像头是否支持设置焦点
 *
 * @deprecated v8.0 版本开始不推荐使用。
 */
#if TARGET_OS_IPHONE
- (BOOL)isCameraFocusPositionInPreviewSupported __attribute__((deprecated));
#endif

/**
 * 设置摄像头焦点坐标位置
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link TXDeviceManager} 中的 {@link setCameraFocusPosition} 接口替代之。
 */
#if TARGET_OS_IPHONE
- (void)setFocusPosition:(CGPoint)touchPoint __attribute__((deprecated("use TXDeviceManager#setCameraFocusPosition instead")));
#endif

/**
 * 查询是否支持自动识别人脸位置
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link TXDeviceManager} 中的 {@link isAutoFocusEnabled} 接口替代之。
 */
#if TARGET_OS_IPHONE
- (BOOL)isCameraAutoFocusFaceModeSupported __attribute__((deprecated("use TXDeviceManager#isAutoFocusEnabled instead")));
#endif

/**
 * 开启/关闭人脸跟踪对焦
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link TXDeviceManager} 中的 {@link enableCameraAutoFocus} 接口替代之。
 */
#if TARGET_OS_IPHONE
- (void)enableAutoFaceFoucs:(BOOL)enable __attribute__((deprecated("use TXDeviceManager#enableCameraAutoFocus instead")));
#endif

/**
 * 设置系统音量类型
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link startLocalAudio}(quality) 替代之，通过 quality 参数来决策音质。
 */
- (void)setSystemVolumeType:(TRTCSystemVolumeType)type __attribute__((deprecated("use startLocalAudio:quality instead")));

/**
 * 视频截图
 *
 * @deprecated v8.2 版本开始不推荐使用，建议使用 {@link snapshotVideo} 替代之。
 */
- (void)snapshotVideo:(NSString *)userId type:(TRTCVideoStreamType)streamType completionBlock:(void (^)(TXImage *image))completionBlock __attribute__((deprecated("use snapshotVideo:type:sourceType:completionBlock instead")));

/**
 * 开始全系统的屏幕分享（iOS）
 *
 * @deprecated v8.6 版本开始不推荐使用，建议使用 {@link startScreenCaptureByReplaykit} 接口替代之。
 */
- (void)startScreenCaptureByReplaykit:(TRTCVideoEncParam *)encParams appGroup:(NSString *)appGroup __attribute__((deprecated("use startScreenCaptureByReplaykit:encParam:appGroup: instead")));

/**
 * 设置音频质量
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link startLocalAudio} 替代之。
 */
- (void)startLocalAudio __attribute__((deprecated("use startLocalAudio(quality) instead")));

/**
 * 开始显示远端视频画面
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link startRemoteView} 替代之。
 */
- (void)startRemoteView:(NSString *)userId view:(TXView *)view __attribute__((deprecated("use startRemoteView:streamType:view: instead")));

/**
 * 停止显示远端视频画面，同时不再拉取该远端用户的视频数据流
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link stopRemoteView} 替代之。
 */
- (void)stopRemoteView:(NSString *)userId __attribute__((deprecated("use stopRemoteView:streamType: instead")));

/**
 * 设置本地图像的渲染模式
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link setLocalRenderParams} 替代之。
 */
- (void)setLocalViewFillMode:(TRTCVideoFillMode)mode __attribute__((deprecated("use setLocalRenderParams instead")));

/**
 * 设置本地图像的顺时针旋转角度
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link setLocalRenderParams} 替代之。
 */
- (void)setLocalViewRotation:(TRTCVideoRotation)rotation __attribute__((deprecated("use setLocalRenderParams instead")));

/**
 * 设置本地摄像头预览画面的镜像模式
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link setLocalRenderParams} 替代之。
 */
#if TARGET_OS_IPHONE
- (void)setLocalViewMirror:(TRTCLocalVideoMirrorType)mirror __attribute__((deprecated("use setLocalRenderParams: instead")));
#elif TARGET_OS_MAC
- (void)setLocalViewMirror:(BOOL)mirror __attribute__((deprecated("use setLocalRenderParams: instead")));
#endif

/**
 * 设置远端图像的渲染模式
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link setRemoteRenderParams} 替代之。
 */
- (void)setRemoteViewFillMode:(NSString *)userId mode:(TRTCVideoFillMode)mode __attribute__((deprecated("use setRemoteRenderParams:streamType:params: instead")));

/**
 * 设置远端图像的顺时针旋转角度
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link setRemoteRenderParams} 替代之。
 */
- (void)setRemoteViewRotation:(NSString *)userId rotation:(TRTCVideoRotation)rotation __attribute__((deprecated("use setRemoteRenderParams:streamType:params: instead")));

/**
 * 开始显示远端用户的辅路画面
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link startRemoteView} 替代之。
 */
- (void)startRemoteSubStreamView:(NSString *)userId view:(TXView *)view __attribute__((deprecated("use startRemoteView:type:view: instead")));

/**
 * 停止显示远端用户的辅路画面
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link stopRemoteView} 替代之。
 */
- (void)stopRemoteSubStreamView:(NSString *)userId __attribute__((deprecated("use stopRemoteView:streamType: instead")));

/**
 * 设置辅路画面的填充模式
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link setRemoteRenderParams} 替代之。
 */
- (void)setRemoteSubStreamViewFillMode:(NSString *)userId mode:(TRTCVideoFillMode)mode __attribute__((deprecated("use setRemoteRenderParams:streamType:params: instead")));

/**
 * 设置辅路画面的顺时针旋转角度
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link setRemoteRenderParams}:streamType:params: 替代之。
 */
- (void)setRemoteSubStreamViewRotation:(NSString *)userId rotation:(TRTCVideoRotation)rotation __attribute__((deprecated("use setRemoteRenderParams:streamType:params: instead")));

/**
 * 设置音频质量
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link startLocalAudio} 替代之。
 */
- (void)setAudioQuality:(TRTCAudioQuality)quality __attribute__((deprecated("use startLocalAudio(quality) instead")));

/**
 * 设定优先观看大画面还是小画面
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link startRemoteView}:streamType:view: 替代之。
 */
- (void)setPriorRemoteVideoStreamType:(TRTCVideoStreamType)streamType __attribute__((deprecated("use startRemoteView:streamType:view: instead")));

/**
 * 设置麦克风音量大小
 */
- (void)setMicVolumeOnMixing:(NSInteger)volume __attribute__((deprecated("use setAudioCaptureVolume instead")));

/**
 * 启动播放背景音乐
 *
 * @deprecated v7.3 版本开始不推荐使用，建议使用 {@link getAudioEffectManager} 替代之。
 */
- (void)playBGM:(NSString *)path
       withBeginNotify:(void (^)(NSInteger errCode))beginNotify
    withProgressNotify:(void (^)(NSInteger progressMS, NSInteger durationMS))progressNotify
     andCompleteNotify:(void (^)(NSInteger errCode))completeNotify __attribute__((deprecated("use getAudioEffectManager instead")));

/**
 * 停止播放背景音乐
 *
 * @deprecated v7.3 版本开始不推荐使用，建议使用 {@link getAudioEffectManager} 替代之。
 */
- (void)stopBGM __attribute__((deprecated("use getAudioEffectManager instead")));

/**
 * 停止播放背景音乐
 *
 * @deprecated v7.3 版本开始不推荐使用，建议使用 {@link getAudioEffectManager} 替代之。
 */
- (void)pauseBGM __attribute__((deprecated("use getAudioEffectManager instead")));

/**
 * 停止播放背景音乐
 *
 * @deprecated v7.3 版本开始不推荐使用，建议使用 {@link getAudioEffectManager} 替代之。
 */
- (void)resumeBGM __attribute__((deprecated("use getAudioEffectManager instead")));

/**
 * 获取背景音乐总时长（单位：毫秒）
 *
 * @deprecated v7.3 版本开始不推荐使用，建议使用 {@link TXAudioEffectManager} 中的 {@link getMusicDurationInMS} 替代之。
 */
- (NSInteger)getBGMDuration:(NSString *)path __attribute__((deprecated("use TXAudioEffectManager#getMusicDurationInMS instead")));

/**
 * 设置背景音乐的播放进度
 *
 * @deprecated v7.3 版本开始不推荐使用，建议使用 {@link TXAudioEffectManager} 中的 {@link seekMusicToPosInMS} 替代之。
 */
- (int)setBGMPosition:(NSInteger)pos __attribute__((deprecated("use TXAudioEffectManager#seekMusicToPosInMS instead")));

/**
 * 设置背景音乐的音量大小
 *
 * @deprecated v7.3 版本开始不推荐使用，建议使用 {@link TXAudioEffectManager} 中的 {@link setMusicVolume} 替代之。
 */
- (void)setBGMVolume:(NSInteger)volume __attribute__((deprecated("use TXAudioEffectManager#setMusicVolume instead")));

/**
 * 设置背景音乐的本地播放音量
 *
 * @deprecated v7.3 版本开始不推荐使用，建议使用 {@link TXAudioEffectManager} 中的 {@link setMusicPlayoutVolume} 替代之。
 */
- (void)setBGMPlayoutVolume:(NSInteger)volume __attribute__((deprecated("use TXAudioEffectManager#setMusicPlayoutVolume instead")));

/**
 * 设置背景音乐的远端播放音量
 *
 * @deprecated v7.3 版本开始不推荐使用，建议使用 {@link TXAudioEffectManager} 中的 {@link setBGMPublishVolume} 替代之。
 */
- (void)setBGMPublishVolume:(NSInteger)volume __attribute__((deprecated("use TXAudioEffectManager#setBGMPublishVolume instead")));

/**
 * 播放音效
 *
 * @deprecated v7.3 版本开始不推荐使用，建议使用 {@link TXAudioEffectManager} 中的 {@link startPlayMusic} 替代之。
 */
- (void)playAudioEffect:(TRTCAudioEffectParam *)effect __attribute__((deprecated("use TXAudioEffectManager#startPlayMusic instead")));

/**
 * 设置音效音量
 *
 * @deprecated v7.3 版本开始不推荐使用，建议使用 {@link TXAudioEffectManager} 中的 {@link setMusicPublishVolume} 和 {@link setMusicPlayoutVolume} 替代之。
 */
- (void)setAudioEffectVolume:(int)effectId volume:(int)volume __attribute__((deprecated("use setMusicPublishVolume/setMusicPlayoutVolume instead")));

/**
 * 停止播放音效
 *
 * @deprecated v7.3 版本开始不推荐使用，建议使用 {@link TXAudioEffectManager} 中的 {@link stopPlayMusic} 替代之。
 */
- (void)stopAudioEffect:(int)effectId __attribute__((deprecated("use TXAudioEffectManager#stopPlayMusic instead")));

/**
 * 停止所有音效
 *
 * @deprecated v7.3 版本开始不推荐使用，建议使用 {@link TXAudioEffectManager} 中的 {@link stopPlayMusic} 替代之。
 */
- (void)stopAllAudioEffects __attribute__((deprecated("use TXAudioEffectManager#stopPlayMusic instead")));

/**
 * 设置所有音效音量
 *
 * @deprecated v7.3 版本开始不推荐使用，建议使用 {@link TXAudioEffectManager} 中的 {@link setMusicPublishVolume} 和 {@link setMusicPlayoutVolume} 替代之。
 */
- (void)setAllAudioEffectsVolume:(int)volume __attribute__((deprecated("use setMusicPublishVolume/setMusicPlayoutVolume instead")));

/**
 * 暂停音效
 *
 * @deprecated v7.3 版本开始不推荐使用，建议使用 {@link TXAudioEffectManager} 中的 {@link pauseAudioEffect} 替代之。
 */
- (void)pauseAudioEffect:(int)effectId __attribute__((deprecated("use TXAudioEffectManager#pauseAudioEffect instead")));

/**
 * 暂停音效
 *
 * @deprecated v7.3 版本开始不推荐使用，建议使用 {@link TXAudioEffectManager} 中的 {@link resumePlayMusic} 替代之。
 */
- (void)resumeAudioEffect:(int)effectId __attribute__((deprecated("use TXAudioEffectManager#resumePlayMusic instead")));

/**
 * 启用视频自定义采集模式
 *
 * @deprecated v8.5 版本开始不推荐使用，建议使用 {@link enableCustomVideoCapture}(streamType, enable) 接口替代之。
 */
- (void)enableCustomVideoCapture:(BOOL)enable __attribute__((deprecated("use enableCustomVideoCapture:enable instead")));

/**
 * 投送自己采集的视频数据
 *
 * @deprecated v8.5 版本开始不推荐使用，建议使用 {@link sendCustomVideoData}(streamType, TRTCVideoFrame) 接口替代之。
 */
- (void)sendCustomVideoData:(TRTCVideoFrame *)frame __attribute__((deprecated("use sendCustomVideoData:frame: instead")));

/**
 * 暂停/恢复发布本地的视频流
 *
 * @deprecated v8.9 版本开始不推荐使用，建议使用 {@link muteLocalVideo}(streamType, mute) 接口替代之。
 */
- (void)muteLocalVideo:(BOOL)mute __attribute__((deprecated("use muteLocalVideo:streamType:mute: instead")));

/**
 * 暂停 / 恢复订阅远端用户的视频流
 *
 * @deprecated v8.9 版本开始不推荐使用，建议使用 {@link muteRemoteVideoStream}(userId, streamType, mute) 接口替代之。
 */
- (void)muteRemoteVideoStream:(NSString *)userId mute:(BOOL)mute __attribute__((deprecated("use muteRemoteVideoStream:userid,streamType:mute: instead")));

/**
 *  开始进行网络测速（进入房间前使用）
 *
 * @deprecated v9.2 版本开始不推荐使用，建议使用 {@link startSpeedTest}(params) 接口替代之。
 */
- (void)startSpeedTest:(uint32_t)sdkAppId
                userId:(NSString *)userId
               userSig:(NSString *)userSig
            completion:(void (^)(TRTCSpeedTestResult *result, NSInteger completedCount, NSInteger totalCount))completion __attribute__((deprecated("use startSpeedTest: instead")));

/**
 * 启动屏幕分享
 *
 * @deprecated v7.2 版本开始不推荐使用，建议使用 {@link startScreenCapture} 替代之。
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)startScreenCapture:(nullable NSView *)view __attribute__((deprecated("use startScreenCapture:streamType:encParam: instead")));
#endif

/**
 * 获取摄像头设备列表
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link TXDeviceManager} 中的 {@link getDevicesList} 接口替代之。
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (NSArray<TRTCMediaDeviceInfo *> *)getCameraDevicesList __attribute__((deprecated("use TXDeviceManager#getDevicesList instead")));
#endif

/**
 * 选定当前要使用的摄像头
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link TXDeviceManager} 中的 {@link setCurrentDevice} 接口替代之。
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (int)setCurrentCameraDevice:(NSString *)deviceId __attribute__((deprecated("use TXDeviceManager#setCurrentDevice instead")));
#endif

/**
 * 获取当前使用的摄像头
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link TXDeviceManager} 中的 {@link getCurrentDevice} 接口替代之。
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (TRTCMediaDeviceInfo *)getCurrentCameraDevice __attribute__((deprecated("use TXDeviceManager#getCurrentDevice instead")));
#endif

/**
 * 获取麦克风设备列表
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link TXDeviceManager} 中的 {@link getDevicesList} 接口替代之。
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (NSArray<TRTCMediaDeviceInfo *> *)getMicDevicesList __attribute__((deprecated("use TXDeviceManager#getDevicesList instead")));
#endif

/**
 * 获取当前的麦克风设备
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link TXDeviceManager} 中的 {@link getCurrentDevice} 接口替代之。
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (TRTCMediaDeviceInfo *)getCurrentMicDevice __attribute__((deprecated("use TXDeviceManager#getCurrentDevice instead")));
#endif

/**
 * 选定当前使用的麦克风
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link TXDeviceManager} 中的 {@link setCurrentDevice} 接口替代之。
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (int)setCurrentMicDevice:(NSString *)deviceId __attribute__((deprecated("use TXDeviceManager#setCurrentDevice instead")));
#endif

/**
 * 获取当前麦克风的设备音量
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link TXDeviceManager} 中的 {@link getCurrentDeviceVolume} 接口替代之。
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (float)getCurrentMicDeviceVolume __attribute__((deprecated("use TXDeviceManager#getCurrentDeviceVolume instead")));
#endif

/**
 * 设置当前麦克风的设备音量
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link TXDeviceManager} 中的 {@link setCurrentDeviceVolume} 接口替代之。
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)setCurrentMicDeviceVolume:(NSInteger)volume __attribute__((deprecated("use TXDeviceManager#setCurrentDeviceVolume instead")));
#endif

/**
 * 设置系统当前麦克风设备的静音状态
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link TXDeviceManager} 中的 {@link setCurrentDeviceMute} 接口替代之。
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)setCurrentMicDeviceMute:(BOOL)mute __attribute__((deprecated("use TXDeviceManager#setCurrentDeviceMute instead")));
#endif

/**
 * 获取系统当前麦克风设备是否静音
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link TXDeviceManager} 中的 {@link getCurrentDeviceMute} 接口替代之。
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (BOOL)getCurrentMicDeviceMute __attribute__((deprecated("use TXDeviceManager#getCurrentDeviceMute instead")));
#endif

/**
 * 获取扬声器设备列表
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link TXDeviceManager} 中的 {@link getDevicesList} 接口替代之。
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (NSArray<TRTCMediaDeviceInfo *> *)getSpeakerDevicesList __attribute__((deprecated("use TXDeviceManager#getDevicesList instead")));
#endif

/**
 * 获取当前的扬声器设备
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link TXDeviceManager} 中的 {@link getCurrentDevice} 接口替代之。
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (TRTCMediaDeviceInfo *)getCurrentSpeakerDevice __attribute__((deprecated("use TXDeviceManager#getCurrentDevice instead")));
#endif

/**
 * 设置要使用的扬声器
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link TXDeviceManager} 中的 {@link setCurrentDevice} 接口替代之。
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (int)setCurrentSpeakerDevice:(NSString *)deviceId __attribute__((deprecated("use TXDeviceManager#setCurrentDevice instead")));
#endif

/**
 * 获取当前扬声器的设备音量
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link TXDeviceManager} 中的 {@link getCurrentDeviceVolume} 接口替代之。
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (float)getCurrentSpeakerDeviceVolume __attribute__((deprecated("use TXDeviceManager#getCurrentDeviceVolume instead")));
#endif

/**
 * 设置当前扬声器的设备音量
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link TXDeviceManager} 中的 {@link setCurrentDeviceVolume} 接口替代之。
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (int)setCurrentSpeakerDeviceVolume:(NSInteger)volume __attribute__((deprecated("use TXDeviceManager#setCurrentDeviceVolume instead")));
#endif

/**
 * 获取系统当前扬声器设备是否静音
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link TXDeviceManager} 中的 {@link getCurrentDeviceMute} 接口替代之。
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (BOOL)getCurrentSpeakerDeviceMute __attribute__((deprecated("use TXDeviceManager#getCurrentDeviceMute instead")));
#endif

/**
 * 设置系统当前扬声器设备的静音状态
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link TXDeviceManager} 中的 {@link setCurrentDeviceMute} 接口替代之。
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)setCurrentSpeakerDeviceMute:(BOOL)mute __attribute__((deprecated("use TXDeviceManager#setCurrentDeviceMute instead")));
#endif

/**
 * 开始进行摄像头测试
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link TXDeviceManager} 中的 {@link startCameraDeviceTest} 接口替代之。
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)startCameraDeviceTestInView:(NSView *)view __attribute__((deprecated("use TXDeviceManager#startCameraDeviceTest instead")));
#endif

/**
 * 停止进行摄像头测试
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link TXDeviceManager} 中的 {@link stopCameraDeviceTest} 接口替代之。
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)stopCameraDeviceTest __attribute__((deprecated("use TXDeviceManager#stopCameraDeviceTest instead")));
#endif

/**
 * 开始进行麦克风测试
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link TXDeviceManager} 中的 {@link startMicDeviceTest} 接口替代之。
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)startMicDeviceTest:(NSInteger)interval testEcho:(void (^)(NSInteger volume))testEcho __attribute__((deprecated("use TXDeviceManager#startMicDeviceTest instead")));
#endif

/**
 * 开始进行麦克风测试
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link TXDeviceManager} 中的 {@link stopMicDeviceTest} 接口替代之。
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)stopMicDeviceTest __attribute__((deprecated("use TXDeviceManager#stopMicDeviceTest instead")));
#endif

/**
 * 开始进行扬声器测试
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link TXDeviceManager} 中的 {@link startSpeakerDeviceTest} 接口替代之。
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)startSpeakerDeviceTest:(NSString *)audioFilePath onVolumeChanged:(void (^)(NSInteger volume, BOOL isLastFrame))volumeBlock __attribute__((deprecated("use TXDeviceManager#startSpeakerDeviceTest instead")));
#endif

/**
 * 停止进行扬声器测试
 *
 * @deprecated v8.0 版本开始不推荐使用，建议使用 {@link TXDeviceManager} 中的 {@link stopSpeakerDeviceTest} 接口替代之。
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)stopSpeakerDeviceTest __attribute__((deprecated("use TXDeviceManager#stopSpeakerDeviceTest instead")));
#endif

/**
 * 开始应用内的屏幕分享（iOS）
 *
 * @deprecated v8.6 版本开始不推荐使用，建议使用 {@link startScreenCaptureInApp} 接口替代之。
 */
- (void)startScreenCaptureInApp:(TRTCVideoEncParam *)encParams __attribute__((deprecated("use startScreenCaptureInApp:encParam: instead")));

@end
NS_ASSUME_NONNULL_END
