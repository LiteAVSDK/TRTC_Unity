//  Copyright © 2021 Tencent. All rights reserved.

#import <Foundation/Foundation.h>
#import "TXLiteAVSymbolExport.h"

/**
 * The definition of player type
 */
typedef NS_ENUM(NSInteger, TX_VOD_MEDIA_TRACK_TYPE) {

    /// Unknown
    TX_VOD_MEDIA_TRACK_TYPE_UNKNOW = 0,

    /// Video Track
    TX_VOD_MEDIA_TRACK_TYPE_VIDEO = 1,

    /// Audio Track
    TX_VOD_MEDIA_TRACK_TYPE_AUDIO = 2,

    /// Subtitle Track
    TX_VOD_MEDIA_TRACK_TYPE_SUBTITLE = 3,
};

NS_ASSUME_NONNULL_BEGIN

LITEAV_EXPORT @interface TXTrackInfo : NSObject

/**
 * Track info
 */
@property(nonatomic, assign) TX_VOD_MEDIA_TRACK_TYPE trackType;

/**
 * Track index
 */
@property(nonatomic, assign) int trackIndex;

/**
 * Track name
 */
@property(nonatomic, copy) NSString *name;

/**
 * Track language
 */
@property(nonatomic, copy) NSString *language;

/**
 * Whether the current track is selected
 */
@property(nonatomic, assign) bool isSelected;

/**
 * If it is Yes, only one track of this type can be selected at each moment. If it is NO, multiple tracks of this type can be selected at the same time.
 */
@property(nonatomic, assign) bool isExclusive;

/**
 * Whether the current track is the internal original track
 */
@property(nonatomic, assign) bool isInternal;

/**
 * Get track index
 *
 * @return  Return the track index
 */
- (int)getTrackIndex;

/**
 * Get the type of track
 *
 * @return Return the type of track
 */
- (TX_VOD_MEDIA_TRACK_TYPE)getTrackType;

/**
 * Get the name of the track
 *
 * @return Return the name of the track
 */
- (NSString *)getTrackName;

/**
 * Whether the tracks are the same
 *
 * @param trackInfo  orbital objects to compare
 * @return  If YES, it means same, NO means different
 */
- (bool)isEqual:(TXTrackInfo *)trackInfo;

@end

NS_ASSUME_NONNULL_END
