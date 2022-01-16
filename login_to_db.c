#include <stdio.h>
#include "mysql.h"
#include "connect_to_db.h"
#include "draw_window.h"
#include "get_input.h"
#include "wait_for_enter.h"
#include "interface.h"

void login_to_db()
{
    char db_hostname[128]="";
    char db_name[128]="";
    char db_username[128]="";
    char db_user_password[128]="";
    draw_window();
    printf("登录数据库\n");
    printf("输入 mariadb 服务器主机名，如果安装在本机上请输入 localhost\n");
    get_str(&db_hostname);
    printf("输入数据库名称\n");
    get_str(&db_name);
    printf("输入数据库用户名\n");
    get_str(&db_username);
    printf("输入密码\n");
    get_str(&db_user_password);
    printf("尝试登录数据库......\n");
    MYSQL *con = mysql_init(NULL);
    connect_to_db(con,&db_hostname,&db_username,&db_user_password,&db_name);
    printf("成功连接数据库。\n");
    wait_for_enter();
    login_interface(con);
}
