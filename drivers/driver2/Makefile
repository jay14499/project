obj-m:= jay.o
jay-objs:=1.o 2.o
dir= /lib/modules/$(shell uname -r)/build
pwd= M=$(shell pwd)
all:
	make -C $(dir) $(pwd) modules
load:
	sudo insmod jay.ko
unload:
	sudo rmmod jay.ko
clear:
	rm -rf *.o *.ko *.mod.o *mod.c *.mod *.temp *.order *.symvers
