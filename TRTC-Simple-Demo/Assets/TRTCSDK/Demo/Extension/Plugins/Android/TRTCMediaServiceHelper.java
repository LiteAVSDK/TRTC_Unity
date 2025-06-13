package com.tencent.trtc.unity;

import android.content.Context;
import android.content.Intent;

public class TRTCMediaServiceHelper {

    public static void launchService(Context context) {
        if (context == null) {
            return;
        }
        context.startService(new Intent(context, TRTCMediaService.class));
    }
}
