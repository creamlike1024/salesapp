#include <stdio.h>
#include "mysql.h"
#include "draw_window.h"
#include "db_error.h"
#include "wait_for_enter.h"

void list_goods(MYSQL * con)
{
    draw_window();
    printf("说明：\nCODE：商品条码\n");
    printf("NAME：商品名称\n");
    printf("PURCHASEPRICE ：进价\n");
    printf("PRICE：售价\n");
    printf("\n");
    if(mysql_query(con,"SELECT CODE,NAME,PURCHASEPRICE,PRICE FROM GOODS"))
    {
        db_error(con);
    }
    MYSQL_RES * result = mysql_store_result(con);
    if(NULL==result)
    {
        db_error(con);
    }
    int num_fields = mysql_num_fields(result);  //获取行数
    MYSQL_ROW row;
    MYSQL_FIELD *field;
    while ((row = mysql_fetch_row(result)))
    {
        for(int i = 0; i < num_fields; i++)
        {
            if (i == 0)
            {
                while(field = mysql_fetch_field(result))
                {
                    printf("%s ", field->name);
                }
                printf("\n");
            }
            printf("%s ", row[i] ? row[i] : "NULL");
        }
    }
    printf("\n");
    mysql_free_result(result);
    wait_for_enter();
}
