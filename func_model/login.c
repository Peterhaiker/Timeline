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
  char account[20]={'\0'};
  char passwd[50]={'\0'};
  char*sql=NULL;
  char dest[200]={'\0'};
  char ch;
  if(!mysql_real_connect(&mysql,HOSTNAME,USERNAME,PASSWORD,DBNAME,0,NULL,CLIENT_MULTI_STATEMENTS)){
    printf("\t连接数据库出错，请稍后再试!!!\n");
    sleep(1);
    exit(EXIT_FAILURE);
  }
  mysql_set_character_set(&mysql,"utf8");
  //跳转函数供注销函数和退出登录模块跳转
  setjmp(ENV);
  while(1){
    //连接数据库成功
show_menu:system("reset");
    puts("\t" Format_Double_Symbol);
    puts("\t|                                                    欢迎来到珍谊                                                      |");
    puts("\t" Format_Double_Symbol);
    puts("\t                         1:登录                        2:注册                                3:退出                    |");
    puts("\t" Format_Single_Symbol);
    printf("\t                                                     请选择:_\b");
    while(1!=scanf("%[123]",&ch)){
      while('\n'!=getchar());
      printf("\t                                             错误输入!!!请重新选择:_\b");
    }
    while('\n'!=getchar());

    if('1'==ch){
      //登录
      printf("\t                                                     账户名:__\b\b");
      input_account(account,20);
      printf("\t                                                     密码:__\b\b");
      while(1){
        fgets(passwd,50,stdin);
        if(NULL!=strpbrk(passwd,"-/#\"'")){
          printf("\t有不合法字符，请重新输入(不可带有-,#,/,',\"字符):_\b");
          continue;
        }
       passwd[strlen(passwd)-1]='\0';
       break;
      }
      //构造sql语句
      if(LOGIN){
        snprintf(dest,200,"set @var_acc='%s',@var_pas='%s';execute pre_login using @var_acc,@var_pas",account,passwd);
      }
      else
        snprintf(dest,200,"select account,passwd from passwd where account='%s' and passwd=password('%s')",account,passwd);
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
        while(0==mysql_next_result(&mysql)){
          mysql_free_result(result);
          result=mysql_store_result(&mysql);
        }
          if(0<mysql_num_rows(result)){
            strncpy(login_name,account,20);
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
      printf("\t                                                    账户名:_\b");
      input_account(account,20);
      //确定此用户名是否已存在
      if(SELECT_PASSWD_ACCOUNT)
        snprintf(dest,200,"set @var_acc='%s';execute pre_sel_pas_acc using @var_acc",account);
      else
        snprintf(dest,200,"select account from passwd where account='%s'",account);
      if(mysql_query(&mysql,dest))
        //执行sql语句错误
        printf("\t                                         服务器故障，请稍后再试!!!\n");
      else{
        result=mysql_store_result(&mysql);
        while(0==mysql_next_result(&mysql)){
          mysql_free_result(result);
          result=mysql_store_result(&mysql);
        }
        if(NULL!=mysql_fetch_row(result)){
          //数据库存有记录
              printf("\t                                 此用户名已存在，按回车继续!!!\n");
              mysql_free_result(result);
              getchar();
              goto show_menu;
        }
        //用户名不存在，继续输入密码完成注册
        printf("\t                                                     密码:_\b");
        while(1){
          fgets(passwd,50,stdin);
          if('\n'!=passwd[strlen(passwd)-1]){
            while('\n'!=getchar());
            printf("\t密码超过限制，重新输入(max 50):_\b");
            continue;
          }
          if(NULL!=strpbrk(passwd,"-/#\"'")){
            printf("\t有不合法字符，请重新输入(不可带有-,#,/,',\"字符):_\b");
            continue;
          }
          passwd[strlen(passwd)-1]='\0';
          break;
        }
        //创建mysql事务，只有所有步骤都成功才注册成功
        if(!mysql_query(&mysql,"set autocommit=0")&&!mysql_query(&mysql,"start transaction")){
          //开始事务
          char sign_up_sql[200]={'\0'};
          //构造sql插入语句
          //if(ADD_ACCOUNT)
          //  snprintf(sign_up_sql,200,"set @var_acc='%s',@var_pas='%s';execute pre_add_account using @var_acc,@var_pas",account,passwd);
          //else
            snprintf(sign_up_sql,200,"insert into passwd(account,passwd) values('%s',password('%s'))",account,passwd);
          //构造sql语句创建profile表的预编译语句
          char profile_sql[400]={'\0'};
          snprintf(profile_sql,400,"create table %s_profile(id int(3) not null primary key auto_increment,account varchar(20) not null,sex varchar(2),birth date,phone varchar(14),motto varchar(50))",account);
          //构造成功的情况下，接下来向这个表写入自己的信息,首先构造插入数据的sql语句
          char insert_profile[200]={'\0'};
          //if(INS_PROFILE)
          //  snprintf(insert_profile,200,"set @var_acc='%s';execute pre_ins_profile using @var_acc,@var_sex,@var_birth,@var_phone,@var_motto",account);
          //else
            snprintf(insert_profile,200,"insert into %s_profile(account) values('%s')",account,account);
          //构造sql语句创建event表
          char event_sql[400]={'\0'};
          snprintf(event_sql,400,"create table %s_event(id int(3) not null primary key auto_increment,executor varchar(20) not null,event varchar(200) not null,exec_time datetime not null,state varchar(5) default '未完成')",account);
          //执行sql语句
          if(!mysql_query(&mysql,sign_up_sql)&&!mysql_query(&mysql,profile_sql)&&!mysql_query(&mysql,insert_profile)&&!mysql_query(&mysql,event_sql)){
            //所有步骤都成功,提交事务
            mysql_query(&mysql,"commit");
            puts("\t" Format_Single_Symbol);
            printf("\t                                               注册成功\n");
            printf("\t                                          用户名:%s\t密码:%s\n",account,passwd);
            printf("\t                                              按回车继续...");
            strncpy(login_name,account,20);
            getchar();
            goto show_profile;
          }
          //注册失败，回滚事务
          mysql_query(&mysql,"rollback");
        }
        //注册失败
        puts(mysql_error(&mysql));
        puts("\t                                              注册失败,按回车继续...");
        getchar();
        mysql_free_result(result);
      }
    }
    else if('3'==ch){
      exit(EXIT_SUCCESS);
    }
  }
show_profile:mysql_free_result(result);
  return;
}
