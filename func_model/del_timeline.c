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
  input_account(name,20);
  if(SELECT_EXECUTOR)
    snprintf(dest,200,"set @var_executor='%s';execute pre_sel_exe using @var_executor",name);
  else
    snprintf(dest,200,"select executor from %s_event where executor='%s'",login_name,name);
  if(!mysql_query(&mysql,dest)){
    //取结果集
    if(SELECT_EXECUTOR){
      while(0==mysql_next_result(&mysql))
        ;
      result=mysql_store_result(&mysql);
    }
    else
      result=mysql_store_result(&mysql);
    //检测取到的结果集是否为空
    if(NULL==result){
      fprintf(stderr,"\t数据库发生错误，按回车继续...");
      puts(mysql_error(&mysql));
      getchar();
      return;
    }
    if(NULL!=mysql_fetch_row(result)){
      //存在这个执行者，继续
      mysql_free_result(result);
      printf("\t输入这个事件的首尾5到10个字，中间用空格间隔:_\b");
      while(1){
        fgets(event,30,stdin);
        if('\n'==event[strlen(event)-1]){
          char *p_blank=NULL;
          if(NULL!=(p_blank=strchr(event,' '))){
            *p_blank='%';
            event[strlen(event)-1]='\0';
            if(DEL_EVENT)
              snprintf(dest,200,"set @var_exe='%s',@var_eve='%s';execute pre_del_event using @var_exe,@var_eve",name,event);
            else{
              if(NULL!=strchr(event,';'))
                mysql_query(&mysql,"delimiter //");
              char quotation_marks='\'';
              if(NULL!=strchr(event,'"'))
                quotation_marks='"';
              snprintf(dest,200,"delete from %s_event where executor='%s' and event like %c%s%c",login_name,name,quotation_marks,event,quotation_marks);
            }
            if(!mysql_query(&mysql,dest))
              printf("\t删除成功，按回车继续...");
            else
              printf("\t删除失败，按回车继续...");
            if(false==DEL_EVENT)
              if(NULL!=strchr(event,';'))
                mysql_query(&mysql,"delimiter ;");
            //清空刚刚可能获得的多个结果集
            while(0==mysql_next_result(&mysql))
              ;
            getchar();
            return;
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
      mysql_free_result(result);
      printf("\t不存在这个执行者，按回车继续:_\b");
      getchar();
      return;
    }
  }
  else{
    printf("\t数据库发生错误，按回车继续...");
    getchar();
    return;
  }
  return;
}
