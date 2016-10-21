#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "keyproc.h"
#include "platform.h"
#include "log.h"
#include "cmd_list.h"

int tab_proc(char *str,int *str_size)
{
	int i=0;
	for (i = 0; i < CMD_MAX_NUM; ++i)
	{
		if (strncmp(str,cmd_list_arr[i].fn_name,*str_size)==0)
		{
			*str_size=strlen(cmd_list_arr[i].fn_name);
			//printf("%d\n",*str_size);
			memcpy(str,cmd_list_arr[i].fn_name,*str_size);
			BACK_LINE_HEAD;//back line head
			print_head();
			printf("%s",str);
			return 0;
		}
	}
	return 1;
}
int backspace_proc(char *str,int *str_size)
{
	(*str_size)--;
	if (*str_size>=0)
	{
		str[*str_size]=0;
		BACK_LINE_HEAD;//delete sanme line
		print_head();
		printf("%s",str);
		printf(" \b");//notice space!!
	}
	else
	{
		*str_size=0;
		memset(str,0,CMD_MAX_LEN);
		BACK_LINE_HEAD;//back line head
		print_head();
	}
	return 0;
}
void direct_key_proc(char **str,int *str_size,int *run_count)
{
	int ret=0;	
	ret=log_out(str,run_count);
	ret=(ret==LOG_SUCCESS)?(0):(printf("LOG out error! %d\n",ret));
	*(str_size)=strlen(*str)+1;
	CLEAR_LINE;
	BACK_LINE_HEAD;//delete same line
	print_head();
	printf("%s",*str);
}
int swicth_direct_key(char last_last_c, char last_c,char c)
{
	if (last_last_c==27&&last_c==91)
	{
		switch(c)
		{
			case 65:
				//printf("up\n");
				return UP;

			case 66:
				//printf("down\n");
				return DOWN;

			case 67:
				//printf("right\n");
				return RIGHT;

			case 68:
				//printf("left\n");
				return LEFT;

			default:
				//printf("wrong\n");
				return KEY_ERR;
		}
	}
	return KEY_ERR;
}

void print_head()
{
	char cmd_prompt = '$';
	static char tag_once = 1;
	if (tag_once)
	{
		tag_once = 0;
		printf("*************************************\n");
		printf("***    Welcome to Command Line    ***\n");
		printf("*************************************\n");
		printf("\n\n");
		printf("[cmd_line]%c:", cmd_prompt);
	}
	else
	{
		printf("[cmd_line]%c:", cmd_prompt);
	}
}
