//
//  LiveVideoCoreSDK.m
//  LiveVideoCoreSDK
//
//  Created by Alex.Shi on 16/3/2.
//  Copyright © 2016年 com.Alex. All rights reserved.
//

#import "LiveVideoCoreSDK.h"

@implementation LiveVideoCoreSDK
{
    VCSimpleSession   *_livesession;
    NSURL* _rtmpUrl;
    NSString* _Dest;
    NSString* _LiveName;
    UIView* _ShowPreview;
    float _micGain;
}

@dynamic micGain;

+ (instancetype)sharedinstance {
    static LiveVideoCoreSDK *s_instance;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        s_instance = [[self alloc] init];
    });
    
    return s_instance;
}

- (void)LiveInit:(NSURL*)rtmpUrl Preview:(UIView*)previewView{
    if (self) {
        _livesession = [[VCSimpleSession alloc] initWithVideoSize:CGSizeMake(LIVE_VIDEO_DEF_WIDTH, LIVE_VIDEO_DEF_HEIGHT) frameRate:LIVE_VIDEO_DEF_FRAMERATE bitrate:LIVE_VIDEO_DEF_BITRATE useInterfaceOrientation:YES];
        
        _livesession.delegate = self;
        
        _rtmpUrl = rtmpUrl;
        
        NSString *strRtmp = rtmpUrl.scheme;
        
        if (![strRtmp isEqualToString:@"rtmp"]) {
            NSLog(@"LiveInit: error rtmp url=%@", rtmpUrl.absoluteString);
            return;
        }
        
        NSString *strRtmpUrl = rtmpUrl.absoluteString;
        NSArray *components = [strRtmpUrl componentsSeparatedByString:@"/"];
        [components enumerateObjectsUsingBlock:^(NSString *str, NSUInteger idx, BOOL *stop) {
            NSString *host = components[0];
            for (NSUInteger i = 1; i <= idx; i++) {
                host = [host stringByAppendingString:[NSString stringWithFormat:@"/%@", components[i]]];
            }
            _Dest = host;
            
            NSString *name = components[idx + 1];
            for (NSUInteger i = idx + 2; i < components.count; i++) {
                name = [name stringByAppendingString:[NSString stringWithFormat:@"/%@", components[i]]];
            }
            _LiveName = name;
            
            *stop = YES;
        }];
        
        _ShowPreview = previewView;
        [previewView addSubview:_livesession.previewView];
        _livesession.previewView.frame = previewView.bounds;
        
        NSLog(@"rtmpUrl=%@, destination=%@, livename=%@",
              rtmpUrl.absoluteString, _Dest, _LiveName);
    }
    
    return;
}

- (void)LiveInit:(NSURL*)rtmpUrl Preview:(UIView*)previewView VideSize:(CGSize)videSize BitRate:(LIVE_BITRATE)iBitRate FrameRate:(LIVE_FRAMERATE)iFrameRate{
    if (self) {
        _livesession = [[VCSimpleSession alloc] initWithVideoSize:videSize frameRate:iFrameRate bitrate:iBitRate useInterfaceOrientation:YES];
        
        _livesession.delegate = self;
        
        _rtmpUrl = rtmpUrl;
        
        NSString *strRtmp = rtmpUrl.scheme;
        
        if (![strRtmp isEqualToString:@"rtmp"]) {
            NSLog(@"LiveInit: error rtmp url=%@", rtmpUrl.absoluteString);
            return;
        }
        
        NSString *strRtmpUrl = rtmpUrl.absoluteString;
        NSArray *components = [strRtmpUrl componentsSeparatedByString:@"/"];
        [components enumerateObjectsUsingBlock:^(NSString *str, NSUInteger idx, BOOL *stop) {
            NSString *host = components[0];
            for (NSUInteger i = 1; i <= idx + 3; i++) {
                host = [host stringByAppendingString:[NSString stringWithFormat:@"/%@", components[i]]];
            }
            _Dest = host;
            
            NSString *name = components[idx + 4];
            for (NSUInteger i = idx + 5; i < components.count; i++) {
                name = [name stringByAppendingString:[NSString stringWithFormat:@"/%@", components[i]]];
            }
            _LiveName = name;
            
            *stop = YES;
        }];
        
        _ShowPreview = previewView;
        [previewView addSubview:_livesession.previewView];
        _livesession.previewView.frame = previewView.bounds;
        
        NSLog(@"rtmpUrl=%@, destination=%@, livename=%@\r\nwidth=%.2f, height=%.2f, bitRate=%lu, frameRate=%lu",
              rtmpUrl.absoluteString, _Dest, _LiveName,
              videSize.width, videSize.height, (unsigned long)iBitRate, (unsigned long)iFrameRate);
        
    }
    
    return;
}

- (void)LiveRelease{
    _livesession = nil;
    NSLog(@"LiveRelease: %@", _rtmpUrl);
}

- (void)connect {
    NSLog(@"connect: %@", _rtmpUrl);
    [_livesession startRtmpSessionWithURL:_Dest andStreamKey:_LiveName];
}

- (void)disconnect {
    NSLog(@"disconnect: %@", _rtmpUrl);
    [_livesession endRtmpSession];
}

- (void)setFilter:(LIVE_FILTER_TYPE) type{
    switch (type) {
        case LIVE_FILTER_ORIGINAL:
            [_livesession setFilter:VCFilterNormal];
            break;
        case LIVE_FILTER_BEAUTY:
            [_livesession setFilter:VCFilterBeauty];
            break;
        case LIVE_FILTER_ANTIQUE:
            [_livesession setFilter:VCFilterSepia];
            break;
        case LIVE_FILTER_BLACK:
            [_livesession setFilter:VCFilterGray];
            break;
        default:
            break;
    }
}

-(void) setMicGain:(float)micGain{
    _livesession.micGain = micGain;
}

-(float) micGain{
    return _livesession.micGain;
}

- (void)focuxAtPoint:(CGPoint)point
{
    _livesession.focusPointOfInterest = point;
    _livesession.exposurePointOfInterest = point;
}

//delegate operation
- (void) connectionStatusChanged: (VCSessionState) sessionState{
    NSLog(@"rtmp live state: %i", sessionState);
    LIVE_VCSessionState state = (LIVE_VCSessionState)sessionState;
    
    [self.delegate LiveConnectionStatusChanged:state];
    
    return;
}

- (void)setCameraFront:(Boolean)bCameraFrontFlag {
    if (!bCameraFrontFlag) {
        _livesession.cameraState = VCCameraStateBack;
        //_ShowPreview.transform = CGAffineTransformMakeScale(1.0, 1.0);
    } else {
        _livesession.cameraState = VCCameraStateFront;
        //_ShowPreview.transform = CGAffineTransformMakeScale(-1.0, 1.0);
    }
}

@end
