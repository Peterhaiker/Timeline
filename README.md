欢迎来到珍谊
=================
![Timeline结构图](./Timeline结构图.png)  
### 概述  
生活中我们认识了很多人后有时候别人的生日或最近要发生的事我们总是不经意忘记，再次面对时难免有些尴尬，于是想出了这个软件  

### 功能  
#### *v1.0*  
* 拥有一般记事本记事的功能[finished]  
* 可以记录一个人的详细信息。姓名，电话，生日，座右铭等[finished]  
* 查看某人时除了可以查看它的信息还可以看看最近它做过什么重要的事以及将要做什么重要的事[finished offline version]  
* 也可以以时间线来显示你保存的所有人的最近将要做的事[finished]  
* 增加了事件错过通知[unfinished]  

#### *v1.1*  
* 增加感恩模块，记录每个人对自己提供的援助，生而为人必须学会感恩[unfinished]  
* 铃声通知[unfinished]  
* 通过本地化设置优化一下输出内容和界面[unfinished]  

#### *v2.0*  
* 增加GUI[unfinished]  
* 开启联网功能后增加添加好友功能，好友之间可以互看时间线，了解对方将要做什么(当然，前提是对方打开了给别人看的权限)[unfinished]  
* 备份恢复时调用系统的文件管理器[unfinished]  

### 依赖  
* **compiler support c99**
* **mysql version 5+**
  * ubuntu install mysql-server
      ```
      sudo apt-get install mysql-server
      ```
  * install development pakage
      ```
      sudo apt-get install mysql-client libmysqlclient-dev
      ```
* **make you mysql-server support utf8,the way below only for ubuntu**[reference link](http://dandanlove.com/2017/02/08/Ubuntu-mysql-code-error/)  
    run this command `sudo vim /etc/mysql/my.cnf` and add the below information into my.cnf
    ```
    [client]
    default-character-set=utf8
    [mysqld]
    character_set_server=utf8
    [mysql]
    default-character-set=utf8
    ```
    then,restart mysql with following two command
    ```
    /etc/init.d/mysql stop
    /etc/init.d/mysql start
    ```
    now,all step you finished.and then we make sure its come into effect with following steps
    * login to mysql server
        ```
        mysql -uroot -p
        ```
    * run mysql command
        ```
        mysql>show variables like "%char%";
        ```
        and you will success if the output look like below
        ```
        mysql> show variables like "%char%";
        +--------------------------+----------------------------+
        | Variable_name            | Value                      |
        +--------------------------+----------------------------+
        | character_set_client     | utf8                       |
        | character_set_connection | utf8                       |
        | character_set_database   | utf8                       |
        | character_set_filesystem | binary                     |
        | character_set_results    | utf8                       |
        | character_set_server     | utf8                       |
        | character_set_system     | utf8                       |
        | character_sets_dir       | /usr/share/mysql/charsets/ |
        +--------------------------+----------------------------+
        8 rows in set (0.01 sec)

        ```
