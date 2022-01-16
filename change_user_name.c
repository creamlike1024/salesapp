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

int change_user_name_window();
int change_user_name_callback(int rtv);

int change_user_name(MYSQL * con,int executor)
{
    int rtv=CMD_UNDEFINED;
    while(1)
    {
        rtv=change_user_name_window();
        rtv=change_user_name_callback(rtv);
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
                printf("操作：修改用户姓名\n");
                printf("输入用户 ID：\n");
                scanf("%d",&id);
                row_num=find_user_id(con,id);
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
            char sql_change_user_name[128]="UPDATE USERS SET NAME='";
            char name[128]="";
            printf("输入用户姓名\n");
            get_str(&name);
            strcat(sql_change_user_name,name);
            strcat(sql_change_user_name,"' WHERE ID=");
            char user_id[64]="";
            itoa(get_user_id(con,row_num),user_id,10);  //将get_user_id返回的整型 id 转为字符串
            strcat(sql_change_user_name,user_id);
            if(mysql_query(con,sql_change_user_name))
            {
                db_error(con);
            }
            printf("修改成功\n");
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
                printf("操作：修改用户姓名\n");
                printf("输入用户名\n");
                get_str(&username);
                row_num=find_username(con,&username);
                if(RTV_FAILED==row_num)
                {
                    printf("未找到用户\n");
                    wait_for_enter();
                    continue;
                }
                if(USER_ROLE_ADMIN!=executor)
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
            char sql_change_user_name[128]="UPDATE USERS SET NAME='";
            char name[128]="";
            printf("输入用户姓名\n");
            get_str(&name);
            strcat(sql_change_user_name,name);
            strcat(sql_change_user_name,"' WHERE ID=");
            char user_id[64]="";
            itoa(get_user_id(con,row_num),user_id,10);  //将get_user_id返回的整型 id 转为字符串
            strcat(sql_change_user_name,user_id);
            if(mysql_query(con,sql_change_user_name))
            {
                db_error(con);
            }
            printf("修改成功\n");
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
int change_user_name_window()
{
    draw_window();
    printf("修改用户姓名\n\n");
    printf("(1)通过 ID\n");
    printf("(2)通过用户名\n");
    printf("(0)返回\n");
    int rtv=get_cmd();
    return rtv;
}
int change_user_name_callback(int rtv)
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
