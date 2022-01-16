#include <stdio.h>
#include "common.h"

int get_cmd()
{
    int cmd=CMD_UNKNOWN;
    printf("\n请输入命令：");
    fflush(stdin);  //清除缓冲区
    scanf("%d",&cmd);
    return cmd;
}
