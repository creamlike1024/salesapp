#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "get_input.h"
#include "db_query.h"
#include "draw_window.h"
#include "interface.h"
#include "user_info.h"
#include "mysql.h"
#include "safe_exit.h"
#include "wait_for_enter.h"
#include "unknown_cmd.h"

int login_window();
int login_callback(int rtv);

static int retry_times=0;

int login_interface(MYSQL * con)
{
    int rtv=CMD_UNDEFINED;
    while(1)
    {
        rtv=login_window();
        rtv=login_callback(rtv);
        if(CMD_UNKNOWN==rtv)
        {
            unknown_cmd();
            continue;
        }
        if(LOGIN_CMD_LOGIN==rtv)
        {
            char username[128]="";
            char password[128]="";
            if(retry_times==3)
            {
                printf("登录失败已 3 次！禁止继续登录\n");
                wait_for_enter();
                continue;
            }
            draw_window();
            printf("Username");
            get_str(&username);
            printf("Password");
            get_str(&password);
            int row_num=find_username(con,&username);
            if(row_num!=RTV_FAILED)
            {
                if(RTV_SUCCESS==verify_user_passwd(con,row_num,&password))
                {
                    if(check_user_status(con,row_num))
                    {
                        int role=get_user_role(con,row_num);
                        switch(role)
                        {
                        case USER_ROLE_ADMIN:
                            admin_interface(con,row_num);
                            break;
                        case USER_ROLE_SELLER:
                            seller_interface(con,row_num);
                            break;
                        case USER_ROLE_CUSTOMER:
                            customer_interface(con,row_num);
                            break;
                        }
                    }
                    else
                    {
                        printf("用户被禁用\n");
                        wait_for_enter();
                        continue;
                    }
                }
                else
                {
                    printf("用户名或密码错误！\n");
                    retry_times++;
                    wait_for_enter();
                }
            }
            else
            {
                printf("用户名或密码错误！\n");
                retry_times++;
                wait_for_enter();
            }
        }
        if(LOGIN_CMD_EXIT==rtv)
        {
            safe_exit(con);
        }
    }

    return rtv;
}
int login_window()
{
    draw_window();
    printf("(1)用户登录\n");
    printf("(0)退出\n");
    int rtv=get_cmd();
    return rtv;
}
int login_callback(int rtv)
{
    switch(rtv)
    {
    case 1:
        rtv=LOGIN_CMD_LOGIN;
        break;
    case 0:
        rtv=LOGIN_CMD_EXIT;
        break;
    default:
        rtv=CMD_UNKNOWN;
        break;
    }
    return rtv;
}
