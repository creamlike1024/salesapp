#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql.h"
#include "common.h"
#include "draw_window.h"
#include "get_input.h"
#include "wait_for_enter.h"
#include "db_query.h"
#include "db_error.h"

int del_good(MYSQL * con)
{
    int rtv=RTV_FAILED;
    long int code=0;
    char name[128]="";
    while(1)
    {
        draw_window();
        printf("操作：删除商品\n");
        printf("扫入商品条码\n：");
        scanf("%ld",&code);
        printf("输入商品名称\n");
        get_str(&name);
        int row_num1=find_good_code(con,code);
        int row_num2=find_good_name(con,name);
        if(row_num1==row_num2&&row_num1>=0)
        {
            break;
        }
        else
        {
            printf("商品名称与条码不匹配！\n");
            wait_for_enter();
        }
    }
    char sql_del_good[128]="DELETE FROM GOODS WHERE CODE=";
    char code_str[128]="";
    itoa(code,code_str,10);
    strcat(sql_del_good,code_str);
    if(mysql_query(con,sql_del_good))
    {
        db_error(con);
    }
    printf("删除成功\n");
    rtv=RTV_SUCCESS;
    wait_for_enter();
    return rtv;
}
