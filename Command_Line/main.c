#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "log.h"
#include "platform.h"
#include "keyproc.h"
#include "cmd_list.h"
/*string copy processs*/
#define STR_COPY_OK 	0
#define STR_COPY_QUIT 	1


int cmd_get();

int str_copy(char *str_tmp);
void cmd_manage(int type,char **str_tmp,int run_count);

int main()
{

	int continue_flag = 1;

    while(continue_flag)
    {
        print_head();
		continue_flag = cmd_get();
    }

	printf("\nExit Command Line...\n");

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}


int cmd_get()
{
	/*最大cmd 字符长度是CMD_MAX_LEN=10*/
	char *tmp_str = calloc(0,sizeof(char)*CMD_MAX_LEN);
	char *tmp_direct_str=calloc(0,sizeof(char)*CMD_MAX_LEN);
	int  n = 0;
	int i=0;
	/*used to confirm wheater input direct key */
	char c = 0,last_c=0,last_last_c=0;
	int copy_result=0;
	int direct_key=0;
	int direct_key_count=0;
	
    while ((c = GET_CH) !=ENTER_KEY&&c != EOF)
	{
		direct_key=swicth_direct_key(last_last_c,last_c,c);
		if (direct_key!=KEY_ERR)
		{
			memset(tmp_direct_str,0,sizeof(char)*CMD_MAX_LEN);
			if (direct_key==DOWN)
			{
				direct_key_count--;
				//printf("input Down key ,key_count=%d\n",direct_key_count);
				MOVEDOWN(1);
				direct_key_proc(&tmp_direct_str,&n,&direct_key_count);
			}
			else if (direct_key==UP)
			{
				direct_key_count++;
				//printf("input Up key ,key_count=%d\n",direct_key_count);
				MOVEDOWN(1);
				direct_key_proc(&tmp_direct_str,&n,&direct_key_count);
			}
			//printf("direct_key_count=%d",direct_key_count);
		}
		/*input a Tab process*/
		else if (c == '\t')
		{
			tab_proc(tmp_str,&n);
			direct_key_count=0;
		}
		/*input a backspace*/
		else if (c=='\b') //backspace
		{	
			if(direct_key_count!=0)
			{
				memcpy(tmp_str,tmp_direct_str,n);
				direct_key_count=0;
			}
			backspace_proc(tmp_str,&n);
		}
		/*swicth is or not direct key*/
		else
		{
			*(tmp_str + n) = c;
			n++;
		}
		last_last_c=last_c;
		last_c=c;
	}
	if(direct_key_count!=0)
	{
		memcpy(tmp_str,tmp_direct_str,n);
		direct_key_count=0;
	}
	*(tmp_str + n) = '\0';
	if(0==strlen(tmp_str))
	{
		copy_result=1;
	}
	else
	{	
		copy_result=str_copy(tmp_str);
		cmd_match(tmp_str);
	}
	return copy_result;
}
int str_copy(char *str_tmp)
{
	
	log_in(str_tmp);
	//PRINT_STR;
	if (strcmp(str_tmp, "quit") == 0)
	{
		//printf("return 0 \n");
		return STR_COPY_OK;
	}
	else
	{
		//printf("return 1 \n");
		return STR_COPY_QUIT;
	}
}

