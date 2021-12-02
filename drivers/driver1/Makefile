obj-m=mydriver.o

all : 
	make ARCH=arm CROSS_COMPILE=/home/engineer/kernel/raspberrypi/buildroot-2021.02.6/output/host/bin/arm-linux- -C /home/engineer/kernel/raspberrypi/buildroot-2021.02.6/output/build/linux-custom M=$(shell pwd) modules

	#make -C /lib/modules/5.4.152 M=$(shell pwd) modules
clear: 
	rm -rf *.o *.ko 

