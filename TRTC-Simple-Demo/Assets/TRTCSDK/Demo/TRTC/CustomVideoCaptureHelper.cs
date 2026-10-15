using System;
using System.Collections;
using System.Runtime.InteropServices;
using UnityEngine;
using trtc;

namespace TRTCCUnityDemo {
  /// <summary>
  /// Helper class that encapsulates all custom video capture logic
  /// (sendCustomVideoData with texture / buffer mode).
  /// Extracted from SettingScript for separation of concerns.
  /// </summary>
  public class CustomVideoCaptureHelper {
    #region Singleton

    private static CustomVideoCaptureHelper s_instance;

    public static CustomVideoCaptureHelper Instance {
      get {
        if (s_instance == null)
          s_instance = new CustomVideoCaptureHelper();
        return s_instance;
      }
    }

    #endregion

    #region Fields

    private ITRTCCloud mTRTCCloud;
    private byte[] mCustomYuvData = null;
    private int mCustomFrameOffset = 0;
    private int mCustomFrameSize = 0;
    private bool mIsCustomVideoCapturing = false;
    private TRTCVideoEncParam mSavedVideoEncParam;
    private Texture2D mCustomCaptureTexture = null;
    private IntPtr mUnityEglContext = IntPtr.Zero;
    private bool mLoggedSamplePixel = false;
    private IntPtr mPersistentBuffer = IntPtr.Zero;
    // Windows D3D11 custom capture fields
    private int _yuvFrameCount = 0;
    private int _yuvCurrentFrameIdx = 0;

    public bool IsCapturing => mIsCustomVideoCapturing;

    #endregion

    #region CoroutineHost

    // Because gameObject.SetActive(false) stops all coroutines, we run
    // long-lived coroutines (custom video capture) on a DontDestroyOnLoad
    // helper so they keep running even when the settings panel is closed.
    private static CoroutineHost s_coroutineHost;

    private class CoroutineHost : MonoBehaviour { }

    private static CoroutineHost GetCoroutineHost() {
      if (s_coroutineHost == null) {
        var go = new GameObject("CustomCaptureCoroutineHost");
        go.hideFlags = HideFlags.HideAndDontSave;
        UnityEngine.Object.DontDestroyOnLoad(go);
        s_coroutineHost = go.AddComponent<CoroutineHost>();
      }
      return s_coroutineHost;
    }

    #endregion

    #region Android EGL / GL Native

#if UNITY_ANDROID && !UNITY_EDITOR
        // EGL: fetch the current EGLContext. MUST be called on the Unity render thread,
        // because with Multithreaded Rendering ON the GL/EGL context lives there, not on
        // the main/script thread (where it returns 0x0).
        [DllImport("libEGL.so")]
        private static extern IntPtr eglGetCurrentContext();
        // GL: force GPU to finish all commands so the shared texture is fully uploaded
        // before the SDK's context samples it. Also must run on the render thread.
        [DllImport("libGLESv2.so")]
        private static extern void glFinish();

        // ---- Render-thread dispatch (the key to working with Multithreaded Rendering ON) ----
        private delegate void RenderEventDelegate(int eventId);
        private static RenderEventDelegate s_renderEventDelegate;     // kept alive to avoid GC
        private static IntPtr s_renderEventFuncPtr = IntPtr.Zero;
        private static IntPtr s_capturedEglContext = IntPtr.Zero;     // filled on render thread
        private const int kEventCaptureContext = 1;                   // capture EGL ctx + glFinish
        private const int kEventGlFinish = 2;                         // glFinish only

        [AOT.MonoPInvokeCallback(typeof(RenderEventDelegate))]
        private static void OnRenderThreadEvent(int eventId)
        {
            // Executed on Unity's render thread — the GL/EGL context is current here.
            if (eventId == kEventCaptureContext)
            {
                s_capturedEglContext = eglGetCurrentContext();
            }
            // Block until the GPU finishes pending uploads so the SDK's context sees a
            // fully written texture (cross-context sharing requires this).
            glFinish();
        }

        private void EnsureRenderEventFuncPtr()
        {
            if (s_renderEventFuncPtr == IntPtr.Zero)
            {
                s_renderEventDelegate = OnRenderThreadEvent;
                s_renderEventFuncPtr = Marshal.GetFunctionPointerForDelegate(s_renderEventDelegate);
            }
        }
#endif

    #endregion

    #region Public API

    /// <summary>
    /// Start custom video capture with the given cloud instance.
    /// </summary>
    /// <param name="cloud">TRTC cloud instance.</param>
    /// <param name="useTexture">true for texture mode, false for buffer (I420) mode.</param>
    public void StartCapture(ITRTCCloud cloud, bool useTexture) {
      if (mIsCustomVideoCapturing) {
        Debug.Log("[CustomCapture] Custom capture already active, ignoring start request");
        return;
      }

      mTRTCCloud = cloud;
      Debug.Log($"[CustomCapture] StartCapture useTexture={useTexture}");

      // Stop TRTC built-in preview before switching to custom capture
      mTRTCCloud.stopLocalPreview();
      // Re-enable video publishing in case it was muted by camera toggle
      mTRTCCloud.muteLocalVideo(false);
      DataManager.GetInstance().captureVideo = true;
      Debug.Log("[CustomCapture] Local preview stopped, video publishing re-enabled for custom capture");

      // Set flag EARLY — before the async YUV load on Android.
      // This allows StopCapture (or OnToggleCamera) to properly
      // stop the capture even while YUV is still loading asynchronously.
      mIsCustomVideoCapturing = true;

      // Load YUV file from StreamingAssets
      string yuvPath = System.IO.Path.Combine(Application.streamingAssetsPath, "320x240_video.yuv");
      const int yuvWidth = 320;
      const int yuvHeight = 240;
      mCustomFrameSize = yuvWidth * yuvHeight * 3 / 2;  // I420 frame size

      try {
#if UNITY_ANDROID && !UNITY_EDITOR
                // Android: StreamingAssets is inside APK, need WWW/UnityWebRequest
                GetCoroutineHost().StartCoroutine(LoadYuvFromAndroid(yuvPath, yuvWidth, yuvHeight, useTexture));
                return;
#else
        mCustomYuvData = System.IO.File.ReadAllBytes(yuvPath);
#endif
      }
      catch (System.Exception e) {
        Debug.Log($"[CustomCapture] Failed to load YUV file: {e.Message}");
        mIsCustomVideoCapturing = false;
        return;
      }

      int frameCount = mCustomYuvData.Length / mCustomFrameSize;
      Debug.Log($"[CustomCapture] YUV loaded: {mCustomYuvData.Length} bytes, {frameCount} frames ({yuvWidth}x{yuvHeight})");

      BeginCustomCapture(yuvWidth, yuvHeight, useTexture);
    }

    /// <summary>
    /// Stop custom video capture without resetting any UI dropdown.
    /// The caller (SettingScript) is responsible for resetting the dropdown.
    /// </summary>
    public void StopCapture() {
      if (!mIsCustomVideoCapturing) return;
      StopCaptureInternal();
    }

    /// <summary>
    /// Full cleanup: stop capture, destroy CoroutineHost, clear references.
    /// Should be called from SettingScript.OnDestroy().
    /// </summary>
    public void Cleanup() {
      if (mIsCustomVideoCapturing) {
        StopCaptureInternal();
      }

      // Always clean up CoroutineHost
      if (s_coroutineHost != null) {
        s_coroutineHost.StopAllCoroutines();
        UnityEngine.Object.Destroy(s_coroutineHost.gameObject);
        s_coroutineHost = null;
      }

      mTRTCCloud = null;
      Debug.Log("[CustomCapture] Helper cleaned up");
    }

    #endregion

    #region Implementation

    private void BeginCustomCapture(int yuvWidth, int yuvHeight, bool useTexture) {
      mSavedVideoEncParam = DataManager.GetInstance().videoEncParam;
      var videoEncParams = new TRTCVideoEncParam {
        videoResolution = TRTCVideoResolution.TRTCVideoResolution_320_240,
        resMode = TRTCVideoResolutionMode.TRTCVideoResolutionModeLandscape,
        videoFps = 15,
        videoBitrate = 400,
        minVideoBitrate = 200
      };
      mTRTCCloud.setVideoEncoderParam(ref videoEncParams);
      Debug.Log($"[CustomCapture] Custom capture encoder set: {yuvWidth}x{yuvHeight} @15fps");

      // mIsCustomVideoCapturing was already set to true in StartCapture
      // (before the async YUV load), so StopCapture can intercept early.
      mCustomFrameOffset = 0;

      var gfxType = SystemInfo.graphicsDeviceType;
      Debug.Log($"[CustomCapture] GraphicsDeviceType = {gfxType}, useTexture = {useTexture}");

      if (useTexture) {
        // ---- Texture mode ----
        mTRTCCloud.enableCustomVideoCapture(TRTCVideoStreamType.TRTCVideoStreamTypeBig, true);

#if UNITY_STANDALONE_WIN
          // Windows D3D11 texture path
          _yuvFrameCount = mCustomYuvData.Length / mCustomFrameSize;
          _yuvCurrentFrameIdx = 0;
          mCustomCaptureTexture = new Texture2D(yuvWidth, yuvHeight, TextureFormat.BGRA32, false, true);
          GetCoroutineHost().StartCoroutine(SendD3DCaptureFramesCoroutine(yuvWidth, yuvHeight));
#elif UNITY_ANDROID
        // Android OpenGL ES texture path
        mCustomCaptureTexture = new Texture2D(yuvWidth, yuvHeight, TextureFormat.RGBA32, false);
        GetCoroutineHost().StartCoroutine(SendTextureFramesCoroutine(yuvWidth, yuvHeight));
#else
        // Texture mode not available on this platform — fall back to buffer
        if (mPersistentBuffer == IntPtr.Zero) {
          mPersistentBuffer = Marshal.AllocHGlobal(mCustomFrameSize);
        }
        string platformName = Application.platform.ToString();
        GetCoroutineHost().StartCoroutine(SendBufferCaptureFramesCoroutine(yuvWidth, yuvHeight, platformName));
#endif
      }
      else {
        // ---- Buffer mode (I420) ----
        mTRTCCloud.enableCustomVideoCapture(TRTCVideoStreamType.TRTCVideoStreamTypeBig, true);

#if UNITY_IOS
                if (mPersistentBuffer == IntPtr.Zero)
                {
                    mPersistentBuffer = Marshal.AllocHGlobal(mCustomFrameSize);
                }
                Debug.Log($"[CustomCapture] Custom capture started (iOS I420 buffer mode, {gfxType})");
                GetCoroutineHost().StartCoroutine(SendBufferCaptureFramesCoroutine(yuvWidth, yuvHeight, "iOS"));
#elif UNITY_STANDALONE_OSX || UNITY_EDITOR_OSX
        if (mPersistentBuffer == IntPtr.Zero) {
          mPersistentBuffer = Marshal.AllocHGlobal(mCustomFrameSize);
        }
        GetCoroutineHost().StartCoroutine(SendBufferCaptureFramesCoroutine(yuvWidth, yuvHeight, "macOS"));
#else
                // Other platforms (e.g. Android buffer fallback, Windows buffer)
                GetCoroutineHost().StartCoroutine(SendBufferCaptureFramesCoroutine(yuvWidth, yuvHeight, Application.platform.ToString()));
#endif
      }
    }

#if UNITY_ANDROID && !UNITY_EDITOR
        private IEnumerator LoadYuvFromAndroid(string path, int width, int height, bool useTexture)
        {
            using (var request = UnityEngine.Networking.UnityWebRequest.Get(path))
            {
                yield return request.SendWebRequest();
                if (request.result == UnityEngine.Networking.UnityWebRequest.Result.Success)
                {
                    mCustomYuvData = request.downloadHandler.data;
                    int frameCount = mCustomYuvData.Length / mCustomFrameSize;
                    BeginCustomCapture(width, height, useTexture);
                }
                else
                {
                    Debug.Log($"[CustomCapture] Failed to load YUV from Android: {request.error}");
                    mIsCustomVideoCapturing = false;
                }
            }
        }
#endif

    private void SendCustomVideoFrame() {
      if (mCustomYuvData == null || mCustomFrameSize == 0) return;
      if (mCustomFrameOffset + mCustomFrameSize > mCustomYuvData.Length) mCustomFrameOffset = 0;

      // Use persistent buffer if available (iOS/macOS), otherwise alloc/free per frame
      IntPtr dataPtr;
      bool freeAfterSend;
      if (mPersistentBuffer != IntPtr.Zero) {
        dataPtr = mPersistentBuffer;
        freeAfterSend = false;
      }
      else {
        dataPtr = Marshal.AllocHGlobal(mCustomFrameSize);
        freeAfterSend = true;
      }
      Marshal.Copy(mCustomYuvData, mCustomFrameOffset, dataPtr, mCustomFrameSize);

      TRTCVideoFrame frame = new TRTCVideoFrame();
      frame.videoFormat = TRTCVideoPixelFormat.TRTCVideoPixelFormat_I420;
      frame.bufferType = TRTCVideoBufferType.TRTCVideoBufferType_Buffer;
      frame.data = dataPtr;
      frame.length = (uint)mCustomFrameSize;
      frame.width = 320;
      frame.height = 240;
      frame.timestamp = mTRTCCloud.generateCustomPTS();
      frame.rotation = TRTCVideoRotation.TRTCVideoRotation0;

      mTRTCCloud.sendCustomVideoData(TRTCVideoStreamType.TRTCVideoStreamTypeBig, frame);
      if (freeAfterSend) Marshal.FreeHGlobal(dataPtr);
      mCustomFrameOffset += mCustomFrameSize;
    }

    private IEnumerator SendTextureFramesCoroutine(int frameWidth, int frameHeight) {
      // Wait one frame for texture to settle, then start sending
      yield return null;

#if UNITY_ANDROID && !UNITY_EDITOR
            // Prepare the render-thread callable pointer once.
            EnsureRenderEventFuncPtr();

            // Capture Unity's EGL context ON THE RENDER THREAD.
            s_capturedEglContext = IntPtr.Zero;
            GL.IssuePluginEvent(s_renderEventFuncPtr, kEventCaptureContext);
            // Wait until the render thread has actually executed the event and filled the value.
            yield return new WaitForEndOfFrame();
            int ctxWaitGuard = 0;
            while (s_capturedEglContext == IntPtr.Zero && ctxWaitGuard < 30)
            {
                GL.IssuePluginEvent(s_renderEventFuncPtr, kEventCaptureContext);
                yield return new WaitForEndOfFrame();
                ctxWaitGuard++;
            }
            mUnityEglContext = s_capturedEglContext;
#else
      yield return new WaitForEndOfFrame();
#endif

      var wait = new WaitForSeconds(1.0f / 15.0f);

      while (mIsCustomVideoCapturing && mCustomYuvData != null && mCustomCaptureTexture != null) {
        // Upload current YUV frame into the texture (SetPixels32 + Apply)
        UpdateCaptureTexture(frameWidth, frameHeight);

        // Ensure GPU upload is FULLY finished before the SDK's GL context samples it.
#if UNITY_ANDROID && !UNITY_EDITOR
                GL.IssuePluginEvent(s_renderEventFuncPtr, kEventGlFinish);
                yield return new WaitForEndOfFrame();
#else
        GL.Flush();
#endif

        IntPtr texPtr = mCustomCaptureTexture.GetNativeTexturePtr();
        if (texPtr == IntPtr.Zero) {
          Debug.Log("[CustomCapture] Texture ptr is null, skipping frame");
          mCustomFrameOffset += mCustomFrameSize;
          yield return wait;
          continue;
        }

        TRTCTexture tex = new TRTCTexture();
        // On Android the native texture ptr is the GL texture name (id)
        tex.glTextureId = texPtr.ToInt32();
        // Pass Unity's EGL context so the SDK can share the texture across its own thread
        tex.glContext = mUnityEglContext;

        TRTCVideoFrame frame = new TRTCVideoFrame();
        frame.videoFormat = TRTCVideoPixelFormat.TRTCVideoPixelFormat_Texture_2D;
        frame.bufferType = TRTCVideoBufferType.TRTCVideoBufferType_Texture;
        frame.texture = tex;
        frame.width = (uint)frameWidth;
        frame.height = (uint)frameHeight;
        frame.timestamp = mTRTCCloud.generateCustomPTS();
        frame.rotation = TRTCVideoRotation.TRTCVideoRotation0;

        mTRTCCloud.sendCustomVideoData(TRTCVideoStreamType.TRTCVideoStreamTypeBig, frame);

        mCustomFrameOffset += mCustomFrameSize;
        yield return wait;
      }
    }

    /// <summary>
    /// macOS/iOS/fallback custom capture — I420 Buffer mode.
    /// </summary>
    private IEnumerator SendBufferCaptureFramesCoroutine(int frameWidth, int frameHeight, string platform) {
      var wait = new WaitForSeconds(1.0f / 15.0f);
      Debug.Log($"[CustomCapture] [{platform}] Buffer coroutine starting, dataSize={mCustomYuvData?.Length ?? 0}, frameSize={mCustomFrameSize}");

      while (mIsCustomVideoCapturing && mCustomYuvData != null) {
        SendCustomVideoFrame();
        yield return wait;
      }
    }

#if UNITY_STANDALONE_WIN
        private IEnumerator SendD3DCaptureFramesCoroutine(int frameWidth, int frameHeight)
        {
            yield return new WaitForEndOfFrame();

            var wait = new WaitForSeconds(1.0f / 15.0f);

            while (mIsCustomVideoCapturing && mCustomYuvData != null && mCustomCaptureTexture != null)
            {
                // 1. Convert I420 → BGRA32 and upload to D3D texture
                ConvertI420ToBGRA(frameWidth, frameHeight);

                // 2. Get D3D11 texture pointer (ID3D11Texture2D*) on Windows
                IntPtr d3d11TexPtr = mCustomCaptureTexture.GetNativeTexturePtr();
                if (d3d11TexPtr == IntPtr.Zero)
                {
                    Debug.Log("[CustomCapture] D3D texture ptr is null, skipping frame");
                    yield return wait;
                    continue;
                }

                // 3. Build TRTCTexture with D3D11 texture
                TRTCTexture tex = new TRTCTexture();
                tex.d3d11TextureId = d3d11TexPtr;

                // 4. Build video frame
                TRTCVideoFrame frame = new TRTCVideoFrame();
                frame.videoFormat = TRTCVideoPixelFormat.TRTCVideoPixelFormat_BGRA32;
                frame.bufferType = TRTCVideoBufferType.TRTCVideoBufferType_TextureD3D11;
                frame.texture = tex;
                frame.width = (uint)frameWidth;
                frame.height = (uint)frameHeight;
                frame.length = (uint)(frameWidth * frameHeight * 4);  // BGRA32
                frame.timestamp = mTRTCCloud.generateCustomPTS();
                frame.rotation = TRTCVideoRotation.TRTCVideoRotation0;

                // 5. Send
                mTRTCCloud.sendCustomVideoData(TRTCVideoStreamType.TRTCVideoStreamTypeBig, frame);

                yield return wait;
            }
        }

        /// <summary>
        /// I420 → BGRA32 conversion directly into mCustomCaptureTexture (Windows D3D11).
        /// Uses ITU-R BT.601 integer approximation.
        /// </summary>
        private void ConvertI420ToBGRA(int width, int height)
        {
            if (mCustomYuvData == null || mCustomCaptureTexture == null) return;

            int ySize = width * height;
            int uvSize = ySize / 4;
            int pixelCount = ySize;

            int srcOffset = _yuvCurrentFrameIdx * mCustomFrameSize;
            if (srcOffset + mCustomFrameSize > mCustomYuvData.Length)
            {
                srcOffset = 0;
                _yuvCurrentFrameIdx = 0;
            }
            _yuvCurrentFrameIdx = (_yuvCurrentFrameIdx + 1) % _yuvFrameCount;

            byte[] bgra = new byte[pixelCount * 4];

            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    int yIndex = y * width + x;
                    int uvIndex = (y / 2) * (width / 2) + (x / 2);

                    int Y = mCustomYuvData[srcOffset + yIndex];
                    int U = mCustomYuvData[srcOffset + ySize + uvIndex] - 128;
                    int V = mCustomYuvData[srcOffset + ySize + uvSize + uvIndex] - 128;

                    // ITU-R BT.601 integer approx
                    int R = ClampByte(Y + ((359 * V) >> 8));
                    int G = ClampByte(Y - ((88 * U + 183 * V) >> 8));
                    int B = ClampByte(Y + ((454 * U) >> 8));

                    int pixelIdx = yIndex * 4;
                    bgra[pixelIdx]     = (byte)B;
                    bgra[pixelIdx + 1] = (byte)G;
                    bgra[pixelIdx + 2] = (byte)R;
                    bgra[pixelIdx + 3] = 255;
                }
            }

            mCustomCaptureTexture.LoadRawTextureData(bgra);
            mCustomCaptureTexture.Apply();

            if (!mLoggedSamplePixel)
            {
                int centerIdx = ((height / 2) * width + (width / 2)) * 4;
                mLoggedSamplePixel = true;
            }
        }

        private static int ClampByte(int v)
        {
            return v < 0 ? 0 : (v > 255 ? 255 : v);
        }
#endif

    private void UpdateCaptureTexture(int width, int height) {
      if (mCustomYuvData == null || mCustomCaptureTexture == null) return;
      if (mCustomFrameOffset + mCustomFrameSize > mCustomYuvData.Length) mCustomFrameOffset = 0;

      int ySize = width * height, uvSize = ySize / 4;
      Color32[] colors = new Color32[width * height];

      for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
          int Y = mCustomYuvData[mCustomFrameOffset + y * width + x];
          int U = mCustomYuvData[mCustomFrameOffset + ySize + (y / 2) * (width / 2) + (x / 2)];
          int V = mCustomYuvData[mCustomFrameOffset + ySize + uvSize + (y / 2) * (width / 2) + (x / 2)];
          int R = Mathf.Clamp((int)(Y + 1.402f * (V - 128)), 0, 255);
          int G = Mathf.Clamp((int)(Y - 0.344f * (U - 128) - 0.714f * (V - 128)), 0, 255);
          int B = Mathf.Clamp((int)(Y + 1.772f * (U - 128)), 0, 255);
          colors[y * width + x] = new Color32((byte)R, (byte)G, (byte)B, 255);
        }
      }
      mCustomCaptureTexture.SetPixels32(colors);
      mCustomCaptureTexture.Apply();

      // Diagnostic: log a center pixel once to verify the YUV->RGB content is not black
      if (!mLoggedSamplePixel) {
        Color32 c = colors[(height / 2) * width + (width / 2)];
        Debug.Log($"[CustomCapture] Center pixel RGBA=({c.r},{c.g},{c.b},{c.a})");
        mLoggedSamplePixel = true;
      }
    }

    private void StopCaptureInternal() {
      if (!mIsCustomVideoCapturing) return;

      mIsCustomVideoCapturing = false;
      Debug.Log("[CustomCapture] Stopping custom video capture...");

      // Immediately stop all capture coroutines on the persistent host.
      // This handles the case where the coroutine is mid-yield (WaitForSeconds etc.)
      // and hasn't had a chance to check mIsCustomVideoCapturing yet.
      if (s_coroutineHost != null) {
        s_coroutineHost.StopAllCoroutines();
      }

      if (mCustomCaptureTexture != null) {
        UnityEngine.Object.Destroy(mCustomCaptureTexture);
        mCustomCaptureTexture = null;
      }
      if (mPersistentBuffer != IntPtr.Zero) {
        Marshal.FreeHGlobal(mPersistentBuffer);
        mPersistentBuffer = IntPtr.Zero;
      }

      mTRTCCloud.enableCustomVideoCapture(TRTCVideoStreamType.TRTCVideoStreamTypeBig, false);

      mCustomYuvData = null;
      mCustomFrameOffset = 0;

      mTRTCCloud.setVideoEncoderParam(ref mSavedVideoEncParam);
      Debug.Log("[CustomCapture] Custom capture: restored encoder params, capture stopped");
    }

    #endregion
  }
}
