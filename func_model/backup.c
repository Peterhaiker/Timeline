/* backup.c
 * Copyright (C) 2018-01-22 10:52 
 * author:peterhaiker
 * email:vim.memory@gmail.com
 *
 * Distributed under terms of the MIT license.
 * Describe:restore all database
 */

#include<stdio.h>
#include<string.h>
#include"../header/timeline.h"

void backup(void)
{
  printf("\t请输入备份文件的路径:_\b");
  char sql_path[255]={'\0'};
  while(1){
    fgets(sql_path,255,stdin);
    if('\n'!=sql_path[strlen(sql_path)-1]){
      while('\n'!=getchar());
      printf("\t路径过长，重新输入(上限255):_\b");
      continue;
    }
    sql_path[strlen(sql_path)-1]='\0';
    break;
  }
  if('/'==sql_path[strlen(sql_path)-1])
    sql_path[strlen(sql_path)-1]='\0';
  //构造备份命令
  char command[350]={'\0'};
  snprintf(command,350,"mysqldump -u %s -p%s timeline > %s/Timeline_back.sql",USERNAME,PASSWORD,sql_path);
  if(0==system(command)){
      printf("\t备份成功，备份文件路径:%s/Timeline_back.sql\n",sql_path);
      printf("\t按回车继续...");
      }
  else
    printf("\t备份失败，按回车继续...");
  getchar();
  return;
}
