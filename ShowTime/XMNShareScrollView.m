//
//  XMNShareScrollView.m
//  XMNShareMenuExample
//
//  Created by XMFraker on 16/1/25.
//  Copyright © 2016年 XMFraker. All rights reserved.
//

#import "XMNShareScrollView.h"

#import "XMNShareMenu.h"

NSString *const kXMNShareTitle = @"com.XMFraker.kXMNShareTitle";
NSString *const kXMNShareImage = @"com.XMFraker.kXMNShareImage";
NSString *const kXMNShareHighlightImage = @"com.XMFraker.kXMNShareHighlightImage";
NSString *const kXMNShareTag = @"com.XMFraker.kXMNShareTag";

@implementation XMNShareScrollView

#pragma mark - Methods

/// ========================================
/// @name   Public Methods
/// ========================================

- (void)setupShareScrollViewWithItems:(NSArray *)items {
    //先移除之前的View
    if (self.subviews.count > 0) {
        [self.subviews makeObjectsPerformSelector:@selector(removeFromSuperview)];
    }
    //设置当前scrollView的contentSize
    if (items.count > 0) {
        //单行
        self.contentSize = CGSizeMake(kXMNOriginX + items.count*(kXMNItemWidth+kXMNHorizontalSpace), self.frame.size.height);
    }
    
    //遍历标签数组,将标签显示在界面上,并给每个标签打上tag加以区分
    for (NSDictionary *shareDic in items) {
        NSUInteger index = [items indexOfObject:shareDic];
        NSUInteger tag = shareDic[kXMNShareTag] ? [shareDic[kXMNShareTag] integerValue] : index;
        CGRect frame = CGRectMake(kXMNOriginX+index*(kXMNItemWidth+kXMNHorizontalSpace), KXMNOriginY, kXMNItemWidth, kXMNItemWidth+kXMNHorizontalSpace+kXMNTitleFontSize);
        UIView *view = [self _itemWithFrame:frame itemInfo:shareDic tag:tag];
        [self addSubview:view];
    }
    
}

/// ========================================
/// @name   Private Methods
/// ========================================

- (void)_handleButtonAction:(UIButton *)button {
    if (self.shareDelegate && [self.shareDelegate respondsToSelector:@selector(scrollView:didSelelctedIndex:title:)]) {
        [self.shareDelegate scrollView:self didSelelctedIndex:button.tag title:[button titleForState:UIControlStateNormal]];
    }
}

- (UIView *)_itemWithFrame:(CGRect)frame itemInfo:(NSDictionary *)itemInfo tag:(NSUInteger)tag{
    NSString *image = itemInfo[kXMNShareImage];
    NSString *highlightedImage = itemInfo[kXMNShareHighlightImage];
    NSString *title = [itemInfo[kXMNShareTitle] length] > 0 ? itemInfo[kXMNShareTitle] : @"";
    UIImage *icoImage = [UIImage imageNamed:image];
    UIView *view = [[UIView alloc] initWithFrame:frame];
    view.backgroundColor = [UIColor clearColor];
    
    UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
    button.frame = CGRectMake((view.frame.size.width-icoImage.size.width)/2, 0, icoImage.size.width, icoImage.size.height);
    button.titleLabel.font = [UIFont systemFontOfSize:kXMNTitleFontSize];
    [button setTitle:title forState:UIControlStateNormal];
    [button setTitleColor:[UIColor clearColor] forState:UIControlStateNormal];
    if (image.length > 0) {
        [button setImage:[UIImage imageNamed:image] forState:UIControlStateNormal];
    }
    if (highlightedImage.length > 0) {
        [button setImage:[UIImage imageNamed:highlightedImage] forState:UIControlStateHighlighted];
    }
    button.tag = tag;
    [button addTarget:self action:@selector(_handleButtonAction:) forControlEvents:UIControlEventTouchUpInside];
    [view addSubview:button];
    
    UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake(0, button.frame.origin.y +button.frame.size.height+ kXMNTitleSpace, view.frame.size.width, kXMNTitleFontSize)];
    label.textColor = kXMNTitleColor;
    label.textAlignment = NSTextAlignmentCenter;
    label.backgroundColor = [UIColor clearColor];
    label.font = [UIFont systemFontOfSize:kXMNTitleFontSize];
    label.text = title;
    [view addSubview:label];
    
    return view;
}

/// ========================================
/// @name   Class Methods
/// ========================================

+ (CGFloat)heightForScrollView {
    CGFloat height = KXMNOriginY+kXMNItemWidth+kXMNTitleSpace+kXMNTitleFontSize+KXMNOriginY;
    return height;
}
@end
