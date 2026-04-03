/**
 * Copyright (c) 2021 Tencent. All rights reserved.
 * Module: beauty filter and image processing parameter configurations
 * Function: you can modify parameters such as beautification, filter, and green screen
 */
#import <Foundation/Foundation.h>
#import <TargetConditionals.h>
#import "TXLiteAVSymbolExport.h"
#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
typedef UIImage TXImage;
#else
#import <AppKit/AppKit.h>
typedef NSImage TXImage;
#endif

NS_ASSUME_NONNULL_BEGIN

/**
 * Beauty (skin smoothing) filter algorithm.
 *
 * TRTC has multiple built-in skin smoothing algorithms. You can select the one most suitable for your product needs.
 */
typedef NS_ENUM(NSInteger, TXBeautyStyle) {

    /// Smooth style, which uses a more radical algorithm for more obvious effect and is suitable for show live streaming.
    TXBeautyStyleSmooth = 0,

    /// Natural style, which retains more facial details for more natural effect and is suitable for most live streaming use cases.
    TXBeautyStyleNature = 1,

    /// Pitu style, which is provided by YouTu Lab. Its skin smoothing effect is between the smooth style and the natural style, that is, it retains more skin details than the smooth style and has a higher skin smoothing degree than the natural
    /// style.
    TXBeautyStylePitu = 2
};

/////////////////////////////////////////////////////////////////////////////////
//
//                    beauty interface
//
/////////////////////////////////////////////////////////////////////////////////

LITEAV_EXPORT @interface TXBeautyManager : NSObject

/**
 * Sets the beauty (skin smoothing) filter algorithm.
 *
 * TRTC has multiple built-in skin smoothing algorithms. You can select the one most suitable for your product needs:
 * @param beautyStyle Beauty filter style. `TXBeautyStyleSmooth`: smooth; `TXBeautyStyleNature`: natural; `TXBeautyStylePitu`: Pitu
 */
- (void)setBeautyStyle:(TXBeautyStyle)beautyStyle;

/**
 * Sets the strength of the beauty filter.
 *
 * @param beautyLevel Strength of the beauty filter. Value range: [0, 9]. `0` indicates to disable the filter, and `9` indicates the most obvious effect.
 */
- (void)setBeautyLevel:(float)beautyLevel;

/**
 * Sets the strength of the brightening filter.
 *
 * @param whitenessLevel Strength of the brightening filter. Value range: [0, 9]. `0` indicates to disable the filter, and `9` indicates the most obvious effect.
 */
- (void)setWhitenessLevel:(float)whitenessLevel;

/**
 * Enables clarity enhancement.
 */
- (void)enableSharpnessEnhancement:(BOOL)enable;

/**
 * Sets the strength of the rosy skin filter.
 *
 * @param ruddyLevel Strength of the rosy skin filter. Value range: [0, 9]. `0` indicates to disable the filter, and `9` indicates the most obvious effect.
 */
- (void)setRuddyLevel:(float)ruddyLevel;

/**
 * Sets color filter.
 *
 * The color filter is a color lookup table image containing color mapping relationships. You can find several predefined filter images in the official demo we provide.
 * The SDK performs secondary processing on the original video image captured by the camera according to the mapping relationships in the lookup table to achieve the expected filter effect.
 * @param image Color lookup table containing color mapping relationships. The image must be in PNG format.
 */
- (void)setFilter:(nullable TXImage *)image;

/**
 * Sets the strength of color filter.
 *
 * The larger this value, the more obvious the effect of the color filter, and the greater the color difference between the video image processed by the filter and the original video image.
 * The default strength is 0.5, and if it is not sufficient, it can be adjusted to a value above 0.5. The maximum value is 1.
 * @param strength Value range: [0, 1]. The greater the value, the more obvious the effect. Default value: 0.5
 */
- (void)setFilterStrength:(float)strength;

/**
 * Sets green screen video.
 *
 * This interface is only available in the enterprise version SDK (the old version has been offline, if you need to use the advanced beauty function in the new version SDK, please refer to [Tencent Beauty Effect
 * SDK](https://www.tencentcloud.com/document/product/1143/53942)) in effect. The green screen feature enabled by this API is not capable of intelligent keying. It requires that there be a green screen behind the videoed person or object for further
 * chroma keying.
 * @param path Path of the video file in MP4 format. An empty value indicates to disable the effect.
 * @return 0: Success; -5: feature of license not supported.
 */
- (int)setGreenScreenFile:(nullable NSString *)path;

/**
 * Sets the strength of the eye enlarging filter.
 *
 * This interface is only available in the enterprise version SDK (the old version has been offline, if you need to use the advanced beauty function in the new version SDK, please refer to [Tencent Beauty Effect
 * SDK](https://www.tencentcloud.com/document/product/1143/53942)) in effect.
 * @param eyeScaleLevel Strength of the eye enlarging filter. Value range: [0, 9]. `0` indicates to disable the filter, and `9` indicates the most obvious effect.
 * @return 0: Success; -5: feature of license not supported.
 */
#if TARGET_OS_IPHONE
- (int)setEyeScaleLevel:(float)eyeScaleLevel;
#endif

/**
 * Sets the strength of the face slimming filter.
 *
 * This interface is only available in the enterprise version SDK (the old version has been offline, if you need to use the advanced beauty function in the new version SDK, please refer to [Tencent Beauty Effect
 * SDK](https://www.tencentcloud.com/document/product/1143/53942)) in effect.
 * @param faceSlimLevel Strength of the face slimming filter. Value range: [0, 9]. `0` indicates to disable the filter, and `9` indicates the most obvious effect.
 * @return 0: Success; -5: feature of license not supported.
 */
#if TARGET_OS_IPHONE
- (int)setFaceSlimLevel:(float)faceSlimLevel;
#endif

/**
 * Sets the strength of the chin slimming filter.
 *
 * This interface is only available in the enterprise version SDK (the old version has been offline, if you need to use the advanced beauty function in the new version SDK, please refer to [Tencent Beauty Effect
 * SDK](https://www.tencentcloud.com/document/product/1143/53942)) in effect.
 * @param faceVLevel Strength of the chin slimming filter. Value range: [0, 9]. `0` indicates to disable the filter, and `9` indicates the most obvious effect.
 * @return 0: Success; -5: feature of license not supported.
 */
#if TARGET_OS_IPHONE
- (int)setFaceVLevel:(float)faceVLevel;
#endif

/**
 * Sets the strength of the chin lengthening/shortening filter.
 *
 * This interface is only available in the enterprise version SDK (the old version has been offline, if you need to use the advanced beauty function in the new version SDK, please refer to [Tencent Beauty Effect
 * SDK](https://www.tencentcloud.com/document/product/1143/53942)) in effect.
 * @param chinLevel Strength of the chin lengthening/shortening filter. Value range: [-9, 9]. `0` indicates to disable the filter, a value smaller than 0 indicates that the chin is shortened, and a value greater than 0 indicates that the chin is
 * lengthened.
 * @return 0: Success; -5: feature of license not supported.
 */
#if TARGET_OS_IPHONE
- (int)setChinLevel:(float)chinLevel;
#endif

/**
 * Sets the strength of the face shortening filter.
 *
 * This interface is only available in the enterprise version SDK (the old version has been offline, if you need to use the advanced beauty function in the new version SDK, please refer to [Tencent Beauty Effect
 * SDK](https://www.tencentcloud.com/document/product/1143/53942)) in effect.
 * @param faceShortLevel Strength of the face shortening filter. Value range: [0, 9]. `0` indicates to disable the filter, and `9` indicates the most obvious effect.
 * @return 0: Success; -5: feature of license not supported.
 */
#if TARGET_OS_IPHONE
- (int)setFaceShortLevel:(float)faceShortLevel;
#endif

/**
 * Sets the strength of the face narrowing filter.
 *
 * This interface is only available in the enterprise version SDK (the old version has been offline, if you need to use the advanced beauty function in the new version SDK, please refer to [Tencent Beauty Effect
 * SDK](https://www.tencentcloud.com/document/product/1143/53942)) in effect.
 * @param level Strength of the face narrowing filter. Value range: [0, 9]. `0` indicates to disable the filter, and `9` indicates the most obvious effect.
 * @return 0: Success; -5: feature of license not supported.
 */
#if TARGET_OS_IPHONE
- (int)setFaceNarrowLevel:(float)faceNarrowLevel;
#endif

/**
 * Sets the strength of the nose slimming filter.
 *
 * This interface is only available in the enterprise version SDK (the old version has been offline, if you need to use the advanced beauty function in the new version SDK, please refer to [Tencent Beauty Effect
 * SDK](https://www.tencentcloud.com/document/product/1143/53942)) in effect.
 * @param noseSlimLevel Strength of the nose slimming filter. Value range: [0, 9]. `0` indicates to disable the filter, and `9` indicates the most obvious effect.
 * @return 0: Success; -5: feature of license not supported.
 */
#if TARGET_OS_IPHONE
- (int)setNoseSlimLevel:(float)noseSlimLevel;
#endif

/**
 * Sets the strength of the eye brightening filter.
 *
 * This interface is only available in the enterprise version SDK (the old version has been offline, if you need to use the advanced beauty function in the new version SDK, please refer to [Tencent Beauty Effect
 * SDK](https://www.tencentcloud.com/document/product/1143/53942)) in effect.
 * @param eyeLightenLevel Strength of the eye brightening filter. Value range: [0, 9]. `0` indicates to disable the filter, and `9` indicates the most obvious effect.
 * @return 0: Success; -5: feature of license not supported.
 */
#if TARGET_OS_IPHONE
- (int)setEyeLightenLevel:(float)eyeLightenLevel;
#endif

/**
 * Sets the strength of the teeth whitening filter.
 *
 * This interface is only available in the enterprise version SDK (the old version has been offline, if you need to use the advanced beauty function in the new version SDK, please refer to [Tencent Beauty Effect
 * SDK](https://www.tencentcloud.com/document/product/1143/53942)) in effect.
 * @param toothWhitenLevel Strength of the teeth whitening filter. Value range: [0, 9]. `0` indicates to disable the filter, and `9` indicates the most obvious effect.
 * @return 0: Success; -5: feature of license not supported.
 */
#if TARGET_OS_IPHONE
- (int)setToothWhitenLevel:(float)toothWhitenLevel;
#endif

/**
 * Sets the strength of the wrinkle removal filter.
 *
 * This interface is only available in the enterprise version SDK (the old version has been offline, if you need to use the advanced beauty function in the new version SDK, please refer to [Tencent Beauty Effect
 * SDK](https://www.tencentcloud.com/document/product/1143/53942)) in effect.
 * @param wrinkleRemoveLevel Strength of the wrinkle removal filter. Value range: [0, 9]. `0` indicates to disable the filter, and `9` indicates the most obvious effect.
 * @return 0: Success; -5: feature of license not supported.
 */
#if TARGET_OS_IPHONE
- (int)setWrinkleRemoveLevel:(float)wrinkleRemoveLevel;
#endif

/**
 * Sets the strength of the eye bag removal filter.
 *
 * This interface is only available in the enterprise version SDK (the old version has been offline, if you need to use the advanced beauty function in the new version SDK, please refer to [Tencent Beauty Effect
 * SDK](https://www.tencentcloud.com/document/product/1143/53942)) in effect.
 * @param pounchRemoveLevel Strength of the eye bag removal filter. Value range: [0, 9]. `0` indicates to disable the filter, and `9` indicates the most obvious effect.
 * @return 0: Success; -5: feature of license not supported.
 */
#if TARGET_OS_IPHONE
- (int)setPounchRemoveLevel:(float)pounchRemoveLevel;
#endif

/**
 * Sets the strength of the smile line removal filter.
 *
 * This interface is only available in the enterprise version SDK (the old version has been offline, if you need to use the advanced beauty function in the new version SDK, please refer to [Tencent Beauty Effect
 * SDK](https://www.tencentcloud.com/document/product/1143/53942)) in effect.
 * @param smileLinesRemoveLevel Strength of the smile line removal filter. Value range: [0, 9]. `0` indicates to disable the filter, and `9` indicates the most obvious effect.
 * @return 0: Success; -5: feature of license not supported.
 */
#if TARGET_OS_IPHONE
- (int)setSmileLinesRemoveLevel:(float)smileLinesRemoveLevel;
#endif

/**
 * Sets the strength of the hairline adjustment filter.
 *
 * This interface is only available in the enterprise version SDK (the old version has been offline, if you need to use the advanced beauty function in the new version SDK, please refer to [Tencent Beauty Effect
 * SDK](https://www.tencentcloud.com/document/product/1143/53942)) in effect.
 * @param foreheadLevel Strength of the hairline adjustment filter. Value range: [-9, 9]. `0` indicates to disable the filter, and `9` indicates the most obvious effect.
 * @return 0: Success; -5: feature of license not supported.
 */
#if TARGET_OS_IPHONE
- (int)setForeheadLevel:(float)foreheadLevel;
#endif

/**
 * Sets the strength of the eye distance adjustment filter.
 *
 * This interface is only available in the enterprise version SDK (the old version has been offline, if you need to use the advanced beauty function in the new version SDK, please refer to [Tencent Beauty Effect
 * SDK](https://www.tencentcloud.com/document/product/1143/53942)) in effect.
 * @param eyeDistanceLevel Strength of the eye distance adjustment filter. Value range: [-9, 9]. `0` indicates to disable the filter, a value smaller than 0 indicates to widen, and a value greater than 0 indicates to narrow.
 * @return 0: Success; -5: feature of license not supported.
 */
#if TARGET_OS_IPHONE
- (int)setEyeDistanceLevel:(float)eyeDistanceLevel;
#endif

/**
 * Sets the strength of the eye corner adjustment filter.
 *
 * This interface is only available in the enterprise version SDK (the old version has been offline, if you need to use the advanced beauty function in the new version SDK, please refer to [Tencent Beauty Effect
 * SDK](https://www.tencentcloud.com/document/product/1143/53942)) in effect.
 * @param eyeAngleLevel Strength of the eye corner adjustment filter. Value range: [-9, 9]. `0` indicates to disable the filter, and `9` indicates the most obvious effect.
 * @return 0: Success; -5: feature of license not supported.
 */
#if TARGET_OS_IPHONE
- (int)setEyeAngleLevel:(float)eyeAngleLevel;
#endif

/**
 * Sets the strength of the mouth shape adjustment filter.
 *
 * This interface is only available in the enterprise version SDK (the old version has been offline, if you need to use the advanced beauty function in the new version SDK, please refer to [Tencent Beauty Effect
 * SDK](https://www.tencentcloud.com/document/product/1143/53942)) in effect.
 * @param mouthShapeLevel Strength of the mouth shape adjustment filter. Value range: [-9, 9]. `0` indicates to disable the filter, a value smaller than 0 indicates to widen, and a value greater than 0 indicates to narrow.
 * @return 0: Success; -5: feature of license not supported.
 */
#if TARGET_OS_IPHONE
- (int)setMouthShapeLevel:(float)mouthShapeLevel;
#endif

/**
 * Sets the strength of the nose wing narrowing filter.
 *
 * This interface is only available in the enterprise version SDK (the old version has been offline, if you need to use the advanced beauty function in the new version SDK, please refer to [Tencent Beauty Effect
 * SDK](https://www.tencentcloud.com/document/product/1143/53942)) in effect.
 * @param noseWingLevel Strength of the nose wing adjustment filter. Value range: [-9, 9]. `0` indicates to disable the filter, a value smaller than 0 indicates to widen, and a value greater than 0 indicates to narrow.
 * @return 0: Success; -5: feature of license not supported.
 */
#if TARGET_OS_IPHONE
- (int)setNoseWingLevel:(float)noseWingLevel;
#endif

/**
 * Sets the strength of the nose position adjustment filter.
 *
 * This interface is only available in the enterprise version SDK (the old version has been offline, if you need to use the advanced beauty function in the new version SDK, please refer to [Tencent Beauty Effect
 * SDK](https://www.tencentcloud.com/document/product/1143/53942)) in effect.
 * @param nosePositionLevel Strength of the nose position adjustment filter. Value range: [-9, 9]. `0` indicates to disable the filter, a value smaller than 0 indicates to lift, and a value greater than 0 indicates to lower.
 * @return 0: Success; -5: feature of license not supported.
 */
#if TARGET_OS_IPHONE
- (int)setNosePositionLevel:(float)nosePositionLevel;
#endif

/**
 * Sets the strength of the lip thickness adjustment filter.
 *
 * This interface is only available in the enterprise version SDK (the old version has been offline, if you need to use the advanced beauty function in the new version SDK, please refer to [Tencent Beauty Effect
 * SDK](https://www.tencentcloud.com/document/product/1143/53942)) in effect.
 * @param lipsThicknessLevel Strength of the lip thickness adjustment filter. Value range: [-9, 9]. `0` indicates to disable the filter, a value smaller than 0 indicates to thicken, and a value greater than 0 indicates to thin.
 * @return 0: Success; -5: feature of license not supported.
 */
#if TARGET_OS_IPHONE
- (int)setLipsThicknessLevel:(float)lipsThicknessLevel;
#endif

/**
 * Sets the strength of the face shape adjustment filter.
 *
 * This interface is only available in the enterprise version SDK (the old version has been offline, if you need to use the advanced beauty function in the new version SDK, please refer to [Tencent Beauty Effect
 * SDK](https://www.tencentcloud.com/document/product/1143/53942)) in effect.
 * @param   faceBeautyLevel Strength of the face shape adjustment filter. Value range: [0, 9]. `0` indicates to disable the filter, and the greater the value, the more obvious the effect.
 * @return 0: Success; -5: feature of license not supported.
 */
#if TARGET_OS_IPHONE
- (int)setFaceBeautyLevel:(float)faceBeautyLevel;
#endif

/**
 * Selects the AI animated effect pendant.
 *
 * This interface is only available in the enterprise version SDK (the old version has been offline, if you need to use the advanced beauty function in the new version SDK, please refer to [Tencent Beauty Effect
 * SDK](https://www.tencentcloud.com/document/product/1143/53942)) in effect.
 * @param tmplName Animated effect pendant name
 * @param tmplDir Directory of the animated effect material file
 */
#if TARGET_OS_IPHONE
- (void)setMotionTmpl:(nullable NSString *)tmplName inDir:(nullable NSString *)tmplDir;
#endif

/**
 * Sets whether to mute during animated effect playback.
 *
 * This interface is only available in the enterprise version SDK (the old version has been offline, if you need to use the advanced beauty function in the new version SDK, please refer to [Tencent Beauty Effect
 * SDK](https://www.tencentcloud.com/document/product/1143/53942)) in effect. Some animated effects have audio effects, which can be disabled through this API when they are played back.
 * @param motionMute `$YES$`: mute; `$NO$`: unmute
 */
#if TARGET_OS_IPHONE
- (void)setMotionMute:(BOOL)motionMute;
#endif

@end
NS_ASSUME_NONNULL_END
