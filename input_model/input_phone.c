/*
 * input_phone.c
 * Copyright (C) 2018-01-29 20:36 
 * peterhaiker <vim.memory@gmail.com>
 *
 * Distributed under terms of the MIT license.
 * Describe:
 */

#include<stdio.h>
#include<string.h>
#include<ctype.h>

void input_phone(char phone[],size_t size)
{
  while(1){
phone_again:fgets(phone,size,stdin);
            if(NULL==strchr(phone,'\n')){
              printf("\t你不要以为我没读过书，有这么长的电话吗?重输:_\b");
              while('\n'!=getchar());
            }
            else{
              phone[strlen(phone)-1]='\0';
              for(int i=0;phone[i]!='\0';i++){
                if(!isdigit(phone[i])){
                  printf("\t输入不合法，请重新输入电话:_\b");
                  goto phone_again;
                }
              }
              break;
            }
  }
  return;
}
