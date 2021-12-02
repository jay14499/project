#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
	int fd1,ret;
	char rbuf[10],buf[20]="<---moschip--->";
	fd1=open("/dev/mychar1",O_RDWR);
	if(fd1<0)
	{
		printf("failed to open\n");
		return 0;
        }
	//sleep(10);
	/* ret=read(fd1,buf,strlen(rbuf));
	if(ret<0)
	{	
	 	printf("failed to read\n");
		return 0;
	}
	write(1,rbuf,strlen(rbuf));*/
        ret=write(fd1,buf,strlen(buf));
	if(ret<0)
	{	
	 printf("failed to write\n");
	 return 0;
	}
	write(1,buf,ret);
	close(fd1);
} 
