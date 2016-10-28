#include <Python.h>
#include "cmd_list.h"
const cmd_list cmd_list_arr[CMD_MAX_NUM] = 
{
	{"help","show the usage of this program",cmd_help},
	{"quit","quit this program",cmd_quit},
	{"show","show something.......",cmd_show},
	{"cal","enter calculator",cmd_caculator},
	{"test","test function",cmd_test},
	{"fun","just for take place",cmd_fun},
	{"fun","just for take place",cmd_fun},
	{"fun","just for take place",cmd_fun},
	{"fun","just for take place",cmd_fun},
	{"fun","just for take place",cmd_fun}
};
int cmd_match(char *str)
{
	int i=0;
	char *args[CMD_MAX_ARGS];
	int args_num=0;
	int ret=0;
	args_extract(str,args,&args_num);
	for(i=0;i<CMD_MAX_NUM;i++)
	{
		if(strcmp(args[0],cmd_list_arr[i].fn_name)==0)
		{
			args_num--;
			if((ret=cmd_list_arr[i].do_fn(&args[1],args_num))==CMD_PROC_SUCCESS)
			{
				/*Command Proc Success*/
				return 0;
			}
			else if(ret==CMD_PROC_ARGS_ERROR)
			{
				printf("Arguments list Error\n");
				return 0;
			}
			else if(ret==CMD_PROC_OTHER_ERROR)
			{
				printf("Unknow Error");
				return 0;
			}
		}
		
	}
	printf("NO matched command in list,tey again.\n");
	return 0;
}
void args_extract(char *tmp_str,char *args[],int *args_num)
{
	char *ptr;
    int valid=0;
    ptr = tmp_str;
    *args_num = 0;
    while (*args_num < CMD_MAX_ARGS && *ptr != '\0')
    {
        while (*ptr != '\0'&& isspace(*ptr))
        {
            *ptr = '\0';
            ptr++;
            valid = 0;
        }
        if (*ptr != '\0')
        {
            if (!valid)
            {
                valid = 1;
                args[*args_num] = ptr;
                (*args_num)++;
            }
            ptr++;
        }
    }
}
/*show guide about this program*/
int cmd_help(char **args,int args_num)
{
	int i=0;
	if(args_num!=0)
	{
		printf("usage:help,show some helpful message about this program\n");
		return CMD_PROC_ARGS_ERROR;
	}
	else
	{
		printf("\nSupport Command list:\n");
		for(i=0;i<CMD_MAX_NUM;i++)
		{
			if(cmd_list_arr[i].fn_name!=NULL)
				printf("%s\t:%s\n",cmd_list_arr[i].fn_name,cmd_list_arr[i].fn_description);
		}
		printf("\nThat's all support command now\n\n");
		return CMD_PROC_SUCCESS;
	}
}
int cmd_show(char **args,int args_num)
{
	printf("show\n");
	printf("show over\n");
	return CMD_PROC_SUCCESS;
}
int cmd_caculator(char **args,int args_num)
{
	printf("enter a caculator program....\n");
	printf("bye\n");
	return CMD_PROC_SUCCESS;
}
int cmd_quit(char **args,int args_num)
{
	return CMD_PROC_SUCCESS;
}
int cmd_fun(char **args,int args_num)
{
	return CMD_PROC_SUCCESS;
}
int cmd_test(char **args,int args_num)
{
    int sum=0;
	Py_Initialize();//初始化python 
	//检查初始化是否成功
	if (!Py_IsInitialized())
	{
		printf("call python failed!\n");
		return 1;
	}
    PyRun_SimpleString("print('hello python')");//把输入的字符串作为Python代码直接运行，返回0表示成功，-1表示有错。 
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("print '---import sys---'");   
    PyRun_SimpleString("sys.path.append('./')");  
    PyObject *pName,*pModule,*pDict,*pFunc,*pArgs,*result;

    // 载入名为demo的脚本  
    pName = PyString_FromString("demo");  
    pModule = PyImport_Import(pName);  
    if ( !pModule ) 
    {  
        printf("can't find demo.py");  
        return 1;  
    }  
    pDict = PyModule_GetDict(pModule);  
    if ( !pDict ) 
    {  
        return 1;  
    }  
    // 找出函数名为add的函数  
    printf("----------------------\n");  
    pFunc = PyDict_GetItemString(pDict, "add");  
    if ( !pFunc || !PyCallable_Check(pFunc) ) 
    {  
        printf("can't find function [add]");  
        getchar();  
        return -1;  
     }  
    // 参数进栈  
    //All integers are implemented as “long” integer objects of arbitrary size
    
    pArgs = PyTuple_New(2); 
    PyTuple_SetItem(pArgs, 0, PyLong_FromLong(1L)); 
    PyTuple_SetItem(pArgs, 1, PyLong_FromLong(2L));  
  
    // 调用Python函数  
    result=PyObject_CallObject(pFunc, pArgs);  
    PyArg_Parse(result, "i", &sum);
    printf("sum=%d \n",sum);
    Py_DECREF(pName);  
    Py_DECREF(pArgs);  
    Py_DECREF(pModule);  
  
    // 关闭Python  
    Py_Finalize();  
    return CMD_PROC_SUCCESS;  
}










































