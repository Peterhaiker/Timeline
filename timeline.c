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

char login_name[50]={'\0'};//保存当前登录账户名
int main(int argc,char*argv[])
{
  mysql_init(&mysql);
  login();
  show_profile();
  return 0;
}
