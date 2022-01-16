#include <string.h>
#include "mysql.h"
#include "db_error.h"

void create_db_user(MYSQL * con,char * db_username,char * db_user_password,char * db_hostname)
{
    char sql_create_user[128]="CREATE USER ";
    strcat(sql_create_user,db_username);
    strcat(sql_create_user,"@");
    strcat(sql_create_user,db_hostname);
    strcat(sql_create_user," IDENTIFIED BY '");
    strcat(sql_create_user,db_user_password);
    strcat(sql_create_user,"'");
    if(mysql_query(con,sql_create_user))
    {
        db_error(con);
    }
}
