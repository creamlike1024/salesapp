#ifndef DB_INIT_H_INCLUDED
#define DB_INIT_H_INCLUDED
#include "mysql.h"

int init();
//数据库初始化程序主界面

void create_db(MYSQL * con,char * db_name);
//创建给定名称的数据库

void create_db_user(MYSQL * con,char * db_username,char * db_user_password,char * db_hostname);
//创建给定用户名和密码的数据库账户

void grant_priviliges(MYSQL * con,char * db_name,char * db_username,char * db_hostname);
//为给定用户赋予给定数据库的完全访问权限

void db_init(MYSQL * con,char * db_name);
//数据库内容初始化，创建表和预设用户

#endif // DB_INIT_H_INCLUDED
