using System;
using UnityEngine;
using UnityEngine.UI;
using trtc;

namespace TRTCCUnityDemo {
  public class Spatial3DAudioPanel : MonoBehaviour {
    private ITRTCCloud mTRTCCloud;
    private GameObject panelRoot;
    private Action<string> logAction;

    private int selfX = 0, selfY = 0, selfZ = 0;
    private int remoteX = 100, remoteY = 0, remoteZ = 0;
    private int receivingRange = 500;
    private string remoteUserId = "345";
    private string rangeUserId = "345";

    private float[] axisForward = new float[] { 1.0f, 0.0f, 0.0f };
    private float[] axisRight = new float[] { 0.0f, 1.0f, 0.0f };
    private float[] axisUp = new float[] { 0.0f, 0.0f, 1.0f };

    private Text lblSelfPos;
    private Text lblRemotePos;
    private Text lblRange;
    private InputField remoteUserIdInput;
    private InputField rangeUserIdInput;

    public static Spatial3DAudioPanel Show(Canvas canvas, Font font, ITRTCCloud cloud, Action<string> logCallback) {
      GameObject panelObj = new GameObject("Spatial3DAudioPanel");
      panelObj.transform.SetParent(canvas.transform, false);
      var panel = panelObj.AddComponent<Spatial3DAudioPanel>();
      panel.mTRTCCloud = cloud;
      panel.logAction = logCallback;
      panel.CreateUI(canvas, font);
      return panel;
    }

    public void Close() {
      if (panelRoot != null) Destroy(panelRoot);
      Destroy(gameObject);
    }

    private void CreateUI(Canvas canvas, Font font) {
      panelRoot = new GameObject("Overlay", typeof(RectTransform), typeof(Image), typeof(Button));
      panelRoot.transform.SetParent(canvas.transform, false);
      var rootRT = panelRoot.GetComponent<RectTransform>();
      rootRT.anchorMin = Vector2.zero;
      rootRT.anchorMax = Vector2.one;
      rootRT.offsetMin = Vector2.zero;
      rootRT.offsetMax = Vector2.zero;
      panelRoot.GetComponent<Image>().color = new Color(0, 0, 0, 0.5f);
      panelRoot.GetComponent<Button>().onClick.AddListener(() => Close());

      GameObject dialog = CreateDialog(panelRoot, font);
      dialog.AddComponent<Button>().onClick.AddListener(() => { /* 空：阻止事件穿透到遮罩 */ });
    }

    private GameObject CreateDialog(GameObject parent, Font font) {
      GameObject dialog = new GameObject("Dialog", typeof(RectTransform), typeof(Image));
      dialog.transform.SetParent(parent.transform, false);
      var rt = dialog.GetComponent<RectTransform>();
      rt.anchorMin = new Vector2(0.15f, 0.5f);
      rt.anchorMax = new Vector2(0.15f, 0.5f);
      rt.pivot = new Vector2(0.5f, 0.5f);
      rt.sizeDelta = new Vector2(750, 950);
      dialog.GetComponent<Image>().color = new Color(0.18f, 0.18f, 0.22f, 1f);
      GameObject titleBar = new GameObject("TitleBar", typeof(RectTransform), typeof(Image));
      titleBar.transform.SetParent(dialog.transform, false);
      var titleBarRT = titleBar.GetComponent<RectTransform>();
      titleBarRT.anchorMin = new Vector2(0, 1);
      titleBarRT.anchorMax = new Vector2(1, 1);
      titleBarRT.pivot = new Vector2(0.5f, 1);
      titleBarRT.sizeDelta = new Vector2(0, 60);
      titleBarRT.anchoredPosition = Vector2.zero;
      titleBar.GetComponent<Image>().color = new Color(0.08f, 0.08f, 0.1f, 1f);
      GameObject closeBtn = new GameObject("CloseBtn", typeof(RectTransform), typeof(Button), typeof(Image));
      closeBtn.transform.SetParent(titleBar.transform, false);
      var closeBtnRT = closeBtn.GetComponent<RectTransform>();
      closeBtnRT.anchorMin = new Vector2(1, 0.5f);
      closeBtnRT.anchorMax = new Vector2(1, 0.5f);
      closeBtnRT.pivot = new Vector2(1, 0.5f);
      closeBtnRT.anchoredPosition = new Vector2(-10, 0);
      closeBtnRT.sizeDelta = new Vector2(50, 50);
      closeBtn.GetComponent<Image>().color = new Color(0.8f, 0.25f, 0.25f, 1f);
      AddText(closeBtn, font, "X", 28, Color.white, TextAnchor.MiddleCenter, FontStyle.Bold);
      closeBtn.GetComponent<Button>().onClick.AddListener(() => Close());

      GameObject scrollArea = new GameObject("ScrollArea", typeof(RectTransform), typeof(ScrollRect));
      scrollArea.transform.SetParent(dialog.transform, false);
      var scrollRT = scrollArea.GetComponent<RectTransform>();
      scrollRT.anchorMin = new Vector2(0, 0);
      scrollRT.anchorMax = new Vector2(1, 1);
      scrollRT.offsetMin = new Vector2(15, 15);
      scrollRT.offsetMax = new Vector2(-15, -65);

      GameObject viewport = new GameObject("Viewport", typeof(RectTransform), typeof(Image), typeof(Mask));
      viewport.transform.SetParent(scrollArea.transform, false);
      var vpRT = viewport.GetComponent<RectTransform>();
      vpRT.anchorMin = Vector2.zero;
      vpRT.anchorMax = Vector2.one;
      vpRT.offsetMin = Vector2.zero;
      vpRT.offsetMax = Vector2.zero;
      viewport.GetComponent<Image>().color = new Color(1, 1, 1, 0.01f);
      viewport.GetComponent<Mask>().showMaskGraphic = false;

      GameObject content = new GameObject("Content", typeof(RectTransform), typeof(VerticalLayoutGroup), typeof(ContentSizeFitter));
      content.transform.SetParent(viewport.transform, false);
      var contentRT = content.GetComponent<RectTransform>();
      contentRT.anchorMin = new Vector2(0, 1);
      contentRT.anchorMax = new Vector2(1, 1);
      contentRT.pivot = new Vector2(0.5f, 1);
      contentRT.offsetMin = Vector2.zero;
      contentRT.offsetMax = Vector2.zero;
      var vlg = content.GetComponent<VerticalLayoutGroup>();
      vlg.childAlignment = TextAnchor.UpperLeft;
      vlg.spacing = 12;
      vlg.padding = new RectOffset(10, 30, 5, 5);
      vlg.childForceExpandWidth = true;
      vlg.childForceExpandHeight = false;
      content.GetComponent<ContentSizeFitter>().verticalFit = ContentSizeFitter.FitMode.PreferredSize;

      var sr = scrollArea.GetComponent<ScrollRect>();
      sr.content = contentRT;
      sr.viewport = vpRT;
      sr.horizontal = false;
      sr.vertical = true;
      sr.movementType = ScrollRect.MovementType.Clamped;
      BuildContent(content, font);

      return dialog;
    }

    private void BuildContent(GameObject content, Font font) {
      AddSection(content, font, "▎自身坐标");
      lblSelfPos = AddLabel(content, font, GetSelfPosText(), 24, Color.yellow);
      AddSlider(content, font, "X", -500, 500, selfX, (v) => { selfX = (int)v; UpdateSelfPosition(); });
      AddSlider(content, font, "Y", -500, 500, selfY, (v) => { selfY = (int)v; UpdateSelfPosition(); });
      AddSlider(content, font, "Z", -500, 500, selfZ, (v) => { selfZ = (int)v; UpdateSelfPosition(); });

      AddSpacer(content, 15);

      AddSection(content, font, "▎远端用户坐标");
      remoteUserIdInput = AddInput(content, font, "用户ID", remoteUserId, (v) => { remoteUserId = v; });
      lblRemotePos = AddLabel(content, font, GetRemotePosText(), 24, Color.yellow);
      AddSlider(content, font, "X", -500, 500, remoteX, (v) => { remoteX = (int)v; UpdateRemotePosition(); });
      AddSlider(content, font, "Y", -500, 500, remoteY, (v) => { remoteY = (int)v; UpdateRemotePosition(); });
      AddSlider(content, font, "Z", -500, 500, remoteZ, (v) => { remoteZ = (int)v; UpdateRemotePosition(); });

      AddSpacer(content, 15);

      AddSection(content, font, "▎声音衰减范围");
      rangeUserIdInput = AddInput(content, font, "用户ID", rangeUserId, (v) => { rangeUserId = v; });
      lblRange = AddLabel(content, font, GetRangeText(), 24, Color.yellow);
      AddSlider(content, font, "Range", 0, 2000, receivingRange, (v) => { receivingRange = (int)v; UpdateReceivingRange(); });
    }
    private void UpdateSelfPosition() {
      int[] pos = new int[] { selfX, selfY, selfZ };
      mTRTCCloud?.updateSelf3DSpatialPosition(pos, axisForward, axisRight, axisUp);
      if (lblSelfPos != null) lblSelfPos.text = GetSelfPosText();
      logAction?.Invoke($"updateSelf3DSpatialPosition [{selfX},{selfY},{selfZ}]");
    }

    private void UpdateRemotePosition() {
      int[] pos = new int[] { remoteX, remoteY, remoteZ };
      string uid = remoteUserIdInput != null ? remoteUserIdInput.text : remoteUserId;
      mTRTCCloud?.updateRemote3DSpatialPosition(uid, pos);
      if (lblRemotePos != null) lblRemotePos.text = GetRemotePosText();
      logAction?.Invoke($"updateRemote3DSpatialPosition userId={uid} [{remoteX},{remoteY},{remoteZ}]");
    }

    private void UpdateReceivingRange() {
      string uid = rangeUserIdInput != null ? rangeUserIdInput.text : rangeUserId;
      mTRTCCloud?.set3DSpatialReceivingRange(uid, receivingRange);
      if (lblRange != null) lblRange.text = GetRangeText();
      logAction?.Invoke($"set3DSpatialReceivingRange userId={uid} range={receivingRange}");
    }

    private string GetSelfPosText() { return $"  坐标: [{selfX}, {selfY}, {selfZ}]"; }
    private string GetRemotePosText() { return $"  坐标: [{remoteX}, {remoteY}, {remoteZ}]"; }
    private string GetRangeText() { return $"  范围: {receivingRange}"; }
    private void AddSection(GameObject parent, Font font, string title) {
      var obj = NewLayoutObj(parent, "Section", 40);
      var txt = obj.AddComponent<Text>();
      txt.text = title;
      txt.font = font;
      txt.fontSize = 28;
      txt.color = new Color(0.5f, 0.85f, 1f);
      txt.fontStyle = FontStyle.Bold;
      txt.alignment = TextAnchor.MiddleLeft;
    }

    private Text AddLabel(GameObject parent, Font font, string text, int size, Color color) {
      var obj = NewLayoutObj(parent, "Label", 30);
      var txt = obj.AddComponent<Text>();
      txt.text = text;
      txt.font = font;
      txt.fontSize = size;
      txt.color = color;
      txt.alignment = TextAnchor.MiddleLeft;
      return txt;
    }

    private InputField AddInput(GameObject parent, Font font, string label, string defaultVal, Action<string> onChanged) {
      var row = NewLayoutObj(parent, "InputRow", 44);
      row.AddComponent<HorizontalLayoutGroup>().spacing = 8;
      row.GetComponent<HorizontalLayoutGroup>().childAlignment = TextAnchor.MiddleLeft;
      row.GetComponent<HorizontalLayoutGroup>().childForceExpandWidth = false;
      row.GetComponent<HorizontalLayoutGroup>().childForceExpandHeight = false;

      // Label
      var lbl = new GameObject("Lbl", typeof(RectTransform), typeof(Text), typeof(LayoutElement));
      lbl.transform.SetParent(row.transform, false);
      lbl.GetComponent<LayoutElement>().preferredWidth = 120;
      lbl.GetComponent<LayoutElement>().preferredHeight = 40;
      var lblTxt = lbl.GetComponent<Text>();
      lblTxt.text = "  " + label + ":";
      lblTxt.font = font;
      lblTxt.fontSize = 24;
      lblTxt.color = Color.white;
      lblTxt.alignment = TextAnchor.MiddleLeft;

      // Input
      var inputGo = new GameObject("Input", typeof(RectTransform), typeof(Image), typeof(InputField), typeof(LayoutElement));
      inputGo.transform.SetParent(row.transform, false);
      inputGo.GetComponent<LayoutElement>().preferredWidth = 180;
      inputGo.GetComponent<LayoutElement>().preferredHeight = 40;
      inputGo.GetComponent<Image>().color = new Color(0.28f, 0.28f, 0.32f, 1f);

      var inputText = new GameObject("Text", typeof(RectTransform), typeof(Text));
      inputText.transform.SetParent(inputGo.transform, false);
      var itRT = inputText.GetComponent<RectTransform>();
      itRT.anchorMin = Vector2.zero;
      itRT.anchorMax = Vector2.one;
      itRT.offsetMin = new Vector2(8, 2);
      itRT.offsetMax = new Vector2(-8, -2);
      var itTxt = inputText.GetComponent<Text>();
      itTxt.font = font;
      itTxt.fontSize = 24;
      itTxt.color = Color.white;
      itTxt.alignment = TextAnchor.MiddleLeft;

      var inputField = inputGo.GetComponent<InputField>();
      inputField.textComponent = itTxt;
      inputField.text = defaultVal;
      inputField.onEndEdit.AddListener((v) => onChanged?.Invoke(v));
      return inputField;
    }

    private void AddSlider(GameObject parent, Font font, string label, float min, float max, float defaultVal, Action<float> onChanged) {
      var row = NewLayoutObj(parent, "SliderRow", 40);
      row.AddComponent<HorizontalLayoutGroup>().spacing = 8;
      row.GetComponent<HorizontalLayoutGroup>().childAlignment = TextAnchor.MiddleLeft;
      row.GetComponent<HorizontalLayoutGroup>().childForceExpandWidth = false;
      row.GetComponent<HorizontalLayoutGroup>().childForceExpandHeight = false;

      // Label
      var lbl = new GameObject("Lbl", typeof(RectTransform), typeof(Text), typeof(LayoutElement));
      lbl.transform.SetParent(row.transform, false);
      lbl.GetComponent<LayoutElement>().preferredWidth = 70;
      lbl.GetComponent<LayoutElement>().preferredHeight = 36;
      lbl.GetComponent<Text>().text = "  " + label;
      lbl.GetComponent<Text>().font = font;
      lbl.GetComponent<Text>().fontSize = 24;
      lbl.GetComponent<Text>().color = Color.white;
      lbl.GetComponent<Text>().alignment = TextAnchor.MiddleRight;

      // Slider
      var sliderGo = MakeSlider(row, 220);
      var slider = sliderGo.GetComponent<Slider>();
      slider.minValue = min;
      slider.maxValue = max;
      slider.value = defaultVal;
      slider.wholeNumbers = true;

      // Value
      var val = new GameObject("Val", typeof(RectTransform), typeof(Text), typeof(LayoutElement));
      val.transform.SetParent(row.transform, false);
      val.GetComponent<LayoutElement>().preferredWidth = 70;
      val.GetComponent<LayoutElement>().preferredHeight = 36;
      var valTxt = val.GetComponent<Text>();
      valTxt.text = ((int)defaultVal).ToString();
      valTxt.font = font;
      valTxt.fontSize = 24;
      valTxt.color = Color.yellow;
      valTxt.alignment = TextAnchor.MiddleLeft;

      slider.onValueChanged.AddListener((v) => {
        valTxt.text = ((int)v).ToString();
        onChanged?.Invoke(v);
      });
    }

    private void AddSpacer(GameObject parent, float h) {
      NewLayoutObj(parent, "Spacer", h);
    }
    private GameObject NewLayoutObj(GameObject parent, string name, float height) {
      var obj = new GameObject(name, typeof(RectTransform), typeof(LayoutElement));
      obj.transform.SetParent(parent.transform, false);
      obj.GetComponent<LayoutElement>().preferredHeight = height;
      return obj;
    }

    private void AddText(GameObject parent, Font font, string text, int size, Color color, TextAnchor align, FontStyle style) {
      var obj = new GameObject("Text", typeof(RectTransform), typeof(Text));
      obj.transform.SetParent(parent.transform, false);
      var rt = obj.GetComponent<RectTransform>();
      rt.anchorMin = Vector2.zero;
      rt.anchorMax = Vector2.one;
      rt.offsetMin = Vector2.zero;
      rt.offsetMax = Vector2.zero;
      var txt = obj.GetComponent<Text>();
      txt.text = text;
      txt.font = font;
      txt.fontSize = size;
      txt.color = color;
      txt.alignment = align;
      txt.fontStyle = style;
    }

    private GameObject MakeSlider(GameObject parent, float width) {
      var sliderGo = new GameObject("Slider", typeof(RectTransform), typeof(Slider), typeof(LayoutElement));
      sliderGo.transform.SetParent(parent.transform, false);
      sliderGo.GetComponent<LayoutElement>().preferredWidth = width;
      sliderGo.GetComponent<LayoutElement>().preferredHeight = 28;

      var bg = new GameObject("Bg", typeof(RectTransform), typeof(Image));
      bg.transform.SetParent(sliderGo.transform, false);
      var bgRT = bg.GetComponent<RectTransform>();
      bgRT.anchorMin = Vector2.zero; bgRT.anchorMax = Vector2.one;
      bgRT.offsetMin = Vector2.zero; bgRT.offsetMax = Vector2.zero;
      bg.GetComponent<Image>().color = new Color(0.35f, 0.35f, 0.38f, 1f);

      var fillArea = new GameObject("FillArea", typeof(RectTransform));
      fillArea.transform.SetParent(sliderGo.transform, false);
      var faRT = fillArea.GetComponent<RectTransform>();
      faRT.anchorMin = new Vector2(0, 0.3f); faRT.anchorMax = new Vector2(1, 0.7f);
      faRT.offsetMin = new Vector2(4, 0); faRT.offsetMax = new Vector2(-4, 0);

      var fill = new GameObject("Fill", typeof(RectTransform), typeof(Image));
      fill.transform.SetParent(fillArea.transform, false);
      var fRT = fill.GetComponent<RectTransform>();
      fRT.anchorMin = Vector2.zero; fRT.anchorMax = Vector2.one;
      fRT.offsetMin = Vector2.zero; fRT.offsetMax = Vector2.zero;
      fill.GetComponent<Image>().color = new Color(0.3f, 0.7f, 1f, 1f);

      var handleArea = new GameObject("HandleArea", typeof(RectTransform));
      handleArea.transform.SetParent(sliderGo.transform, false);
      var haRT = handleArea.GetComponent<RectTransform>();
      haRT.anchorMin = Vector2.zero; haRT.anchorMax = Vector2.one;
      haRT.offsetMin = new Vector2(8, 0); haRT.offsetMax = new Vector2(-8, 0);

      var handle = new GameObject("Handle", typeof(RectTransform), typeof(Image));
      handle.transform.SetParent(handleArea.transform, false);
      handle.GetComponent<RectTransform>().sizeDelta = new Vector2(20, 30);
      handle.GetComponent<Image>().color = Color.white;

      var slider = sliderGo.GetComponent<Slider>();
      slider.fillRect = fRT;
      slider.handleRect = handle.GetComponent<RectTransform>();
      slider.targetGraphic = handle.GetComponent<Image>();

      return sliderGo;
    }
  }
}
