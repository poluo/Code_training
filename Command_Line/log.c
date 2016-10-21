#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"

static input_log_struct input_log;
int log_in(char *str_tmp)
{
	input_element_strcut input_element = { NULL, 0 };
	
	if (str_tmp==NULL)
	{
		//printf("file=%s,func=%s,line=%d error",__FILE__,__FUNCTION__,__LINE__);
		return LOG_IN_ERR;
	}
	else
	{

		input_element.str_len=strlen(str_tmp)+1;
		//printf("%s %d str_len=%d \n",__FUNCTION__,__LINE__,input_element.str_len);
		input_element.str_ptr=calloc(0,sizeof(char)*input_element.str_len);
		memcpy(input_element.str_ptr,str_tmp,input_element.str_len);
		//printf("%s %d str_ptr=%s \n",__FUNCTION__,__LINE__,input_element.str_ptr);

		memcpy((input_log.input_element_ptr+input_log.log_size),&input_element,sizeof(input_element_strcut));
		/*still have some problem here......*/
		//*(input_log.input_element_ptr + input_log.log_size) = input_element;
		//printf("log in %s\n",(input_log.input_element_ptr+input_log.log_size)->str_ptr);
		
		input_log.log_size++;

		/*for(i=0;i<input_log.log_size;i++)
		{
			printf("input_log %d %s\n",i,(input_log.input_element_ptr+i)->str_ptr);
		}*/
		if(input_log.log_size>=LOG_MAX_NUM)
			input_log.log_size=0;
		
		return LOG_SUCCESS;
	}


}
int log_out(char **str_tmp,int *run_count)
{
	
	if (*run_count > input_log.log_size)
	{
		*run_count = input_log.log_size;
	}
	else if (*run_count < 1)
	{
		*run_count = 1;
	}
	

	input_element_strcut input_element = {NULL,0};
	if (strlen(*str_tmp)==0)
	{
		//printf("logsize=%d",input_log.log_size);
		memcpy(&input_element,(input_log.input_element_ptr+input_log.log_size-*run_count),sizeof(input_element_strcut));
		memcpy(*str_tmp,input_element.str_ptr,input_element.str_len);
		//printf("log_out %s\n",*str_tmp);
		return LOG_SUCCESS;
	}
	else
	{
		//printf("log out error %d",strlen(*str_tmp));
		return LOG_OUT_ERR;
	}

}
