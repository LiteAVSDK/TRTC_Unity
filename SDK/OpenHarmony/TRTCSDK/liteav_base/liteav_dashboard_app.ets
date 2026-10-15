
import { BusinessError } from '@ohos.base';
import window from '@ohos.window';


let storage: LocalStorage = new LocalStorage();
storage.setOrCreate('dashboardIDList', [] as string[])
storage.setOrCreate('dashboardStatusList', {} as Record<string, string>)
storage.setOrCreate('dashboardLogList', {} as Record<string, string>)

@Entry({ routeName: 'liteav_dashboard_view', storage: storage})
@Component
struct DashBoardView {
  aboutToAppear(): void {}
  aboutToDisappear() {}

  @LocalStorageLink('dashboardIDList') dashboardIDList: string[] = [];
  @LocalStorageLink('dashboardStatusList') dashboardStatusList: Record<string, string> = {};
  @LocalStorageLink('dashboardLogList') dashboardLogList: Record<string, string> = {};
  @State selectedIDIndex: number = -1;

  private logScroller: Scroller = new Scroller();

  build() {
    Flex({direction: FlexDirection.Column, wrap: FlexWrap.NoWrap}) {
      Row() {
        Text("Dashboard")
        Blank()
        Button('Close').onClick(()=> {
          let windowClass = window.findWindow("liteav_dashboard_window");
          windowClass.destroyWindow();
        })
      }.width('100%').flexBasis('auto')
      Row() {
        Select(this.dashboardIDList.map((i) => { return {value: i} as SelectOption; }))
          .selected(Math.min(this.dashboardIDList.length-1, Math.max(0, (this.selectedIDIndex))))
          .value(this.dashboardIDList[Math.min(this.dashboardIDList.length-1, Math.max(0, (this.selectedIDIndex)))])
          .onSelect((index: number, text?: string | undefined) => {
            this.selectedIDIndex = index;
          })
          .width('100%');
      }.width('100%').flexBasis('auto')
      Text(this.dashboardStatusList[this.dashboardIDList[Math.min(this.dashboardIDList.length - 1, Math.max(0, (this.selectedIDIndex)))]])
        .fontSize(12).align(Alignment.TopStart).width('100%').padding(5)
        .width('100%').height('25%').flexGrow(1).border({ width: 1, color: Color.Black, style: BorderStyle.Solid})
      Scroll(this.logScroller) {
        Text(this.dashboardLogList[this.dashboardIDList[Math.min(this.dashboardIDList.length-1, Math.max(0, (this.selectedIDIndex)))]])
          .fontSize(12).align(Alignment.TopStart).width('100%').padding(5)
      }.width('100%').height('50%').flexGrow(2).border({ width: 1, color: Color.Black, style: BorderStyle.Solid})
    }.width('100%').padding(30).backgroundColor(Color.Gray)
  }
}

export class LiteavDashboardApp {
  private windowClass: window.Window | undefined = undefined;

  public nativeShowDashboard() {
    let config: window.Configuration = {
      name: "liteav_dashboard_window",
      windowType: window.WindowType.TYPE_DIALOG,
      ctx: globalThis.getContext()
    };
    window.createWindow(config, (err: BusinessError, data: window.Window) => {
      if (err.code) {
        console.error('Failed to create the Window. Cause:' + JSON.stringify(err));
        return;
      }

      this.windowClass = data;
      console.info('Succeeded in creating the window. Data:' + JSON.stringify(data));
      this.windowClass?.loadContentByName('liteav_dashboard_view', (err) => {
        if (err.code) {
          console.error('Failed to load the content. Cause: ' + JSON.stringify(err));
          return;
        }
        console.info('Succeeded in loading the content.');
        this.windowClass?.showWindow( (err: BusinessError) => {
          if (err.code) {
            console.error('Failed to show the window. Cause: ' + JSON.stringify(err));
            return;
          }
          console.info('Succeeded in showing the window.');
        });
      });
    });
  }

  public nativeHideDashboard() {
    this.windowClass?.destroyWindow((err: BusinessError) => {
      if (err.code) {
        console.error('Failed to destroy the window. Cause:' + JSON.stringify(err));
        return;
      }
      console.info('Succeeded in destroying the window.');
    });
  }

  public nativeAddDashboard(dashboardID: string) {
    let dashboardIDList = storage.get('dashboardIDList') as string[];
    const index = dashboardIDList.findIndex(item => item === dashboardID);
    if (index !== -1) {
      return;
    }
    dashboardIDList.push(dashboardID);
  }

  public nativeRemoveDashboard(dashboardID: string) {
    let dashboardIDList = storage.get('dashboardIDList') as string[];
    const index = dashboardIDList.findIndex(item => item === dashboardID);
    if (index === -1) {
      return;
    }

    dashboardIDList.splice(index, 1);
    let dashboardStatusList = storage.get('dashboardStatusList') as Record<string, string>;
    dashboardStatusList[dashboardID] = ""
    let dashboardLogList = storage.get('dashboardLogList') as Record<string, string>;
    dashboardLogList[dashboardID] = ""
  }

  public nativeRemoveAllDashboard() {
    storage.setOrCreate('dashboardIDList', [] as string[])
    storage.setOrCreate('dashboardStatusList', {} as Record<string, string>)
    storage.setOrCreate('dashboardLogList', {} as Record<string, string>)
  }

  public nativeSetStatus(dashboardID: string, status: string) {
    let dashboardIDList = storage.get('dashboardIDList') as string[];
    const index = dashboardIDList.findIndex(item => item === dashboardID);
    if (index === -1) {
      return;
    }
    let dashboardStatusList = storage.get('dashboardStatusList') as Record<string, string>;
    dashboardStatusList[dashboardID] = status;
  }

  public nativeAppendLog(dashboardID: string, log: string) {
    let dashboardIDList = storage.get('dashboardIDList') as string[];
    const index = dashboardIDList.findIndex(item => item === dashboardID);
    if (index === -1) {
      return;
    }
    let dashboardLogList = storage.get('dashboardLogList') as Record<string, string>;
    let logOld = dashboardLogList[dashboardID];
    if (typeof logOld === 'string') {
      dashboardLogList[dashboardID] = logOld + "\n" + log;
    } else {
      dashboardLogList[dashboardID] = log;
    }
  }
}