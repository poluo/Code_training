#include <stdio.h>
#include <sys/time.h>
#include <sys/select.h>


int main(int argc, char const *argv[])
{
	fd_set readfds, writefds;
	int ready,timeout_forever,nfds,i,num,fd;
	char buf[5];
	struct timeval timeout;

	if (strcmp(argv[1],"-") == 0)
	{
		timeout_forever = 1;
	}
	else
	{
		timeout_forever = 0;
		timeout.tv_sec = strtol(argv[1],NULL,10);
		timeout.tv_usec = 0;
	}

	nfds = 0;
	FD_ZERO(&readfds);
	FD_ZERO(&writefds);

	for (i = 2; i < argc; ++i)
	{
		printf("%s\n", argv[i]);
		num = sscanf(argv[i],"%d%2[rw]",&fd,buf);
		if(num != 2)
		{
			printf("%s illegal usae\n", argv[i]);
		}
		if(fd > nfds)
			nfds = fd + 1;

		if(strchr(buf,'r') != NULL)
			FD_SET(fd,&readfds);

		if(strchr(buf,'w') != NULL)
			FD_SET(fd,&writefds);
	}

	ready = select(nfds, &readfds, &writefds, NULL, timeout_forever ? NULL: &timeout);
	if (ready == -1)
	{
		printf("error happened in select\n");
	}
	printf("ready = %d\n",ready);

	for (i = 0; i < nfds; ++i)
	{
		printf("%d: %s%s\n",i,FD_ISSET(fd,&readfds) ? "r":"",FD_ISSET(fd,&writefds) ? "w":"");
	}
	printf("timeout after %ld.%03ld\n",(long)timeout.tv_sec,(long)timeout.tv_usec/10000);



	return 0;
}