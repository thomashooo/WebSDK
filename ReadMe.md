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
   [self.navigationController pushViewController:[WebSDK createWebViewController:url] animated:YES];
}
```

#### 三、修改日志

2022.4.26 v1.6 添加内部编码，修正中文url打开空白

2022.4.24 v1.5 修正navigationBar自定义设置

