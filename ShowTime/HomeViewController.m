//
//  HomeViewController.m
//  ShowTime
//
//  Created by YJ on 16/6/16.
//  Copyright © 2016年 YJ. All rights reserved.
//

#import "HomeViewController.h"
#import "HttpRequestTool.h"
#import "ListModel.h"
#import "ShowLivingViewController.h"
#import "HomeTableViewCell.h"
#import "Foundation+Log.m"
#import "MJRefresh.h"
@interface HomeViewController ()
/** 数据源 */
@property(nonatomic,strong)NSArray * datas;
@end

@implementation HomeViewController
- (NSArray *)datas
{
    if (!_datas) {
        _datas=[NSArray array];
    }
    return _datas;
}
- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor=[UIColor whiteColor];
    [self.tableView registerNib:[UINib nibWithNibName:NSStringFromClass([HomeTableViewCell class]) bundle:nil] forCellReuseIdentifier:NSStringFromClass([HomeTableViewCell class])];
    MJRefreshNormalHeader *mj_header = [MJRefreshNormalHeader headerWithRefreshingTarget:self refreshingAction:@selector(loadData)];
    mj_header.lastUpdatedTimeLabel.hidden=YES;
    self.tableView.mj_header = mj_header;
    [self loadData];
    
}
-(void)loadData{
    
    [HttpRequestTool getWithURLString:@"http://service.ingkee.com/api/live/gettop?imsi=&uid=17800399&proto=5&idfa=A1205EB8-0C9A-4131-A2A2-27B9A1E06622&lc=0000000000000026&cc=TG0001&imei=&sid=20i0a3GAvc8ykfClKMAen8WNeIBKrUwgdG9whVJ0ljXi1Af8hQci3&cv=IK3.1.00_Iphone&devi=bcb94097c7a3f3314be284c8a5be2aaeae66d6ab&conn=Wifi&ua=iPhone&idfv=DEBAD23B-7C6A-4251-B8AF-A95910B778B7&osversion=ios_9.300000&count=10&multiaddr=1" parameters:nil success:^(NSDictionary *dictionary) {
        self.datas=[ListModel mj_objectArrayWithKeyValuesArray:dictionary[@"lives"]];
        [self.tableView reloadData];
        [self.tableView.mj_header endRefreshing];
    } failure:^(NSError *error) {
        [self.tableView.mj_header endRefreshing];
    }];
}
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    return self.datas.count;
}
-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    HomeTableViewCell * cell=[tableView dequeueReusableCellWithIdentifier:NSStringFromClass([HomeTableViewCell class])];
    cell.selectionStyle=UITableViewCellSelectionStyleNone;
    ListModel * model=self.datas[indexPath.row];
    cell.listModel=model;
    return cell;
}
-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    ShowLivingViewController * show=[[ShowLivingViewController alloc]init];
    ListModel * model=self.datas[indexPath.row];
    show.model=model;
    show.hidesBottomBarWhenPushed=YES;
    [self.navigationController pushViewController:show animated:YES];
}
-(CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    ListModel * model=self.datas[indexPath.row];
    return model.cellHeight;
}
@end
