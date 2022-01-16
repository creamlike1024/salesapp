#include <stdio.h>
#include "mysql.h"
#include "draw_window.h"
#include "get_input.h"
#include "interface.h"
#include "common.h"
#include "db_query.h"
#include "db_update.h"
#include "user_info.h"
#include "unknown_cmd.h"

int ai_window(MYSQL * con,int row_num);
int ai_callback(int rtv);

int admin_interface(MYSQL * con,int row_num)
{
    int rtv=CMD_UNDEFINED;
    while(1)
    {
        rtv=ai_window(con,row_num);
        rtv=ai_callback(rtv);
        if(CMD_UNKNOWN==rtv)
        {
            unknown_cmd();
            continue;
        }
        if(AI_CMD_USER_LIST==rtv)
        {
            list_users(con);
            continue;
        }
        if(AI_CMD_USER_ADD==rtv)
        {
            user_role_select(con);
            continue;
        }
        if(AI_CMD_USER_RM==rtv)
        {
            del_user(con,USER_ROLE_ADMIN);
            continue;
        }
        if(AI_CMD_USER_ENABLE==rtv)
        {
            enable_user(con,USER_ROLE_ADMIN);
            continue;
        }
        if(AI_CMD_USER_DISABLE==rtv)
        {
            disable_user(con,USER_ROLE_ADMIN);
            continue;
        }
        if(AI_CMD_USER_CHANGE_USERNAME==rtv)
        {
            change_user_username(con,USER_ROLE_ADMIN);
            continue;
        }
        if(AI_CMD_USER_CHANGE_PWD==rtv)
        {
            change_user_pwd(con,USER_ROLE_ADMIN);
            continue;
        }
        if(AI_CMD_USER_CHANGE_NAME==rtv)
        {
            change_user_name(con,USER_ROLE_ADMIN);
            continue;
        }
        if(AI_CMD_EXIT==rtv)
        {
            break;
        }
    }
    return rtv;
}
int ai_window(MYSQL * con,int row_num)
{
    draw_window();
    char name[128]="";
    get_user_name(con,row_num,&name);
    printf("欢迎，%s\n\n",name);
    printf("管理员控制台\n\n");
    printf("(1)列出用户信息\n");
    printf("(2)添加用户\n");
    printf("(3)删除用户\n");
    printf("(4)启用用户\n");
    printf("(5)禁用用户\n");
    printf("(6)修改用户名\n");
    printf("(7)修改用户密码\n");
    printf("(8)修改用户姓名\n");
    printf("(0)退出登录\n");
    int rtv=get_cmd();
    return rtv;
}
int ai_callback(int rtv)
{
    switch(rtv)
    {
    case 1:
        rtv=AI_CMD_USER_LIST;
        break;
    case 2:
        rtv=AI_CMD_USER_ADD;
        break;
    case 3:
        rtv=AI_CMD_USER_RM;
        break;
    case 4:
        rtv=AI_CMD_USER_ENABLE;
        break;
    case 5:
        rtv=AI_CMD_USER_DISABLE;
        break;
    case 6:
        rtv=AI_CMD_USER_CHANGE_USERNAME;
        break;
    case 7:
        rtv=AI_CMD_USER_CHANGE_PWD;
        break;
    case 8:
        rtv=AI_CMD_USER_CHANGE_NAME;
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
