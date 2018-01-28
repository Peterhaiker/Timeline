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
#include<stdbool.h>
#include<mysql/mysql.h>

#define Format_Double_Symbol "========================================================================================================================"
#define Format_Single_Symbol "------------------------------------------------------------------------------------------------------------------------"
static const char*HOSTNAME="localhost";
static const char*USERNAME="root";
static const char*PASSWORD="2391457146";
static const char*DBNAME="timeline";

extern MYSQL mysql;
extern MYSQL_RES *result;
extern MYSQL_ROW row;
extern char login_name[20];

//预编译语句名称
extern bool SELECT_PASSWD_ACCOUNT;//选择passwd表中的account记录
extern bool SELECT_PROFILE_ACCOUNT;//选择profile表中的account记录
extern bool SELECT_EXECUTOR;//选择执行者
extern bool LOGIN;//登录
extern bool ADD_ACCOUNT;//增加账户
extern bool DEL_ACCOUNT;//删除账户
extern bool DEL_PROFILE;//删除profile表记录
extern bool DEL_EVENT;//删除event记录
extern bool INS_PROFILE;//删除profile表记录
extern bool INS_EVENT;//删除event表记录

//功能接口
int home(void);//主页
void login(void);//登录模块
int show_profile(void);//显示个人信息
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
int del_account(void);//删除账户
int setting(void);//设置
void backup(void);//备份数据库
int restore(void);//恢复数据库
void prepared_statement(void);//实现大部分预编译语句
void test(void);

#endif /* !TIMELINE_H */
