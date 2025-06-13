#if UNITY_EDITOR_OSX

using System;
using System.IO;
using UnityEditor;
using UnityEditor.Callbacks;
using UnityEditor.iOS.Xcode;
using UnityEngine;

namespace TRTCSDK.Editor {
  public class FixAppSign : MonoBehaviour {
    private static bool IsPipeline() {
      var pipelineId = Environment.GetEnvironmentVariable("BK_CI_PIPELINE_ID");
      return !string.IsNullOrEmpty(pipelineId);
    }

    [PostProcessBuild(1003)]
    public static void OnPostprocessBuild(BuildTarget buildTarget, string buildPath) {
      if (buildTarget == BuildTarget.iOS) {
        Debug.Log("FixAppSign OnPostprocessBuild buildPath:" + buildPath);
        {
          var projPath = PBXProject.GetPBXProjectPath(buildPath);
          var proj = new PBXProject();

          proj.ReadFromString(File.ReadAllText(projPath));

          var mainTargetGuid = proj.GetUnityMainTargetGuid();
          Debug.Log("FixAppSign OnPostprocessBuild mainTargetGuid:" + mainTargetGuid);
          var releaseConfigGuid = proj.BuildConfigByName(mainTargetGuid, "Release");
          Debug.Log("FixAppSign OnPostprocessBuild releaseConfigGuid:" + releaseConfigGuid);

          if (IsPipeline()) {
            proj.SetBuildPropertyForConfig(releaseConfigGuid, "DEVELOPMENT_TEAM[sdk=iphoneos*]",
                                           "FN2V63AD2J");
            proj.SetBuildPropertyForConfig(releaseConfigGuid,
                                           "PROVISIONING_PROFILE_SPECIFIER[sdk=iphoneos*]",
                                           "com.tencent.trtc.demo.unity_Development_SignProvision");
          }

          File.WriteAllText(projPath, proj.WriteToString());
        }
        // for file shared
        {
          var plist = new PlistDocument();
          var plistFile = buildPath + "/Info.plist";
          plist.ReadFromString(File.ReadAllText(plistFile));
          plist.root.SetBoolean("UIFileSharingEnabled", true);
          File.WriteAllText(plistFile, plist.WriteToString());
        }
      }
    }
  }
}
#endif