#include <string.h>
#include "mysql.h"
#include "db_error.h"
#include "common.h"

int find_good_name(MYSQL * con,char * good_name)
{
    int rtv=RTV_FAILED;
    if(mysql_query(con,"SELECT NAME FROM GOODS"))
    {
        db_error(con);
    }
    MYSQL_RES * result = mysql_store_result(con);
    MYSQL_ROW row;
    for(int i=0;(row=mysql_fetch_row(result)); i++)
    {
        if(strcmp(row[0],good_name)==0)
        {
            rtv=i;
            break;
        }
    }
    mysql_free_result(result);
    return rtv;
}
