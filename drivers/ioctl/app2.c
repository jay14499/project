#include<stdio.h>
#include<stdlib.h>
#include<linux/ioctl.h>
#include<fcntl.h>
#include<unistd.h>
#include "myioctl.h"
int main()
{
	int fd,ret;
	int32_t value=0,number=0;
	fd=open("/dev/driv_char1",O_RDONLY);
	if(fd<0)
	{
		printf("failed to open\n");
		return 0;
	}
	ret=ioctl(fd,rd,(int32_t*)&number);
	
	if(ret<0)
	{
		printf("failed to read\n");
		return 0;
	}
	printf("number=%d\n",number);
	close(fd);
}
