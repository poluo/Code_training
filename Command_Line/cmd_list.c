#include "CallPython.h"  //<Python.h> must call before <stdio.h> otherwise will warning
#include <stdio.h>
#include "cmd_list.h"

extern void RunSimpleStringPython(const char *args);
extern void RunPyhtonScript(const char *FileName);
extern void CallFunPythonType1(const char * FileName,const char * Func,PyObject *pArg);
extern void CallFunPythonType3(const char * FileName,const char * Func,int *Result ,PyObject *pArg);

extern PyObject *ConvertPyObject(const char *Format,...);



const cmd_list cmd_list_arr[CMD_MAX_NUM] = 
{
	{"help","		show the usage of this program",cmd_help},
	{"quit","		quit this program",cmd_quit},
	{"show","		show something.......",cmd_show},
	{"calculator","	enter calculator",cmd_caculator},
	{"user","		user sign in/up function",cmd_user},
	{"wget","		simulate linux wget command",cmd_wget},
	{"fun","		just for take place",cmd_fun},
	{"fun","		just for take place",cmd_fun},
	{"fun","		just for take place",cmd_fun},
	{"fun","		just for take place",cmd_fun}
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
		for(i=0;i<CMD_MAX_NUM;i++)
		{
			if(cmd_list_arr[i].fn_name!=NULL)
				printf("%s:	%s\n",cmd_list_arr[i].fn_name,cmd_list_arr[i].fn_description);
		}
		printf("\n\nThat's all support command now\n\n");
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
/*quit is not completed in here*/
int cmd_quit(char **args,int args_num)
{
	return CMD_PROC_SUCCESS;
}
int cmd_fun(char **args,int args_num)
{
	int ret=0;
	CallFunPythonType1("demo","foo",NULL);//无返回值无参数
	CallFunPythonType1("demo","bar",ConvertPyObject("%d",5));
	CallFunPythonType3("demo","too",&ret,NULL);
	printf("ret=%d\n",ret);
	CallFunPythonType3("demo","boo",&ret,ConvertPyObject("%d",8));
	printf("ret=%d\n",ret);
	return CMD_PROC_SUCCESS;
}
int cmd_wget(char **args,int args_num)
{
	printf("arg 1 %s",args[0]);
	return CMD_PROC_SUCCESS;
	
}
int cmd_user(char **args,int args_num)
{
    //InitPython();
	RunPyhtonScript("userpw");
    //ExitPython();
    return CMD_PROC_SUCCESS;
}










































