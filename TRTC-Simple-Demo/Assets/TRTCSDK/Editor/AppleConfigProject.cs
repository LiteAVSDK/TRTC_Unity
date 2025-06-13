#if UNITY_EDITOR_OSX

using UnityEngine;
using UnityEditor;
using UnityEditor.Callbacks;
using UnityEditor.iOS.Xcode;
using System.Text;

namespace TRTCSDK.Editor {
  public class AppleConfigProject : MonoBehaviour {
    static string Utf8string(string s) {
      UTF8Encoding.UTF8.GetString(UTF8Encoding.UTF8.GetBytes(s));
      return s;
    }

    [PostProcessBuild(1001)]
    public static void OnPostProcessBuild(BuildTarget buildTarget, string buildPath) {
      if (buildTarget == BuildTarget.iOS) {
        Debug.Log("--ios--start buildPath:" + buildPath);
        var projPath = buildPath + "/Unity-Iphone.xcodeproj/project.pbxproj";
        Debug.Log("projPath:" + projPath);
        var proj = new PBXProject();
        proj.ReadFromFile(projPath);
        
        proj.SetBuildProperty(proj.ProjectGuid(), "ENABLE_BITCODE", "NO");
        proj.AddBuildProperty(proj.ProjectGuid(), "OTHER_LDFLAGS", "-ObjC");
        
        var frameTarget = proj.GetUnityFrameworkTargetGuid();
        
        proj.SetBuildProperty(frameTarget, "ENABLE_BITCODE", "NO");

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

        var mainTarget = proj.GetUnityMainTargetGuid();
        
        proj.SetBuildProperty(mainTarget, "ENABLE_BITCODE", "NO");
        proj.AddBuildProperty(mainTarget, "OTHER_LDFLAGS", "-ObjC");
        proj.AddBuildProperty(
            mainTarget, "LD_RUNPATH_SEARCH_PATHS",
            "@executable_path/Frameworks $(PROJECT_DIR)/lib/$(CONFIGURATION) $(inherited)");
        proj.AddBuildProperty(mainTarget, "FRAMERWORK_SEARCH_PATHS",
                              "$(inherited) $(PROJECT_DIR) $(PROJECT_DIR)/Frameworks");
        proj.AddBuildProperty(mainTarget, "ALWAYS_EMBED_SWIFT_STANDARD_LIBRARIES", "YES");
        proj.AddBuildProperty(mainTarget, "DYLIB_INSTALL_NAME_BASE", "@rpath");
        proj.AddBuildProperty(mainTarget, "LD_DYLIB_INSTALL_NAME",
                              "@executable_path/../Frameworks/$(EXECUTABLE_PATH)");
        proj.AddBuildProperty(mainTarget, "DEFINES_MODULE", "YES");

        proj.AddFrameworkToProject(mainTarget, Utf8string("Accelerate.framework"), true);
        proj.AddFrameworkToProject(mainTarget, Utf8string("VideoToolBox.framework"), true);
        proj.AddFrameworkToProject(mainTarget, Utf8string("Metal.framework"), true);
        proj.AddFrameworkToProject(mainTarget, Utf8string("MetalKit.framework"), true);
        proj.AddFrameworkToProject(mainTarget, Utf8string("SystemConfiguration.framework"), true);
        proj.AddFrameworkToProject(mainTarget, Utf8string("ReplayKit.framework"), true);
        proj.AddFrameworkToProject(mainTarget, Utf8string("CoreMedia.framework"), true);
        proj.AddFrameworkToProject(mainTarget, Utf8string("CoreTelephony.framework"), true);
        proj.AddFrameworkToProject(mainTarget, Utf8string("OpenGLES.framework"), true);
        proj.AddFrameworkToProject(mainTarget, Utf8string("CoreImage.framework"), true);
        proj.AddFrameworkToProject(mainTarget, Utf8string("MobileCoreServices.framework"), true);

        proj.WriteToFile(projPath);
        Debug.Log("--ios-- build complete");
      } else if (buildTarget == BuildTarget.StandaloneOSX) {
        Debug.Log("--macos-- build complete");
      }
    }
  }
}

#endif