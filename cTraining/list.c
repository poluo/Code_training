#include <linux/init.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/types.h> 

#define print_message_info(fmt,args...) printk(KERN_INFO "[My Module] %s: " fmt,__func__,##args)

typedef struct module_info
{
    u8 module_id;
    char *module_name;
    struct list_head module_info_node;
}module_info;

module_info *create_module(u8 module_id,char *module_name)
{
    module_info *module = (module_info *)kmalloc(sizeof(module_info),GFP_KERNEL);
    if(module == NULL)
    {
        print_message_info("module malloc memory failed\n");
        return NULL;
    }

    module->module_id = module_id;
    module->module_name = (char *)kmalloc(sizeof(char)*sizeof(module_name),GFP_KERNEL);
    if(module->module_name == NULL)
    {
        print_message_info("module name molloc memory failed\n");
        return NULL;
    }
    strcpy(module->module_name,module_name);
    return module;
}
static int __init  hello_init(void)
{
    module_info *first_module = create_module(0,"Hello");
    module_info *module;
    struct list_head *pos,*head,*tmp;
    if(first_module == NULL)
    {
        return -1;
    }
    head = &(first_module->module_info_node);
    /*初始化链表头结点*/
    INIT_LIST_HEAD(head);
    
    module = create_module(1,"TEST1");
    /*从节点尾部添加节点*/
    list_add_tail(&module->module_info_node,head);
    module = create_module(2,"TEST2");
    list_add_tail(&module->module_info_node,head);
    module = create_module(3,"TEST3");
    list_add_tail(&module->module_info_node,head);
    print_message_info("Enter module: name %s id %d\n",first_module->module_name,first_module->module_id);
    module = list_entry((head)->prev,module_info,module_info_node);
    print_message_info("The last module name %s id %d \n",module->module_name,module->module_id);
    
    module = create_module(4,"TEST4");
    /*链表替换，把1替换为4*/
    list_replace((head)->next,&module->module_info_node);
    /*把4 移到链表尾，移动还有list_move移到链表头*/
    list_move_tail(&module->module_info_node,head);
    /*安全遍历链表，注意与list_for_each的区别*/
    list_for_each_safe(pos,tmp,head)
    {
        module = list_entry(pos,module_info,module_info_node);
        print_message_info("module: name %s id %d\n",module->module_name,module->module_id);
        if(module->module_id == 3)
        {
            print_message_info("module id 3 will be delete\n");
            list_del(pos);
        }
    }
    
    module = list_entry((head)->prev,module_info,module_info_node);
    print_message_info("The last module name %s id %d \n",module->module_name,module->module_id);
    kfree(module);
    kfree(first_module);
    return 0;

}

static void __exit hello_exit(void)
{
    print_message_info("Hello World exit\n ");
}

 

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("BSD/GPL");
MODULE_AUTHOR("cfn");
MODULE_DESCRIPTION("A simple HelloWorld Module");
MODULE_ALIAS("a simplestmodule");
