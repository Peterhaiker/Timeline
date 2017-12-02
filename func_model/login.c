/*
 * login.c
 * Copyright (C) 2017-12-02 00:41 
 * author  Peterhaiker 
 * email   <vim.memory@gmail.com>
 *
 * description:
 */

#include "stdio.h"
#include"../header/timeline.h"

void login_in(void);
void sign_up(void);

void login(void)
{
  puts("\t\tWelcome to Timeline");
  puts("\t\t1:login   2:sign up");
  int i;
  while(1==scanf("%d",&i)){
    while('\n'!=getchar());  //clear input buffer

    switch(i){
      case 1:login_in();break;
      case 2:sign_up();break;
      default:puts("invalid input,try again:");
    }
  }
}

void login_in(void)
{

}

void sign_up(void)
{

}
