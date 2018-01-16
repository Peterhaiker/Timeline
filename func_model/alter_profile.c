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
      while(strcmp(new_sex,"男")&&strcmp(new_sex,"女")){
        //输入不合法
        puts(new_sex);
        printf("\t请输入正确的格式(男/女):_\b");
        fgets(new_sex,3,stdin);
        new_sex[strlen(new_sex)-1]='\0';
      }
      //性别输入成功，输入生日
      printf("\t生日(YYYY-MM-DD):_\b");
      fgets(new_birth,15,stdin);
      new_birth[strlen(new_birth)-1]='\0';
      //if(//输入不合法时的处理，包括输入非数字，格式不对或超过当前日期)

      //生日输入成功，输入电话
      printf("\t电话:_\b");
      fgets(new_phone,14,stdin);
      new_phone[strlen(new_phone)-1]='\0';
      //对不合法输入的处理

      //电话输入成功，输入座右铭
      printf("\t座右铭(上限50字):");
      fgets(new_motto,50,stdin);
      new_motto[strlen(new_motto)-1]='\0';

      //开始更新账户信息
      snprintf(dest,200,"update %s_profile set sex='%s',birth='%s',phone='%s',motto='%s'",login_name,new_sex,new_birth,new_phone,new_motto);

      if(!mysql_query(&mysql,dest)){
        //更新成功
        puts("\t更新成功");
        //显示更新后的信息
      }
      else
        puts("\t更新失败");
      mysql_free_result(result);
    }
    else{
      puts("\t数据库发生错误，按回车继续...");
      getchar();
    }
    mysql_close(&mysql);
  }
  return;
}
