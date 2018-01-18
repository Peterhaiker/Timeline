/* show_profile.c
 * Copyright (C) 2018-01-14 23:12 
 * author:peterhaiker
 * email:vim.memory@gmail.com
 *
 * Distributed under terms of the MIT license.
 * Discribe:这个文件显示个人信息
 */

#include<stdio.h>
#include<string.h>
#include"../header/timeline.h"

int show_profile(void)
{
  char*sql=NULL;//存储sql语句通用部分
  char dest[200]={'\0'};//存储sql语句
  int return_value;//接收各个调用函数的返回值
  while(1){
    //构造sql语句
    snprintf(dest,200,"select * from %s_profile where account='%s'",login_name,login_name);
    //设置默认字符集
    mysql_set_character_set(&mysql,"utf8");
    //执行sql语句并取出结果集
    if((!mysql_query(&mysql,dest))&&(NULL!=(result=mysql_store_result(&mysql)))){
      //执行sql语句成功且获取结果集成功
      if(row=mysql_fetch_row(result)){
        //获取记录
        system("reset");
        //输出个人信息
        puts("\t" Format_Double_Symbol);
        puts("\t|                      *个*人*信*息*                       |");
        puts("\t|                                                          |");
        printf("|姓名:%-20s性别:%-10s好友数:%-6llu|",row[0],row[1]?row[1]:"未知",mysql_num_rows(result)-1);
        printf("\t|生日:%-20s电话:%-29s|\n",row[2]?row[2]:"未知",row[3]?row[3]:"未知");
        printf("\t|座右铭:%-50s|\n",row[4]?row[4]:"未知");
        //输出自己记录的事件
        mysql_free_result(result);
        //构造sql语句
        snprintf(dest,200,"select * from %s_event where executor='%s' order by exec_time",login_name,login_name);
        puts("\t" Format_Double_Symbol);
        puts("\t|                    * 个*人*事*件*集*                     |");
        puts("\t|                                                          |");
        //执行sql语句查询属于登录用户的所有事件
        if((!mysql_query(&mysql,dest))&&(NULL!=(result=mysql_store_result(&mysql)))){
          //执行sql语句成功且获取结果集成功
          format_timeline(result);//格式化输出事件
          mysql_free_result(result);
        }
        else
          puts("\t|               获取您的事件集失败                       |");
      }
      //显示选项菜单
      puts("\t" Format_Double_Symbol);
      puts("\t|                      *菜*单*导*航*                       |");
      puts("\t|                                                          |");
      puts("\t| a:修改账户      b:退出账户     c:删除账户     d:返回主页 |");
      printf("\n\t请选择:");
      char ch;
      while(1!=scanf("%[a-d]",&ch)){
        while('\n'!=getchar());
        printf("\t输入不合法，重新选择:");
      }
      while('\n'!=getchar());
      switch(ch){
        case 'a':alter_profile();break;
        case 'b':return 1;break;
        case 'c':return_value=del_account();break;
        case 'd':return 0;
        default:break;
      }
      if(1==return_value)//删除账户成功
        return 1;
    }
    else{
      //执行sql语句失败或获取结果集失败
      fprintf(stderr,"\t\t   获取数据失败，按回车继续:%s",mysql_error(&mysql));
      getchar();
      return 0;
    }
  }
}
