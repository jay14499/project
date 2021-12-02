#include<linux/module.h>
#include<linux/kernel.h>
static void __exit mydriver_exit(void)
{
	printk(KERN_INFO "unloaded");
	
}

module_exit(mydriver_exit);
