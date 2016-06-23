//
//  XMNShareScrollView.h
//  XMNShareMenuExample
//
//  Created by XMFraker on 16/1/25.
//  Copyright © 2016年 XMFraker. All rights reserved.
//

#import <UIKit/UIKit.h>


@class XMNShareScrollView;
@protocol XMNShareScrollViewDelegate <NSObject>

- (void)scrollView:(XMNShareScrollView *)shareScrollView didSelelctedIndex:(NSUInteger)index title:(NSString *)title;

@end

@interface XMNShareScrollView : UIScrollView

@property (nonatomic, weak)   id<XMNShareScrollViewDelegate> shareDelegate;

- (void)setupShareScrollViewWithItems:(NSArray *)items;

+ (CGFloat)heightForScrollView;

@end
