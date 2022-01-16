#include <stdio.h>
#include <string.h>
#include "mysql.h"
#include "db_error.h"
#include "db_query.h"
#include "common.h"
#include "user_info.h"
#include "get_input.h"
#include "draw_window.h"
#include "wait_for_enter.h"

void sql_strcat(char * sql_add_user,char * username,char * password,char * name);

int add_user(MYSQL * con,int role)
{
    int rtv=RTV_FAILED;
    char username[128]="";
    char password[128]="";
    char password2[128]="";
    char name[128]="";
    while(1)
    {
        draw_window();
        printf("请输入用户名\n");
        get_str(&username);
        if(find_username(con,&username)!=RTV_FAILED)
        {
            printf("用户名已存在！\n");
            wait_for_enter();
            continue;
        }
        printf("请输入密码\n");
        get_str(&password);
        printf("再次输入密码以确认\n");
        get_str(&password2);
        if(strcmp(password,password2)==0)
        {
            break;
        }
        else
        {
            printf("两次输入密码不一致！\n");
            wait_for_enter();
        }
    }
    printf("请输入用户姓名\n");
    get_str(&name);
    char sql_add_user[128]="INSERT INTO USERS(STATUS,ROLE,USERNAME,PASSWORD,NAME) VALUES(1,";
    switch(role)
    {
    case USER_ROLE_ADMIN:
        strcat(sql_add_user,"1,'");
        sql_strcat(&sql_add_user,&username,&password,&name);
        break;
    case USER_ROLE_SELLER:
        strcat(sql_add_user,"2,'");
        sql_strcat(&sql_add_user,&username,&password,&name);
        break;
    case USER_ROLE_CUSTOMER:
        strcat(sql_add_user,"3,'");
        sql_strcat(&sql_add_user,&username,&password,&name);
        break;
    }
    if(mysql_query(con,sql_add_user))
    {
        db_error(con);
    }
    printf("创建完成。\n");
    rtv=RTV_SUCCESS;
    wait_for_enter();
    return rtv;
}
void sql_strcat(char * sql_add_user,char * username,char * password,char * name)
{
    strcat(sql_add_user,username);
    strcat(sql_add_user,"','");
    strcat(sql_add_user,password);
    strcat(sql_add_user,"','");
    strcat(sql_add_user,name);
    strcat(sql_add_user,"')");
}
