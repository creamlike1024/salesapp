#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mysql.h"
#include "db_error.h"
#include "db_query.h"
#include "common.h"
#include "get_input.h"
#include "draw_window.h"
#include "wait_for_enter.h"

int add_good(MYSQL * con)
{
    int rtv=RTV_FAILED;
    char code[128]="";
    char name[128]="";
    char purchase_price[128]="";
    char price[128]="";
    while(1)
    {
        draw_window();
        printf("扫入条码：\n");
        get_str(&code);
        if(find_good_code(con,atoi(code))!=RTV_FAILED)
        {
            printf("条码已存在！\n");
            wait_for_enter();
            continue;
        }
        printf("请输入商品名称\n");
        get_str(&name);
        if(find_good_name(con,&name)!=RTV_FAILED)
        {
            printf("商品名称已存在！\n");
            wait_for_enter();
            continue;
        }
        break;
    }
    printf("进价：\n");
    get_str(&purchase_price);
    printf("售价：\n");
    get_str(&price);
    char sql_add_good[128]="INSERT INTO GOODS(CODE,NAME,PURCHASEPRICE,PRICE) VALUES(";
    strcat(sql_add_good,code);
    strcat(sql_add_good,",'");
    strcat(sql_add_good,name);
    strcat(sql_add_good,"',");
    strcat(sql_add_good,purchase_price);
    strcat(sql_add_good,",");
    strcat(sql_add_good,price);
    strcat(sql_add_good,")");
    if(mysql_query(con,sql_add_good))
    {
        db_error(con);
    }
    printf("添加完成。\n");
    rtv=RTV_SUCCESS;
    wait_for_enter();
    return rtv;
}
