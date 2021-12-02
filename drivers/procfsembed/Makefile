obj-m=chardriv3.o
dir= /lib/modules/$(shell uname -r)/build
pwd= M=$(shell pwd)
all:
	make -C $(dir) $(pwd) modules
load:
	sudo insmod chardriv3.ko
unload:
	sudo rmmod chardriv3.ko
clear:
	rm -rf *.o *.ko *.mod.o *mod.c *.mod *.temp *.order *.symvers

