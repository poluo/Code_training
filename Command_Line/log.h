#ifndef _LOG_H
#define _LOG_H

#define LOG_MAX_NUM 20
#define LOG_SUCCESS 0
#define LOG_IN_ERR	1 //log in str is null
#define LOG_OUT_ERR	2 //log out str is not null

typedef struct input_element_strcut
{
	char *str_ptr;
	int str_len;
}input_element_strcut;
typedef struct input_log_struct
{
	input_element_strcut input_element_ptr[LOG_MAX_NUM];
	int log_size;
}input_log_struct;


extern int log_in(char *str_tmp);
extern int log_out(char **str_tmp,int *run_count);


#endif
