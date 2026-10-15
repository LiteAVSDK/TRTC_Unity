// Copyright (c) 2024 Tencent. All rights reserved.
// Author: kleinjia

import connection  from '@ohos.net.connection';
import { BusinessError } from "@ohos.base";
import radio from '@ohos.telephony.radio';
import { LiteavLog as Log } from './liteav_log';
import { Callback } from '@ohos.base';

export class NetworkStateMonitor {
  private static NETWORK_TYPE_UNSET = -1;
  private static NETWORK_TYPE_UNKNOWN = 0x0;
  private static NETWORK_TYPE_WIFI = 0x1;
  private static NETWORK_TYPE_4G = 0x2;
  private static NETWORK_TYPE_3G = 0x3;
  private static NETWORK_TYPE_2G = 0x4;
  private static NETWORK_TYPE_WIRED = 0x5;
  private static NETWORK_TYPE_5G = 0x6;

  private static instance: NetworkStateMonitor;
  private netConnection: connection.NetConnection | undefined = undefined;
  private networkType:number = NetworkStateMonitor.NETWORK_TYPE_UNSET;
  private onNetworkTypeChanged: Callback<number> | null = null;

  private constructor() {}
  
  public static getInstance(): NetworkStateMonitor {
    if (!NetworkStateMonitor.instance) {
      NetworkStateMonitor.instance = new NetworkStateMonitor();
    }
    return NetworkStateMonitor.instance;
  }

  public on(type: 'onNetworkTypeChanged', callback: Callback<number>): void {
    this.onNetworkTypeChanged = callback;
  }

  public start() {
    if (this.netConnection) {
      return;
    }
    this.netConnection = connection.createNetConnection();
    try {
      this.netConnection.register(() => {});
    } catch (error) {
      Log.error('NetworkStateMonitor', "register netConnection failed err:" + error);
      this.netConnection = undefined;
      return;
    }

    this.netConnection.on('netCapabilitiesChange', (capInfo: connection.NetCapabilityInfo) => {
      this.getNetworkTypeFromNetCapabilities(capInfo.netCap);
    });

    this.netConnection.on('netUnavailable', () => {
      this.setNetworkType(NetworkStateMonitor.NETWORK_TYPE_UNKNOWN); // 启动时没有网络的时候会调用
    })

    this.netConnection.on('netLost', (netHandle: connection.NetHandle) => {
      this.setNetworkType(NetworkStateMonitor.NETWORK_TYPE_UNKNOWN);  // 断开网络时调用
    });
  }

  public stop() {
    if (this.netConnection) {
      try {
        this.netConnection.unregister(() => {});
      } catch (error) {
        Log.error('NetworkStateMonitor', "unregister netConnection failed err:" + error);
      } finally {
        this.netConnection = undefined;
      }
    }
  }

  private setNetworkType(netType: number) {
    if (this.networkType != netType) {
      this.networkType = netType;
      if (this.onNetworkTypeChanged) {
        this.onNetworkTypeChanged(this.networkType);
      }
    }
  }

  private getNetworkTypeFromNetCapabilities(data: connection.NetCapabilities) {
    if (data && data.bearerTypes.length > 0) {
      if (data.bearerTypes[0] == connection.NetBearType.BEARER_WIFI) {
        this.setNetworkType(NetworkStateMonitor.NETWORK_TYPE_WIFI);
      } else if (data.bearerTypes[0] == connection.NetBearType.BEARER_ETHERNET) {
        this.setNetworkType(NetworkStateMonitor.NETWORK_TYPE_WIRED);
      } else if(data.bearerTypes[0] == connection.NetBearType.BEARER_CELLULAR) {
        this.getCellularType();
      } else {
        this.networkType = NetworkStateMonitor.NETWORK_TYPE_UNKNOWN;
      }
    } else {
      this.setNetworkType(NetworkStateMonitor.NETWORK_TYPE_UNKNOWN);
    }
  }

  private getCellularType():void {
    radio.getPrimarySlotId().then((slotId: number) => {
      radio.getSignalInformation(slotId, (err: BusinessError, data: Array<radio.SignalInformation>) => {
        if (err || data.length < 1) {
          this.setNetworkType(NetworkStateMonitor.NETWORK_TYPE_UNKNOWN);
          return;
        }
        for (let signalInfo of data) {
          if (signalInfo.signalLevel > 0) {
            switch (signalInfo.signalType) {
              case radio.NetworkType.NETWORK_TYPE_GSM:
              case radio.NetworkType.NETWORK_TYPE_CDMA:
                this.setNetworkType(NetworkStateMonitor.NETWORK_TYPE_2G);
                break;
              case radio.NetworkType.NETWORK_TYPE_WCDMA:
              case radio.NetworkType.NETWORK_TYPE_TDSCDMA:
                this.setNetworkType(NetworkStateMonitor.NETWORK_TYPE_3G);
                break;
              case radio.NetworkType.NETWORK_TYPE_LTE:
                this.setNetworkType(NetworkStateMonitor.NETWORK_TYPE_4G);
                break;
              case radio.NetworkType.NETWORK_TYPE_NR:
                this.setNetworkType(NetworkStateMonitor.NETWORK_TYPE_5G);
                break;
              default :
                this.setNetworkType(NetworkStateMonitor.NETWORK_TYPE_UNKNOWN);
            }
          }
        }
      });
    }).catch((error: BusinessError) => {
      this.setNetworkType(NetworkStateMonitor.NETWORK_TYPE_UNKNOWN);
    });
  }
}