#include "CallPython.h"
#include <stdio.h>
#include <stdarg.h>
/*初始化python*/
int InitPython()
{
	Py_Initialize();//初始化python 
	//检查初始化是否成功
	if (!Py_IsInitialized())
	{
		printf("call python failed!\n");
		return 1;
	}
	else
	{
		return 0;
	}
}
/*退出python环境*/
int ExitPython()
{
	Py_Finalize();
	return 0;
}
/*在python shell中运行简单的语句*/
void RunSimpleStringPython(const char *args)
{
	printf("%s\n",args);
	if(1)
	{
		PyRun_SimpleString(args);
	}
	else
	{
		printf("Error,args is NULL!\n");
	}
}
/*执行python脚本*/
void RunPyhtonScript(const char *FileName)
{
	InitPython();
	char *args=NULL;
	char *str=calloc(0,sizeof(char)*(MAX_LENGTH_PYTHON_SCRIPT_NAME+12));
	strcat(str,"execfile('./");
	strcat(str,FileName);
	strcat(str,".py')");
	args=calloc(0,sizeof(char)*(strlen(str)+1));
	memcpy(args,str,strlen(str)+1);
	free(str);
	RunSimpleStringPython(args);
	free(args);
	ExitPython();
}
//导出当前环境变量
void getcurrent()  
{  
    PyRun_SimpleString("import sys");  
    PyRun_SimpleString("sys.path.append('./')");  
}  

/*调用python函数，有以下几种类型
1.无返回值无参数
2.无返回值有参数
3.有返回值无参数
4.有返回值有参数
*/
/*Type1:No return value,No arguments*/
void CallFunPythonType1(const char * FileName,const char * Func,PyObject *pArg)
{
	InitPython();
    getcurrent();  
    PyObject *pModule = NULL, *pFunc = NULL;
	/*导入模块*/
	
    pModule = PyImport_ImportModule(FileName);
	if(!pModule)
	{
	 	printf("can't find %s.py\n",FileName);
		return;
	}
	//直接获取模块中的函数  
    pFunc = PyObject_GetAttrString(pModule, Func);
	if ( !pFunc || !PyCallable_Check(pFunc) ) 
    {  
        printf("can't find function %s\n",Func);    
        return;  
    }   
	//调用函数，参数为空??
    PyEval_CallObject(pFunc, pArg); 
    ExitPython();
}

/*Type3:With return value,No arguments*/
/*only return int*/
void CallFunPythonType3(const char * FileName,const char * Func,int *Result ,PyObject *pArg)
{
	InitPython();
    getcurrent();  
    PyObject *pModule = NULL, *pFunc = NULL,*pResult=NULL;
	
	/*导入模块*/
    pModule = PyImport_ImportModule(FileName);
	if(!pModule)
	{
	 	printf("can't find %s.py\n",FileName);
		return;
	}
	//直接获取模块中的函数  
    pFunc = PyObject_GetAttrString(pModule, Func);
	if ( !pFunc || !PyCallable_Check(pFunc) ) 
    {  
        printf("can't find function %s\n",Func);    
        return;  
    }   
	//调用函数，参数为空??
    pResult=PyEval_CallObject(pFunc, pArg);
	PyArg_Parse(pResult, "i", Result);
	printf("return value %d",*Result);
    ExitPython();
}
PyObject *ConvertPyObject(const char *Format,...)
{
	int int_num[MAX_ARGS_NUM]={0};
	int count_int=0;
	double double_num[MAX_ARGS_NUM]={0};
	int count_double=0;
	char ** str=calloc(0,sizeof(char*)*MAX_LENGTH_PYTHON_SCRIPT_NAME);
	int count_str=0;
	int i=0;
	va_list vl;
	va_start(vl,Format);
	/*参数有1.int %d  2.double %f 3.string %s */
	while(*Format!='\0')
	{
		switch(*Format)
		{
			case '%':
				break;
			case 's':
				str[count_str]=va_arg(vl,char *);
				printf("%s\n",str[count_str]);
				count_str++;
				break;
			case 'd':
				int_num[count_int]=va_arg(vl,int);
				printf("%d\n",int_num[count_int]);
				count_int++;
				break;
			case 'f':
				double_num[count_double]=va_arg(vl,double);
				printf("%f\n",double_num[count_double]);
				count_double++;
				break;
		}
		Format++;
	}
	va_end(vl);
	PyObject *pArgs= PyTuple_New(count_int+count_double+count_str);
	for (i=0;i<count_int;i++)
	{
		 PyTuple_SetItem(pArgs, i, PyLong_FromLong((long)int_num[i])); 
	}
	for (i=0;i<count_double;i++)
	{
		 PyTuple_SetItem(pArgs, i+count_int,  PyFloat_FromDouble(double_num[i])); 
	}
	for (i=0;i<count_str;i++)
	{
		/*PyObject* Py_BuildValue(char *format, ...) ,s 表示字符串,i表示整型变量,f表示浮点数*/
		 PyTuple_SetItem(pArgs, i+count_int+count_double, Py_BuildValue("s",int_num[i])); 
	}
	return pArgs;
}

