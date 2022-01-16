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

int change_user_username(MYSQL * con,int executor)
{
    int rtv=RTV_FAILED;
    int row_num=-1;
    while(1)
    {
        draw_window();
        int id=0;
        char username[128]="";
        printf("操作：修改用户名\n");
        printf("输入用户 ID：\n");
        scanf("%d",&id);
        printf("输入原来的用户名：\n");
        get_str(&username);
        int row_num1=find_user_id(con,id);
        int row_num2=find_username(con,&username);
        if(row_num1==row_num2&&row_num1>=0)
        {
            if(USER_ROLE_ADMIN!=executor)
            {
                if(get_user_role(con,row_num1)!=USER_ROLE_CUSTOMER)
                {
                    printf("你没有权限操作这个用户！\n");
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
    char new_username[128]="";
    char new_username2[128]="";
    while(1)
    {
        printf("请输入新用户名\n");
        get_str(&new_username);
        printf("再次输入以确认\n");
        get_str(&new_username2);
        if(strcmp(new_username,new_username2)==0)
        {
            break;
        }
        else
        {
            printf("两次输入的用户名不一致！\n");
            wait_for_enter();
        }
    }
    char sql_change_user_username[128]="UPDATE USERS SET USERNAME='";
    strcat(sql_change_user_username,new_username);
    strcat(sql_change_user_username,"' WHERE ID=");
    char user_id[64]="";
    itoa(get_user_id(con,row_num),user_id,10);  //将get_user_id返回的整型 id 转为字符串
    strcat(sql_change_user_username,user_id);
    if(mysql_query(con,sql_change_user_username))
    {
        db_error(con);
    }
    printf("成功修改了用户名\n");
    rtv=RTV_SUCCESS;
    wait_for_enter();
    return rtv;
}
