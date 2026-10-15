using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using trtc;

namespace TRTCCUnityDemo {
  /// <summary>
  /// A standalone settings window for testing screen share Excluded/Included window APIs.
  /// Dynamically creates all UI elements via code — no prefab required.
  /// 
  /// Tested APIs:
  ///   - addExcludedShareWindow / removeExcludedShareWindow / removeAllExcludedShareWindows
  ///   - addIncludedShareWindow / removeIncludedShareWindow / removeAllIncludedShareWindows
  /// </summary>
  public class ScreenShareSettingScript : MonoBehaviour {
#if UNITY_STANDALONE_WIN || UNITY_STANDALONE_OSX
    private ITRTCCloud mTRTCCloud;
    private TRTCScreenCaptureSourceInfo[] mSources;
    private List<TRTCScreenCaptureSourceInfo> mWindowSources = new List<TRTCScreenCaptureSourceInfo>();

    // Compact UI scaling (to avoid the panel being too tall on small resolutions)
    private float mUIScale = 1.0f;

    // Track which windows are currently in excluded / included lists
    private HashSet<IntPtr> mExcludedWindows = new HashSet<IntPtr>();
    private HashSet<IntPtr> mIncludedWindows = new HashSet<IntPtr>();

    // UI references
    private Transform mContentParent;
    private Text mLogText;
    private ScrollRect mLogScrollRect;
    private Dropdown mWindowDropdown;
    private string mLogContent = "";

    // Selected window index in dropdown
    private int mSelectedWindowIndex = 0;

    void Start() {
      mTRTCCloud = ITRTCCloud.getTRTCShareInstance();
      RefreshWindowSources();
      BuildUI();
    }

    /// <summary>
    /// Refresh the list of available screen capture window sources.
    /// </summary>
    private void RefreshWindowSources() {
      SIZE thumbnail = new SIZE { width = 100, height = 60 };
      SIZE icon = new SIZE { width = 20, height = 20 };
      mSources = mTRTCCloud.getScreenCaptureSources(thumbnail, icon);

      mWindowSources.Clear();
      if (mSources != null) {
        foreach (var src in mSources) {
          if (src.type == TRTCScreenCaptureSourceType.TRTCScreenCaptureSourceTypeWindow) {
            mWindowSources.Add(src);
          }
        }
      }
      AppendLog($"Refreshed sources: {(mSources != null ? mSources.Length : 0)} total, {mWindowSources.Count} windows.");
    }

    /// <summary>
    /// Build the entire settings panel UI dynamically via code.
    /// </summary>
    private void BuildUI() {
      // --- Root Panel (semi-transparent dark background) ---
      RectTransform rootRect = gameObject.GetComponent<RectTransform>();
      if (rootRect == null) rootRect = gameObject.AddComponent<RectTransform>();
      rootRect.anchorMin = new Vector2(0.05f, 0.08f);
      rootRect.anchorMax = new Vector2(0.95f, 0.92f);
      rootRect.offsetMin = Vector2.zero;
      rootRect.offsetMax = Vector2.zero;

      // Make the whole panel slightly smaller on low resolutions so the bottom row is visible.
      // (Scaling the root is the safest way since everything here is created dynamically.)
      mUIScale = 1.0f;
      if (Screen.height < 700 || Screen.width < 1100) mUIScale = 0.88f;
      if (Screen.height < 600 || Screen.width < 900) mUIScale = 0.84f;
      if (Screen.height < 520 || Screen.width < 820) mUIScale = 0.80f;
      rootRect.pivot = new Vector2(0.5f, 0.5f);
      rootRect.localScale = new Vector3(mUIScale, mUIScale, 1f);

      Image bgImage = gameObject.AddComponent<Image>();
      bgImage.color = new Color(0.12f, 0.12f, 0.12f, 0.95f);

      // --- Vertical Layout for the whole panel ---
      VerticalLayoutGroup vlg = gameObject.AddComponent<VerticalLayoutGroup>();
      // Slightly more compact spacing to avoid overflowing the screen.
      vlg.padding = new RectOffset(10, 10, 10, 10);
      vlg.spacing = 1.0f;
      vlg.childAlignment = TextAnchor.UpperCenter;
      vlg.childControlWidth = true;
      vlg.childControlHeight = true;
      vlg.childForceExpandWidth = true;
      vlg.childForceExpandHeight = false;

      // ===== Window Selector Row =====
      CreateWindowSelector(transform);

      // ===== selectScreenCaptureTarget =====
      CreateSectionLabel(transform, "--- selectScreenCaptureTarget ---");
      CreateSelectTargetRow(transform);

      // ===== Excluded Window Buttons =====
      CreateSectionLabel(transform, "--- Excluded Share Window APIs ---");
      CreateButtonRow(transform, new string[] { "Add Excluded", "Remove Excluded", "Remove All Excluded" },
        new Action[] { OnAddExcluded, OnRemoveExcluded, OnRemoveAllExcluded });

      // ===== Included Window Buttons =====
      CreateSectionLabel(transform, "--- Included Share Window APIs ---");
      CreateButtonRow(transform, new string[] { "Add Included", "Remove Included", "Remove All Included" },
        new Action[] { OnAddIncluded, OnRemoveIncluded, OnRemoveAllIncluded });

      // ===== Log Area =====
      CreateLogArea(transform);
    }

    #region UI Construction Helpers

    // Action button sizing (compact mode)
    private const float kButtonWidthScale = 0.67f; // shrink by ~1/3
    // 4f is too small for 14pt text and makes buttons look like they disappeared.
    private const float kButtonRowHeight = 44f;     // compact but more comfortable
    private const float kButtonSpacing = 6f;        // spacing between buttons

    private void CreateWindowSelector(Transform parent) {
      const float rowHeight = 40f;
      GameObject row = CreateHorizontalRow(parent, rowHeight);

      // Allow children to use their own preferred sizes.
      // Important: disable forced width expansion so the label won't stretch and steal space from the dropdown.
      HorizontalLayoutGroup hlg = row.GetComponent<HorizontalLayoutGroup>();
      if (hlg != null) {
        hlg.childForceExpandHeight = false;
        hlg.childForceExpandWidth = false;
        hlg.childAlignment = TextAnchor.MiddleLeft;
      }

      float compactHeight = rowHeight;

      // Label
      GameObject labelObj = new GameObject("Label", typeof(RectTransform), typeof(Text));
      labelObj.transform.SetParent(row.transform, false);
      Text labelText = labelObj.GetComponent<Text>();
      labelText.text = "Window:";
      labelText.font = Resources.GetBuiltinResource<Font>("LegacyRuntime.ttf");
      labelText.fontSize = 14;
      labelText.color = Color.white;
      labelText.alignment = TextAnchor.MiddleLeft;
      LayoutElement labelLE = labelObj.AddComponent<LayoutElement>();
      labelLE.preferredWidth = 70;
      labelLE.preferredHeight = compactHeight;
      labelLE.flexibleWidth = 0;

      // Dropdown
      GameObject dropdownObj = CreateDropdown(row.transform, "WindowDropdown");
      LayoutElement ddLE = dropdownObj.GetComponent<LayoutElement>();
      if (ddLE != null) {
        ddLE.preferredHeight = compactHeight;
        ddLE.flexibleWidth = 1;
        ddLE.minWidth = 260f;
      }

      mWindowDropdown = dropdownObj.GetComponent<Dropdown>();
      PopulateWindowDropdown();
      mWindowDropdown.onValueChanged.AddListener((val) => { mSelectedWindowIndex = val; });

      // Refresh button
      CreateButton(row.transform, "Refresh", OnRefreshWindows, 120f, compactHeight);
    }

    private void CreateSelectTargetRow(Transform parent) {
      GameObject row = CreateHorizontalRow(parent, kButtonRowHeight);

      HorizontalLayoutGroup hlg = row.GetComponent<HorizontalLayoutGroup>();
      if (hlg != null) {
        hlg.childForceExpandWidth = false;
        hlg.childForceExpandHeight = false;
        hlg.childAlignment = TextAnchor.MiddleCenter;
        hlg.spacing = kButtonSpacing;
      }

      CreateButton(row.transform, "Select Target", OnSelectScreenCaptureTarget, 170f, kButtonRowHeight);
    }

    private void PopulateWindowDropdown() {
      if (mWindowDropdown == null) return;
      mWindowDropdown.ClearOptions();
      List<string> options = new List<string>();
      for (int i = 0; i < mWindowSources.Count; i++) {
        string name = mWindowSources[i].sourceName;
        if (string.IsNullOrEmpty(name)) name = "(unnamed)";
        if (name.Length > 40) name = name.Substring(0, 40) + "...";
        options.Add($"[{i}] {name}");
      }
      if (options.Count == 0) options.Add("(No windows found)");
      mWindowDropdown.AddOptions(options);
      mSelectedWindowIndex = 0;
    }

    private void CreateSectionLabel(Transform parent, string text) {
      GameObject labelObj = new GameObject("SectionLabel", typeof(RectTransform), typeof(Text));
      labelObj.transform.SetParent(parent, false);
      Text t = labelObj.GetComponent<Text>();
      t.text = text;
      t.font = Resources.GetBuiltinResource<Font>("LegacyRuntime.ttf");
      t.fontSize = 14;
      t.color = new Color(0.6f, 0.9f, 0.6f, 1f);
      t.alignment = TextAnchor.MiddleCenter;
      LayoutElement le = labelObj.AddComponent<LayoutElement>();
      le.preferredHeight = 16;
    }

    private void CreateButtonRow(Transform parent, string[] labels, Action[] actions) {
      GameObject row = CreateHorizontalRow(parent, kButtonRowHeight);

      // Do not force buttons to expand to fill the full row width/height; we want a more compact layout.
      HorizontalLayoutGroup hlg = row.GetComponent<HorizontalLayoutGroup>();
      if (hlg != null) {
        hlg.childForceExpandWidth = false;
        hlg.childForceExpandHeight = false;
        hlg.childAlignment = TextAnchor.MiddleCenter;
        hlg.spacing = kButtonSpacing;
      }

      // Compute a preferred width based on the current panel width.
      // Panel anchors: 0.05 ~ 0.95 => about 90% of screen width, minus vlg paddings (10 + 10).
      float panelWidth = Screen.width * 0.9f - 20f;
      float spacing = (hlg != null) ? hlg.spacing : 0f;
      int count = (labels != null) ? labels.Length : 0;
      float available = Mathf.Max(0f, panelWidth - spacing * Mathf.Max(0, count - 1));
      float baseWidth = (count > 0) ? (available / count) : 0f;
      float preferredButtonWidth = baseWidth * kButtonWidthScale;

      for (int i = 0; i < labels.Length; i++) {
        CreateButton(row.transform, labels[i], actions[i], preferredButtonWidth, kButtonRowHeight);
      }
    }

    private GameObject CreateHorizontalRow(Transform parent, float height) {
      GameObject row = new GameObject("Row", typeof(RectTransform));
      row.transform.SetParent(parent, false);
      HorizontalLayoutGroup hlg = row.AddComponent<HorizontalLayoutGroup>();
      hlg.spacing = 1.0f;
      hlg.childAlignment = TextAnchor.MiddleCenter;
      hlg.childControlWidth = true;
      hlg.childControlHeight = true;
      hlg.childForceExpandWidth = true;
      hlg.childForceExpandHeight = false;
      LayoutElement le = row.AddComponent<LayoutElement>();
      le.minHeight = height;
      le.preferredHeight = height;
      le.flexibleHeight = 0;
      return row;
    }

    private void CreateButton(Transform parent, string label, Action onClick, float preferredWidth, float preferredHeight) {
      GameObject btnObj = new GameObject(label, typeof(RectTransform), typeof(Image), typeof(Button));
      btnObj.transform.SetParent(parent, false);
      btnObj.GetComponent<Image>().color = new Color(0.25f, 0.45f, 0.7f, 1f);

      LayoutElement btnLE = btnObj.AddComponent<LayoutElement>();
      btnLE.preferredWidth = preferredWidth;
      btnLE.preferredHeight = preferredHeight;
      btnLE.minHeight = preferredHeight;
      btnLE.flexibleHeight = 0;

      GameObject textObj = new GameObject("Text", typeof(RectTransform), typeof(Text));
      textObj.transform.SetParent(btnObj.transform, false);
      RectTransform textRect = textObj.GetComponent<RectTransform>();
      textRect.anchorMin = Vector2.zero;
      textRect.anchorMax = Vector2.one;
      // Keep padding compact so the label fits in a shorter button.
      textRect.offsetMin = new Vector2(4, 0);
      textRect.offsetMax = new Vector2(-4, 0);
      Text t = textObj.GetComponent<Text>();
      t.text = label;
      t.font = Resources.GetBuiltinResource<Font>("LegacyRuntime.ttf");
      t.fontSize = 14;
      t.color = Color.white;
      t.alignment = TextAnchor.MiddleCenter;

      btnObj.GetComponent<Button>().onClick.AddListener(() => onClick());
    }

    private GameObject CreateDropdown(Transform parent, string name) {
      // Create a simple dropdown using Unity's built-in Dropdown component
      GameObject ddObj = new GameObject(name, typeof(RectTransform), typeof(Image), typeof(Dropdown));
      ddObj.transform.SetParent(parent, false);
      ddObj.GetComponent<Image>().color = new Color(0.2f, 0.2f, 0.2f, 1f);
      LayoutElement le = ddObj.AddComponent<LayoutElement>();
      le.flexibleWidth = 1;

      // Caption text
      GameObject captionObj = new GameObject("Label", typeof(RectTransform), typeof(Text));
      captionObj.transform.SetParent(ddObj.transform, false);
      RectTransform captionRect = captionObj.GetComponent<RectTransform>();
      captionRect.anchorMin = new Vector2(0.1f, 0f);
      captionRect.anchorMax = new Vector2(0.9f, 1f);
      captionRect.offsetMin = Vector2.zero;
      captionRect.offsetMax = Vector2.zero;
      Text captionText = captionObj.GetComponent<Text>();
      captionText.font = Resources.GetBuiltinResource<Font>("LegacyRuntime.ttf");
      captionText.fontSize = 14;
      captionText.color = Color.white;
      captionText.alignment = TextAnchor.MiddleLeft;

      // Template (required by Dropdown)
      GameObject templateObj = new GameObject("Template", typeof(RectTransform), typeof(Image), typeof(ScrollRect));
      templateObj.transform.SetParent(ddObj.transform, false);
      RectTransform templateRect = templateObj.GetComponent<RectTransform>();
      templateRect.anchorMin = new Vector2(0, 0);
      templateRect.anchorMax = new Vector2(1, 0);
      templateRect.pivot = new Vector2(0.5f, 1f);
      templateRect.sizeDelta = new Vector2(0, 320);
      templateObj.GetComponent<Image>().color = new Color(0.15f, 0.15f, 0.15f, 1f);

      // Viewport
      GameObject viewportObj = new GameObject("Viewport", typeof(RectTransform), typeof(Image), typeof(Mask));
      viewportObj.transform.SetParent(templateObj.transform, false);
      RectTransform viewportRect = viewportObj.GetComponent<RectTransform>();
      viewportRect.anchorMin = Vector2.zero;
      viewportRect.anchorMax = Vector2.one;
      viewportRect.offsetMin = Vector2.zero;
      viewportRect.offsetMax = Vector2.zero;
      viewportObj.GetComponent<Image>().color = new Color(0.15f, 0.15f, 0.15f, 1f);

      // Content
      GameObject contentObj = new GameObject("Content", typeof(RectTransform));
      contentObj.transform.SetParent(viewportObj.transform, false);
      RectTransform contentRect = contentObj.GetComponent<RectTransform>();
      contentRect.anchorMin = new Vector2(0, 1);
      contentRect.anchorMax = new Vector2(1, 1);
      contentRect.pivot = new Vector2(0.5f, 1f);
      contentRect.sizeDelta = new Vector2(0, 28);

      // Item
      GameObject itemObj = new GameObject("Item", typeof(RectTransform), typeof(Image), typeof(Toggle));
      itemObj.transform.SetParent(contentObj.transform, false);
      RectTransform itemRect = itemObj.GetComponent<RectTransform>();
      itemRect.anchorMin = new Vector2(0, 0.5f);
      itemRect.anchorMax = new Vector2(1, 0.5f);
      itemRect.sizeDelta = new Vector2(0, 28);
      itemObj.GetComponent<Image>().color = new Color(0.25f, 0.25f, 0.25f, 1f);

      // Item label
      GameObject itemLabelObj = new GameObject("Item Label", typeof(RectTransform), typeof(Text));
      itemLabelObj.transform.SetParent(itemObj.transform, false);
      RectTransform itemLabelRect = itemLabelObj.GetComponent<RectTransform>();
      itemLabelRect.anchorMin = Vector2.zero;
      itemLabelRect.anchorMax = Vector2.one;
      itemLabelRect.offsetMin = new Vector2(8, 0);
      itemLabelRect.offsetMax = new Vector2(-8, 0);
      Text itemLabelText = itemLabelObj.GetComponent<Text>();
      itemLabelText.font = Resources.GetBuiltinResource<Font>("LegacyRuntime.ttf");
      itemLabelText.fontSize = 14;
      itemLabelText.color = Color.white;

      // Wire up the Dropdown
      Dropdown dd = ddObj.GetComponent<Dropdown>();
      dd.captionText = captionText;
      dd.itemText = itemLabelText;
      dd.template = templateRect;

      // ScrollRect setup
      ScrollRect sr = templateObj.GetComponent<ScrollRect>();
      sr.content = contentRect;
      sr.viewport = viewportRect;

      // Toggle setup
      Toggle toggle = itemObj.GetComponent<Toggle>();
      toggle.targetGraphic = itemObj.GetComponent<Image>();

      templateObj.SetActive(false);

      return ddObj;
    }

    private void CreateLogArea(Transform parent) {
      // Log area with scroll
      GameObject scrollObj = new GameObject("LogScroll", typeof(RectTransform), typeof(Image), typeof(ScrollRect));
      scrollObj.transform.SetParent(parent, false);
      scrollObj.GetComponent<Image>().color = new Color(0.08f, 0.08f, 0.08f, 1f);
      LayoutElement scrollLE = scrollObj.AddComponent<LayoutElement>();
      scrollLE.flexibleHeight = 1;
      scrollLE.preferredHeight = 110;

      // Viewport
      GameObject viewportObj = new GameObject("Viewport", typeof(RectTransform), typeof(Image), typeof(Mask));
      viewportObj.transform.SetParent(scrollObj.transform, false);
      RectTransform vpRect = viewportObj.GetComponent<RectTransform>();
      vpRect.anchorMin = Vector2.zero;
      vpRect.anchorMax = Vector2.one;
      vpRect.offsetMin = new Vector2(4, 4);
      vpRect.offsetMax = new Vector2(-4, -4);
      viewportObj.GetComponent<Image>().color = new Color(0.08f, 0.08f, 0.08f, 1f);

      // Content
      GameObject contentObj = new GameObject("Content", typeof(RectTransform), typeof(ContentSizeFitter), typeof(VerticalLayoutGroup));
      contentObj.transform.SetParent(viewportObj.transform, false);
      RectTransform contentRect = contentObj.GetComponent<RectTransform>();
      contentRect.anchorMin = new Vector2(0, 1);
      contentRect.anchorMax = new Vector2(1, 1);
      contentRect.pivot = new Vector2(0, 1);
      contentRect.sizeDelta = new Vector2(0, 0);
      ContentSizeFitter csf = contentObj.GetComponent<ContentSizeFitter>();
      csf.verticalFit = ContentSizeFitter.FitMode.PreferredSize;

      // Log text
      GameObject textObj = new GameObject("LogText", typeof(RectTransform), typeof(Text));
      textObj.transform.SetParent(contentObj.transform, false);
      mLogText = textObj.GetComponent<Text>();
      mLogText.text = "";
      mLogText.font = Resources.GetBuiltinResource<Font>("LegacyRuntime.ttf");
      mLogText.fontSize = 11;
      mLogText.color = new Color(0.8f, 0.8f, 0.8f, 1f);
      mLogText.alignment = TextAnchor.UpperLeft;
      mLogText.horizontalOverflow = HorizontalWrapMode.Wrap;
      mLogText.verticalOverflow = VerticalWrapMode.Overflow;

      LayoutElement textLE = textObj.AddComponent<LayoutElement>();
      textLE.flexibleWidth = 1;

      // Wire ScrollRect
      mLogScrollRect = scrollObj.GetComponent<ScrollRect>();
      mLogScrollRect.content = contentRect;
      mLogScrollRect.viewport = vpRect;
      mLogScrollRect.horizontal = false;
      mLogScrollRect.vertical = true;
    }

    #endregion

    #region Button Handlers

    private void OnRefreshWindows() {
      RefreshWindowSources();
      PopulateWindowDropdown();
      AppendLog("[RefreshWindows] Window sources refreshed.");
    }

    private void OnSelectScreenCaptureTarget() {
      if (!ValidateSelection()) return;

      var src = mWindowSources[mSelectedWindowIndex];
      Rect captureRect = new Rect(0, 0, 0, 0);

      TRTCScreenCaptureProperty prop = new TRTCScreenCaptureProperty();
      mTRTCCloud.selectScreenCaptureTarget(src, captureRect, prop);
      AppendLog($"[selectScreenCaptureTarget] sourceId={src.sourceId}, name=\"{src.sourceName}\" (default property)");
    }

    private void OnAddExcluded() {
      if (!ValidateSelection()) return;
      var src = mWindowSources[mSelectedWindowIndex];
      IntPtr wid = src.sourceId;

      mTRTCCloud.addExcludedShareWindow(wid);
      mExcludedWindows.Add(wid);
      AppendLog($"[addExcludedShareWindow] sourceId={wid}, name=\"{src.sourceName}\"");
    }

    private void OnRemoveExcluded() {
      if (!ValidateSelection()) return;
      var src = mWindowSources[mSelectedWindowIndex];
      IntPtr wid = src.sourceId;

      mTRTCCloud.removeExcludedShareWindow(wid);
      mExcludedWindows.Remove(wid);
      AppendLog($"[removeExcludedShareWindow] sourceId={wid}, name=\"{src.sourceName}\"");
    }

    private void OnRemoveAllExcluded() {
      mTRTCCloud.removeAllExcludedShareWindows();
      mExcludedWindows.Clear();
      AppendLog("[removeAllExcludedShareWindows] All excluded windows cleared.");
    }

    private void OnAddIncluded() {
      if (!ValidateSelection()) return;
      var src = mWindowSources[mSelectedWindowIndex];
      IntPtr wid = src.sourceId;

      mTRTCCloud.addIncludedShareWindow(wid);
      mIncludedWindows.Add(wid);
      AppendLog($"[addIncludedShareWindow] sourceId={wid}, name=\"{src.sourceName}\"");
    }

    private void OnRemoveIncluded() {
      if (!ValidateSelection()) return;
      var src = mWindowSources[mSelectedWindowIndex];
      IntPtr wid = src.sourceId;

      mTRTCCloud.removeIncludedShareWindow(wid);
      mIncludedWindows.Remove(wid);
      AppendLog($"[removeIncludedShareWindow] sourceId={wid}, name=\"{src.sourceName}\"");
    }

    private void OnRemoveAllIncluded() {
      mTRTCCloud.removeAllIncludedShareWindows();
      mIncludedWindows.Clear();
      AppendLog("[removeAllIncludedShareWindows] All included windows cleared.");
    }

    #endregion

    #region Utility

    private bool ValidateSelection() {
      if (mWindowSources.Count == 0) {
        AppendLog("[Warning] No window sources available. Please click 'Refresh Windows'.");
        return false;
      }
      if (mSelectedWindowIndex < 0 || mSelectedWindowIndex >= mWindowSources.Count) {
        AppendLog("[Warning] Invalid window selection.");
        return false;
      }
      return true;
    }

    private string FindWindowName(IntPtr windowId) {
      foreach (var src in mWindowSources) {
        if (src.sourceId == windowId)
          return src.sourceName;
      }
      return "unknown";
    }

    private void AppendLog(string msg) {
      string timestamp = DateTime.Now.ToString("HH:mm:ss.fff");
      mLogContent += $"[{timestamp}] {msg}\n";
      // Limit log length
      if (mLogContent.Length > 5000) {
        mLogContent = mLogContent.Substring(mLogContent.Length - 4000);
      }
      if (mLogText != null) mLogText.text = mLogContent;

      // Also output to LogManager and Debug
      LogManager.Log($"[ScreenShareSetting] {msg}");

      // Auto scroll to bottom
      if (mLogScrollRect != null) {
        Canvas.ForceUpdateCanvases();
        mLogScrollRect.verticalNormalizedPosition = 0f;
      }
    }

    /// <summary>
    /// Static helper to create and show the settings window on a given canvas.
    /// Usage: ScreenShareSettingScript.Show(parentCanvas);
    /// </summary>
    public static ScreenShareSettingScript Show(Transform parentCanvas) {
      GameObject panelObj = new GameObject("ScreenShareSettingPanel", typeof(RectTransform));
      panelObj.transform.SetParent(parentCanvas, false);
      ScreenShareSettingScript script = panelObj.AddComponent<ScreenShareSettingScript>();
      return script;
    }

    #endregion

#else
    // Non-desktop platforms: provide a stub so the script can compile everywhere.
    void Start()
    {
      LogManager.Log("[ScreenShareSettingScript] This feature is only available on Windows/macOS desktop platforms.");
    }

    public static ScreenShareSettingScript Show(Transform parentCanvas)
    {
      LogManager.Log("[ScreenShareSettingScript] This feature is only available on Windows/macOS desktop platforms.");
      return null;
    }
#endif
  }
}
