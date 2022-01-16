#include <stdio.h>
#include "mysql.h"
#include "draw_window.h"
#include "db_error.h"
#include "wait_for_enter.h"

void list_users(MYSQL * con)
{
    draw_window();
    printf("说明：\nSTATUS：1 为启用，0 为禁用\n");
    printf("ROLE：1 为管理员，2 为售货员，3 为顾客\n");
    printf("USERNAME：登录用的用户名\n");
    printf("NAME：姓名\n");
    printf("\n");
    if(mysql_query(con,"SELECT ID,ROLE,STATUS,USERNAME,NAME FROM USERS"))
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
