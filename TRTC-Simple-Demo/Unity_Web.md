## Run Unity Webgl Demo
1. Switch Platform to WebGL, choose 'Development Build', then 'Build and run'
![](https://dscache.tencent-cloud.cn/upload/uploader/webgl-3050d99718f5c4b3ba90c6097957a7d5bedfb6c0.png)

2. After building successfully, you will get a html project，modify 'index.html'
 * Add a global variable 'trtcUnityInstance'
 * Add two scripts at the bottom of the page

```
<script src="https://dscache.tencent-cloud.cn/upload/uploader/trtc-cloud-js-sdk-02adaa29e01a5618477f199d8f5c9d52ed7235d2.js"></script>
<script src="https://dscache.tencent-cloud.cn/upload/uploader/trtc_unity-77593bdb36dbdcccc94b9ba99c2e4978899eef71.js"></script>
```
![](https://dscache.tencent-cloud.cn/upload/uploader/web-15156ff2f21a5b3371b88168278a8318adddf5de.png)

3. Refresh page(The code can refer to the root directory 'webtest')

## Unity Web API OverView
### Basic APIs

| API                                                          | Description                            |
| ------------------------------------------------------------ | --------------------------------- |
| getTRTCShareInstance | Creates a `TRTCCloud` singleton.             |
| destroyTRTCShareInstance | Releases a `TRTCCloud` singleton.        |
| addCallback | Sets the callback API. |
| removeCallback | Removes event callback.                    |
| enterRoom | Enters a room. If the room does not exist, the system will create one automatically.           |
| exitRoom | Exits a room.           |
| startLocalAudio | Enables local audio capturing and upstream data transfer.           |
| stopLocalAudio | Disables local audio capturing and upstream data transfer.            |
| muteLocalAudio | Mutes/Unmutes local audio.|
| muteRemoteAudio | Mutes/Unmutes a specified remote user.|
| muteAllRemoteAudio | Mutes/Unmutes all remote users. |
| enableAudioVolumeEvaluation | Enables volume reminders. |
| setRemoteAudioVolume | Sets the playback volume of a remote user. |
| getAudioCaptureVolume | Gets the SDK capturing volume. |
| GetDevicesList | Get device list, parameter 'type'(TXMediaDeviceType.TXMediaDeviceTypeMic/TXMediaDeviceType.TXMediaDeviceTypeSpeaker), specifying which device list to obtain. |
| SetCurrentDevice | Set the current device to use, parameter 'type'(TXMediaDeviceType.TXMediaDeviceTypeMic/TXMediaDeviceType.TXMediaDeviceTypeSpeaker), parameter 'deviceId'(You can get the device ID through the interface 'GetDevicesList') |
| GetCurrentDevice | Get the device currently in use, parameter 'type'(TXMediaDeviceType.TXMediaDeviceTypeMic/TXMediaDeviceType.TXMediaDeviceTypeSpeaker) |
| switchRole | Switch roles (TRTCRoleType.TRTCRoleAnchor/TRTCRoleType.TRTCRoleAudience) |

### Callback APIs
|API                                                          | Description                            |
| ------------------------------------------------------------ | --------------------------------- |
| onEnterRoom | Callback of room entry        |
| onExitRoom | Callback of room exit        |
| onRemoteUserEnterRoom | Callback of the entry of a user         |
| onRemoteUserLeaveRoomWeb | Callback of the exit of a user        |
| onUserAudioAvailableWeb | Callback of whether a remote user has playable audio        |
| onErrorWeb | Error callback. This indicates that the SDK encountered an irrecoverable error. Such errors must be listened for, and UI reminders should be displayed to users if necessary.        |
| onUserVoiceVolumeWeb | Callback of volume, including the volume of each `userId` and the total remote volume       |