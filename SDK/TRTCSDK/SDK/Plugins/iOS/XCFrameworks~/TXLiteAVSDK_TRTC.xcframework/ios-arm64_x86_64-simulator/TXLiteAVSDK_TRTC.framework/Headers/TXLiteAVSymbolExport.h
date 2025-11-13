// Copyright (c) 2021 Tencent. All rights reserved.
// Author: gamhonghu

#ifndef SDK_COMMON_APPLE_TXLITEAVSYMBOLEXPORT_H_
#define SDK_COMMON_APPLE_TXLITEAVSYMBOLEXPORT_H_

#if defined(BUILD_LITEAVSDK)
#define LITEAV_EXPORT __attribute__((visibility("default")))
#else
#define LITEAV_EXPORT
#endif

#endif  // SDK_COMMON_APPLE_TXLITEAVSYMBOLEXPORT_H_