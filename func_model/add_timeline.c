/* add_timeline.c
 * Copyright (C) 2018-01-19 13:46 
 * author:peterhaiker
 * email:vim.memory@gmail.com
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include"../header/timeline.h"

void add_timeline(void)
{
  mysql_set_character_set(&mysql,"utf8");
  char executor[20]={'\0'};
  char event[122]={'\0'};
  char exec_time[21]={'\0'};
  char state[12]={'\0'};
  char dest[300]={'\0'};
  printf("\t输入事件执行者:_\b");
  input_account(executor,20);
  printf("\t输入执行时间(YYYY-MM-DD HH:MM:SS):_\b");
  int year,month,day,hour,min,sec;
  char*p_exec_time=NULL;
  while(1){
    fgets(exec_time,21,stdin);
    if('-'!=exec_time[4]||'-'!=exec_time[7]||' '!=exec_time[10]||':'!=exec_time[13]||':'!=exec_time[16]||'\n'!=exec_time[19]){
      printf("\t输入不正确，重新输入(YYYY-MM-DD HH:MM:SS):_\b");
      if('\n'!=exec_time[strlen(exec_time)-1])
        while('\n'!=getchar());
    }
    else{
      //检测输入的是否都是数字
      year=(int)strtol(exec_time,&p_exec_time,10)-1900;
      if(p_exec_time==exec_time+4){
          month=(int)strtol(exec_time+5,&p_exec_time,10)-1;
          if(p_exec_time==exec_time+7){
            day=(int)strtol(exec_time+8,&p_exec_time,10);
            if(p_exec_time==exec_time+10){
              hour=(int)strtol(exec_time+11,&p_exec_time,10);
              if(p_exec_time==exec_time+13){
                min=(int)strtol(exec_time+14,&p_exec_time,10);
                if(p_exec_time==exec_time+16){
                  sec=(int)strtol(exec_time+17,&p_exec_time,10);
                  if(p_exec_time==exec_time+19){
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
                      exec_time[strlen(exec_time)-1]='\0';
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
                        exec_time[strlen(exec_time)-1]='\0';
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
  //时间输入完毕，开始输入事件
  printf("\t输入事件内容(上限40):_\b");
  while(1){
    fgets(event,122,stdin);
    if('\n'!=event[strlen(event)-1]){
      printf("\t事件超过上限，重新输入(max 120):_\b");
      while('\n'!=getchar());
      continue;
    }
    event[strlen(event)-1]='\0';
    break;
  }
  if(INS_EVENT)
    snprintf(dest,300,"set @var_executor='%s',@var_event='%s',@var_time='%s';execute pre_ins_event using @var_executor,@var_event,@var_time",executor,event,exec_time);
  else{
    char quotation_marks='\'';
    if(NULL!=strchr(event,'\''))
      quotation_marks='\"';
    if(NULL!=strchr(event,';'))
      mysql_query(&mysql,"delimiter //");
    snprintf(dest,300,"insert into %s_event(executor,event,exec_time) values('%s','%s',%c%s%c)",login_name,executor,event,quotation_marks,exec_time,quotation_marks);
  }
  if(!mysql_query(&mysql,dest)){
    printf("\t事件已增加，按回车继续...");
  }
  else{
    printf("\t事件增加失败，按回车继续...");
    puts(mysql_error(&mysql));
  }
  if(false==INS_EVENT){
    if(NULL!=strchr(event,';'))
      mysql_query(&mysql,"delimiter //");
  }
  //清空刚刚请求得到的多个结果集
  getchar();
  while(0==mysql_next_result(&mysql))
    mysql_store_result(&mysql);
  return;
}
