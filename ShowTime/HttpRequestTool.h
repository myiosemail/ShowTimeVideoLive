//
//  HttpRequestTool.h
//  ShowTime
//
//  Created by YJ on 16/6/16.
//  Copyright © 2016年 YJ. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MJExtension.h"
@interface HttpRequestTool : NSObject

+ (void)getWithURLString:(NSString *)URLString
              parameters:(id)parameters
                 success:(void (^)(NSDictionary * dictionary))success
                 failure:(void (^)(NSError * error))failure;
+ (void)postWithURLString:(NSString *)URLString
               parameters:(id)parameters
                  success:(void (^)(id))success
                  failure:(void (^)(NSError *))failure;
+ (void)uploadWithURLString:(NSString *)URLString
                 parameters:(id)parameters
                 uploadData:(NSData *)uploadData
                 uploadName:(NSString *)uploadName
                    success:(void (^)())success
                    failure:(void (^)(NSError *))failure;
+ (void)uploadMostImageWithURLString:(NSString *)URLString
                         parameters:(id)parameters
                        uploadDatas:(NSArray *)uploadDatas
                         uploadName:(NSString *)uploadName
                            success:(void (^)())success
                            failure:(void (^)(NSError *))failure;
@end
