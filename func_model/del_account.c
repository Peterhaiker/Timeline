/* del_account.c
 * Copyright (C) 2018-01-18 19:22 
 * author:peterhaiker
 * email:vim.memory@gmail.com
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
#include<ctype.h>
#include"../header/timeline.h"

int del_account(void)
{
  char dest[200]={'\0'};
  mysql_set_character_set(&mysql,"utf8");
  printf("\t您确定要彻底删除该账户?(y/n):_\b");
  char ch;
  while(1!=scanf("%[yYnN]",&ch)){
    while('\n'!=getchar());
    printf("\t输入不合法，请重新输入(y/n):_\b");
  }
  while('\n'!=getchar());
  ch=tolower(ch);
  if('y'==ch){
    //删除
    if(!mysql_query(&mysql,"set autocommit=0")){//如果不显示提交就自动回滚
      if(!mysql_query(&mysql,"start transaction")){
        //开始事务
        //开始删除passwd的记录
        snprintf(dest,200,"delete from passwd where account='%s'",login_name);
        if(!mysql_query(&mysql,dest)){
          //passwd记录删除成功，开始删除对应的event和profile表
          //先删profile表
          snprintf(dest,200,"drop table %s_profile",login_name);
          if(!mysql_query(&mysql,dest)){
            //删除profile表成功，开始删除event表
            snprintf(dest,200,"drop table %s_event",login_name);
            if(!mysql_query(&mysql,dest)){
              //都删除成功，直接返回
              if(!mysql_query(&mysql,"commit")){
                printf("\t你还是那么狠心，按回车吧，前任");
                getchar();
                return 1;
              }
            }
          }
        }
      }
    }
    mysql_query(&mysql,"rollback");
    puts(mysql_error(&mysql));
    printf("\t哎呀，月老好像并不希望你此时离开我，稍后再来吧，虽然我很难过");
  }
  else{
    puts("\t哈哈，你怂了，舍不得我就别离开嘛");
  }
  return 0;
}
