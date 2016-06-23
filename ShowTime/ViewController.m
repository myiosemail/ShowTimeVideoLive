//
//  ViewController.m
//  ShowTime
//
//  Created by YJ on 16/6/16.
//  Copyright © 2016年 YJ. All rights reserved.
//

#import "ViewController.h"


#define kClassKey   @"rootVCClassString"
#define kTitleKey   @"title"
#define kImgKey     @"imageName"
#define kSelImgKey  @"selectedImageName"

//**********************************************************************************
//function:颜色值的宏
//**********************************************************************************
#define RGBCOLOR(r,g,b) [UIColor colorWithRed:(r)/255.0f green:(g)/255.0f blue:(b)/255.0f alpha:1.0]
//#define RGBACOLOR(r,g,b,a) [UIColor colorWithRed:(r)/255.0f green:(g)/255.0f blue:(b)/255.0f alpha:(a)]
#define RGBVCOLOR(v) RGBCOLOR(((v&0xFF0000)>>16),((v&0xFF00)>>8),(v&0xFF))
#define RGBVACOLOR(v,a) RGBACOLOR(((v&0xFF0000)>>16),((v&0xFF00)>>8),(v&0xFF),a)

#define Global_tintColor RGBCOLOR(235, 105, 96)

//**********************************************************************************
//function:宽度
//**********************************************************************************
#define SCREEN_WIDTH ([UIScreen mainScreen].bounds.size.width)

//**********************************************************************************
//function:高度
//**********************************************************************************
#define SCREEN_HEIGHT ([UIScreen mainScreen].bounds.size.height)

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self setupView];
}
-(void)setupView{
    
    NSArray *childItemsArray = @[
                                 @{kClassKey  : @"HomeViewController",
                                   kTitleKey  : @"首页",
                                   kImgKey    : @"tabbar_home_nomal",
                                   kSelImgKey : @"tabbar_home"},
                                 
                                 @{kClassKey  : @"LiveViewController",
                                   kTitleKey  : @"直播",
                                   kImgKey    : @"tabbar_find_nomal",
                                   kSelImgKey : @"tabbar_find"}];
    [childItemsArray enumerateObjectsUsingBlock:^(NSDictionary *dict, NSUInteger idx, BOOL *stop) {
        UIViewController * vc = [NSClassFromString(dict[kClassKey]) new];
        vc.title = dict[kTitleKey];
        UINavigationController * nav = [[UINavigationController alloc] initWithRootViewController:vc];
        UITabBarItem * item = nav.tabBarItem;
        item.title = dict[kTitleKey];
        item.image = [[UIImage imageNamed:dict[kImgKey]] imageWithRenderingMode:UIImageRenderingModeAlwaysOriginal];
        item.selectedImage = [[UIImage imageNamed:dict[kSelImgKey]] imageWithRenderingMode:UIImageRenderingModeAlwaysOriginal];
        [item setTitleTextAttributes:@{NSForegroundColorAttributeName:Global_tintColor} forState:UIControlStateSelected];
        [item setTitleTextAttributes:@{NSForegroundColorAttributeName:RGBVCOLOR(0xffffff)} forState:UIControlStateNormal];
        
        [self addChildViewController:nav];
        
    }];
    //背景颜色
    UIView * backView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, SCREEN_WIDTH, 49)];
    backView.backgroundColor = RGBCOLOR(38, 38, 38);
    [[UITabBar appearance] insertSubview:backView atIndex:0];
    [UITabBar appearance].opaque = YES;
    
}

@end
