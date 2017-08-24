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
#include "main.h"

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
}
void get_memory_info(meminfo *this)
{
    FILE* fd = fopen(PROCMEMINFOFILE,"r");
    size_t len = 0;
    ssize_t read;
    if(fd == NULL)
    {
        PINFO("%s open failed\n",PROCMEMINFOFILE);
        return;
    }
    char *buf = NULL;

    while((read = getline(&buf,&len,fd)) != -1)
    {
        #define tryRead(label, variable) (String_startsWith(buf, label) && sscanf(buf + strlen(label), " %32llu kB", variable))
        switch (buf[0]) {
          case 'M':
             if (tryRead("MemTotal:", &this->totalMem)) {}
             else if (tryRead("MemFree:", &this->freeMem)) {}
             else if (tryRead("MemShared:", &this->sharedMem)) {}
             break;
          case 'B':
             if (tryRead("Buffers:", &this->buffersMem)) {}
             break;
          case 'C':
             if (tryRead("Cached:", &this->cachedMem)) {}
             break;
          case 'S':
             switch (buf[1]) {
             case 'w':
                if (tryRead("SwapTotal:", &this->totalSwap)) {}
         }
         break;
      }
        #undef tryRead
    }
    fclose(fd);
    if(buf)
    {
        free(buf);
    }
    PDEBUG("MemTotal:\t\t%d KB\n",this->totalMem);
    PDEBUG("MemFree:\t\t%d KB\n", this->freeMem);
    PDEBUG("MemShared:\t%d KB\n", this->sharedMem);
    PDEBUG("Buffers:\t\t%d KB\n", this->buffersMem);
    PDEBUG("Cached:\t\t%d KB\n", this->cachedMem);
    PDEBUG("SwapTotal:\t%d KB\n", this->totalSwap);
    PDEBUG("SwapFree:\t\t%d KB\n", this->totalSwap);

}
int main(int argc,char *argv[])
{
   operation oper = get_operation(argc,argv);
   meminfo info;
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
        get_memory_info(&info);
        break;
    case GET_CPU_INFO:
        break;
    case GET_PROCESS_INFO:
        break;
    default:
        PINFO("Warn,Undefined operation\n");
   }
}
