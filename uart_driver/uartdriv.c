#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/poll.h>
#include<linux/ioport.h>
#include<linux/errno.h>
#include<linux/proc_fs.h>
#include<linux/io.h>
#include<linux/interrupt.h>
#include<linux/sched.h>


MODULE_LICENSE("GPL");

/* fileoperation declarations */
static int uart_open(struct inode *inode,struct file *file);
static int uart_close(struct inode *inode,struct file *file);
static int uart_read(struct file *file,char *buf,size_t count,loff_t *offset);
static int uart_write(struct file *file,char *buf,size_t count,loff_t *offset);


#define MYDEV_MAJOR_NUM 42 
#define MYDEV_NAME      "uart"
#define SER_IOBASE      0x3f8
#define SER_IRQ         4

static struct file_operations uart_ops=
{
	.read     = uart_read;
	.write    = uart_write;
	.open     = uart_open;
	.release     = uart_close;
};


#define SUCCESS          0
#define MAXSIZE          4000
#define DATA             0
#define DIV_LATCH_LOW    0
#define DIV_LATCH_HIGH   1
#define IER              1    
#define IIR              2
#define DFR              3
#define MDMC             4
#define LSR              5

#define SER_DEV "uartdev"

/*** circular queue ***/
typedef struct CircularBuf
{
	int RDINDEX;
	int WRINDEX;
	int NoOfChar;
	char Buf[MAXSIZE];
}cblock_t;

struct dev_context
		{
		 char buf[1024];
		 int no_chars;
		 int base_address;    
		 int _IRQ_lineno;
		 struct cdev c_dev;
}my_context;

cblock_t cblkp;

/*********************************************************************************************************************
* Name:int_receiv
*
*description:
             this function receives characters from serial port and store in receive
             queue and give semaphore
*parameters:
 input:control block pointer
returns:nothing
***********************************************************************************************************************/

static void int_Receiv()  /*RI */
{
 while(inb(cblkp.baseAddr+LSR) & 0x1)/* inb=data from device to comp*/
 {
   if(cblkp.Rxq.NoofChar <MAXSIZE)
   {
     cblkp.Rxq.Buf[cblkp.Rxq.WRINDEX]=inb(cblkp.baseAddr+DATA);
     cblkp.Rxq.WRINDEX++;
     cblkp.Rxq.NoofChar++;
     if(cblkp.Rxq.WRINDEX == MAXSIZE)
        cblkp.Rxq.WRINDEX=0;
   }
   else
   {
     inb(cblkp.baseAddr+DATA);
   }
 }
 wake_up_interruptable(&cblkp.rxWq);
}


/*********************************************************************************************************************
* Name:int_transmit
*
*description:
             this function is called when transmit interrupt comes.
             this function responsibility is taking characters transmit queue and  
             transmit too serial port. 
*parameters:
 input:device control block pointer
returns:SER_DEV
  nothing
***********************************************************************************************************************/

static void int_Transmit() 
{
   if(cblkp.Txq.NoofChar ==0)
   {
     /* disable transmit interrupt */
     outb((inb(cblkp.baseAddr+IER) & 0xfd),cblkp.baseAddr+IER);
     return;
   }
   else
   {
     while((inb(cblkp.baseAddr+LSR) & 0x20) && (cblkp.Txq.NoofChar))/*verifying 5th bit of LSR && total noof chars -->0 */
     {
     outb(cblkp.Txq.Buf[cblkp.Txq.RDINDEX++],cblkp.baseAddr+DATA);/* Tx buf ->THR */
     cblkp.Txq.NoofChar--;/* decrementing total noof chars */
     if(cblkp.Txq.RDINDEX == MAXSIZE)
        cblkp.Txq.RDINDEX=0;
     }
 wake_up_interruptable(&cblkp.txWq);
   }
}
/*********************************************************************************************************************
* Name:myinthandler
*description:
***********************************************************************************************************************/

static irqreturn_t myIntHandler(int irq,void *dev_id,struct pt_regs *regs)
{
 unsigned char intStat;

  intStat=inb(cblkp.baseAddr+IIR);
  while((intStat & 1 )==0)/* interrupt is pending or not */
  {
    if((intStat & 0x2)==0x2)/* verifying 1st bit of IIR -TI */
      int_Transmit();
    if((intStat & 0x4)==0x4)/* verifying 2nd bit of IIR -RI */
      int_Receiv();
    intStat=inb(cblkp.baseAddr+IIR);
  }
  return IRQ_HANDLED;
}

static int serInit(int irq,unsigned int baseaddr)
{
   cblkp.Rxq.RDINDEX=0;
   cblkp.Rxq.WRINDEX=0;
   cblkp.Rxq.NoofChar=0;
   cblkp.Txq.RDINDEX=0;
   cblkp.Txq.WRINDEX=0;
   cblkp.Txq.NoofChar=0;
    
   cblkp.baseAddr=baseaddr;
   cblkp.irq=irq;
 
   sema_init(&cblkp.sem,1);
   init_waitqueue_head(&cblkp.rxWq);
   init_waitqueue_head(&cblkp.txWq);

   /*** set the baud rate ***/
   outb(0x83, cblkp.baseAddr+LCR);
   outb(0x01, cblkp.baseAddr+DIV_LATCH_LOW);
   outb(0x00, cblkp.baseAddr+DIV_LATCH_HIGH);
   outb(0x03, cblkp.baseAddr+LCR);
   outb(0x0b, cblkp.baseAddr+MDMC);
   outb(0x0, cblkp.baseAddr+IER);
   /*** enable fifos ***/
   outb(0x70, cblkp.baseAddr+IIR);
 /* install isr for serial port */
//if(request_irq(irq,myIntHandler,SA_INTERRUPT,SER_DEV,NULL))
  if(request_irq(irq,myIntHandler,IRQF_DISABLED,SER_DEV,NULL))
    {
      printk("<1>cant get interrupt %d\n",irq);
      return -1;
    }
  return 0;
}

/*********************************************************************************************************************
* Name:init_module
*description:
***********************************************************************************************************************/

int uart_init(void)
{
   int res;
   res=register_chrdev_region(MYDEV_MAJOR_NUM,SER_DEV,&uart_ops);
   if(res<0)
   {
     printk("<1>" "registration error %d\n",res);
      return res;
  }
  else
  {
    printk("<1>" "registration success %d\n",res);
  }   
  if(!request_region(SER_IOBASE,8,SER_DEV))
  {
    printk(KERN_INFO "cant get I/O port address 0x3f8 \n");
      return -1;
  }
 cdev_init(&my_context.c_dev,&uart_ops); //linking cdev_object and file operations

	my_context.c_dev.owner=THIS_MODULE; //THIS_MODULE predefined macro,it will return the base address of the driver

	res=cdev_add(&my_context.c_dev,MYDEV_MAJOR_NUM,1); //after linking loading into kernel space
	if(res<0)
	{
		printk("<1>" "cdev_object is not loaded\n");
		//unregister_chrdev_region(devno,1); //unregistering the driv_char from kernel
	}

	printk(KERN_ALERT "cdev_object added succesfully\n");
  return serInit(SER_IRQ,SER_IOBASE);
}

/*********************************************************************************************************************
* Name:cleanup_module
*description:
***********************************************************************************************************************/

void uart_cleanup(void)
{
   unregister_chrdev(MYDEV_MAJOR_NUM,SER_DEV);
   free_irq(SER_IRQ,NULL);
   release_region(SER_IOBASE,8);  
   printk(KERN_ALERT "good bye \n");
}


/*********************************************************************************************************************
* Name:uart_open
*description:
***********************************************************************************************************************/

static int uart_open(struct inode *inode,struct file *file)
{
   try_module_get(THIS_MODULE);
   if(file->f_mode & FMODE_READ)
     printk("<1>" "open for read \n");
   if(file->f_mode & FMODE_WRITE)
     printk("<1>" "open for write \n");
   /*** enable interrupts on serial port 1 ***/
  outb(1,cblkp.baseAddr+IER);
  return 0;
}


/*********************************************************************************************************************
* Name:uart_close
*description:
***********************************************************************************************************************/

static int uart_close(struct inode *inode,struct file *file)
{
   module_put(THIS_MODULE);
   if(file->f_mode & FMODE_READ)
     printk("<1>" "device closed \n");
   /*** disable receive interrupts  ***/
  outb((inb(cblkp.baseAddr+IER) & 0xfe),cblkp.baseAddr+IER);
  return 0;
}

/*********************************************************************************************************************
* Name:uart_read
*description:
***********************************************************************************************************************/

static int uart_read(struct file *file,char *buf,size_t count,loff_t *offset)
{
   int cLen;
   int partlen;
   printk("<5>" "read called\n");
   wait_event_interruptable(cblkp.rxwq,cblkp.Rxq.NoofChar >0);
   if(len <    cblkp.Rxq.NoofChar)
     cLen=len;
   else
    cLen=cblkp.Rxq.NoofChar;
   if((cblkp.Rxq.RDINDEX+cLen) <= MAXSIZE)
   {
     copy_to_user(buf,cblkp.Rxq.Buf+cblkp.Rxq.RDINDEX,cLen);
   }
   else
   {
     partlen=MAXSIZE-cblkp.Rxq.RDINDEX;
     copy_to_user(buf,cblkp.Rxq.Buf+cblkp.Rxq.RDINDEX,partlen);
     copy_to_user(buf+partlen,cblkp.Rxq.Buf,cLen -partlen);
   }
   cblkp.Rxq.RDINDEX=(cblkp.Rxq.RDINDEX+cLen) % MAXSIZE;
   cblkp.Rxq.NoofChar -=cLen;
 return(cLen);
}

/*********************************************************************************************************************
* Name:uart_write
*description:
***********************************************************************************************************************/

static int uart_write(struct file *file,char *buf,size_t count,loff_t *offset)
{
   int avllen,copylen,partlen;
   int culen=count;
   printk("<1>" "write called\n"); 
   while(culen)
	{
		wait_event_interruptible(cblk.txWq,cblkp.Txq.NoofChar<MAXSIZE);
		printk("After block\n");
		if(down_interruptible(&cblkp.sem))
		return -ERESTARTSYS;
		avllen=MAXSIZE - cblkp.Txq.Buf+cblkp.Txq.WrIndex,buf,partlen);
		copylen=(culen<avllen) ? culen :avllen;
		if((cblk.Txq.WrIndex+copylen)<=MAXSIZE)
		{
		 copy_from_user(cblk.Txq.Buf+cblkp.Txq.WrIndex,buf,copylen);
		}
		else
		{
		 partlen=MAXSIZE - cblk.Txq.WrIndex;
		copy_from_user(cblk.Txq.Buf+cblkp.Txq.WrIndex,buf,partlen);
		copy_from_user(cblk.Txq.Buf,buf+partlen,copylen-patrlen);
		}
		cblk.Txq.WrIndex = (cblk.Txq.WrIndex+copylen)%MAXSIZE;
		cblkp.Txq.NoOfChar +=copylen;
		
		culen=culen-copylen;
		outb(inb(cblk.baseAddr+IER)|0x02,Cbkp.baseAddr+IER);
	}
	up(&cblkp.sem);
	return count;
}
module_init(myserial_init);
module_exit(myserial_cleanup);


      
 
