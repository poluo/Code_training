#ifndef _FOPS_H
#define _FOPS_H

struct scull_qset {
    void **data;
    struct scull_qset *next;
};

struct scull_dev
{
	struct scull_qset *data;  /* Pointer to first quantum set */
    int quantum;              /* the current quantum size */
    int qset;                 /* the current array size */
    unsigned long size;       /* amount of data stored here */
    unsigned int access_key;  /* used by sculluid and scullpriv */
    struct semaphore sem;     /* mutual exclusion semaphore     */
    struct cdev cdev;     	  /* Char device structure      */
};

extern int scull_open(struct inode *inode, struct file *filp);

extern int scull_release(struct inode *inode, struct file *filp);

extern ssize_t scull_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos);

extern ssize_t scull_write(struct file *filp, const char  __user *buf, size_t count,loff_t *f_pos);

extern int scull_trim(struct scull_dev *dev);
#endif