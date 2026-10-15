//  Copyright © 2023 Tencent. All rights reserved.

#import <Foundation/Foundation.h>
#import "TXLiteAVSymbolExport.h"

/**
 * Subtitle callback data
 */
LITEAV_EXPORT @interface TXVodSubtitleData : NSObject

/// Subtitle content
@property(nonatomic, copy) NSString *subtitleData;

/// Subtitle duration, in milliseconds
@property(nonatomic, assign) int64_t durationMs;

/// Subtitle start time, which is the position of the video, in milliseconds
@property(nonatomic, assign) int64_t startPositionMs;

/// TrackIndex of the current subtitle track
@property(nonatomic, assign) int64_t trackIndex;

@end

/**
 * Audio frame data
 */
LITEAV_EXPORT @interface TXVodAudioFrameData : NSObject

/// Audio sample data
/// When the data is non-planar, data[0] stores the data
@property(nonatomic, assign) uint8_t **data;

/// Audio sample data size
/// When the data is non-planar, size[0] stores the data length
@property(nonatomic, assign) int *size;

/// Audio sampling rate
@property(nonatomic, assign) unsigned int sampleRate;

/// Audio channel layout. Common values: 3 - stereo (STEREO), 4 - mono (MONO)
@property(nonatomic, assign) uint64_t channelLayout;

/// Audio format. Common values: 0 - unsigned 8 bits, 1 - signed 16 bits, 2 - signed 32 bits
@property(nonatomic, assign) int format;

/// The current sample's PTS (in milliseconds)
@property(nonatomic, assign) int64_t ptsMs;

/// Number of samples per channel
@property(nonatomic, assign) int nbSamples;

/// Number of channels
@property(nonatomic, assign) int channels;

@end
