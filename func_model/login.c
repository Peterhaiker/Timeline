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
  char name[20]={'\0'};
  char passwd[50]={'\0'};
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
show_menu:system("reset");
    puts("\t" Format_Double_Symbol);
    puts("\t||\t             Welcome to Timeline                  ||");
    puts("\t" Format_Double_Symbol);
    puts("\t\t         1:login   2:sign up   3:exit");
    printf("\t请选择:_\b");
    while(1!=scanf("%[123]",&ch)){
      while('\n'!=getchar());
      printf("\t错误输入!!!请重新选择:_\b");
    }
    while('\n'!=getchar());

    if('1'==ch){
      //登录
      printf("\t账户名:__\b\b");
      fgets(name,20,stdin);
      name[strlen(name)-1]='\0';
      printf("\t密码:__\b\b");
      fgets(passwd,50,stdin);
      passwd[strlen(passwd)-1]='\0';

      sql="select * from passwd where passwd=password('";
      strncpy(dest,sql,200);
      strncat(dest,passwd,200);
      strncat(dest,"')",200);
      if(mysql_query(&mysql,dest)){
        //sql语句执行失败
        printf("\t服务器故障，请稍后再试!!!按回车继续...\n");
        getchar();
        //回收结果集空间
        mysql_free_result(result);
        exit(EXIT_FAILURE);
      }
      else{//sql语句执行成功
        result=mysql_store_result(&mysql);
        if(0!=mysql_num_rows(result))
          //数据库存有账户数据
          while((row=mysql_fetch_row(result)))
            if(0==strcmp(name,row[0])){
              printf("\t登录成功，2秒后自动跳转...\n");
              goto show_profile;//如果匹配成功就跳转，否则即为输入错误
            }
        //登录错误或者数据库没有存有账户时
        printf("\t账户名或密码输入错误!!!\n");
        printf("\t按回车继续...\n");
        getchar();
        //回收结果集空间
        mysql_free_result(result);
      }
    }
    else if('2'==ch){
      //注册
      printf("\t账户名:_\b");
      fgets(name,20,stdin);
      name[strlen(name)-1]='\0';
      //确定此用户名是否已存在
      sql="select * from passwd where number='";
      strncpy(dest,sql,200);
      strncat(dest,name,200);
      strncat(dest,"'",200);
      if(mysql_query(&mysql,dest))
        //执行sql语句错误
        printf("\t服务器故障，请稍后再试!!!\n");
      else{
        result=mysql_store_result(&mysql);
        if(0!=mysql_num_rows(result)){
          //数据库存有记录
          while((row=mysql_fetch_row(result)))
            if(0==strcmp(row[0],name)){
              printf("\t此用户名已存在，按回车继续!!!\n");
              mysql_free_result(result);
              getchar();
              goto show_menu;
            }
        }
        //用户名不存在，继续输入密码完成注册
        printf("\t密码:_\b");
        fgets(passwd,50,stdin);
        passwd[strlen(passwd)-1]='\0';
        //构造sql插入语句
        sql="insert into passwd(number,passwd) values('";
        strncpy(dest,sql,200);
        strncat(dest,name,200);
        strncat(dest,"',",200);
        strncat(dest,"password('",200);
        strncat(dest,passwd,200);
        strncat(dest,"'))",200);
        //构造成功，开始注册
        if(mysql_query(&mysql,dest)){
          //注册失败
          mysql_free_result(result);
          fprintf(stderr,"\t服务器故障，注册失败，请稍后再试!!!\n");
          fprintf(stderr,"\t按回车继续...");
          getchar();
          exit(EXIT_FAILURE);
        }
        printf("\t注册成功，按回车继续...");
        getchar();
        goto show_profile;
      }
    }
    else if('3'==ch)
      exit(EXIT_SUCCESS);
  }
show_profile:mysql_free_result(result);
  return;
}
