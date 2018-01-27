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

bool SELECT_ACCOUNT=false;
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
  //登录
  if(0==mysql_query(&mysql,"prepare pre_login from 'select account,passwd from passwd where account=? and passwd=password(?)'"))
    LOGIN=true;
  //查询account字段
  if(0==mysql_query(&mysql,"prepare pre_select_account from 'select account from ? where account=?'"))
    SELECT_ACCOUNT=true;
  if(0==mysql_query(&mysql,"prepare pre_select_executor from 'select executor from ? where executor=?'"))
    SELECT_EXECUTOR=true;
  //删除passwd记录
  if(0==mysql_query(&mysql,"prepare pre_del_account from 'delete from passwd where account=?'"))
    DEL_ACCOUNT=true;
  //删除profile记录
  if(0==mysql_query(&mysql,"prepare pre_del_profile from 'delete from ? where account=?'"))
    DEL_PROFILE=true;
  //删除event记录
  if(0==mysql_query(&mysql,"prepare pre_del_event from 'delete from ? where executor=? and event like ?'"))
    DEL_EVENT=true;
  //插入记录到profile表
  if(0==mysql_query(&mysql,"prepare pre_ins_profile from 'insert into ?_profile(account,sex,birth,phone,motto) values(?,?,?,?,?)'"))
    INS_PROFILE=true;
  //插入记录到event表
  if(0==mysql_query(&mysql,"prepare pre_ins_event from 'insert into ?_event(executor,event,exec_time) values(?,?,?)'"))
    INS_EVENT=true;
  //插入记录到passwd表
  if(0==mysql_query(&mysql,"prepare pre_add_account from 'insert into passwd(account,passwd) values(?,password(?))'"))
    ADD_ACCOUNT=true;
  return;
}
