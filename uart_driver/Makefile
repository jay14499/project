obj-m=uartdriv.o
dir= /lib/modules/$(shell uname -r)/build
pwd= M=$(shell pwd)
all:
	make -C $(dir) $(pwd) modules
load:
	sudo insmod uartdriv.ko
unload:
	sudo rmmod uartdriv.ko
clear:
	rm -rf *.o *.ko *.mod.o *mod.c *.mod *.temp *.order *.symvers

