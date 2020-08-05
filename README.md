·准备工作
在进行水桥授权登录接入之前，在水桥开放平台注册开发者帐号，并拥有一个已审核通过的移动应用，并获得相应的 AppID，申请水桥登录且通过审核后，可开始接入流程。

1.目前移动应用上水桥登录只提供原生的登录方式，需要用户安装水桥客户端才能配合使用。

2.对于iOS应用，考虑到iOS应用商店审核指南中的相关规定，建议开发者接入水桥登录时，先检测用户手机是否已安装水桥客户端（使用sdk中isInstalled 函数 ），对未安装的用户隐藏水桥登录按钮，只提供其他登录方式（比如手机号注册登录、游客登录等）。
·集成
·手动集成
下载水桥终端SDK文件 下载地址
SDK 文件包括 libWaterBridgeSDK，WBApi.h 两个
·通过 CocoaPods 集成
·在 XCode 中建立你的工程。
·在工程的 Podfile 里面添加以下代码：
pod 'libWaterBridgeSDK'
保存并执行 pod install,然后用后缀为.xcworkspace 的文件打开工程。
注意:
命令行下执行 pod search libWaterBridgeSDK,如显示的 libWaterBridgeSDK版本不是最新的，则先执行 pod repo update 操作更新本地 repo 的内容
关于 CocoaPods 的更多信息请查看 CocoaPods 官方网站 。

·配置
[1] 在 Xcode 中，选择你的工程设置项，选中“TARGETS”一栏，在“info”标签栏的“URL type“添加“URL scheme”为你所注册的应用程序 id（如下图所示）。
规则为wb+APPID，如wb202083712837192837 请务必按此格式配置URLSchemes

[2] 由于iOS9引入白名单的概念。所以我们需要在Xcode中，选择你的工程设置项，选中“TARGETS”一栏，在 “info”标签栏的“LSApplicationQueriesSchemes“添加waterbridge（如下图所示）。

[3] 在你需要使 用水桥终端 API 的文件中 #import <libWaterBridgeSDK/WBApi.h>
 头文件，并增加 WBApiDelegate协议。

·示例代码
[1] 要使你的程序启动后水桥终端能响应你的程序，必须在代码中向水桥终端注册你的 id。（在 AppDelegate 的 didFinishLaunchingWithOptions 函数中向水桥注册 id）。
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    [WBApi registerApp:APPID];
    return YES;
}
[2]重写 AppDelegate 的 handleOpenURL 和 openURL 方法：
-(BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options{
    return [WBApi handleOpenURL:url delegate:self];
}


- (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url {
    return [WBApi handleOpenURL:url delegate:self];
}
一旦流程全部跑通，url中将携第三方授权带登录所需参数，处理后将通过协议方法返回。为演示方便 ，这边delegate设为了自己，实际项目可以根据需求设为其他对象。

[3] 现在，你的程序要实现和水桥终端交互的具体请求与回应，因此需要实现 WBApiDelegate协议的方法：
- (void)onWaterBridgeResp:(WBAuth *)resp{
    
}
如果授权登录成功 ，将会在上面方法返回用户信息。比如openId、昵称 、头像等
[4] 在需要授权登录的地方调起水桥app
在调起前可以判断是否安装水桥且设置了白名单可跳转
[WBApi isInstalled] 结果为true则代表可以调起水桥app
[WBApi sendAuthRequestWithCompletion:^(NSError * _Nullable error) {

}];
如果授权失败 ，在上述回调中获取错误状态码及错误信息。

·常见问题及解决方法
一.无法跳转到水桥App
1.iOS9 引入白名单的概念，是否将水桥的url scheme(waterbridge)配置到白名单，详见配置【2】
2.APPID是否正确 及 是否已注册，详见 示例代码【1】
3.检查网络是否良好
4.参考控制台错误信息对照表

二.跳转水桥后无法回到App
1.由于审核原因，水桥无法动态配置所有要跳转的App。水桥会默认待跳转的app的url scheme为以上规则拼接（wb+APPID）。 因此需检查App的url scheme 是否按照上述配置。详见 配置【1】
2.因为需要水桥相关信息，因此水桥需要已登录状态。未登录状态会跳转到登录页，完成登录后方可回到App
3.检查网络是否良好
4.参考控制台错误信息对照表

三.App如何知道用户的手机是否已安装水桥
1.配置水桥的url scheme到白名单 ，调用sdk的 isInstalled 方法，详情 示例代码【4】

