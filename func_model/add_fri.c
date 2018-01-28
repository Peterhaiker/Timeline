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
  while(1){
    fgets(name,20,stdin);
    if(NULL==strchr(name,'\n')){
      printf("\t名字太长了(上限 20)，重新输入:_\b");
      while('\n'!=getchar());
      continue;
    }
    else if(NULL!=strpbrk(name,"-#/*'\"")){
      printf("有不合法字符，重新输入:_\b");
      continue;
    }
    else{
      name[strlen(name)-1]='\0';
      break;
    }
  }
  //名字输入成功，开始检测是否有这个好友
  char dest[300]={'\0'};
  if(SELECT_PROFILE_ACCOUNT)
    snprintf(dest,300,"set @var_acc='%s';execute pre_sel_pro_acc using @var_acc",name);
  else
    snprintf(dest,300,"select account from %s_profile where account='%s'",login_name,name);
  if(!mysql_query(&mysql,dest)&&(NULL!=(result=mysql_store_result(&mysql)))){
    //获取结果成功且取到结果集
    if(NULL!=mysql_fetch_row(result)){
      //该好友已存在
      printf("\t该好友已存在，按回车继续...");
      getchar();
      mysql_free_result(result);
      return;
    }
    else{
      char sex[5]={'\0'};
      char birth[15]={'\0'};
      char phone[15]={'\0'};
      char motto[150]={'\0'};//座右铭
      printf("\t性别(男/女):_\b");
      while(1){
        fgets(sex,5,stdin);
        if(NULL==strchr(sex,'\n')){
          printf("\t请按指定格式输入(男/女):_\b");
          while('\n'!=getchar());
        }
        else{
          sex[strlen(sex)-1]='\0';
          if(NULL==strstr("男女",sex)){
            printf("\t请输入指定字段(男/女):_\b");
          }
          else
            break;
        }
      }
      printf("\t生日(YYYY-MM-DD):_\b");
      int year,month,day;
      char *p_birth=birth;
      time_t birth_time;
      struct tm *birth_tm;
      while(1){
        fgets(birth,15,stdin);
        if(NULL==strchr(birth,'\n')||birth[4]!='-'||birth[7]!='-'){
          printf("\t请按指定格式输入(YYYY-MM-DD):_\b");
          if(NULL==strchr(birth,'\n'))
            while('\n'!=getchar());
        }
        else{
          year=(int)strtol(birth,&p_birth,10)-1900;
          if(p_birth==birth+4){
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
                if(0<difftime(time(NULL),birth_time)){
                  break;
                }
                else{
                  printf("\t请回到娘胎或重新输入(YYYY-MM-DD):_\b");
                  continue;
                }
              }
            }
          }
          printf("\t别闹，输入数字好不好(YYYY-MM-DD):_\b");
        }
      }
      printf("\t电话:_\b");
      while(1){
phone_again:fgets(phone,15,stdin);
        if(NULL==strchr(phone,'\n')){
          printf("你不要以为我没读过书，有这么长的电话吗?重输:_\b");
          while('\n'!=getchar());
        }
        else{
          phone[strlen(phone)-1]='\0';
          for(int i=0;phone[i]!='\0';i++){
            if(!isdigit(phone[i])){
              printf("输入不合法，请重新输入电话:_\b");
              goto phone_again;
            }
          }
          break;
        }
      }
      printf("\t座右铭(上限150):_\b");
      while(1){
        fgets(motto,150,stdin);
        if('\n'==motto[strlen(motto)-1])
          break;
        else{
          printf("\t超过上限，重新输入:_\b");
          while('\n'!=getchar());
        }
      }
      //开始写入好友信息
      if(INS_PROFILE)
        snprintf(dest,300,"set @var_acc='%s',@var_sex='%s',@var_birth='%s',@var_phone='%s',@var_motto='%s';execute pre_ins_profile using @var_acc,@var_sex,@var_birth,@var_phone,@var_motto",name,sex,birth,phone,motto);
      else{
        char quotation_marks='\'';
        if(NULL!=strchr(motto,'\''))
          quotation_marks='\"';
        if(NULL!=strchr(motto,';'))
          mysql_query(&mysql,"delimiter //");
        snprintf(dest,300,"insert into %s_profile(account,sex,birth,phone,motto) values('%s','%s','%s','%s',%c%s%c)",login_name,name,sex,birth,phone,quotation_marks,motto,quotation_marks);
      }
      if(!mysql_query(&mysql,dest))
        printf("\t写入成功，按回车继续...");
      if(false==INS_PROFILE){
        if(NULL!=strchr(motto,';'))
          mysql_query(&mysql,"delimiter ;");
      }
    }
  }
  else{
    printf("\t数据库发生错误，按回车继续...");
  }
  getchar();
  return;
}
