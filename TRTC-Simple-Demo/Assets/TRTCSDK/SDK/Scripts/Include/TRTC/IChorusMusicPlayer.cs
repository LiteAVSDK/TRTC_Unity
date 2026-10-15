/**
 * Copyright (c) 2024 Tencent. All rights reserved.
 * Module:   合唱模块
 * Function: 提供 TRTC 房间内多人合唱能力
 */
using System;

namespace trtc {

  /////////////////////////////////////////////////////////////////////////////////
  //
  //                    合唱相关枚举值定义
  //
  /////////////////////////////////////////////////////////////////////////////////

  /**
   * 合唱角色。
   */
  public enum ChorusRole {
    /// 主唱
    LeadSinger = 1,
    /// 副唱
    BackSinger = 2,
    /// 主播
    Anchor = 3,
    /// 观众
    Audience = 4,
  }

  /**
   * 伴唱方式。
   */
  public enum ChorusMusicTrack {
    /// 伴唱
    Accompaniment = 1,
    /// 原唱
    OriginalSong = 2,
  }

  /**
   * 合唱错误码。
   */
  public enum ChorusError {
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
  }

  /**
   * 合唱停止原因。
   */
  public enum ChorusStopReason {
    /// 主唱主动结束
    Stopped = 1,
    /// 歌曲播放完成
    Completed = 2,
    /// 歌曲播放出错
    Error = 3,
    /// 和主唱的连接断开（非主唱角色）
    LeaderSingerDisconnected = 4,
  }

  /////////////////////////////////////////////////////////////////////////////////
  //
  //                    合唱核心类型定义
  //
  /////////////////////////////////////////////////////////////////////////////////

  /**
   * 合唱外部音乐参数。
   */
  public class ChorusExternalMusicParams {
    /// 【字段含义】歌曲 ID。
    public string musicId;
    /// 【字段含义】歌曲文件 URL。
    public string musicUrl;
    /// 【字段含义】伴奏文件 URL。
    public string accompanyUrl;
  }

  /////////////////////////////////////////////////////////////////////////////////
  //
  //                    合唱事件回调
  //
  /////////////////////////////////////////////////////////////////////////////////

  /**
   * 合唱播放器事件回调接口。
   */
  public interface IChorusPlayerEventCallback {
    /**
     * 合唱错误回调。
     *
     * @param errCode 错误码，参见 {@link ChorusError}。
     * @param errMsg 错误信息。
     */
    void onChorusError(ChorusError errCode, string errMsg);

    /**
     * 要求加载音乐回调。
     *
     * @param musicId 歌曲 ID。
     */
    void onChorusRequireLoadMusic(string musicId);

    /**
     * 音乐加载进度回调。
     *
     * @param musicId 歌曲 ID。
     * @param progress 加载进度，取值范围 [0, 1]。
     */
    void onChorusMusicLoadProgress(string musicId, float progress);

    /**
     * 音乐加载完成回调。
     *
     * @param musicId 歌曲 ID。
     */
    void onChorusMusicLoadSucceed(string musicId);

    /**
     * 合唱已开始回调。
     */
    void onChorusStarted();

    /**
     * 合唱已暂停回调。
     */
    void onChorusPaused();

    /**
     * 合唱已恢复回调。
     */
    void onChorusResumed();

    /**
     * 合唱已停止回调。
     *
     * @param reason 停止原因，参见 {@link ChorusStopReason}。
     */
    void onChorusStopped(ChorusStopReason reason);

    /**
     * 音乐播放进度更新回调。
     *
     * @param progressMs 当前播放进度，单位毫秒。
     * @param durationMs 歌曲总时长，单位毫秒。
     */
    void onMusicProgressUpdated(long progressMs, long durationMs);
  }

  /////////////////////////////////////////////////////////////////////////////////
  //
  //                    合唱音乐播放器
  //
  /////////////////////////////////////////////////////////////////////////////////

  /**
   * 合唱音乐播放器。
   */
  public abstract class IChorusMusicPlayer {

    /**
     * 创建合唱播放器实例。
     *
     * @param cloud TRTCCloud 实例。
     * @param roomId 合唱房间 ID。
     * @param callback 事件回调。
     * @return 合唱播放器实例。
     */
    public static IChorusMusicPlayer create(ITRTCCloud cloud,
                                            string roomId,
                                            IChorusPlayerEventCallback callback) {
      return TXChorusMusicPlayerImplement.create(cloud, roomId, callback);
    }

    /**
     * 销毁合唱播放器实例。
     *
     * @param player 合唱播放器实例。
     */
    public static void destroy(IChorusMusicPlayer player) {
      TXChorusMusicPlayerImplement.destroy(player);
    }

    /**
     * 设置合唱角色。
     *
     * @param role 合唱角色，参见 {@link ChorusRole}。
     * @param trtcParamsForPlayer 进房参数，非主唱角色可传 null。
     * @note 该接口必须在使用其它合唱接口之前调用。
     */
    public abstract void setChorusRole(ChorusRole role, TRTCParams? trtcParamsForPlayer);

    /**
     * 加载外部音乐。
     *
     * @param param 外部音乐参数，参见 {@link ChorusExternalMusicParams}。
     */
    public abstract void loadExternalMusic(ChorusExternalMusicParams param);

    /**
     * 开始合唱。
     */
    public abstract void start();

    /**
     * 结束合唱。
     */
    public abstract void stop();

    /**
     * 暂停合唱。
     */
    public abstract void pause();

    /**
     * 恢复合唱。
     */
    public abstract void resume();

    /**
     * 跳转播放进度。
     *
     * @param timestampMs 目标时间戳，单位毫秒。
     */
    public abstract void seek(long timestampMs);

    /**
     * 切换原唱/伴唱。
     *
     * @param track 伴唱方式，参见 {@link ChorusMusicTrack}。
     */
    public abstract void switchMusicTrack(ChorusMusicTrack track);

    /**
     * 设置音乐本地播放音量。
     *
     * @param volume 音量，取值范围 [0, 100]。
     */
    public abstract void setPlayoutVolume(int volume);

    /**
     * 设置音乐远端播放音量。
     *
     * @param volume 音量，取值范围 [0, 100]。
     */
    public abstract void setPublishVolume(int volume);

    /**
     * 设置音乐升降调。
     *
     * @param pitch 音高，0.0 为原调。
     */
    public abstract void setMusicPitch(float pitch);

    /**
     * 调用实验性接口。
     *
     * @param jsonStr JSON 参数字符串。
     */
    public abstract void callExperimentalAPI(string jsonStr);
  }
}
