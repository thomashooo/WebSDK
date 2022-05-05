//
//  WebSDK.h
//  WebSDK
//
//  Created by thomasho on 2021/11/11.
//  Copyright © 2021 thomasho. All rights reserved.
//
//info.plist 权限添加：定位权限，相机权限，语音权限，网络权限。
/*
 <key>NSLocationAlwaysAndWhenInUseUsageDescription</key>
 <string>寻车导航</string>
 <key>NSCameraUsageDescription</key>
 <string>使用相机</string>
 <key>NSLocationWhenInUseUsageDescription</key>
 <string>寻车定位期间</string>
 <key>NSMicrophoneUsageDescription</key>
 <string>用于语音搜索服务</string>
 <key>NSAppTransportSecurity</key>
 <dict>
 <key>NSAllowsArbitraryLoads</key>
 <true/>
 </dict>
 
 //自定义导航栏颜色(默认白色，IOS13+为systemBackgroundColor)
 - (UIColor *)webViewNavigtionBarColor {
    return [UIColor blackColor];
 }
 - (UIColor *)webViewNavigtionBarTintColor {
    return [UIColor whiteColor];
 }
 */

#import <Foundation/Foundation.h>
#import <WebKit/WebKit.h>

/// 用于支持的H5产品进行iBeacon扫描定位的SDK
@interface WebSDK : NSObject

/// JS回调方法，设置此block(回调名称，回调数据string或dict，反回调JS方法)，可以响应JS方法：zs.call(JSON.stringify({"action":"回调名称","data":"回调数据","callback":"反回调JS方法名"}));
/// 如果jsCall内有循环引用，务必弱引用或在销毁时置空：webSDK.onJSCall = nil;
@property (nonatomic, copy) void (^onJSCall)(NSString *action,id data,void(^callback)(NSString *));

/// 初始化构造一个JS和APP交互类
/// @param webView 需要定位JS交互的webView容器
- (instancetype)initWithWebView:(WKWebView *)webView;

/// 单例构造JS和APP交互类（适合单个WebView场景）
/// @param webView  需要定位JS交互的webView容器
+ (instancetype)setupWebView:(WKWebView *)webView;


/// 针对url转码，防止部分链接包含中文无法打开
+ (NSString *)urlEncode:(NSString *)url;

/// 快捷构造支持定位导航的H5的ViewController
/// @param url 访问的h5网站
+ (UIViewController *)createWebViewController:(NSString *)url;
+ (UIViewController *)createWebViewController:(NSString *)url delegate:(id<WKNavigationDelegate,WKUIDelegate>)delegate onJSCall:(void(^)(NSString *,id,void(^callback)(NSString *)))onJSCall;

/// 如果jsCall内有循环应引用，采用弱引用或在销毁时手动调用此方法置空：[WebSDK removeJSCall]（防止内存循环引用）
+ (void)removeJSCall;

@end

/// 代理类，部分webView代理必要内部实现（js的alert，promt等）
@interface WebViewDelegateProxy : NSObject <WKNavigationDelegate,WKUIDelegate>
@end
