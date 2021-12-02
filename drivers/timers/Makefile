obj-m=timer1.o

dir= /lib/modules/$(shell uname -r)/build
pwd= M=$(shell pwd)

all:
	make -C $(dir) $(pwd) modules
load:
	sudo insmod timer1.ko
unload:
	sudo rmmod timer1.ko

clear:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
