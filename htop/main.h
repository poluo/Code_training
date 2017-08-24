#ifndef _MAIN_H
#define _MAIN_H

#define ENABLE_DEBUG
#define ENABLE_INFO
#define FUNCTION_NAME 	"htop"
#define VERSION  		"0.01"
typedef enum operation
{
	GET_HELP_INFO,
	GET_MEM_INFO,
	GET_CPU_INFO,
	GET_PROCESS_INFO,
	GET_VERSION_INFO,
	GET_OTHER_INFO,
	GET_MAX_NUM,
}operation;

typedef struct meminfo
{
   unsigned long long int totalMem;
   unsigned long long int usedMem;
   unsigned long long int freeMem;
   unsigned long long int sharedMem;
   unsigned long long int buffersMem;
   unsigned long long int cachedMem;
   unsigned long long int totalSwap;
   unsigned long long int usedSwap;
   unsigned long long int freeSwap;
}meminfo;

#define String_startsWith(s, match) (strncmp((s),(match),strlen(match)) == 0)

#ifdef ENABLE_DEBUG
#   define PDEBUG(format, args...) fprintf(stdout, FUNCTION_NAME ": " format, ##args)
#else
#  	define PDEBUG(format, args...)
#endif

#ifdef ENABLE_DEBUG
#   define PINFO(format, args...) fprintf(stdout, FUNCTION_NAME ": " format, ##args)
#else
#  	define PINFO(format, args...)
#endif

#ifndef PROCDIR
#define PROCDIR "/proc"
#endif

#ifndef PROCSTATFILE
#define PROCSTATFILE PROCDIR "/stat"
#endif

#ifndef PROCMEMINFOFILE
#define PROCMEMINFOFILE PROCDIR "/meminfo"
#endif

#endif