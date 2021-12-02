#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>

static int mydriver_init(void)
{
 printk(KERN_INFO "loaded");
 return 0;
}

static void mydriver_exit(void)
{
 printk(KERN_INFO "unloaded");
}

module_init(mydriver_init);
module_exit(mydriver_exit);

