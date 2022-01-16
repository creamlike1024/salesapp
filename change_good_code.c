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

int change_good_code_window();
int change_good_code_callback(int rtv);

int change_good_code(MYSQL * con)
{
    int rtv=CMD_UNDEFINED;
    while(1)
    {
        rtv=change_good_code_window();
        rtv=change_good_code_callback(rtv);
        if(CMD_UNKNOWN==rtv)
        {
            unknown_cmd();
            continue;
        }
        if(CMD_BY_CODE==rtv)
        {
            rtv=RTV_FAILED;
            int row_num=-1;
            long int old_code;
            while(1)
            {
                draw_window();
                printf("操作：修改商品条码\n");
                printf("输入旧条码：");
                scanf("%ld",&old_code);
                row_num=find_good_code(con,old_code);
                if(RTV_FAILED==row_num)
                {
                    printf("未找到商品\n");
                    wait_for_enter();
                    continue;
                }
                break;
            }
            char sql_change_good_code[128]="UPDATE GOODS SET CODE=";
            char code[128]="";
            printf("扫入新条码：");
            get_str(&code);
            char old_code_str[128]="";
            itoa(old_code,old_code_str,10);
            strcat(sql_change_good_code,code);
            strcat(sql_change_good_code," WHERE CODE=");
            strcat(sql_change_good_code,old_code_str);
            if(mysql_query(con,sql_change_good_code))
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
            char name[128]="";
            while(1)
            {
                draw_window();
                printf("操作：修改商品条码\n");
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
            char sql_change_good_code[128]="UPDATE GOODS SET CODE=";
            char code[128]="";
            printf("扫入新条码\n");
            get_str(&code);
            char old_code[128]="";
            get_good_code(con,row_num,&old_code);
            strcat(sql_change_good_code,code);
            strcat(sql_change_good_code," WHERE CODE=");
            strcat(sql_change_good_code,old_code);
            if(mysql_query(con,sql_change_good_code))
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
int change_good_code_window()
{
    draw_window();
    printf("修改商品条码\n\n");
    printf("(1)通过旧条码\n");
    printf("(2)通过商品名称\n");
    printf("(0)返回\n");
    int rtv=get_cmd();
    return rtv;
}
int change_good_code_callback(int rtv)
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
