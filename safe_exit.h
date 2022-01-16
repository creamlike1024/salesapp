#ifndef SAFE_EXIT_H_INCLUDED
#define SAFE_EXIT_H_INCLUDED

#include "mysql.h"

int safe_exit(MYSQL * con);

/*
函数名称：safe_exit
参数：MYSQL * con
返回值：无
说明：关闭数据库连接后退出程序
*/

#endif // SAFE_EXIT_H_INCLUDED
