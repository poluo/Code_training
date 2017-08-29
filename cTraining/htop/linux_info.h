#ifndef _LINUX_INFO_H
#define _LINUX_INFO_H

#include <unistd.h>

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

typedef struct cpuinfo
{
   unsigned long long int usertime;
   unsigned long long int nicetime;
   unsigned long long int systemtime;
   unsigned long long int idletime;
   unsigned long long int ioWait;
   unsigned long long int irq;
   unsigned long long int softIrq;
   unsigned long long int steal;
   unsigned long long int guest;
   unsigned long long int guestnice;
}cpuinfo;

typedef struct process_info {
   unsigned long long int time;
   pid_t pid;
   pid_t ppid;
   char* command;
   int command_len;
   char state;
   unsigned int session;
   int processor;
   unsigned long long int utime;
   unsigned long long int stime;
   unsigned long long int cutime;
   unsigned long long int cstime;

   float percent_cpu;
   float percent_mem;
   char* user;

   long int priority;
   long int nice;
   long int nlwp;
   char starttime_show[8];
   time_t starttime_ctime;

   int exit_signal;

   unsigned long int minflt;
   struct process_info *next;
   struct process_info *prev;
} process_info;

typedef struct process_list_info
{
	process_info *process;
	int size;
}process_list_info;

#ifndef MAX_NAME
#define MAX_NAME 128
#endif

#ifndef MAX_READ
#define MAX_READ 2048
#endif

extern void get_memory_info(meminfo *this);
extern void get_cpu_info(cpuinfo *this);
extern void get_process_list_info(process_list_info *this);
#endif