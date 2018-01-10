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
void login(void);  //登录模块
void show_timeline(const struct timeline*tl);//以时间线形式显示事件
int choice_setup(void);//进入功能界面选择相应的功能并返回对应的序号
void list_allfri(struct fl_index*);//列出所有的朋友，也可以查询朋友
void add_fri(struct fl_index*,struct fri_list*,struct timeline*);//增加一个朋友
void del_fri(struct fl_index*,struct fri_list*,struct timeline*);//删除好友

#endif /* !TIMELINE_H */
