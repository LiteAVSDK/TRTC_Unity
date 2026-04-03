using UnityEngine;
using UnityEngine.UI;
using trtc;
namespace TRTCCUnityDemo {
  public class SnapshotScript : MonoBehaviour {
    public InputField userIdInputField;
    public Dropdown streamTypeDropdown;
    public Dropdown sourceTypeDropdown;
    private ITRTCCloud mTRTCCloud;
    public Button startButton;

    void Start() {
      mTRTCCloud = ITRTCCloud.getTRTCShareInstance();
      startButton.onClick.AddListener(OnConfirmSnapshot);
    }

    public void OnConfirmSnapshot() {
      string userId = userIdInputField.text.Trim();

      if (string.IsNullOrEmpty(userId)) {
        userId = "";
      }

      TRTCVideoStreamType streamType = GetStreamTypeFromDropdown(streamTypeDropdown.value);
      TRTCSnapshotSourceType sourceType = GetSourceTypeFromDropdown(sourceTypeDropdown.value);

      LogManager.Log($"SnapshotVideo - userId: {userId}, streamType: {streamType}, sourceType: {sourceType}");
      mTRTCCloud.snapshotVideo(userId, streamType, sourceType);
    }

    private TRTCVideoStreamType GetStreamTypeFromDropdown(int value) {
      switch (value) {
        case 0:
          return TRTCVideoStreamType.TRTCVideoStreamTypeBig;
        case 1:
          return TRTCVideoStreamType.TRTCVideoStreamTypeSmall;
        case 2:
          return TRTCVideoStreamType.TRTCVideoStreamTypeSub;
        default:
          return TRTCVideoStreamType.TRTCVideoStreamTypeBig;
      }
    }

    private TRTCSnapshotSourceType GetSourceTypeFromDropdown(int value) {
      switch (value) {
        case 0:
          return TRTCSnapshotSourceType.TRTCSnapshotSourceTypeStream;
        case 1:
          return TRTCSnapshotSourceType.TRTCSnapshotSourceTypeView;
        default:
          return TRTCSnapshotSourceType.TRTCSnapshotSourceTypeStream;
      }
    }
  }
}
