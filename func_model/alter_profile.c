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

extern char login_name[20];
void alter_profile(void)
{
  if(!mysql_real_connect(&mysql,HOSTNAME,USERNAME,PASSWORD,DBNAME,0,NULL,0)){
    //连接数据库失败
    fprintf(stderr,"\t                  连接数据库失败，按回车继续...");
    return;
  }
  else{
    //连接成功
    mysql_set_character_set(&mysql,"utf8");
    system("reset");
    puts("\t" Format_Double_Symbol);
    puts("\t|                       *修*改*信*息*                      |");
    puts("\t" Format_Double_Symbol);
    char dest[200]={'\0'};
    //构造sql语句查出所有的用户
    snprintf(dest,200,"select * from %s_profile",login_name);
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
        puts("\t|                       *朋*友*列*表*                      |");
        puts("\t" Format_Single_Symbol);
        while(row=mysql_fetch_row(result)){
          printf("\t|姓名:%-17s    性别:%-7s   电话:%-16s|\n",row[0],row[1],row[3]);
          printf("\t|生日:%-53s|\n",row[2]);
          printf("\t|座右铭:%-55s|\n",row[4]);
          puts("\t" Format_Single_Symbol);
        }
      }
      //开始选择你要更改的朋友
      printf("\t您要更改的账户名:_\b");
      char account_name[20]={'\0'};
      char new_sex[6]={'\0'};
      char new_birth[15]={'\0'};
      char new_phone[14]={'\0'};
      char new_motto[50]={'\0'};
      fgets(account_name,20,stdin);
      account_name[strlen(account_name)-1]='\0';
      while(1){
        snprintf(dest,200,"select * from %s_profile where account='%s'",login_name,account_name);
        if((!mysql_query(&mysql,dest))&&(NULL!=(result=mysql_store_result(&mysql)))){
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
          fprintf(stderr,"\t数据库发生错误，按回车继续...");
          getchar();
          return;
        }
      }
      //账户名查找成功,输入性别
      printf("\t性别(男/女):_\b");
      fgets(new_sex,6,stdin);
      new_sex[strlen(new_sex)-1]='\0';
      while(NULL==strstr("女男",new_sex)){
        //输入不合法
        printf("\t请输入正确的格式(男/女):_\b");
        fgets(new_sex,6,stdin);
        new_sex[strlen(new_sex)-1]='\0';
      }
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
            puts(ctime(&tm));
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
      while(fgets(new_phone,14,stdin)){
        //如果输入超过14个字符则清除输入缓冲区
        if(NULL==strchr(new_phone,'\n')){
          while('\n'!=getchar());
          printf("\t你不要欺负我没读过书，有这么长的号码吗。重新输入:_\b");
        }
        else{
          new_phone[strlen(new_phone)-1]='\0';
          //对不合法输入的处理
          strtol(new_phone,&p1,10);
          if(p1!=new_phone+strlen(new_phone)){
            printf("\t请不要逗我，这是电话号码吗。重新输入:_\b");
          }
          else
            break;//输入正确，跳出循环
          memset(new_phone,'\0',sizeof(new_phone));
        }
      }


      //电话输入成功，输入座右铭
      printf("\t座右铭(上限50字):");
      fgets(new_motto,50,stdin);
      new_motto[strlen(new_motto)-1]='\0';

      //开始更新账户信息
      //检测座右铭中是否包含单引号和分号
      char quotation_marks='\'';
      if(strchr(new_motto,'\''))
        quotation_marks='"';
      if(strchr(new_motto,';'))
        mysql_query(&mysql,"delimiter //");
      snprintf(dest,200,"update %s_profile set sex='%s',birth='%s',phone='%s',motto=%c%s%c",login_name,new_sex,new_birth,new_phone,quotation_marks,new_motto,quotation_marks);
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
    }
    getchar();
    mysql_close(&mysql);
  }
  return;
}
