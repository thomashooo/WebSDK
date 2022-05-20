## WebSDK集成说明

本 WebSDK 集成常规WKWebView需要的alert，promt等必要衔接回调。

也添加了定位导航所需，蓝牙、GPS权限、扫描iBeacon等调用API。

（系统初始化会内置window.zs，可以通过据此判断是否支持）

#### 一、引入SDK文件到项目

1、将webSDK.h/a拖动到项目

2、配置项目权限列表，打开info.plist添加：

```javascript
    <key>NSLocationWhenInUseUsageDescription</key>
    <string>进行定位导航</string>
    <key>NSBluetoothPeripheralUsageDescription</key>
    <string>扫描周边iBeacon</string>
    <key>NSCameraUsageDescription</key>
    <string>展示实景</string>
    <key>NSMotionUsageDescription</key>
    <string>辅助定位导航</string>
     <key>NSMicrophoneUsageDescription</key>
     <string>用于语音搜索服务</string>
    <key>NSAppTransportSecurity</key>
    <dict>
        <key>NSAllowsArbitraryLoads</key>
        <true/>
    </dict>
```

#### 二、快速启动

```objective-c
#import "WebSDK.h"
- (IBAction)pushNaviController (){
   [self.navigationController pushViewController:[WebSDK createWebViewController:(NSString *)url] animated:YES];
  //另有webView自定义delegate处理、数据交互调用方式：createWebViewController:delegate:onJSCall:;
}
```

#### 三、自定义启动

```objective-c
    WKWebViewConfiguration *cfg = [[WKWebViewConfiguration alloc] init];
    cfg.allowsInlineMediaPlayback = YES;
    if (@available(iOS 13.0, *)) {
        cfg.defaultWebpagePreferences.preferredContentMode = WKContentModeMobile;
    }
    _webView = [[WKWebView alloc] initWithFrame:self.view.bounds configuration:cfg];
    [_webView loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:[WebSDK urlEncode:_urlStr]]]];
    [self.view addSubview:_webView];
    //注入定位、导航、交互
    WebSDK *sdk = [WebSDK setupWebView:_webView];
        //自定义交互示例：
        //页面调用:zs.call(JSON.stringify({action:'test',data:'string & obj',callback:'appCall'}));window.appCall=function(res){ alert(res); };
        //SDK 响应示例：
        [sdk setOnJSCall:^(NSString * action,id data, void (^callback)(NSString *)) {
         if([action isEqualToString:@"test"]) {
            NSLog(@"%@",data);
            callback(@"test callback.");
                 }
    }];
```

#### 四、修改日志

2022.5.18 v1.9 规避web弹窗权限请求。

2022.5.5 v1.8 添加Localizable.strings文件，需本地化可拷入主项目；快捷url传入改为NSString *类型，内部进行urlEncode防止中文白屏

2022.4.28 v1.7 添加[webSDK removeJSCall]，销毁webSDK内循环引用（onJSCall不含强引用则无需调用）

2022.4.26 v1.6 添加url中文编码方法：[webSDK urlEncode:url]，修正含中文链接打开空白

2022.4.24 v1.5 修正navigationBar自定义设置
