obj-m=kthrd.o

dir= /lib/modules/$(shell uname -r)/build
pwd= M=$(shell pwd)

all:
	make -C $(dir) $(pwd) modules
load:
	sudo insmod kthrd.ko
unload:
	sudo rmmod kthrd.ko

clear:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
