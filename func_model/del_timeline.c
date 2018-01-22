/* del_timeline.c
 * Copyright (C) 2018-01-19 19:51 
 * author:peterhaiker
 * email:vim.memory@gmail.com
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
#include<string.h>
#include"../header/timeline.h"

void del_timeline(void)
{
  mysql_set_character_set(&mysql,"utf8");
  char name[20]={'\0'};
  char dest[200]={'\0'};
  char event[30]={'\0'};
  printf("\t请输入您要删除的事件的执行者:_\b");
  while(1){
    fgets(name,20,stdin);
    if('\n'!=name[strlen(name)-1]){
      printf("\t名字太长了，请重新输入:_\b");
      while('\n'!=getchar());
      continue;
    }
    name[strlen(name)-1]='\0';
    break;
  }
  snprintf(dest,200,"select executor from %s_event where executor='%s'",login_name,name);
  if(!mysql_query(&mysql,dest)&&(NULL!=(result=mysql_store_result(&mysql)))){
    if(0<mysql_num_rows(result)){
      //存在这个执行者，继续
      mysql_free_result(result);
      printf("输入这个事件的首尾5到10个字，中间用空格间隔:_\b");
      while(1){
        fgets(event,30,stdin);
        if('\n'==event[strlen(event)-1]){
          char *p_blank=NULL;
          if(NULL!=(p_blank=strchr(event,' '))){
            *p_blank='%';
            event[strlen(event)-1]='\0';
            if(NULL!=strchr(event,';'))
              mysql_query(&mysql,"delimiter //");
            char quotation_marks='\'';
            if(NULL!=strchr(event,'"'))
              quotation_marks='"';
            snprintf(dest,200,"delete from %s_event where executor='%s' and event like %c%s%c",login_name,name,quotation_marks,event,quotation_marks);
            puts(dest);
            if(!mysql_query(&mysql,dest)){
              if(NULL!=strchr(event,';'))
                mysql_query(&mysql,"delimiter ;");
              printf("\t删除成功，按回车继续...");
              getchar();
              return;
            }
            else{
              if(NULL!=strchr(event,';'))
                mysql_query(&mysql,"delimiter ;");
              printf("\t删除失败，按回车继续...");
              getchar();
              return;
            }
          }
          else{
            printf("\t请按提示正确输入:_\b");
            continue;
          }
        }
        else{
          printf("\t您的输入字数超过上限，首尾在5-10字。请重新输入:_\b");
          continue;
        }
      }
    }
    else{
      printf("\t不存在这个执行者，按回车继续:_\b");
    }
  }
  else{
    printf("\t数据库发生错误，按回车继续...");
    getchar();
    return;
  }
  return;
}
