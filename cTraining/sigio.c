#include <signal.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>

static volatile sig_atomic_t get_sig = 0;

static void sigio(int sig)
{
	get_sig = 1;
}

static void alarm_handler(int sig)
{
	printf("print something to stdout\n");
}
int main(int argc, char const *argv[])
{
	struct sigaction sa;
	int flags, fd;

	fd = 1;//strtol(argv[1], NULL, 10)
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sigio;
	
	if(sigaction(SIGIO, &sa, NULL) == -1)
	{
		printf("sigaction error\n");
	}
	signal(SIGALRM,alarm_handler);
	alarm(2);

	if(fcntl(fd, F_SETOWN, getpid()) == -1)
	{
		printf("fctnl F_SETOWN\n");
	}

	flags = fcntl(fd, F_GETFL, 0);
    flags |= O_ASYNC | O_NONBLOCK;
    fcntl(fd, F_SETFL, flags);
    while(!get_sig);
    printf("%d\n",get_sig );
	return 0;
}