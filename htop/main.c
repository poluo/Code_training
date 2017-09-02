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
int parse_arg(int argc,char *argv[])
{
    int ch;
    char *rvalue = NULL;
    while((ch = getopt(argc,argv,"hdr:")) != -1)
    {
        switch(ch)
        {
            case 'r':
                rvalue = optarg;
                if((strcmp(rvalue,"s") == 0 )||(strcmp(rvalue,"S") == 0))
               	{
               		USER_ID = 1;
               	}
                if((strcmp(rvalue,"c") == 0 )||(strcmp(rvalue,"C") == 0))
                {
                	USER_ID = 2;
                }
		
                PINFO("argument must be m\\M or s\\S \n");
                break;

            case 'h':
                PINFO("help text\n");
                break;
			
			case 'd':
				USER_ID = 3;
				break;
			
            default:
                break;
        }
		return USER_ID;
    }   
}


int main(int argc,char *argv[])
{
    int role = parse_arg(argc,argv);
	draw_init();
    if(role == 2)
    {
        printc(COLOR_DEFAULT_TEXT,"This is a socket Client\n");
        play_client();
    }
    else if(role == 1)
    {
        printc(COLOR_DEFAULT_TEXT,"This is a socket Server\n");
        play_server();
    }
	else if(role == 3)
	{
		printc(COLOR_DEFAULT_TEXT,"This is debug mode\n");
		scan();
		draw_panel();
	}
    else
    {
        printc(COLOR_DEFAULT_TEXT,"Nither Server or Client,exit\n");
    }
	getch();
	draw_done();
    return 0;
}
