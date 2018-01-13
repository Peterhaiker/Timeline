/*
 * login.c
 * Copyright (C) 2017-12-02 00:41 
 * author  Peterhaiker 
 * email   <vim.memory@gmail.com>
 *
 * description:
 */

#include<stdio.h>
#include<string.h>
#include"../header/timeline.h"

void login(void)
{
  system("reset");
  char*sql=NULL;
  char dest[200]={'\0'};
  puts("\t" Format_Double_Symbol);
  puts("\t||\t             Welcome to Timeline                  ||");
  puts("\t" Format_Double_Symbol);
  puts("\t\t             1:login   2:sign up");
  printf("\t请选择:_\b");
  char ch;
  while(1!=scanf("%[12]",&ch)){
    while('\n'!=getchar());
    printf("\t错误输入!!!请重新选择:_\b");
  }
  while('\n'!=getchar());

  if(!mysql_real_connect(&mysql,HOSTNAME,USERNAME,PASSWORD,DBNAME,0,NULL,0))
    printf("\t连接数据库出错，请稍后再试!!!\n");
  else{
    //连接数据库成功
    if('1'==ch){
      //登录
      printf("\t账户名:__\b\b");
      char name[20]={'\0'};
      char passwd[50]={'\0'};
      fgets(name,20,stdin);
      name[strlen(name)-1]='\0';
      printf("\t密码:__\b\b");
      fgets(passwd,50,stdin);
      passwd[strlen(passwd)-1]='\0';

      sql="select * from passwd where number="
      strncpy(dest,sql,200);
      strncat(dest,name,200);
      if(mysql_query(&mysql,dest))
        //数据库未存有记录,即登录失败
        printf("\t服务器故障，请稍后再试!!!\n");
      else{
        result=mysql_store_result(&mysql);
        if(0!=mysql_num_rows(result)){
          while((row=mysql_fetch_row(result)))
            //********************************************
        }
      }
      //result=mysql_store_result(&mysql);
    }
  }
  return;
}
