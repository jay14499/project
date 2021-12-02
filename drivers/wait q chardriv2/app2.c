#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
	int fd,ret;
	char buf[5];
	fd=open("/dev/mychar2",O_RDWR);
	if(fd<0)
	{
		printf("failed to open\n");
		return 0;
        }
 	//sleep(10);
        ret=read(fd,buf,strlen(buf));
	if(ret<0)
	{	
	 	printf("failed to read\n");
		return 0;
	}
 	int ret1=write(1,buf,ret);
	
	if(ret1<0)
	{	
	 printf("failed to write\n");
	return 0;
	}
}
