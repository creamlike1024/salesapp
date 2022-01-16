#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mysql.h"
#include "draw_window.h"
#include "interface.h"
#include "get_input.h"
#include "common.h"
#include "db_query.h"
#include "unknown_cmd.h"
#include "wait_for_enter.h"

int cashier_window();
int cashier_callback(int rtv);

int cashier(MYSQL * con)
{
    int rtv=CMD_UNDEFINED;
    while(1)
    {
        rtv=cashier_window();
        rtv=cashier_callback(rtv);
        if(CMD_UNKNOWN==rtv)
        {
            unknown_cmd();
            continue;
        }
        if(CASHIER_CMD_NEW_ORDER==rtv)
        {
            draw_window();
            float total_price=0;
            int good_num=0;
            while(1)
            {
                printf("扫入条码或输入商品名称\n");
                char good[128]="";
                get_str(&good);
                if(strspn(good,"1234567890")==strlen(good))
                {
                    int row_num=find_good_code(con,atoi(good));
                    if(RTV_FAILED==row_num)
                    {
                        printf("未找到商品信息！\n");
                        wait_for_enter();
                        continue;
                    }
                    else
                    {
                        printf("添加商品：\n");
                        printf("--------------------------------------------------\n");
                        show_good(con,row_num);
                        total_price+=get_good_price(con,row_num);
                        good_num++;
                        printf("%d 件商品，总计：%.2f元\n",good_num,total_price);
                        int status=1;
                        while(1)
                        {
                            printf("继续添加商品？(Y/n)");
                            fflush(stdin);
                            char cmd_confirm=getchar();
                            if('Y'==cmd_confirm||'y'==cmd_confirm||'\n'==cmd_confirm)
                                break;
                            else if('N'==cmd_confirm||'n'==cmd_confirm)
                            {
                                status=0;
                                break;
                            }
                            else
                            {
                                printf("未知指令！\n");
                                wait_for_enter();
                                continue;
                            }
                        }
                        if(1==status)
                            continue;
                        else
                        {
                            printf("\n录入结束，共 %d 件商品，总计：%.2f元\n",good_num,total_price);
                            wait_for_enter();
                            break;
                        }
                    }
                }
                else
                {
                    int row_num=find_good_name(con,&good);
                    if(RTV_FAILED==row_num)
                    {
                        printf("未找到商品信息！\n");
                        wait_for_enter();
                        continue;
                    }
                    else
                    {
                        printf("添加商品：\n");
                        printf("--------------------------------------------------\n");
                        show_good(con,row_num);
                        total_price+=get_good_price(con,row_num);
                        good_num++;
                        printf("%d 件商品，总计：%.2f元\n\n",good_num,total_price);
                        int status=1;
                        while(1)
                        {
                            printf("继续添加商品？(Y/n)");
                            fflush(stdin);
                            char cmd_confirm=getchar();
                            if('Y'==cmd_confirm||'y'==cmd_confirm||'\n'==cmd_confirm)
                                break;
                            else if('N'==cmd_confirm||'n'==cmd_confirm)
                            {
                                status=0;
                                break;
                            }
                            else
                            {
                                printf("未知指令！\n");
                                wait_for_enter();
                                continue;
                            }
                        }
                        if(1==status)
                            continue;
                        else
                        {
                            printf("\n录入结束，共 %d 件商品，总计：%.2f元\n\n",good_num,total_price);
                            wait_for_enter();
                            break;
                        }
                    }
                }

            }
        }
        if(CMD_BACK==rtv)
        {
            break;
        }
    }
    return rtv;
}
int cashier_window()
{
    draw_window();
    printf("(1)新建订单\n");
    printf("(0)返回\n");
    int rtv=get_cmd();
    return rtv;
}
int cashier_callback(int rtv)
{
    switch(rtv)
    {
    case 1:
        rtv=CASHIER_CMD_NEW_ORDER;
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
