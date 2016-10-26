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
    return 0;  
}










































