//
//  HomeTableViewCell.m
//  ShowTime
//
//  Created by YJ on 16/6/22.
//  Copyright © 2016年 YJ. All rights reserved.
//

#import "HomeTableViewCell.h"
#import "ListModel.h"
#import "UIImageView+WebCache.h"
#import "MJExtension.h"
@implementation HomeTableViewCell

- (void)awakeFromNib {
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}
-(void)setListModel:(ListModel *)listModel
{
    _listModel=listModel;
    [self.headImgView sd_setImageWithURL:[NSURL URLWithString:[NSString stringWithFormat:@"http://img.meelive.cn/%@",listModel.creator[@"portrait"]]] placeholderImage:nil] ;
     [self.ShowImgView sd_setImageWithURL:[NSURL URLWithString:[NSString stringWithFormat:@"http://img.meelive.cn/%@",listModel.creator[@"portrait"]]] placeholderImage:nil] ;
    self.nickNameLabel.text=listModel.creator[@"nick"];
    NSString * str=[NSString stringWithFormat:@"%@ 在看",listModel.online_users];
    NSMutableAttributedString * attribute=[[NSMutableAttributedString alloc]initWithString:str];
    [attribute addAttributes:@{NSFontAttributeName:[UIFont systemFontOfSize:16],NSForegroundColorAttributeName:[UIColor orangeColor] } range:NSMakeRange(0, attribute.length-2)];
    [attribute addAttributes:@{NSFontAttributeName:[UIFont systemFontOfSize:12],NSForegroundColorAttributeName:[UIColor blackColor] } range:NSMakeRange(attribute.length-2, 2)];
    self.onlineLabel.attributedText=attribute;
    if (![listModel.creator[@"location"]isEqualToString:@""]) {
        self.locationLabel.text=listModel.creator[@"location"];
    }else{
        self.locationLabel.text=@"难道在火星?";
    }
}
@end
