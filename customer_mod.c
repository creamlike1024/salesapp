#include <stdio.h>
#include "mysql.h"
#include "draw_window.h"
#include "get_input.h"
#include "interface.h"
#include "common.h"
#include "db_update.h"
#include "unknown_cmd.h"

int cm_window();
int cm_callback(int rtv);

int customer_mod(MYSQL * con,int role)
{
    int rtv=CMD_UNDEFINED;
    while(1)
    {
        rtv=cm_window();
        rtv=cm_callback(rtv);
        if(CMD_UNKNOWN==rtv)
        {
            unknown_cmd();
            continue;
        }
        if(CM_MOD_USERNAME==rtv)
        {
            change_user_username(con,role);
            continue;
        }
        if(CM_MOD_PASSWORD==rtv)
        {
            change_user_pwd(con,role);
            continue;
        }
        if(CM_MOD_NAME==rtv)
        {
            change_user_name(con,role);
            continue;
        }
        if(CM_MOD_DEL==rtv)
        {
            del_user(con,role);
            continue;
        }
        if(CMD_BACK==rtv)
        {
            break;
        }
    }
    return rtv;
}
int cm_window()
{
    draw_window();
    printf("(1)修改用户名\n");
    printf("(2)修改密码\n");
    printf("(3)修改姓名\n");
    printf("(4)删除帐号\n");
    printf("(0)返回\n");
    int rtv=get_cmd();
    return rtv;
}
int cm_callback(int rtv)
{
    switch(rtv)
    {
    case 1:
        rtv=CM_MOD_USERNAME;
        break;
    case 2:
        rtv=CM_MOD_PASSWORD;
        break;
    case 3:
        rtv=CM_MOD_NAME;
        break;
    case 4:
        rtv=CM_MOD_DEL;
        break;
    case 0:
        rtv=CMD_BACK;
        break;
    default:
        rtv=CMD_UNKNOWN;
        break;
    }
    return rtv;
}
