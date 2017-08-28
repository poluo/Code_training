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
#include "draw.h"
#include "main.h"
#include "linux_info.h"

operation get_operation(int argc,char *argv[])
{
    int opt,opt_index;
    char *cvalue = NULL;
    static struct option long_opts[]=
    {
        {"help",    no_argument,        0,  'h'},
        {"memory",  no_argument,        0,  'm'},
        {"cpu",     no_argument,        0,  'c'},
        {"process", no_argument,        0,  'p'},
        {"version", no_argument,        0,  'v'},
        {"test",    required_argument,  0,  't'},
        {0,         0,                  0,    0} 
    };
    while((opt = getopt_long(argc,argv,"mcphvt:",long_opts,&opt_index)) != -1)
    {
        switch(opt)
        {   
            case 'h':
                PDEBUG("This is memory info\n");
                return GET_HELP_INFO;

            case 'm':
                PDEBUG("This is memory info\n");
                return GET_MEM_INFO;

            case 'c':
                PDEBUG("This is cpu info\n");
                return GET_CPU_INFO;

            case 'p':
                PDEBUG("This is process info\n");
                return GET_PROCESS_INFO;

            case 'v':
                PDEBUG("This is version text\n");
                return GET_VERSION_INFO;

            case 't':
                cvalue = optarg;
                PDEBUG("this is test function,3+%s=%d\n",cvalue,3+atoi(cvalue));
                return GET_OTHER_INFO;
        }
    }
	draw_init();
	draw_done();
}


int main(int argc,char *argv[])
{
   operation oper = get_operation(argc,argv);
   meminfo memory;
   cpuinfo cpu;
   process_list_info process_list;
   process_list.process = NULL;
   process_list.size = 0;

   switch(oper){
    case GET_HELP_INFO:
        PINFO("help text\n");
        break;

    case GET_VERSION_INFO:
        PINFO("This Version:%s\n",VERSION);
        break;

    case GET_OTHER_INFO:
        PINFO("This function not defined yet\n");
        break;

    case GET_MEM_INFO:
        get_memory_info(&memory);
        break;

    case GET_CPU_INFO:
        get_cpu_info(&cpu);
        break;

    case GET_PROCESS_INFO:
		get_process_list_info(&process_list);
        break;
    default:
        PINFO("Warn,Undefined operation\n");
   }
   draw_done();
   draw_init();
}
