#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#define BUF_SIZE 2000

void set_fl(int fd, int flags) /* flags are file status flags to turn on */
{
	int	val;

	if ((val = fcntl(fd, F_GETFL, 0)) < 0)
		printf("fcntl F_GETFL error");

	val |= flags;		/* turn on flags */

	if (fcntl(fd, F_SETFL, val) < 0)
		printf("fcntl F_SETFL error");
}
void clr_fl(int fd, int flags)
				/* flags are the file status flags to turn off */
{
	int	val;

	if ((val = fcntl(fd, F_GETFL, 0)) < 0)
		printf("fcntl F_GETFL error");

	val &= ~flags;		/* turn flags off */

	if (fcntl(fd, F_SETFL, val) < 0)
		printf("fcntl F_SETFL error");
}

int main(int argc, char const *argv[])
{
	char buf[BUF_SIZE];
	char *ptr;
	int n_read,n_write;

	n_read = read(STDIN_FILENO,buf,sizeof(buf));
	fprintf(stderr, "read %d bytes\n",n_read);

	set_fl(STDOUT_FILENO,O_NONBLOCK);
	ptr = buf;
	while(n_read > 0)
	{
		errno = 0;

		n_write = write(STDOUT_FILENO, ptr, n_read)		;
		fprintf(stderr, "n_write =%d bytes,errno = %d\n",n_write,errno);
		if(n_write > 0)
		{
			ptr += n_write;
			n_read -= n_write;
		}
	}
	clr_fl(STDOUT_FILENO, O_NONBLOCK);
	return 0;
}