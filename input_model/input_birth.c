/*
 * input_birth.c
 * Copyright (C) 2018-01-29 20:14 
 * peterhaiker <vim.memory@gmail.com>
 *
 * Distributed under terms of the MIT license.
 * Describe:
 */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

void input_birth(char birth[],size_t size)
{
  int year,month,day;
  char*p_birth=birth;
  time_t birth_time;
  struct tm*birth_tm;
  while(1){
    fgets(birth,15,stdin);
    if(NULL==strchr(birth,'\n')){
      printf("\t生日超过长度，重新输入(YYYY-MM-DD):_\b");
      while('\n'!=getchar());
      continue;
    }
    else if(NULL==strchr(birth,'\n')||birth[4]!='-'||birth[7]!='-'){
      printf("\t请按指定格式输入(YYYY-MM-DD):_\b");
      continue;
    }
    else{
      year=(int)strtol(birth,&p_birth,10)-1900;
      if(p_birth==birth+4)
        month=(int)strtol(birth+5,&p_birth,10)-1;
      if(p_birth==birth+7){
        day=(int)strtol(birth+8,&p_birth,10);
        if(p_birth==birth+10){
          //格式都正确，开始检查时间是否合理，比如不能是未来或现在的时间
          //先用当前时间的其余部分初始化struct tm结构，除了年月日
          birth_time=time(NULL);
          birth_tm=localtime(&birth_time);
          birth_tm->tm_year=year;
          birth_tm->tm_mon=month;
          birth_tm->tm_mday=day;
          birth_time=mktime(birth_tm);
          if(0<difftime(time(NULL),birth_time))
            //大于当前时间
            break;
          else{
            printf("\t请回到娘胎或重新输入(YYYY-MM-DD):_\b");
            continue;
          }
        }
      }
      printf("\t别闹，输入数字好不好(YYYY-MM-DD):_\b");
    }
  }
  return;
}
