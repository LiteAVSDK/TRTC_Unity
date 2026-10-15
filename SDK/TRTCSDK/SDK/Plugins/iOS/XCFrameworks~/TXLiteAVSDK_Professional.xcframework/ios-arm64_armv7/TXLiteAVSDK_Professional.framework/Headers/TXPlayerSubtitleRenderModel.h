//  Copyright © 2021 Tencent. All rights reserved.

#import <Foundation/Foundation.h>
#import "TXLiteAVSymbolExport.h"

LITEAV_EXPORT @interface TXPlayerSubtitleRenderModel : NSObject

@property(nonatomic, assign) int canvasWidth;
@property(nonatomic, assign) int canvasHeight;

@property(nonatomic, copy) NSString *familyName;

@property(nonatomic, assign) float fontSize;

@property(nonatomic, assign) float fontScale;

@property(nonatomic, assign) uint32_t fontColor;

@property(nonatomic, assign) float outlineWidth;

@property(nonatomic, assign) uint32_t outlineColor;

@property(nonatomic, assign) BOOL isBondFontStyle;

@property(nonatomic, assign) float lineSpace;

/**
 * The following startMargin, endMargin and yMargin define the drawing area of the subtitle. If not set, the settings in the subtitle file are used. If the subtitle file is not defined, the default is used.
 * Note: Once startMargin, endMargin and yMargin are set, and the subtitle file also defines one or more of these parameters, the corresponding parameters in the subtitle file will be overwritten.
 * The following diagram depicts the meaning of these parameters in the horizontal writing direction, please use the comments of each parameter to understand
 *   \--------------------------------------------------------------------------------------------
 * |                                                                                                                |
 * |                                                                                                                |
 * |                                                                                                                |
 * |                                ________________________                                |
 * |----- startMargin -----|       This is subtitle text          |------endMargin-----  |
 * |                                |_______________________|                                 |
 * |                                                         | yMargin                                         |
 *   \--------------------------------------------------------------------------------------------
 * The margin along the direction of the subtitle text has different meanings according to different writing directions.
 * startMargin is a ratio value in the range [0, 1], that is, the ratio relative to the video screen size.
 * For the horizontal writing direction, startMargin indicates the distance from the left side of the subtitle to the left side of the video screen. For example, if startMargin=0.05, the margin is 0.05 times (5%) of the video width.
 * For the vertical writing direction (regardless of right to left or left to right), startMargin indicates the distance between the top of the subtitle and the top of the video screen. For example, if startMargin=0.05, the margin is 0.05 times the
 * height of the video (5%). If startMargin is set, paramFlags must be set to TXPlayerSubtitleRenderParamFlagStartMargin.
 */
@property(nonatomic, assign) float startMargin;

@property(nonatomic, assign) float endMargin;

@property(nonatomic, assign) float verticalMargin;

@end
