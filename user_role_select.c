#include <stdio.h>
#include "mysql.h"
#include "get_input.h"
#include "user_info.h"
#include "common.h"
#include "interface.h"
#include "draw_window.h"
#include "unknown_cmd.h"
#include "db_update.h"

int user_role_select_window();
int user_role_select_callback(int rtv);

int user_role_select(MYSQL * con)
{
    int rtv=CMD_UNDEFINED;
    while(1)
    {
        rtv=user_role_select_window();
        rtv=user_role_select_callback(rtv);
        if(CMD_UNKNOWN==rtv)
        {
            unknown_cmd();
            continue;
        }
        if(USER_ROLE_ADMIN==rtv)
        {
            add_user(con,USER_ROLE_ADMIN);
            continue;
        }
        if(USER_ROLE_SELLER==rtv)
        {
            add_user(con,USER_ROLE_SELLER);
            continue;
        }
        if(USER_ROLE_CUSTOMER==rtv)
        {
            add_user(con,USER_ROLE_CUSTOMER);
            continue;
        }
        if(AI_CMD_EXIT==rtv)
        {
            break;
        }
    }
    return rtv;
}

int user_role_select_window()
{
    draw_window();
    printf("选择要添加的用户角色\n\n");
    printf("(1)管理员\n");
    printf("(2)售货员\n");
    printf("(3)顾客\n");
    printf("(0)返回\n");
    int rtv=get_cmd();
    return rtv;
}
int user_role_select_callback(int rtv)
{
    switch(rtv)
    {
    case 1:
        rtv=USER_ROLE_ADMIN;
        break;
    case 2:
        rtv=USER_ROLE_SELLER;
        break;
    case 3:
        rtv=USER_ROLE_CUSTOMER;
        break;
    case 0:
        rtv=AI_CMD_EXIT;
        break;
    default:
        rtv=CMD_UNKNOWN;
        break;
    }
    return rtv;
}
