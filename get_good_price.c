#include <stdlib.h>
#include "mysql.h"
#include "db_error.h"

float get_good_price(MYSQL * con,int row_num)
{
    float rtv;
    if(mysql_query(con,"SELECT PRICE FROM GOODS"))
    {
        db_error(con);
    }
    MYSQL_RES * result = mysql_store_result(con);
    MYSQL_ROW row;
    for(int i=0;i<=row_num; i++)
    {
        row=mysql_fetch_row(result);
    }
    rtv=atof(row[0]);
    mysql_free_result(result);
    return rtv;
}
