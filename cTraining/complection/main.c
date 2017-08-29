#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/completion.h>
#include "main.h"

static struct completion_dev *my_dev;
int completion_major = 0;

struct completion_dev
{
    struct completion completion;
    struct cdev cdev;         /* Char device structure      */
};

int completion_open(struct inode *inode, struct file *filp)
{
    struct completion_dev *dev;
    dev = container_of(inode->i_cdev,struct completion_dev,cdev);
    filp->private_data = dev;
    return 0;
}

ssize_t completion_write(struct file *filp, const char  __user *buf, size_t count,loff_t *f_pos)
{
    struct completion_dev *dev  = filp->private_data;
    PDEBUG(": write function invoked\n");
    complete(&dev->completion);
    PDEBUG(": write function done\n");
    return count;

}
ssize_t completion_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    struct completion_dev *dev  = filp->private_data;
    PDEBUG(": read function invoked\n");
    wait_for_completion(&dev->completion);
    PDEBUG(": read function done\n");
    return 0;
}
static struct file_operations completion_fops={
	.owner = THIS_MODULE,
	.open = completion_open,
	.write = completion_write,
	.read = completion_read
};

static int __init m_init(void)
{
	dev_t dev_id;
	int retval,devno,err;

    retval = alloc_chrdev_region(&dev_id,0,DEVICE_COUNT,MODULE_NAME);
    completion_major = MAJOR(dev_id);

    if(retval)
    {
    	PDEBUG(": register completion dev failed\n");
    	return -1;
    }

	my_dev = kmalloc(sizeof(struct completion_dev), GFP_KERNEL);
	if(!my_dev)
	{
		PDEBUG(":kmalloc failed on completion_struct\n");
	    return -1;
    }
    init_completion(&my_dev->completion);
    cdev_init(&my_dev->cdev, &completion_fops);
	
    devno = MKDEV(completion_major, 0);
    err = cdev_add(&my_dev->cdev, devno, 1);
    if (err)
    {
        kfree(my_dev);
        my_dev = NULL;
        PDEBUG(": Error %d adding completion", err);
    }

	return 0;
}

static void __exit m_exit(void)
{
	dev_t dev_id = MKDEV(completion_major,0);
	cdev_del(&my_dev->cdev);
    kfree(my_dev);
	unregister_chrdev_region(dev_id,1);
	PDEBUG(": Bye, completion!\n");
}

module_init(m_init);
module_exit(m_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("cfn");
MODULE_DESCRIPTION("learning program");
