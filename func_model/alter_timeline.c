/* alter_timeline.c
 * Copyright (C) 2018-01-21 16:26 
 * author:peterhaiker
 * email:vim.memory@gmail.com
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include"../header/timeline.h"

void alter_timeline(void)
{
  mysql_set_character_set(&mysql,"utf8");
  char dest[700]={'\0'};
  char executor[20]={'\0'};
  char event[70]={'\0'};
  printf("\t输入您要修改的事件的执行者:_\b");
  while(1){
    fgets(executor,20,stdin);
    if('\n'!=executor[strlen(executor)-1]){
      fprintf(stderr,"\t输入的名字过长，重新输入执行者:_\b");
      while('\n'!=getchar());
      continue;
    }
    executor[strlen(executor)-1]='\0';
    break;
  }

  snprintf(dest,700,"select executor from %s_event where executor='%s'",login_name,executor);
  if(!mysql_query(&mysql,dest)&&(NULL!=(result=mysql_store_result(&mysql)))){
    if(0>=mysql_num_rows(result)){
      fprintf(stderr,"\t没有这个执行者，按回车继续...");
      mysql_free_result(result);
      getchar();
      return;
    }
    mysql_free_result(result);
  }
  else{
    fprintf(stderr,"\t数据库发生错误，按回车继续...");
    //puts(mysql_error(&mysql));
    getchar();
    return;
  }

  printf("\t请输入您要修改的事件的首尾5-10字:_\b");
  while(1){
    fgets(event,70,stdin);
    if('\n'!=event[strlen(event)-1]){
      fprintf(stderr,"\t输入字符过多，请重新输入5-10字:_\b");
      while('\n'!=getchar());
      continue;
    }
    event[strlen(event)-1]='\0';
    break;
  }
  char *p_blank=NULL;
  if(NULL!=(p_blank=strchr(event,' ')))
    *p_blank='%';
  char quotation_marks='\'';
  if(NULL!=strchr(event,'\''))
    quotation_marks='"';
  if(NULL!=strchr(event,';'))
    mysql_query(&mysql,"delimiter //");
  snprintf(dest,700,"select * from %s_profile where executor='%s' and event like %c%s%c",login_name,executor,quotation_marks,event,quotation_marks);
  if(!mysql_query(&mysql,dest)&&(NULL!=(result=mysql_store_result(&mysql)))){
    format_timeline(result);
    mysql_free_result(result);
  }
  char new_executor[20]={'\0'};
  char new_event[600]={'\0'};
  char new_time[21]={'\0'};
  char new_state[11]={'\0'};
  printf("\t请输入新执行者，按q取消更改:_\b");
  while(1){
    fgets(new_executor,20,stdin);
    if(NULL==strchr(new_executor,'\n')){
      fprintf(stderr,"\t输入的名字过长，重新输入新执行者:_\b");
      while('\n'!=getchar());
      continue;
    }
    if('q'==new_executor[0]&&'\n'==new_executor[1])
      new_executor[0]='\0';
    new_executor[strlen(new_executor)-1]='\0';
    break;
  }
  printf("\t请输入新事件(上限200字)，按q取消:_\b");
  while(1){
    fgets(new_event,600,stdin);
    if(NULL==strchr(new_event,'\n')){
      fprintf(stderr,"\t事件最多200字，重新输入:_\b");
      while('\n'!=getchar());
      continue;
    }
    if('q'==new_event[0]&&'\n'==new_event[1])
      new_event[0]='\0';
    new_event[strlen(new_event)-1]='\0';
    break;
  }
  printf("\t请输入新执行时间，按q取消更改:_\b");
  int year,month,day,hour,min,sec;
  char*p_new_time=NULL;
  while(1){
    fgets(new_time,21,stdin);
    if('q'==new_time[0]&&'\n'==new_time[1]){
      new_time[0]='\0';
      break;
    }
    if('-'!=new_time[4]||'-'!=new_time[7]||' '!=new_time[10]||':'!=new_time[13]||':'!=new_time[16]||'\n'!=new_time[19]){
      printf("输入不正确，重新输入(YYYY-MM-DD HH:MM:SS):_\b");
      if('\n'!=new_time[19])
        while('\n'!=getchar());
    }
    else{
      //检测输入是否都为数字
      year=(int)strtol(new_time,&p_new_time,10)-1900;
      if(p_new_time==new_time+4){
        month=(int)strtol(new_time+5,&p_new_time,10)-1;
        if(p_new_time==new_time+7){
          day=(int)strtol(new_time+8,&p_new_time,10);
          if(p_new_time==new_time+10){
            hour=(int)strtol(new_time+11,&p_new_time,10);
            if(p_new_time==new_time+13){
              min=(int)strtol(new_time+14,&p_new_time,10);
              if(p_new_time==new_time+16){
                sec=(int)strtol(new_time+17,&p_new_time,10);
                if(p_new_time==new_time+19){
                  //都是数字，开始检测这个时间是否是未来的时间
                  struct tm*event_tm;
                  time_t event_time;
                  event_time=time(NULL);
                  event_tm=localtime(&event_time);
                  event_tm->tm_sec=sec;
                  event_tm->tm_min=min;
                  event_tm->tm_hour=hour;
                  event_tm->tm_mday=day;
                  event_tm->tm_mon=month;
                  event_tm->tm_year=year;
                  event_time=mktime(event_tm);
                  if(0<=difftime(event_time,time(NULL))){
                    //时间合理，跳出循环
                    new_time[strlen(new_time)-1]='\0';
                    break;
                  }
                  else{
                    printf("\t时间是过去，你确定要添加?(y/n):_\b");
                    char ch;
                    while(1!=scanf("%[yYnN]",&ch)){
                      printf("\t输入错误，你确定要添加?(y/n):_\b");
                      while('\n'!=getchar());
                    }
                    while('\n'!=getchar());
                    ch=tolower(ch);
                    if('y'==ch){
                      new_time[strlen(new_time)-1]='\0';
                      break;
                    }
                    else{
                      printf("\t时间不合理，请重新输入(YYYY-MM-DD HH:MM:SS):_\b");
                      continue;
                    }
                  }
                }
              }
            }
          }
        }
      }
      //时间不合理，重新输入
      printf("\t时间不合理，请重新输入(YYYY-MM-DD HH:MM:SS):_\b");
    }
  }
  printf("\t请输入事件执行状态(已完成/未完成)，按q取消更改:_\b");
  while(1){
    fgets(new_state,11,stdin);
    if('q'==new_state[0]&&'\n'==new_state[1]){
      new_state[0]='\0';
      break;
    }
    if(NULL==strchr(new_state,'\n'))
      while('\n'!=getchar());
    new_state[strlen(new_state)-1]='\0';
    if(0!=strcmp(new_state,"已完成")&&0!=strcmp(new_state,"未完成")){
      printf("\t输入不合理，请重新输入(已完成/未完成):_\b");
      continue;
    }
    break;
  }
  //构造更新记录语句
  snprintf(dest,700,"update ");
  strncat(dest,login_name,700);
  strncat(dest,"_event set ",700);
  if(0!=strlen(new_executor)){
    strncat(dest,"executor='",700);
    strncat(dest,new_executor,700);
    strncat(dest,"',",700);
  }
  if(0!=strlen(new_event)){
    if(NULL!=strchr(new_event,'\''))
      strncat(dest,"event=\"",700);
    else
      strncat(dest,"event='",700);
    strncat(dest,new_event,700);
    if(NULL!=strchr(new_event,'\''))
      strncat(dest,"\",",700);
    else
      strncat(dest,"',",700);
  }
  if(0!=strlen(new_time)){
    strncat(dest,"exec_time='",700);
    strncat(dest,new_time,700);
    strncat(dest,"',",700);
  }
  if(0!=strlen(new_state)){
    strncat(dest,"state='",700);
    strncat(dest,new_state,700);
    strncat(dest,"',",700);
  }
  dest[strlen(dest)-1]='\0';
  strncat(dest," where executor='",700);
  strncat(dest,executor,700);
  strncat(dest,"' and event like ",700);
  if(NULL!=strchr(event,'\''))
    strncat(dest,"\"",700);
  else
    strncat(dest,"\'",700);
  strncat(dest,event,700);
  if(NULL!=strchr(event,'\''))
    strncat(dest,"\"",700);
  else
    strncat(dest,"\'",700);
  if(NULL!=strchr(event,';'))
    mysql_query(&mysql,"delimiter //");
  //更新记录
  if(!mysql_query(&mysql,dest))
    printf("\t修改成功，按回车继续...");
  else{
    printf("\t修改失败，按回车继续...");
    //puts(mysql_error(&mysql));
  }
    getchar();
  if(NULL!=strchr(event,';'))
    mysql_query(&mysql,"delimiter ;");
  return;
}
