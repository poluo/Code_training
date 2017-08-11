#ifndef _FOPS_H
#define _FOPS_H

#include <linux/ioctl.h>
#define IOCTL_QUANTUM 	2000
#define IOCTL_QSET 		10
#define IOCTL_IOC_MAGIC  'k'
/*
 * S means "Set" through a ptr,
 * T means "Tell" directly with the argument value
 * G means "Get": reply by setting through a pointer
 * Q means "Query": response is on the return value
 * X means "eXchange": switch G and S atomically
 * H means "sHift": switch T and Q atomically

 */
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

#define IOCTL_IOC_MAXNR 14

extern int ioctl_open(struct inode *inode, struct file *filp);

extern ssize_t ioctl_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos);

extern long ioctl_ioctl(struct file *filp, unsigned int cmd, unsigned long arg);

struct ioctl_dev
{
    int quantum;              /* the current quantum size */
    int qset;                 /* the current array size */
    struct cdev cdev;     	  /* Char device structure      */
};
#endif