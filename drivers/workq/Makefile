obj-m=workq.o
dir= /lib/modules/$(shell uname -r)/build
pwd= M=$(shell pwd)
all:
	make -C $(dir) $(pwd) modules
load:
	sudo insmod workq.ko
unload:
	sudo rmmod workq.ko
clear:
	rm -rf *.o *.ko *.mod.o *mod.c *.mod *.temp *.order *.symvers

