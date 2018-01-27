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

void format_timeline(MYSQL_RES*result)
{
  assert(result);//判断传入的是否为空指针

  for(unsigned long long row_num=mysql_num_rows(result);row=mysql_fetch_row(result);){
   printf("\t|%-40s%-50s%34s|\n",row[1],row[3],row[4]);
   //格式化输出事件
       printf("\t|%.118s\n",row[2]);
   if(--row_num)
     puts("\t" Format_Single_Symbol);
  }
  return;
}
