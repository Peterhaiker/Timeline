/* setting.c
 * Copyright (C) 2018-01-22 10:39 
 * author:peterhaiker
 * email:vim.memory@gmail.com
 *
 * Distributed under terms of the MIT license.
 */

#include<stdio.h>
#include<ctype.h>
#include"../header/timeline.h"

void setting(void)
{
  while(1){
    system("reset");
    printf("\t" Format_Double_Symbol);
    printf("\t|                     *设*置*                     |");
    printf("\t|                                                 |");
    printf("\t| a:备份            b:恢复             r:返回主页 |");
    printf("\t\t请选择:_\b");
    char ch;
    while(1!=scanf("%[abrABR]",&ch)){
      while('\n'!=getchar());
      printf("\t输入有误，请重新选择:_\b");
    }
    ch=tolower(ch);
    switch(ch){
      case 'a':backup();break;
      case 'b':restore();break;
      case 'r':return;break;
      default:break;
    }
  }
  return;
}
