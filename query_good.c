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

int query_good_window();
int query_good_callback(int rtv);

int query_good(MYSQL * con)
{
    int rtv=CMD_UNDEFINED;
    while(1)
    {
        rtv=query_good_window();
        rtv=query_good_callback(rtv);
        if(CMD_UNKNOWN==rtv)
        {
            unknown_cmd();
            continue;
        }
        if(CMD_BY_CODE==rtv)
        {
            draw_window();
            if(mysql_query(con,"SELECT * FROM GOODS"))
            {
                db_error(con);
            }
            MYSQL_RES * result=mysql_store_result(con);
            MYSQL_ROW row;
            MYSQL_FIELD * field;
            long int code=0;
            printf("扫入条码\n：");
            scanf("%ld",&code);
            int row_num=find_good_code(con,code);
            if(row_num==RTV_FAILED)
            {
                printf("未查询到结果。\n");
                wait_for_enter();
                continue;
            }
            printf("\n说明：\nCODE：商品条码\n");
            printf("NAME：商品名称\n");
            printf("PURCHASEPRICE：进价\n");
            printf("PRICE：售价\n\n");
            int num_fields = mysql_num_fields(result);
            for(int i=0;i<num_fields;i++)
            {
                field = mysql_fetch_field(result);
                printf("%s ", field->name);
            }
            printf("\n");
            for(int i=0; i<=row_num; i++)
            {
                row=mysql_fetch_row(result);
            }
            for(int i=0; i<num_fields; i++)
            {
                printf("%s ",row[i]);
            }
            printf("\n");
            mysql_free_result(result);
            wait_for_enter();
        }
        if(CMD_BY_GOOD_NAME==rtv)
        {
            draw_window();
            if(mysql_query(con,"SELECT * FROM GOODS"))
            {
                db_error(con);
            }
            MYSQL_RES * result=mysql_store_result(con);
            MYSQL_ROW row;
            MYSQL_FIELD * field;
            char name[128]="";
            printf("输入商品名称\n");
            get_str(&name);
            int row_num=find_good_name(con,name);
            if(row_num==RTV_FAILED)
            {
                printf("未查询到结果。\n");
                wait_for_enter();
                continue;
            }
            printf("\n说明：\nCODE：商品条码\n");
            printf("NAME：商品名称\n");
            printf("PURCHASEPRICE：进价\n");
            printf("PRICE：售价\n\n");
            int num_fields = mysql_num_fields(result);
            for(int i=0;i<num_fields;i++)
            {
                field = mysql_fetch_field(result);
                printf("%s ", field->name);
            }
            printf("\n");
            for(int i=0; i<=row_num; i++)
            {
                row=mysql_fetch_row(result);
            }
            for(int i=0; i<num_fields; i++)
            {
                printf("%s ",row[i]);
            }
            printf("\n");
            mysql_free_result(result);
            wait_for_enter();
        }
        if(CMD_BACK==rtv)
        {
            break;
        }
    }
    return rtv;

}
int query_good_window()
{
    draw_window();
    printf("查询商品信息\n\n");
    printf("(1)通过条码\n");
    printf("(2)通过商品名称\n");
    printf("(0)返回\n");
    int rtv=get_cmd();
    return rtv;
}
int query_good_callback(int rtv)
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
