/* alter_profile.c
 * Copyright (C) 2018-01-16 16:37 
 * author:peterhaiker
 * email:vim.memory@gmail.com
 *
 * Distributed under terms of the MIT license.
 * Describe:modify friends profile
 */

#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include"../header/timeline.h"

void alter_profile(void)
{
  mysql_set_character_set(&mysql,"utf8");
//  mysql_set_server_option(&mysql,MYSQL_OPTION_MULTI_STATEMENTS_ON);
  system("reset");
  puts("\t" Format_Double_Symbol);
  puts("\t|                                                 *修*改*信*息*                                                        |");
  puts("\t" Format_Double_Symbol);
  char dest[300]={'\0'};
  //构造sql语句查出所有的用户
  snprintf(dest,300,"select * from %s_profile",login_name);
  if((!mysql_query(&mysql,dest))&&(NULL!=(result=mysql_store_result(&mysql)))){
    //获取数据成功
    printf("\t显示所有朋友?(y/n):_\b");
    char ch;
    while(1!=scanf("%[yYnN]",&ch)){
      while('\n'!=getchar());
      printf("\t输入不合法，显示所有用户?(y/n):_\b");
    }
    while('\n'!=getchar());
    ch=tolower(ch);
    if('y'==ch){
      puts("\t" Format_Double_Symbol);
      puts("\t|                                                 *朋*友*列*表*                                                        |");
      puts("\t" Format_Single_Symbol);
      while(row=mysql_fetch_row(result)){
        printf("\t|姓名:%-37s    性别:%-27s   电话:%-36s\n",row[1],row[2],row[4]);
        printf("\t|生日:%-113s\n",row[3]);
        printf("\t|座右铭:%-115s\n",row[5]);
        puts("\t" Format_Single_Symbol);
      }
    }
    //开始选择你要更改的朋友
    char account_name[20]={'\0'};
    char new_sex[6]={'\0'};
    char new_birth[15]={'\0'};
    char new_phone[14]={'\0'};
    char new_motto[50]={'\0'};
    //输入要修改的账户名直到合法才退出循环
    printf("\t您要更改的账户名:_\b");
    input_account(account_name,20);

    while(1){
      if(SELECT_PROFILE_ACCOUNT)
        snprintf(dest,300,"set @var_acc='%s';execute pre_sel_pro_acc using @var_acc",account_name);
      else
        snprintf(dest,300,"select account from %s_profile where account='%s'",login_name,account_name);
      if((!mysql_query(&mysql,dest))/*&&(NULL!=(result=mysql_store_result(&mysql)))*/){
        result=mysql_store_result(&mysql);
        //取第二个结果集
        if(mysql_next_result(&mysql)==0){
          mysql_free_result(result);
          result=mysql_store_result(&mysql);
        }
        else{
          fprintf(stderr,"\t数据库发生错误，按回车继续...");
          getchar();
          return;
        }
        if(1==mysql_num_rows(result)){
          //查到该用户名
          break;
        }
        else{
          printf("\t该用户不存在，请重新输入,或按q取消更改:_\b");
          fgets(account_name,20,stdin);
          if('q'==account_name[0]&&'\n'==account_name[1])
            return;
          account_name[strlen(account_name)-1]='\0';
        }
      }
      else{
        fprintf(stderr,"\ta数据库发生错误，按回车继续...");
        puts(mysql_error(&mysql));
        getchar();
        return;
      }
    }
    //账户名查找成功,输入性别
    printf("\t性别(男/女):_\b");
    input_sex(new_sex,6);
    //性别输入成功，输入生日
    char birth_cpy[15]={'\0'};
    char*p1,*p2,*p3;
    p1=p2=p3=NULL;
    int year,month,day;
    time_t tm;
    struct tm *birth_tm=NULL;
    int diff_time;
    printf("\t生日(YYYY-MM-DD):_\b");
    while(fgets(new_birth,15,stdin)){
      //检测是否输入多于15个字符，如果是则清除掉多余输入
      if(NULL==strchr(new_birth,'\n'))
        //若不包含换行，则说明输入多于15个字符
        while('\n'!=getchar());
      
      new_birth[strlen(new_birth)-1]='\0';
      if('-'==new_birth[4]&&'-'==new_birth[7]){
        strncpy(birth_cpy,new_birth,15);
        birth_cpy[4]=birth_cpy[7]=birth_cpy[10]='\0';
        //判断时间是否大于当前时间
        time(&tm);
        birth_tm=localtime(&tm);//获取当前时间的struct_tm结构
        birth_tm->tm_year=(int)strtol(birth_cpy,&p1,10)-1900;
        birth_tm->tm_mon=(int)strtol(birth_cpy+5,&p2,10)-1;
        birth_tm->tm_mday=(int)strtol(birth_cpy+8,&p3,10);
        if(p1!=birth_cpy+4||p2!=birth_cpy+7||p3!=birth_cpy+10){
          printf("\t大哥，请不要调戏我，输入数字好不好(YYY-MM-DD):_\b");
        }
        else{
          tm=mktime(birth_tm);
          diff_time=difftime(tm,time(NULL));
          if(0<diff_time)
            printf("\t抱歉，您现在该待在娘胎，请重新输入或待在娘胎(YYYY-MM-DD):_\b");
          else if(0==diff_time){
            printf("\t您的诞生将会给世间带来美好，生日快乐\n");
            break;
          }
          else{
            //格式和时间都正确，跳出输入循环
            //if((month==birth_tm->tm_mon+1)&&(day==now_tm->tm_mday))
             // printf("\t生日快乐\n");
            break;
          }
        }
      }
      else
        printf("\t请大佬按照小弟给出的格式输入(YYYY-MM-DD):_\b");
      memset(new_birth,'\0',sizeof(new_birth));
    }

    //生日输入成功，输入电话
    printf("\t电话:_\b");
    input_phone(new_phone,14);
    //电话输入成功，输入座右铭
    printf("\t座右铭(上限50字):");
    input_motto(new_motto,50);
    //开始更新账户信息
    //检测座右铭中是否包含单引号和分号
    char quotation_marks='\'';
    if(strchr(new_motto,'\''))
      quotation_marks='"';
    if(strchr(new_motto,';'))
      mysql_query(&mysql,"delimiter //");
    //这里的profile没有用预编译，存在潜在危险
    snprintf(dest,300,"update %s_profile set sex='%s',birth='%s',phone='%s',motto=%c%s%c where account='%s'",login_name,new_sex,new_birth,new_phone,quotation_marks,new_motto,quotation_marks,account_name);
    if(!mysql_query(&mysql,dest)){
      //更新成功
      puts("\t更新成功，按回车继续...");
      //显示更新后的信息
    }
    else{
      puts("\t更新失败，按回车继续...");
      puts(mysql_error(&mysql));
    }
    if(strchr(new_motto,';'))
      mysql_query(&mysql,"delimiter ;");
    mysql_free_result(result);
  }
  else{
    puts("\t数据库发生错误，按回车继续...");
    //puts(mysql_error(&mysql));
  }
  getchar();
  return;
}
