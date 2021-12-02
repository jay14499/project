#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
	int fd1,ret;
	char buf[20]="<---moschip--->";
	fd1=open("/dev/mychar2",O_WRONLY);
	if(fd1<0)
	{
		printf("failed to open\n");
		return 0;
        }
	//sleep(10);
        ret=write(fd1,buf,strlen(buf));
	if(ret<0)
	{	
	 printf("failed to write\n");
	 return 0;
	}
	close(fd1);
} 
