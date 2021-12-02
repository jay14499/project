#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/poll.h>
#include<linux/ioport.h>
#include<linux/errno.h>
#include<linux/proc_fs.h>
#include<asm/io.h>
#include<linux/interrupt.h>
#include<linux/sched.h>
#include<linux/cdev.h>

MODULE_LICENSE("GPL");
static int myserial_open(struct inode *inode,struct file *file);
static int myserial_close(struct inode *inode,struct file *file);
static ssize_t myserial_write(struct file *file,const char *buf,size_t len,loff_t *offset);
static ssize_t myserial_read(struct file *file,char *buf,size_t len,loff_t *offset);


#define MYDEV_MAJOR_NUM   42					//defining the device number with macro
#define MYDEV_NAME        "myserial"				//defining device file name with myserial
#define SER_IOBASE        0x3f8					//defining the base address of the UART registers
#define SER_IRQ           4					//defining irq line no as 4 and this irq line information is present in /proc/interrupts
#define IRQF_DISABLED 	0x00000020				//defining irqf_disabled as default 0x00000020 

static struct file_operations myserial_ops=
{
    .read=myserial_read,
    .write=myserial_write,
    .open=myserial_open,
    .release=myserial_close
};

#define SUCCESS          0
#define MAXSIZE          4000				//defining the maximum size for kernel buffer
#define DATA             0				//set the THR and RBR to zero
#define DIV_LATCH_LOW    0				//to set the baud rate 
#define DIV_LATCH_HIGH   1				//to set the baud rate
#define IER              1				//interrupt enable register to generate interrupt when an event occured
#define IIR              2				//interrupt identification register 
#define DFR              3				//disable the FIFO register
#define LSR              5				//line status register (THRE) transmitter holding register empty. when set to 1 the FIFO now has space for atleast one word to transmit.
#define LCR              3				//line control register parity enabled when set to 1 a parity bit is inserted between the last bit of the data and stop bit

#define SER_DEV  "myserialdev"				//defining the device name as myserialdev
#define MDMC 		 4
struct dev_context		//device context info
{
char buf[1024];
int no_chars;
int base_address;//hw resources
int IRQ_lineno;//hw resources
struct cdev c_dev;
}my_context;


/****circular queue****/
typedef struct circularbuf
{
   int rdindex;
   int wrindex;
   int noofchar;
   char buf[MAXSIZE];
}cirq_t;

/****comtrol block structure ****/
typedef struct
{
   struct semaphore sem;
   wait_queue_head_t rxwq;
   wait_queue_head_t txwq;
   unsigned int baseaddr;
   int irq;					//uart irq line number is 4
   cirq_t Txq;
   cirq_t Rxq;
}cblock_t;

cblock_t cblkp;


/*********************************************************************************************
*name: int_receive
*description:
   this function receives characters from serial port and store in receive queue and give semaphore.
*parameters:
*input:control block pointer
*returns:nothing
***********************************************************************************************/

static void Int_Receiv(void)	/*RI*/
{
    while(inb(cblkp.baseaddr+LSR) & 0x1)				//inb=data from device to comp and we have to check the 0th bit of LSR register with 0x1 if it will true then this will perform the operation inside the lop
    {
       if(cblkp.Rxq.noofchar < MAXSIZE)					//if no of chars are less the maximum size then it will perform th
       {
          cblkp.Rxq.buf[cblkp.Rxq.wrindex]=inb(cblkp.baseaddr+DATA);	//the receiver buf index is equal to the no of character written into the receive buffer
          cblkp.Rxq.wrindex++;						//increment th write index 
          cblkp.Rxq.noofchar++;						//increment the no of chars 
          if(cblkp.Rxq.wrindex == MAXSIZE)
               cblkp.Rxq.wrindex=0;
       }
       else
       {
          inb(cblkp.baseaddr+DATA);
       }
    }
   wake_up_interruptible(&cblkp.rxwq);
}


/**********************************************************************************************
*name : int_transmit
*description:
*     this function is calle dwhen transmitt interrupt comes.
*     this function responsibility is taking characters transmit queue and transmitt to serialport
*parameters:
*  input: device control block pointer
*  returns :SER_DEV
* nothing
************************************************************************************************/

static void Int_Transmt(void)
{
  if(cblkp.Txq.noofchar == 0)
  {
    outb((inb(cblkp.baseaddr+IER) & 0xf),cblkp.baseaddr+IER);		//disable transmitt interrupt
    return;
  }
  else
  {
      while((inb(cblkp.baseaddr+LSR) & 0x20) && (cblkp.Txq.noofchar))	//verifying 5th bit and total no of chars
      {
        outb(cblkp.Txq.buf[cblkp.Txq.rdindex++],cblkp.baseaddr+DATA);	//tx buf -> thr
        cblkp.Txq.noofchar--;
        if(cblkp.Txq.rdindex == MAXSIZE)				//if rd index is equal to maximum size then change the read index to 0
           cblkp.Txq.rdindex=0;
      }
    wake_up_interruptible(&cblkp.txwq);					
  }
}

/*******************************************************************************************
* name : myinthandler
*description:
********************************************************************************************/

static irqreturn_t myIntHandler(int irq,void *dev_id)
{
   unsigned char intstat;
   intstat = inb(cblkp.baseaddr+IIR);
   while((intstat & 1) == 0)						//interrupt is pending or not it checks the all the interrupts serviced or not
   {
      if((intstat & 0x2) == 0x2)					//verifying 1st bit of IIR -TI
        Int_Transmt();							//when THR register is  empty then it will raise the transmit interrupt
      if((intstat & 0x4) == 0x4)					//verifying 2nd bit of IIR -RI
        Int_Receiv();							//when the RBR register is full then it will raise the receive interrupt
      intstat = inb(cblkp.baseaddr+IIR);
   }
 return IRQ_HANDLED;
}

static int serInit(int irq,unsigned int baseAddr)
{
   cblkp.Rxq.rdindex=0;							//initially the front and rear index at zero
   cblkp.Rxq.wrindex=0;
   cblkp.Rxq.noofchar=0;
   cblkp.Txq.rdindex=0;
   cblkp.Txq.wrindex=0;
   cblkp.Txq.noofchar=0;
   
   cblkp.baseaddr=baseAddr;
   cblkp.irq = irq;
   
   sema_init(&cblkp.sem,1);						//initializing the semaphore object
   init_waitqueue_head(&cblkp.rxwq);					//initializing the wait queue objects
   init_waitqueue_head(&cblkp.txwq);
   
   /**** set the baud rate ****/
   outb(0x83,cblkp.baseaddr+LCR);
   outb(0x01,cblkp.baseaddr+DIV_LATCH_LOW);
   outb(0x00,cblkp.baseaddr+DIV_LATCH_HIGH);
   outb(0x03,cblkp.baseaddr+LCR);
   outb(0x0,cblkp.baseaddr+IER);
   
   /**** ENABLE FIFOS ****/
   outb(0x70,cblkp.baseaddr+IIR);
   outb(0x0b,cblkp.baseaddr+MDMC);
   /**** INSTALL ISR FOR SERIAL PORT ****/
   if(request_irq(irq,myIntHandler,IRQF_DISABLED,SER_DEV,NULL))		//this function is used to register the interrupt handler function, if this call successful the entry gets updated in /proc/irqs and /proc/interrupts
   {
      printk("<1>cant get interrupt %d\n",irq);
      return -1;
   }
  return 0;
}

/****************************************************************************************
*name:init_module
*description:
*****************************************************************************************/
int myserial_init(void)
{
  int res,res1;
  res=register_chrdev_region(MYDEV_MAJOR_NUM,1,SER_DEV); 		//registering the driver with kernel and the entry gets upadted in /proc/devices
  if(res<0)
  {
      printk("<1>" "registration error %d\n",res);
      return res;
  }
  else
  {
     printk("<1>" "registration success %d\n",res);
  }
  cdev_init(&my_context.c_dev,&myserial_ops);				//initializing the cdev object linking cdev object and file operations 
  my_context.c_dev.owner=THIS_MODULE;					//THIS_MODULE is a predefined macro and it will return base address of the driver
 res1=cdev_add(&my_context.c_dev,MYDEV_MAJOR_NUM,1);			//after linking ,we have to add the structure to the kernel and to load the cdev object
 if(res1<0)
 {
     printk(KERN_INFO "c_dev object is not loaded\n");
 }
  printk(KERN_INFO "c_dev object is loaded\n");
  if(!request_region(SER_IOBASE,8,SER_DEV))				//check and inform the kernel to access the range of adress of I/O ports
  {
     printk(KERN_INFO "cant get I/O port address 0x3f8\n");
     return -1;
  }
 
  return serInit(SER_IRQ,SER_IOBASE);
}

/******************************************************************************************
*NAME: cleanup module
*description:
*******************************************************************************************/

void myserial_cleanup(void)
{
   unregister_chrdev_region(MYDEV_MAJOR_NUM,1);				// unregistering driver with kernel
   cdev_del(&my_context.c_dev);						//removing cdev object
   free_irq(SER_IRQ,NULL);						//removing irq line numbers
   release_region(SER_IOBASE,8);
   printk(KERN_ALERT "GOOD BYE\n");
   
}

/********************************************************************************************
*NAME:myserial_open
*description:
*********************************************************************************************/
static int myserial_open(struct inode *inode,struct file *file)
{
   try_module_get(THIS_MODULE);						//to increment the counter value using the base adress of current loaded module
   if(file->f_mode & FMODE_READ)					//check if the file is opened for read mode
     printk("<1>" "open for read\n");
   if(file->f_mode & FMODE_WRITE)
     printk("<1>" "open for write\n");					//check if the file is opened for write mode
   
   /**** enable interrupts on serial port 1****/
   outb(1,cblkp.baseaddr+IER);						// to enable the interrupts on serial port
   
   return 0;
}

/********************************************************************************************
*NAME:myserial_close
*description:
*********************************************************************************************/
static int myserial_close(struct inode *inode,struct file *file)
{
   module_put(THIS_MODULE);						//to decrement the counter value
   printk("<1>" "device closed\n");
   //disable receive interrupt
   outb((inb(cblkp.baseaddr+IER) & 0xfe),cblkp.baseaddr+IER);		//disable receive interrupt
   return 0;
}
/********************************************************************************************
*NAME:myserial_read
*description:
*********************************************************************************************/
static ssize_t myserial_read(struct file *file,char *buf,size_t len,loff_t *offset)
{
   int clen;
   int partlen;
   
   printk("<5>" "read called\n");
   wait_event_interruptible(cblkp.rxwq,cblkp.Rxq.noofchar > 0);		//blocks the read driver routine until the no of chars greater than zero		
   if(len < cblkp.Rxq.noofchar)
     clen=len;								 //if length is less than no of chars then change current length to length
   else
     clen=cblkp.Rxq.noofchar;  						 //changing current length to no of chars
     
   if((cblkp.Rxq.rdindex + clen) <= MAXSIZE) 				//readindex+current length less than equal to maximum size
   {
     copy_to_user(buf,cblkp.Rxq.buf+cblkp.Rxq.rdindex,clen);
   }
   else
   {
      partlen = MAXSIZE - cblkp.Rxq.rdindex;				//change the partion length to maximum size - read index
      copy_to_user(buf,cblkp.Rxq.buf+cblkp.Rxq.rdindex,partlen);
      copy_to_user(buf+partlen,cblkp.Rxq.buf,clen - partlen);
   }
   cblkp.Rxq.rdindex = (cblkp.Rxq.rdindex + clen) % MAXSIZE;		//chage the read index to read index + current length
   cblkp.Rxq.noofchar -= clen;						//change the no of chars to no of chars - current length
   return(clen);
}

/********************************************************************************************
*NAME:myserial_write
*description:
*********************************************************************************************/
static ssize_t myserial_write(struct file *file,const char *buf,size_t count,loff_t *offset)
{
   int avllen,copylen,partlen;
   int culen = count;							//changing current length to count
   printk("<1>" "write called\n'");
   
   while(culen)
   {
     wait_event_interruptible(cblkp.txwq,cblkp.Txq.noofchar < MAXSIZE);	// ch
     printk("after block\n");
     if(down_interruptible(&cblkp.sem))					//it is used to decrement the value of semaphore counter
        return -ERESTARTSYS;
     avllen=MAXSIZE - cblkp.Txq.noofchar;   				//available length equal to maximum length - no of. chars
     copylen = (culen < avllen) ? culen : avllen; 			//copy if current length, if current lenght less than available length
     if((cblkp.Txq.wrindex + copylen) <= MAXSIZE)			//checking the write and copylength is lessthan maximum size 
     {
        copy_from_user(cblkp.Txq.buf+cblkp.Txq.wrindex,buf,copylen);
     }
     else
     {
        partlen =MAXSIZE - cblkp.Txq.wrindex;				//change the partion length  to maximum size - write index
        copy_from_user(cblkp.Txq.buf+cblkp.Txq.wrindex,buf,partlen);
        copy_from_user(cblkp.Txq.buf,buf+partlen,copylen - partlen);
     }
     cblkp.Txq.wrindex = (cblkp.Txq.wrindex + copylen) % MAXSIZE;	//change the write index to write index + copy length
     cblkp.Txq.noofchar += copylen;					//change the total no of chars to total no of chars + copy length
     
     culen=culen - copylen;						//making current equal to current length - copied length
     outb(inb(cblkp.baseaddr+IER) | 0x02,cblkp.baseaddr+IER);		//enabled TI-IER => THR is empty? empty => TI
   }
  up(&cblkp.sem);							//incrementing the semaphore counter
  return count;
}
module_init(myserial_init); 						//module initialization
module_exit(myserial_cleanup);						//module exit
