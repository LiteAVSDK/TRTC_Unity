[简体中文](./README-zh_CN.md) | English

This document describes how to quickly integrate TRTC SDK for Unity into your project.

## Environment Requirements
* Unity 2020.2.1f1c1 is recommended.
* Supported platforms: Android, iOS, Windows, macOS (Mac only supports the sdkAppId starting with 1)
* Modules required: `Android Build Support`, `iOS Build Support`, `Windows Build Support`, `MacOS Build Support`
- If you are developing for iOS, you also need:
  - Xcode 11.0 or above
  - A valid developer signature for your project

## Integrating SDK
1. Download the SDK and [Demo source code](https://github.com/LiteAVSDK/TRTC_Unity).
2. Decompress the ZIP file and copy `TRTC-Simple-Demo/Assets/TRTCSDK/SDK` to the `Assets` directory of your project.

## FAQs
### iOS Compilation considerations
1. Open Unity Editor，click【File】>【Build Setting】，switch platform to iOS。
![](https://tccweb-1258344699.cos.ap-nanjing.myqcloud.com/sdk/trtc/unity/ios.png)
2. Connect iPhone real machine，click【Build And Run】，Wait until the compilation is completed, and a new window will pop up Xcode project.
3. Click the 'Link Binary with Libraries' item to expand，and click the "+" icon at the bottom to add the dependent **libc++.tbd** 、 **libresolv.tbd**、**Accelerate.framework**、**MetalKit.framework**、**MobileCoreServices.framework**、**SystemConfiguration.framework**、**ReplayKit.framework**、**CoreTelephony.framework**(Unity-iPhone/UnityFramework both need to add).
![](https://imgcache.qq.com/operation/dianshi/other/link.743c57b230fa1be24a2226b6cd1c99378eca81ca.png)
4. If you use TRTC SDK v9.6 or a later version, you need to manually add the dynamic libraries.
Click General, expand Frameworks, Libraries, and Embedded Content, and click the + icon at the bottom to add the dynamic libraries required by TXLiteAVSDK_TRTC.framework: TXFFmpeg.xcframework and TXSoundTouch.xcframework. Click Embed & Sign. [Download addresses of two dynamic libraries](https://liteav.sdk.qcloud.com/download/latest/TXLiteAVSDK_TRTC_iOS_latest.zip)
![](https://qcloudimg.tencent-cloud.cn/raw/a159c5fb799cf50611387bdae7275863.png)
5. Click 'Other Linker Flags item' to expand，add `-ObjC`
![](https://imgcache.qq.com/operation/dianshi/other/8.6-objc.e0df060a638c1056fc07d1cb51c303a9de5b542f.png)
6. Error prompt `You must rebuild it with bitcode enabled (Xcode setting ENABLE_BITCODE)`
![](https://imgcache.qq.com/operation/dianshi/other/enable.d0cd40914b1d60e74bcc32b0c14ad5afbca4d1ee.png)
7. Error prompt ` The Legacy Build System will be removed in a future release. You can configure the selected build system and this deprecation message in File > Project Settings.`
open File —> Project Setting，change Build type。
![](https://imgcache.qq.com/operation/dianshi/other/newBuild.af51c956404867ac237269e78da8ee8e2c556bd1.png)
8. Granting Camera and Mic Permissions

To use the audio/video features of the SDK, you need to grant it mic and camera permissions. Add the two items below to Info.plist of your application. Their content is what users see in the mic and camera access pop-up windows.

* Privacy - Microphone Usage Description, plus a statement specifying why mic access is needed
* Privacy - Camera Usage Description, plus a statement specifying why camera access is needed

![](https://main.qcloudimg.com/raw/7c483aae65f64cd2bf35b55d9c896a52.png)

### What should I do if a network access error occurs on Android?
Copy `/Assets/Plugins/AndroidManifest.xml` to the same directory of your project.

### What should I do if the SDK does not have mic or camera access on Android?
You need to add mic and camera permission requests manually when building for Android. For details, see the code below:
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


