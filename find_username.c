#include <string.h>
#include "mysql.h"
#include "db_error.h"
#include "common.h"

int find_username(MYSQL * con,char * username)
{
    int rtv=RTV_FAILED;
    if(mysql_query(con,"SELECT USERNAME FROM USERS"))
    {
        db_error(con);
    }
    MYSQL_RES * result = mysql_store_result(con);
    MYSQL_ROW row;
    for(int i=0;(row=mysql_fetch_row(result)); i++)
    {
        if(strcmp(row[0],username)==0)
        {
            rtv=i;
            break;
        }
    }
    mysql_free_result(result);
    return rtv;
}
