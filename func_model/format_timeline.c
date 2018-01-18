/* format_timeline.c
 * Copyright (C) 2018-01-18 18:32 
 * author:peterhaiker
 * email:vim.memory@gmail.com
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
#include<string.h>
#include"../header/timeline.h"
#include<assert.h>

extern MYSQL_ROW row;

void format_timeline(MYSQL_RES*result)
{
  assert(result);//判断传入的是否为空指针

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
     puts("\t" Format_Single_Symbol);
  }
  return;
}
