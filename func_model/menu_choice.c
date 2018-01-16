/* menu_choice.c
 * Copyright (C) 2018-01-16 12:45 
 * author:peterhaiker
 * email:vim.memory@gmail.com
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
#include"../header/timeline.h"

void menu_choice(void)
{
  puts("\t" Format_Double_Symbol);
  puts("\t|                      *菜*单*导*航*                       |");
  puts("\t|                                                          |");
  puts("\t| a:返回主页     b:账户资料      c:修改资料     d:退出登录 |");
  puts("\t| e:搜索好友     f:添加好友      g:删除好友     h:好友名单 |");
  puts("\t| i:增加事件     j:修改事件      k:删除事件     l:注销账户 |");
  puts("\t| q:退出                                                   |");
  printf("\n\t请选择:_\b");
  char ch;
  while(1!=scanf("%[a-k,q]",&ch)){
    while('\n'!=getchar());
    printf("\t                     输入不合法，请重新选择:_\b");
  }
  while('\n'!=getchar());

  switch(ch){
    case 'a':home();break;
    case 'b':show_profile();break;
    case 'c':alter_profile();break;
    case 'd':sign_out();break;
//    case 'e':search_fri();break;
//    case 'f':add_fri();break;
//    case 'g':del_fri();break;
//    case 'h':list_fri();break;
//    case 'i':add_timeline();break;
//    case 'j':alter_timeline();break;
//    case 'k':del_timeline();break;
//    case 'l':del_account();break;
    case 'q':exit(EXIT_SUCCESS);break;
    default:break;
  }
  exit(EXIT_SUCCESS);
}
