obj-m=chardriv1.o
dir= /lib/modules/$(shell uname -r)/build
pwd= M=$(shell pwd)
all:
	make -C $(dir) $(pwd) modules
load:
	sudo insmod chardriv1.ko
unload:
	sudo rmmod chardriv1.ko
clear:
	rm -rf *.o *.ko *.mod.o *mod.c *.mod *.temp *.order *.symvers

