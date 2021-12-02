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
	fd=open("/dev/driv_char1",O_WRONLY);
	if(fd<0)
	{
		printf("failed to open\n");
		return 0;
	}
	printf("enter the value to send\n");
	scanf("%d",&number);
	ioctl(fd,wr,(int32_t*)&number);
	close(fd);

}
