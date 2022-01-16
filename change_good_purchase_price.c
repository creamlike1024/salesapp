#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql.h"
#include "get_input.h"
#include "common.h"
#include "draw_window.h"
#include "wait_for_enter.h"
#include "db_query.h"
#include "db_error.h"
#include "unknown_cmd.h"

int change_good_purchase_price_window();
int change_good_purchase_price_callback(int rtv);

int change_good_purchase_price(MYSQL * con)
{
    int rtv=CMD_UNDEFINED;
    while(1)
    {
        rtv=change_good_purchase_price_window();
        rtv=change_good_purchase_price_callback(rtv);
        if(CMD_UNKNOWN==rtv)
        {
            unknown_cmd();
            continue;
        }
        if(CMD_BY_CODE==rtv)
        {
            rtv=RTV_FAILED;
            int row_num=-1;
            long int code;
            while(1)
            {
                draw_window();
                printf("操作：修改商品进价\n");
                printf("扫入条码：");
                scanf("%ld",&code);
                row_num=find_good_code(con,code);
                if(RTV_FAILED==row_num)
                {
                    printf("未找到商品\n");
                    wait_for_enter();
                    continue;
                }
                break;
            }
            char sql_change_good_price[128]="UPDATE GOODS SET PURCHASEPRICE=";
            char price[128]="";
            printf("输入商品新进价\n");
            get_str(&price);
            char code_str[128]="";
            itoa(code,&code_str,10);
            strcat(sql_change_good_price,price);
            strcat(sql_change_good_price," WHERE CODE=");
            strcat(sql_change_good_price,code_str);
            if(mysql_query(con,sql_change_good_price))
            {
                db_error(con);
            }
            printf("修改成功\n");
            rtv=RTV_SUCCESS;
            wait_for_enter();
            return rtv;
        }
        if(CMD_BY_GOOD_NAME==rtv)
        {
            rtv=RTV_FAILED;
            int row_num=-1;
            while(1)
            {
                draw_window();
                char name[128]="";
                printf("操作：修改商品进价\n");
                printf("输入商品名称：");
                get_str(&name);
                row_num=find_good_name(con,&name);
                if(RTV_FAILED==row_num)
                {
                    printf("未找到商品\n");
                    wait_for_enter();
                    continue;
                }
                break;
            }
            char sql_change_good_price[128]="UPDATE GOODS SET PURCHASEPRICE=";
            char price[128]="";
            printf("输入商品新进价\n");
            get_str(&price);
            char code[128]="";
            get_good_code(con,row_num,&code);
            strcat(sql_change_good_price,price);
            strcat(sql_change_good_price," WHERE CODE=");
            strcat(sql_change_good_price,code);
            if(mysql_query(con,sql_change_good_price))
            {
                db_error(con);
            }
            printf("修改成功\n");
            rtv=RTV_SUCCESS;
            wait_for_enter();
            return rtv;
        }
        if(CMD_BACK==rtv)
        {
            break;
        }
    }
    return rtv;

}
int change_good_purchase_price_window()
{
    draw_window();
    printf("修改商品进价\n\n");
    printf("(1)通过条码\n");
    printf("(2)通过商品名称\n");
    printf("(0)返回\n");
    int rtv=get_cmd();
    return rtv;
}
int change_good_purchase_price_callback(int rtv)
{
    switch(rtv)
    {
    case 1:
        rtv=CMD_BY_CODE;
        break;
    case 2:
        rtv=CMD_BY_GOOD_NAME;
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
