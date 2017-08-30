#ifndef _MAIN_H
#define _MAIN_H

#define ENABLE_DEBUG
#define ENABLE_INFO
#define FUNCTION_NAME   "htop"
#define VERSION         "0.01"

#define GET_MEM_INFO		(1 << 0)
#define GET_CPU_INFO		(1 << 1)
#define GET_PROCESS_INFO 	(1 << 2)
#define GET_VERSION_INFO	(1 << 3)
#define GET_MAX_NUM			(5)


#define String_startsWith(s, match) (strncmp((s),(match),strlen(match)) == 0)

#ifdef ENABLE_DEBUG
#   define PDEBUG(format, args...) fprintf(stdout, FUNCTION_NAME ": " format, ##args)
#else
#   define PDEBUG(format, args...)
#endif

#ifdef ENABLE_DEBUG
#   define PINFO(format, args...) fprintf(stdout, FUNCTION_NAME ": " format, ##args)
#else
#   define PINFO(format, args...)
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

#ifndef PROCCPUINFO
#define PROCCPUINFO PROCDIR "/cpuinfo"
#endif

#endif