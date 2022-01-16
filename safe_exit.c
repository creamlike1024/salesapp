#include <stdlib.h>
#include "mysql.h"

int safe_exit(MYSQL * con)
{
    mysql_close(con);
    exit(0);
}
