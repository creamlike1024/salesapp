#include <stdlib.h>
#include "mysql.h"
#include "db_error.h"
#include "common.h"

int find_good_code(MYSQL * con,long int code)
{
    int rtv=RTV_FAILED;
    if(mysql_query(con,"SELECT CODE FROM GOODS"))
    {
        db_error(con);
    }
    MYSQL_RES * result = mysql_store_result(con);
    MYSQL_ROW row;
    for(int i=0; (row=mysql_fetch_row(result)); i++)
    {
        if(atoi(row[0])==code)
        {
            rtv=i;
            break;
        }
    }
    mysql_free_result(result);
    return rtv;
}
