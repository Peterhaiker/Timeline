/*
 * login.c
 * Copyright (C) 2017-12-02 00:41 
 * author  Peterhaiker 
 * email   <vim.memory@gmail.com>
 *
 * description:
 */

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include"../header/timeline.h"

void login(void)
{
  char*sql=NULL;
  char dest[200]={'\0'};
  char ch;
  if(!mysql_real_connect(&mysql,HOSTNAME,USERNAME,PASSWORD,DBNAME,0,NULL,0)){
    printf("\t连接数据库出错，请稍后再试!!!\n");
    sleep(1);
    exit(EXIT_FAILURE);
  }
  while(1){
    //连接数据库成功
    system("reset");
    puts("\t" Format_Double_Symbol);
    puts("\t||\t             Welcome to Timeline                  ||");
    puts("\t" Format_Double_Symbol);
    puts("\t\t             1:login   2:sign up");
    printf("\t请选择:_\b");
    while(1!=scanf("%[12]",&ch)){
      while('\n'!=getchar());
      printf("\t错误输入!!!请重新选择:_\b");
    }
    while('\n'!=getchar());

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

      sql="select * from passwd where passwd=password('";
      strncpy(dest,sql,200);
      strncat(dest,passwd,200);
      strncat(dest,"')",200);
      if(mysql_query(&mysql,dest))
        //登录失败
        printf("\t服务器故障，请稍后再试!!!\n");
      else{
        result=mysql_store_result(&mysql);
        if(0!=mysql_num_rows(result))
          while((row=mysql_fetch_row(result)))
            if(0==strcmp(name,row[0]))
              goto a;//如果匹配成功就跳转，否则即为输入错误
          printf("\t账户名或密码输入错误!!!\n");
      }
      printf("\t按回车继续...\n");
      getchar();
      //回收结果集空间
      mysql_free_result(result);
    }
    else{
      //注册
    }
  }
a:mysql_free_result(result);
  printf("\t登录成功，2秒后自动跳转...\n");
  return;
}
