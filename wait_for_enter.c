#include <stdio.h>
#include <stdlib.h>

void wait_for_enter()
{
    printf("按回车键继续。");
    fflush(stdin);  //清除缓冲区，否则 getchar 将获得回车符号
    getchar();
}
