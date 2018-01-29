/*
 * input_motto.c
 * Copyright (C) 2018-01-29 20:42 
 * peterhaiker <vim.memory@gmail.com>
 *
 * Distributed under terms of the MIT license.
 * Describe:
 */

#include<stdio.h>
#include<string.h>

void input_motto(char motto[],size_t size)
{
  while(1){
    fgets(motto,size,stdin);
    if('\n'==motto[strlen(motto)-1]){
      motto[strlen(motto)-1]='\0';
      break;
    }
    else{
      printf("\t超过上限，重新输入:_\b");
      while('\n'!=getchar());
    }
  }
  return;
}
