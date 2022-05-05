## SDK集成说明

本 SDK 集成IOS与Web通信方式（zs.call），以及常规蓝牙、GPS权限、扫描iBeacon等调用

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
}
```

#### 三、修改日志

2022.5.5 v1.8 添加Localizable.strings本地化；快捷url传入改为NSString *类型，内部进行urlEncode防止中文白屏

2022.4.28 v1.7 添加[webSDK removeJSCall]，销毁webSDK内循环引用（onJSCall不含强引用则无需调用）

2022.4.26 v1.6 添加url中文编码方法：[webSDK urlEncode:url]，修正含中文链接打开空白

2022.4.24 v1.5 修正navigationBar自定义设置

