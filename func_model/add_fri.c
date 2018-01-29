/* add_fri.c
 * Copyright (C) 2018-01-19 10:43 
 * author:peterhaiker
 * email:vim.memory@gmail.com
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include"../header/timeline.h"

void add_fri(void)
{
  mysql_set_character_set(&mysql,"utf8");
  char name[20]={'\0'};
  printf("\t输入您想添加的好友:_\b");
  input_account(name,20);
  //名字输入成功，开始检测是否有这个好友
  char dest[400]={'\0'};
  if(SELECT_PROFILE_ACCOUNT)
    snprintf(dest,400,"set @var_acc='%s';execute pre_sel_pro_acc using @var_acc",name);
  else
    snprintf(dest,400,"select account from %s_profile where account='%s'",login_name,name);
  if(!mysql_query(&mysql,dest)){
    mysql_store_result(&mysql);
    if(0==mysql_next_result(&mysql)){
      result=mysql_store_result(&mysql);
    }
    else{
      fprintf(stderr,"\t数据库发生错误，按回车继续...");
      return;
    }
    //获取结果成功且取到结果集
    if(NULL!=mysql_fetch_row(result)){
      //该好友已存在
      printf("\t该好友已存在，按回车继续...");
      getchar();
      mysql_free_result(result);
      return;
    }
    else{
      mysql_free_result(result);
      char sex[5]={'\0'};
      char birth[15]={'\0'};
      char phone[15]={'\0'};
      char motto[150]={'\0'};//座右铭
      printf("\t性别(男/女):_\b");
      input_sex(sex,5);
      printf("\t生日(YYYY-MM-DD):_\b");
      input_birth(birth,15);
      printf("\t电话:_\b");
      input_phone(phone,15);
      printf("\t座右铭(上限150):_\b");
      input_motto(motto,150);
      //开始写入好友信息
      char quotation_marks='\'';
      if(NULL!=strchr(motto,'\''))
        quotation_marks='\"';
      if(INS_PROFILE)
        snprintf(dest,400,"set @var_acc='%s',@var_sex='%s',@var_birth='%s',@var_phone='%s',@var_motto=%c%s%c;execute pre_ins_profile using @var_acc,@var_sex,@var_birth,@var_phone,@var_motto",name,sex,birth,phone,quotation_marks,motto,quotation_marks);
      else{
        if(NULL!=strchr(motto,';'))
          mysql_query(&mysql,"delimiter //");
        snprintf(dest,400,"insert into %s_profile(account,sex,birth,phone,motto) values('%s','%s','%s','%s',%c%s%c)",login_name,name,sex,birth,phone,quotation_marks,motto,quotation_marks);
      }
      if(!mysql_query(&mysql,dest))
        printf("\t写入成功，按回车继续...");
      else{
        fprintf(stderr,"\t写入失败，按回车继续...");
        puts(mysql_error(&mysql));
      }
      if(false==INS_PROFILE){
        if(NULL!=strchr(motto,';'))
          mysql_query(&mysql,"delimiter ;");
      }
      while(0==mysql_next_result(&mysql)){
        mysql_store_result(&mysql);
      }
      getchar();
      return;
    }
  }
  else{
    printf("\t数据库发生错误，按回车继续...");
  }
  getchar();
  return;
}
