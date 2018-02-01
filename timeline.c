/*
 * timeline.c
 * Copyright (C) 2017-12-02 18:57 
 * author  Peterhaiker 
 * email   <vim.memory@gmail.com>
 *
 * description:This program have multi function like notebook pro
 */

#include "stdio.h"
#include"header/timeline.h"
#include<setjmp.h>

char login_name[20]={'\0'};//保存当前登录账户名
jmp_buf ENV;//跳转函数保存的跳转时的环境
MYSQL mysql;//MYSQL对象
MYSQL_RES *result;//结果集变量
MYSQL_ROW row;//定义行变量

int main(int argc,char*argv[])
{
  mysql_init(&mysql);
  mysql_options(&mysql,CLIENT_MULTI_STATEMENTS,0);
  login();
  prepared_statement();
  while(1==home()){
    mysql_init(&mysql);
    mysql_options(&mysql,CLIENT_MULTI_STATEMENTS,0);
    login();
    prepared_statement();
  }
  return 0;
}
