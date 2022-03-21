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
 */

#import <Foundation/Foundation.h>
#import <WebKit/WebKit.h>

/// 用于支持ZS的H5产品进行iBeacon扫描定位的SDK
@interface WebSDK : NSObject
/// 快捷构造支持定位导航的H5的ViewController
/// @param url 访问的h5网站
+ (UIViewController *)createWebViewController:(NSURL *)url;
+ (UIViewController *)createWebViewController:(NSURL *)url delegate:(id<WKNavigationDelegate,WKUIDelegate>)delegate onJSCall:(void(^)(NSString *,id,void(^callback)(NSString *)))onJSCall;

/// 初始化构造一个JS和APP交互类
/// @param webView 需要定位JS交互的webView容器
- (instancetype)initWithWebView:(WKWebView *)webView;

/// 使用instancetype响应兼容包含zs.call("{}")，以及prompt("zs.call","{}")方法,  请在WKWebview.UIDelegate中runJavaScriptTextInputPanelWithPrompt:响应[self.WebSDK call:prompt:defaultText]
/// @param action 仅处理zs.call返回true，其他返回false
/// @param data js传入数据
- (BOOL)call:(NSString *)action data:(NSString *)data;

//执行JS方法
- (void)runJSFunction:(NSString *)func data:(NSString *)data delete:(BOOL)delCallBack completion:(void(^)(id,NSError*)) completion;

/// 单例构造JS和APP交互类（适合单个WebView场景）
/// @param webView  需要定位JS交互的webView容器
+ (instancetype)setupWebView:(WKWebView *)webView;

/// 会使用ZSWebSDK单例，兼容包含zs.call("{}")，以及prompt("zs.call","{}")方法, 请在WKWebview.UIDelegate中runJavaScriptTextInputPanelWithPrompt:响应[ZSWebSDK call:prompt:defaultText]
/// @param action  仅处理zs.call返回true，其他返回false
/// @param data  js传入数据
+ (BOOL)call:(NSString *)action data:(NSString *)data;

//执行JS方法
+ (void)runJSFunction:(NSString *)func data:(NSString *)data delete:(BOOL)delCallBack completion:(void(^)(id,NSError*)) completion;

/// 仅用于显示一个系统分享（obj内支持：NSString或NSDictinary{}）
/// @param obj 显示一个系统分享
+ (void)showShareView:(id)obj;

/// JS回调方法，设置此block(回调名称，回调数据string或dict，反回调JS方法)，可以响应JS方法：zs.call(JSON.stringify({"action":"回调名称","data":"回调数据","callback":"反回调JS方法名"}));
@property (nonatomic, copy) void (^onJSCall)(NSString *action,id data,void(^callback)(NSString *));

@end


/// 代理分发类，部分webView代理需要内部实现（js的alert，promt等）
@interface WebViewDelegateProxy : NSObject <WKNavigationDelegate,WKUIDelegate>
+ (instancetype)delagateTargets:(NSArray *)targets;
@end
