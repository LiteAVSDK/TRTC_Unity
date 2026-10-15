using System;
using System.Runtime.InteropServices;
using UnityEngine;
using trtc;

namespace TRTCCUnityDemo {
  /// <summary>
  /// TRTC 自定义视频回调中的 OpenGL ES 纹理处理（仅 iOS / Android 真机生效）。
  ///
  /// 用法：在 ITRTCVideoFrameCallback 的实现里，把
  ///   onGLContextCreated / onProcessVideoFrame / onGLContextDestroy
  /// 三个回调直接转发到本类的同名静态方法。
  ///
  /// 当前实现：在画面右上角 1/4 区域 glClear 一个红色色块，验证回调链路。
  /// 接入真实美颜引擎（如 XMagic）时，把 DrawRedWatermark + glCopyTexSubImage2D
  /// 替换为 美颜引擎的 process(srcTex, w, h) -> dstTex 调用即可。
  /// </summary>
  public static class CustomBeautyProcessor {
    // 全平台共用的帧计数（Buffer 路径不依赖 GL，所有平台都会用到）
    private static int _frameCount = 0;

#if (UNITY_ANDROID || UNITY_IOS) && !UNITY_EDITOR
#if UNITY_ANDROID
    private const string GLLIB = "libGLESv2.so";
    private const string Platform = "Android";
#elif UNITY_IOS
    private const string GLLIB = "__Internal";   // iOS OpenGLES 走静态链接
    private const string Platform = "iOS";
#endif

    private const int GL_FRAMEBUFFER          = 0x8D40;
    private const int GL_COLOR_ATTACHMENT0    = 0x8CE0;
    private const int GL_TEXTURE_2D           = 0x0DE1;
    private const int GL_COLOR_BUFFER_BIT     = 0x00004000;
    private const int GL_SCISSOR_TEST         = 0x0C11;
    private const int GL_FRAMEBUFFER_COMPLETE = 0x8CD5;
    private const int GL_RGBA                 = 0x1908;
    private const int GL_UNSIGNED_BYTE        = 0x1401;

    [DllImport(GLLIB)] private static extern void glGenFramebuffers(int n, uint[] fbos);
    [DllImport(GLLIB)] private static extern void glDeleteFramebuffers(int n, uint[] fbos);
    [DllImport(GLLIB)] private static extern void glBindFramebuffer(int target, uint fbo);
    [DllImport(GLLIB)] private static extern void glFramebufferTexture2D(int target, int attachment, int textarget, uint texture, int level);
    [DllImport(GLLIB)] private static extern void glScissor(int x, int y, int w, int h);
    [DllImport(GLLIB)] private static extern void glEnable(int cap);
    [DllImport(GLLIB)] private static extern void glDisable(int cap);
    [DllImport(GLLIB)] private static extern void glClearColor(float r, float g, float b, float a);
    [DllImport(GLLIB)] private static extern void glClear(int mask);
    [DllImport(GLLIB)] private static extern int  glCheckFramebufferStatus(int target);
    [DllImport(GLLIB)] private static extern void glBindTexture(int target, uint texture);
    [DllImport(GLLIB)] private static extern void glCopyTexSubImage2D(int target, int level, int xoffset, int yoffset, int x, int y, int width, int height);
    [DllImport(GLLIB)] private static extern void glGenTextures(int n, uint[] textures);
    [DllImport(GLLIB)] private static extern void glDeleteTextures(int n, uint[] textures);
    [DllImport(GLLIB)] private static extern void glTexImage2D(int target, int level, int internalformat, int width, int height, int border, int format, int type, IntPtr pixels);

    private static uint _watermarkFbo = 0;
    private static uint _warmupSrcTex = 0;
    private static uint _warmupDstTex = 0;
    private static bool _warmedUp = false;
#endif

    public static void OnGLContextCreated() {
      Debug.Log("[CustomBeautyProcessor] onGLContextCreated");
#if (UNITY_ANDROID || UNITY_IOS) && !UNITY_EDITOR
      // 尝试在 GL 上下文创建时机预热：创建 FBO + 跑一次 dummy glCopyTexSubImage2D，
      // 把 iOS 驱动的 staging buffer / readback pipeline 提前初始化好。
      // 如果该回调线程的 GL 上下文不 current（不同 SDK 版本行为不一致），
      // 这里调用会被驱动忽略；OnProcessVideoFrame 首帧仍有兜底 warm up。
      WarmUp();
#endif
    }

    public static void OnGLContextDestroy() {
      Debug.Log("[CustomBeautyProcessor] onGLContextDestroy");
      _frameCount = 0;
#if (UNITY_ANDROID || UNITY_IOS) && !UNITY_EDITOR
      if (_watermarkFbo != 0) {
        uint[] fbos = new uint[] { _watermarkFbo };
        glDeleteFramebuffers(1, fbos);
        _watermarkFbo = 0;
      }
      if (_warmupSrcTex != 0 || _warmupDstTex != 0) {
        uint[] texs = new uint[] { _warmupSrcTex, _warmupDstTex };
        glDeleteTextures(2, texs);
        _warmupSrcTex = 0;
        _warmupDstTex = 0;
      }
      _warmedUp = false;
#endif
    }

    public static int OnProcessVideoFrame(TRTCVideoFrame srcFrame, ref TRTCVideoFrame dstFrame) {
      // Buffer 路径是纯 CPU 操作（Marshal.Copy + 内存遍历），所有平台都能跑
      // （mac / Windows / iOS / Android / Editor）
      if (srcFrame.bufferType == TRTCVideoBufferType.TRTCVideoBufferType_Buffer) {
        return ProcessBuffer(srcFrame, ref dstFrame);
      }

#if (UNITY_ANDROID || UNITY_IOS) && !UNITY_EDITOR
      // 默认走 OpenGL ES 纹理路径（仅 iOS / Android 真机有效）
      return ProcessTexture(srcFrame, ref dstFrame);
#else
      // 其它平台（mac / Windows / Editor）的 Texture 路径未实现，直接返回
      return 0;
#endif
    }

    /// <summary>
    /// CPU Buffer 路径：把 srcFrame.data 拷到 dstFrame.data，并把每个像素的第 0 字节置 0
    /// （BGRA32 时第 0 字节是 B 通道；I420 时是 Y 平面顶部）。仅用于验证 buffer 回调链路。
    /// 启用方式：mTRTCCloud.enableLocalVideoCustomProcess(true,
    ///                                                  TRTCVideoPixelFormat_BGRA32,
    ///                                                  TRTCVideoBufferType_Buffer);
    /// 全平台通用：纯 CPU 内存操作，不依赖任何 GL 调用。
    /// </summary>
    private static int ProcessBuffer(TRTCVideoFrame srcFrame, ref TRTCVideoFrame dstFrame) {
      if (srcFrame.data == IntPtr.Zero || dstFrame.data == IntPtr.Zero) {
        return 0;
      }

      int len = (int)srcFrame.length;
      if (len <= 0) return 0;

      if ((_frameCount++ % 60) == 0) {
        Debug.Log($"[CustomBeautyProcessor][Buffer] format={srcFrame.videoFormat}, " +
                  $"size={srcFrame.width}x{srcFrame.height}, len={len}");
      }

      // 1) src.data -> dst.data 整块拷贝
      byte[] buffer = new byte[len];
      Marshal.Copy(srcFrame.data, buffer, 0, len);

      // 2) 每像素的第 0 字节置 0（BGRA32: 把 B 通道清零，画面整体会偏黄色调，肉眼可见）
      for (int i = 0; i < len / 4; i++) {
        buffer[4 * i] = 0;
      }

      // 3) 写回 dst.data
      Marshal.Copy(buffer, 0, dstFrame.data, len);

      dstFrame.width = srcFrame.width;
      dstFrame.height = srcFrame.height;
      dstFrame.timestamp = srcFrame.timestamp;
      dstFrame.rotation = srcFrame.rotation;
      return 0;
    }

#if (UNITY_ANDROID || UNITY_IOS) && !UNITY_EDITOR
    /// <summary>
    /// OpenGL ES 纹理路径：iOS 走 glCopyTexSubImage2D + 红块；Android 走透传 + 红块。
    /// 启用方式：mTRTCCloud.enableLocalVideoCustomProcess(true,
    ///                                                  TRTCVideoPixelFormat_Texture_2D,
    ///                                                  TRTCVideoBufferType_Texture);
    /// </summary>
    private static int ProcessTexture(TRTCVideoFrame srcFrame, ref TRTCVideoFrame dstFrame) {
      int srcTex = srcFrame.texture.glTextureId;
      int dstTex = dstFrame.texture.glTextureId;
      int w = (int)srcFrame.width;
      int h = (int)srcFrame.height;

      if ((_frameCount++ % 60) == 0) {
        Debug.Log($"[CustomBeautyProcessor][{Platform}][Texture] srcTex={srcTex}, dstTex={dstTex}, " +
                  $"size={w}x{h}, rotation={srcFrame.rotation}");
      }

      // 写入 dst 帧基本字段：
      // - Android: 直接透传 srcTex 给 dstFrame.glTextureId
      // - iOS: SDK 提供的 dstTex 不能替换，需手动把 src 内容拷过去
#if UNITY_ANDROID
      dstFrame.texture.glTextureId = srcTex;
      dstFrame.texture.glContext   = srcFrame.texture.glContext;
#endif
      dstFrame.width     = srcFrame.width;
      dstFrame.height    = srcFrame.height;
      dstFrame.timestamp = srcFrame.timestamp;
      dstFrame.rotation  = srcFrame.rotation;

      if (srcTex == 0 || w <= 0 || h <= 0) {
        return 0;
      }

      // 兜底：如果 OnGLContextCreated 阶段没成功 warm up（不同 SDK 版本上下文 current 时机不一致），
      // 在第一次有真实纹理的回调里再 warm up 一次，让首帧拷贝走最简化路径。
      if (!_warmedUp) {
        WarmUp();
      }

      // FBO 在第一次调用时懒创建，后续帧复用（WarmUp 通常已创建好）
      if (_watermarkFbo == 0) {
        uint[] fbos = new uint[1];
        glGenFramebuffers(1, fbos);
        _watermarkFbo = fbos[0];
      }

#if UNITY_IOS
      ProcessIOS(srcTex, dstTex, w, h);
#else
      ProcessAndroid(srcTex, w, h);
#endif

      // 写一个无害的默认 GL 状态
      glDisable(GL_SCISSOR_TEST);
      glBindFramebuffer(GL_FRAMEBUFFER, 0);
      return 0;
    }

    /// <summary>
    /// 预热 GL 资源：FBO 创建 + 一张 dummy 纹理走一次 glCopyTexSubImage2D，
    /// 让 iOS 驱动的 staging buffer / readback pipeline 提前初始化完成。
    /// 调用时机：OnGLContextCreated（最佳）或首次 OnProcessVideoFrame（兜底）。
    /// </summary>
    private static void WarmUp() {
      if (_warmedUp) return;

      // 1) 创建 FBO
      if (_watermarkFbo == 0) {
        uint[] fbos = new uint[1];
        glGenFramebuffers(1, fbos);
        _watermarkFbo = fbos[0];
      }
      if (_watermarkFbo == 0) {
        Debug.LogWarning("[CustomBeautyProcessor] WarmUp: glGenFramebuffers failed (GL context maybe not current)");
        return;
      }

      // 2) 创建 2 张 dummy 纹理（src 16x16 + dst 16x16），分配空像素 storage
      uint[] texs = new uint[2];
      glGenTextures(2, texs);
      _warmupSrcTex = texs[0];
      _warmupDstTex = texs[1];

      glBindTexture(GL_TEXTURE_2D, _warmupSrcTex);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 16, 16, 0, GL_RGBA, GL_UNSIGNED_BYTE, IntPtr.Zero);

      glBindTexture(GL_TEXTURE_2D, _warmupDstTex);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 16, 16, 0, GL_RGBA, GL_UNSIGNED_BYTE, IntPtr.Zero);

      // 3) FBO 绑 srcTex，跑一次 glCopyTexSubImage2D —— 这是首帧主要耗时来源
      glBindFramebuffer(GL_FRAMEBUFFER, _watermarkFbo);
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _warmupSrcTex, 0);
      int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
      if (status == GL_FRAMEBUFFER_COMPLETE) {
        glBindTexture(GL_TEXTURE_2D, _warmupDstTex);
        glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, 16, 16);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        _warmedUp = true;
        Debug.Log("[CustomBeautyProcessor] WarmUp completed");
      } else {
        Debug.LogWarning($"[CustomBeautyProcessor] WarmUp: FBO incomplete status=0x{status:X}");
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
      }
    }
    /// <summary>
    /// iOS：先把 srcTex 内容 glCopyTexSubImage2D 拷到 dstTex，再在 dstTex 上画红块。
    /// 因为 iOS SDK 严格只读 dstTex 推流，不读 srcTex。
    /// 注：glCopyTexSubImage2D 首帧驱动初始化耗时较大（~1-2s），属已知现象。
    /// </summary>
    private static void ProcessIOS(int srcTex, int dstTex, int w, int h) {
      if (dstTex == 0) return;

      // 1) FBO 绑 srcTex 作为 read source
      glBindFramebuffer(GL_FRAMEBUFFER, _watermarkFbo);
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, (uint)srcTex, 0);
      int srcStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
      if (srcStatus == GL_FRAMEBUFFER_COMPLETE) {
        glBindTexture(GL_TEXTURE_2D, (uint)dstTex);
        glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, w, h);
        glBindTexture(GL_TEXTURE_2D, 0);
      } else if ((_frameCount % 60) == 1) {
        Debug.Log($"[CustomBeautyProcessor][iOS] FBO incomplete (src for copy) status=0x{srcStatus:X}");
      }

      // 2) FBO 绑 dstTex，scissor + glClear 在右上角画红块
      glBindFramebuffer(GL_FRAMEBUFFER, _watermarkFbo);
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, (uint)dstTex, 0);
      int dstStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
      if (dstStatus == GL_FRAMEBUFFER_COMPLETE) {
        DrawRedWatermark(w, h);
      } else if ((_frameCount % 60) == 1) {
        Debug.Log($"[CustomBeautyProcessor][iOS] FBO incomplete (dst) status=0x{dstStatus:X}");
      }
    }

    /// <summary>
    /// Android：dstFrame.glTextureId 已透传为 srcTex，直接在 srcTex 上画红块即可。
    /// </summary>
    private static void ProcessAndroid(int srcTex, int w, int h) {
      glBindFramebuffer(GL_FRAMEBUFFER, _watermarkFbo);
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, (uint)srcTex, 0);
      int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
      if (status == GL_FRAMEBUFFER_COMPLETE) {
        DrawRedWatermark(w, h);
      } else if ((_frameCount % 60) == 1) {
        Debug.Log($"[CustomBeautyProcessor][Android] FBO incomplete (src) status=0x{status:X}");
      }
    }

    /// <summary>
    /// 在当前绑定的 FBO 颜色附件上，用 scissor + glClear 画一个右上角红色色块。
    /// </summary>
    private static void DrawRedWatermark(int w, int h) {
      glEnable(GL_SCISSOR_TEST);
      int rw = w / 4;
      int rh = h / 4;
      glScissor(w - rw, h - rh, rw, rh);
      glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
    }
#endif
  }
}
