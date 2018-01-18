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

int home(void)
{
  int return_value=-1;
  while(1){
    return_value=-1;
    system("reset");
    char dest[200]={'\0'};//存储sql语句
    //连接数据库成功,设置默认字符集并取出事件集
    mysql_set_character_set(&mysql,"utf8");
    if(result=mysql_store_result(&mysql)){
      //取结果集失败
      fprintf(stderr,"\t数据库发生错误，按回车继续...");
      getchar();
      exit(EXIT_FAILURE);
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
        format_timeline(result);
        mysql_free_result(result);
        //显示菜单
        puts("\t" Format_Double_Symbol);
        puts("\t|                     *菜*单*导*航*                        |");
        puts("\t|                                                          |");
        puts("\t| a:账户相关      b:好友相关      c:事件相关      d:退出   |");
        printf("\n\t请选择:_\b");
        char ch;
        while(1!=scanf("%[a-d]",&ch)){
          while('\n'!=getchar());
          printf("\t输入不合法，请重新选择:_\b");
        }
        while('\n'!=getchar());

        switch(ch){
          case 'a':return_value=show_profile();break;
          case 'b':list_fri();break;
          case 'c':all_timeline();break;
          case 'd':exit(EXIT_SUCCESS);break;
          default:break;
        }
        if(1==return_value)
          return 1;//返回到登录界面
      }
      else{
        //查询语句执行失败或返回结果集失败
        fprintf(stderr,"\t|              获取事件失败，按回车继续...                |");
        puts(mysql_error(&mysql));
        getchar();
        exit(EXIT_FAILURE);
      }
    }
  }
  exit(EXIT_SUCCESS);
}
