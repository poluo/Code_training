#ifndef _KEYPROC_H
#define _KEYPROC_H

/*direct key process*/
#define KEY_ERR 	0
#define UP 			1
#define DOWN 		2
#define	RIGHT 		3
#define LEFT 		4

#define CMD_MAX_NUM 	5
#define CMD_MAX_LEN 	10


extern int tab_proc(char *str,int *str_size);
extern int backspace_proc(char *str,int *str_size);
extern int swicth_direct_key(char last_last_c, char last_c,char c);
extern void print_head();

extern void direct_key_proc(char **str,int *str_size,int run_count);


#endif
