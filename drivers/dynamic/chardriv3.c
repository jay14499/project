#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/poll.h>
#include<linux/ioport.h>
#include<linux/errno.h>
#include<linux/cdev.h>
#include<linux/wait.h>
#include<linux/device.h>
MODULE_AUTHOR("jay");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("character driver using dynamic allocation");

//struct wait_queue_head_t wq,rq;
static DECLARE_WAIT_QUEUE_HEAD(wq);

struct class *cls;
struct device *dev;
dev_t devno=0; 

//static DECLARE_WAIT_QUEUE_HEAD(rq);
/*************************driver routines declarations*********************/

static int mychar_open(struct inode *inode,struct file *file);
static int mychar_close(struct inode *inode,struct file *file);
static ssize_t mychar_write(struct file *file,const char *buff,size_t len,loff_t *offset);
static ssize_t mychar_read(struct file *file,char *buff,size_t len,loff_t *offset);


/***************************device context info**************************/

struct dev_context
		{
		 char buf[1024];
		 int no_chars;
		 int base_address;    
		 int _IRQ_lineno;
		 struct cdev c_dev;
}my_context;

/*storing the base addresses or driver routines in function pointers */

static struct file_operations my_routines=
{
	.read=mychar_read,
	.open=mychar_open,
	.write=mychar_write,
	.release=mychar_close
};

/*******************************character driver inistilization**********/

static int mydev_init(void)
{
	int res=0;
	         //dev_t is a typedef of int in kernel
	//devno=MKDEV(42,0);      //MKDEV is a predefined macro which associates with major number nad minor number

	//init_waitqueue_head(&wq);
	//init_waitqueue_head(&rq);
       
	res=alloc_chrdev_region(&devno,0,2,"driv_char1");//registering driver with vfs layer of kernel
	if(res<0)
	{
		printk("<1>""driv_char is not loaded\n");
		return res;
	}
	else
	{
		printk(KERN_ALERT "driv_char is loaded succesfully\n");
	}
	cdev_init(&my_context.c_dev,&my_routines); //linking cdev_object and file operations

	my_context.c_dev.owner=THIS_MODULE; //THIS_MODULE predefined macro,it will return the base address of the driver

	res=cdev_add(&my_context.c_dev,devno,2); //after linking loading into kernel space
	if(res<0)
	{
		printk("<1>" "cdev_object is not loaded\n");
		//unregister_chrdev_region(devno,1); //unregistering the driv_char from kernel
	}

	printk(KERN_ALERT "cdev_object added succesfully\n");
	cls=class_create(THIS_MODULE,"cls_driv");
	dev=device_create(cls,NULL,devno,0,"driv_char1");
	
	

	my_context.no_chars=0;
	pr_info("<---MAJOR=%d--->\n",MAJOR(devno));
	pr_info("<---MINOR=%d--->\n",MINOR(devno));
	return res;
	
}


/*********************************char driver exit function**************************/

static void mydev_release(void)
{
	
	cdev_del(&my_context.c_dev); //deleting cdev_object
	device_destroy(cls,devno);
	class_destroy(cls);
	unregister_chrdev_region(devno,2);
	printk(KERN_ALERT "driv_char is unloaded successfully\n");
}

static int mychar_open(struct inode *inode,struct file *file)
{
 	try_module_get(THIS_MODULE);
 	file->private_data=&my_context;
 	if(file->f_mode& FMODE_READ)
 	  printk(KERN_ALERT "open for read mode\n");
 	if(file->f_mode & FMODE_WRITE)
 	  printk(KERN_ALERT "open for write mode\n");
 	return 0;
}
static int mychar_close(struct inode *inode,struct file *file)
{
	module_put(THIS_MODULE);
	printk(KERN_ALERT "device file is closed\n");
        return 0;
}
static ssize_t mychar_write(struct file *file,const char *buff,size_t len,loff_t *offset)
{
	struct dev_context *tdev;
	tdev=file->private_data; //storing the address of device context info of particular device file into a device context pointer
	if(len>1024)
	len=1024;
	//wait_event(wq,(tdev->no_chars>0)); //------wait queue object 
	copy_from_user(tdev->buf,buff,len); //1st arg is the destination adress of device context info member buf,2nd arg is the source address of application buf,3rd arg is len
//copying data from appication to kernel


	tdev->no_chars=len; //updating no of chars written to kernel (device context info member-buf)
	pr_info("%s\n", tdev->buf);
	//wake_up(&wq);       //wakeup call
	printk(KERN_ALERT "write is called\n");
 	return (ssize_t)len;
}
static ssize_t mychar_read(struct file *file,char *buff,size_t len,loff_t *offset)
{
	struct dev_context *tdev;
	tdev=file->private_data; //storing the adress of device context info of particular device file into a device context pointer

	//wait_event(wq,(tdev->no_chars>0));
	if(len > (tdev->no_chars))
	len=tdev->no_chars;
	copy_to_user(buff,tdev->buf,len); //2nd arg is the destination adress of device context info memeber buf, 1st arg is the source address of application data from kernel to application

	//wake_up(&rq);

	tdev->no_chars=0; //updating no of chars written to user(device context info member-buf)
	printk(KERN_ALERT "read is called\n");
        return (ssize_t)len; 
}


module_init(mydev_init);
module_exit(mydev_release);
