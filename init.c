#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql.h"
#include "get_input.h"
#include "db_error.h"
#include "init.h"
#include "wait_for_enter.h"

int init()
{
    system("cls");
    printf("销售管理系统——初始化程序\n\n");
    printf("Mariadb 客户端版本:%s\n",mysql_get_client_info);
    printf("\n");
    printf("说明：\n");
    printf("在首次使用销售管理系统之前，使用本程序进行数据库初始化\n");
    printf("继续之前，需要 mariadb 已经安装\n");
    printf("\n");
    printf("请输入 mariadb 服务器的地址\n");
    printf("如果 mariadb 服务器安装在本地，输入 localhost 即可\n");
    char db_hostname[128]="";
    get_str(&db_hostname);
    printf("请输入 root 密码：");
    char db_root_password[128]="";
    get_str(&db_root_password);

    MYSQL *con = mysql_init(NULL);  //初始化指针
    if (con == NULL)
    {
        db_error(con);
    }
    if (mysql_real_connect(con, db_hostname, "root", db_root_password,NULL, 0, NULL, 0) == NULL)
    {
        db_error(con);
    }
    printf("成功登录了 mariadb 服务器。\n");

    printf("请输入创建的数据库名称\n");
    char db_name[128]="";
    get_str(&db_name);
    create_db(con,&db_name);
    printf("成功创建了数据库\n");

    printf("将创建一个普通用户并给予该数据库的所有权限，请输入用户名\n");
    char db_username[128]="";
    get_str(&db_username);
    printf("输入该用户的密码");
    char db_user_password[128]="";
    get_str(&db_user_password);
    create_db_user(con,&db_username,&db_user_password,&db_hostname);
    printf("创建用户成功。\n");
    grant_priviliges(con,&db_name,&db_username,&db_hostname);
    printf("成功设置权限。\n");
    printf("开始初始化数据库......\n");
    db_init(con,&db_name);
    printf("数据库初始化完成。\n");
    mysql_close(con);
    wait_for_enter();
    return 0;
}
