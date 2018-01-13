/*
 * login.c
 * Copyright (C) 2017-12-02 00:41 
 * author  Peterhaiker 
 * email   <vim.memory@gmail.com>
 *
 * description:
 */

#include<stdio.h>
#include"../header/timeline.h"

void login_in(void);
void sign_up(void);

void login(void)
{
  system("reset");
  puts("\t" Format_Double_Symbol);
  puts("\t||\t             Welcome to Timeline                  ||");
  puts("\t" Format_Double_Symbol);
  puts("\t\t             1:login   2:sign up");
  printf("\t请选择:_\b");
  char ch;
  while(1!=scanf("%[12]",&ch)){
    while('\n'!=getchar());
    printf("\t错误输入!!!请重新选择:_\b");
  }
  while('\n'!=getchar());

  switch(ch){
    case '1':login_in();break;
    case '2':sign_up();break;
  }
  return;
}

void login_in(void)
{
  char name[50]={'\0'};
  printf("name:___\b\b\b");
  while(NULL==fgets(name,50,stdin))
    ;
  char passwd[50]={'\0'};
  printf("passwd:___\b\b\b");
  while(NULL==fgets(passwd,50,stdin))
    ;
  return;
}

void sign_up(void)
{
  return;
}
