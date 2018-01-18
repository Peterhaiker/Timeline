/*
 * timeline.h
 * Copyright (C) 2017-12-01 23:29
 * author  Peterhaiker 
 * email  <vim.memory@gmail.com>
 *
 * description:
 */

#ifndef TIMELINE_H
#define TIMELINE_H

#include<time.h>
#include<mysql/mysql.h>

#define Format_Double_Symbol "============================================================"
#define Format_Single_Symbol "------------------------------------------------------------"
static const char*HOSTNAME="localhost";
static const char*USERNAME="root";
static const char*PASSWORD="2391457146";
static const char*DBNAME="timeline";

//时间线事件
struct timeline{
  char*name;  //姓名
  time_t tm;  //事件发生时期
  char*event;  //事件内容
  int finished;  //表明此事件是否被处理，1为已处理，0为没有
  struct timeline*before;
  struct timeline*next;
}Timeline;//以时间线显示事件

//个人信息
struct profile{
  char*name;  //姓名
  char sex[8];  //性别
  time_t birth;  //出生年月日，以空格或小数点或斜杠分隔
  char phone[14];  //电话号码
  char*motto;  //座右铭
  struct timeline*timeline;
}profile;

//显示所有朋友的链表
struct fri_list{
  char*name;
  struct profile*profile;
  struct fri_list*before;
  struct fri_list*next;
}fri_list;

//对上一个朋友链表做的二级索引
struct fl_index{
  struct fri_list*first_profile;//每个字母开头的第一个朋友
}fl_index[26];

//功能接口
void home(void);//主页
void home_menu(void);//主页模块菜单导航
void login(void);//登录模块
void show_profile(void);//显示个人信息
void alter_profile(void);//修改用户信息
void all_timeline(void);//以时间线形式显示所有事件
void format_timeline(MYSQL_RES*result);//格式化输出事件集
void add_timeline(void);//增加事件
void alter_timeline(void);//修改事件状态
void del_timeline(void);//删除事件
void menu(void);//进入功能界面选择相应的功能
void list_fri(void);//列出所有的朋友
void search_fri(void);//搜索好友
void add_fri(void);//增加一个朋友
void del_fri(void);//删除好友
void del_account(void);//删除账户
void sign_out(void);//退出登录

#endif /* !TIMELINE_H */
