//
//  XMNshareContentView.m
//  XMNShareMenuExample
//
//  Created by XMFraker on 16/1/25.
//  Copyright © 2016年 XMFraker. All rights reserved.
//

#import "XMNShareView.h"
#import "XMNShareScrollView.h"

@interface XMNShareView () <XMNShareScrollViewDelegate>


/**
 *  显示所有内容的view
 */
@property (nonatomic, strong) UIView *shareContentView;

/**
 *  显示shareItemView的
 */
@property (nonatomic, strong) UIView *itemsContentView;

/**
 *  shareScrollView多行时显示的分割线, 默认不显示,多行时显示
 */
@property (nonatomic, strong) UIView *lineView;


/**
 *  取消按钮,位于shareContentView最底部 默认显示
 */
@property (nonatomic, strong) UIButton *cancelButton;


@end

@implementation XMNShareView

#pragma mark - Life Cycle

- (instancetype)init {
    if (self = [super init]) {
        self.backgroundColor = [UIColor colorWithRed:.0f green:.0f blue:.0f alpha:.5f];
        [self _setup];
        
    }
    return self;
}

#pragma mark - XMNShareScrollViewDelegate

- (void)scrollView:(XMNShareScrollView *)shareScrollView didSelelctedIndex:(NSUInteger)index title:(NSString *)title  {
    self.selectedBlock ? self.selectedBlock(shareScrollView.tag * self.itemsPerLine + index,title) : nil;
}


#pragma mark - Methods

/// ========================================
/// @name   Public Methods
/// ========================================

- (void)showUseAnimated:(BOOL)animated {
    [[[UIApplication sharedApplication] keyWindow] addSubview:self];
    [self _updateshareContentViewFrame:YES];
    if (!animated) {
        self.alpha = 1.0f;
        [self.shareContentView setFrame:CGRectMake(0, self.frame.size.height - CGRectGetHeight(self.shareContentView.bounds), CGRectGetWidth(self.shareContentView.bounds), CGRectGetHeight(self.shareContentView.bounds))];
        return;
    }
    [UIView animateWithDuration:.3 animations:^{
        [self.shareContentView setFrame:CGRectMake(0, self.frame.size.height - CGRectGetHeight(self.shareContentView.bounds), CGRectGetWidth(self.shareContentView.bounds), CGRectGetHeight(self.shareContentView.bounds))];
        self.alpha = 1.0f;
    }];
}

- (void)dismissUseAnimated:(BOOL)animated {
    [self _updateshareContentViewFrame:NO];
    if (!animated) {
        [self removeFromSuperview];
        return;
    }
    [UIView animateWithDuration:.3 animations:^{
        self.alpha = .0f;
        [self.shareContentView setFrame:CGRectMake(0, self.frame.size.height, CGRectGetWidth(self.shareContentView.bounds), CGRectGetHeight(self.shareContentView.bounds))];
    } completion:^(BOOL finished) {
        [self removeFromSuperview];
    }];
}

- (void)setupShareViewWithItems:(NSArray *)items {
    
    if (self.itemsPerLine > items.count || self.itemsPerLine == 0) {
        self.itemsPerLine = items.count;
    }
    NSArray *firstLineArray = [items subarrayWithRange:NSMakeRange(0,self.itemsPerLine)];
    NSArray *secondLineArray = [items subarrayWithRange:NSMakeRange(self.itemsPerLine,items.count-self.itemsPerLine)];
    
    XMNShareScrollView *shareScrollView = [[XMNShareScrollView alloc] initWithFrame:CGRectMake(0, 0, self.frame.size.width, [XMNShareScrollView heightForScrollView])];
    shareScrollView.shareDelegate = self;
    [shareScrollView setupShareScrollViewWithItems:firstLineArray];
    shareScrollView.showsHorizontalScrollIndicator = NO;
    [self.itemsContentView addSubview:shareScrollView];
    
    if (self.itemsPerLine < items.count) {
        //分割线
        self.lineView.frame = CGRectMake(0, shareScrollView.frame.size.height + shareScrollView.frame.origin.y, self.frame.size.width, .5f);
        
        shareScrollView = [[XMNShareScrollView alloc] initWithFrame:CGRectMake(0, self.lineView.frame.origin.y+self.lineView.frame.size.height, self.frame.size.width, [XMNShareScrollView heightForScrollView])];
        shareScrollView.shareDelegate = self;
        shareScrollView.tag = 1;
        [shareScrollView setupShareScrollViewWithItems:secondLineArray];
        shareScrollView.showsHorizontalScrollIndicator = NO;
        [self.itemsContentView addSubview:shareScrollView];
    }
    self.itemsContentView.bounds = CGRectMake(0, 0, self.frame.size.width, self.itemsPerLine < items.count ? [XMNShareScrollView heightForScrollView]*2 + 1 : [XMNShareScrollView heightForScrollView]);
}

/// ========================================
/// @name   Private Methods
/// ========================================

- (void)_setup {
    
    self.alpha = 0.f;
    self.userInteractionEnabled = YES;
    UITapGestureRecognizer *tapGes = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(_handleCancelAction)];
    [self addGestureRecognizer:tapGes];
    
    self.frame = CGRectMake(0, 0, CGRectGetWidth([UIScreen mainScreen].bounds), CGRectGetHeight([UIScreen mainScreen].bounds));
    
    self.itemsPerLine = 9;
    
    [self addSubview:self.shareContentView];
    [self.shareContentView addSubview:self.itemsContentView];
    [self.shareContentView addSubview:self.cancelButton];
    
}

- (void)_handleCancelAction {
    [self dismissUseAnimated:YES];
}

- (void)_updateshareContentViewFrame:(BOOL)hidden {
    CGFloat height = 0;
    if (self.headerView) {
        self.headerView.frame = CGRectMake(0, 0, CGRectGetWidth(self.bounds), CGRectGetHeight(self.headerView.frame));
        height += CGRectGetHeight(self.headerView.bounds);
    }
    self.itemsContentView.frame = CGRectMake(0, height, CGRectGetWidth(self.bounds), CGRectGetHeight(self.itemsContentView.bounds));
    height += CGRectGetHeight(self.itemsContentView.bounds);
    
    if (self.footerView) {
        self.footerView.frame = CGRectMake(0, height, CGRectGetWidth(self.bounds), CGRectGetHeight(self.footerView.bounds));
        height += CGRectGetHeight(self.footerView.bounds);
    }
    
    self.cancelButton.frame = CGRectMake(0, height, CGRectGetWidth(self.bounds), CGRectGetHeight(self.cancelButton.bounds));
    height += CGRectGetHeight(self.cancelButton.bounds);
    
    self.shareContentView.frame = CGRectMake(0, hidden ? self.frame.size.height : self.frame.size.height - height, CGRectGetWidth(self.bounds), height);
}

#pragma mark - Setters

- (void)setHeaderView:(UIView *)headerView {
    [_headerView removeFromSuperview];
    _headerView = nil;
    headerView ? [self.shareContentView addSubview:_headerView = headerView] : nil;
}


- (void)setFooterView:(UIView *)footerView {
    [_footerView removeFromSuperview];
    _footerView = nil;
    footerView ? [self.shareContentView addSubview:_footerView = footerView] : nil;
}

#pragma mark - Getters

- (UIView *)shareContentView {
    if (!_shareContentView) {
        _shareContentView = [[UIView alloc] init];
        _shareContentView.backgroundColor = [UIColor colorWithRed:234/255.0f green:234/255.0f blue:234/255.0f alpha:1.0f];
        _shareContentView.userInteractionEnabled = YES;
    }
    return _shareContentView;
}

- (UIView *)itemsContentView {
    if (!_itemsContentView) {
        _itemsContentView = [[UIView alloc] init];
        [_itemsContentView addSubview:self.lineView];
    }
    return _itemsContentView;
}

- (UIButton *)cancelButton {
    if (!_cancelButton) {
        _cancelButton = [UIButton buttonWithType:UIButtonTypeCustom];
        _cancelButton.frame = CGRectMake(0, 0, self.frame.size.width, 50);
        _cancelButton.titleLabel.font = [UIFont systemFontOfSize:16];
        [_cancelButton setTitle:@"取消" forState:UIControlStateNormal];
        [_cancelButton setTitleColor:[UIColor colorWithRed:51/255.0 green:51/255.0 blue:51/255.0 alpha:1.0] forState:UIControlStateNormal];
        [_cancelButton setBackgroundImage:[self imageWithColor:[UIColor whiteColor] size:CGSizeMake(1.0, 1.0)] forState:UIControlStateNormal];
        [_cancelButton setBackgroundImage:[self imageWithColor:[UIColor colorWithRed:234/255.0 green:234/255.0 blue:234/255.0 alpha:1.0] size:CGSizeMake(1.0, 1.0)] forState:UIControlStateHighlighted];
        [_cancelButton addTarget:self action:@selector(_handleCancelAction) forControlEvents:UIControlEventTouchUpInside];
    }
    return _cancelButton;
}

- (UIView *)lineView {
    if (!_lineView) {
        _lineView = [[UIView alloc] init];
        _lineView.backgroundColor = [UIColor colorWithRed:212/255.0f green:212/255.0f blue:212/255.0f alpha:1.0f];
    }
    return _lineView;
}

//颜色生成图片方法
- (UIImage *)imageWithColor:(UIColor *)color size:(CGSize)size {
    CGRect rect = CGRectMake(0, 0, size.width, size.height);
    UIGraphicsBeginImageContext(rect.size);
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSetFillColorWithColor(context,
                                   color.CGColor);
    CGContextFillRect(context, rect);
    UIImage *img = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return img;
}

@end
