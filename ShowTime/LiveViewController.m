//
//  LiveViewController.m
//  ShowTime
//
//  Created by YJ on 16/6/16.
//  Copyright © 2016年 YJ. All rights reserved.
//

#import "LiveViewController.h"
#import "LiveVideoCoreSDK.h"
#import "XMNShareMenu.h"
#import "ASValueTrackingSlider.h"
#import "HomeViewController.h"
#define RtmpUrl @"rtmp://daniulive.com:1935/hls/stream727908"//这是大牛Live的服务器推流地址,其中727908为1000000以内的随机数字,可修改,在这也感谢大牛Live的大力支持,服务器仅供测试使用,实际项目中用自己搭建的推流服务器或者第三方的服务器
@interface LiveViewController ()<LIVEVCSessionDelegate,ASValueTrackingSliderDelegate,ASValueTrackingSliderDataSource>
@end

@implementation LiveViewController
{
    UIView* _AllBackGroudView;
    UIButton* _ExitButton;
    UILabel*  _RtmpStatusLabel;
    UIButton* _FilterButton;
    UIButton* _CameraChangeButton;
    XMNShareView* _FilterMenu;
    ASValueTrackingSlider* _MicSlider;
    Boolean _bCameraFrontFlag;
    UIView *_focusBox;
    
}
-(void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    self.navigationController.navigationBarHidden=NO;
    self.tabBarController.tabBar.hidden=NO;
}
-(void) UIInit{
    double fScreenW = [UIScreen mainScreen].bounds.size.width;
    double fScreenH = [UIScreen mainScreen].bounds.size.height;
    if (self.IsHorizontal) {
        double fTmp = fScreenH;
        fScreenH = fScreenW;
        fScreenW = fTmp;
    }
    
    _AllBackGroudView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, fScreenW, fScreenH)];
    [self.view addSubview:_AllBackGroudView];
    
    float fExitButtonW = 40;
    float fExitButtonH = 20;
    float fExitButtonX = fScreenW - fExitButtonW - 10;
    float fExitButtonY = fScreenH - fExitButtonH - 10;
    _ExitButton = [[UIButton alloc] initWithFrame:CGRectMake(fExitButtonX, fExitButtonY, fExitButtonW, fExitButtonH)];
    _ExitButton.backgroundColor = [UIColor blueColor];
    _ExitButton.layer.masksToBounds = YES;
    _ExitButton.layer.cornerRadius  = 5;
    [_ExitButton setTitle:@"退出" forState:UIControlStateNormal];
    [_ExitButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    _ExitButton.titleLabel.font = [UIFont fontWithName:@"Helvetica-Bold" size:10];
    [_ExitButton addTarget:self action:@selector(OnExitClicked:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:_ExitButton];
    
    float fRtmpStatusLabelW = 120;
    float fRtmpStatusLabelH = 20;
    float fRtmpStatusLabelX = 10;
    float fRtmpStatusLabelY = 30;
    _RtmpStatusLabel = [[UILabel alloc] initWithFrame:CGRectMake(fRtmpStatusLabelX, fRtmpStatusLabelY, fRtmpStatusLabelW, fRtmpStatusLabelH)];
    _RtmpStatusLabel.backgroundColor = [UIColor lightGrayColor];
    _RtmpStatusLabel.layer.masksToBounds = YES;
    _RtmpStatusLabel.layer.cornerRadius  = 5;
    _RtmpStatusLabel.font = [UIFont fontWithName:@"Helvetica-Bold" size:10];
    [_RtmpStatusLabel setTextColor:[UIColor whiteColor]];
    _RtmpStatusLabel.text = @"RTMP状态: 未连接";
    [self.view addSubview:_RtmpStatusLabel];
    
    float fFilterButtonW = 50;
    float fFilterButtonH = 30;
    float fFilterButtonX = fScreenW/2-fFilterButtonW-5;
    float fFilterButtonY = fScreenH - fFilterButtonH - 10;
    _FilterButton = [[UIButton alloc] initWithFrame:CGRectMake(fFilterButtonX, fFilterButtonY, fFilterButtonW, fFilterButtonH)];
    _FilterButton.backgroundColor = [UIColor blueColor];
    _FilterButton.layer.masksToBounds = YES;
    _FilterButton.layer.cornerRadius  = 5;
    [_FilterButton setTitle:@"滤镜" forState:UIControlStateNormal];
    [_FilterButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    _FilterButton.titleLabel.font = [UIFont fontWithName:@"Helvetica-Bold" size:12];
    [_FilterButton addTarget:self action:@selector(OnFilterClicked:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:_FilterButton];
    
    float fCameraChangeButtonW = fFilterButtonW;
    float fCameraChangeButtonH = fFilterButtonH;
    float fCameraChangeButtonX = fScreenW/2+5;
    float fCameraChangeButtonY = fFilterButtonY;
    
    _CameraChangeButton = [[UIButton alloc] initWithFrame:CGRectMake(fCameraChangeButtonX, fCameraChangeButtonY, fCameraChangeButtonW, fCameraChangeButtonH)];
    _CameraChangeButton.backgroundColor = [UIColor blueColor];
    _CameraChangeButton.layer.masksToBounds = YES;
    _CameraChangeButton.layer.cornerRadius  = 5;
    [_CameraChangeButton setTitle:@"后置镜头" forState:UIControlStateNormal];
    [_CameraChangeButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    _CameraChangeButton.titleLabel.font = [UIFont fontWithName:@"Helvetica-Bold" size:11];
    [_CameraChangeButton addTarget:self action:@selector(OnCameraChangeClicked:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:_CameraChangeButton];
    
    float fMicSliderX = 20;
    float fMicSliderY = fCameraChangeButtonY - fCameraChangeButtonH - 10;
    float fMicSliderW = fScreenW - fMicSliderX*2;
    float fMicSliderH = 30;
    _MicSlider = [[ASValueTrackingSlider alloc] initWithFrame:CGRectMake(fMicSliderX, fMicSliderY, fMicSliderW, fMicSliderH)];
    _MicSlider.maximumValue = 10.0;
    _MicSlider.popUpViewCornerRadius = 4;
    [_MicSlider setMaxFractionDigitsDisplayed:0];
    _MicSlider.popUpViewColor = [UIColor colorWithHue:0.55 saturation:0.8 brightness:0.9 alpha:0.7];
    _MicSlider.font = [UIFont fontWithName:@"GillSans-Bold" size:18];
    _MicSlider.textColor = [UIColor colorWithHue:0.55 saturation:1.0 brightness:0.5 alpha:1];
    _MicSlider.popUpViewWidthPaddingFactor = 1.7;
    _MicSlider.delegate = self;
    _MicSlider.dataSource = self;
    _MicSlider.value = 5;
    [self.view addSubview:_MicSlider];
    
    UITapGestureRecognizer *singleTap = [[UITapGestureRecognizer alloc]initWithTarget:self action:@selector(dealSingleTap:)];
    [self.view addGestureRecognizer:singleTap];
    
    _focusBox = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 150, 150)];
    _focusBox.backgroundColor = [UIColor clearColor];
    _focusBox.layer.borderColor = [UIColor greenColor].CGColor;
    _focusBox.layer.borderWidth = 5.0f;
    _focusBox.hidden = YES;
    [self.view addSubview:_focusBox];
}

-(void) RtmpInit{
    dispatch_async(dispatch_get_main_queue(), ^{
        CGSize videosize;
        
        if (self.IsHorizontal) {
            videosize = LIVE_VIEDO_SIZE_HORIZONTAL_D1;
        }else{
            videosize = LIVE_VIEDO_SIZE_D1;
        }
        [[LiveVideoCoreSDK sharedinstance] LiveInit:[NSURL URLWithString:RtmpUrl] Preview:_AllBackGroudView VideSize:videosize BitRate:LIVE_BITRATE_800Kbps FrameRate:LIVE_FRAMERATE_20];
        [LiveVideoCoreSDK sharedinstance].delegate = self;
        [[LiveVideoCoreSDK sharedinstance] connect];
        NSLog(@"Rtmp[%@] is connecting", RtmpUrl);
        
        [LiveVideoCoreSDK sharedinstance].micGain = 5;
        
        [self.view addSubview:_MicSlider];
        [self.view addSubview:_ExitButton];
        [self.view addSubview:_RtmpStatusLabel];
        [self.view addSubview:_FilterButton];
        [self.view addSubview:_CameraChangeButton];
    });
}

-(void) OnCameraChangeClicked:(id)sender{
    _bCameraFrontFlag = !_bCameraFrontFlag;
    [[LiveVideoCoreSDK sharedinstance] setCameraFront:_bCameraFrontFlag];
    if (_bCameraFrontFlag) {
        [_CameraChangeButton setTitle:@"前置镜头" forState:UIControlStateNormal];
    }else{
        [_CameraChangeButton setTitle:@"后置镜头" forState:UIControlStateNormal];
    }
}

-(void) OnFilterClicked:(id)sender{
    NSArray *shareAry = @[@{kXMNShareImage:@"original_Image",
                            kXMNShareHighlightImage:@"original_Image",
                            kXMNShareTitle:@"原始"},
                          @{kXMNShareImage:@"beauty_Image",
                            kXMNShareHighlightImage:@"beauty_Image",
                            kXMNShareTitle:@"美颜"},
                          @{kXMNShareImage:@"fugu_Image",
                            kXMNShareHighlightImage:@"fugu_Image",
                            kXMNShareTitle:@"复古"},
                          @{kXMNShareImage:@"black_Image",
                            kXMNShareHighlightImage:@"fugu_Image",
                            kXMNShareTitle:@"黑白"},];
    //自定义头部
    UIView *headerView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, self.view.bounds.size.width, 36)];
    headerView.backgroundColor = [UIColor clearColor];
    
    UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake(16, 21, headerView.frame.size.width-32, 15)];
    label.textColor = [UIColor colorWithRed:94/255.0 green:94/255.0 blue:94/255.0 alpha:1.0];;
    label.backgroundColor = [UIColor clearColor];
    label.font = [UIFont systemFontOfSize:15];
    label.text = @"滤镜:";
    [headerView addSubview:label];
    
    _FilterMenu = [[XMNShareView alloc] init];
    //设置头部View 如果不设置则不显示头部
    _FilterMenu.headerView = headerView;
    [_FilterMenu setSelectedBlock:^(NSUInteger tag, NSString *title) {
        NSLog(@"\ntag :%lu  \ntitle :%@",(unsigned long)tag,title);
        
        switch(tag) {
            case 0://原图像
                NSLog(@"设置无滤镜...");
                [[LiveVideoCoreSDK sharedinstance] setFilter:LIVE_FILTER_ORIGINAL];
                break;
            case 1://美颜
                NSLog(@"设置美艳滤镜...");
                [[LiveVideoCoreSDK sharedinstance] setFilter:LIVE_FILTER_BEAUTY];
                break;
            case 2://复古
                NSLog(@"设置复古滤镜...");
                [[LiveVideoCoreSDK sharedinstance] setFilter:LIVE_FILTER_ANTIQUE];
                break;
            case 3://黑白
                NSLog(@"设置黑白滤镜...");
                [[LiveVideoCoreSDK sharedinstance] setFilter:LIVE_FILTER_BLACK];
                break;
            default:
                break;
        }
    }];
    
    //计算高度 根据第一行显示的数量和总数,可以确定显示一行还是两行,最多显示2行
    [_FilterMenu setupShareViewWithItems:shareAry];
    
    [_FilterMenu showUseAnimated:YES];
}

-(void) OnExitClicked:(id)sender{
    [[LiveVideoCoreSDK sharedinstance] disconnect];
    [[LiveVideoCoreSDK sharedinstance] LiveRelease];
    self.navigationController.tabBarController.selectedIndex=0;
}

- (BOOL) shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation {
    if(self.IsHorizontal){
        bool bRet = ((toInterfaceOrientation == UIInterfaceOrientationLandscapeRight) || (toInterfaceOrientation == UIInterfaceOrientationLandscapeLeft));
        return bRet;
    }else{
        return false;
    }
}
- (UIInterfaceOrientationMask)supportedInterfaceOrientations {
    if(self.IsHorizontal){
        return UIInterfaceOrientationMaskLandscapeRight|UIInterfaceOrientationMaskLandscapeLeft;
    }else{
        return UIInterfaceOrientationMaskPortrait;
    }
}
- (void) viewWillAppear:(BOOL)animated{
    
    [self.view.subviews makeObjectsPerformSelector:@selector(removeFromSuperview)];
    NSLog(@"CameraViewController: viewWillAppear");
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(WillResignActiveNotification) name:UIApplicationWillResignActiveNotification object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(WillDidBecomeActiveNotification) name:UIApplicationDidBecomeActiveNotification object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appWillEnterForegroundNotification) name:UIApplicationDidBecomeActiveNotification object:nil];
    
    [super viewDidAppear:YES];
    self.navigationController.navigationBarHidden=YES;
    self.tabBarController.tabBar.hidden=YES;
    
    [self UIInit];
    
    [self RtmpInit];
    
    _bCameraFrontFlag = false;
}
- (void) appWillEnterForegroundNotification{
    NSLog(@"trigger event when will enter foreground.");
    if (![self hasPermissionOfCamera]) {
        return;
    }
    [self RtmpInit];
    
}
- (void)WillDidBecomeActiveNotification{
    NSLog(@"CameraViewController: WillDidBecomeActiveNotification");
    
}

- (void)WillResignActiveNotification{
    NSLog(@"LiveShowViewController: WillResignActiveNotification");
    
    if (![self hasPermissionOfCamera]) {
        return;
    }
    //得到当前应用程序的UIApplication对象
    UIApplication *app = [UIApplication sharedApplication];
    
    //一个后台任务标识符
    UIBackgroundTaskIdentifier taskID;
    taskID = [app beginBackgroundTaskWithExpirationHandler:^{
        //如果系统觉得我们还是运行了太久，将执行这个程序块，并停止运行应用程序
        [app endBackgroundTask:taskID];
    }];
    //UIBackgroundTaskInvalid表示系统没有为我们提供额外的时候
    if (taskID == UIBackgroundTaskInvalid) {
        NSLog(@"Failed to start background task!");
        return;
    }
    
    //[[SCCaptureManager sharedManager] disconnect];
    [[LiveVideoCoreSDK sharedinstance] disconnect];
    [[LiveVideoCoreSDK sharedinstance] LiveRelease];
    
    //告诉系统我们完成了
    [app endBackgroundTask:taskID];
}
- (BOOL)hasPermissionOfCamera
{
    NSString *mediaType = AVMediaTypeVideo;
    AVAuthorizationStatus authStatus = [AVCaptureDevice authorizationStatusForMediaType:mediaType];
    if(authStatus != AVAuthorizationStatusAuthorized){
        
        NSLog(@"相机权限受限");
        return NO;
    }
    return YES;
}
-(void) viewDidDisappear:(BOOL)animated{
    NSLog(@"CameraViewController: viewDidDisappear");
    [[NSNotificationCenter defaultCenter] removeObserver:self name:UIApplicationWillResignActiveNotification object:nil];//删除去激活界面的回调
    [[NSNotificationCenter defaultCenter] removeObserver:self name:UIApplicationDidBecomeActiveNotification object:nil];//删除激活界面的回调
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

//rtmp status delegate:
- (void) LiveConnectionStatusChanged: (LIVE_VCSessionState) sessionState{
    dispatch_async(dispatch_get_main_queue(), ^{
        switch (sessionState) {
            case LIVE_VCSessionStatePreviewStarted:
                _RtmpStatusLabel.text = @"RTMP状态: 预览未连接";
                break;
            case LIVE_VCSessionStateStarting:
                _RtmpStatusLabel.text = @"RTMP状态: 连接中...";
                break;
            case LIVE_VCSessionStateStarted:
                _RtmpStatusLabel.text = @"RTMP状态: 已连接";
                break;
            case LIVE_VCSessionStateEnded:
                _RtmpStatusLabel.text = @"RTMP状态: 未连接";
                break;
            case LIVE_VCSessionStateError:
                _RtmpStatusLabel.text = @"RTMP状态: 错误";
                break;
            default:
                break;
        }
    });
}

- (NSString *)slider:(ASValueTrackingSlider *)slider stringForValue:(float)value{
    if (slider == _MicSlider) {
        float fMicGain = value/10.0;
        NSLog(@"mic slider:%0.2f, %0.2f", value, fMicGain);
        [LiveVideoCoreSDK sharedinstance].micGain = fMicGain;
    }
    
    return nil;
}

- (void)sliderWillDisplayPopUpView:(ASValueTrackingSlider *)slider{
    NSLog(@"sliderWillDisplayPopUpView...");
    return;
}

- (void)sliderWillHidePopUpView:(ASValueTrackingSlider *)slider{
    NSLog(@"sliderWillHidePopUpView...");
}

- (void)dealSingleTap:(UITapGestureRecognizer *)tap
{
    CGPoint point = [tap locationInView:self.view];
    [[LiveVideoCoreSDK sharedinstance] focuxAtPoint:point];
    [self runBoxAnimationOnView:_focusBox point:point];
}
//对焦的动画效果
- (void)runBoxAnimationOnView:(UIView *)view point:(CGPoint)point {
    view.center = point;
    view.hidden = NO;
    [UIView animateWithDuration:0.2f
                          delay:0.0f
                        options:UIViewAnimationOptionCurveEaseInOut
                     animations:^{
                         view.layer.transform = CATransform3DMakeScale(0.5, 0.5, 1.0);
                     }
                     completion:^(BOOL complete) {
                         double delayInSeconds = 0.5f;
                         dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
                         dispatch_after(popTime, dispatch_get_main_queue(), ^(void){
                             view.hidden = YES;
                             view.transform = CGAffineTransformIdentity;
                         });
                     }];
}
@end
