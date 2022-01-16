#include <string.h>
#include "mysql.h"
#include "common.h"
#include "db_error.h"

int verify_user_passwd(MYSQL * con,int row_num,char * passwd)
{
    int rtv=RTV_FAILED;
    if(mysql_query(con,"SELECT PASSWORD FROM USERS"))
    {
        db_error(con);
    }
    MYSQL_RES * result=mysql_store_result(con);
    MYSQL_ROW row;
    for(int i=0;i<=row_num;i++)
    {
        row=mysql_fetch_row(result);
    }
    if(strcmp(row[0],passwd)==0)
    {
        rtv=RTV_SUCCESS;
    }
    mysql_free_result(result);
    return rtv;
}
