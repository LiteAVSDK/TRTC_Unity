简体中文 | [English](./README.md)

这个示例项目演示了如何在 Unity 中快速集成 TRTC SDK，实现在游戏中的音视频通话。

在这个示例项目中包含了以下功能：

- 加入通话和离开通话。
- 自定义视频渲染。
- 设备管理、音乐特效和人声特效。

> 具体 API 功能参数说明，请参见 [Unity API 概览](https://cloud.tencent.com/document/product/647/55158)。更多项目接入问题，请接入 QQ 群（764231117）咨询。

## 运行环境要求

- Unity 建议版本： 2020.2.1f1c1。
- 目前支持 Android、iOS、Windows、Mac(Mac 还在内测中)平台。
- 需要包含 `Android Build Support`、`iOS Build Support`、`Winodows Build Support` 和 `MacOs Build Support` 模块。
- 其中 iOS 端开发还需要：
  - Xcode 11.0 及以上版本。
  - 请确保您的项目已设置有效的开发者签名。

## 运行示例程序

[](id:step1)

### 步骤 1：创建新的应用

1. 登录实时音视频控制台，选择【开发辅助】>【[快速跑通 Demo](https://console.cloud.tencent.com/trtc/quickstart)】。
2. 输入应用名称，例如`APIExample`；若您已创建过应用，可以勾选【选择已有应用】，然后单击【创建】。
   ![#900px](https://qcloudimg.tencent-cloud.cn/raw/899626ba2c8f9b32921bda193c9ab9a9.png)

[](id:step2)

### 步骤 2：下载 SDK 与源码

1. 前往【[Github](https://github.com/LiteAVSDK/TRTC_Unity/tree/main/TRTC-Simple-Demo)】下载相关 SDK 及配套的 Demo 源码。
2. 下载完成后，返回实时音视频控制台，单击【已下载，下一步】，可以查看 SDKAppID 和密钥信息。

[](id:step3)

### 步骤 3：配置 Demo 工程文件

1. 解压 [步骤 2](#step2) 中下载的源码包。
2. 找到并打开`TRTC-Simple-Demo/Assets/TRTCSDK/Demo/Tools/GenerateTestUserSig.cs`文件。
3. 设置`GenerateTestUserSig.cs`文件中的相关参数：

> - SDKAPPID：默认为 PLACEHOLDER ，请设置为实际的 SDKAppID。
> - SECRETKEY：默认为 PLACEHOLDER ，请设置为实际的密钥信息。
>   ![#900px](https://qcloudimg.tencent-cloud.cn/raw/c8a787f11cb3f52a49ffd04ad0197d4b.png)

4. 返回实时音视频控制台，单击【已复制粘贴，下一步】。
5. 单击【关闭指引，进入控制台管理应用】。

[](id:step4)

### 步骤 4：编译运行

#### Android 平台

1. 配置 Unity Editor，单击【File】>【Build Setting】，切换至 Android。
   ![](https://main.qcloudimg.com/raw/4464eb891829e3505a59c8ec00cc2414.png)
2. 连接 Android 真机，单击【Build And Run】，Demo 就能跑起来。
3. 接口测试，需要先点击调用 enterRoom ，然后自行测试其他相关，数据展示窗口显示点击调用成功，另外一个窗口显示回调信息。

#### iOS 平台

1. 打开`TRTC 构建配置工具`（可在 Unity 编辑器顶部导航栏找到）
2. 点击`构建&配置 IOS`，等待项目生成完成
   ![](https://imgcache.qq.com/operation/dianshi/other/ios.88273906e5ca84fa9199dff33dfae1d8e53a5388.png)
3. 使用 xcode 打开生成好的 Unity-iPhone.xcodeproj 项目
4. 下载[TRTC 底层 sdk](https://comm.qq.com/trtc/TRTC_9.7.0.11440_iOS.zip)，单击 General，选择 Frameworks,Libraries,and Embedded Content，单击底下的“+”号图标依次添加所需要动态库 FFmpeg.xcframework、SoundTouch.xcframework，选择 Embed & Sign。
   ![](https://imgcache.qq.com/operation/dianshi/other/unity.ca7b6e717bf7b34e4f08a7e688ff59bf49d92217.png)
5. 连接 iOS 真机进行调试

#### Windows 平台

1. 配置 Unity Editor，单击【File】>【Build Setting】，切换至 `PC, Mac & Linux Standalone`，Target Platform 选择 Windows。
   ![](https://main.qcloudimg.com/raw/580764f661c06cf71c4952727c409c5e.png)
2. 单击【 Build And Run】，Demo 就能跑起来。

#### macOS 平台

1. 配置 Unity Editor，单击【File】>【Build Setting】，切换至 `PC, Mac & Linux Standalone`，Target Platform 选择 macOS。
   ![](https://main.qcloudimg.com/raw/6f3f9c21aa9eeadd7a4e3be377b2a6b3.png)
2. 单击【 Build And Run】，Demo 就能跑起来。
3. 使用 Unity Editor 模拟器运行，先要安装 `Device Simulator Package`。
4. 单击【Window】>【General】>【Device Simulator】
   ![](https://main.qcloudimg.com/raw/79f707b89553528956a888f48b4d4d6d.png)

[](id:demo)

## Demo 示例

Demo 里面包含了已上线的大部分 API，可以测试和作为调用参考，API 文档参见 [SDK API（Unity）](https://cloud.tencent.com/document/product/647/55158)。

> UI 可能会有部分调整更新，请以最新版为准。

![](https://main.qcloudimg.com/raw/2ce3ab51c6fdc843c1e8b086b55840c0.png)

## 目录结构

```
├─Assets
├── Editor                        // Unity 编辑器脚本
│   ├── BuildScript.cs            // Unity 编辑器build菜单
│   ├── IosPostProcess.cs         // Unity 编辑器构建ios应用脚本
├── Plugins
│   ├── Android
│   │   ├── AndroidManifest.xml   //Android应用配置文件
├── StreamingAssets               // Unity Demo 音视频流文件
├── TRTCSDK
    ├── Demo                      // Unity 示例 Demo
    ├── SDK                       // TRTC Unity SDK
        ├── Implement             // TRTC Unity SDK 实现
        ├── Include               // TRTC Unity SDK 头文件
        └── Plugins               // TRTC Unity SDK 不同平台底层实现
```
