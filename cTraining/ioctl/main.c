#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/timer.h>

#include "fops.h"
#include "main.h"

static int ioctl_major = 0,ioctl_minor = 0;

static struct file_operations fops={
	.owner = THIS_MODULE,
	.open = ioctl_open,
	.read = ioctl_read,
    .unlocked_ioctl = ioctl_ioctl,
};
struct ioctl_dev *ioctl_dev = NULL;
static struct timer_list mytimer;

static void mytimer_func(unsigned long data)
{
    printk("received timer msg,data %ld\n",data);
    mod_timer(&mytimer, jiffies + 5*HZ);
}

static int __init ioctl_init(void)
{
	dev_t dev_id;
	int retval,devno,err;

	if(ioctl_major)
	{
		dev_id = MKDEV(ioctl_major,ioctl_minor);
		retval = register_chrdev_region(dev_id,DEVICE_COUNT,MODULE_NAME);
	}
    else
    {
    	retval = alloc_chrdev_region(&dev_id,ioctl_minor,DEVICE_COUNT,MODULE_NAME);
    	ioctl_major = MAJOR(dev_id);
    }

    if(retval)
    {
    	PDEBUG(": register ioctl failed in get major id\n");
    	return -1;
    }

    ioctl_dev = kmalloc(sizeof(struct ioctl_dev),GFP_KERNEL);

    if(ioctl_dev == NULL)
    {
    	PDEBUG(": register ioctl failed, because of kmalloc struct ioctl_dev failed\n");
    	return -1;
    }

    ioctl_dev->quantum = IOCTL_QUANTUM;
    ioctl_dev->qset = IOCTL_QSET;

    cdev_init(&ioctl_dev->cdev,&fops);
    ioctl_dev->cdev.owner = THIS_MODULE;
    ioctl_dev->cdev.ops = &fops;

    devno = MKDEV(ioctl_major, ioctl_minor);
    err = cdev_add(&ioctl_dev->cdev, devno, DEVICE_COUNT);
    if(err)
    {
    	kfree(ioctl_dev);
    	ioctl_dev = NULL;
    	PDEBUG(": Error %d in register ioctl", err);
    }

    setup_timer(&mytimer, mytimer_func, 20);
    mod_timer(&mytimer,jiffies + 1*HZ);
    //mytimer.expires = jiffies + 1*HZ;
    //add_timer(&mytimer);
    PDEBUG(": register ioctl success\n");
	return 0;
}

static void __exit ioctl_exit(void)
{
	dev_t dev_id = MKDEV(ioctl_major,ioctl_minor);
	cdev_del(&ioctl_dev->cdev);
	unregister_chrdev_region(dev_id,DEVICE_COUNT);
    del_timer_sync(&mytimer);
	PDEBUG(": Bye, ioctl_exit!\n");
}

module_init(ioctl_init);
module_exit(ioctl_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("cfn");
MODULE_DESCRIPTION("learning program");
