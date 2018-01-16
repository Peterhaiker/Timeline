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
  puts("\t|a:增加事件     b:修改事件      c:删除事件      d:修改信息 |");
  puts("\t|e:搜索好友     f:添加好友      g:删除好友      h:好友名单 |");
  puts("\t|i:返回主页     j:注销账户      k:退出登录      q:退出     |");
  printf("\n\t请选择:_\b");
  char ch;
  while(1!=scanf("%[a-k,q]",&ch)){
    while('\n'!=getchar());
    printf("\t                     输入不合法，请重新选择:_\b");
  }
  while('\n'!=getchar());

  /*switch(ch){
    case 'a':add_timeline();break;
    case 'b':alter_timeline();break;
    case 'c':del_timeline();break;
    case 'd':alter_profile();break;
    case 'e':search_fri();break;
    case 'f':add_fri();break;
    case 'g':del_fri();break;
    case 'h':list_fri();break;
    case 'i':home();break;
    case 'j':del_account();break;
    case 'k':sign_out();break;
    case 'q':exit(EXIT_SUCCESS);break;
    default:
  }*/
  exit(EXIT_SUCCESS);
}
