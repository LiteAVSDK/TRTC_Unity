# LivePlayer的Unity版本接口API文档

本文档包含LivePlayer的Unity版本 API 接口和所有事件说明，您通过查阅此文档能够获得更多 LivePlayer 的使用帮助，本文将在 API 概览部分中为您介绍 LivePlayer提供的所有接口及其含义，在 API 使用指引的部分为您介绍，这些接口详细的使用方式，及注意事项

## V2TXLivePremier 对象API概览
以下会为您介绍每个 API 的含义，基础方法是创建V2TXLivePremier对象，使用V2TXLivePremier来设置license用于鉴权

**基础方法**
| API                   | 描述                 |
| :-------------------- | :------------------ |
| setLicense(string url, string key) | 用于设置LivePlayer的鉴权信息 |

**示例代码：**

```CSharp
using liteav;

public void Awake(){
    V2TXLivePremier.setLicense("Please use your own url " , "Please use your key");
}
```

## V2TXLivePlayer 对象API概览

以下会为您介绍每个 API 的含义，基础方法是创建LivePlayer对象，使用LivePlayer快直播服务的必用的 API。

**基础方法**

您可以通过这些方法完成事件监听，并创建LivePlayer对象，进行快直播并控制直播状态等操作。

| API                   | 描述                 |
| :-------------------- | :------------------ |
| createLivePlayer() | 用于创建一个livePlayer的对象 |
| setCallback(V2TXLivePlayerObserver callback) | 设置livePlayer的回调接受对象 |
| startPlay(string url)| 开启快直播播放   |
| enableObserverVideoFrame(bool enable,V2TXLivePixelFormat pixelFormat,V2TXLiveBufferType bufferType)|设置是否开启视频帧渲染，以及选择渲染数据格式|
| stopPlay()|停止快直播播放|
| isPlaying()|获取当前是否播放的状态|
| pauseAudio()|暂停音频播放|
| resumeAudio() | 恢复音频播放 |
| pauseVideo()  | 暂停视频播放|
| resumeVideo() | 恢复视频播放 |
| setPlayoutVolume(int volume) | 设置播放音量大小 |
| showDebugView(bool isShow)| 是否显示调试窗口 |


## API 使用指引

这部分会为您介绍如何进行使用上述 API 方法。

### createLivePlayer 创建LivePlayer对象

**示例代码：**

```CSharp

using liteav;
private V2TXLivePlayer _mV2TXLive = null;
public void Awake(){
   _mV2TXLive = V2TXLivePlayer.createLivePlayer();
}
```

### setCallback 设置livePlayer的回调接受对象

**示例代码：**

```CSharp

using liteav;

//V2TXLiveVideoRender继承于V2TXLivePlayerObserver
public V2TXLiveVideoRender VideoRender;

public void Awake(){
   _mV2TXLive = V2TXLivePlayer.createLivePlayer();
}
public void Start(){
   _mV2TXLive.setCallback(VideoRender);
}
```
### startPlay 开始快直播播放

**示例代码：**

```CSharp

using liteav;
public void Start(){
    string url = "Please use your own playback address";
   _mV2TXLive.startPlay(url);
}
```

### enableObserverVideoFrame 开始视频帧渲染
**简介**
在unity中需要开始视频帧渲染的方式，将每一帧数据从回调中获取。在通过自己喜欢的方式渲染到rawImage或者其他unity组件中

注意在android平台中帧渲染只能使用RGBA32格式或I420的格式，这里推荐使用RGBA32的方式，其他平台可使用BGRA32的格式
**示例代码：**

```CSharp

using liteav;
public void Start(){
    string url = "Please use your own playback address";
   _mV2TXLive.startPlay(url);
#if PLATFORM_ANDROID
    int res =
        _mV2TXLive.enableObserverVideoFrame(true, V2TXLivePixelFormat.V2TXLivePixelFormatRGBA32,
                                           V2TXLiveBufferType.V2TXLiveBufferTypeByteBuffer);
#else
    int res =
        _mV2TXLive.enableObserverVideoFrame(true, V2TXLivePixelFormat.V2TXLivePixelFormatBGRA32,
                                            V2TXLiveBufferType.V2TXLiveBufferTypeB
#endif
}
```
### stopPlay 停止快直播播放

**示例代码：**

```CSharp

using liteav;
public void StopPlay() { 
    _mV2TXLive.stopPlay();
}
```
### isPlaying 获取当前是否播放的状态

**示例代码：**

```CSharp

using liteav;
public Bool GetPlayState() { 
    int res = _mV2TXLive.isPlaying();
    return res == 1;
}
```
### pauseAudio 暂停音频播放

**示例代码：**

```CSharp
using liteav;
public void PauseAudio() { 
    _mV2TXLive.pauseAudio();
}
```
### pauseVideo 暂停视频播放

**示例代码：**

```CSharp
using liteav;
public void PauseVideo() { 
    _mV2TXLive.pauseVideo();
}
```
### pauseAudio 恢复音频播放

**示例代码：**

```CSharp
using liteav;
public void ResumeAudio() { 
    _mV2TXLive.resumeAudio();
}
```
### pauseVideo 恢复视频播放

**示例代码：**

```CSharp
using liteav;
public void ResumeVideo() { 
    _mV2TXLive.resumeVideo();
}
```
### setPlayoutVolume 设置播放音量的大小

**示例代码：**

```CSharp
using liteav;
public void SliderChanged(float volume) {
    if (_mV2TXLive == null) {
      return;
    }
    _mV2TXLive.setPlayoutVolume((int)volume);
}
```
### showDebugView 是否显示调试窗口
**注意**
在android平台中要正确显示调试窗口需要增加悬浮框的权限

**示例代码：**

```CSharp
using liteav;
public void EnableDebugView(bool isEnable) {
    if (_mV2TXLive == null) {
      return;
    }
    _mV2TXLive.showDebugView(isEnable);
}
```

## V2TXLivePlayerObserver 接口概览
以下会为您介绍每个 API 的含义，该对象是一个公共接口，通过继承该接口来获取livePlayer的回调数据
**基础方法**
您可以通过这些方法完成事件监听，获取快直播过程中的状态以及每帧的数据
| API                   | 描述                 |
| :-------------------- | :------------------ |
| onError(V2TXLivePlayer player, V2TXLiveCode code, string msg, IntPtr extraInfo) | 用户监听快直播中出现错误的事件 |
| onWarning(V2TXLivePlayer player, V2TXLiveCode code, string msg, IntPtr extraInfo) | 用户监听快直播中出现警告的事件 |
| onVideoResolutionChanged(V2TXLivePlayer player,int width, int height ) | 监听快直播中视频宽高变化的事件 |
| onConnected(V2TXLivePlayer player,IntPtr extraInfo ) | 监听快直播中网络已连接的事件 |
| onVideoPlaying(V2TXLivePlayer player, bool firstPlay, IntPtr extraInfo) | 监听快直播中视频播放事件 |
| onAudioPlaying(V2TXLivePlayer player, bool firstPlay, IntPtr extraInfo) | 监听快直播中音频播放事件 |
| onVideoLoading(V2TXLivePlayer player, IntPtr extraInfo) | 监听快直播中视频加载事件 |
| onAudioLoading(V2TXLivePlayer player, IntPtr extraInfo) | 监听快直播中音频加载事件 |
| onStatisticsUpdate(V2TXLivePlayer player, V2TXLivePlayerStatistics statistics) | 监听快直播中网络状态，cpu数据变化的事件 |
| onRenderVideoFrame(V2TXLivePlayer player, V2TXLiveVideoFrame videoFrame) | 监听快直播中每帧数据，该数据可以用于自定义渲染或绘制到rawImage中 |

**使用方法**
在unity中我们视频的播放是通过从回调中获取视频帧数据，再将这些帧数据渲染到unity的组件中。那么我们的渲染组件需要继承V2TXLivePlayerObserver接口并在onRenderVideoFrame中获取每帧的视频数据，在V2TXLivePlayer对象中设置setCallback，将渲染组件和V2TXLivePlayer对象绑定。示例如下：
**示例代码：**

```CSharp

using liteav;
public class V2TXLiveVideoRender : MonoBehaviour, V2TXLivePlayerObserver  { 
    private V2TXLiveVideoFrame _videoFrame;
    private UnityEngine.Object _videoFrameLock = new UnityEngine.Object();
     //监听并获取快直播的视频帧数据
    public void onRenderVideoFrame(V2TXLivePlayer player, V2TXLiveVideoFrame videoFrame) {
      lock (_videoFrameLock) {
        _videoFrame = videoFrame;
      }
    }
     void Update() {
        V2TXLiveVideoFrame videoFrame;
        lock (_videoFrameLock) {
        videoFrame = _videoFrame;
      }
      lock(this){
        //渲染到rawImage或其他播放组件
      }
     }
}
```
### onError 用户监听快直播中出现错误的事件

**示例代码：**
```CSharp
using liteav;
public class V2TXLiveVideoRender : MonoBehaviour, V2TXLivePlayerObserver  { 
    public void onError(V2TXLivePlayer player, V2TXLiveCode code, string msg, IntPtr extraInfo) {
      Debug.Log("OnError:" + code.ToString() + " " + msg);
    }
}
```
### onWarning 用户监听快直播中出现警告的事件

**示例代码：**
```CSharp
using liteav;
public class V2TXLiveVideoRender : MonoBehaviour, V2TXLivePlayerObserver  { 
    public void onWarning(V2TXLivePlayer player, V2TXLiveCode code, string msg, IntPtr extraInfo) {
      Debug.Log("onWarning:" + code.ToString() + " " + msg);
    }
}
```
### onVideoResolutionChanged 用户监听快直播中视频宽高发生改变

**示例代码：**
```CSharp
using liteav;
public class V2TXLiveVideoRender : MonoBehaviour, V2TXLivePlayerObserver  { 
    public void onVideoResolutionChanged(V2TXLivePlayer player, int width, int height) {
      Debug.Log("OnVideoResolutionChanged:" + " " + width.ToString() + " " + height.ToString());
    }
}
```
### onConnected 监听快直播中网络已连接事件

**示例代码：**
```CSharp
using liteav;
public class V2TXLiveVideoRender : MonoBehaviour, V2TXLivePlayerObserver  { 
    public void onConnected(V2TXLivePlayer player, IntPtr extraInfo) { 
        Debug.Log("OnConnected"); 
    }
}
```
### onVideoPlaying 监听快直播中视频播放事件

**示例代码：**
```CSharp
using liteav;
public class V2TXLiveVideoRender : MonoBehaviour, V2TXLivePlayerObserver  { 
    public void onVideoPlaying(V2TXLivePlayer player, bool firstPlay, IntPtr extraInfo) {
      Debug.Log("OnVideoPlaying:" + " " + firstPlay.ToString());
    }
}
```
### onAudioPlaying 监听快直播中音频播放事件

**示例代码：**
```CSharp
using liteav;
public class V2TXLiveVideoRender : MonoBehaviour, V2TXLivePlayerObserver  { 
    public void onAudioPlaying(V2TXLivePlayer player, bool firstPlay, IntPtr extraInfo) {
      Debug.Log("OnAudioPlaying" + " " + firstPlay.ToString());
    }
}
```
### onVideoLoading 监听快直播中视频加载事件

**示例代码：**
```CSharp
using liteav;
public class V2TXLiveVideoRender : MonoBehaviour, V2TXLivePlayerObserver  { 
    public void onVideoLoading(V2TXLivePlayer player, IntPtr extraInfo) {
      Debug.Log("OnVideoLoading");
    }
}
```
### onAudioLoading 监听快直播中音频加载事件

**示例代码：**
```CSharp
using liteav;
public class V2TXLiveVideoRender : MonoBehaviour, V2TXLivePlayerObserver  { 
    public void onAudioLoading(V2TXLivePlayer player, IntPtr extraInfo) {
      Debug.Log("OnAudioLoading");
    }
}
```
### onStatisticsUpdate 监听快直播中网络状态，cpu数据统计占比等事件
**示例代码：**
```CSharp
using liteav;
public class V2TXLiveVideoRender : MonoBehaviour, V2TXLivePlayerObserver  { 
    public void onStatisticsUpdate(V2TXLivePlayer player, V2TXLivePlayerStatistics statistics) {
      Debug.Log("OnStatisticsUpdate:" + "appCpu" + statistics.appCpu.ToString());
    }
}
```