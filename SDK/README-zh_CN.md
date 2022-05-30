简体中文 | [English](./README.md)

本文主要介绍如何快速地将腾讯云 TRTC SDK（Unity）集成到您的项目中，只要按照如下步骤进行配置，就可以完成 SDK 的集成工作。

## 环境要求
* Unity 建议版本： 2020.2.1f1c1。
* 目前支持 Android、iOS、Windows、Mac（Mac仅支持1开头的应用id）平台。
* 需要包含 `Android Build Support`、`iOS Build Support`、 `Winodows Build Support` 和 `MacOs Build Support` 模块。
- 其中 iOS  端开发还需要：
  - Xcode 11.0及以上版本。
  - 请确保您的项目已设置有效的开发者签名。

## 集成 SDK
1. 下载 SDK 及配套的 [Demo 源码](https://github.com/LiteAVSDK/TRTC_Unity)。
2. 解压后，把项目中的 `SDK` 文件夹拷贝到您项目中的 Assets 目录下。

## 常见问题
### iOS 编译注意事项
1. 配置 Unity Editor，单击【File】>【Build Setting】，切换至 iOS。
![](https://tccweb-1258344699.cos.ap-nanjing.myqcloud.com/sdk/trtc/unity/ios.png)
2. 连接 iPhone 真机，单击【Build And Run】，需要选择一个新的目录存放编译出来的 iOS 工程，等待编译完成，会有新窗口弹出 Xcode 工程。
3. 单击 Link Binary with Libraries 项展开，单击底下的“+”号图标去添加依赖库 `libc++.tbd` 、`Accelerate.framework` 	、 `libresolv.tbd`、`AVFoundation.framework`、`VideoToolBox.framework`、`Metal.framework`、`MetalKit.framework`、`SystemConfiguration.framework`、`ReplayKit.framework`、`ACoreMedia.framework`、`CoreTelephony.framework`、`OpenGLES.framework`、`CoreImage.framework`。
![](https://imgcache.qq.com/operation/dianshi/other/link.743c57b230fa1be24a2226b6cd1c99378eca81ca.png)
4. 单击 Other Linker Flags 项展开，添加 `-ObjC`
![](https://imgcache.qq.com/operation/dianshi/other/8.6-objc.e0df060a638c1056fc07d1cb51c303a9de5b542f.png)
5. 错误提示`You must rebuild it with bitcode enabled (Xcode setting ENABLE_BITCODE)`
![](https://imgcache.qq.com/operation/dianshi/other/enable.d0cd40914b1d60e74bcc32b0c14ad5afbca4d1ee.png)
6. 错误提示` The Legacy Build System will be removed in a future release. You can configure the selected build system and this deprecation message in File > Project Settings.`
打开 File —> Project Setting 面板，修改Build 类型。
![](https://imgcache.qq.com/operation/dianshi/other/newBuild.af51c956404867ac237269e78da8ee8e2c556bd1.png)
7. 授权摄像头和麦克风使用权限

  使用 SDK 的音视频功能，需要授权麦克风和摄像头的使用权限。在 App 的 Info.plist 中添加以下两项，分别对应麦克风和摄像头在系统弹出授权对话框时的提示信息。

  * Privacy - Microphone Usage Description，并填入麦克风使用目的提示语。
  
  * Privacy - Camera Usage Description，并填入摄像头使用目的提示语。
  
  ![](https://main.qcloudimg.com/raw/54cc6989a8225700ff57494cba819c7b.jpg)

### macos 相关问题
1. 提示` "macosliteav.bundle" 已损怀，无法打开。您应该将它移到废纸篓 `
![](https://imgcache.qq.com/operation/dianshi/other/macos.600034e6a5bd6750d6abe5eb63ff45099f7a51ac.png)

解决办法[参考文档](https://zhuanlan.zhihu.com/p/163702779) 设置权限。

### Android 提示网络权限问题？
请将项目中 `/Assets/Plugins/AndroidManifest.xml` 文件放到同级目录下。

### Android 没有音视频的权限？
Android 端的麦克风、摄像头权限要手动申请，具体方法请参见以下代码：
```
#if PLATFORM_ANDROID
if (!Permission.HasUserAuthorizedPermission(Permission.Microphone))
 {
     Permission.RequestUserPermission(Permission.Microphone);
 }
 if (!Permission.HasUserAuthorizedPermission(Permission.Camera))
 {
     Permission.RequestUserPermission(Permission.Camera);
 }
 #endif
```  
