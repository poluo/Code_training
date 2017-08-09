#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <asm/uaccess.h>
#include <linux/slab.h>

#include "fops.h"
#include "main.h"

extern int scull_quantum_size;
extern int scull_qset_size;

static int scull_major = 0,scull_minor = 0;

static struct scull_dev *scull_dev[DEVICE_COUNT];

static struct file_operations scull_fops={
	.owner = THIS_MODULE,
	.open = scull_open,
	.write = scull_write,
	.read = scull_read,
	.release= scull_release
};

static void scull_setup_cdev(struct scull_dev *dev, int index)

{
    int err, devno = MKDEV(scull_major, scull_minor + index);
    cdev_init(&dev->cdev, &scull_fops);
    dev->cdev.owner = THIS_MODULE;
    dev->cdev.ops = &scull_fops;
    dev->quantum = scull_quantum_size;
    dev->qset = scull_qset_size;
    dev->data = NULL;
    err = cdev_add(&dev->cdev, devno, 1);
    if (err)
    {
    	kfree(dev);
    	dev = NULL;
    	PDEBUG(": Error %d adding scull%d", err, index);
    }
}

static int __init scull_init(void)
{
	dev_t dev_id;
	int retval,i;
	if(scull_major)
	{
		dev_id = MKDEV(scull_major,scull_minor);
		retval = register_chrdev_region(dev_id,DEVICE_COUNT,MODULE_NAME);
	}
    else
    {
    	retval = alloc_chrdev_region(&dev_id,0,DEVICE_COUNT,MODULE_NAME);
    	scull_major = MAJOR(dev_id);
    }

    if(retval)
    {
    	PDEBUG(": register chrdev failed\n");
    	return -1;
    }
    for(i = 0; i <DEVICE_COUNT; i++)
    {
    	scull_dev[i] = kmalloc(sizeof(struct scull_dev), GFP_KERNEL);
    	if(!scull_dev[i])
    	{
    		PDEBUG(":kmalloc failed on scull%d\n",i);
    		continue;
    	}
        scull_dev[i]->quantum = scull_quantum_size;
        scull_dev[i] ->qset = scull_qset_size;
        sema_init(&scull_dev[i]->sem,1);
    	scull_setup_cdev(scull_dev[i],i);
    }
    PDEBUG(": register chrdev success\n");
	return 0;
}

static void __exit scull_exit(void)
{
	int i = 0;
	dev_t dev_id = MKDEV(scull_major,scull_minor);
	for(i = 0;i<DEVICE_COUNT;i++)
	{
		cdev_del(&scull_dev[i]->cdev);
		scull_trim(scull_dev[i]);
        PDEBUG(": unregister chadev %d\n",i);
		// kfree(scull_dev[i]);
	}

	unregister_chrdev_region(dev_id,DEVICE_COUNT);
	PDEBUG(": Bye, scull!\n");
}

module_init(scull_init);
module_exit(scull_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("cfn");
MODULE_DESCRIPTION("learning program");
