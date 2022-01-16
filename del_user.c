#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql.h"
#include "common.h"
#include "draw_window.h"
#include "get_input.h"
#include "wait_for_enter.h"
#include "db_query.h"
#include "db_error.h"
#include "user_info.h"

int del_user(MYSQL * con,int executor)
{
    int rtv=RTV_FAILED;
    int id=0;
    char username[128]="";
    int row_num=-1;
    while(1)
    {
        draw_window();
        printf("操作：删除用户\n");
        printf("输入用户 ID：\n");
        scanf("%d",&id);
        printf("输入用户名：\n");
        get_str(&username);
        int row_num1=find_user_id(con,id);
        int row_num2=find_username(con,&username);
        if(row_num1==row_num2&&row_num1>=0)
        {
            if(USER_ROLE_ADMIN!=executor)
            {
                if(get_user_role(con,row_num1)!=USER_ROLE_CUSTOMER)
                {
                    printf("你没有权限删除这个用户！\n");
                    wait_for_enter();
                    continue;
                }
            }
            row_num=row_num1;
            break;
        }
        else
        {
            printf("用户名与 ID 不匹配！\n");
            wait_for_enter();
        }
    }
    char sql_del_user[128]="DELETE FROM USERS WHERE ID=";
    char user_id[64]="";
    itoa(get_user_id(con,row_num),user_id,10);
    strcat(sql_del_user,user_id);
    if(mysql_query(con,sql_del_user))
    {
        db_error(con);
    }
    printf("删除成功\n");
    rtv=RTV_SUCCESS;
    wait_for_enter();
    return rtv;
}
