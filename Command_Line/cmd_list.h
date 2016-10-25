#ifndef _CMD_LIST_H
#define _CMD_LIST_H


#define CMD_MAX_NUM 	5
#define CMD_MAX_LEN 	10

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

const cmd_list cmd_list_arr[CMD_MAX_NUM];



#endif
