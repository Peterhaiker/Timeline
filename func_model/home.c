/* home.c
 * Copyright (C) 2018-01-16 13:21 
 * author:peterhaiker
 * email:vim.memory@gmail.com
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
#include<string.h>
#include"../header/timeline.h"

extern char login_name[50];
void home(void)
{
  system("reset");
  char dest[200]={'\0'};//存储sql语句
  if(!mysql_real_connect(&mysql,HOSTNAME,USERNAME,PASSWORD,DBNAME,0,NULL,0)){
    //连接错误
    fprintf(stderr,"\t数据库连接错误，按回车继续...");
    getchar();
    return;
  }
  else{
    //连接数据库成功,设置默认字符集并取出事件集
    mysql_set_character_set(&mysql,"utf8");
    if(result=mysql_store_result(&mysql)){
      //取结果集失败
      fprintf(stderr,"\t数据库发生错误，按回车继续...");
      getchar();
      return;
    }
    else{
      //取结果集成功,构造查询事件语句
      snprintf(dest,200,"select * from %s_event order by exec_time",login_name);
      if((!mysql_query(&mysql,dest))&&(NULL!=(result=mysql_store_result(&mysql)))){
        //查询语句成功且返回了结果集
        puts("\t" Format_Double_Symbol);
        puts("\t|          .    .    ....      ..     ..    ......         |");
        puts("\t|          .    .   .    .     . .   . .     .             |");
        puts("\t|          ......  .      .    .  . .  .      .            |");
        puts("\t|          .    .   .    .     .   .   .     .             |");
        puts("\t|          .    .    ....      .   .   .    ......         |");
        puts("\t" Format_Double_Symbol);
        puts("\t|                       *事*件*集*                         |");
        char*p_event=NULL;//指向事件字符串的指针
        int eve_char_num;//指示一个事件占用的字符数
        for(unsigned long long row_num=mysql_num_rows(result);row=mysql_fetch_row(result);){
          printf("\t|%-20s%-30s%14s|\n",row[0],row[2],row[3]);
          //格式化输出事件
          for(p_event=row[1],eve_char_num=strlen(p_event);0<eve_char_num;p_event+=58,eve_char_num-=58){
            if(eve_char_num>=58)
              printf("\t|%-.58s|\n",p_event);
            else
              printf("\t|%s\n",p_event);
          }
          if(--row_num)
            puts("\t" Format_Single_Symbol);//每个事件用单行线分隔
        }
        mysql_free_result(result);
        mysql_close(&mysql);
        menu_choice();
        return;
      }
      else{
        //查询语句执行失败或返回结果集失败
        fprintf(stderr,"\t|              获取事件失败，按回车继续...                |");
        getchar();
      }
    }
    mysql_close(&mysql);
  }
  return;
}
