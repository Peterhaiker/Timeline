/*
 * input_account.c
 * Copyright (C) 2018-01-29 19:56 
 * peterhaiker <vim.memory@gmail.com>
 *
 * Distributed under terms of the MIT license.
 * Describe:
 */

#include<stdio.h>
#include<string.h>

void input_account(char name[],size_t size)
{
  while(1){
    fgets(name,size,stdin);
    if(NULL==strchr(name,'\n')){
      printf("\t名字太长了，重新输入(max 20):_\b");
      while('\n'!=getchar());
      continue;
    }
    else if(NULL!=strpbrk(name,"-#/*'\"")){
      printf("\t有不合法字符，重新输入(不可包含-#/*'\"):_\b");
      continue;
    }
    else{
      name[strlen(name)-1]='\0';
      break;
    }
  }
  return;
}
