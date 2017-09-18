#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <pwd.h>
#include "linux_info.h"
#include "draw.h"

extern cpuinfo cpu;
extern meminfo memory;
extern process_list_info process_list;
int row,col;

void draw_cpu(void)
{
	 printf("CPU: Model %s, Cores %d, utilization ",cpu.model,cpu.cores);
	 printf("%lf %lf %ld",cpu.lavg1,cpu.lavg5,cpu.lavg15);
	 printf("%%\n");
	 
}
void draw_memory(void)
{
	int unit = memory.totalMem / 50;
	int i,used = memory.usedMem / unit;

	printf("Mem: ");
	printf("Total %lld KB,  ",memory.totalMem);
    printf("Free %lld KB,  ", memory.freeMem);
	printf("Used %lld KB,  ", memory.usedMem);
    printf("Buffers %lld KB \n", memory.buffersMem);

}
void print_process_time(unsigned long long int totalHundredths) {
   unsigned long long totalSeconds = totalHundredths / 100;

   unsigned long long hours = totalSeconds / 3600;
   int minutes = (totalSeconds / 60) % 60;
   int seconds = totalSeconds % 60;
   int hundredths = totalHundredths - (totalSeconds * 100);

	if(hours)
	{
	   	printf("%lld:%d\t",hours,minutes);
	}
   	else
   	{
   		printf("%lld:%d.%d\t",hours,minutes,hundredths);
   	}
}

void draw_process(void)
{
	process_info *tmp;
	struct passwd *pw;
	
	
	printf("PID\tUSER\t\tPRI\tS\tCPU%%\tMEM%%\tTIME+\tCommand\n");
	tmp = process_list.process;
	while (tmp)
	{
		pw = getpwuid(tmp->uid);
		if(pw)
		{
			printf("%d\t%s\t\t%d\t%c\t%.2lf\t%.5f\t", 
				tmp->stat_info.pid, 
				pw->pw_name,
				tmp->stat_info.priority,
				tmp->stat_info.state,
				tmp->cpu_usage,
				tmp->mem_usage);
		}
		else
		{
			printf("%d\t%s\t\t%d\t%c\t%.2lf\t%.5f\t", 
				tmp->stat_info.pid, 
				"NO ONE",
				tmp->stat_info.priority,
				tmp->stat_info.state,
				tmp->cpu_usage,
				tmp->mem_usage);
		}
		print_process_time(tmp->stat_info.starttime);
		printf("%s\n",tmp->stat_info.command);
		tmp = tmp->next;
	}
	
}

