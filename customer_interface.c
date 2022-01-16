#include <stdio.h>
#include "mysql.h"
#include "draw_window.h"
#include "get_input.h"
#include "interface.h"
#include "common.h"
#include "user_info.h"
#include "db_query.h"
#include "unknown_cmd.h"

int ci_window(MYSQL * con,int row_num);
int ci_callback(int rtv);

int customer_interface(MYSQL * con,int row_num)
{
    int rtv=CMD_UNDEFINED;
    while(1)
    {
        rtv=ci_window(con,row_num);
        rtv=ci_callback(rtv);
        if(CMD_UNKNOWN==rtv)
        {
            unknown_cmd();
            continue;
        }
        if(CI_CMD_USER_MOD==rtv)
        {
            customer_mod(con,USER_ROLE_CUSTOMER);
            continue;
        }
        if(CI_CMD_EXIT==rtv)
        {
            break;
        }
    }
    return rtv;
}
int ci_window(MYSQL * con,int row_num)
{
    draw_window();
    char name[128]="";
    get_user_name(con,row_num,&name);
    printf("欢迎，%s\n\n",name);
    printf("今天要做什么呢\n");
    printf("(1)修改信息\n");
    printf("(0)退出登录\n");
    int rtv=get_cmd();
    return rtv;
}
int ci_callback(int rtv)
{
    switch(rtv)
    {
    case 1:
        rtv=CI_CMD_USER_MOD;
        break;
    case 0:
        rtv=CI_CMD_EXIT;
        break;
    default:
        rtv=CMD_UNKNOWN;
        break;
    }
    return rtv;
}
