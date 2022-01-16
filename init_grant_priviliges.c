#include <string.h>
#include "mysql.h"
#include "db_error.h"

void grant_priviliges(MYSQL * con,char * db_name,char * db_username,char * db_hostname)
{
    char sql_grant_priviliges[128]="GRANT ALL ON ";
    strcat(sql_grant_priviliges,db_name);
    strcat(sql_grant_priviliges,".* to ");
    strcat(sql_grant_priviliges,db_username);
    strcat(sql_grant_priviliges,"@");
    strcat(sql_grant_priviliges,db_hostname);
    if(mysql_query(con,sql_grant_priviliges))
    {
        db_error(con);
    }
}
