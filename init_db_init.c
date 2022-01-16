#include <string.h>
#include <stdio.h>
#include "mysql.h"
#include "db_error.h"
#include "get_input.h"
#include "db_query.h"
#include "common.h"

void db_init(MYSQL * con,char * db_name)
{
    char sql_use_db[128]="use ";
    strcat(sql_use_db,db_name);
    if(mysql_query(con,sql_use_db))
    {
        db_error(con);
    }
    if(mysql_query(con,"CREATE TABLE USERS(Id INT PRIMARY KEY AUTO_INCREMENT,Role INT NOT NULL,Status INT NOT NULL,Username TEXT NOT NULL,Password TEXT NOT NULL,Name TEXT)"))
    {
        db_error(con);
    }
    if(mysql_query(con,"ALTER TABLE USERS AUTO_INCREMENT=1001"))
    {
        db_error(con);
    }
    char admin_username[128]="";
    char admin_passwd[128]="";
    char admin_name[128]="";
    printf("输入管理员用户的用户名");
    get_str(&admin_username);
    printf("输入管理员用户的密码：");
    get_str(&admin_passwd);
    printf("输入管理员用户的姓名");
    get_str(&admin_name);
    char sql_insert_user_admin[128]="INSERT INTO USERS(Role,Status,Username,Password,Name) VALUES(1,1,'";
    strcat(sql_insert_user_admin,admin_username);
    strcat(sql_insert_user_admin,"','");
    strcat(sql_insert_user_admin,admin_passwd);
    strcat(sql_insert_user_admin,"','");
    strcat(sql_insert_user_admin,admin_name);
    strcat(sql_insert_user_admin,"')");
    if(mysql_query(con,sql_insert_user_admin))
    {
        db_error(con);
    }
    printf("管理员用户创建成功。\n\n");
    char seller_username[128]="";
    char seller_passwd[128]="";
    char seller_name[128]="";
    while(1)
    {
        printf("输入售货员的用户名");
        get_str(&seller_username);
        if(find_username(con,&seller_username)==RTV_FAILED)
        {
            break;
        }
        else
        {
            printf("销售员用户名不能和管理员用户名重复！\n");
            printf("按回车键后重新输入。。。");
            fflush(stdin);
            getchar();
        }
    }
    printf("输入售货员的密码");
    get_str(&seller_passwd);
    printf("输入售货员的姓名");
    get_str(&seller_name);
    char sql_insert_user_seller[128]="INSERT INTO USERS(Role,Status,Username,Password,Name) VALUES(2,1,'";
    strcat(sql_insert_user_seller,seller_username);
    strcat(sql_insert_user_seller,"','");
    strcat(sql_insert_user_seller,seller_passwd);
    strcat(sql_insert_user_seller,"','");
    strcat(sql_insert_user_seller,seller_name);
    strcat(sql_insert_user_seller,"')");
    if(mysql_query(con,sql_insert_user_seller))
    {
        db_error(con);
    }
    printf("售货员用户创建成功。\n");
    if(mysql_query(con,"CREATE TABLE GOODS(Code BIGINT PRIMARY KEY NOT NULL,Name TEXT NOT NULL,PurchasePrice FLOAT UNSIGNED NOT NULL,Price FLOAT UNSIGNED NOT NULL)"))
    {
        db_error(con);
    }
}
