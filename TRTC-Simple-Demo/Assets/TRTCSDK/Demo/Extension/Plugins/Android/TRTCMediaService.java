package com.tencent.trtc.unity;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.graphics.BitmapFactory;
import android.os.Build;
import android.os.IBinder;
import android.util.Log;

public class TRTCMediaService extends Service {
    private static final String TAG = TRTCMediaService.class.getSimpleName();

    private static final String NOTIFICATION_CHANNEL_ID = "com.tencent.trtc.unity.MediaService";
    private static final String NOTIFICATION_CHANNEL_NAME = "com.tencent.trtc.unity.channel_name";
    private static final String NOTIFICATION_CHANNEL_DESC = "com.tencent.trtc.unity.channel_desc";

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public void onCreate() {
        super.onCreate();
        startNotification();
    }

    public void startNotification() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {

            PackageManager pm = getPackageManager();
            String pkgName = getApplicationContext().getPackageName();
            int icon = android.R.drawable.ic_menu_share;
            try {
                ApplicationInfo ai = pm.getApplicationInfo(pkgName, 0);
                icon = ai.icon;
            } catch (Exception ignore) {
                Log.d(TAG, "getApplicationInfo error");
            }

            Intent notificationIntent = new Intent(this, TRTCMediaService.class);
            PendingIntent pendingIntent = PendingIntent.getActivity(
                    this, 0, notificationIntent, 0);

            Notification.Builder notificationBuilder =
                    new Notification.Builder(this, NOTIFICATION_CHANNEL_ID)
                    .setLargeIcon(BitmapFactory.decodeResource(getResources(), icon))
                    .setSmallIcon(icon)
                    .setContentTitle("Starting Service")
                    .setContentText("Starting monitoring service")
                    .setContentIntent(pendingIntent);
            Notification notification = notificationBuilder.build();
            NotificationChannel channel = new NotificationChannel(
                    NOTIFICATION_CHANNEL_ID,
                    NOTIFICATION_CHANNEL_NAME,
                    NotificationManager.IMPORTANCE_DEFAULT);

            channel.setDescription(NOTIFICATION_CHANNEL_DESC);
            NotificationManager notificationManager = (NotificationManager)
                    getSystemService(Context.NOTIFICATION_SERVICE);
            notificationManager.createNotificationChannel(channel);
            startForeground(1, notification);
        }
    }

}
