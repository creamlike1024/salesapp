#include <stdlib.h>
#include "mysql.h"
#include "db_error.h"

int check_user_status(MYSQL * con,int row_num)
{
    if(mysql_query(con,"SELECT STATUS FROM USERS"))
    {
        db_error(con);
    }
    MYSQL_RES * result =mysql_store_result(con);
    MYSQL_ROW row;
    for(int i=0;i<=row_num;i++)
    {
        row=mysql_fetch_row(result);
    }
    int status=atoi(row[0]);
    mysql_free_result(result);
    return status;
}
