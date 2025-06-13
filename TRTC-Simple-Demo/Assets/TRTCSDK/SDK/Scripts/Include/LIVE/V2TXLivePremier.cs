// Copyright (c) 2023 Tencent. All rights reserved.
// Author: makbaktan

namespace liteav {
  public abstract class V2TXLivePremier {
    public static void setLicense(string url, string key) {
      V2TXLivePremierNative.v2tx_live_premier_set_license(url, key);
    }
  }
}