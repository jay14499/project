#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
MODULE_LICENSE("GPL2");
MODULE_AUTHOR("JAY");
static int __init mydriver_init(void)
{
	printk(KERN_INFO "loaded");
	pr_info("info");
	pr_emerg("emerg");
	pr_alert("alert");
	pr_err("error");
	pr_debug("debug");
	pr_crit("critical");
	pr_notice("notice");
	pr_warning("warning");
	return 0;
}

module_init(mydriver_init);
