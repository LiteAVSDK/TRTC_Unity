/**
 * Copyright (c) 2021 Tencent. All rights reserved.
 * Module: beauty filter and image processing parameter configurations
 * Function: you can modify parameters such as beautification, filter, and green screen
 */
#ifndef __ITXBEAUTYMANAGER_H__
#define __ITXBEAUTYMANAGER_H__

#include <stdint.h>
#ifdef __APPLE__
#include <TargetConditionals.h>
#endif

namespace liteav {

/**
 * 5.20 Structure for Image
 */
struct TXImageBuffer {
    /// image content in BGRA format
    const char* buffer;

    /// buffer size
    uint32_t length;

    /// image width
    uint32_t width;

    /// image height
    uint32_t height;

    TXImageBuffer() : buffer(nullptr), length(0), width(0), height(0) {
    }
};

/**
 * Beauty (skin smoothing) filter algorithm.
 *
 * TRTC has multiple built-in skin smoothing algorithms. You can select the one most suitable for your product needs.
 */
enum TXBeautyStyle {

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

class ITXBeautyManager {
   protected:
    ITXBeautyManager() {
    }
    virtual ~ITXBeautyManager() {
    }

   public:
    /**
     * Sets the beauty (skin smoothing) filter algorithm.
     *
     * TRTC has multiple built-in skin smoothing algorithms. You can select the one most suitable for your product needs:
     * @param beautyStyle Beauty filter style. `TXBeautyStyleSmooth`: smooth; `TXBeautyStyleNature`: natural; `TXBeautyStylePitu`: Pitu
     */
    virtual void setBeautyStyle(TXBeautyStyle beautyStyle) = 0;

    /**
     * Sets the strength of the beauty filter.
     *
     * @param beautyLevel Strength of the beauty filter. Value range: [0, 9]. `0` indicates to disable the filter, and `9` indicates the most obvious effect.
     */
    virtual void setBeautyLevel(float beautyLevel) = 0;

    /**
     * Sets the strength of the brightening filter.
     *
     * @param whitenessLevel Strength of the brightening filter. Value range: [0, 9]. `0` indicates to disable the filter, and `9` indicates the most obvious effect.
     */
    virtual void setWhitenessLevel(float whitenessLevel) = 0;

    /**
     * Sets the strength of the rosy skin filter.
     *
     * @param ruddyLevel Strength of the rosy skin filter. Value range: [0, 9]. `0` indicates to disable the filter, and `9` indicates the most obvious effect.
     */
    virtual void setRuddyLevel(float ruddyLevel) = 0;

    /**
     * Sets color filter.
     *
     * The color filter is a color lookup table image containing color mapping relationships. You can find several predefined filter images in the official demo we provide.
     * The SDK performs secondary processing on the original video image captured by the camera according to the mapping relationships in the lookup table to achieve the expected filter effect.
     * @param image Color lookup table containing color mapping relationships. The image must be in PNG format.
     */
    virtual void setFilter(TXImageBuffer* image) = 0;

    /**
     * Sets the strength of color filter.
     *
     * The larger this value, the more obvious the effect of the color filter, and the greater the color difference between the video image processed by the filter and the original video image.
     * The default strength is 0.5, and if it is not sufficient, it can be adjusted to a value above 0.5. The maximum value is 1.
     * @param strength Value range: [0, 1]. The greater the value, the more obvious the effect. Default value: 0.5
     */
    virtual void setFilterStrength(float strength) = 0;
};
}  // namespace liteav
#ifdef _WIN32
using namespace liteav;
#endif
#endif
