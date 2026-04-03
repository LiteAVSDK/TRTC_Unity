/**
 * Copyright (c) 2021 Tencent. All rights reserved.
 * Module: TRTC audio/video metrics (read-only)
 * Function: the TRTC SDK reports to you the current real-time audio/video metrics (frame rate, bitrate, lag, etc.) once every two seconds
 */
#import "TXLiteAVSymbolExport.h"

/////////////////////////////////////////////////////////////////////////////////
//
//                    Local audio/video metrics
//
/////////////////////////////////////////////////////////////////////////////////
/// @name Local audio/video metrics
/// @{

/**
 * Local audio/video metrics.
 */
LITEAV_EXPORT @interface TRTCLocalStatistics : NSObject

/// Field description: local video width in px
@property(nonatomic, assign) uint32_t width;

/// Field description: local video height in px
@property(nonatomic, assign) uint32_t height;

/// Field description: local video frame rate in fps, i.e., how many video frames there are per second
@property(nonatomic, assign) uint32_t frameRate;

/// Field description: local video bitrate in Kbps, i.e., how much video data is generated per second
@property(nonatomic, assign) uint32_t videoBitrate;

/// Field description: local audio sample rate (Hz)
@property(nonatomic, assign) uint32_t audioSampleRate;

/// Field description: local audio bitrate in Kbps, i.e., how much audio data is generated per second
@property(nonatomic, assign) uint32_t audioBitrate;

/// Field description: video stream type (HD big image | smooth small image | substream image)
@property(nonatomic, assign) TRTCVideoStreamType streamType;

/// Field description:Audio equipment collection status(
/// 0：Normal；1：Long silence detected；2：Broken sound detected；3：Abnormal intermittent sound detected;)
@property(nonatomic, assign) uint32_t audioCaptureState;

@end

/////////////////////////////////////////////////////////////////////////////////
//
//                    Remote audio/video metrics
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * Remote audio/video metrics.
 */
LITEAV_EXPORT @interface TRTCRemoteStatistics : NSObject

/// Field description: user ID
@property(nonatomic, retain) NSString* userId;

/// Field description: total packet loss rate (%) of the audio stream
///`audioPacketLoss` represents the packet loss rate eventually calculated on the audience side after the audio/video stream goes through the complete transfer linkage of "anchor -> cloud -> audience".
/// The smaller the `audioPacketLoss`, the better. The packet loss rate of 0 indicates that all data of the audio stream has entirely reached the audience.
/// If `downLoss` is `0` but `audioPacketLoss` isn't, there is no packet loss on the linkage of "cloud -> audience" for the audiostream, but there are unrecoverable packet losses on the linkage of "anchor -> cloud".
@property(nonatomic, assign) uint32_t audioPacketLoss;

/// Field description: total packet loss rate (%) of the video stream
///`videoPacketLoss` represents the packet loss rate eventually calculated on the audience side after the audio/video stream goes through the complete transfer linkage of "anchor -> cloud -> audience".
/// The smaller the `videoPacketLoss`, the better. The packet loss rate of 0 indicates that all data of the video stream has entirely reached the audience.
/// If `downLoss` is `0` but `videoPacketLoss` isn't, there is no packet loss on the linkage of "cloud -> audience" for the video stream, but there are unrecoverable packet losses on the linkage of "anchor -> cloud".
@property(nonatomic, assign) uint32_t videoPacketLoss;

/// Field description: remote video width in px
@property(nonatomic, assign) uint32_t width;

/// Field description: remote video height in px
@property(nonatomic, assign) uint32_t height;

/// Field description: remote video frame rate (fps)
@property(nonatomic, assign) uint32_t frameRate;

/// Field description: remote video bitrate (Kbps)
@property(nonatomic, assign) uint32_t videoBitrate;

/// Field description: local audio sample rate (Hz)
@property(nonatomic, assign) uint32_t audioSampleRate;

/// Field description: local audio bitrate (Kbps)
@property(nonatomic, assign) uint32_t audioBitrate;

/// Field description: playback delay (ms)
/// In order to avoid audio/video lags caused by network jitters and network packet disorders, TRTC maintains a playback buffer on the playback side to organize the received network data packets.
/// The size of the buffer is adaptively adjusted according to the current network quality and converted to the length of time in milliseconds, i.e., `jitterBufferDelay`.
@property(nonatomic, assign) uint32_t jitterBufferDelay;

/// Field description: end-to-end delay (ms)
///`point2PointDelay` represents the delay of "anchor -> cloud -> audience". To be more precise, it represents the delay of the entire linkage of "collection -> encoding -> network transfer -> receiving -> buffering -> decoding -> playback".
///`point2PointDelay` works only if both the local and remote SDKs are on version 8.5 or above. If the remote SDK is on a version below 8.5, this value will always be 0 and thus meaningless.
@property(nonatomic, assign) uint32_t point2PointDelay;

/// Field description: cumulative audio playback lag duration (ms)
@property(nonatomic, assign) uint32_t audioTotalBlockTime;

/// Field description: audio playback lag rate (%)
/// Audio playback lag rate (audioBlockRate) = cumulative audio playback lag duration (audioTotalBlockTime)/total audio playback duration
@property(nonatomic, assign) uint32_t audioBlockRate;

/// Field description: cumulative video playback lag duration (ms)
@property(nonatomic, assign) uint32_t videoTotalBlockTime;

/// Field description: video playback lag rate (%)
/// Video playback lag rate (videoBlockRate) = cumulative video playback lag duration (videoTotalBlockTime)/total video playback duration
@property(nonatomic, assign) uint32_t videoBlockRate;

/// Field description: total packet loss rate (%) of the audio/video stream
/// Deprecated, please use audioPacketLoss and videoPacketLoss instead.
@property(nonatomic, assign) uint32_t finalLoss __attribute__((deprecated("Use audioPacketLoss and videoPacketLoss instead.")));

/// Field description: upstream packet loss rate (%) from the SDK to cloud
/// The smaller the value, the better. If `remoteNetworkUplinkLoss` is `0%`, the upstream network quality is very good, and the data packets uploaded to the cloud are basically not lost.
/// If `remoteNetworkUplinkLoss` is `30%`, 30% of the audio/video data packets sent to the cloud by the SDK are lost on the transfer linkage.
@property(nonatomic, assign) uint32_t remoteNetworkUplinkLoss;

/// Field description: round-trip delay (ms) from the SDK to cloud
/// This value represents the total time it takes to send a network packet from the SDK to the cloud and then send a network packet back from the cloud to the SDK, i.e., the total time it takes for a network packet to go through the linkage of "SDK
/// -> cloud -> SDK". The smaller the value, the better. If `remoteNetworkRTT` is below 50 ms, it means a short audio/video call delay; if `remoteNetworkRTT` is above 200 ms, it means a long audio/video call delay. It should be explained that
/// `remoteNetworkRTT` represents the total time spent on the linkage of "SDK -> cloud -> SDK"; therefore, there is no need to distinguish between `remoteNetworkUpRTT` and `remoteNetworkDownRTT`.
@property(nonatomic, assign) uint32_t remoteNetworkRTT;

/// Field description: video stream type (HD big image | smooth small image | substream image)
@property(nonatomic, assign) TRTCVideoStreamType streamType;

@end

/////////////////////////////////////////////////////////////////////////////////
//
//                    Network and performance metrics
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * Network and performance metrics.
 */
LITEAV_EXPORT @interface TRTCStatistics : NSObject

/// Field description: CPU utilization (%) of the current application, Android 8.0 and above systems are not supported
@property(nonatomic, assign) uint32_t appCpu;

/// Field description: CPU utilization (%) of the current system, Android 8.0 and above systems are not supported
@property(nonatomic, assign) uint32_t systemCpu;

/// Field description: upstream packet loss rate (%) from the SDK to cloud
/// The smaller the value, the better. If `upLoss` is `0%`, the upstream network quality is very good, and the data packets uploaded to the cloud are basically not lost.
/// If `upLoss` is `30%`, 30% of the audio/video data packets sent to the cloud by the SDK are lost on the transfer linkage.
@property(nonatomic, assign) uint32_t upLoss;

/// Field description: downstream packet loss rate (%) from cloud to the SDK
/// The smaller the value, the better. If `downLoss` is `0%`, the downstream network quality is very good, and the data packets received from the cloud are basically not lost.
/// If `downLoss` is `30%`, 30% of the audio/video data packets sent to the SDK by the cloud are lost on the transfer linkage.
@property(nonatomic, assign) uint32_t downLoss;

/// Field description: round-trip delay (ms) from the SDK to cloud
/// This value represents the total time it takes to send a network packet from the SDK to the cloud and then send a network packet back from the cloud to the SDK, i.e., the total time it takes for a network packet to go through the linkage of "SDK
/// -> cloud -> SDK". The smaller the value, the better. If `rtt` is below 50 ms, it means a short audio/video call delay; if `rtt` is above 200 ms, it means a long audio/video call delay. It should be explained that `rtt` represents the total time
/// spent on the linkage of "SDK -> cloud -> SDK"; therefore, there is no need to distinguish between `upRtt` and `downRtt`.
@property(nonatomic, assign) uint32_t rtt;

/// Field description: round-trip delay (ms) from the SDK to gateway
/// This value represents the total time it takes to send a network packet from the SDK to the gateway and then send a network packet back from the gateway to the SDK, i.e., the total time it takes for a network packet to go through the linkage of
/// "SDK -> gateway -> SDK". The smaller the value, the better. If `gatewayRtt` is below 50 ms, it means a short audio/video call delay; if `gatewayRtt` is above 200 ms, it means a long audio/video call delay. It should be explained that `gatewayRtt`
/// is invalid for cellular network.
@property(nonatomic, assign) uint32_t gatewayRtt;

/// Field description: total number of sent bytes (including signaling data and audio/video data)
@property(nonatomic, assign) uint64_t sentBytes;

/// Field description: total number of received bytes (including signaling data and audio/video data)
@property(nonatomic, assign) uint64_t receivedBytes;

/// Field description: local audio/video statistics
/// As there may be three local audio/video streams (i.e., HD big image, smooth small image, and substream image), the local audio/video statistics are an array.
@property(nonatomic, strong) NSArray<TRTCLocalStatistics*>* localStatistics;

/// Field description: remote audio/video statistics
/// As there may be multiple concurrent remote users, and each of them may have multiple concurrent audio/video streams (i.e., HD big image, smooth small image, and substream image), the remote audio/video statistics are an array.
@property(nonatomic, strong) NSArray<TRTCRemoteStatistics*>* remoteStatistics;

@end
