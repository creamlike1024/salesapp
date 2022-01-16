#include <stdlib.h>
#include "mysql.h"
#include "db_error.h"

int get_user_id(MYSQL * con,int row_num)
{
    int rtv;
    if(mysql_query(con,"SELECT ID FROM USERS"))
    {
        db_error(con);
    }
    MYSQL_RES * result = mysql_store_result(con);
    MYSQL_ROW row;
    for(int i=0;i<=row_num; i++)
    {
        row=mysql_fetch_row(result);
    }
    rtv=atoi(row[0]);
    mysql_free_result(result);
    return rtv;
}
