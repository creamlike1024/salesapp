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

int si_window(MYSQL * con,int row_num);
int si_callback(int rtv);

int seller_interface(MYSQL * con,int row_num)
{
    int rtv=CMD_UNDEFINED;
    while(1)
    {
        rtv=si_window(con,row_num);
        rtv=si_callback(rtv);
        if(CMD_UNKNOWN==rtv)
        {
            unknown_cmd();
            continue;
        }
        if(SI_CMD_CHECKOUT==rtv)
        {
            cashier(con);
            continue;
        }
        if(SI_CMD_CUSTOMER_ADD==rtv)
        {
            add_user(con,USER_ROLE_CUSTOMER);
            continue;
        }
        if(SI_CMD_CUSTOMER_MOD==rtv)
        {
            customer_mod(con,USER_ROLE_SELLER);
            continue;
        }
        if(SI_CMD_GOOD_LIST==rtv)
        {
            list_goods(con);
            continue;
        }
        if(SI_CMD_GOOD_QUERY==rtv)
        {
            query_good(con);
            continue;
        }
        if(SI_CMD_GOOD_ADD==rtv)
        {
            add_good(con);
            continue;
        }
        if(SI_CMD_GOOD_MOD==rtv)
        {
            good_mod(con);
            continue;
        }
        if(SI_CMD_GOOD_RM==rtv)
        {
            del_good(con);
            continue;
        }
        if(SI_CMD_EXIT==rtv)
        {
            break;
        }
    }
    return rtv;
}
int si_window(MYSQL * con,int row_num)
{
    draw_window();
    char name[128]="";
    get_user_name(con,row_num,&name);
    printf("欢迎，%s\n\n",name);
    printf("收银员控制台\n\n");
    printf("(1)收银\n");
    printf("(2)添加顾客\n");
    printf("(3)修改顾客信息\n");
    printf("(4)列出所有商品\n");
    printf("(5)查询商品\n");
    printf("(6)添加商品\n");
    printf("(7)修改商品信息\n");
    printf("(8)移除商品\n");
    printf("(0)退出登录\n");
    int rtv=get_cmd();
    return rtv;
}
int si_callback(int rtv)
{
    switch(rtv)
    {
    case 1:
        rtv=SI_CMD_CHECKOUT;
        break;
    case 2:
        rtv=SI_CMD_CUSTOMER_ADD;
        break;
    case 3:
        rtv=SI_CMD_CUSTOMER_MOD;
        break;
    case 4:
        rtv=SI_CMD_GOOD_LIST;
        break;
    case 5:
        rtv=SI_CMD_GOOD_QUERY;
        break;
    case 6:
        rtv=SI_CMD_GOOD_ADD;
        break;
    case 7:
        rtv=SI_CMD_GOOD_MOD;
        break;
    case 8:
        rtv=SI_CMD_GOOD_RM;
        break;
    case 0:
        rtv=SI_CMD_EXIT;
        break;
    default:
        rtv=CMD_UNKNOWN;
        break;
    }
    return rtv;
}
