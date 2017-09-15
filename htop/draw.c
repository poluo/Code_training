#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "linux_info.h"
#include "draw.h"

extern cpuinfo cpu;
extern meminfo memory;
extern process_list_info process_list;
int row,col;

void draw_cpu(void)
{
	 int use = cpu.utilization;
	 printf("CPU: Model %s, Cores %d, utilization ",cpu.model,cpu.cores);
	 printf("%.2lf",cpu.utilization);
	 printf("%\n");
	 
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
void printTime(unsigned long long int totalHundredths) {
   unsigned long long totalSeconds = totalHundredths / 100;

   unsigned long long hours = totalSeconds / 3600;
   int minutes = (totalSeconds / 60) % 60;
   int seconds = totalSeconds % 60;
   int hundredths = totalHundredths - (totalSeconds * 100);

	if(hours)
	{
	   	printf("%d:%d\t",hours,minutes);
	}
   	else
   	{
   		printf("%d:%d.%d\t",hours,minutes,hundredths);
   	}
}

void draw_process(void)
{
	int i;
	process_info tmp;
	printf("PID\tUSER\t\tPRI\tS\tCPU%\tMEM%\tTIME+\tCommand\n");
	for(i = 0; i < process_list.size && i <10; i++)
	{
		tmp = process_list.process[i];
		printf("%d\t%s\t\t%ld\t%c\t%.2lf\t%.5f\t",tmp.pid,tmp.user,tmp.priority,tmp.state,tmp.percent_cpu,0.0);
		printTime(tmp.time);
		printf("%s\n",tmp.command);
	}
	
}
void draw_panel()
{
	draw_cpu();
	draw_memory();
	draw_process();
}

