#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/utsname.h> //for utsname()

static int howmany = 1;
static char *word = "wolrd";

module_param(howmany,int,S_IRUGO);
module_param(word,charp,S_IRUGO);

static int __init hello_init(void)
{
	int i = 0;
	atomic_t v;
	atomic_t u = ATOMCI_INIT(0);
	printk(KERN_ALERT "atomic_t u=%d\n",atomic_read(&u));
	atomic_set(&v,4);
	printk(KERN_ALERT "atomic_t v= %d\n",atomic_read(&v));
	atomic_add(2,&v);
	atomic_inc(&u);
	atomic_dec(&u);
	printk(KERN_ALERT "atomic_t v= %d\n",atomic_read(&v));
	printk(KERN_ALERT "atomic_t u=%d\n",atomic_read(&u));
	printk(KERN_ALERT "decrease and test %d\n"atomic_dec_and_test(&v));
    for(i = 0; i < howmany;i++)
    {
        printk(KERN_ALERT "Hello, %s\n",word);
    }
    printk(KERN_ALERT "kernel version:%s\n",utsname()->release);
	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_ALERT "Bye, World!\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("cfn");
MODULE_DESCRIPTION("learning program");
