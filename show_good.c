#include <stdio.h>
#include "mysql.h"
#include "db_error.h"

void show_good(MYSQL * con,int row_num)
{
    if(mysql_query(con,"SELECT CODE,NAME,PRICE FROM GOODS"))
    {
        db_error(con);
    }
    MYSQL_RES * result = mysql_store_result(con);
    MYSQL_ROW row;
    MYSQL_FIELD * field;
    for(int i=0; i<=row_num; i++)
    {
        row=mysql_fetch_row(result);
    }
    int num_fields=mysql_num_fields(result);
    for(int i=0; i<num_fields; i++)
    {
        field = mysql_fetch_field(result);
        printf("%s ", field->name);
    }
    printf("\n");
    for(int i=0; i<num_fields; i++)
    {
        printf("%s ",row[i]);
    }
    printf("\n\n");
    mysql_free_result(result);
}
