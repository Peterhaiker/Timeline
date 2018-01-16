/* home_menu.c
 * Copyright (C) 2018-01-16 12:45 
 * author:peterhaiker
 * email:vim.memory@gmail.com
 *
 * Distributed under terms of the MIT license.
 * Describe:专为主页设置的菜单导航
 */

#include<stdio.h>
#include"../header/timeline.h"

void home_menu(void)
{
  puts("\t" Format_Double_Symbol);
  puts("\t|                      *菜*单*导*航*                       |");
  puts("\t|                                                          |");
  puts("\t| a:账户相关     b:好友相关      c:事件相关     d:退出     |");
  printf("\n\t请选择:_\b");
  char ch;
  while(1!=scanf("%[a-d]",&ch)){
    while('\n'!=getchar());
    printf("\t                     输入不合法，请重新选择:_\b");
  }
  while('\n'!=getchar());

  switch(ch){
    case 'a':show_profile();break;
//    case 'b':list_fri();break;
//    case 'c':all_timeline();break;
    case 'd':exit(EXIT_SUCCESS);break;
    default:break;
  }
  return;
}
