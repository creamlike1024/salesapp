#ifndef GET_INPUT_H_INCLUDED
#define GET_INPUT_H_INCLUDED

int get_cmd();
/*
函数名称：get_cmd
参数：无
返回值：int cmd
说明：调用该函数会获取用户输入的命令并作为 int 类型返回
*/

void get_str(char * str);
/*
get_str函数
参数：char * str
返回值：无
说明：提供一个字符数组指针，获取用户输入保存在该字符数组中
*/


#endif // GET_INPUT_H_INCLUDED
