/*
 * input_sex.c
 * Copyright (C) 2018-01-29 20:03 
 * peterhaiker <vim.memory@gmail.com>
 *
 * Distributed under terms of the MIT license.
 * Describe:
 */

#include<stdio.h>
#include<string.h>

void input_sex(char sex[],size_t size)
{
  while(1){
    fgets(sex,size,stdin);
    if(NULL==strchr(sex,'\n')){
      printf("\t请按指定格式输入(男/女):_\b");
      while('\n'!=getchar());
    }
    else{
      sex[strlen(sex)-1]='\0';
      if(NULL==strstr("男女",sex)){
        printf("\t请输入指定字段(男/女):_\b");
        continue;
      }
      else
        break;
    }
  }
  return;
}
