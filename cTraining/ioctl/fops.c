#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include <linux/slab.h>

#include "fops.h"
#include "main.h"

int ioctl_open(struct inode *inode, struct file *filp)
{
	filp->private_data  = container_of(inode->i_cdev,struct ioctl_dev,cdev);
	PDEBUG(": %s() is invoked\n",__FUNCTION__);
	return 0;
}

ssize_t ioctl_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	struct ioctl_dev *ioctl_dev;
	ioctl_dev = filp->private_data;
	PDEBUG(": quantum %d,qset %d\n",ioctl_dev->quantum,ioctl_dev->qset);
	return 0;
}

long ioctl_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	int err = 0,tmp = 0;
	int retval = 0;
	struct ioctl_dev *ioctl_dev;
	ioctl_dev = file->private_data;
	PDEBUG(": %s invokedn",__FUNCTION__);
	if(_IOC_TYPE(cmd) != IOCTL_IOC_MAGIC)
	{
		PDEBUG("TYPE not right\n");
		return -EFAULT;
	}

	if(_IOC_NR(cmd) > IOCTL_IOC_MAXNR)
	{
		PDEBUG("NR not right\n");
		return -EFAULT;
	}

	if (_IOC_DIR(cmd) & _IOC_READ)
    	err = !access_ok(VERIFY_WRITE, (void __user *)arg, _IOC_SIZE(cmd));
    else if (_IOC_DIR(cmd) & _IOC_WRITE)
    	err =  !access_ok(VERIFY_READ, (void __user *)arg, _IOC_SIZE(cmd));
    if (err) return -EFAULT;

    switch(cmd)
   	{
   		case IOCTL_IOCRESET:
   			ioctl_dev->quantum = IOCTL_QUANTUM;
   			ioctl_dev->qset = IOCTL_QSET;
   			break;

   		case IOCTL_IOCSQUANTUM:/* Set: arg points to the value */
   			if(!capable(CAP_SYS_ADMIN))
   				return -EPERM;
   			retval = __get_user(ioctl_dev->quantum,(int __user*)arg);
   			break;

		case IOCTL_IOCSQSET: /* Set: arg points to the value */
   			if(!capable(CAP_SYS_ADMIN))
   				return -EPERM;
			retval = __get_user(ioctl_dev->qset,(int __user*)arg);
			break;

		case IOCTL_IOCTQUANTUM:
			if(!capable(CAP_SYS_ADMIN))
   				return -EPERM;
   			ioctl_dev->quantum = arg;
			break;

		case IOCTL_IOCTQSET:
			if(!capable(CAP_SYS_ADMIN))
	   			return -EPERM;
   			ioctl_dev->qset = arg;
			break;

		case IOCTL_IOCGQUANTUM:
			retval = __put_user(ioctl_dev->quantum, (int __user *)arg);
			break;

		case IOCTL_IOCGQSET:
			retval = __put_user(ioctl_dev->qset, (int __user *)arg);
			break;

		case IOCTL_IOCQQUANTUM:
			return ioctl_dev->quantum;

		case IOCTL_IOCQQSET:
			return ioctl_dev->qset;

		case IOCTL_IOCXQUANTUM:
			if(!capable(CAP_SYS_ADMIN))
	   			return -EPERM;
	   		tmp = ioctl_dev->quantum;
	   		retval = __get_user(ioctl_dev->quantum,(int __user*)arg);
	   		if(retval == 0)
	   			retval = __put_user(tmp,(int __user*)arg);
			break;

		case IOCTL_IOCXQSET:
			if(!capable(CAP_SYS_ADMIN))
	   			return -EPERM;
	   		tmp = ioctl_dev->qset;
	   		retval = __get_user(ioctl_dev->qset,(int __user*)arg);
	   		if(retval == 0)
	   			retval = __put_user(tmp,(int __user*)arg);
			break;

		case IOCTL_IOCHQUANTUM:
			if(!capable(CAP_SYS_ADMIN))
	   			return -EPERM;
	   		tmp = ioctl_dev->quantum;
	   		ioctl_dev->quantum = arg;
	   		return tmp;

		default:
			break;
   	}
   	return retval;
}