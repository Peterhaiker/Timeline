/* list_fri.c
 * Copyright (C) 2018-01-16 16:50 
 * author:peterhaiker
 * email:vim.memory@gmail.com
 *
 * Distributed under terms of the MIT license.
 * Describe:列出所有保存的好友
 */

#include<stdio.h>
#include"../header/timeline.h"

extern char login_name[20];

void list_fri(void)
{
  while(1){
    system("reset");
    if(!mysql_real_connect(&mysql,HOSTNAME,USERNAME,PASSWORD,DBNAME,0,NULL,0)){
      //连接数据库失败
      fprintf(stderr,"\t                连接数据库失败，按回车继续...");
      getchar();
      return;
    }
    else{
      mysql_set_character_set(&mysql,"utf8");
      char dest[200]={'\0'};
      snprintf(dest,200,"select * from %s_profile",login_name);
      if((!mysql_query(&mysql,dest))&&(NULL!=(result=mysql_store_result(&mysql)))){
        //sql语句执行成功且获取到结果集
        puts("\t" Format_Double_Symbol);
        puts("\t|                      *朋*友*列*表*                       |");
        while(row=mysql_fetch_row(result)){
          puts("\t" Format_Single_Symbol);
          printf("\t|姓名:%-20s性别:%-19s好友数:%-6llu|\n",row[0],row[1]?row[1]:"未知",mysql_num_rows(result)-1);
          printf("\t|生日:%-17s电话:%-31s|\n",row[2]?row[2]:"未知",row[3]?row[3]:"未知");
          printf("\t|座右铭:%-55s|\n",row[4]?row[4]:"未知");
        }
        mysql_free_result(result);
        mysql_close(&mysql);
        //显示菜单
        puts("\t" Format_Double_Symbol);
        puts("\t|                       *菜*单*导*航*                      |");
        puts("\t|                                                          |");
        puts("\t| a:搜索好友      b:添加好友     c:删除好友     d:返回主页 |");
        printf("\n\t请选择:_\b");
        char ch;
        while(1!=scanf("%[a-d]",&ch)){
          while('\n'!=getchar());
          printf("\t输入不合法，请重新选择:_\b");
        }
        while('\n'!=getchar());

        switch(ch){
          //case 'a':search_fri();break;
          //case 'b':add_fri();break;
          //case 'c':del_fri();break;
          case 'd':return;
          default:break;
        }

      }//if
      else{
        //执行sql语句失败或未取到结果集
        mysql_close(&mysql);
      }//else
    }//else
  }//while
  return;
}
