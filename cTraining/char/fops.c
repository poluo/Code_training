#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <asm/uaccess.h>

#include "fops.h"
int scull_quantum_size = 4096;
int scull_qset_size = 1000;

int scull_trim(struct scull_dev *dev)
{
	struct scull_qset *next, *dptr;
	int qset = dev->qset;
	int i;
	for(dptr = dev->data;dptr;dptr=next)
	{
		if(dptr->data)
		{
			for (i = 0; i < qset; ++i)
			{
				kfree(dptr->data[i]);
			}
			kfree(dptr->data);
			dptr->data = NULL;
		}
		next = dptr->next;
		kfree(dptr);
	}
	dev->size = 0;
	dev->quantum = scull_quantum_size;
	dev->qset = scull_qset_size;
	dev->data = NULL;
	return 0;
}
static struct scull_qset* scull_follow(struct scull_dev *dev,int item)
{
	struct scull_qset *qs = dev->data;
	int count = 0;
	struct scull_qset *next ,*dptr;
	printk(KERN_ALERT NAME ": scull_follow,item %d\n",item);
	if(!qs)
	{
		printk(KERN_INFO NAME ":data is NULL\n");
		qs = dev->data = kmalloc(sizeof(struct scull_qset),GFP_KERNEL);
		if(qs == NULL)
			return NULL;
		memset(qs,0,sizeof(struct scull_qset));
	}
	for(dptr = qs;dptr;dptr=next)
	{
		count ++;
		if(!dptr->next)
		{
			dptr->next = kmalloc(sizeof(struct scull_qset),GFP_KERNEL);
			if(dptr->next == NULL)
				return NULL;
			memset(dptr->next,0,sizeof(struct scull_qset));
		}
		if(count == item)
		{
			printk(KERN_ALERT NAME ": item found\n");
			return dptr->next;
		}	
		next = dptr->next;
	}
	return NULL;
}

int scull_open(struct inode *inode, struct file *filp)
{
	struct scull_dev *dev;
	dev = container_of(inode->i_cdev,struct scull_dev,cdev);
	filp->private_data = dev; /* for other methods */
	if((filp->f_flags & O_ACCMODE) == O_WRONLY) 
	{
		if(down_interruptible(&dev->sem))
			return -ERESTARTSYS;
		scull_trim(dev); /* ignore errors */
		up(&dev->sem);
		printk(KERN_INFO NAME ":%s\n invokedn",__FUNCTION__);
    }
    return 0;
}

int scull_release(struct inode *inode, struct file *filp)
{
    return 0;
}

ssize_t scull_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	struct scull_dev *dev  = filp->private_data;
	struct scull_qset *dptr;
	int quantum = dev->quantum,qset = dev->qset;
	int itemsize = quantum * qset;
	int item,s_pos,q_pos,reset;
	ssize_t retval = 0;

	if (down_interruptible(&dev->sem))
		return -ERESTARTSYS;

	if(*f_pos > dev->size)
		goto out;

	if(*f_pos + count > dev->size)
		count = dev->size - *f_pos;

	item = (long) *f_pos /itemsize;
	reset = (long) *f_pos % itemsize;
	s_pos = reset / quantum;
	q_pos = reset % quantum;

	dptr = scull_follow(dev,item);

	printk(KERN_INFO NAME ":%s\n invokedn",__FUNCTION__);

	if(dptr == NULL || !dptr->data || !dptr->data[s_pos])
		goto out;

	if(count > quantum - q_pos)
		count = quantum - q_pos;

	if(copy_to_user(buf,dptr->data[s_pos]+q_pos,count))
	{
		retval = -EFAULT;
		goto out;
	}
	*f_pos += count;
	retval = count;

	out:
		printk(KERN_ALERT NAME ": %s out\n",__FUNCTION__);
		up(&dev->sem);
		return retval;
}

ssize_t scull_write(struct file *filp, const char  __user *buf, size_t count,loff_t *f_pos)
{
	struct scull_dev *dev  = filp->private_data;
	struct scull_qset *dptr;
	int quantum = dev->quantum,qset = dev->qset;
	int itemsize = quantum * qset;
	int item,s_pos,q_pos,reset;
	ssize_t retval = -ENOMEM;

	if(down_interruptible(&dev->sem))
		return -ERESTARTSYS;

	item = (long)*f_pos / itemsize;
	reset = (long) *f_pos % itemsize;
	s_pos = reset / quantum;
	q_pos = reset % quantum;

	dptr = scull_follow(dev,item);
	if(dptr == NULL)
		goto out;

	if(!dptr->data)
	{
		dptr->data = kmalloc(qset * sizeof(char *),GFP_KERNEL);
		if(!dptr->data)
			goto out;
		memset(dptr->data,0,qset * sizeof(char *));
	}

	if (!dptr->data[s_pos]) 
	{
        dptr->data[s_pos] = kmalloc(quantum, GFP_KERNEL);
        if (!dptr->data[s_pos])
            goto out;
    }
    if (count > quantum - q_pos)
        count = quantum - q_pos;
    printk(KERN_INFO NAME ":%s\n invokedn",__FUNCTION__);
    if (copy_from_user(dptr->data[s_pos]+q_pos, buf, count)) 
    {
        retval = -EFAULT;
        goto out;
    }
    *f_pos += count;
    retval = count;
    if (dev->size < *f_pos)
        dev->size = *f_pos;
    out:
    	printk(KERN_ALERT NAME ": %s out\n",__FUNCTION__);
   		up(&dev->sem);
    	return retval;
}
