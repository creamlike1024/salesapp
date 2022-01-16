#include <stdio.h>
#include "draw_window.h"
#include "wait_for_enter.h"

void about()
{
    draw_window();
    printf("关于信息：\n");
    printf("销售管理系统v0.1\n");
    printf("程序设计作业\n");
    printf("2021-12-12\n");
    wait_for_enter();
}
