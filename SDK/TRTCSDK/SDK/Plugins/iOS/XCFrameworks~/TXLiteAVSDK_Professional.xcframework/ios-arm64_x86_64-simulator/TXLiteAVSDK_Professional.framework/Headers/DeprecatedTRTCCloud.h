/**
 * Copyright (c) 2022 Tencent. All rights reserved.
 */
#import "TRTCCloudDef.h"
#import "TRTCCloud.h"

NS_ASSUME_NONNULL_BEGIN
@interface TRTCCloud (deprecated)

/////////////////////////////////////////////////////////////////////////////////
//
//                    Disused APIs (the corresponding new APIs are recommended)
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * Terminate TRTCCloud instance (singleton mode).
 *
 * @deprecated This API is not recommended after 11.5 Please use {@link destroySharedInstance} instead.
 */
+ (void)destroySharedIntance __attribute__((deprecated("use destroySharedInstance instead")));

/**
 * Set TRTC event callback.
 *
 * @deprecated This API is not recommended after v11.4 Please use {@link addDelegate} instead.
 */
@property(nonatomic, weak, nullable) id<TRTCCloudDelegate> delegate __attribute__((deprecated("use addDelegate instead")));

/**
 * Set the strength of beauty, brightening, and rosy skin filters.
 *
 * @deprecated This API is not recommended after v6.9. Please use {@link setBeautyStyle}, {@link setBeautyLevel}, {@link setWhitenessLevel}, {@link setRuddyLevel} API in {@link TXBeautyManager} instead.
 */
- (void)setBeautyStyle:(TRTCBeautyStyle)beautyStyle
           beautyLevel:(NSInteger)beautyLevel
        whitenessLevel:(NSInteger)whitenessLevel
        ruddinessLevel:(NSInteger)ruddinessLevel __attribute__((deprecated("use TXBeautyManager#setBeautyStyle, TXBeautyManager#setBeautyLevel, TXBeautyManager#setWhitenessLevel, TXBeautyManager#setRuddyLevel instead")));

/**
 * Set the strength of eye enlarging filter.
 *
 * @deprecated This API is not recommended after v6.9. Please use {@link setEyeScaleLevel} API in {@link TXBeautyManager} instead.
 */
#if TARGET_OS_IPHONE
- (void)setEyeScaleLevel:(float)eyeScaleLevel __attribute__((deprecated("use TXBeautyManager#setEyeScaleLevel instead")));
#endif

/**
 * Set the strength of face slimming filter.
 *
 * @deprecated This API is not recommended after v6.9. Please use {@link setFaceSlimLevel} API in {@link TXBeautyManager} instead.
 */
#if TARGET_OS_IPHONE
- (void)setFaceScaleLevel:(float)faceScaleLevel __attribute__((deprecated("use TXBeautyManager#setFaceSlimLevel instead")));
#endif

/**
 * Set the strength of chin slimming filter.
 *
 * @deprecated This API is not recommended after v6.9. Please use {@link setFaceVLevel} API in {@link TXBeautyManager} instead.
 */
#if TARGET_OS_IPHONE
- (void)setFaceVLevel:(float)faceVLevel __attribute__((deprecated("use TXBeautyManager#setFaceVLevel instead")));
#endif

/**
 * Set the strength of chin lengthening/shortening filter.
 *
 * @deprecated This API is not recommended after v6.9. Please use {@link setChinLevel} API in {@link TXBeautyManager} instead.
 */
#if TARGET_OS_IPHONE
- (void)setChinLevel:(float)chinLevel __attribute__((deprecated("use TXBeautyManager#setChinLevel instead")));
#endif

/**
 * Set the strength of face shortening filter.
 *
 * @deprecated This API is not recommended after v6.9. Please use {@link setFaceShortLevel} API in {@link TXBeautyManager} instead.
 */
#if TARGET_OS_IPHONE
- (void)setFaceShortLevel:(float)faceShortlevel __attribute__((deprecated("use TXBeautyManager#setFaceShortLevel instead")));
#endif

/**
 * Set the strength of nose slimming filter.
 *
 * @deprecated This API is not recommended after v6.9. Please use {@link setNoseSlimLevel} API in {@link TXBeautyManager} instead.
 */
#if TARGET_OS_IPHONE
- (void)setNoseSlimLevel:(float)noseSlimLevel __attribute__((deprecated("use TXBeautyManager#setNoseSlimLevel instead")));
#endif

/**
 * Set animated sticker.
 *
 * @deprecated This API is not recommended after v6.9. Please use {@link setMotionTmpl} API in {@link TXBeautyManager} instead.
 */
#if TARGET_OS_IPHONE
- (void)selectMotionTmpl:(NSString *)tmplPath __attribute__((deprecated("use TXBeautyManager#setMotionTmpl instead")));
#endif

/**
 * Mute animated sticker.
 *
 * @deprecated This API is not recommended after v6.9. Please use {@link setMotionMute} API in {@link TXBeautyManager} instead.
 */
#if TARGET_OS_IPHONE
- (void)setMotionMute:(BOOL)motionMute __attribute__((deprecated("use TXBeautyManager#setMotionMute instead")));
#endif

/**
 * Set color filter.
 *
 * @deprecated This API is not recommended after v7.2. Please use {@link setFilter} API in {@link TXBeautyManager} instead.
 */
- (void)setFilter:(TXImage *)image __attribute__((deprecated("use TXBeautyManager#setFilter instead")));

/**
 * Set the strength of color filter.
 *
 * @deprecated This API is not recommended after v7.2. Please use {@link setFilterStrength} API in {@link TXBeautyManager} instead.
 */
- (void)setFilterConcentration:(float)concentration __attribute__((deprecated("use TXBeautyManager#setFilterStrength instead")));

/**
 * Set green screen video.
 *
 * @deprecated This API is not recommended after v7.2. Please use {@link setGreenScreenFile} API in {@link TXBeautyManager} instead.
 */
- (void)setGreenScreenFile:(NSURL *)file __attribute__((deprecated("use TXBeautyManager#setGreenScreenFile instead")));

/**
 * Set reverb effect.
 *
 * @deprecated This API is not recommended after v7.3. Please use {@link setVoiceReverbType} API in {@link TXAudioEffectManager} instead.
 */
- (void)setReverbType:(TRTCReverbType)reverbType __attribute__((deprecated("use TXAudioEffectManager#setVoiceReverbType instead")));

/**
 * Set voice changing type.
 *
 * @deprecated This API is not recommended after v7.3. Please use {@link setVoiceChangerType} API in {@link TXAudioEffectManager} instead.
 */
- (void)setVoiceChangerType:(TRTCVoiceChangerType)voiceChangerType __attribute__((deprecated("use TXAudioEffectManager#setVoiceChangerType instead")));

/**
 * Enable or disable in-ear monitoring.
 *
 * @deprecated This API is not recommended after v7.3. Please use {@link setVoiceEarMonitor} API in {@link TXAudioEffectManager} instead.
 */
#if TARGET_OS_IPHONE
- (void)enableAudioEarMonitoring:(BOOL)enable __attribute__((deprecated("use TXAudioEffectManager#setVoiceEarMonitor instead")));
#endif

/**
 * Enable volume reminder.
 *
 * @deprecated This API is not recommended after v10.1. Please use {@link enableAudioVolumeEvaluation}(enable, params) instead.
 */
- (void)enableAudioVolumeEvaluation:(NSUInteger)interval __attribute__((deprecated("use enableAudioVolumeEvaluation:withParams: instead")));

/**
 * Enable volume reminder.
 *
 * @deprecated This API is not recommended after v11.2. Please use {@link enableAudioVolumeEvaluation}(enable, params) instead.
 */
- (void)enableAudioVolumeEvaluation:(NSUInteger)interval enable_vad:(BOOL)enable_vad __attribute__((deprecated("use enableAudioVolumeEvaluation:withParams: instead")));

/**
 * Switch camera.
 *
 * @deprecated This API is not recommended after v8.0. Please use the {@link switchCamera} API in {@link TXDeviceManager} instead.
 */
#if TARGET_OS_IPHONE
- (void)switchCamera __attribute__((deprecated("use TXDeviceManager#switchCamera instead")));
#endif

/**
 * Query whether the current camera supports zoom.
 *
 * @deprecated This API is not recommended after v8.0. Please use the {@link isCameraZoomSupported} API in {@link TXDeviceManager} instead.
 */
#if TARGET_OS_IPHONE
- (BOOL)isCameraZoomSupported __attribute__((deprecated("use TXDeviceManager#isCameraZoomSupported instead")));
#endif

/**
 * Set camera zoom ratio (focal length).
 *
 * @deprecated This API is not recommended after v8.0. Please use the {@link setCameraZoomRatio} API in {@link TXDeviceManager} instead.
 */
#if TARGET_OS_IPHONE
- (void)setZoom:(CGFloat)distance __attribute__((deprecated("use TXDeviceManager#setCameraZoomRatio instead")));
#endif

/**
 * Query whether the device supports flash.
 *
 * @deprecated This API is not recommended after v8.0. Please use the {@link isCameraTorchSupported} API in {@link TXDeviceManager} instead.
 */
#if TARGET_OS_IPHONE
- (BOOL)isCameraTorchSupported __attribute__((deprecated("use TXDeviceManager#isCameraTorchSupported instead")));
#endif

/**
 * Enable/Disable flash.
 *
 * @deprecated This API is not recommended after v8.0. Please use the {@link enableCameraTorch} API in {@link TXDeviceManager} instead.
 */
#if TARGET_OS_IPHONE
- (BOOL)enbaleTorch:(BOOL)enable __attribute__((deprecated("use TXDeviceManager#enableCameraTorch instead")));
#endif

/**
 * Query whether the camera supports setting focus.
 *
 * @deprecated This API is not recommended after v8.0.
 */
#if TARGET_OS_IPHONE
- (BOOL)isCameraFocusPositionInPreviewSupported __attribute__((deprecated));
#endif

/**
 * Set the focal position of camera.
 *
 * @deprecated This API is not recommended after v8.0. Please use the {@link setCameraFocusPosition} API in {@link TXDeviceManager} instead.
 */
#if TARGET_OS_IPHONE
- (void)setFocusPosition:(CGPoint)touchPoint __attribute__((deprecated("use TXDeviceManager#setCameraFocusPosition instead")));
#endif

/**
 * Query whether the device supports the automatic recognition of face position.
 *
 * @deprecated This API is not recommended after v8.0. Please use the {@link isAutoFocusEnabled} API in {@link TXDeviceManager} instead.
 */
#if TARGET_OS_IPHONE
- (BOOL)isCameraAutoFocusFaceModeSupported __attribute__((deprecated("use TXDeviceManager#isAutoFocusEnabled instead")));
#endif

/**
 * Enable/Disable face auto focus.
 *
 * @deprecated This API is not recommended after v8.0. Please use the {@link enableCameraAutoFocus} API in {@link TXDeviceManager} instead.
 */
#if TARGET_OS_IPHONE
- (void)enableAutoFaceFoucs:(BOOL)enable __attribute__((deprecated("use TXDeviceManager#enableCameraAutoFocus instead")));
#endif

/**
 * Setting the system volume type (for mobile OS).
 *
 * @deprecated This API is not recommended after v8.0. Please use the {@link startLocalAudio} instead, which param `quality` is used to decide audio quality.
 */
- (void)setSystemVolumeType:(TRTCSystemVolumeType)type __attribute__((deprecated("use startLocalAudio:quality instead")));

/**
 * Screencapture video.
 *
 * @deprecated This API is not recommended after v8.2. Please use {@link snapshotVideo} instead.
 */
- (void)snapshotVideo:(NSString *)userId type:(TRTCVideoStreamType)streamType completionBlock:(void (^)(TXImage *image))completionBlock __attribute__((deprecated("use snapshotVideo:type:sourceType:completionBlock instead")));

/**
 * Start system-level screen sharing (for iOS 11.0 and above only).
 *
 * @deprecated This API is not recommended after v8.6. Please use {@link startScreenCaptureByReplaykit} instead.
 */
- (void)startScreenCaptureByReplaykit:(TRTCVideoEncParam *)encParams appGroup:(NSString *)appGroup __attribute__((deprecated("use startScreenCaptureByReplaykit:encParam:appGroup: instead")));

/**
 * Set sound quality.
 *
 * @deprecated This API is not recommended after v8.0. Please use {@link startLocalAudio}:quality instead.
 */
- (void)startLocalAudio __attribute__((deprecated("use startLocalAudio(quality) instead")));

/**
 * Start displaying remote video image.
 *
 * @deprecated This API is not recommended after v8.0. Please use {@link startRemoteView}:streamType:view: instead.
 */
- (void)startRemoteView:(NSString *)userId view:(TXView *)view __attribute__((deprecated("use startRemoteView:streamType:view: instead")));

/**
 * Stop displaying remote video image and pulling the video data stream of remote user.
 *
 * @deprecated This API is not recommended after v8.0. Please use {@link stopRemoteView}:streamType: instead.
 */
- (void)stopRemoteView:(NSString *)userId __attribute__((deprecated("use stopRemoteView:streamType: instead")));

/**
 * Set the rendering mode of local image.
 *
 * @deprecated This API is not recommended after v8.0. Please use {@link setLocalRenderParams} instead.
 */
- (void)setLocalViewFillMode:(TRTCVideoFillMode)mode __attribute__((deprecated("use setLocalRenderParams instead")));

/**
 * Set the clockwise rotation angle of local image.
 *
 * @deprecated This API is not recommended after v8.0. Please use {@link setLocalRenderParams} instead.
 */
- (void)setLocalViewRotation:(TRTCVideoRotation)rotation __attribute__((deprecated("use setLocalRenderParams instead")));

/**
 * Set the mirror mode of local camera's preview image.
 *
 * @deprecated This API is not recommended after v8.0. Please use {@link setLocalRenderParams} instead.
 */
#if TARGET_OS_IPHONE
- (void)setLocalViewMirror:(TRTCLocalVideoMirrorType)mirror __attribute__((deprecated("use setLocalRenderParams: instead")));
#elif TARGET_OS_MAC
- (void)setLocalViewMirror:(BOOL)mirror __attribute__((deprecated("use setLocalRenderParams: instead")));
#endif

/**
 * Set the fill mode of substream image.
 *
 * @deprecated This API is not recommended after v8.0. Please use {@link setRemoteRenderParams}:streamType:params: instead.
 */
- (void)setRemoteViewFillMode:(NSString *)userId mode:(TRTCVideoFillMode)mode __attribute__((deprecated("use setRemoteRenderParams:streamType:params: instead")));

/**
 * Set the clockwise rotation angle of remote image.
 *
 * @deprecated This API is not recommended after v8.0. Please use {@link setRemoteRenderParams}:streamType:params: instead.
 */
- (void)setRemoteViewRotation:(NSString *)userId rotation:(TRTCVideoRotation)rotation __attribute__((deprecated("use setRemoteRenderParams:streamType:params: instead")));

/**
 * Start displaying the substream image of remote user.
 *
 * @deprecated This API is not recommended after v8.0. Please use {@link startRemoteView}:streamType:view: instead.
 */
- (void)startRemoteSubStreamView:(NSString *)userId view:(TXView *)view __attribute__((deprecated("use startRemoteView:type:view: instead")));

/**
 * Stop displaying the substream image of remote user.
 *
 * @deprecated This API is not recommended after v8.0. Please use {@link stopRemoteView}:streamType: instead.
 */
- (void)stopRemoteSubStreamView:(NSString *)userId __attribute__((deprecated("use stopRemoteView:streamType: instead")));

/**
 * Set the fill mode of substream image.
 *
 * @deprecated This API is not recommended after v8.0. Please use {@link setRemoteRenderParams}:streamType:params: instead.
 */
- (void)setRemoteSubStreamViewFillMode:(NSString *)userId mode:(TRTCVideoFillMode)mode __attribute__((deprecated("use setRemoteRenderParams:streamType:params: instead")));

/**
 * Set the clockwise rotation angle of substream image.
 *
 * @deprecated This API is not recommended after v8.0. Please use {@link setRemoteRenderParams}:streamType:params: instead.
 */
- (void)setRemoteSubStreamViewRotation:(NSString *)userId rotation:(TRTCVideoRotation)rotation __attribute__((deprecated("use setRemoteRenderParams:streamType:params: instead")));

/**
 * Set sound quality.
 *
 * @deprecated This API is not recommended after v8.0. Please use {@link startLocalAudio}:quality instead.
 */
- (void)setAudioQuality:(TRTCAudioQuality)quality __attribute__((deprecated("use startLocalAudio(quality) instead")));

/**
 * Specify whether to view the big or small image.
 *
 * @deprecated This API is not recommended after v8.0. Please use {@link startRemoteView}:streamType:view: instead.
 */
- (void)setPriorRemoteVideoStreamType:(TRTCVideoStreamType)streamType __attribute__((deprecated("use startRemoteView:streamType:view: instead")));

/**
 * Set mic volume.
 *
 * @deprecated This API is not recommended after v6.9. Please use {@link setAudioCaptureVolume} instead.
 */
- (void)setMicVolumeOnMixing:(NSInteger)volume __attribute__((deprecated("use setAudioCaptureVolume instead")));

/**
 * Start background music.
 *
 * @deprecated This API is not recommended after v7.3. Please use {@link startPlayMusic} API in {@link TXAudioEffectManager} instead.
 */
- (void)playBGM:(NSString *)path
       withBeginNotify:(void (^)(NSInteger errCode))beginNotify
    withProgressNotify:(void (^)(NSInteger progressMS, NSInteger durationMS))progressNotify
     andCompleteNotify:(void (^)(NSInteger errCode))completeNotify __attribute__((deprecated("use TXAudioEffectManager#startPlayMusic instead")));

/**
 * Stop background music.
 *
 * @deprecated This API is not recommended after v7.3. Please use {@link stopPlayMusic} API in {@link TXAudioEffectManager} instead.
 */
- (void)stopBGM __attribute__((deprecated("use TXAudioEffectManager#stopPlayMusic instead")));

/**
 * Stop background music.
 *
 * @deprecated This API is not recommended after v7.3. Please use {@link pausePlayMusic} API in {@link TXAudioEffectManager} instead.
 */
- (void)pauseBGM __attribute__((deprecated("use TXAudioEffectManager#pausePlayMusic instead")));

/**
 * Stop background music.
 *
 * @deprecated This API is not recommended after v7.3. Please use {@link resumePlayMusic} API in {@link TXAudioEffectManager} instead.
 */
- (void)resumeBGM __attribute__((deprecated("use TXAudioEffectManager#resumePlayMusic instead")));

/**
 * Get the total length of background music in ms.
 *
 * @deprecated This API is not recommended after v7.3. Please use {@link getMusicDurationInMS} API in {@link TXAudioEffectManager} instead.
 */
- (NSInteger)getBGMDuration:(NSString *)path __attribute__((deprecated("use TXAudioEffectManager#getMusicDurationInMS instead")));

/**
 * Set background music playback progress.
 *
 * @deprecated This API is not recommended after v7.3. Please use {@link seekMusicToPosInMS} API in {@link TXAudioEffectManager} instead.
 */
- (int)setBGMPosition:(NSInteger)pos __attribute__((deprecated("use TXAudioEffectManager#seekMusicToPosInMS instead")));

/**
 * Set background music volume.
 *
 * @deprecated This API is not recommended after v7.3. Please use {@link setMusicVolume} API in {@link TXAudioEffectManager} instead.
 */
- (void)setBGMVolume:(NSInteger)volume __attribute__((deprecated("use TXAudioEffectManager#setMusicVolume instead")));

/**
 * Set the local playback volume of background music.
 *
 * @deprecated This API is not recommended after v7.3. Please use {@link setMusicPlayoutVolume} API in {@link TXAudioEffectManager} instead.
 */
- (void)setBGMPlayoutVolume:(NSInteger)volume __attribute__((deprecated("use TXAudioEffectManager#setMusicPlayoutVolume instead")));

/**
 * Set the remote playback volume of background music.
 *
 * @deprecated This API is not recommended after v7.3. Please use {@link setBGMPublishVolume} API in {@link TXAudioEffectManager} instead.
 */
- (void)setBGMPublishVolume:(NSInteger)volume __attribute__((deprecated("use TXAudioEffectManager#setBGMPublishVolume instead")));

/**
 * Play sound effect.
 *
 * @deprecated This API is not recommended after v7.3. Please use {@link startPlayMusic} API in {@link TXAudioEffectManager} instead.
 */
- (void)playAudioEffect:(TRTCAudioEffectParam *)effect __attribute__((deprecated("use TXAudioEffectManager#startPlayMusic instead")));

/**
 * Set sound effect volume.
 *
 * @deprecated This API is not recommended after v7.3. Please use {@link setMusicPublishVolume} and {@link setMusicPlayoutVolume} API in {@link TXAudioEffectManager} instead.
 */
- (void)setAudioEffectVolume:(int)effectId volume:(int)volume __attribute__((deprecated("use setMusicPublishVolume/setMusicPlayoutVolume instead")));

/**
 * Stop sound effect.
 *
 * @deprecated This API is not recommended after v7.3. Please use {@link stopPlayMusic} API in {@link TXAudioEffectManager} instead.
 */
- (void)stopAudioEffect:(int)effectId __attribute__((deprecated("use TXAudioEffectManager#stopPlayMusic instead")));

/**
 * Stop all sound effects.
 *
 * @deprecated This API is not recommended after v7.3. Please use {@link stopPlayMusic} API in {@link TXAudioEffectManager} instead.
 */
- (void)stopAllAudioEffects __attribute__((deprecated("use TXAudioEffectManager#stopPlayMusic instead")));

/**
 * Set the volume of all sound effects.
 *
 * @deprecated This API is not recommended after v7.3. Please use {@link setMusicPublishVolume} and {@link setMusicPlayoutVolume} API in {@link TXAudioEffectManager} instead.
 */
- (void)setAllAudioEffectsVolume:(int)volume __attribute__((deprecated("use setMusicPublishVolume/setMusicPlayoutVolume instead")));

/**
 * Pause sound effect.
 *
 * @deprecated This API is not recommended after v7.3. Please use {@link pauseAudioEffect} API in {@link TXAudioEffectManager} instead.
 */
- (void)pauseAudioEffect:(int)effectId __attribute__((deprecated("use TXAudioEffectManager#pauseAudioEffect instead")));

/**
 * Pause sound effect.
 *
 * @deprecated This API is not recommended after v7.3. Please use {@link resumePlayMusic} API in {@link TXAudioEffectManager} instead.
 */
- (void)resumeAudioEffect:(int)effectId __attribute__((deprecated("use TXAudioEffectManager#resumePlayMusic instead")));

/**
 * Enable custom video capturing mode.
 *
 * @deprecated This API is not recommended after v8.5. Please use {@link enableCustomVideoCapture} instead.
 */
- (void)enableCustomVideoCapture:(BOOL)enable __attribute__((deprecated("use enableCustomVideoCapture:enable instead")));

/**
 * Deliver captured video data to SDK.
 *
 * @deprecated This API is not recommended after v8.5. Please use {@link sendCustomVideoData} instead.
 */
- (void)sendCustomVideoData:(TRTCVideoFrame *)frame __attribute__((deprecated("use sendCustomVideoData:frame: instead")));

/**
 * Pause/Resume publishing local video stream.
 *
 * @deprecated This API is not recommended after v8.9. Please use {@link muteLocalVideo} (streamType, mute) instead.
 */
- (void)muteLocalVideo:(BOOL)mute __attribute__((deprecated("use muteLocalVideo:streamType:mute: instead")));

/**
 * Pause/Resume subscribing to remote user's video stream.
 *
 * @deprecated This API is not recommended after v8.9. Please use {@link muteRemoteVideoStream} (userId, streamType, mute) instead.
 */
- (void)muteRemoteVideoStream:(NSString *)userId mute:(BOOL)mute __attribute__((deprecated("use muteRemoteVideoStream:userid,streamType:mute: instead")));

/**
 * Start network speed test (used before room entry).
 *
 * @deprecated This API is not recommended after v9.2. Please use {@link startSpeedTest} (params) instead.
 */
- (void)startSpeedTest:(uint32_t)sdkAppId
                userId:(NSString *)userId
               userSig:(NSString *)userSig
            completion:(void (^)(TRTCSpeedTestResult *result, NSInteger completedCount, NSInteger totalCount))completion __attribute__((deprecated("use startSpeedTest: instead")));

/**
 * Start screen sharing.
 *
 * @deprecated This API is not recommended after v7.2. Please use `startScreenCapture:streamType:encParam:` instead.
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)startScreenCapture:(nullable NSView *)view __attribute__((deprecated("use startScreenCapture:streamType:encParam: instead")));
#endif

/**
 * Get the list of cameras.
 *
 * @deprecated This API is not recommended after v8.0. Please use the {@link getDevicesList} API in {@link TXDeviceManager} instead.
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (NSArray<TRTCMediaDeviceInfo *> *)getCameraDevicesList __attribute__((deprecated("use TXDeviceManager#getDevicesList instead")));
#endif

/**
 * Set the camera to be used currently.
 *
 * @deprecated This API is not recommended after v8.0. Please use the {@link setCurrentDevice} API in {@link TXDeviceManager} instead.
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (int)setCurrentCameraDevice:(NSString *)deviceId __attribute__((deprecated("use TXDeviceManager#setCurrentDevice instead")));
#endif

/**
 * Get the currently used camera.
 *
 * @deprecated This API is not recommended after v8.0. Please use the {@link getCurrentDevice} API in {@link TXDeviceManager} instead.
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (TRTCMediaDeviceInfo *)getCurrentCameraDevice __attribute__((deprecated("use TXDeviceManager#getCurrentDevice instead")));
#endif

/**
 * Get the list of mics.
 *
 * @deprecated This API is not recommended after v8.0. Please use the {@link getDevicesList} API in {@link TXDeviceManager} instead.
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (NSArray<TRTCMediaDeviceInfo *> *)getMicDevicesList __attribute__((deprecated("use TXDeviceManager#getDevicesList instead")));
#endif

/**
 * Get the current mic device.
 *
 * @deprecated This API is not recommended after v8.0. Please use the {@link getCurrentDevice} API in {@link TXDeviceManager} instead.
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (TRTCMediaDeviceInfo *)getCurrentMicDevice __attribute__((deprecated("use TXDeviceManager#getCurrentDevice instead")));
#endif

/**
 * Select the currently used mic.
 *
 * @deprecated This API is not recommended after v8.0. Please use the {@link setCurrentDevice} API in {@link TXDeviceManager} instead.
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (int)setCurrentMicDevice:(NSString *)deviceId __attribute__((deprecated("use TXDeviceManager#setCurrentDevice instead")));
#endif

/**
 * Get the current mic volume.
 *
 * @deprecated This API is not recommended after v8.0. Please use the {@link getCurrentDeviceVolume} API in {@link TXDeviceManager} instead.
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (float)getCurrentMicDeviceVolume __attribute__((deprecated("use TXDeviceManager#getCurrentDeviceVolume instead")));
#endif

/**
 * Set the current mic volume.
 *
 * @deprecated This API is not recommended after v8.0. Please use the {@link setCurrentDeviceVolume} API in {@link TXDeviceManager} instead.
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)setCurrentMicDeviceVolume:(NSInteger)volume __attribute__((deprecated("use TXDeviceManager#setCurrentDeviceVolume instead")));
#endif

/**
 * Set the mute status of the current system mic.
 *
 * @deprecated This API is not recommended after v8.0. Please use the {@link setCurrentDeviceMute} API in {@link TXDeviceManager} instead.
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)setCurrentMicDeviceMute:(BOOL)mute __attribute__((deprecated("use TXDeviceManager#setCurrentDeviceMute instead")));
#endif

/**
 * Get the mute status of the current system mic.
 *
 * @deprecated This API is not recommended after v8.0. Please use the {@link getCurrentDeviceMute} API in {@link TXDeviceManager} instead.
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (BOOL)getCurrentMicDeviceMute __attribute__((deprecated("use TXDeviceManager#getCurrentDeviceMute instead")));
#endif

/**
 * Get the list of speakers.
 *
 * @deprecated This API is not recommended after v8.0. Please use the {@link getDevicesList} API in {@link TXDeviceManager} instead.
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (NSArray<TRTCMediaDeviceInfo *> *)getSpeakerDevicesList __attribute__((deprecated("use TXDeviceManager#getDevicesList instead")));
#endif

/**
 * Get the currently used speaker.
 *
 * @deprecated This API is not recommended after v8.0. Please use the {@link getCurrentDevice} API in {@link TXDeviceManager} instead.
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (TRTCMediaDeviceInfo *)getCurrentSpeakerDevice __attribute__((deprecated("use TXDeviceManager#getCurrentDevice instead")));
#endif

/**
 * Set the speaker to use.
 *
 * @deprecated This API is not recommended after v8.0. Please use the {@link setCurrentDevice} API in {@link TXDeviceManager} instead.
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (int)setCurrentSpeakerDevice:(NSString *)deviceId __attribute__((deprecated("use TXDeviceManager#setCurrentDevice instead")));
#endif

/**
 * Get the current speaker volume.
 *
 * @deprecated This API is not recommended after v8.0. Please use the {@link getCurrentDeviceVolume} API in {@link TXDeviceManager} instead.
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (float)getCurrentSpeakerDeviceVolume __attribute__((deprecated("use TXDeviceManager#getCurrentDeviceVolume instead")));
#endif

/**
 * Set the current speaker volume.
 *
 * @deprecated This API is not recommended after v8.0. Please use the {@link setCurrentDeviceVolume} API in {@link TXDeviceManager} instead.
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (int)setCurrentSpeakerDeviceVolume:(NSInteger)volume __attribute__((deprecated("use TXDeviceManager#setCurrentDeviceVolume instead")));
#endif

/**
 * Get the mute status of the current system speaker.
 *
 * @deprecated This API is not recommended after v8.0. Please use the {@link getCurrentDeviceMute} API in {@link TXDeviceManager} instead.
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (BOOL)getCurrentSpeakerDeviceMute __attribute__((deprecated("use TXDeviceManager#getCurrentDeviceMute instead")));
#endif

/**
 * Set whether to mute the current system speaker.
 *
 * @deprecated This API is not recommended after v8.0. Please use the {@link setCurrentDeviceMute} API in {@link TXDeviceManager} instead.
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)setCurrentSpeakerDeviceMute:(BOOL)mute __attribute__((deprecated("use TXDeviceManager#setCurrentDeviceMute instead")));
#endif

/**
 * Start camera test.
 *
 * @deprecated This API is not recommended after v8.0. Please use the {@link startCameraDeviceTest} API in {@link TXDeviceManager} instead.
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)startCameraDeviceTestInView:(NSView *)view __attribute__((deprecated("use TXDeviceManager#startCameraDeviceTest instead")));
#endif

/**
 * Start camera test.
 *
 * @deprecated This API is not recommended after v8.0. Please use the {@link stopCameraDeviceTest} API in {@link TXDeviceManager} instead.
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)stopCameraDeviceTest __attribute__((deprecated("use TXDeviceManager#stopCameraDeviceTest instead")));
#endif

/**
 * Start mic test.
 *
 * @deprecated This API is not recommended after v8.0. Please use the {@link startMicDeviceTest} API in {@link TXDeviceManager} instead.
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)startMicDeviceTest:(NSInteger)interval testEcho:(void (^)(NSInteger volume))testEcho __attribute__((deprecated("use TXDeviceManager#startMicDeviceTest instead")));
#endif

/**
 * Start mic test.
 *
 * @deprecated This API is not recommended after v8.0. Please use the {@link stopMicDeviceTest} API in {@link TXDeviceManager} instead.
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)stopMicDeviceTest __attribute__((deprecated("use TXDeviceManager#stopMicDeviceTest instead")));
#endif

/**
 * Start speaker test.
 *
 * @deprecated This API is not recommended after v8.0. Please use the {@link startSpeakerDeviceTest} API in {@link TXDeviceManager} instead.
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)startSpeakerDeviceTest:(NSString *)audioFilePath onVolumeChanged:(void (^)(NSInteger volume, BOOL isLastFrame))volumeBlock __attribute__((deprecated("use TXDeviceManager#startSpeakerDeviceTest instead")));
#endif

/**
 * Stop speaker test.
 *
 * @deprecated This API is not recommended after v8.0. Please use the {@link stopSpeakerDeviceTest} API in {@link TXDeviceManager} instead.
 */
#if !TARGET_OS_IPHONE && TARGET_OS_MAC
- (void)stopSpeakerDeviceTest __attribute__((deprecated("use TXDeviceManager#stopSpeakerDeviceTest instead")));
#endif

/**
 * start in-app screen sharing (for iOS 13.0 and above only).
 *
 * @deprecated This API is not recommended after v8.6. Please use {@link startScreenCaptureInApp} instead.
 */
- (void)startScreenCaptureInApp:(TRTCVideoEncParam *)encParams __attribute__((deprecated("use startScreenCaptureInApp:encParam: instead")));

/**
 * Set the direction of image output by video encoder.
 *
 * @deprecated It is deprecated starting from v11.7.
 */
- (void)setVideoEncoderRotation:(TRTCVideoRotation)rotation __attribute__((deprecated("no use")));

/**
 * Set the mirror mode of image output by encoder.
 *
 * @deprecated It is deprecated starting from v11.7.
 */
- (void)setVideoEncoderMirror:(BOOL)mirror __attribute__((deprecated("no use")));

/**
 * Set the adaptation mode of G-sensor.
 *
 * @deprecated It is deprecated starting from v11.7. It is recommended to use the {@link setGravitySensorAdaptiveMode} interface instead.
 */
- (void)setGSensorMode:(TRTCGSensorMode)mode __attribute__((deprecated("use setGravitySensorAdaptiveMode: instead")));

/**
 * Start publishing audio/video streams to Tencent Cloud CSS CDN.
 *
 * @deprecated It is deprecated starting from v12.0. Please use {@link startPublishMediaStream} instead.
 */
- (void)startPublishing:(NSString *)streamId type:(TRTCVideoStreamType)streamType __attribute__((deprecated("use startPublishMediaStream instead")));

/**
 * Stop publishing audio/video streams to Tencent Cloud CSS CDN.
 *
 * @deprecated It is deprecated starting from v12.0. Please use {@link stopPublishMediaStream} instead.
 */
- (void)stopPublishing __attribute__((deprecated("use stopPublishMediaStream instead")));

/**
 * Start publishing audio/video streams to non-Tencent Cloud CDN.
 *
 * @deprecated It is deprecated starting from v12.0. Please use {@link startPublishMediaStream} instead.
 */
- (void)startPublishCDNStream:(TRTCPublishCDNParam *)param __attribute__((deprecated("use startPublishMediaStream instead")));

/**
 * Stop publishing audio/video streams to non-Tencent Cloud CDN.
 *
 * @deprecated It is deprecated starting from v12.0. Please use {@link stopPublishMediaStream} instead.
 */
- (void)stopPublishCDNStream __attribute__((deprecated("use stopPublishMediaStream instead")));

/**
 * Set the layout and transcoding parameters of On-Cloud MixTranscoding.
 *
 * @deprecated It is deprecated starting from v12.0. Please use {@link startPublishMediaStream}， {@link updatePublishMediaStream} and {@link stopPublishMediaStream} instead.
 */
- (void)setMixTranscodingConfig:(nullable TRTCTranscodingConfig *)config __attribute__((deprecated("use startPublishMediaStream, updatePublishMediaStream and stopPublishMediaStream instead")));

@end
NS_ASSUME_NONNULL_END
