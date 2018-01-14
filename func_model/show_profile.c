/* show_profile.c
 * Copyright (C) 2018-01-14 23:12 
 * author:peterhaiker
 * email:vim.memory@gmail.com
 *
 * Distributed under terms of the MIT license.
 * Discribe:这个文件显示个人信息
 */

#include<stdio.h>
#include"../header/timeline.h"

void show_profile(void)
{
  if(!mysql_real_connect(&mysql,HOSTNAME,USERNAME,PASSWORD,DBNAME,0,NULL,0)){
    fprintf("\t获取数据失败，按回车继续...");
    return;
  }
  else{
    //连接数据库成功

  }
  system("reset");
  puts("\t" Format_Double_Symbol);
  puts("\t||                        个人信息                        ||");
  puts("\t" Format_Double_Symbol);
  
  return;
}
