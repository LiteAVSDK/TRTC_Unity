#if UNITY_EDITOR_OSX

using System.Collections.Generic;
using System.IO;
using UnityEditor;
using UnityEditor.Callbacks;
using UnityEngine;
using UnityEditor.iOS.Xcode;
using UnityEditor.iOS.Xcode.Extensions;

namespace TRTCSDK.Editor {
  public class IOSAddDylib : MonoBehaviour {
    private static List<string> GetDirectoryNames(string folderName, string extension) {
      string[] directories =
          Directory.GetDirectories(folderName, $"*.{extension}", SearchOption.TopDirectoryOnly);

      var result = new List<string>();
      foreach (var directory in directories) {
        result.Add(Path.GetFileName(directory));
      }
      return result;
    }

    [PostProcessBuild(1002)]
    public static void OnPostprocessBuild(BuildTarget buildTarget, string buildPath) {
      if (buildTarget != BuildTarget.iOS) {
        return;
      }

      // Point to the 'Assets' path
      var dataPath = Application.dataPath;

      Debug.Log("IOSAddDylib OnPostprocessBuild buildPath:" + buildPath);
      Debug.Log("IOSAddDylib OnPostprocessBuild dataPath:" + dataPath);

      var xcFrameworksPath = dataPath + "/TRTCSDK/SDK/Plugins/iOS/XCFrameworks~/";

      var absPath = "Frameworks/TRTCSDK/SDK/Plugins/iOS/";
      var destPath = buildPath + "/" + absPath;

      if (!Directory.Exists(buildPath)) {
        Directory.CreateDirectory(buildPath);
      }

      string[] folderNames = { "Frameworks", "TRTCSDK", "SDK", "Plugins", "iOS" };
      var tmpPath = buildPath;
      foreach (var folderName in folderNames) {
        var folderPath = Path.Combine(tmpPath, folderName);
        if (!Directory.Exists(folderPath))
          Directory.CreateDirectory(folderPath);

        tmpPath = folderPath;
      }

      List<string> sdkNames;
      if (Directory.Exists(xcFrameworksPath) &&
          Directory.GetDirectories(xcFrameworksPath).Length > 0) {
        sdkNames = GetDirectoryNames(xcFrameworksPath, "xcframework");
        {
          foreach (var name in sdkNames) {
            FileUtil.CopyFileOrDirectory(xcFrameworksPath + name, destPath + name);
          }
        }
      } else {
        sdkNames = GetDirectoryNames(destPath, "framework");
      }

      {
        // add depend
        var pbxProjectPath = PBXProject.GetPBXProjectPath(buildPath);
        var project = new PBXProject();
        project.ReadFromFile(pbxProjectPath);

        // Unity-iPhone
        var mainGuid = project.GetUnityMainTargetGuid();
        Debug.Log($"iOSAddDylib mainGuid = {mainGuid}");

        // UnityFramework
        var frameGuid = project.GetUnityFrameworkTargetGuid();
        Debug.Log($"iOSAddDylib  frameGuid = {frameGuid}");

        // UnityFramework -> Frameworks
        var unityFrameFrameGuid = project.GetFrameworksBuildPhaseByTarget(frameGuid);
        Debug.Log($"iOSAddDylib unityFrameFrameGuid = {unityFrameFrameGuid}");

        // add & embed
        foreach (var name in sdkNames) {
          var frameworkPath = absPath + name;
          var fileGuid = project.AddFile(frameworkPath, frameworkPath);
          project.AddFileToEmbedFrameworks(mainGuid, fileGuid);
          project.AddFileToBuildSection(frameGuid, unityFrameFrameGuid, fileGuid);
        }

        File.WriteAllText(pbxProjectPath, project.WriteToString());
      }
    }
  }
}
#endif