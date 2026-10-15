/**
 * Copyright (c) 2024 Tencent. All rights reserved.
 * Module: ChorusPlayer
 * Function: 用于合唱功能
 * 此功能默认没有打包到 SDK 中，如果想使用此文件中的功能，联系腾讯单独提供 SDK。
 */

#import <Foundation/Foundation.h>
#import "TRTCCloud.h"
#import "TRTCCloudDef.h"
#import "TXLiteAVSymbolExport.h"

/**
 * 合唱角色
 */
typedef NS_ENUM(NSInteger, TXChorusRole) {
  /// 主唱
  TXChorusRoleLeadSinger = 1,
  /// 副唱
  TXChorusRoleBackSinger = 2,
  /// 主播
  TXChorusRoleAnchor = 3,
  /// 观众
  TXChorusRoleAudience = 4,
};

/**
 * 伴唱方式
 */
typedef NS_ENUM(NSInteger, TXChorusMusicTrack) {
  /// 伴唱
  TXChorusAccompaniment = 1,
  /// 原唱
  TXChorusOriginalSong = 2,
};

/**
 * 合唱错误
 */
typedef NS_ENUM(NSInteger, TXChorusError) {
  /// 参数非法
  TXChorusErrorInvalidParameters = 1,
  /// 未设置 TRTCCloud
  TXChorusErrorTrtcCloudNotFound = 2,
  /// 接口只允许主唱调用
  TXChorusErrorRestrictedToLeadSinger = 3,
  /// 未加载歌曲
  TXChorusErrorMusicPreloadRequired = 4,
  /// 歌曲加载失败
  TXChorusErrorMusicLoadFailed = 5,
  /// 歌曲解码失败
  TXChorusErrorMusicDecodeFailed = 6,
  /// 进房失败
  TXChorusErrorEnterRoomFailed = 7,
  /// 房间连接中断
  TXChorusErrorRoomDisconnected = 8,
  /// TRTCCloud 报错
  TXChorusErrorTrtcError = 9,
};

/**
 * 合唱停止原因
 */
typedef NS_ENUM(NSInteger, TXChorusStopReason) {
  /// 主唱主动结束
  TXChorusStopReasonStopped = 1,
  /// 歌曲播放完成
  TXChorusStopReasonCompleted = 2,
  /// 歌曲播放出错
  TXChorusStopReasonError = 3,
  /// 和主唱的连接断开（非主唱角色）
  TXChorusStopReasonLeaderSingerDisconnected = 4,
};

/**
 * 合唱版权音乐参数
 */
LITEAV_EXPORT @interface TXChorusCopyrightedMusicParams : NSObject

@property(nonatomic, copy) NSString *musicId;
@property(nonatomic, copy) NSString *playToken;
@property(nonatomic, copy) NSString *copyrightedLicenseKey;
@property(nonatomic, copy) NSString *copyrightedLicenseUrl;

@end

LITEAV_EXPORT @interface TXChorusExternalMusicParams : NSObject

@property(nonatomic, copy) NSString *musicId;
@property(nonatomic, copy) NSString *musicUrl;
@property(nonatomic, copy) NSString *accompanyUrl;
@property(nonatomic, assign) NSInteger isEncrypted;
@property(nonatomic, assign) NSInteger encryptBlockLength;

@end

LITEAV_EXPORT @interface TXChorusYsdMusicParams : NSObject

/// 音乐 ID
@property(nonatomic, copy) NSString *musicId;
/// 用户 ID
@property(nonatomic, copy) NSString *userId;
/// 用户 Token
@property(nonatomic, copy) NSString *userToken;
/// 设备 ID
@property(nonatomic, copy) NSString *deviceId;
/// 音速达注册的 pId
@property(nonatomic, copy) NSString *appId;
/// 音速达注册的 pKey
@property(nonatomic, copy) NSString *appKey;
/// 是否一次性付费，默认为false表示包月模式
@property(nonatomic, assign) BOOL isChargedOnce;

@end

/**
 * 合唱音乐参考音高
 */
LITEAV_EXPORT @interface TXReferencePitch : NSObject

@property(nonatomic, assign) NSInteger startTimeMs;
@property(nonatomic, assign) NSInteger durationMs;
@property(nonatomic, assign) NSInteger referencePitch;

@end

/** 歌词字符 */
LITEAV_EXPORT @interface TXChorusLyricCharacter : NSObject

/// 歌词开始时间
@property(nonatomic, assign) int64_t startTimeMs;

/// 歌词持续时间
@property(nonatomic, assign) int64_t durationMs;

/// UTF8 字符串
@property(nonatomic, copy) NSString *utf8Character;

@end

/** 歌词行 */
LITEAV_EXPORT @interface TXLyricLine : NSObject

/// 歌词开始时间
@property(nonatomic, assign) int64_t startTimeMs;

/// 歌词持续时间
@property(nonatomic, assign) int64_t durationMs;

/// 歌词字符列表
@property(nonatomic, strong) NSArray<TXChorusLyricCharacter *> *characterArray;

@end

@protocol ITXChorusPlayerDelegate <NSObject>
@optional
- (void)onChorusError:(TXChorusError)errCode errMsg:(NSString *)errMsg;

- (void)onNetworkQualityUpdated:(TRTCQuality)quality rtt:(uint32_t)rtt loss:(uint32_t)loss;

- (void)onChorusRequireLoadMusic:(NSString *)musicId;

- (void)onChorusMusicLoadProgress:(NSString *)musicId progress:(float)progress;

- (void)onChorusMusicLoadSucceed:(NSString *)musicId
                       lyricList:(NSArray<TXLyricLine *> *)lyricList
                       pitchList:(NSArray<TXReferencePitch *> *)pitchList;

- (void)onChorusStarted;

- (void)onChorusPaused;

- (void)onChorusResumed;

- (void)onChorusStopped:(TXChorusStopReason)reason;

- (void)onMusicProgressUpdated:(int64_t)progressMs durationMs:(int64_t)durationMs;

- (void)onVoicePitchUpdated:(int32_t)pitch hasVoice:(BOOL)hasVoice progressMs:(int64_t)progressMs;

- (void)onVoiceScoreUpdated:(int32_t)currentScore
               averageScore:(int32_t)averageScore
                currentLine:(int32_t)currentLine;

- (void)shouldDecryptAudioData:(NSData *)audioData;

@end

LITEAV_EXPORT @interface TXChorusMusicPlayer : NSObject

+ (instancetype)createPlayerWithTrtcCloud:(TRTCCloud *)cloud
                                   roomId:(NSString *)roomId
                                 delegate:(id<ITXChorusPlayerDelegate>)delegate;

// 设置角色
- (void)setChorusRole:(TXChorusRole)role trtcParamsForPlayer:(TRTCParams *)params;

- (void)setDelegate:(id<ITXChorusPlayerDelegate>)delegate;

// 加载音乐
- (void)loadMusic:(TXChorusCopyrightedMusicParams *)params;

// 加载外部音乐
- (void)loadExternalMusic:(TXChorusExternalMusicParams *)params;

// 加载 YSD 音乐
- (void)loadYsdMusic:(TXChorusYsdMusicParams *)params;

// 开始播放
- (void)start;

// 停止播放
- (void)stop;

// 暂停播放
- (void)pause;

// 恢复播放
- (void)resume;

// 跳转到指定时间戳
- (void)seek:(int64_t)timestampMs;

// 切换音乐轨道
- (void)switchMusicTrack:(TXChorusMusicTrack)track;

// 设置播放音量
- (void)setPlayoutVolume:(int32_t)volume;

// 设置发布音量
- (void)setPublishVolume:(int32_t)volume;

// 设置音乐音调：-1.0 ~ 1.0，默认 0.0
- (void)setMusicPitch:(float)pitch;

// 实验性接口
- (void)callExperimentalAPI:(NSString *)jsonStr;

@end