#include <string.h>
#include "mysql.h"
#include "db_error.h"

void create_db(MYSQL * con,char * db_name)
{
    char sql_create_db[128]="CREATE DATABASE ";
    strcat(sql_create_db,db_name);
    if (mysql_query(con, sql_create_db))
    {
        db_error(con);
    }
}
