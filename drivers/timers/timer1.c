#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/timer.h>
#include<linux/jiffies.h>
static void mykmod_timer_handler(struct timer_list *data);
static unsigned long onesec;
struct timer_list mytimer;

DEFINE_TIMER(mytimer,mykmod_timer_handler);

static void mykmod_timer_handler(struct timer_list *data)
{
	unsigned long j=jiffies;
	pr_info("driver timer handler is invoked at jiffies %u\n" ,(unsigned )j);
	mod_timer(&mytimer,jiffies+onesec);
}

static int driver_init(void)
{
	unsigned long j=jiffies;
	onesec=msecs_to_jiffies(1000*1);
	pr_info("driver is loaded %u %u jiffies before modification",(unsigned)j,(unsigned)onesec);
	//mod_timer(&mytimer,jiffies+onesec);
	add_timer(&mytimer);
	timer_pending(&mytimer);
	pr_info("driver is loaded %u jiffies after modification\n",(unsigned)j);
	return 0;
}

static void driver_exit(void)
{
	del_timer(&mytimer);
	pr_info("unloaded driver succesfully\n");
}

module_init(driver_init);
module_exit(driver_exit);
