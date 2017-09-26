#include <poll.h>
#include <time.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	int (*pfds)[2];
	struct pollfd *pollfd;
	int num_pipe, num_write, i, rand,ready;

	num_pipe = strtol(argv[1],NULL,10);
	num_write = strtol(argv[2],NULL,10);
	pfds = calloc(num_pipe, sizeof(int [2]));
	pollfd = calloc(num_pipe,sizeof(struct pollfd));
	for ( i = 0; i < num_pipe; ++i)
	{
		if(pipe(pfds[i]) == -1)
		{
			printf("pipe %d error\n",i);
			exit(1);
		}
	}
	srandom((int)time(NULL));
	for (i = 0; i < num_write; ++i)
	{
		rand = random()%num_pipe;
		printf("write to %3d ,read %3d\n",
			pfds[rand][1],pfds[rand][0]);
		if(write(pfds[rand][1],"a",1) == -1)
		{
			printf("write pipe error %d\n", rand);
			exit(1);
		}
	}

	for (i = 0; i < num_pipe; ++i)
	{
		pollfd[i].fd = pfds[i][0];
		pollfd[i].events = POLLIN;
		/* code */
	}

	ready = poll(pollfd, num_pipe, -1);
	if(ready == -1)
	{
		printf("poll error happened \n");
		exit(1);
	}

	for (i = 0; i < num_pipe; ++i)
	{
		if(pollfd[i].revents & POLLIN)
		{
			printf("read %d %3d\n",i,pollfd[i].fd);
		}
	}

	return 0;
}