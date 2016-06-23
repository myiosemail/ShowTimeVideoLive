//
//  ListModel.h
//  ShowTime
//
//  Created by YJ on 16/6/16.
//  Copyright © 2016年 YJ. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
@interface ListModel : NSObject
/*

 city = "\U65e0\U9521\U5e02";
 creator =             {
 birth = "1987-07-31";
 description = "\U4e3b\U64ad\U5728\U5403\U571f\Uff0c\U522b\U5957\U8def\U6211\U4e86\U3002VB\Uff1a\U89c5\U5f97\U4e00";
 emotion = "\U4fdd\U5bc6";
 gender = 1;
 gmutex = 1;
 hometown = "\U706b\U661f&";
 id = 1494553;
 "inke_verify" = 0;
 level = 91;
 location = "\U65e0\U9521\U5e02";
 nick = "\U795e\U63a2\U00b7\U6211\U662f\U5c01\U5148\U751f";
 portrait = "NzY1NzIxNDY1ODgzNzUy.jpg";
 profession = "\U6d6e\U4e91";
 "rank_veri" = 13;
 "third_platform" = 1;
 "veri_info" = "\U9738\U9053\U603b\U88c1";
 verified = 0;
 "verified_reason" = "";
 };
 group = 1;
 id = 1466064820230495;
 image = "";
 link = 0;
 multi = 0;
 name = "#\U6ca1\U6574\U5bb9\U3001\U4e0d\U88c5\U903c\Uff0c\U4e0d\U5957\U8def\Uff0c\U4f60\U95ee\U6211\U7b54#";
 "online_users" = 52905;
 optimal = 0;
 "pub_stat" = 1;
 "room_id" = 352171551;
 "share_addr" = "http://live.a8.com/s/?uid=1494553&liveid=1466064820230495&ctime=1466064820";
 slot = 2;
 status = 1;
 "stream_addr" = "http://pull99.a8.com/live/1466064820230495.flv?ikHost=ws&ikOp=1";
 version = 0;
 */
/** 播放流地址 */
@property(nonatomic,copy)NSString * stream_addr;
/** 在线人数 */
@property(nonatomic,copy)NSString * online_users;
/** 详情 */
@property(nonatomic,strong)NSDictionary * creator;
/** id */
@property(nonatomic,copy)NSString * id;
/** 高度 */
@property(nonatomic,assign,readonly)CGFloat  cellHeight;
@end
