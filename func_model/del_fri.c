/* del_fri.c
 * Copyright (C) 2018-01-19 13:12 
 * author:peterhaiker
 * email:vim.memory@gmail.com
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
#include<string.h>
#include"../header/timeline.h"

void del_fri(void)
{
  printf("\t请输入您想删除的好友姓名，按q退出:_\b");
  char name[20]={'\0'};
  while(1){
    fgets(name,20,stdin);
    if('q'==name[0]&&'\n'==name[1])
      return;
    if('\n'==name[strlen(name)-1]){
      name[strlen(name)-1]='\0';
      if(0==strcmp(name,login_name)){
        puts("\t您输入您自己的名字是不可以的，如果您要删除账户请到删除账户区去删除，按回车继续...");
        getchar();
        continue;
      }
      if(NULL!=strpbrk(name,"/*#-'\"")){
        printf("输入不合法，重新输入姓名:_\b");
        continue;
      }
      break;
    }
    else{
      printf("\t名字太长，重新输入(上限20):_\b");
      while('\n'!=getchar());
    }
  }
  char dest[200]={'\0'};
  //查询是否存在这个好友
  if(SELECT_ACCOUNT)
    snprintf(dest,200,"set @var_pre_profile='%s_profile',@var_acc='%s';execute pre_select_account using @var_pre_profile,@var_acc",login_name,name);
  else
    snprintf(dest,200,"select account from %s_profile where account='%s'",login_name,name);
  if(!mysql_query(&mysql,dest)&&(NULL!=(result=mysql_store_result(&mysql)))){
    if(NULL!=mysql_fetch_row(result)){
      //存在这个好友，开始删除
      if(DEL_PROFILE)
        snprintf(dest,200,"set @var_pre_profile='%s_profile',@var_acc='%s';execute pre_del_profile using @var_pre_profile,@var_acc",login_name,name);
      else
        snprintf(dest,200,"delete from %s_profile where account='%s'",login_name,name);
      if(!mysql_query(&mysql,dest)){
        mysql_free_result(result);
        printf("\t删除成功，按回车继续...");
        getchar();
        return;
      }
    }
    else{
      mysql_free_result(result);
      printf("没有这位朋友，按回车继续...");
    }
  }
  else
    printf("查找这位朋友失败，按回车继续...");
  getchar();
  return;
}
