#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/hrtimer.h>
#include <linux/ktime.h>
 
//Timer Variable
#define TIMEOUT_NSEC   ( 1000000000L )      //1 second in nano seconds
#define TIMEOUT_SEC    ( 1 )                //2 seconds
static void even(int);
static struct hrtimer etx_hr_timer;
static unsigned int count;
static unsigned int x;
static unsigned int z;
static int __init etx_driver_init(void);
static void __exit etx_driver_exit(void);

//Timer Callback function. This will be called when timer expires
enum hrtimer_restart timer_callback(struct hrtimer *timer)
{
     /* do your timer stuff here */
    if(count%10==0)
    {
    even(count);
    pr_info("Timer Callback function Called [%d]\n",count);
    //count++;
    }
    count++;
    hrtimer_forward_now(timer,ktime_set(TIMEOUT_SEC, TIMEOUT_NSEC));
    return HRTIMER_RESTART;
}

static void even(int count)
{
 x=count;
 z=count+10;
  /*if(x>0)
  {
	if(x%2==0)
	{
		pr_info("%d ",x);
	}
 even(x-1);
 }*/
 if(x>z)
 { 
 	if(x%2==0)
	{
 	pr_info("%d ", x);
	}
 even(x+1);
 }
  return;
}
/**************** Module Init function*************************/ 
static int __init etx_driver_init(void)
{
    ktime_t ktime;  
    ktime = ktime_set(TIMEOUT_SEC, TIMEOUT_NSEC);
    hrtimer_init(&etx_hr_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
    pr_info("high resolution timer initialized\n");
    etx_hr_timer.function = &timer_callback;
    hrtimer_start( &etx_hr_timer, ktime, HRTIMER_MODE_REL);
    pr_info("high resolution timer started\n");
    return 0;

}

/**********************Module exit function******************/ 

static void __exit etx_driver_exit(void)
{
    //stop the timer
    hrtimer_cancel(&etx_hr_timer);
  
    pr_info("high resolution timer stopped\n");
}
 
module_init(etx_driver_init);
module_exit(etx_driver_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("jay");
MODULE_DESCRIPTION("A simple device driver - High Resolution Timer");
MODULE_VERSION("1.22");
