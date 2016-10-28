#ifndef _CMD_LIST_H
#define _CMD_LIST_H


#define CMD_PROC_SUCCESS		0
#define CMD_PROC_ARGS_ERROR		1
#define CMD_PROC_OTHER_ERROR	2

#define CMD_MAX_NUM 	10
#define CMD_MAX_LEN 	10
#define CMD_MAX_ARGS	5
typedef int (*cmd_fn_ptr)(char **args,int args_num);
typedef struct cmd_list
{
	char *fn_name;
	char *fn_description;
	cmd_fn_ptr do_fn;
}cmd_list;

int cmd_help(char **args,int args_num);
int cmd_show(char **args,int args_num);
int cmd_caculator(char **args,int args_num);
int cmd_quit(char **args,int args_num);
int cmd_test(char **args,int args_num);
int cmd_match(char *str);
int cmd_fun(char **args,int args_num);

void args_extract(char *tmp_str,char *args[],int *args_num);

const cmd_list cmd_list_arr[CMD_MAX_NUM];



#endif
