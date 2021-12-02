#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
int main(int argc,char *argv[])
{
 int fd,fd1,ret1,ret2,ret3,ret4,fd2;
 char *ptr1,*ptr2;
 struct stat buf1,buf2;
 if(argc!=4)
 {
	printf("invalid format\n");
	exit(10);
 }
 fd=open(argv[1],O_RDONLY);
 if(fd<0)
 {
	printf("failed to open :fd\n");
	exit(1);
 }
 fstat(fd,&buf1);
 ptr1=(char *)malloc(buf1.st_size*sizeof(char));
 if(ptr1==NULL)
 {
	printf("insufficient memory\n");
	exit(3);
 }
 ret1=read(fd,ptr1,buf1.st_size);
 if(ret1<0)
 {
	printf("failed to read:ret1\n");
	exit(2);
 }
 fd1=open(argv[2],O_RDONLY);
 if(fd<0)
 {
	printf("failed to open :fd\n");
	exit(4);
 }
 fstat(fd1,&buf2);
 ptr2=(char *)malloc(buf1.st_size*sizeof(char));
 if(ptr2==NULL)
 {
	printf("insufficient memory\n");
	exit(5);
 }
 ret1=read(fd1,ptr2,buf1.st_size);
 if(ret1<0)
 {
	printf("failed to read:ret1\n");
	exit(6);
 }
 
 fd2=open(argv[3],O_CREAT|O_TRUNC|O_RDWR|O_APPEND,0660);
 if(fd<0)
 {
	printf("failed to open:fd2\n");
	exit(7);
 }
 ret3=write(fd2,ptr1,(buf1.st_size-1));
 if(ret3<0)
 {
	printf("failed to write:ret3\n");
	exit(8);
 }
 ret4=write(fd2,ptr2,buf2.st_size);
 if(ret4<0)
 {
	printf("failed to write:ret4\n");
	exit(9);
 }
 
}
