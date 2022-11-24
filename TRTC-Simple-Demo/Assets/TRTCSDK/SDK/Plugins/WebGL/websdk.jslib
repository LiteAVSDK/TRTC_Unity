mergeInto(LibraryManager.library, {
  TRTCUnityAddOtherCallback: function (
    instance,
    on_connect_other_room,
    on_disconnect_otherRoom,
    on_switch_room,
    on_speed_test,
    on_test_mic_volume,
    on_test_speaker_volume,
    on_audio_device_capture_volume_changed,
    on_audio_device_playout_volume_changed,
    on_recv_custom_cmdmsg_handler,
    on_miss_custom_cmdmsg_handler,
    on_start_publishing_cdn_handler,
    on_stop_publishing_cdn_handler,
    on_set_mix_transcoding_config_handler
  ) {},
  TRTCUnityAddCallback: function (
    instance,
    on_error_handler,
    on_warning_handler,
    on_enter_room_handler,
    on_exit_room_handler,
    on_switch_role_handler,
    on_remote_user_enterRoom_handler,
    on_remote_user_leave_room_handler,
    on_user_video_available_handler,
    on_user_sub_stream_available_handler,
    on_user_audio_available_handler,
    on_first_video_frame_handler,
    on_first_audio_frame_handler,
    on_send_first_local_video_frame_handler,
    on_send_first_local_audio_frame_handler,
    on_network_quality_handler,
    on_statistics_handler,
    on_connection_lost_handler,
    on_try_to_reconnect_handler,
    on_connection_recovery_handler,
    on_camera_did_ready_handler,
    on_mic_did_ready_handler,
    on_user_voice_volume_handler,
    on_device_change_handler,
    on_recv_sei_msg_handler,
    on_start_publishing_handler,
    on_stop_publishing_handler
  ) {
    TRTCUnityAddCallback(
      instance,
      on_error_handler,
      on_warning_handler,
      on_enter_room_handler,
      on_exit_room_handler,
      on_switch_role_handler,
      on_remote_user_enterRoom_handler,
      on_remote_user_leave_room_handler,
      on_user_video_available_handler,
      on_user_sub_stream_available_handler,
      on_user_audio_available_handler,
      on_first_video_frame_handler,
      on_first_audio_frame_handler,
      on_send_first_local_video_frame_handler,
      on_send_first_local_audio_frame_handler,
      on_network_quality_handler,
      on_statistics_handler,
      on_connection_lost_handler,
      on_try_to_reconnect_handler,
      on_connection_recovery_handler,
      on_camera_did_ready_handler,
      on_mic_did_ready_handler,
      on_user_voice_volume_handler,
      on_device_change_handler,
      on_recv_sei_msg_handler,
      on_start_publishing_handler,
      on_stop_publishing_handler
    );
  },
  TRTCUnityAddScreenCaptureCallback: function (
    instance,
    on_screen_capture_started_handler,
    on_screen_capture_paused_handler,
    on_screen_capture_resumed_handler,
    screen_capture_stoped_handler
  ) {},
  TRTCUnitySetAudioFrameCallback: function (
    instance,
    on_captured_raw_audio_frameHandler,
    on_local_processed_audio_frame_handler,
    on_play_audio_frame_handler,
    on_mixed_play_audio_frame_handler
  ) {},
  TRTCUnityRemoveCallback: function (instance) {
    TRTCUnityRemoveCallback(instance);
  },
  TRTCUnityGetTRTCInstance: function () {
    TRTCUnityGetTRTCInstance();
  },
  TRTCUnityGetDeviceManager: function (instance) {},
  TRTCUnityGetAudioEffectManager: function (instance) {},
  TRTCUnityDestroyTRTCInstance: function (instance) {
    TRTCUnityDestroyTRTCInstance(instance);
  },
  TRTCUnityEnterRoom: function (
    instance,
    sdk_app_id,
    user_id,
    user_sig,
    room_id,
    str_room_id,
    role,
    stream_id,
    user_define_record_id,
    private_map_key,
    business_info,
    scene
  ) {
    TRTCUnityEnterRoom(
      instance,
      sdk_app_id,
      Pointer_stringify(user_id),
      Pointer_stringify(user_sig),
      room_id,
      Pointer_stringify(str_room_id),
      role,
      Pointer_stringify(stream_id),
      Pointer_stringify(user_define_record_id),
      Pointer_stringify(private_map_key),
      Pointer_stringify(business_info),
      scene
    );
  },

  TRTCUnityExitRoom: function (instance) {
    TRTCUnityExitRoom(instance);
  },

  TRTCUnitySwitchRole: function (instance, role) {
    TRTCUnitySwitchRole(instance, role);
  },

  TRTCUnityConnectOtherRoom: function (instance, jsonParams) {
    TRTCUnityConnectOtherRoom(instance, Pointer_stringify(jsonParams));
  },

  TRTCUnityDisconnectOtherRoom: function (instance) {
    TRTCUnityDisconnectOtherRoom(instance);
  },

  TRTCUnitySetDefaultStreamRecvMode: function (
    instance,
    autoRecvAudio,
    autoRecvVideo
  ) {},

  TRTCUnitySwitchRoom: function (
    instance,
    roomId,
    strRoomId,
    userSig,
    privateMapKey
  ) {
    TRTCUnitySwitchRoom(
      instance,
      roomId,
      Pointer_stringify(strRoomId),
      Pointer_stringify(userSig),
      Pointer_stringify(privateMapKey)
    );
  },

  TRTCUnityStartPublishing: function (instance, stream_id, type) {
    TRTCUnityStartPublishing(instance, Pointer_stringify(stream_id), type);
  },

  TRTCUnityStopPublishing: function (instance) {
    TRTCUnityStopPublishing(instance);
  },

  TRTCUnityStartPublishCDNStream: function (instance, appId, bizId, url) {},
  TRTCUnityStopPublishCDNStream: function (instance) {},

  TRTCUnitySetMixTranscodingConfigNull: function (instance) {},

  TRTCUnitySetMixTranscodingConfig: function (
    instance,
    mode,
    appId,
    bizId,
    videoWidth,
    videoHeight,
    videoBitrate,
    videoFramerate,
    videoGOP,
    backgroundColor,
    backgroundImage,
    audioSampleRate,
    audioBitrate,
    audioChannels,
    mixUsersArraySize,
    streamId,
    mixUsersArray
  ) {},
  TRTCUnityStartLocalPreview: function (instance) {},

  TRTCUnityStopLocalPreview: function (instance) {},

  TRTCUnityGetVideoRenderData: function (
    instance,
    userId,
    rotation,
    width,
    height,
    length,
    isNeedDestroy
  ) {},

  TRTCUnityMuteLocalVideo: function (instance, mute) {},

  TRTCUnityStartRemoteView: function (instance, user_id, stream_type) {},

  TRTCUnityStopRemoteView: function (instance, user_id, stream_type) {},

  TRTCUnityStopAllRemoteView: function (instance) {},

  TRTCUnityMuteRemoteVideoStream: function (instance, user_id, mute) {},

  TRTCUnityMuteAllRemoteVideoStreams: function (instance, mute) {},
  TRTCUnitySetVideoEncoderParam: function (
    instance,
    video_resolution,
    res_mode,
    video_fps,
    video_bitrate,
    min_video_bitrate,
    enable_adjust_res
  ) {},

  TRTCUnitySetNetworkQosParam: function (instance, preference, control_mode) {},

  TRTCUnitySetVideoEncoderRotation: function (instance, rotation) {},

  TRTCUnitySetVideoEncoderMirror: function (instance, mirror) {},

  TRTCUnitySetRemoteRenderParams: function (
    instance,
    userId,
    streamType,
    fillMode,
    mirrorType,
    rotation
  ) {},

  TRTCUnityEnableSmallVideoStream: function (
    instance,
    enable,
    smallVideoParam
  ) {},

  TRTCUnitySetRemoteVideoStreamType: function (instance, userId, type) {},

  TRTCUnitySetBeautyStyle: function (
    instance,
    style,
    beauty,
    white,
    ruddiness
  ) {},

  TRTCUnitySetWaterMark: function (
    instance,
    streamType,
    srcData,
    srcType,
    nWidth,
    nHeight,
    xOffset,
    yOffset,
    fWidthRatio
  ) {},
  TRTCUnityStartLocalAudio: function (instance, quality) {
    TRTCUnityStartLocalAudio(instance, quality);
  },

  TRTCUnityStopLocalAudio: function (instance) {
    TRTCUnityStopLocalAudio(instance);
  },

  TRTCUnityMuteLocalAudio: function (instance, mute) {
    TRTCUnityMuteLocalAudio(instance, mute);
  },

  TRTCUnityMuteRemoteAudio: function (instance, user_id, mute) {
    TRTCUnityMuteRemoteAudio(instance, Pointer_stringify(user_id), mute);
  },

  TRTCUnityMuteAllRemoteAudio: function (instance, mute) {
    TRTCUnityMuteAllRemoteAudio(instance, mute);
  },

  TRTCUnityEnableAudioVolumeEvaluation: function (instance, erval) {
    TRTCUnityEnableAudioVolumeEvaluation(instance, erval);
  },
  TRTCUnitySetRemoteAudioVolume: function (instance, userId, volume) {
    TRTCUnitySetRemoteAudioVolume(instance, Pointer_stringify(userId), volume);
  },

  TRTCUnitySetAudioPlayoutVolume: function (instance, volume) {
    TRTCUnitySetAudioPlayoutVolume(instance, volume);
  },

  TRTCUnityGetAudioPlayoutVolume: function (instance) {
    TRTCUnityGetAudioPlayoutVolume(instance);
  },

  TRTCUnityStartAudioRecording: function (instance, filePath) {
    TRTCUnityStartAudioRecording(instance, Pointer_stringify(filePath));
  },

  TRTCUnityStopAudioRecording: function (instance) {
    TRTCUnityStopAudioRecording(instance);
  },

  TRTCUnityStartLocalRecording: function (
    instance,
    filePath,
    recordType,
    erval
  ) {},

  TRTCUnityStopLocalRecording: function (instance) {},

  TRTCUnitySetAudioCaptureVolume: function (instance, volume) {
    TRTCUnitySetAudioCaptureVolume(instance, volume);
  },

  TRTCUnityGetAudioCaptureVolume: function (instance) {
    return TRTCUnityGetAudioCaptureVolume(instance);
  },

  TRTCUnityEnableCustomVideoCapture: function (instance, enable) {},
  TRTCUnitySendCustomVideoData: function (
    instance,
    video_format,
    buffer_type,
    data,
    texture_id,
    length,
    width,
    height,
    timestamp,
    rotation
  ) {},

  TRTCUnityEnableCustomAudioCapture: function (instance, enable) {},

  TRTCUnitySendCustomAudioData: function (
    instance,
    audio_format,
    data,
    length,
    sample_rate,
    channel,
    timestamp
  ) {},

  TRTCUnitySetLocalVideoRenderCallback: function (
    instance,
    pixel_format,
    buffer_type,
    on_render_video_frame_handler
  ) {},

  TRTCUnitySetRemoteVideoRenderCallback: function (
    instance,
    user_id,
    pixel_format,
    buffer_type,
    on_render_video_frame_handler
  ) {},

  TRTCUnitySendSEIMsg: function (instance, data, data_size, repeat_count) {},

  TRTCUnitySendCustomCmdMsg: function (
    instance,
    cmdId,
    data,
    dataSize,
    reliable,
    ordered
  ) {},

  TRTCUnityGetSDKVersion: function (instance, data, size) {
    var returnStr = TRTCUnityGetSDKVersion();
    var bufferSize = lengthBytesUTF8(returnStr) + 1;
    var buffer = _malloc(bufferSize);
    stringToUTF8(returnStr, buffer, bufferSize);
    return buffer;
  },

  TRTCUnitySetLogLevel: function (instance, level) {
    TRTCUnitySetLogLevel(instance, level);
  },

  TRTCUnitySetConsoleEnabled: function (instance, enabled) {
    TRTCUnitySetConsoleEnabled(instance, enabled);
  },

  TRTCUnitySetLogCompressEnabled: function (instance, enabled) {},

  TRTCUnitySetLogDirPath: function (instance, path) {},

  TRTCUnityCallExperimentalAPI: function (instance, json) {
    TRTCUnityCallExperimentalAPI(instance, Pointer_stringify(json));
  },

  TRTCUnityStartScreenCapture: function (
    instance,
    stream_type,
    video_resolution,
    res_mode,
    video_fps,
    video_bitrate,
    min_video_bitrate,
    enable_adjust_res
  ) {},

  TRTCUnityStopScreenCapture: function (instance) {},

  TRTCUnityPauseScreenCapture: function (instance) {},

  TRTCUnityResumeScreenCapture: function (instance) {},

  TRTCUnityGetScreenCaptureSourceCount: function (
    instance,
    thumbnail_width,
    thumbnail_height
  ) {},

  TRTCUnitySelectScreenCaptureTarget: function (
    instance,
    type,
    source_id,
    source_name,
    capture_left,
    capture_top,
    capture_right,
    capture_bottom,
    enable_capture_mouse,
    enable_highlight,
    enable_high_performance,
    highlight_color,
    highlight_Width
  ) {},

  TRTCUnitySetSubStreamEncoderParam: function (
    instance,
    video_resolution,
    res_mode,
    video_fps,
    video_bitrate,
    min_video_bitrate,
    enable_adjust_res
  ) {},

  TRTCUnityUpdate: function () {},
  TRTCUnityStartSpeedTest: function (instance, sdkAppId, userId, userSig) {},
  TRTCUnityStopSpeedTest: function (instance) {},

  TRTCUnityEnableVoiceEarMonitor: function (instance, enable) {},

  TRTCUnityGetMusicCurrentPosInMS: function (instance, id) {},

  TRTCUnityGetMusicDurationInMS: function (instance, path) {},

  TRTCUnityPausePlayMusic: function (instance, id) {},

  TRTCUnityResumePlayMusic: function (instance, id) {},

  TRTCUnitySeekMusicToPosInMS: function (instance, id, pts) {},

  TRTCUnitySetAllMusicVolume: function (instance, volume) {},

  TRTCUnitySetMusicPitch: function (instance, id, pitch) {},

  TRTCUnitySetMusicPlayoutVolume: function (instance, id, volume) {},

  TRTCUnitySetMusicPublishVolume: function (instance, id, volume) {},

  TRTCUnitySetMusicSpeedRate: function (instance, id, speedRate) {},

  TRTCUnitySetVoiceChangerType: function (instance, changerType) {},

  TRTCUnitySetVoiceEarMonitorVolume: function (instance, volume) {},

  TRTCUnitySetVoiceReverbType: function (instance, reverbType) {},

  TRTCUnitySetVoiceCaptureVolume: function (instance, volume) {},

  TRTCUnityStartPlayMusic: function (instance, musicParam) {},

  TRTCUnityStopPlayMusic: function (instance, id) {},

  TRTCUnitySetMusicObserver: function (
    instance,
    musicId,
    onStart,
    onPlayProgress,
    onComplete
  ) {},
  TRTCUnityGetDevicesList: function (instance, type, returnData, returnSize) {
    TRTCUnityGetDevicesList(type);
  },
  TRTCUnitySetCurrentDevice: function (instance, type, deviceId) {
    TRTCUnitySetCurrentDevice(type, deviceId);
  },
  TRTCUnityGetCurrentDevice: function (instance, type, returnData, returnSize) {
    TRTCUnityGetCurrentDevice(type);
  },
  TRTCUnityEnable3DSpatialAudioEffect: function (instance, enable) {},
  TRTCUnityUpdateSelf3DSpatialPosition: function (
    instance,
    position,
    axisForward,
    axisRight,
    axisUp
  ) {},
  TRTCUnitySet3DSpatialReceivingRange: function (instance, userId, range) {},
  TRTCUnityUpdateRemote3DSpatialPosition: function (
    instance,
    userId,
    position
  ) {},
});
