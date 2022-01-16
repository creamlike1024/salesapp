#ifndef DB_ERROR_H_INCLUDED
#define DB_ERROR_H_INCLUDED

void db_error(MYSQL *con);
//数据库操作出错时的处理函数，将显示错误信息并关闭数据库连接退出程序

#endif // DB_ERROR_H_INCLUDED
