#include <stdio.h>
#include "cmd_list.h"
const cmd_list cmd_list_arr[CMD_MAX_NUM] = 
{
	{"help","show the usage of this program",cmd_help},
	{"quit","quit this program",cmd_quit},
	{"show","show something.......",cmd_show},
	{"caulator","enter  caulator",cmd_caculator},
	{0,0,0}
};

int cmd_help(char **args,int args_num)
{
	printf("help\n");
	printf("ok\n");
	printf("over\n");
	return 0;
}
int cmd_show(char **args,int args_num)
{
	printf("show\n");
	printf("show over\n");
	return 0;
}
int cmd_caculator(char **args,int args_num)
{
	printf("enter a caculator program....\n");
	printf("bye\n");
	return 0;
}
int cmd_quit(char **args,int args_num)
{
	return 0;
}










































