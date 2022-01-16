#ifndef DB_QUERY_H_INCLUDED
#define DB_QUERY_H_INCLUDED

#include "mysql.h"

int find_username(MYSQL * con,char * username);
//查找用户，如果用户存在则返回其行号，否则返回 RTV_FAILED

int find_user_id(MYSQL * con,int id);
//提供用户 ID，返回所在行数，未找到则返回RTV_FAILED

int find_good_code(MYSQL * con,long int code);
//提供长整型的商品条码，返回所在行数，如果未找到则返回RTV_FAILED

int find_good_name(MYSQL * con,char * good_name);
//提供商品名称，返回其所在行数，如果未找到则返回RTV_FAILED

int verify_user_passwd(MYSQL * con,int row_num,char * passwd);
//验证给定行号对应的密码是否正确，比较一致返回 RTV_SUCCESS,否则返回 RTV_FAILED

int check_user_status(MYSQL * con,int row_num);
//提供数据所在行，返回用户启用状态（0/1）

void list_users(MYSQL * con);
//列出所有用户

void list_goods(MYSQL * con);
//列出所有商品

void get_good_code(MYSQL * con,int row_num,char * code);
//提供所在行数，将对应条码存入字符数组 code

float get_good_price(MYSQL * con,int row_num);
//提供所在行数，返回对应售价

int get_user_role(MYSQL * con,int row_num);
//提供所在行数，返回用户角色

void get_user_name(MYSQL * con,int row_num,char * name);
//提供所在行数，将对应用户姓名存到字符数组 name

int get_user_id(MYSQL * con,int row_num);
//提供所在行数，返回用户 ID

void show_good(MYSQL * con,int row_num);
//提供所在行数，显示商品除进价之外的信息


#endif // DB_QUERY_H_INCLUDED
