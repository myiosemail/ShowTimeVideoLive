//
//  LiveViewController.h
//  ShowTime
//
//  Created by YJ on 16/6/16.
//  Copyright © 2016年 YJ. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LiveVideoCoreSDK.h"
#import "ASValueTrackingSlider.h"

@interface LiveViewController : UIViewController<LIVEVCSessionDelegate, ASValueTrackingSliderDataSource, ASValueTrackingSliderDelegate>
@property (nonatomic, copy) NSURL* RtmpUrl;
@property (nonatomic, assign) Boolean IsHorizontal;

- (void) LiveConnectionStatusChanged: (LIVE_VCSessionState) sessionState;
@end
