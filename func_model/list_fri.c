/* list_fri.c
 * Copyright (C) 2018-01-16 16:50 
 * author:peterhaiker
 * email:vim.memory@gmail.com
 *
 * Distributed under terms of the MIT license.
 * Describe:列出所有保存的好友
 */

#include<stdio.h>
#include<ctype.h>
#include"../header/timeline.h"

void list_fri(void)
{
  char dest[200]={'\0'};
  mysql_set_character_set(&mysql,"utf8");
  while(1){
    system("reset");
    snprintf(dest,200,"select * from %s_profile where account<>'%s'",login_name,login_name);
    puts(dest);
    if((!mysql_query(&mysql,dest))&&(NULL!=(result=mysql_store_result(&mysql)))){
      //sql语句执行成功且获取到结果集
      puts("\t" Format_Double_Symbol);
      puts("\t|                                                     *朋*友*列*表*                                                    |");
      if(0<mysql_num_rows(result)){
        while(row=mysql_fetch_row(result)){
          puts("\t" Format_Single_Symbol);
          printf("\t|姓名:%-40s性别:%-39s\n",row[1],row[2]?row[2]:"未知");
          printf("\t|生日:%-47s电话:%-61s\n",row[3]?row[3]:"未知",row[4]?row[4]:"未知");
          printf("\t|座右铭:%-115s\n",row[5]?row[5]:"未知");
        }
      }
      else
        printf("\t                                                        暂无好友\n");
      mysql_free_result(result);
      //显示菜单
      puts("\t" Format_Double_Symbol);
      puts("\t|                                                    *菜*单*导*航*                                                     |");
      puts("\t|                                                                                                                      |");
      puts("\t|             a:搜索好友                b:添加好友                     c:删除好友                r:返回主页            |");
      printf("\n\t请选择:_\b");
      char ch;
      while(1!=scanf("%[a-c,A-C,r,R]",&ch)){
        while('\n'!=getchar());
        printf("\t输入不合法，请重新选择:_\b");
      }
      while('\n'!=getchar());
      ch=tolower(ch);
      switch(ch){
        case 'a':search_fri();break;
        case 'b':add_fri();break;
        case 'c':del_fri();break;
        case 'r':return;
        default:break;
      }
    }//if
    else{
      fprintf(stderr,"\t获取朋友列表失败，按回车继续...");
      puts(mysql_error(&mysql));
      getchar();
      return;
    }
    //执行sql语句失败或未取到结果集
  }//while
  return;
}
