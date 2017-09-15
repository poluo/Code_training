/**********************************************************
 * Author        : poluo
 * Email         : xxx@email.com
 * Create time   : 2017-08-01 09:01
 * Last modified : 2017-08-01 09:01
 * Filename      : main.c
 * Description   : rewrite htop, original in https://github.com/hishamhm/htop
 * *******************************************************/
#include <stdio.h>  //for printf
#include <stdlib.h> //for atioi
#include <getopt.h> // for getopt_long
#include <string.h>  //strlen
#include "socket.h"
#include "main.h"
#include "draw.h"
#include "linux_info.h"

extern int USER_ID;
unsigned char scan_flag = 0x00;
int parse_arg(int argc,char *argv[])
{
    int ch;
    char *rvalue = NULL;
    while((ch = getopt(argc,argv,"hcmpadr:")) != -1)
    {
        switch(ch)
        {
            case 'r':
                rvalue = optarg;
                if((strcmp(rvalue,"s") == 0 )||(strcmp(rvalue,"S") == 0))
               	{
               		return CLIENT;
               	}
                if((strcmp(rvalue,"c") == 0 )||(strcmp(rvalue,"C") == 0))
                {
                	return SERVER;
                }
		
                PINFO("argument must be m\\M or s\\S \n");
                break;

            case 'h':
                PINFO("help text\n");
                break;
			
			case 'c':
				scan_flag |= (GET_CPU_INFO);
				break;

			case 'm':
				scan_flag |= (GET_MEM_INFO);
				break;

			case 'p':
				scan_flag |= (GET_PROCESS_INFO);
				break;
				
			case 'a':
            default:
				scan_flag |= (GET_CPU_INFO);
				scan_flag |= (GET_MEM_INFO);
				scan_flag |= (GET_PROCESS_INFO);
                break;
        }
		return OTHERS;
    }   
}


int main(int argc,char *argv[])
{
    int role = parse_arg(argc,argv);

    if(role == CLIENT)
    {
        printf("This is a socket Client\n");
        play_client();
    }
    else if(role == SERVER)
    {
        printf("This is a socket Server\n");
        play_server();
    }
	else if(role == OTHERS)
	{
		scan();
	}
    else
    {
        printf("No support parmgrams\n");
    }
	getch();

    return 0;
}
