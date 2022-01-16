#include <stdio.h>
#include "common.h"
#include "interface.h"
#include "login_to_db.h"
#include "init.h"
#include "draw_window.h"
#include "get_input.h"
#include "about.h"
#include "unknown_cmd.h"

int appmain_window();
int appmain_callback(int rtv);

int appmain()
{
    int rtv=CMD_UNDEFINED;
    while(1)
    {
        rtv=appmain_window();
        rtv=appmain_callback(rtv);
        if(CMD_UNKNOWN==rtv)
        {
            unknown_cmd();
            continue;
        }
        if(APPMAIN_CMD_MAIN_INTERFACE==rtv)
        {
            login_to_db();
            continue;
        }
        if(APPMAIN_CMD_INIT==rtv)
        {
            init();
            continue;
        }
        if(APPMAIN_CMD_ABOUT==rtv)
        {
            about();
            continue;
        }
        if(APPMAIN_CMD_EXIT==rtv)
        {
            break;
        }
    }

    return rtv;
}
int appmain_window()
{
    draw_window();
    printf("(1)进入主程序\n");
    printf("(2)数据库初始化\n");
    printf("(3)关于\n");
    printf("(0)退出\n");
    int rtv=get_cmd();
    return rtv;
}
int appmain_callback(int rtv)
{
    switch(rtv)
    {
    case 1:
        rtv=APPMAIN_CMD_MAIN_INTERFACE;
        break;
    case 2:
        rtv=APPMAIN_CMD_INIT;
        break;
    case 3:
        rtv=APPMAIN_CMD_ABOUT;
        break;
    case 0:
        rtv=APPMAIN_CMD_EXIT;
        break;
    default:
        rtv=CMD_UNKNOWN;
        break;
    }
    return rtv;
}
