#ifndef DB_UPDATE_H_INCLUDED
#define DB_UPDATE_H_INCLUDED

#include "mysql.h"

int add_user(MYSQL * con,int role);
//提供要添加的用户角色，进行添加用户操作

int del_user(MYSQL * con,int executor);
//提供执行者角色，进行删除用户操作

int add_good(MYSQL * con);
//添加商品

int del_good(MYSQL * con);
//删除商品

int enable_user(MYSQL * con,int executor);
//启用用户

int disable_user(MYSQL * con,int executor);
//禁用用户

int change_good_code(MYSQL * con);
//修改商品条码

int change_good_name(MYSQL * con);
//修改商品名称

int change_good_purchase_price(MYSQL * con);
//修改商品进价

int change_good_price(MYSQL * con);
//修改商品售价

int change_user_username(MYSQL * con,int executor);
//修改用户名

int change_user_pwd(MYSQL * con,int executor);
//修改用户密码

int change_user_name(MYSQL * con,int executor);
//修改用户姓名


#endif // DB_UPDATE_H_INCLUDED
