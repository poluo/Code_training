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
#include <sys/utsname.h> //utsname
#include <unistd.h>
#include <time.h>
#include "socket.h"
#include "main.h"
#include "draw.h"
#include "linux_info.h"

extern int USER_ID;
unsigned char scan_flag = 0x00;
/* Number of ticks per second */
unsigned int hz;
unsigned long long uptime;
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

void get_HZ(void)
{
	long ticks;

	if ((ticks = sysconf(_SC_CLK_TCK)) == -1) {
		perror("sysconf");
	}

	hz = (unsigned int) ticks;
}

time_t get_local_time(struct tm *rectime,int day_off)
{
	time_t timer;
	struct tm *ltm;

	time(&timer);
	timer -= SEC_PER_DAY * day_off;
	ltm = localtime(&timer);
	if(ltm)
	{
		*rectime = *ltm;
	}
	return timer;
}
void print_header()
{
	struct utsname header;
	struct tm now_time;
	char cur_date[64];

	uname(&header);
	get_local_time(&now_time,0);
	strftime(cur_date,sizeof(cur_date),"%Y-%m-%d",&now_time);
	printf("%s %s (%s) \t%s \t_%s_\t\n", header.sysname, header.release, header.nodename,
		       cur_date, header.machine);
}
int main(int argc,char *argv[])
{
    int role = parse_arg(argc,argv);

	if(role > OTHERS)
	{
		printf("No support parameter\n");
		return 0;
	}

	print_header();
	get_HZ();
	read_uptime(&uptime);
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
		while(1)
		{
			scan();
			sleep(5);
		}
	}

    return 0;
}
