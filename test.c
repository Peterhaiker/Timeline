/*
 * test.c
 * Copyright (C) 2018-01-28 13:03 
 * peterhaiker <vim.memory@gmail.com>
 *
 * Distributed under terms of the MIT license.
 * Describe:
 */

#include<stdio.h>
#include"header/timeline.h"

void test(void)
{
  if(SELECT_PASSWD_ACCOUNT)
    puts("SELECT_PASSWD_ACCOUNT");
  if(SELECT_PROFILE_ACCOUNT)
    puts("SELECT_PROFILE_ACCOUNT");
  if(SELECT_EXECUTOR)
    puts("SELECT_EXECUTOR");
  if(LOGIN)
    puts("LOGIN");
  if(ADD_ACCOUNT)
    puts("ADD_ACCOUNT");
  if(DEL_ACCOUNT)
    puts("DEL_ACCOUNT");
  if(DEL_EVENT)
    puts("DEL_EVENT");
  if(DEL_PROFILE)
    puts("DEL_PROFILE");
  if(INS_PROFILE)
    puts("INS_PROFILE");
  if(INS_EVENT)
    puts("INS_EVENT");
  puts("test finished");
  return;
}
