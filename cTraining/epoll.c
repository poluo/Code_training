#include <sys/epoll.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_EVENTS_NUM 	10
#define MAX_BUF	1024
int main(int argc, char const *argv[])
{
	int epfd, i, fd, num, ready, s;
	struct epoll_event ev;
	struct epoll_event evlist[MAX_EVENTS_NUM];
	char buf[MAX_BUF];

	epfd = epoll_create(argc - 1);
	for (i = 1; i < argc; ++i)
	{
		fd = open(argv[i], O_RDONLY);
		if(fd == -1)
		{
			printf("error open %s \n", argv[i]);
			exit(1);
		}
		printf("%s opened on fd %d\n",argv[i], fd);
		ev.events = EPOLLIN;
		ev.data.fd = fd;
		if(epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) == -1)
		{
			printf("epoll ecnt %s \n",argv[i]);
			exit(1);
		}
	}
	num = argc -1;

	while(num > 0)
	{
		printf("epoll_wait\n");
		ready = epoll_wait(epfd, evlist, MAX_EVENTS_NUM, -1);
		if(ready == -1)
		{
			if(errno == EINTR)
			{
				continue;
			}
			else
			{
				printf("error in epoll wait\n");
				exit(1);
			}
		}

		for (i = 0; i < ready; ++i)
		{
			printf("%d events %s %s %s\n", evlist[i].data.fd,
					(evlist[i].events & EPOLLIN) ? "EPOLLIN" : "",
					(evlist[i].events & EPOLLHUP) ? "EPOLLHUP" : "",
					(evlist[i].events & EPOLLERR) ? "EPOLLERR" : "");
			if(evlist[i].events & EPOLLIN)
			{
				s = read(evlist[i].data.fd,buf,MAX_BUF);
				if (s == -1)
				{
					printf("error on read %d\n", evlist[i].data.fd);
				}
				buf[s] = '\0';
				printf("read %s on %d\n",buf,evlist[i].data.fd);
			}
			else if(evlist[i].events & (EPOLLERR|EPOLLHUP))
			{
				printf("close fd %d\n",evlist[i].data.fd);
				if(close(evlist[i].data.fd) == -1)
				{
					printf("close fd %d error\n", evlist[i].data.fd);
				}
				num--;
			}
		}

	}
	printf("all file closed\n");
	return 0;
}