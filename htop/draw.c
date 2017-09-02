#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "linux_info.h"
#include "draw.h"

extern cpuinfo cpu;
extern meminfo memory;
extern process_list_info process_list;
int row,col;
void draw_init()
{
    initscr();
    if(has_colors())
    {
        start_color();
        init_pair(0,COLOR_BLACK,COLOR_BLACK);
        init_pair(1,COLOR_GREEN,COLOR_BLACK);
        init_pair(2,COLOR_RED,COLOR_BLACK);
        init_pair(3,COLOR_CYAN,COLOR_BLACK);
        init_pair(4,COLOR_WHITE,COLOR_BLACK);
        init_pair(5,COLOR_MAGENTA,COLOR_BLACK);
        init_pair(6,COLOR_BLUE,COLOR_BLACK);
        init_pair(7,COLOR_YELLOW,COLOR_BLACK);
		init_pair(8,COLOR_BLACK,COLOR_CYAN);
		getmaxyx(stdscr,row,col);
		echo();
    }
    else
    {
        printf("there is no color\n");
    }
}
void draw_cpu(void)
{
	 int i = 0;
	 int use = cpu.utilization / 2;
	 //move(1,1);
	 printc(COLOR_DEFAULT_TEXT,"CPU Model: %s,CORE Number:%d,utilization:",cpu.model,cpu.cores);
	 printc(COLOR_ALERT_TEXT,"%.2f\n",cpu.utilization);
	 printc(COLOR_WHITE_TEXT,"[");
	 for(i = 0; i < use; i++)
	 {
	 	printc(COLOR_CPU_USED_TEXT,"|");
	 }
	 for(;i< 100 /2;i++)
	 {
	 	printc(COLOR_DEFAULT_TEXT,"|");
	 }
	 printc(COLOR_WHITE_TEXT,"]\n");
	 
}
void draw_memory(void)
{
	int unit = memory.totalMem / 50;
	int i,used = memory.usedMem / unit;
	printc(COLOR_WHITE_TEXT,"[");
	for(i = 0; i < used; i++)
	{
		printc(COLOR_CPU_USED_TEXT,"|");
	}
	for(;i< 100 /2;i++)
	{
	 	printc(COLOR_DEFAULT_TEXT,"|");
	}
	printc(COLOR_ALERT_TEXT,"%d/%d",memory.usedMem,memory.totalMem);
	printc(COLOR_WHITE_TEXT,"]\n");
}
void printTime(unsigned long long int totalHundredths) {
   unsigned long long totalSeconds = totalHundredths / 100;

   unsigned long long hours = totalSeconds / 3600;
   int minutes = (totalSeconds / 60) % 60;
   int seconds = totalSeconds % 60;
   int hundredths = totalHundredths - (totalSeconds * 100);

	if(hours)
	{
	   	printc(COLOR_DEFAULT_TEXT,"%d:%d\t",hours,minutes);
	}
   	else
   	{
   		printc(COLOR_DEFAULT_TEXT,"%d:%d.%d\t",hours,minutes,hundredths);
   	}
}

void draw_process(void)
{
	int i;
	process_info tmp;
	printc(COLOR_PROCESS_HEADER,"PID\tUSER\t\tPRI\tS\tCPU%\tMEM%\tTIME+\tCommand\n");
	for(i = 0; i < process_list.size && i <10; i++)
	{
		tmp = process_list.process[i];
		printc(COLOR_DEFAULT_TEXT,"%d\t%s\t\t%ld\t%c\t%.2f\t%.2f\t",tmp.pid,tmp.user,tmp.priority,tmp.state,0.0,0.0);
		printTime(tmp.time);
		printc(COLOR_DEFAULT_TEXT,"%s\n",tmp.command);
	}
	
}
void draw_panel()
{
	printc(COLOR_DEFAULT_TEXT,"-----------Chat-----------\n");
	printc(COLOR_DEFAULT_TEXT,"Time:\n");
	printc(COLOR_DEFAULT_TEXT,"User:\n");
	printc(COLOR_DEFAULT_TEXT,"Content:\n");
	printc(COLOR_DEFAULT_TEXT,"Time:\n");
	printc(COLOR_DEFAULT_TEXT,"User:\n");
	printc(COLOR_DEFAULT_TEXT,"Content:\n");
	printc(COLOR_DEFAULT_TEXT,"-----------Chat-----------\n");
	draw_cpu();
	draw_memory();
	draw_process();
}
void draw_done()
{
    endwin();
}
