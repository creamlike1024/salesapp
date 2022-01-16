#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql.h"
#include "get_input.h"
#include "common.h"
#include "draw_window.h"
#include "wait_for_enter.h"
#include "db_query.h"
#include "db_error.h"
#include "user_info.h"
#include "unknown_cmd.h"

int enable_user_window();
int enable_user_callback(int rtv);

int enable_user(MYSQL * con,int executor)
{
    int rtv=CMD_UNDEFINED;
    while(1)
    {
        rtv=enable_user_window();
        rtv=enable_user_callback(rtv);
        if(CMD_UNKNOWN==rtv)
        {
            unknown_cmd();
            continue;
        }
        if(CMD_BY_ID==rtv)
        {
            rtv=RTV_FAILED;
            int row_num=-1;
            while(1)
            {
                draw_window();
                int id;
                printf("操作：启用用户\n");
                printf("输入用户 ID：\n");
                scanf("%d",&id);
                row_num=find_user_id(con,id);
                if(USER_ROLE_SELLER==executor)
                {
                    if(get_user_role(con,row_num)!=USER_ROLE_CUSTOMER)
                    {
                        printf("你没有权限操作这个用户！\n");
                        wait_for_enter();
                        continue;
                    }
                }
                break;
            }
            char sql_enable_user[128]="UPDATE USERS SET STATUS=1 WHERE ID=";
            char user_id[64]="";
            itoa(get_user_id(con,row_num),user_id,10);  //将get_user_id返回的整型 id 转为字符串
            strcat(sql_enable_user,user_id);
            if(mysql_query(con,sql_enable_user))
            {
                db_error(con);
            }
            printf("启用成功\n");
            rtv=RTV_SUCCESS;
            wait_for_enter();
            return rtv;
        }
        if(CMD_BY_USERNAME==rtv)
        {
            rtv=RTV_FAILED;
            int row_num=-1;
            while(1)
            {
                draw_window();
                char username[128]="";
                printf("操作：启用用户\n");
                printf("输入用户名\n");
                get_str(&username);
                row_num=find_username(con,&username);
                if(RTV_FAILED==row_num)
                {
                    printf("未找到用户\n");
                    wait_for_enter();
                    continue;
                }
                if(USER_ROLE_SELLER==executor)
                {
                    if(get_user_role(con,row_num)!=USER_ROLE_CUSTOMER)
                    {
                        printf("你没有权限操作这个用户！\n");
                        wait_for_enter();
                        continue;
                    }
                }
                break;
            }
            char sql_enable_user[128]="UPDATE USERS SET STATUS=1 WHERE ID=";
            char user_id[64]="";
            itoa(get_user_id(con,row_num),user_id,10);  //将get_user_id返回的整型 id 转为字符串
            strcat(sql_enable_user,user_id);
            if(mysql_query(con,sql_enable_user))
            {
                db_error(con);
            }
            printf("启用成功\n");
            rtv=RTV_SUCCESS;
            wait_for_enter();
            return rtv;
        }
        if(CMD_BACK==rtv)
        {
            break;
        }
    }
    return rtv;

}
int enable_user_window()
{
    draw_window();
    printf("启用用户\n\n");
    printf("(1)通过 ID\n");
    printf("(2)通过用户名\n");
    printf("(0)返回\n");
    int rtv=get_cmd();
    return rtv;
}
int enable_user_callback(int rtv)
{
    switch(rtv)
    {
    case 1:
        rtv=CMD_BY_ID;
        break;
    case 2:
        rtv=CMD_BY_USERNAME;
        break;
    case 0:
        rtv=CMD_BACK;
        break;
    default:
        rtv=CMD_UNKNOWN;
        break;
    }
    return rtv;
}
