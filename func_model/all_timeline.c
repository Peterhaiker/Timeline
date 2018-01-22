/* all_timeline.c
 * Copyright (C) 2018-01-18 14:48 
 * author:peterhaiker
 * email:vim.memory@gmail.com
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
#include<ctype.h>
#include"../header/timeline.h"

void all_timeline(void)
{
  char dest[200]={'\0'};
  //构造sql语句
  snprintf(dest,200,"select * from %s_event order by exec_time",login_name);
  while(1){
    system("reset");
    if(!mysql_query(&mysql,dest)&&(NULL!=(result=mysql_store_result(&mysql)))){
      //sql语句执行成功且取到结果集
      char*p_event=NULL;//指向事件字符串的指针
      int eve_char_num;//指示一个事件占用的字符数
      puts("\t" Format_Double_Symbol);
      puts("\t|                                                    *事*件*集*                                                        |");
      puts("\t|                                                                                                                      |");
      puts("\t" Format_Single_Symbol);
      format_timeline(result);//格式化输出事件集
      mysql_free_result(result);
      puts("\t" Format_Double_Symbol);
      puts("\t|                                                  *菜*单*导*航*                                                       |");
      puts("\t|                                                                                                                      |");
      puts("\t|               a:增加事件                b:修改事件                c:删除事件                d:返回主页               |");
      printf("\n\t请选择:_\b");
      char ch;
      while(1!=scanf("%[a-d,A-D]",&ch)){
        while('\n'!=getchar());
        printf("\t不要调皮好不好，重新选择:_\b");
      }
      while('\n'!=getchar());
      ch=tolower(ch);

      switch(ch){
        case 'a':add_timeline();break;
        case 'b':alter_timeline();break;
        case 'c':del_timeline();break;
        case 'd':return;
      }
    }
    else{
      //sql语句执行失败或未取到结果集
      printf("\t获取数据失败，按回车继续...");
      puts(mysql_error(&mysql));
      getchar();
    }
  }
  return;
}
