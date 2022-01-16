#include <string.h>
#include "mysql.h"
#include "db_error.h"

void get_user_name(MYSQL * con,int row_num,char * name)
{
    if(mysql_query(con,"SELECT NAME FROM USERS"))
    {
        db_error(con);
    }
    MYSQL_RES * result = mysql_store_result(con);
    MYSQL_ROW row;
    for(int i=0;i<=row_num; i++)
    {
        row=mysql_fetch_row(result);
    }
    strcpy(name,row[0]);
    mysql_free_result(result);
}
