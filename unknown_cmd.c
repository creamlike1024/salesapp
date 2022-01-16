#include <stdio.h>

void unknown_cmd()
{
    printf("未知的命令！\n");
    printf("按回车后重新选择命令。。。");
    fflush(stdin);  //清除缓冲区，否则 getchar 将获得回车符号
    getchar();
}
