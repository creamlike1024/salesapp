#ifndef CONNECT_TO_DB_H_INCLUDED
#define CONNECT_TO_DB_H_INCLUDED

void connect_to_db(MYSQL * con,char * db_hostname,char * db_username,char * db_user_password,char * db_name);
//提供数据库服务器主机名，数据库用户名，数据库用户密码，数据库名称连接数据库


#endif // CONNECT_TO_DB_H_INCLUDED
