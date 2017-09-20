#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <time.h>

static volatile int sig_alarm_count = 0;

static void sig_alarm_handler(int sig)
{
	sig_alarm_count = 1;
}

int main(int argc, char const *argv[])
{
	struct itimerval tv;
	struct sigaction sa;
	char *pend;
	clock_t old_clock;
	struct timespec req,remain;


	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sig_alarm_handler;
	if(sigaction(SIGALRM, &sa, NULL) == -1)
	{
		printf("sigaction SIGALARM error\n");
		return -1;
	}

	if(argc > 1)
	{
		tv.it_value.tv_sec = (argc > 1) ? strtol(argv,&pend,10):0;
		tv.it_value.tv_usec = (argc > 2) ? strtol(pend,&pend,10):0;
		tv.it_interval.tv_sec = (argc > 3) ? strtol(pend,&pend,10):0;
		tv.it_interval.tv_usec = (argc > 4) ? strtol(pend,&pend,10):0;
	}
	else
	{
		tv.it_value.tv_sec = 3;
		tv.it_value.tv_usec = 0;
		tv.it_interval.tv_sec = 3;
		tv.it_interval.tv_usec = 0;
	}

	printf("timer :%d %d %d %d\n",
		tv.it_value.tv_sec,tv.it_value.tv_usec,tv.it_interval.tv_sec,tv.it_interval.tv_usec );
	
	if(setitimer(ITIMER_REAL,&tv,0) == -1)
	{
		printf("set timer error\n");
		return -1;
	}

	req.tv_sec = 1;
	req.tv_nsec = 0; 
	//old_clock = clock();
	while(1)
	{
		#if 0
		while((clock() - old_clock) * 10/CLOCKS_PER_SEC < 5)
		{
			if(sig_alarm_count)
			{
				sig_alarm_count = 0;
				printf("timer timeout\n");
			}
		}
		old_clock = clock();
		printf("0.5s passed\n");
		#endif
		if(sig_alarm_count)
		{
			sig_alarm_count = 0;
			printf("timer timeout\n");
		}

		if(nanosleep(&req, &remain) == -1)
		{
			printf("nanosleep remain %ds %dns\n",remain.tv_sec,remain.tv_nsec);
			req = remain;
		}
		else
		{
			req.tv_sec = 1;
			req.tv_nsec = 0; 
			printf("1s passed\n");
		}
		
	}

	return 0;
}