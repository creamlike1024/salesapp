#include <stdio.h>
#include "mysql.h"
#include "db_error.h"

void connect_to_db(MYSQL * con,char * db_hostname,char * db_username,char * db_user_password,char * db_name)
{
    if (con == NULL)
    {
        db_error(con);
    }
    if (mysql_real_connect(con, db_hostname, db_username, db_user_password, db_name, 0, NULL, 0) == NULL)
    {
        db_error(con);
    }
}
