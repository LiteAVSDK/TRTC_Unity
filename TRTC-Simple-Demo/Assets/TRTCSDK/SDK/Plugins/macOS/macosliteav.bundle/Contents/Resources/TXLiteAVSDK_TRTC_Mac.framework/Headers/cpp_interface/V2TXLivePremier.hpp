/// @defgroup V2TXLivePremier_cplusplus V2TXLivePremier
///
/// @{

#ifndef MODULE_CPP_V2TXLIVE_PREMIER_H_
#define MODULE_CPP_V2TXLIVE_PREMIER_H_

#include "V2TXLiveDef.hpp"

namespace liteav {
#ifdef _WIN32
class V2TXLivePremierObserver;
#endif

/////////////////////////////////////////////////////////////////////////////////
//
//                      V2TXLive 高级接口
//
/////////////////////////////////////////////////////////////////////////////////

class V2_API V2TXLivePremier {
   public:
    /**
     * 获取 SDK 版本号
     */
    static const char* getSDKVersionStr();

/**
 * 设置 V2TXLivePremier 回调接口
 */
#ifdef _WIN32
    static void setObserver(V2TXLivePremierObserver* observer);
#endif

/**
 * 设置 Log 的配置信息
 */
#ifdef _WIN32
    static int32_t setLogConfig(const V2TXLiveLogConfig& config);
#endif

    /**
     * 设置 SDK 接入环境
     *
     * @note 如您的应用无特殊需求，请不要调用此接口进行设置。
     * @param env 目前支持 “default” 和 “GDPR” 两个参数
     *        - default：默认环境，SDK 会在全球寻找最佳接入点进行接入。
     *        - GDPR：所有音视频数据和质量统计数据都不会经过中国大陆地区的服务器。
     */
    static int32_t setEnvironment(const char* env);

/**
 * 设置 SDK sock5 代理配置
 *
 * @param host sock5 代理服务器的地址
 * @param port sock5 代理服务器的端口
 * @param username sock5 代理服务器的验证的用户名
 * @param password sock5 代理服务器的验证的密码
 */
#ifdef _WIN32
    static int32_t setSocks5Proxy(const char* host, unsigned short port, const char* username, const char* password);
#endif

/**
 * 开启/关闭对音频采集数据的监听回调（可读写）
 *
 * @param enable 是否开启。 【默认值】：false
 * @param format 设置回调出的 AudioFrame 的格式
 *
 * @note 需要在 {@link V2TXLivePusher#startPush} 之前调用，才会生效。
 */
#ifdef _WIN32
    static int32_t enableAudioCaptureObserver(bool enable, const V2TXLiveAudioFrameObserverFormat& format);
#endif
};

/////////////////////////////////////////////////////////////////////////////////
//
//                      V2TXLive 高级回调接口
//
/////////////////////////////////////////////////////////////////////////////////

#ifdef _WIN32
class V2TXLivePremierObserver {
   public:
    virtual ~V2TXLivePremierObserver() {
    }

    /**
     * 自定义 Log 输出回调接口
     */
    virtual void onLog(V2TXLiveLogLevel level, const char* log){};

    /**
     * 本地麦克风采集到的音频数据回调
     *
     * @param frame 音频数据
     *
     * @note - 请不要在此回调函数中做任何耗时操作，建议直接拷贝到另一线程进行处理，否则会导致各种声音问题
     * @note - 此接口回调出的音频数据支持修改
     * @note - 此接口回调出的音频时间帧长固定为0.02s
     *         由时间帧长转化为字节帧长的公式为【采样率 × 时间帧长 × 声道数 × 采样点位宽】。
     *         以SDK默认的音频录制格式48000采样率、单声道、16采样点位宽为例，字节帧长为【48000 × 0.02s × 1 × 16bit = 15360bit = 1920字节】
     * @note - 此接口回调出的音频数据**不包含**背景音、音效、混响等前处理效果，延迟极低。
     * @note - 需要您调用 [enableAudioCaptureObserver](@ref V2TXLivePremier#enableAudioCaptureObserver) 开启回调开关
     */
    virtual void onCaptureAudioFrame(V2TXLiveAudioFrame* frame){};
};
#endif

}  // namespace liteav
#endif  // #ifndef MODULE_CPP_V2TXLIVE_PREMIER_H_
/// @}
