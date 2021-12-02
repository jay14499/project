obj-m=hrtimer.o

dir= /lib/modules/$(shell uname -r)/build
pwd= M=$(shell pwd)

all:
	make -C $(dir) $(pwd) modules
load:
	sudo insmod hrtimer.ko
unload:
	sudo rmmod hrtimer.ko

clear:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
