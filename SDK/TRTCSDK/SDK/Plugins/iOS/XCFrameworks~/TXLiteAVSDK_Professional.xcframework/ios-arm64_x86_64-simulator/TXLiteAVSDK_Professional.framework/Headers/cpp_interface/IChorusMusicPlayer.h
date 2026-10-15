/**
 * Copyright (c) 2024 Tencent. All rights reserved.
 * Module:   合唱模块
 * Function: 提供 TRTC 房间内多人合唱功能
 */

#ifndef TRTC_CPP_ICHORUSMUSICPLAYER_H_
#define TRTC_CPP_ICHORUSMUSICPLAYER_H_

#include "ITRTCCloud.h"
#include "TRTCTypeDef.h"

namespace liteav {
class IChorusMusicPlayer;
}

namespace liteav {

/**
 * 合唱角色
 */
enum class ChorusRole {
  /// 主唱
  LeadSinger = 1,

  /// 副唱
  BackSinger = 2,

  /// 主播
  Anchor = 3,

  /// 观众
  Audience = 4,
};

/**
 * 伴唱方式
 */
enum class ChorusMusicTrack {
  /// 伴唱
  Accompaniment = 1,

  /// 原唱
  OriginalSong = 2,
};

/**
 * 合唱错误
 */
enum class ChorusError {
  /// 参数非法
  InvalidParameters = 1,
  /// 未设置 TRTCCloud
  TrtcCloudNotFound = 2,
  /// 接口只允许主唱调用
  RestrictedToLeadSinger = 3,
  /// 未加载歌曲
  MusicPreloadRequired = 4,
  /// 歌曲加载失败
  MusicLoadFailed = 5,
  /// 歌曲解码失败
  MusicDecodeFailed = 6,
  /// 进房失败
  EnterRoomFailed = 7,
  /// 房间连接中断
  RoomDisconnected = 8,
  /// TRTCCloud 报错
  TrtcError = 9,
};

enum class ChorusStopReason {
  // 主唱主动结束
  Stopped = 1,
  // 歌曲播放完成
  Completed = 2,
  // 歌曲播放出错
  Error = 3,
  // 和主唱的连接断开（非主唱角色）
  LeaderSingerDisconnected = 4,
};

/**
 * 合唱版权音乐参数
 */
struct ChorusCopyrightedMusicParams {
  const char* musicId = nullptr;
  const char* playToken = nullptr;
  const char* copyrightedLicenseKey = nullptr;
  const char* copyrightedLicenseUrl = nullptr;
};

struct ChorusExternalMusicParams {
  /// 歌曲 ID
  const char* musicId = nullptr;
  /// 歌曲文件
  const char* musicUrl = nullptr;
  /// 伴奏文件
  const char* accompanyUrl = nullptr;
  /// 是否加密
  bool isEncrypted = false;
  /// 加密块长度
  int32_t encryptBlockLength = 0;
};

struct ChorusYsdMusicParams {
  /// 音乐 ID
  const char* musicId = nullptr;
  /// 用户 ID
  const char* userId = nullptr;
  /// 用户 Token
  const char* userToken = nullptr;
  /// 设备 ID
  const char* deviceId = nullptr;
  /// 音速达注册的 pId
  const char* appId = nullptr;
  /// 音速达注册的 pKey
  const char* appKey = nullptr;
  /// 是否一次性付费，默认为false表示包月模式
  bool isChargedOnce = false;
};

/** 歌词字符 */
struct ChorusLyricCharacter {
  /// 歌词开始时间
  int64_t startTimeMs = 0;
  /// 歌词持续时间
  int64_t durationMs = 0;
  /// UTF8 字符串
  const char* utf8Character = nullptr;
};

/** 歌词行 */
struct LyricLine {
  /// 歌词开始时间
  int64_t startTimeMs = 0;
  /// 歌词持续时间
  int64_t durationMs = 0;
  /// 歌词字符列表
  ChorusLyricCharacter* characterArray = nullptr;
  /// 歌词字符数量
  uint32_t characterCount = 0;
};

/** 合唱音乐参考音高 */
struct ReferencePitch {
  int64_t startTimeMs = 0;
  int64_t durationMs = 0;
  int32_t referencePitch = 0;
};

class IChorusPlayerEventCallback {
 public:
  virtual ~IChorusPlayerEventCallback() {}
  virtual void onChorusError(ChorusError errCode, const char* errMsg) = 0;
  virtual void onNetworkQualityUpdated(TRTCQuality quality, uint32_t rtt, uint32_t loss) = 0;
  virtual void onChorusRequireLoadMusic(const char* musicId) = 0;
  virtual void onChorusMusicLoadProgress(const char* musicId, float progress) = 0;
  virtual void onChorusMusicLoadSucceed(const char* musicId,
                                        const LyricLine* lyricList,
                                        uint32_t lyricListSize,
                                        const ReferencePitch* pitchList,
                                        uint32_t pitchListSize) = 0;
  virtual void onChorusStarted() = 0;
  virtual void onChorusPaused() = 0;
  virtual void onChorusResumed() = 0;
  virtual void onChorusStopped(ChorusStopReason reason) = 0;
  virtual void onMusicProgressUpdated(int64_t progressMs, int64_t durationMs) = 0;
  virtual void onVoicePitchUpdated(int32_t pitch, bool hasVoice, int64_t progressMs) = 0;
  virtual void onVoiceScoreUpdated(int32_t currentScore,
                                   int32_t averageScore,
                                   int32_t currentLine) = 0;
  virtual void shouldDecryptAudioData(uint8_t* data, int32_t dataLength) = 0;
};

class IChorusMusicPlayer {
 public:
  TRTC_API static IChorusMusicPlayer* create(ITRTCCloud* cloud,
                                             const char* room_id,
                                             IChorusPlayerEventCallback* callback);
  TRTC_API static void destroy(IChorusMusicPlayer* player);

  virtual void setChorusRole(ChorusRole role, TRTCParams* trtcParamsForPlayer) = 0;
  virtual void loadMusic(const ChorusCopyrightedMusicParams& params) = 0;
  virtual void loadExternalMusic(const ChorusExternalMusicParams& params) = 0;
  virtual void loadYsdMusic(const ChorusYsdMusicParams& params) = 0;
  virtual void start() = 0;
  virtual void stop() = 0;
  virtual void pause() = 0;
  virtual void resume() = 0;
  virtual void seek(int64_t timestampMs) = 0;
  virtual void switchMusicTrack(ChorusMusicTrack track) = 0;
  virtual void setPlayoutVolume(int32_t volume) = 0;
  virtual void setPublishVolume(int32_t volume) = 0;
  virtual void setMusicPitch(float pitch) = 0;
  virtual void callExperimentalAPI(const char* jsonStr) = 0;

 protected:
  virtual ~IChorusMusicPlayer() {}
};

}  // namespace liteav

#endif  // TRTC_CPP_ICHORUSMUSICPLAYER_H_
