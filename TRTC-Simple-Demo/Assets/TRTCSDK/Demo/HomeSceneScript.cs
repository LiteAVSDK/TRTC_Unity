using LitJson;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
# if PLATFORM_ANDROID
using UnityEngine.Android;
# endif
using trtc;

namespace TRTCCUnityDemo
{
    public class HomeSceneScript : MonoBehaviour
    {
        public GameObject settingPrefab;
        public RectTransform mainCanvas;

        void Start()
        {
            LogManager.Log($"ITRTCCloud.PLUGIN_VERSION = {ITRTCCloud.PLUGIN_VERSION}");
            
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
            
            transform.Find("UserID/editUserID").GetComponent<InputField>().text = DataManager.GetInstance().GetUserID();
            transform.Find("RoomID/editRoomID").GetComponent<InputField>().text = DataManager.GetInstance().GetRoomID();
            transform.Find("Oper/Env/dpEnv").GetComponent<Dropdown>().value = DataManager.GetInstance().GetNetEnv();
            
            var enterRoomBtn = transform.Find("Oper/btnEnterRoom").gameObject.GetComponent<Button>();
            enterRoomBtn.onClick.AddListener(this.OnEnterRoomClick);

            var showSettingBtn = transform.Find("Oper/btnShowSetting").gameObject.GetComponent<Button>();
            showSettingBtn.onClick.AddListener(this.OnShowSettingClick);

            var showApiTestBtn = transform.Find("Oper/btnApiTest").gameObject.GetComponent<Button>();
            showApiTestBtn.onClick.AddListener(this.OnShowApiTestClick);
            
            var version = ITRTCCloud.getTRTCShareInstance().getSDKVersion();
            transform.Find("lblTextVersion").GetComponent<Text>().text = "version:"+version;
        }

        void OnDestroy()
        {

        }

        private void OnEnterRoomClick()
        {
            var userID = transform.Find("UserID/editUserID").GetComponent<InputField>().text;
            var roomID = transform.Find("RoomID/editRoomID").GetComponent<InputField>().text;

            DataManager.GetInstance().SetUserID(userID);
            DataManager.GetInstance().SetRoomID(roomID);
            
            if (GenerateTestUserSig.SDKAPPID != 0 && !string.IsNullOrEmpty(GenerateTestUserSig.SECRETKEY))
            {
                this.ConfigEnv();
                SceneManager.LoadScene("RoomScene", LoadSceneMode.Single);
            }
            else
            {
                Debug.Assert(false, "Please fill in your sdkappid && secretkey first");
            }
        }

        private void ConfigEnv()
        {
            var netEnv = transform.Find("Oper/Env/dpEnv").GetComponent<Dropdown>().value;
            DataManager.GetInstance().SetNetEnv(netEnv);
            
            var data = new JsonData
            {
                ["api"] = "setNetEnv"
            };
            var param = new JsonData
            {
                ["env"] = netEnv
            };
            data["params"] = param;
            var api = data.ToJson();
            LogManager.Log($"call api => {api}");
            ITRTCCloud.getTRTCShareInstance().callExperimentalAPI(api);
        }

        private void OnShowSettingClick()
        {
            var setting = Instantiate(settingPrefab, new Vector3(0, 0, 0), Quaternion.identity);
            setting.transform.SetParent(mainCanvas.transform, false);
        }

        private void OnShowApiTestClick()
        {
            SceneManager.LoadScene("ApiTestScene", LoadSceneMode.Single);
        }
    }
}