/* restore.c
 * Copyright (C) 2018-01-22 13:50 
 * author:peterhaiker
 * email:vim.memory@gmail.com
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
#include<string.h>
#include"../header/timeline.h"

void restore(void)
{
  printf("\t请输入备份文件路径:_\b");
  char sql_path[255]={'\0'};
  while(1){
    fgets(sql_path,255,stdin);
    if('\n'!=sql_path[strlen(sql_path)-1]){
      while('\n'!=getchar());
      printf("\t路径名过长，重新输入路径:_\b");
      continue;
    }
    sql_path[strlen(sql_path)-1]='\0';
    break;
  }
  char command[350]={'\0'};
  snprintf(command,350,"mysql -u %s -p timeline <%s",USERNAME,sql_path);
  if(0==system(command))
    printf("\t恢复成功，按回车继续...");
  else
    printf("\t恢复失败，按回车继续...");
  getchar();
  return;
}
