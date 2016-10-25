#include <stdio.h>
#include <string.h>
#include <Python.h>
#include "cmd_list.h"
const cmd_list cmd_list_arr[CMD_MAX_NUM] = 
{
	{"help","show the usage of this program",cmd_help},
	{"quit","quit this program",cmd_quit},
	{"show","show something.......",cmd_show},
	{"caulator","enter  caulator",cmd_caculator},
	{"test","test function",cmd_test}
};
int cmd_match(char *str)
{
	int i=0;
	for(i=0;i<CMD_MAX_NUM;i++)
	{
		if(strcmp(str,cmd_list_arr[i].fn_name)==0)
		{
			cmd_list_arr[i].do_fn(NULL,0);
			return 0;
		}
		
	}
	return 1;
}

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
int cmd_test(char **args,int args_num)
{
	Py_Initialize();//初始化python  
    PyRun_SimpleString("print('hello python')");//直接运行python代码  
    Py_Finalize(); //释放python  
    return 0; 
}










































