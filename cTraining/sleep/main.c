#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/wait.h>
#include "main.h"

static struct sleep_dev *my_dev;
int sleep_major = 0;

struct sleep_dev
{
    wait_queue_head_t my_queue;
    int wait_flag;
    struct cdev cdev;         /* Char device structure      */
};

int sleep_open(struct inode *inode, struct file *filp)
{
    struct sleep_dev *dev;
    dev = container_of(inode->i_cdev,struct sleep_dev,cdev);
    filp->private_data = dev;
    return 0;
}

ssize_t sleep_write(struct file *filp, const char  __user *buf, size_t count,loff_t *f_pos)
{
    struct sleep_dev *dev  = filp->private_data;
    PDEBUG(": write function invoked\n");
    dev->wait_flag = 1;
    wake_up_interruptible(&dev->my_queue);
    PDEBUG(": write function done\n");
    return count;

}
ssize_t sleep_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    struct sleep_dev *dev  = filp->private_data;
    PDEBUG(": read function invoked,may be sleep until someone write\n");
    wait_event_interruptible(dev->my_queue,dev->wait_flag);
    dev->wait_flag = 0;
    PDEBUG(": read function done\n");
    return 0;
}
static struct file_operations sleep_fops={
	.owner = THIS_MODULE,
	.open = sleep_open,
	.write = sleep_write,
	.read = sleep_read
};

static int __init m_init(void)
{
	dev_t dev_id;
	int retval,devno,err;

    retval = alloc_chrdev_region(&dev_id,0,DEVICE_COUNT,MODULE_NAME);
    sleep_major = MAJOR(dev_id);

    if(retval)
    {
    	PDEBUG(": register sleep dev failed\n");
    	return -1;
    }

	my_dev = kmalloc(sizeof(struct sleep_dev), GFP_KERNEL);
	if(!my_dev)
	{
		PDEBUG(":kmalloc failed on sleep_struct\n");
	    return -1;
    }
    init_waitqueue_head(&my_dev->my_queue);
    my_dev->wait_flag = 0;
    cdev_init(&my_dev->cdev, &sleep_fops);
	
    devno = MKDEV(sleep_major, 0);
    err = cdev_add(&my_dev->cdev, devno, 1);
    if (err)
    {
        kfree(my_dev);
        my_dev = NULL;
        PDEBUG(": Error %d adding sleep", err);
    }

	return 0;
}

static void __exit m_exit(void)
{
	dev_t dev_id = MKDEV(sleep_major,0);
	cdev_del(&my_dev->cdev);
    kfree(my_dev);
	unregister_chrdev_region(dev_id,1);
	PDEBUG(": Bye, sleep!\n");
}

module_init(m_init);
module_exit(m_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("cfn");
MODULE_DESCRIPTION("learning program");
