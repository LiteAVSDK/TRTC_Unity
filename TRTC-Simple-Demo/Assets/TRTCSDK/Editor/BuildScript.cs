using System.IO;
using UnityEditor;
using UnityEngine;
using System.Collections.Generic;
using System;

namespace TRTCSDK.Editor
{
    public class BuildScript : UnityEditor.Editor
    {
        public static string projectName
        {
            get { return "TRTCUnityDemo"; }
        }

        public static String[] GetBuildScenes()
        {
            List<string> names = new List<String>();
            names.Add("Assets/TRTCSDK/Demo/HomeScene.unity");
            names.Add("Assets/TRTCSDK/Demo/RoomScene.unity");
            names.Add("Assets/TRTCSDK/Demo/ApiTestScene.unity");
            return names.ToArray();
        }

        [MenuItem("TRTC Build Configuration Tool/Windows x64", false, 50)]
        public static void BuildWindowsx64()
        {
            BuildPipeline.BuildPlayer(GetBuildScenes(), "Builds\\x64\\" + projectName + ".exe",
                BuildTarget.StandaloneWindows64,
                BuildOptions.Development);
        }

        [MenuItem("TRTC Build Configuration Tool/Windows x86", false, 50)]
        public static void BuildWindowsx86()
        {
            BuildPipeline.BuildPlayer(GetBuildScenes(), "Builds\\x86\\" + projectName + ".exe",
                BuildTarget.StandaloneWindows,
                BuildOptions.Development);
        }

        [MenuItem("TRTC Build Configuration Tool/Windows All", false, 50)]
        public static void BuildWindowsAll()
        {
            BuildWindowsx64();
            BuildWindowsx86();
        }

        [MenuItem("TRTC Build Configuration Tool/macOS", false, 50)]
        public static void BuildOSXUniversal()
        {
            BuildPipeline.BuildPlayer(GetBuildScenes(), "Builds\\macOS\\" + projectName, BuildTarget.StandaloneOSX,
                BuildOptions.Development);
        }

        [MenuItem("TRTC Build Configuration Tool/Android", false, 50)]
        public static void BuildAndroid()
        {
            BuildPipeline.BuildPlayer(GetBuildScenes(), "Builds\\Android\\" + projectName + ".apk", BuildTarget.Android,
                BuildOptions.Development);
        }

        [MenuItem("TRTC Build Configuration Tool/IOS", false, 50)]
        public static void BuildIOS()
        {
            BuildPipeline.BuildPlayer(GetBuildScenes(), "Builds\\iOS\\" + projectName, BuildTarget.iOS,
                BuildOptions.Development);
        }

        [MenuItem("TRTC Build Configuration Tool/WebGL", false, 50)]
        public static void BuildWebGL()
        {
            BuildPipeline.BuildPlayer(GetBuildScenes(), "Builds\\WebGL\\" + projectName, BuildTarget.WebGL,
                BuildOptions.Development);
        }
        
        [MenuItem("TRTC Build Configuration Tool/All", false, 50)]
        public static void BuildAll()
        {
            BuildAndroid();
            BuildIOS();
            BuildOSXUniversal();
            BuildWindowsAll();
        }

        [MenuItem("TRTC Build Configuration Tool/Export Package", false, 50)]
        public static void ExportPackage()
        {
            var exportPath = Path.Combine(Application.dataPath, "..", "Builds", "Package");
            string[] exportFiles =
            {
                "Assets/TRTCSDK"
            };
            if (!Directory.Exists(exportPath)) Directory.CreateDirectory(exportPath);
            AssetDatabase.ExportPackage(exportFiles, Path.Combine(exportPath, "TRTCUnitySDK.unitypackage"),
                ExportPackageOptions.Recurse);
            Debug.Log("ExportPackage End");
        }
    }
}