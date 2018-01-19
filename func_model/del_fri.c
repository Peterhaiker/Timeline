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
  printf("\t请输入您想删除的好友姓名:_\b");
  char name[20]={'\0'};
  while(1){
    fgets(name,20,stdin);
    if('\n'==name[strlen(name)-1]){
      name[strlen(name)-1]='\0';
      if(0==strcmp(name,login_name)){
        printf("\t您输入您自己的名字是不可以的，如果您要删除账户请到删除账户区去删除，按回车继续...");
        getchar();
        return;
      }
      break;
    }
    else{
      printf("\t名字太长，重新输入(上限20):_\b");
      while('\n'!=getchar());
    }
  }
  char dest[200]={'\0'};
  snprintf(dest,200,"select account from %s_profile where account='%s'",login_name,name);
  if(!mysql_query(&mysql,dest)&&(NULL!=(result=mysql_store_result(&mysql)))){
    if(0<mysql_num_rows(result)){
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
