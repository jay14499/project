#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<string.h>
#include<sys/stat.h>
int main()
{
 char buf[30]="hello-world";
 int fd,fd1,ret;
 mkfifo("fifo",0777);
 
 fd1=open("fif0",O_RDWR);
 if(fd1<0)
 {
	printf("failed to open\n");
	return 0;
 }
 ret=write(fd1,buf,strlen(buf));
 if(ret<0)
 {
	printf("failed to write");
	return 0;
 }
 write(1,buf,strlen(buf));
close(fd);
close(fd1);
}
