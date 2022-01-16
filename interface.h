#ifndef CMD_H_INCLUDED
#define CMD_H_INCLUDED

#include "mysql.h"

#define LOGIN_CMD_EXIT 10
#define LOGIN_CMD_LOGIN 11

#define APPMAIN_CMD_MAIN_INTERFACE 21
#define APPMAIN_CMD_INIT 22
#define APPMAIN_CMD_ABOUT 23
#define APPMAIN_CMD_EXIT 20

#define AI_CMD_USER_LIST 31
#define AI_CMD_USER_ADD 32
#define AI_CMD_USER_RM 33
#define AI_CMD_USER_ENABLE 34
#define AI_CMD_USER_DISABLE 35
#define AI_CMD_USER_CHANGE_USERNAME 36
#define AI_CMD_USER_CHANGE_PWD 37
#define AI_CMD_USER_CHANGE_NAME 38
#define AI_CMD_EXIT 30

#define SI_CMD_CHECKOUT 41
#define SI_CMD_CUSTOMER_ADD 42
#define SI_CMD_CUSTOMER_MOD 43
#define SI_CMD_GOOD_LIST 44
#define SI_CMD_GOOD_QUERY 45
#define SI_CMD_GOOD_ADD 46
#define SI_CMD_GOOD_MOD 47
#define SI_CMD_GOOD_RM 48
#define SI_CMD_EXIT 40

#define CI_CMD_USER_MOD 51
#define CI_CMD_EXIT 50

#define CM_MOD_USERNAME 61
#define CM_MOD_PASSWORD 62
#define CM_MOD_NAME 63
#define CM_MOD_DEL 64

#define CASHIER_CMD_NEW_ORDER 71

#define GM_CMD_CHANGE_GOOD_CODE 81
#define GM_CMD_CHANGE_GOOD_NAME 82
#define GM_CMD_CHANGE_GOOD_PURCHASEPRICE 83
#define GM_CMD_CHANGE_GOOD_PRICE 84

void about();
//显示关于信息

int admin_interface(MYSQL * con,int row_num);
//管理员控制台

int appmain();
//初始界面

int cashier(MYSQL * con);
//收银界面

int customer_interface(MYSQL * con,int row_num);
//顾客界面

int customer_mod(MYSQL * con,int role);
//修改顾客信息界面

int good_mod(MYSQL * con);
//商品信息修改界面

int login_interface(MYSQL * con);
//用户登录界面

void login_to_db();
//数据库登录界面

int query_good(MYSQL * con);
//商品查询界面

int seller_interface(MYSQL * con,int row_num);
//售货员控制台

int user_role_select(MYSQL * con);
//添加用户的角色选择界面


#endif // CMD_H_INCLUDED
