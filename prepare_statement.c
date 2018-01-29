/*
 * prepare_statement.c
 * Copyright (C) 2018-01-27 10:59 
 * peterhaiker <vim.memory@gmail.com>
 *
 * Distributed under terms of the MIT license.
 * Describe:all prepared statement are in here
 */

#include<stdio.h>
#include<mysql/mysql.h>
#include"header/timeline.h"

bool SELECT_PASSWD_ACCOUNT=false;
bool SELECT_PROFILE_ACCOUNT=false;
bool SELECT_EXECUTOR=false;
bool LOGIN=false;
bool ADD_ACCOUNT=false;
bool DEL_ACCOUNT=false;
bool DEL_PROFILE=false;
bool DEL_EVENT=false;
bool INS_PROFILE=false;
bool INS_EVENT=false;

void prepared_statement(void)
{
  char dest[200]={'\0'};
  //登录
  if(0==mysql_query(&mysql,"prepare pre_login from 'select account,passwd from passwd where account=? and passwd=password(?)'"))
    LOGIN=true;
  //查询passwd的account字段
  if(0==mysql_query(&mysql,"prepare pre_sel_pas_acc from 'select account from passwd where account=?'"))
    SELECT_PASSWD_ACCOUNT=true;
  //查询profile的account字段
  snprintf(dest,200,"prepare pre_sel_pro_acc from 'select account from %s_profile where account=?'",login_name);
  if(0==mysql_query(&mysql,dest))
    SELECT_PROFILE_ACCOUNT=true;
  //查询event表的executor字段
  snprintf(dest,200,"prepare pre_sel_exe from 'select executor from %s_event where executor=?'",login_name);
  if(0==mysql_query(&mysql,dest))
    SELECT_EXECUTOR=true;
  //删除passwd记录
  if(0==mysql_query(&mysql,"prepare pre_del_account from 'delete from passwd where account=?'"))
    DEL_ACCOUNT=true;
  //删除profile记录
  snprintf(dest,200,"prepare pre_del_profile from 'delete from %s_profile where account=?'",login_name);
  if(0==mysql_query(&mysql,dest))
    DEL_PROFILE=true;
  //删除event记录
  snprintf(dest,200,"prepare pre_del_event from 'delete from %s_event where executor=? and event like ?'",login_name);
  if(0==mysql_query(&mysql,dest))
    DEL_EVENT=true;
  //插入记录到profile表
  snprintf(dest,200,"prepare pre_ins_profile from 'insert into %s_profile(account,sex,birth,phone,motto) values(?,?,?,?,?)'",login_name);
  if(0==mysql_query(&mysql,dest))
    INS_PROFILE=true;
  //插入记录到event表
  snprintf(dest,200,"prepare pre_ins_event from 'insert into %s_event(executor,event,exec_time) values(?,?,?)'",login_name);
  if(0==mysql_query(&mysql,dest))
    INS_EVENT=true;
  //插入记录到passwd表
  if(0==mysql_query(&mysql,"prepare pre_add_account from 'insert into passwd(account,passwd) values(?,password(?))'"))
    ADD_ACCOUNT=true;
  return;
}
