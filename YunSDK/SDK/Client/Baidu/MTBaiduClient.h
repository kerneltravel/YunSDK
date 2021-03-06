//
//  MTBaiduClient.h
//  YunSDK
//
//  Created by zrz on 12-11-4.
//  Copyright (c) 2012年 zrz. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MTOAuth.h"
#import "MTClientDefine.h"

@protocol MTBaiduClientDelegate;

@interface MTBaiduClient : NSObject
<MTOAuthDelegate>

@property (nonatomic, readonly) NSString    *consumerKey;
@property (nonatomic, readonly) NSString    *consumerSecret;
@property (nonatomic, strong)   NSString    *callback;
@property (nonatomic, strong)   NSDictionary    *oauthInfo;
@property (nonatomic, strong)   NSOperationQueue    *queue;

@property (nonatomic, assign)   id<MTBaiduClientDelegate>   delegate;

- (void)cleanCookies;

- (id)initWithConsumerKey:(NSString *)consumerKey
           consumerSecret:(NSString *)consumerSecret;

//直接调用oauth里面的startOAuthWithWebView:
- (BOOL)startOAuthWithWebView:(UIWebView *)webView;


/** 生成请求，params中不用写oauth参数
 *  第一个方法使用默认的baseUrl   https://pcs.baidu.com/rest
 *  第二个方法使用自定的baseUrl
 */
- (NSMutableURLRequest *)requestWithMethod:(NSString *)method
                                   urlPath:(NSString *)path
                                 urlParams:(NSDictionary *)urlParams
                                formParams:(NSDictionary *)formParams;

- (NSMutableURLRequest *)requestWithMethod:(NSString *)method
                                   urlPath:(NSString *)path
                                 urlParams:(NSDictionary *)urlParams
                                formParams:(NSDictionary *)formParams
                                   baseUrl:(NSString *)baseUrl;

#pragma mark - APIs

/**
 *  获得网盘用量
 *  2.0/pcs/quota
 */
- (void)checkDiskQuota;
- (void)checkDiskQuotaWithBlock:(MTClientDictionaryBlock)block;

/**
 *  上传文件
 *  2.0/pcs/file
 *  @param path 文件在网盘中的路径 必须
 *  @param file 文件数据 必须
 */
- (void)uploadFile:(NSString *)path
              file:(NSData *)file;
- (void)uploadFile:(NSString *)path
              file:(NSData *)file
             block:(MTClientDictionaryBlock)block;

/**
 *  2.0/pcs/file
 *  @param path 同上
 */
- (void)createFolderWithPath:(NSString *)path;
- (void)createFolderWithPath:(NSString *)path
                       block:(MTClientDictionaryBlock)block;

/**
 *  2.0/pcs/file    method:delete
 *  @param  path 同上
 */
- (void)deleteFile:(NSString *)path;
- (void)deleteFile:(NSString *)path
             block:(MTClientDictionaryBlock)block;

/**
 *  2.0/pcs/file
 *  @param  path 同上
 */
- (void)downloadFile:(NSString *)path;
- (void)downloadFile:(NSString *)path
               block:(MTClientDataBlock)block;

@end

@protocol MTBaiduClientDelegate <MTOAuthDelegate>

@optional

/**
 *  得到使用量
 *  example:
 *  {
 *  "quota":15000000000,
 *  "used":5221166,
 *  "request_id":4043312634
 *  }
 */
- (void)client:(id)client
  getDiskQuota:(NSDictionary *)dictionary
     withError:(NSError *)error;

/**
 *  上传文件
 *  {
 *  "path":"\/apps\/yunform\/music\/hello",
 *  "size":13,
 *  "ctime":1331184269,
 *  "mtime":1331184269,
 *  "md5":"59ca0efa9f5633cb0371bbc0355478d8",
 *  "fs_id":3528850315,
 *  "request_id":4043312669
 *  }
 */
- (void)client:(id)client
    uploadFile:(NSDictionary *)dictionary
     withError:(NSError *)error;

/**
 *  创建目录
 *  {
 *  "fs_id":1636599174,
 *  "path":"\/apps\/yunform\/music",
 *  "ctime":1331183814,
 *  "mtime":1331183814,
 *  "request_id":4043312656
 *  }
 */
- (void)client:(id)client
  createFolder:(NSDictionary *)dictionary
     withError:(NSError *)error;
/**
 *  创建目录
 * {
 *  "request_id":4043312866
 *  }
 */
- (void)client:(id)client
    deleteFile:(NSDictionary *)dictionary
     withError:(NSError *)error;


//下载文件
- (void)client:(id)client
  downloadFile:(NSData *)file
     withError:(NSError *)error;

@end
