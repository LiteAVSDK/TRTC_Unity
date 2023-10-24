#if UNITY_EDITOR_OSX

using System.IO;
using UnityEditor;
using UnityEditor.Callbacks;
using UnityEngine;
using UnityEditor.iOS.Xcode;
using UnityEditor.iOS.Xcode.Extensions;

namespace TRTCSDK.Editor
{
    public class IOSAddDylib : MonoBehaviour
    {
        [PostProcessBuild(1002)]
        public static void OnPostprocessBuild(BuildTarget buildTarget, string buildPath)
        {
            if (buildTarget == BuildTarget.iOS)
            {
                // Point to the 'Assets' path 
                var dataPath = Application.dataPath;

                Debug.Log("IOSAddDylib OnPostprocessBuild buildPath:" + buildPath);
                Debug.Log("IOSAddDylib OnPostprocessBuild dataPath:" + dataPath);

                var sdkPath = dataPath + "/TRTCSDK/SDK/Plugins/iOS/XCFrameworks~/";
                var absPath = "Frameworks/TRTCSDK/SDK/Plugins/iOS/";
                var destPath = buildPath + "/" + absPath;

                if (!Directory.Exists(buildPath)) Directory.CreateDirectory(buildPath);

                string[] folderNames = { "Frameworks", "TRTCSDK", "SDK", "Plugins", "iOS" };
                var tmpPath = buildPath;
                foreach (var folderName in folderNames)
                {
                    var folderPath = Path.Combine(tmpPath, folderName);
                    if (!Directory.Exists(folderPath)) Directory.CreateDirectory(folderPath);

                    tmpPath = folderPath;
                }

                string[] sdkNames =
                {
                    "TXLiteAVSDK_TRTC.xcframework"
                };
                string[] addonNames =
                {
                    "TXFFmpeg.xcframework",
                    "TXSoundTouch.xcframework"
                };

                {
                    //copy all to destPath path
                    foreach (var name in sdkNames) FileUtil.CopyFileOrDirectory(sdkPath + name, destPath + name);
                    foreach (var name in addonNames) FileUtil.CopyFileOrDirectory(sdkPath + name, destPath + name);
                }

                {
                    //add depend
                    var pbxProjectPath = PBXProject.GetPBXProjectPath(buildPath);
                    var project = new PBXProject();
                    project.ReadFromFile(pbxProjectPath);

                    //Unity-iPhone
                    var mainTargetGuid = project.GetUnityMainTargetGuid();
                    Debug.Log("iOSAddDylib OnPostprocessBuild MainTargetGuid:" + mainTargetGuid);
                    //UnityFramework
                    var frameworkTargetGuid = project.GetUnityFrameworkTargetGuid();
                    Debug.Log("iOSAddDylib OnPostprocessBuild FrameworkTargetGuid:" + frameworkTargetGuid);
                    //UnityFramework -> Frameworks
                    var unityFrameworkFrameworksGuid = project.GetFrameworksBuildPhaseByTarget(frameworkTargetGuid);
                    Debug.Log("iOSAddDylib OnPostprocessBuild UnityFrameworkFrameworksGuid:" +
                              unityFrameworkFrameworksGuid);

                    //add
                    foreach (var name in sdkNames)
                    {
                        var frameworkPath = absPath + name;
                        var fileGuid = project.AddFile(frameworkPath, frameworkPath);
                        project.AddFileToBuildSection(frameworkTargetGuid, unityFrameworkFrameworksGuid, fileGuid);
                    }

                    //add & embed
                    foreach (var name in addonNames)
                    {
                        var frameworkPath = absPath + name;
                        var fileGuid = project.AddFile(frameworkPath, frameworkPath);
                        project.AddFileToEmbedFrameworks(mainTargetGuid, fileGuid);
                        project.AddFileToBuildSection(frameworkTargetGuid, unityFrameworkFrameworksGuid, fileGuid);
                    }

                    File.WriteAllText(pbxProjectPath, project.WriteToString());
                }
            }
        }
    }
}
#endif