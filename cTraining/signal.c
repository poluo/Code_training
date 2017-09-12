#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static void signal_handler(int sig)
{
	printf("get singal %d,Ouch\n",sig);
}
static void sig_usr(int sig)
{
	if(sig == SIGUSR1)
		printf("received SIGUSR1\n");
	else if(sig == SIGUSR2)
		printf("received SIGUSR2\n");
	else
		printf("received signal %d\n", sig);
}
int main(int argc, char const *argv[])
{
	int i = 0;
	if(signal(SIGINT,signal_handler) == SIG_ERR)
		printf("catch signal handler error\n");
	if(signal(SIGUSR1,sig_usr) == SIG_ERR)
		printf("catch SIGUSR1 failed\n");
	if(signal(SIGUSR2,sig_usr) == SIG_ERR)
		printf("catch SIGUSR2 failed\n");
	for (; ; )
	{
        pause();
	}
	return 0;
}
