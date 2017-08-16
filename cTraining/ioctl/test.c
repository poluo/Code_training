#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#define DEV_FILE		"/dev/ioctl"

#define IOCTL_IOC_MAGIC		'k'


#define IOCTL_IOCRESET    _IO(IOCTL_IOC_MAGIC, 0)

#define IOCTL_IOCSQUANTUM _IOW(IOCTL_IOC_MAGIC,  1, int)

#define IOCTL_IOCSQSET    _IOW(IOCTL_IOC_MAGIC,  2, int)

#define IOCTL_IOCTQUANTUM _IO(IOCTL_IOC_MAGIC,   3)

#define IOCTL_IOCTQSET    _IO(IOCTL_IOC_MAGIC,   4)

#define IOCTL_IOCGQUANTUM _IOR(IOCTL_IOC_MAGIC,  5, int)

#define IOCTL_IOCGQSET    _IOR(IOCTL_IOC_MAGIC,  6, int)

#define IOCTL_IOCQQUANTUM _IO(IOCTL_IOC_MAGIC,   7)

#define IOCTL_IOCQQSET    _IO(IOCTL_IOC_MAGIC,   8)

#define IOCTL_IOCXQUANTUM _IOWR(IOCTL_IOC_MAGIC, 9, int)

#define IOCTL_IOCXQSET    _IOWR(IOCTL_IOC_MAGIC,10, int)

#define IOCTL_IOCHQUANTUM _IO(IOCTL_IOC_MAGIC,  11)

#define IOCTL_IOCHQSET    _IO(IOCTL_IOC_MAGIC,  12)

int main(int argc, char *argv[])
{

	int fd = open(DEV_FILE, O_RDWR);
	int quant = 1024;
	int qset = 1;
	int err = ioctl(fd, IOCTL_IOCSQUANTUM,&quant);
	printf("retval = %d\n", err);
	err = ioctl(fd, IOCTL_IOCSQSET,&qset);
	printf("retval = %d\n", err);
	quant = 10;
	err = ioctl(fd,IOCTL_IOCXQUANTUM,&quant);
	printf("exchage quant %d\n", quant);
	// err = ioctl(fd, IOCTL_IOCRESET);
	// printf("retval = %d\n", err);

	return 0;	
}
