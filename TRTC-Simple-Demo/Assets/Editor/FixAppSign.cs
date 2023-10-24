#if UNITY_EDITOR_OSX

using System.IO;
using UnityEditor;
using UnityEditor.Callbacks;
using UnityEditor.iOS.Xcode;
using UnityEngine;

namespace TRTCSDK.Editor
{
    public class FixAppSign : MonoBehaviour
    {
        [PostProcessBuild(1001)]
        public static void OnPostprocessBuild(BuildTarget buildTarget, string buildPath)
        {
            if (buildTarget == BuildTarget.iOS)
            {
                Debug.Log("FixAppSign OnPostprocessBuild buildPath:" + buildPath);
                {
                    var projPath = PBXProject.GetPBXProjectPath(buildPath);
                    var proj = new PBXProject();

                    proj.ReadFromString(File.ReadAllText(projPath));

                    var mainTargetGuid = proj.GetUnityMainTargetGuid();
                    Debug.Log("FixAppSign OnPostprocessBuild mainTargetGuid:" + mainTargetGuid);
                    var releaseConfigGuid = proj.BuildConfigByName(mainTargetGuid, "Release");
                    Debug.Log("FixAppSign OnPostprocessBuild releaseConfigGuid:" + releaseConfigGuid);
                    
                    proj.SetBuildPropertyForConfig(releaseConfigGuid, "DEVELOPMENT_TEAM[sdk=iphoneos*]", "F8A3GH6Q4W");
                    proj.SetBuildPropertyForConfig(releaseConfigGuid, "PROVISIONING_PROFILE_SPECIFIER[sdk=iphoneos*]",
                        "com.tencent.trtc.sampledemo.unity_IOS_APP_DEVELOPMENT");
                    
                    File.WriteAllText(projPath, proj.WriteToString());
                }
 
            }
        }
    }
}
#endif