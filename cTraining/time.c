#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	time_t now=0;
	struct timeval *tv = malloc(sizeof(struct timeval));
	char *ct = malloc(256);
	struct tm *split_time = malloc(sizeof(struct tm));
	now = time(NULL);
	printf("time() return %d\n",now);
	gettimeofday(tv,NULL);
	printf("gettimeofday() return %ds %dus\n",tv->tv_sec,tv->tv_usec);
	//time_t转换为可打印格式
	strcpy(ct,ctime(&now));
	printf("ctime() %s", ct);
	// time_t 转为分解时间,gmtime返回UTC时间，localtime返回本地分解时间
	split_time = localtime(&now);
	printf("local split time,year %d month %d day %d hour %d min %d \n",
		1990+split_time->tm_year,1+split_time->tm_mon,split_time->tm_mday,split_time->tm_hour,split_time->tm_min);
	//分解时间转换为可打印格式
	strcpy(ct,asctime(split_time));
	printf("asctime %s\n", ct);

	return 0;
}
