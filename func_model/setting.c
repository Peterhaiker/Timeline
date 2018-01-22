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

int setting(void)
{
  int return_value=-1;
  while(1){
    system("reset");
    puts("\t" Format_Double_Symbol);
    puts("\t|                                                          *设*置*                                                      |");
    puts("\t|                                                                                                                       |");
    puts("\t|                  a:备份                                  b:恢复                              r:返回主页               |");
    printf("\n\t请选择:_\b");
    char ch;
    while(1!=scanf("%[abrABR]",&ch)){
      while('\n'!=getchar());
      printf("\t输入有误，请重新选择:_\b");
    }
    while('\n'!=getchar());
    ch=tolower(ch);
    switch(ch){
      case 'a':backup();break;
      case 'b':return_value=restore();break;
      case 'r':return 0;break;
      default:break;
    }
    if(1==return_value)
      return 1;//恢复成功，重新登录
  }
  return 0;
}
