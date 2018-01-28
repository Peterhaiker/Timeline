/* search_fri.c
 * Copyright (C) 2018-01-18 23:08 
 * author:peterhaiker
 * email:vim.memory@gmail.com
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include"../header/timeline.h"

void search_fri(void)
{
  char dest[200]={'\0'};
  char name[20]={'\0'};
  char ch;
  mysql_set_character_set(&mysql,"utf8");
  snprintf(dest,200,"select account from %s_profile where account<>'%s'",login_name,login_name);
  if(!mysql_query(&mysql,dest)&&(NULL!=(result=mysql_store_result(&mysql)))){
    //sql语句执行成功且取到结果集
    if(0<mysql_num_rows(result)){
      printf("\t发现您的好友名单，是否显示?(y/n):_\b");
      while(1!=scanf("%[yYnN]",&ch)){
        printf("输入不合法，请重新输入:_\b");
        while('\n'!=getchar());
      }
      while('\n'!=getchar());

      ch=tolower(ch);
      if('y'==ch){
        system("reset");
        puts("\t" Format_Double_Symbol);
        puts("\t|                                                    *好*友*列*表*                                                     |");
        puts("\t|                                                                                                                      |");
        printf("\t|");
        for(int i=0;row=mysql_fetch_row(result);++i){
          if((0!=i)&&(0==i%3))
            printf("|\n\t|");
          printf("%-20s",row[0]);
        }
        puts("\n\t" Format_Single_Symbol);
      }
    }
    printf("\t请输入您想搜索的好友名字:_\b");
    while(1){
      fgets(name,20,stdin);
      if(NULL==strchr(name,'\n')){
        printf("\t名字太长了，重新输入:_\b");
        while('\n'!=getchar());
      }
      else{
        name[strlen(name)-1]='\0';
        break;
      }
    }
    //开始搜寻好友
    snprintf(dest,200,"select * from %s_profile where account='%s'",login_name,name);
    if(!mysql_query(&mysql,dest)&&(NULL!=(result=mysql_store_result(&mysql)))){
      if(0<mysql_num_rows(result)){
        //以账户列表形式显示这个好友信息和事件
        row=mysql_fetch_row(result);
        system("reset");
        puts("\t" Format_Double_Symbol);
        puts("\t|                                                     *好*友*信*息*                                                    |");
        puts("\t|                                                                                                                      |");
        printf("\t|姓名:%-50s性别:%-56s\n",row[1],row[2]?row[2]:"未知");
        printf("\t|生日:%-50s电话:%-59s\n",row[3]?row[3]:"未知",row[4]?row[4]:"未知");
        printf("\t|座右铭:%-.120s\n",row[5]?row[5]:"未知");
        puts("\t" Format_Single_Symbol);
        puts("\t|                                                      *事*件*集*                                                      |");
        puts("\t|                                                                                                                      |");
        snprintf(dest,200,"select * from %s_event where executor='%s'",login_name,name);
        if(!mysql_query(&mysql,dest)&&(NULL!=(result=mysql_store_result(&mysql)))){
          format_timeline(result);
          mysql_free_result(result);
          printf("\t按回车继续...");
          getchar();
          return;
        }
        else{
          puts("\t获取事件集失败,按回车继续...");
          getchar();
          return;
        }
      }
      else{
        puts("\t未找到您的这位好友，按回车继续...");
        getchar();
        mysql_free_result(result);
        return;
      }
    }
    else{
      printf("\t查询时发生未知错误，按回车继续...");
      getchar();
      return;
    }
  }
  else{
    printf("\t数据库发生未知错误，按回车继续...");
    getchar();
  }
  return;
}
