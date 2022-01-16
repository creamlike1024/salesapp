#include <stdio.h>
#include <stdlib.h>
#include "mysql.h"

void db_error(MYSQL *con)
{
    printf("发生错误！\n");
    fprintf(stderr, "%s\n", mysql_error(con));  //输出 Mariadb 的错误信息
    mysql_close(con);
    printf("按任意键退出。。。");
    fflush(stdin);
    getchar();
    exit(1);
}
