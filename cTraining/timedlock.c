#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>

#define USECTONSEC 1000		/* microseconds to nanoseconds */

void myclock_gettime(int id, struct timespec *tsp)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	tsp->tv_sec = tv.tv_sec;
	tsp->tv_nsec = tv.tv_usec * USECTONSEC;
}

int main(int argc, char const *argv[])
{
	int err,t;
	struct timespec tout;
	struct tm *tmp;
	char buf[64];
	pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&lock);
	printf("mutex is locked\n");
	myclock_gettime(CLOCK_REALTIME,&tout);
	tmp = localtime(&tout.tv_sec);
	strftime(buf,sizeof(buf),"%r",tmp);
	printf("current time is %s\n",buf);
	if(argc == 2)
	{
		t = atoi(argv[1])
		printf("mutex will timeout in %d s\n",t);
		tout.tv_sec += t;
	}
	else
		tout.tv_sec += 5;
	err = pthread_mutex_timedlock(&lock,&tout);
	myclock_gettime(CLOCK_REALTIME,&tout);
	tmp = localtime(&tout.tv_sec);
	strftime(buf,sizeof(buf),"%r",tmp);
	printf("now time is %s\n",buf);
	if (err == 0)
	{
		printf("mutex locked again!\n");
	}
	else
		printf("can not lock again %s\n",strerror(err));

	exit(0);
}