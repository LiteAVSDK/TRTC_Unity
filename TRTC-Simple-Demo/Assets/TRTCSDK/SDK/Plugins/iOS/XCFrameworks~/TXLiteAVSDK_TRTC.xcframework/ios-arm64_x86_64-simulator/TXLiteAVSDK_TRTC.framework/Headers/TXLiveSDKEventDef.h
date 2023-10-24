//  Copyright © 2020 Tencent. All rights reserved.

#ifndef __TX_LIVE_SDK_EVENT_DEF_H__
#define __TX_LIVE_SDK_EVENT_DEF_H__

/////////////////////////////////////////////////////////////////////////////////
//
//                     事件码和错误码定义
//
//  以下错误码适用于 V1 版本的 TXLivePusher 和 TXLivePlayer
//  如果您是新版本客户，推荐使用 V2 版本的 V2TXLivePusher 和 V2TXLivePlayer
//
/////////////////////////////////////////////////////////////////////////////////
// clang-format off

enum EventID
{

    /////////////////////////////////////////////////////////////////////////////////
    //       公共错误码、事件码和警告码
    /////////////////////////////////////////////////////////////////////////////////
    ERR_LICENSE_CHECK_FAIL                      = -5,        ///< license 检查失败

    /////////////////////////////////////////////////////////////////////////////////
    //       推流相关错误码、事件码和警告码
    /////////////////////////////////////////////////////////////////////////////////
    PUSH_EVT_CONNECT_SUCC                       =  1001,     ///< 推流事件: 已经连接RTMP推流服务器
    PUSH_EVT_PUSH_BEGIN                         =  1002,     ///< 推流事件: 已经与RTMP服务器握手完毕，准备开始推流
    PUSH_EVT_OPEN_CAMERA_SUCC                   =  1003,     ///< 推流事件: 打开摄像头成功
    PUSH_EVT_SCREEN_CAPTURE_SUCC                =  1004,     ///< 推流事件: 屏幕录制启动成功（用于录屏直播）
    PUSH_EVT_CHANGE_RESOLUTION                  =  1005,     ///< 推流事件: SDK 主动调整了编码分辨率以适应当前主播的网络速度
    PUSH_EVT_CHANGE_BITRATE                     =  1006,     ///< 推流事件: SDK 主动调整了编码码率以适应当前主播的网络速度
    PUSH_EVT_FIRST_FRAME_AVAILABLE              =  1007,     ///< 推流事件: SDK 完成了首帧画面的采集
    PUSH_EVT_START_VIDEO_ENCODER                =  1008,     ///< 推流事件: 编码器已经启动

    PUSH_EVT_CAMERA_REMOVED                     =  1023,     ///< 推流事件: 摄像头已被移除（适用于 Windows 和 Mac OS 版）
    PUSH_EVT_CAMERA_AVAILABLE                   =  1024,     ///< 推流事件: 摄像头已经可用（适用于 Windows 和 Mac OS 版）
    PUSH_EVT_CAMERA_CLOSE                       =  1025,     ///< 推流事件: 摄像头已被关闭（适用于 Windows 和 Mac OS 版）
    PUSH_EVT_HW_ENCODER_START_SUCC              =  1027,     ///< 推流事件: 硬编码器启动成功
    PUSH_EVT_SW_ENCODER_START_SUCC              =  1028,     ///< 推流事件: 软编码器启动成功
    PUSH_EVT_LOCAL_RECORD_RESULT                =  1029,     ///< 推流事件: 本地录制完成通知
    PUSH_EVT_LOCAL_RECORD_PROGRESS              =  1030,     ///< 推流事件: 本地录制状态通知

    PUSH_EVT_ROOM_IN                            =  1018,     ///< ROOM协议：当前用户进入房间成功
    PUSH_EVT_ROOM_OUT                           =  1019,     ///< ROOM协议：当前用户已经离开房间
    PUSH_EVT_ROOM_USERLIST                      =  1020,     ///< ROOM协议：返回房间中的其他用户（不包含当前用户自己）
    PUSH_EVT_ROOM_NEED_REENTER                  =  1021,     ///< ROOM协议：断开连接，需要重新进入房间
    PUSH_EVT_ROOM_IN_FAILED                     =  1022,     ///< ROOM协议：当前用户进入房间失败
    PUSH_EVT_ROOM_USER_ENTER                    =  1031,     ///< ROOM协议：有新的远端用户进入当前房间中
    PUSH_EVT_ROOM_USER_EXIT                     =  1032,     ///< ROOM协议：有远端用户离开当前房间
    PUSH_EVT_ROOM_USER_VIDEO_STATE              =  1033,     ///< ROOM协议：远端用户的视频状态发生变化（比如摄像头的开关状态）
    PUSH_EVT_ROOM_USER_AUDIO_STATE              =  1034,     ///< ROOM协议：远端用户的音频状态发生变化（比如麦克风的开关状态）
    
    PUSH_ERR_OPEN_CAMERA_FAIL                   = -1301,     ///< 推流错误: 摄像头开启失败
    PUSH_ERR_OPEN_MIC_FAIL                      = -1302,     ///< 推流错误: 麦克风开启失败
    PUSH_ERR_VIDEO_ENCODE_FAIL                  = -1303,     ///< 推流错误: 视频编码器出现不可恢复的错误
    PUSH_ERR_AUDIO_ENCODE_FAIL                  = -1304,     ///< 推流错误: 音频编码器出现不可恢复的错误
    PUSH_ERR_UNSUPPORTED_RESOLUTION             = -1305,     ///< 推流错误: 您指定了 SDK 尚不支持的视频分辨率
    PUSH_ERR_UNSUPPORTED_SAMPLERATE             = -1306,     ///< 推流错误: 您指定了 SDK 尚不支持的音频采样率
    PUSH_ERR_NET_DISCONNECT                     = -1307,     ///< 推流错误: 网络连接断开（已经经过三次重试并且未能重连成功）
    PUSH_ERR_AUDIO_SYSTEM_NOT_WORK              = -1308,     ///< 推流错误: 系统状态异常，无法正常采集麦克风的声音
    PUSH_ERR_INVALID_ADDRESS                    = -1313,     ///< 推流错误: 您指定了不合法的推流地址
    PUSH_ERR_CONNECT_SERVER_FAILED              = -1324,     ///< 推流错误: 连接推流服务器失败（若支持智能选路，IP 全部失败）
    PUSH_ERR_NETWORK_UNAVAIABLE                 = -1325,     ///< 推流错误: 网络不可用，请确认 Wi-Fi、移动数据或者有线网络是否正常
    PUSH_ERR_SERVER_REFUSED                     = -1326,     ///< 推流错误: 服务器拒绝连接请求，可能原因：推流地址非法；流地址被占用；txScrect校验失败；txTime过期；服务欠费等。

    PUSH_WARNING_NET_BUSY                       =  1101,     ///< 推流警告：上行网速不够用，建议提示用户改善当前的网络环境
    PUSH_WARNING_RECONNECT                      =  1102,     ///< 推流警告：网络断连，已启动重连流程（重试失败超过三次会放弃）
    PUSH_WARNING_HW_ACCELERATION_FAIL           =  1103,     ///< 推流警告：硬编码启动失败，SDK 已经自动切换到软编码模式
    PUSH_WARNING_VIDEO_ENCODE_FAIL              =  1104,     ///< 推流警告：当前视频帧未能成功编码，非致命错，SDK 内部会自行规避
    PUSH_WARNING_DNS_FAIL                       =  3001,     ///< 推流警告：DNS 解析失败，SDK 已经启动重试流程
    PUSH_WARNING_SEVER_CONN_FAIL                =  3002,     ///< 推流警告：服务器连接失败，SDK 已经启动重试流程
    PUSH_WARNING_SHAKE_FAIL                     =  3003,     ///< 推流警告：同 RTMP 服务器的握手失败，SDK 已经启动重试流程
    PUSH_WARNING_SERVER_DISCONNECT              =  3004,     ///< 推流警告：RTMP 服务器主动断开，请检查推流地址的合法性或防盗链有效期
    PUSH_WARNING_READ_WRITE_FAIL                =  3005,     ///< 推流警告：RTMP 写操作失败，当前连接将会断开

    /////////////////////////////////////////////////////////////////////////////////
    //       播放相关错误码、事件码和警告码
    /////////////////////////////////////////////////////////////////////////////////
    PLAY_EVT_CONNECT_SUCC                       =  2001,     ///< 播放事件: 已经连接到服务器
    PLAY_EVT_RTMP_STREAM_BEGIN                  =  2002,     ///< 播放事件: 已经连接服务器，开始拉流
    PLAY_EVT_RCV_FIRST_I_FRAME                  =  2003,     ///< 播放事件: 成功接受到第一个视频帧
    PLAY_EVT_RCV_FIRST_AUDIO_FRAME              =  2026,     ///< 播放事件: 成功接受到第一个音频帧
    PLAY_EVT_PLAY_BEGIN                         =  2004,     ///< 播放事件: 播放已经开始
    PLAY_EVT_PLAY_PROGRESS                      =  2005,     ///< 播放事件: 播放进度更新，点播播放器（VodPlayer）专用
    PLAY_EVT_PLAY_END                           =  2006,     ///< 播放事件: 播放已经结束
    PLAY_EVT_PLAY_LOADING                       =  2007,     ///< 播放事件: 数据缓冲中
    PLAY_EVT_START_VIDEO_DECODER                =  2008,     ///< 播放事件: 视频解码器已经启动
    PLAY_EVT_CHANGE_RESOLUTION                  =  2009,     ///< 播放事件: 视频分辨率发生变化
    PLAY_EVT_GET_PLAYINFO_SUCC                  =  2010,     ///< 播放事件: 成功获取到点播文件的信息，点播播放器（VodPlayer）专用
    PLAY_EVT_CHANGE_ROTATION                    =  2011,     ///< 播放事件: MP4 视频的旋转角度发生变化，点播播放器（VodPlayer）专用
    PLAY_EVT_GET_MESSAGE                        =  2012,     ///< 播放事件: 接收到视频流中的 SEI 消息（https://cloud.tencent.com/document/product/454/7880#Message）
    PLAY_EVT_VOD_PLAY_PREPARED                  =  2013,     ///< 播放事件: 视频加载完毕，点播播放器（VodPlayer）专用
    PLAY_EVT_VOD_LOADING_END                    =  2014,     ///< 播放事件: 视频缓冲结束，点播播放器（VodPlayer）专用
    PLAY_EVT_STREAM_SWITCH_SUCC                 =  2015,     ///< 播放事件: 已经成功完成切流（在不同清晰度的视频流之间进行切换）
    PLAY_EVT_GET_METADATA                       =  2028,     ///< 播放事件: TXLivePlayer 接收到视频流中的 metadata 头信息（一条视频流仅触发一次）
    PLAY_EVT_GET_FLVSESSIONKEY                  =  2031,     ///< 播放事件: TXLivePlayer 接收到 http 响应头中的 flvSessionKey 信息
    PLAY_EVT_AUDIO_SESSION_INTERRUPT            =  2032,     ///< 播放事件: Audio Session 被其他 App 中断（仅适用于 iOS 平台）

    PLAY_ERR_NET_DISCONNECT                     = -2301,     ///< 直播错误: 网络连接断开（已经经过三次重试并且未能重连成功）
    PLAY_ERR_GET_RTMP_ACC_URL_FAIL              = -2302,     ///< 直播错误: 获取加速流失败，可能是由于您指定的加速流URL中没有携带正确的txTime和txSecret参数，SDK会自动切换到高延迟的 CDN 地址。
    PLAY_ERR_HEVC_DECODE_FAIL                   = -2304,     ///< 直播错误: HEVC 解码失败，并且没有找到备用的选解码器
    PLAY_ERR_STREAM_SWITCH_FAIL                 = -2307,     ///< 直播错误: 切换直播流失败
    PLAY_ERR_STREAM_SERVER_REFUSED              = -2308,     ///< 直播错误：服务器拒绝连接请求，可能原因：播放地址非法；txScrect校验失败；txTime过期；服务欠费等。
    PLAY_ERR_FILE_NOT_FOUND                     = -2303,     ///< 点播错误: 播放文件不存在
    PLAY_ERR_HLS_KEY                            = -2305,     ///< 点播错误: HLS 解码 KEY 获取失败
    PLAY_ERR_GET_PLAYINFO_FAIL                  = -2306,     ///< 点播错误: 获取点播文件的文件信息失败

    PLAY_WARNING_VIDEO_DECODE_FAIL              =  2101,     ///< 直播警告：当前视频帧解码失败，SDK内部会尝试自动恢复
    PLAY_WARNING_AUDIO_DECODE_FAIL              =  2102,     ///< 直播警告：当前音频帧解码失败，SDK内部会尝试自动恢复
    PLAY_WARNING_RECONNECT                      =  2103,     ///< 直播警告：网络断连，已启动重连流程（重试失败超过三次会放弃）
    PLAY_WARNING_RECV_DATA_LAG                  =  2104,     ///< 直播警告：音视频流拉取不稳定，可能由于网络原因所致
    PLAY_WARNING_VIDEO_PLAY_LAG                 =  2105,     ///< 直播警告：当前视频画面出现卡顿
    PLAY_WARNING_HW_ACCELERATION_FAIL           =  2106,     ///< 直播警告：硬件解码失败，自动切换到软件解码
    PLAY_WARNING_VIDEO_DISCONTINUITY            =  2107,     ///< 直播警告：检测到视频帧不连续
    PLAY_WARNING_FIRST_IDR_HW_DECODE_FAIL       =  2108,     ///< 直播警告：视频硬解码失败，SDK 内部自动切换到软件解码
    PLAY_WARNING_DNS_FAIL                       =  3001,     ///< 直播警告：DNS 解析失败，SDK 已经启动重试流程
    PLAY_WARNING_SEVER_CONN_FAIL                =  3002,     ///< 直播警告：服务器连接失败，SDK 已经启动重试流程
    PLAY_WARNING_SHAKE_FAIL                     =  3003,     ///< 直播警告：同 RTMP 服务器的握手失败，SDK 已经启动重试流程
    PLAY_WARNING_SERVER_DISCONNECT              =  3004,     ///< 直播警告：RTMP 服务器主动断开，请检查播放地址的合法性或防盗链有效期
    PLAY_WARNING_READ_WRITE_FAIL                =  3005,     ///< 直播警告：RTMP 读操作失败，当前连接将会断开
    
};


/////////////////////////////////////////////////////////////////////////////////
//
//                     兼容定义
//     （用于兼容老版本的错误码定义，请在代码中尽量使用右侧的新定义）
//
/////////////////////////////////////////////////////////////////////////////////
#define EVT_RTMP_PUSH_CONNECT_SUCC             PUSH_EVT_CONNECT_SUCC
#define EVT_RTMP_PUSH_BEGIN                    PUSH_EVT_PUSH_BEGIN
#define EVT_CAMERA_START_SUCC                  PUSH_EVT_OPEN_CAMERA_SUCC
#define EVT_SCREEN_CAPTURE_SUCC                PUSH_EVT_SCREEN_CAPTURE_SUCC
#define EVT_UP_CHANGE_RESOLUTION               PUSH_EVT_CHANGE_RESOLUTION
#define EVT_UP_CHANGE_BITRATE                  PUSH_EVT_CHANGE_BITRATE
#define EVT_FIRST_FRAME_AVAILABLE              PUSH_EVT_FIRST_FRAME_AVAILABLE
#define EVT_START_VIDEO_ENCODER                PUSH_EVT_START_VIDEO_ENCODER

#define EVT_CAMERA_REMOVED                     PUSH_EVT_CAMERA_REMOVED
#define EVT_CAMERA_AVAILABLE                   PUSH_EVT_CAMERA_AVAILABLE
#define EVT_CAMERA_CLOSE                       PUSH_EVT_CAMERA_CLOSE
#define EVT_HW_ENCODER_START_SUCC              PUSH_EVT_HW_ENCODER_START_SUCC
#define EVT_SW_ENCODER_START_SUCC              PUSH_EVT_SW_ENCODER_START_SUCC
#define EVT_LOCAL_RECORD_RESULT                PUSH_EVT_LOCAL_RECORD_RESULT
#define EVT_LOCAL_RECORD_PROGRESS              PUSH_EVT_LOCAL_RECORD_PROGRESS

#define EVT_ROOM_ENTER                         PUSH_EVT_ROOM_IN
#define EVT_ROOM_ENTER_FAILED                  PUSH_EVT_ROOM_IN_FAILED
#define EVT_ROOM_EXIT                          PUSH_EVT_ROOM_OUT
#define EVT_ROOM_USERLIST                      PUSH_EVT_ROOM_USERLIST
#define EVT_ROOM_NEED_REENTER                  PUSH_EVT_ROOM_NEED_REENTER
#define EVT_ROOM_USER_ENTER                    PUSH_EVT_ROOM_USER_ENTER
#define EVT_ROOM_USER_EXIT                     PUSH_EVT_ROOM_USER_EXIT
#define EVT_ROOM_USER_VIDEO_STATE              PUSH_EVT_ROOM_USER_VIDEO_STATE
#define EVT_ROOM_USER_AUDIO_STATE              PUSH_EVT_ROOM_USER_AUDIO_STATE

#define ERR_RTMP_PUSH_NET_DISCONNECT           PUSH_ERR_NET_DISCONNECT
#define ERR_RTMP_PUSH_INVALID_ADDRESS          PUSH_ERR_INVALID_ADDRESS
#define ERR_RTMP_PUSH_NET_ALLADDRESS_FAIL      PUSH_ERR_CONNECT_SERVER_FAILED
#define ERR_RTMP_PUSH_NO_NETWORK               PUSH_ERR_NETWORK_UNAVAIABLE
#define ERR_RTMP_PUSH_SERVER_REFUSE            PUSH_ERR_SERVER_REFUSED

#define WARNING_NET_BUSY                       PUSH_WARNING_NET_BUSY
#define WARNING_RTMP_SERVER_RECONNECT          PUSH_WARNING_RECONNECT
#define WARNING_RTMP_DNS_FAIL                  PUSH_WARNING_DNS_FAIL
#define WARNING_RTMP_SEVER_CONN_FAIL           PUSH_WARNING_SEVER_CONN_FAIL
#define WARNING_RTMP_SHAKE_FAIL                PUSH_WARNING_SHAKE_FAIL
#define WARNING_RTMP_SERVER_BREAK_CONNECT      PUSH_WARNING_SERVER_DISCONNECT
#define WARNING_RTMP_READ_WRITE_FAIL           PUSH_WARNING_READ_WRITE_FAIL

#define EVT_PLAY_LIVE_STREAM_CONNECT_SUCC      PLAY_EVT_CONNECT_SUCC
#define EVT_PLAY_LIVE_STREAM_BEGIN             PLAY_EVT_RTMP_STREAM_BEGIN
#define EVT_RENDER_FIRST_I_FRAME               PLAY_EVT_RCV_FIRST_I_FRAME
#define EVT_AUDIO_JITTER_STATE_FIRST_PLAY      PLAY_EVT_RCV_FIRST_AUDIO_FRAME
#define EVT_VIDEO_PLAY_BEGIN                   PLAY_EVT_PLAY_BEGIN
#define EVT_VIDEO_PLAY_PROGRESS                PLAY_EVT_PLAY_PROGRESS
#define EVT_VIDEO_PLAY_END                     PLAY_EVT_PLAY_END
#define EVT_VIDEO_PLAY_LOADING                 PLAY_EVT_PLAY_LOADING
#define EVT_START_VIDEO_DECODER                PLAY_EVT_START_VIDEO_DECODER
#define EVT_DOWN_CHANGE_RESOLUTION             PLAY_EVT_CHANGE_RESOLUTION
#define EVT_GET_VODFILE_MEDIAINFO_SUCC         PLAY_EVT_GET_PLAYINFO_SUCC
#define EVT_VIDEO_CHANGE_ROTATION              PLAY_EVT_CHANGE_ROTATION
#define EVT_PLAY_GET_MESSAGE                   PLAY_EVT_GET_MESSAGE
#define EVT_VOD_PLAY_PREPARED                  PLAY_EVT_VOD_PLAY_PREPARED
#define EVT_VOD_PLAY_LOADING_END               PLAY_EVT_VOD_LOADING_END
#define EVT_PLAY_LIVE_STREAM_SWITCH_SUCC       PLAY_EVT_STREAM_SWITCH_SUCC
#define EVT_PLAY_GET_METADATA                  PLAY_EVT_GET_METADATA
#define EVT_PLAY_GET_FLVSESSIONKEY             PLAY_EVT_GET_FLVSESSIONKEY
#define EVT_AUDIO_SESSION_INTERRUPT            PLAY_EVT_AUDIO_SESSION_INTERRUPT

#define ERR_PLAY_LIVE_STREAM_NET_DISCONNECT    PLAY_ERR_NET_DISCONNECT
#define ERR_GET_RTMP_ACC_URL_FAIL              PLAY_ERR_GET_RTMP_ACC_URL_FAIL
#define ERR_FILE_NOT_FOUND                     PLAY_ERR_FILE_NOT_FOUND
#define ERR_VOD_DECRYPT_FAIL                   PLAY_ERR_HLS_KEY
#define ERR_GET_VODFILE_MEDIAINFO_FAIL         PLAY_ERR_GET_PLAYINFO_FAIL
#define ERR_PLAY_LIVE_STREAM_SWITCH_FAIL       PLAY_ERR_STREAM_SWITCH_FAIL
#define ERR_PLAY_LIVE_STREAM_SERVER_REFUSE     PLAY_ERR_STREAM_SERVER_REFUSED

#define WARNING_LIVE_STREAM_SERVER_RECONNECT   PLAY_WARNING_RECONNECT
#define WARNING_RECV_DATA_LAG                  PLAY_WARNING_RECV_DATA_LAG
#define WARNING_VIDEO_PLAY_LAG                 PLAY_WARNING_VIDEO_PLAY_LAG

#define EVT_SNAPSHOT_COMPLETE                  1022       ///< 已经完成一帧截图

// clang-format on
#endif  // __TX_LIVE_SDK_TYPE_DEF_H__
