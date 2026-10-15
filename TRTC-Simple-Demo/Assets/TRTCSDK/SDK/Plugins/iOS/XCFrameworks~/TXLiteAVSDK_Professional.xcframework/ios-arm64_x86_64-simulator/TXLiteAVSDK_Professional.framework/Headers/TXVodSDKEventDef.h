//  Copyright © 2021 Tencent. All rights reserved.

#ifndef __TX_VOD_SDK_EVENT_DEF_H__
#define __TX_VOD_SDK_EVENT_DEF_H__

#import "TXLiveSDKEventDef.h"
#import "TXLiveSDKTypeDef.h"

/**
 * The following are VOD event codes and error codes
 */
enum TXVODEventID {

    /**
     * ​	/////////////////////////////////////////////////////////////////////////////////
     * ​   //       Playback error codes, event codes, and warning codes
     * ​   /////////////////////////////////////////////////////////////////////////////////
     */
    /// Playback event: Hit cache.
    VOD_PLAY_EVT_HIT_CACHE = 2002,

    /// Playback event: Received the first video frame successfully.
    VOD_PLAY_EVT_RCV_FIRST_I_FRAME = 2003,

    /// Playback event: Received the first audio frame successfully.
    VOD_PLAY_EVT_RCV_FIRST_AUDIO_FRAME = 2026,

    /// Playback event: Playback started.
    VOD_PLAY_EVT_PLAY_BEGIN = 2004,

    /// Playback event: The playback progress was updated. This event is applicable to the VOD player only.
    VOD_PLAY_EVT_PLAY_PROGRESS = 2005,

    /// Playback event: Playback ended.
    VOD_PLAY_EVT_PLAY_END = 2006,

    /// Playback event: The data is buffering.
    VOD_PLAY_EVT_PLAY_LOADING = 2007,

    /// Playback event: The video decoder started.
    VOD_PLAY_EVT_START_VIDEO_DECODER = 2008,

    /// Playback event: The video resolution changed.
    VOD_PLAY_EVT_CHANGE_RESOLUTION = 2009,

    /// Playback event: Obtained the information of the VOD file successfully. This event is applicable to the VOD player only.
    VOD_PLAY_EVT_GET_PLAYINFO_SUCC = 2010,

    /// Playback event: The rotation angle of the MP4 video changed. This event is applicable to the VOD player only.
    VOD_PLAY_EVT_CHANGE_ROTATION = 2011,

    /// Playback event: The SEI message (https://cloud.tencent.com/document/product/454/7880#Message) in the video stream was received.
    VOD_PLAY_EVT_GET_MESSAGE = 2012,

    /// Playback event: Video loading was completed. This event is applicable to the VOD player only.
    VOD_PLAY_EVT_VOD_PLAY_PREPARED = 2013,

    /// Playback event: Video buffering ended. This event is applicable to the VOD player only.
    VOD_PLAY_EVT_VOD_LOADING_END = 2014,

    /// Playback event: Switched the video stream between different definitions successfully.
    VOD_PLAY_EVT_STREAM_SWITCH_SUCC = 2015,

    /// Playback event: TCP connection succeeded.
    VOD_PLAY_EVT_VOD_PLAY_TCP_CONNECT_SUCC = 2016,

    /// Playback event: Received the first data frame successfully. Supported starting from version 12.0.
    VOD_PLAY_EVT_VOD_PLAY_FIRST_VIDEO_PACKET = 2017,

    /// Playback event: DNS resolution was completed.
    VOD_PLAY_EVT_VOD_PLAY_DNS_RESOLVED = 2018,

    /// Playback event: Video playback seeking was completed.
    VOD_PLAY_EVT_VOD_PLAY_SEEK_COMPLETE = 2019,

    /// Playback event: Select track complete
    VOD_PLAY_EVT_SELECT_TRACK_COMPLETE = 2020,

    /// Playback event: Deselect track complete
    VOD_PLAY_EVT_DESELECT_TRACK_COMPLETE = 2021,

    /// Playback event: Playback paused
    VOD_PLAY_EVT_PLAY_PAUSE = 2022,

    /// Playback event: Video SEI
    VOD_PLAY_EVT_VIDEO_SEI = 2030,

    /// Playback event: HEVC downgrade playback
    VOD_PLAY_EVT_HEVC_DOWNGRADE_PLAYBACK = 2031,

    /// Playback event: The audio session was interrupted by another app. This event is applicable to iOS only.
    VOD_PLAY_EVT_AUDIO_SESSION_INTERRUPT = 2032,

    /// Live streaming error: The network was disconnected and couldn't be reconnected after three retries.
    VOD_PLAY_ERR_NET_DISCONNECT = -2301,

    /// VOD error: The file to be played back does not exist.
    VOD_PLAY_ERR_FILE_NOT_FOUND = -2303,

    /// VOD error: Failed to get the HLS decryption key.
    VOD_PLAY_ERR_HLS_KEY = -2305,

    /// VOD error: Failed to get the information of the VOD file.
    VOD_PLAY_ERR_GET_PLAYINFO_FAIL = -2306,

    /// VOD error: Failed to check  license.
    VOD_PLAY_ERR_LICENCE_CHECK_FAIL = -5,

    /// End of loop once playback complete ( Since 10.8)
    VOD_PLAY_EVT_LOOP_ONCE_COMPLETE = 6001,

    /// VOD error: unknow error.
    VOD_PLAY_ERR_UNKNOW = -6001,

    /// VOD error: general error.
    VOD_PLAY_ERR_GENERAL = -6002,

    /// VOD error: demuxer fail.
    VOD_PLAY_ERR_DEMUXER_FAIL = -6003,

    /// VOD error:System player playback fail.
    VOD_PLAY_ERR_SYSTEM_PLAY_FAIL = -6004,

    /// VOD error: demuxer timeout.
    VOD_PLAY_ERR_DEMUXER_TIMEOUT = -6005,

    /// VOD error: video decode fail.
    VOD_PLAY_ERR_DECODE_VIDEO_FAIL = -6006,

    /// VOD error: audio decode fail.
    VOD_PLAY_ERR_DECODE_AUDIO_FAIL = -6007,

    /// VOD error: subtitle decode fail.
    VOD_PLAY_ERR_DECODE_SUBTITLE_FAIL = -6008,

    /// VOD error: video render fail.
    VOD_PLAY_ERR_RENDER_FAIL = -6009,

    /// VOD error: video postprocess fail.
    VOD_PLAY_ERR_PROCESS_VIDEO_FAIL = -6010,

    /// VOD error: video download fail.
    VOD_PLAY_ERR_DOWNLOAD_FAIL = -6011,
};

/**
 * Compatible definitions
 *
 * The following definitions are used for compatibility with error code definitions on early versions. Use new definitions on the right in your code as much as possible.
 */
#define EVT_VOD_PLAY_TCP_CONNECT_SUCC VOD_PLAY_EVT_VOD_PLAY_TCP_CONNECT_SUCC
#define EVT_VOD_PLAY_FIRST_VIDEO_PACKET VOD_PLAY_EVT_VOD_PLAY_FIRST_VIDEO_PACKET
#define EVT_VOD_PLAY_DNS_RESOLVED VOD_PLAY_EVT_VOD_PLAY_DNS_RESOLVED
#define EVT_VOD_PLAY_SEEK_COMPLETE VOD_PLAY_EVT_VOD_PLAY_SEEK_COMPLETE

/**
 * The PiP controller status
 */
typedef NS_ENUM(NSInteger, TX_VOD_PLAYER_PIP_STATE) {

    /// No status is set.
    TX_VOD_PLAYER_PIP_STATE_UNDEFINED = 0,

    /// PiP will start soon.
    TX_VOD_PLAYER_PIP_STATE_WILL_START = 1,

    /// PiP started.
    TX_VOD_PLAYER_PIP_STATE_DID_START = 2,

    /// PiP will end soon.
    TX_VOD_PLAYER_PIP_STATE_WILL_STOP = 3,

    /// PiP ended.
    TX_VOD_PLAYER_PIP_STATE_DID_STOP = 4,

    /// The UI was reset.
    TX_VOD_PLAYER_PIP_STATE_RESTORE_UI = 5,
};

/**
 * The PiP error type
 */
typedef NS_ENUM(NSInteger, TX_VOD_PLAYER_PIP_ERROR_TYPE) {

    /// No error.
    TX_VOD_PLAYER_PIP_ERROR_TYPE_NONE = 0,

    /// The player doesn't support PiP.
    TX_VOD_PLAYER_PIP_ERROR_TYPE_DEVICE_NOT_SUPPORT = 1,

    /// The video doesn't support PiP.
    TX_VOD_PLAYER_PIP_ERROR_TYPE_PLAYER_NOT_SUPPORT = 2,

    /// The PiP controller is unavailable.
    TX_VOD_PLAYER_PIP_ERROR_TYPE_VIDEO_NOT_SUPPORT = 3,

    /// The PiP controller is unavailable.
    TX_VOD_PLAYER_PIP_ERROR_TYPE_PIP_IS_NOT_POSSIBLE = 4,

    /// The PiP controller reported an error.
    TX_VOD_PLAYER_PIP_ERROR_TYPE_ERROR_FROM_SYSTEM = 5,

    /// The player object does not exist.
    TX_VOD_PLAYER_PIP_ERROR_TYPE_PLAYER_NOT_EXIST = 10,

    /// The PiP feature is running.
    TX_VOD_PLAYER_PIP_ERROR_TYPE_PIP_IS_RUNNING = 11,

    /// The PiP feature has not been started.
    TX_VOD_PLAYER_PIP_ERROR_TYPE_PIP_NOT_RUNNING = 12,

    /// The PiP function fails to start because it's timed out
    TX_VOD_PLAYER_PIP_ERROR_TYPE_PIP_START_TIMEOUT = 13,

    /// The seamless PiP function fails to start
    TX_VOD_PLAYER_PIP_ERROR_TYPE_SEAMLESS_PIP_ERROR = 20,

    /// Not support seamless PiP
    TX_VOD_PLAYER_PIP_ERROR_TYPE_SEAMLESS_PIP_NOT_SUPPORT = 21,

    /// Seamless PiP function is already running
    TX_VOD_PLAYER_PIP_ERROR_TYPE_SEAMLESS_PIP_IS_RUNNING = 22,
};

/**
 * AIRPLAY state (only system players are supported)
 */
typedef NS_ENUM(NSInteger, TX_VOD_PLAYER_AIRPLAY_STATE) {

    /// not running
    TX_VOD_PLAYER_AIRPLAY_STATE_NOT_RUNNING = 0,

    /// running
    TX_VOD_PLAYER_AIRPLAY_STATE_DID_RUNNING = 1,
};

/**
 * the error type of AIRPLAY (only system players are supported)
 */
typedef NS_ENUM(NSInteger, TX_VOD_PLAYER_AIRPLAY_ERROR_TYPE) {

    /// no errors
    TX_VOD_PLAYER_AIRPLAY_ERROR_TYPE_NONE = 0,

    /// player doesn't support
    TX_VOD_PLAYER_AIRPLAY_ERROR_TYPE_PLAYER_NOT_SUPPORT = 1,

    /// video doesn't supported
    TX_VOD_PLAYER_AIRPLAY_ERROR_TYPE_VIDEO_NOT_SUPPORT = 2,

    /// player is not available
    TX_VOD_PLAYER_AIRPLAY_ERROR_TYPE_PLAYER_INVALID = 10,

    /// player state is error
    TX_VOD_PLAYER_AIRPLAY_ERROR_TYPE_PLAYER_STATE = 11,
};

/**
 * The mime type of external subtitle
 */
typedef NS_ENUM(NSInteger, TX_VOD_PLAYER_SUBTITLE_MIME_TYPE) {

    /// The SRT format of external subtitle
    TX_VOD_PLAYER_MIMETYPE_TEXT_SRT = 0,

    /// The VTT format of external subtitle
    TX_VOD_PLAYER_MIMETYPE_TEXT_VTT = 1,
};

/**
 * The type of Player buffering
 */
typedef NS_ENUM(NSInteger, TX_VOD_PLAYER_BUFFERING_TYPE) {

    /// undefined
    TX_VOD_PLAYER_BUFFERING_TYPE_NONE = -1,

    /// normal buffer
    TX_VOD_PLAYER_BUFFERING_TYPE_NORMAL = 0,

    /// buffering events generated by the player's internal restart
    TX_VOD_PLAYER_BUFFERING_TYPE_PLAYER_REOPEN = 1,
};

/**
 * LiteAVSDK notifies you of internal events, errors, alarms, through the callback of ‘onPlayEvent:event:withParam:’. The following is the parameters , in the format of key-value, the definition of the key-value is as follows:
 */
#ifndef TX_VOD_PLAY_EVENT_MSG
#define TX_VOD_PLAY_EVENT_MSG

/**
 * the value list of Parameter Key
 */
/// the download url of the sprite image's web Vtt description file
#define VOD_PLAY_EVENT_IMAGESPRIT_WEBVTTURL @"EVT_IMAGESPRIT_WEBVTTURL"

/// the download url list of sprite image
#define VOD_PLAY_EVENT_IMAGESPRIT_IMAGEURL_LIST @"EVT_IMAGESPRIT_IMAGEURL_LIST"

/// the description information of video‘s key frame
#define VOD_PLAY_EVENT_KEY_FRAME_CONTENT_LIST @"EVT_KEY_FRAME_CONTENT_LIST"

/// the time of video‘s key frame (s)
#define VOD_PLAY_EVENT_KEY_FRAME_TIME_LIST @"EVT_KEY_FRAME_TIME_LIST"

/// the video rotation
#define VOD_PLAY_EVENT_KEY_VIDEO_ROTATION @"EVT_KEY_VIDEO_ROTATION"

/// Return the parameter of External subtitle— switch to the index of media track
#define EVT_KEY_SELECT_TRACK_INDEX @"EVT_KEY_SELECT_TRACK_INDEX"

/// Return the parameter of External subtitle—return error code for switching media tracks
#define EVT_KEY_SELECT_TRACK_ERROR_CODE @"EVT_KEY_SELECT_TRACK_ERROR_CODE"

/// The type of Player Loading
#define VOD_PLAY_BUFFERING_LOADING_TYPE @"VOD_PLAY_BUFFERING_LOADING_TYPE"

/// Ghost watermark text(Supported starting from version 11.5)
#define EVT_KEY_WATER_MARK_TEXT @"EVT_KEY_WATER_MARK_TEXT"

/// The type of video SEI
#define EVT_KEY_SEI_TYPE @"EVT_KEY_SEI_TYPE"

/// The size of video SEI data buffer
#define EVT_KEY_SEI_SIZE @"EVT_KEY_SEI_SIZE"

/// video SEI data buffer
#define EVT_KEY_SEI_DATA @"EVT_KEY_SEI_DATA"

/**
 * Compatible Definition
 * for compatibility with the old version of the error code definition, please try to use the new definition of the left side of 'VOD_PLAY_XXX' in the code
 */
/// the message of event
#define VOD_PLAY_EVENT_MSG EVT_MSG

/// the timestamp of event
#define VOD_PLAY_EVENT_TIME EVT_TIME

/// the UTC millisecond timestamp of event
#define VOD_PLAY_EVENT_UTC_TIME EVT_UTC_TIME

/// the timestamp of caton (millisecond)
#define VOD_PLAY_EVENT_BLOCK_DURATION EVT_BLOCK_DURATION

///  VOD player error code.
#define VOD_PLAY_EVT_ERROR_CODE @"EVT_ERROR_CODE"

/// the first parameter of the event
#define VOD_PLAY_EVENT_PARAM1 EVT_PARAM1

/// the second parameter of the event
#define VOD_PLAY_EVENT_PARAM2 EVT_PARAM2

/// the content of message
#define VOD_PLAY_EVENT_GET_MSG EVT_GET_MSG

/// the progress of player
#define VOD_PLAY_EVENT_PLAY_PROGRESS EVT_PLAY_PROGRESS

/// the duration of video
#define VOD_PLAY_EVENT_PLAY_DURATION EVT_PLAY_DURATION

/// the playable duration of video
#define VOD_PLAY_EVENT_PLAYABLE_DURATION EVT_PLAYABLE_DURATION

/// the cover of video
#define VOD_PLAY_EVENT_PLAY_COVER_URL EVT_PLAY_COVER_URL

/// the url of video
#define VOD_PLAY_EVENT_PLAY_URL EVT_PLAY_URL

/// the name of video
#define VOD_PLAY_EVENT_PLAY_NAME EVT_PLAY_NAME

/// the introduction of video
#define VOD_PLAY_EVENT_PLAY_DESCRIPTION EVT_PLAY_DESCRIPTION

/// the PDT time of video
#define VOD_PLAY_EVENT_PLAY_PDT_TIME_MS @"EVT_PLAY_PDT_TIME_MS"

/// Custom transparent reporting field key (added in version 11.7)
#define VOD_KEY_CUSTOM_DATA @"VOD_KEY_CUSTOM_DATA"

/// backup url Key (added in version 11.7)
#define VOD_KEY_BACKUP_URL @"VOD_KEY_BACKUP_URL"

/// video codec type key, the value refers to CMVideoCodecType (added in version 11.7)
#define VOD_KEY_VIDEO_CODEC_TYPE @"VOD_KEY_VIDEO_CODEC_TYPE"

/// Type corresponding to the alternative playback resource (VOD_KEY_BACKUP_URL) (New in version 12.0)
#define VOD_KEY_BACKUP_URL_MEDIA_TYPE @"VOD_KEY_BACKUP_URL_MEDIA_TYPE"

/// Module type
#define PLAYER_OPTION_PARAM_MODULE_TYPE @"PARAM_MODULE_TYPE"

/// Module config
#define PLAYER_OPTION_PARAM_MODULE_CONFIG @"PARAM_MODULE_CONFIG"

/// Whether to enable the sensor, default is true
#define PLAYER_OPTION_PARAM_MODULE_VR_ENABLE_SENSOR @"ENABLE_SENSOR"

/// Field of view, default is 65.0f degrees, limited range is 30.0f - 110.0f degrees
#define PLAYER_OPTION_PARAM_MODULE_VR_FOV @"FOV"

/// Horizontal rotation angle: positive values indicate a right turn, negative values indicate a left turn. 0° represents the front direction, with a range of -180° to 180°
#define PLAYER_OPTION_PARAM_MODULE_VR_ANGLE_X @"ANGLE_X"

/// Vertical rotation angle: positive values indicate upward rotation, negative values indicate downward rotation. 0° represents a horizontal view angle, with a range of -85° to 85°.
#define PLAYER_OPTION_PARAM_MODULE_VR_ANGLE_Y @"ANGLE_Y"

/// The rate of gesture swipe distance to angle; the larger the ratio, the higher the sensitivity. The default value is 1/3.0f.
#define PLAYER_OPTION_PARAM_MODULE_VR_ANGLE_RATE @"ANGLE_RATE"

/// The threshold for the slope of the rotation angles in the XY plane. The default value is 0.5f, and only the longer edge will be selected for rotation within the threshold range.
#define PLAYER_OPTION_PARAM_MODULE_VR_ANGLE_SLOPE_THRESHOLD @"ANGLE_SLOPE_THRESHOLD"

/**
 * Module type
 */
typedef NS_ENUM(NSInteger, TX_VOD_PLAYER_OPTION_PARAM_MODULE_TYPE) {

    /// Empty type, disable super resolution and VR
    PLAYER_OPTION_PARAM_MODULE_TYPE_NONE = 0,

    /// Super resolution type
    PLAYER_OPTION_PARAM_MODULE_TYPE_SR = 1,

    /// VR panoramic model, monocular
    PLAYER_OPTION_PARAM_MODULE_TYPE_VR_PANORAMA = 11,

    /// VR panoramic model, binocular
    PLAYER_OPTION_PARAM_MODULE_TYPE_VR_BINOCULAR = 12,
};

/// Monet action
/// VR do rotate action
#define PLAYER_OPTION_PARAM_MODULE_VR_DO_ROTATE @"MONET_AC_DO_ROTATE"

/**
 * Monet callback event ID, event range 8000~8200
 */
typedef NS_ENUM(NSInteger, TX_VOD_PLAYER_OPTION_MONET_EVT_ID) {

    /// Rotation angles event
    PLAYER_OPTION_EVT_ANGLES = 8001,
};

/// Monet callback event parameters
/// Horizontal rotation angle; positive values indicate right turn, negative values indicate left turn.
#define PLAYER_OPTION_EVT_KEY_ANGLE_X @"ANGLE_X"

/// Vertical rotation angle; positive values indicate upward turn, negative values indicate downward turn.
#define PLAYER_OPTION_EVT_KEY_ANGLE_Y @"ANGLE_Y"

/// External subtitle output type configuration Key
#define PLAYER_OPTION_KEY_SUBTITLE_OUTPUT_TYPE @"450"

#endif  /* TX_VOD_PLAY_EVT_MSG */
#endif  // __TX_VOD_SDK_EVENT_DEF_H__
