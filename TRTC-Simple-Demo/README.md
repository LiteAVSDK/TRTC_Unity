[简体中文](./README-zh_CN.md) | English

This document shows how to integrate the TRTC SDK in Unity to enable audio/video calls in games.

The demo includes the following features:
- Room entry/exit
- Custom video rendering
- Device management and music/voice effects

> For details about API features and parameters, please see [Client APIs > Unity > Overview](https://intl.cloud.tencent.com/document/product/647/40139).

## Environmental description
- Unity 2020.2.1f1c1 is recommended.
- Supported platforms: Android, iOS, Windows, macOS (alpha testing)
- Modules required: `Android Build Support`, `iOS Build Support`, `Windows Build Support`, `MacOS Build Support`
- If you are developing for iOS, you also need:
  - Xcode 11.0 or above
  - A valid developer signature for your project

## Directions
[](id:step1)
### Step 1. Create an application
1. Log in to the TRTC console and select **Development Assistance** > **[Create application](https://console.tencentcloud.com/trtc/app/create)**.
2. Enter an application name such as `TestTRTC` and click **Create**.
![ #900px](https://qcloudimg.tencent-cloud.cn/raw/51c73a617e69a76ed26e6f74b0071ec9.png)

[](id:step2)
### Step 2. Download the SDK and source code
1. Download the SDK and [Demo source code](https://github.com/LiteAVSDK/TRTC_Unity).
2. Click **Next**. You can open the project with Unity, or copy `/SDK` in the SDK ZIP file to the `Assets` directory of your project.

3. Find and open `TRTC-Simple-Demo/Assets/TRTCSDK/Demo/Tools/GenerateTestUserSig.cs`.
4. Set parameters in `GenerateTestUserSig.cs` as follows:
  <ul><li>SDKAPPID: `0` by default. Set it to the actual `SDKAppID`.</li>
  <li>SECRETKEY: left empty by default. Set it to the actual key.</li></ul> 

![ #900px](https://qcloudimg.tencent-cloud.cn/raw/429ae90ac533b37c0036bebdc38d0488/TRTC-create-application-sdkAppId.png)

[](id:step3)
### Step 3. Compile and run

#### Android
1. Open Unity Editor, go to **File** > **Build Settings**, and select **Android** for **Platform**.
![](https://main.qcloudimg.com/raw/4464eb891829e3505a59c8ec00cc2414.png)
2. Connect to a real Android device and click **Build And Run** to run the demo.
3. Call `enterRoom` first and go on to test other APIs. The data display window shows whether the call is successful, and the other window displays the callback information.

#### iOS
1. Open 'TRTC Build Configuration'（You can find it in the navigation bar at the top of the unity editor）
2. Click 'IOS'，Wait for project generation to complete
![](https://imgcache.qq.com/operation/dianshi/other/ios-en.a177d686f175b086b565565c66e35b9a07accaed.png)
3. Use Xcode to open the generated 'Unity-iPhone.xcodeproj' project
4. Download [TRTC SDK](https://comm.qq.com/trtc/TRTC_9.7.0.11440_iOS.zip).You need to manually add the dynamic libraries.
Click General, expand Frameworks, Libraries, and Embedded Content, and click the + icon at the bottom to add the dynamic libraries required in turn:  FFmpeg.xcframework, and SoundTouch.xcframework. Click Embed & Sign.
![](https://imgcache.qq.com/operation/dianshi/other/unity.ca7b6e717bf7b34e4f08a7e688ff59bf49d92217.png)
5. Connects IOS device for debugging

#### Windows
1. Open Unity Editor, go to **File** > **Build Settings**, and select **PC, Mac & Linux Standalone** for **Platform** and **Windows** for **Target Platform**.
![](https://main.qcloudimg.com/raw/580764f661c06cf71c4952727c409c5e.png)
2. Click **Build And Run** to run the demo.

#### macOS
1. Open Unity Editor, go to **File** > **Build Settings**, and select **PC, Mac & Linux Standalone** for **Platform**, and **macOS** for **Target Platform**.
![](https://main.qcloudimg.com/raw/6f3f9c21aa9eeadd7a4e3be377b2a6b3.png)
2. Click **Build And Run** to run the demo.
3. To use the simulator feature of Unity Editor, you must install `Device Simulator Package`.
4. Click **Windows** > **General** > **Device Simulator**.
![](https://main.qcloudimg.com/raw/79f707b89553528956a888f48b4d4d6d.png)

[](id:demo)
## Demo
The demo integrates most of the APIs launched so far, which can be used for testing and as reference for API calls. For more information about APIs, see [Client APIs > Unity > Overview](https://intl.cloud.tencent.com/document/product/647/40139).
> The UI of the latest version of the demo may look different.

![](https://main.qcloudimg.com/raw/2ce3ab51c6fdc843c1e8b086b55840c0.png)

## Directory Structure
```
├─Assets
├── Editor                        // Unity Editor script
│   ├── BuildScript.cs            // Unity Editor build menu
│   ├── IosPostProcess.cs         // Script for building iOS application in Unity Editor
├── Plugins
│   ├── Android                   
│   │   ├── AndroidManifest.xml   //Android configuration file
├── StreamingAssets               // Audio/video stream files for the Unity demo
├── TRTCSDK
    ├── Demo                      // Unity demo
    ├── SDK                       // TRTC SDK for Unity
        ├── Implement             // Implementation of TRTC SDK for Unity
        ├── Include               // Header files of TRTC SDK for Unity
        └── Plugins               // Underlying implementation of TRTC SDK for Unity for different platforms
            
```
