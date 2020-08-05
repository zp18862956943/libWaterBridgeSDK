//
//  WBApi.h
//  WaterBridgeSDK
//
//  Created by 周鹏 on 2020/4/11.
//  Copyright © 2020 周鹏. All rights reserved.
//

#import <UIKit/UIKit.h>

@class WBAuth;

NS_ASSUME_NONNULL_BEGIN

@protocol WBApiDelegate <NSObject>
@optional

/*! @brief 发送一个sendReq后，收到微信的回应
 *
 * 收到一个来自微信的处理结果。调用一次sendReq后会收到onResp。
 * 可能收到的处理结果有SendMessageToWXResp、SendAuthResp等。
 * @param resp 具体的回应内容，是自动释放的
 */
- (void)onWaterBridgeResp:(WBAuth *)resp;

@end

@interface WBApi : NSObject

/*! @brief 检查水桥是否已被用户安装
 *
 * @return 水桥已安装返回YES，未安装返回NO。
 */
+ (BOOL)isInstalled;

/*! @brief WBApi的成员函数，向微信终端程序注册第三方应用。
*/
+ (BOOL)registerApp:(NSString *)appid;

/// 调起水桥程序
+(void)sendAuthRequestWithCompletion:(void (^)(NSError * _Nullable error))completion;

/*! @brief 处理微信通过URL启动App时传递的数据
 *
 * 需要在 application:openURL:sourceApplication:annotation:或者application:handleOpenURL中调用。
 * @param url 微信启动第三方应用时传递过来的URL
 * @param delegate  WBApiDelegate对象，用来接收微信触发的消息。
 * @return 成功返回YES，失败返回NO。
 */
+ (BOOL)handleOpenURL:(NSURL *)url delegate:(nullable id<WBApiDelegate>)delegate;

@end

@interface WBAuth : NSObject

/// openid
@property(nonatomic, copy) NSString *openId;

/// 手机号
@property(nonatomic, copy) NSString *mobile;

/// 手机区号
@property(nonatomic, copy) NSString *mobileCode;

/// 昵称
@property(nonatomic, copy) NSString *nickName;

/// 头像
@property(nonatomic, copy) NSString *headUrl;

+(instancetype)authWithDic:(NSDictionary*)dic;

@end

NS_ASSUME_NONNULL_END
