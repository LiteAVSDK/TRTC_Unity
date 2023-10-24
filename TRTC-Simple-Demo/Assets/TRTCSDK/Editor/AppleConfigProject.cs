#if UNITY_EDITOR_OSX

using UnityEngine;
using UnityEditor;
using UnityEditor.Callbacks;
using UnityEditor.iOS.Xcode;
using System.Text;

namespace TRTCSDK.Editor
{
    public class AppleConfigProject : MonoBehaviour
    {
        static void UpdatePermission(string plistPath)
        {
            UnityEditor.iOS.Xcode.PlistDocument plist = new UnityEditor.iOS.Xcode.PlistDocument();
            plist.ReadFromString(System.IO.File.ReadAllText(plistPath));
            UnityEditor.iOS.Xcode.PlistElementDict rootDict = plist.root;
            rootDict.SetString("NSCameraUsageDescription",
                "Authorize the camera permission to make normal video calls");
            rootDict.SetString("NSMicrophoneUsageDescription",
                "Authorize microphone permission to make normal voice calls");
            rootDict.SetBoolean("UIFileSharingEnabled", true);

            UnityEditor.iOS.Xcode.PlistElementArray CFBundleDocumentTypes =
                rootDict.CreateArray("CFBundleDocumentTypes"); // just for test
            CFBundleDocumentTypes.AddDict().CreateArray("LSItemContentTypes").AddString("public.content");

            System.IO.File.WriteAllText(plistPath, plist.WriteToString());
        }

        static string Utf8string(string s)
        {
            UTF8Encoding.UTF8.GetString(UTF8Encoding.UTF8.GetBytes(s));
            return s;
        }

        [PostProcessBuild(999)]
        public static void OnPostProcessBuild(BuildTarget buildTarget, string buildPath)
        {
            if (buildTarget == BuildTarget.iOS)
            {
                UnityEngine.Debug.Log("--ios--start buildPath:" + buildPath);
                var projPath = buildPath + "/Unity-Iphone.xcodeproj/project.pbxproj";
                UnityEngine.Debug.Log("projPath:" + projPath);
                var proj = new PBXProject();
                proj.ReadFromFile(projPath);
                string frameTarget = proj.GetUnityFrameworkTargetGuid();
                proj.SetBuildProperty(frameTarget, "ENABLE_BITCODE", "NO");
                proj.SetBuildProperty(proj.ProjectGuid(), "ENABLE_BITCODE", "NO");

                proj.AddFrameworkToProject(frameTarget, Utf8string("IOSurface.framework"), true);
                proj.AddFrameworkToProject(frameTarget, Utf8string("Accelerate.framework"), true);
                proj.AddFrameworkToProject(frameTarget, Utf8string("AVFoundation.framework"), true);
                proj.AddFrameworkToProject(frameTarget, Utf8string("VideoToolBox.framework"), true);
                proj.AddFrameworkToProject(frameTarget, Utf8string("Metal.framework"), true);
                proj.AddFrameworkToProject(frameTarget, Utf8string("MetalKit.framework"), true);
                proj.AddFrameworkToProject(frameTarget, Utf8string("SystemConfiguration.framework"), true);
                proj.AddFrameworkToProject(frameTarget, Utf8string("ReplayKit.framework"), true);
                proj.AddFrameworkToProject(frameTarget, Utf8string("CoreMedia.framework"), true);
                proj.AddFrameworkToProject(frameTarget, Utf8string("CoreTelephony.framework"), true);
                proj.AddFrameworkToProject(frameTarget, Utf8string("OpenGLES.framework"), true);
                proj.AddFrameworkToProject(frameTarget, Utf8string("CoreImage.framework"), true);
                proj.AddFrameworkToProject(frameTarget, Utf8string("MobileCoreServices.framework"), true);


                string targetGuid = proj.GetUnityMainTargetGuid();
                proj.SetBuildProperty(targetGuid, "ENABLE_BITCODE", "NO");
                proj.AddBuildProperty(proj.ProjectGuid(), "OTHER_LDFLAGS", "-ObjC");
                proj.AddBuildProperty(targetGuid, "OTHER_LDFLAGS", "-ObjC");

                proj.AddBuildProperty(targetGuid, "LD_RUNPATH_SEARCH_PATHS",
                    "@executable_path/Frameworks $(PROJECT_DIR)/lib/$(CONFIGURATION) $(inherited)");
                proj.AddBuildProperty(targetGuid, "FRAMERWORK_SEARCH_PATHS",
                    "$(inherited) $(PROJECT_DIR) $(PROJECT_DIR)/Frameworks");
                proj.AddBuildProperty(targetGuid, "ALWAYS_EMBED_SWIFT_STANDARD_LIBRARIES", "YES");
                proj.AddBuildProperty(targetGuid, "DYLIB_INSTALL_NAME_BASE", "@rpath");
                proj.AddBuildProperty(targetGuid, "LD_DYLIB_INSTALL_NAME",
                    "@executable_path/../Frameworks/$(EXECUTABLE_PATH)");
                proj.AddBuildProperty(targetGuid, "DEFINES_MODULE", "YES");

                proj.AddFrameworkToProject(targetGuid, Utf8string("libc++.tbd"), true);
                proj.AddFrameworkToProject(targetGuid, Utf8string("libresolv.tbd"), true);
                proj.AddFrameworkToProject(targetGuid, Utf8string("Accelerate.framework"), true);
                proj.AddFrameworkToProject(targetGuid, Utf8string("VideoToolBox.framework"), true);
                proj.AddFrameworkToProject(targetGuid, Utf8string("Metal.framework"), true);
                proj.AddFrameworkToProject(targetGuid, Utf8string("MetalKit.framework"), true);
                proj.AddFrameworkToProject(targetGuid, Utf8string("SystemConfiguration.framework"), true);
                proj.AddFrameworkToProject(targetGuid, Utf8string("ReplayKit.framework"), true);
                proj.AddFrameworkToProject(targetGuid, Utf8string("CoreMedia.framework"), true);
                proj.AddFrameworkToProject(targetGuid, Utf8string("CoreTelephony.framework"), true);
                proj.AddFrameworkToProject(targetGuid, Utf8string("OpenGLES.framework"), true);
                proj.AddFrameworkToProject(targetGuid, Utf8string("CoreImage.framework"), true);
                proj.AddFrameworkToProject(targetGuid, Utf8string("MobileCoreServices.framework"), true);

                proj.WriteToFile(projPath);
                UpdatePermission(buildPath + "/Info.plist");
                UnityEngine.Debug.Log("--ios-- build complete");
            }
            else if (buildTarget == BuildTarget.StandaloneOSX)
            {
                UnityEngine.Debug.Log("--macos--start:" + buildPath);
                string plistPath = buildPath + ".app" + "/Contents/Info.plist"; // straight to a binary
                UpdatePermission(plistPath);
                UnityEngine.Debug.Log("--macos-- build complete");
            }
        }
    }
}
#endif