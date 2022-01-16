#include <stdio.h>
#include "mysql.h"
#include "draw_window.h"
#include "get_input.h"
#include "common.h"
#include "interface.h"
#include "db_update.h"
#include "unknown_cmd.h"

int gm_window();
int gm_callback(int rtv);

int good_mod(MYSQL * con)
{
    int rtv=CMD_UNDEFINED;
    while(1)
    {
        rtv=gm_window();
        rtv=gm_callback(rtv);
        if(CMD_UNKNOWN==rtv)
        {
            unknown_cmd();
            continue;
        }
        if(rtv==GM_CMD_CHANGE_GOOD_CODE)
        {
            change_good_code(con);
            continue;
        }
        if(rtv==GM_CMD_CHANGE_GOOD_NAME)
        {
            change_good_name(con);
            continue;
        }
        if(rtv==GM_CMD_CHANGE_GOOD_PURCHASEPRICE)
        {
            change_good_purchase_price(con);
            continue;
        }
        if(rtv==GM_CMD_CHANGE_GOOD_PRICE)
        {
            change_good_price(con);
            continue;
        }
        if(CMD_BACK==rtv)
        {
            break;
        }
    }
    return rtv;
}
int gm_window()
{
    draw_window();
    printf("(1)修改商品条码\n");
    printf("(2)修改商品名称\n");
    printf("(3)修改商品进价\n");
    printf("(4)修改商品售价\n");
    printf("(0)返回\n");
    int rtv=get_cmd();
    return rtv;
}
int gm_callback(int rtv)
{
    switch(rtv)
    {
    case 1:
        rtv=GM_CMD_CHANGE_GOOD_CODE;
        break;
    case 2:
        rtv=GM_CMD_CHANGE_GOOD_NAME;
        break;
    case 3:
        rtv=GM_CMD_CHANGE_GOOD_PURCHASEPRICE;
        break;
    case 4:
        rtv=GM_CMD_CHANGE_GOOD_PRICE;
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
