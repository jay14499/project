#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
int main(int argc,char *argv[])
{
 int fd1,fd2,fd3,fd4,ret1,ret2,ret3,ret4;
 char *ptr1,*ptr2;
 struct stat buf1,buf2;
 if(argc!=3)
 {
	printf("invalid format\n");
	exit(10);
 }
 fd1=open(argv[1],O_RDONLY);
 if(fd1<0)
 {
	printf("failed to open :fd\n");
	exit(1);
 }
 fstat(fd1,&buf1);
 ptr1=(char *)malloc(buf1.st_size*sizeof(char));
 if(ptr1==NULL)
 {
	printf("insufficient memory\n");
	exit(3);
 }
 ret1=read(fd1,ptr1,buf1.st_size);
 if(ret1<0)
 {
	printf("failed to read:ret1\n");
	exit(2);
 }
 fd2=open(argv[2],O_RDONLY);
 if(fd2<0)
 {
	printf("failed to open :fd\n");
	exit(4);
 }
 fstat(fd2,&buf2);
 ptr2=(char *)malloc(buf2.st_size*sizeof(char));
 if(ptr2==NULL)
 {
	printf("insufficient memory\n");
	exit(5);
 }
 ret1=read(fd2,ptr2,buf2.st_size);
 if(ret1<0)
 {
	printf("failed to read:ret1\n");
	exit(6);
 }
 ftruncate(fd1,0);
 ftruncate(fd2,0);
 fd3=open(argv[1],O_RDWR|O_TRUNC,0660);
 if(fd3<0)
 {
	printf("failed to open:fd3\n");
	exit(9);
 }
 ret3=write(fd3,ptr2,buf2.st_size);
 if(ret3<0)
 {
	printf("failed to write:ret3\n");
	exit(7);
 }
 fd4=open(argv[2],O_RDWR|O_TRUNC,0660);
 if(fd4<0)
 {
	printf("failed to open:fd4\n");
	exit(10);
 }
 ret4=write(fd4,ptr1,buf1.st_size);
 if(ret4<0)
 {
	printf("failed to write:ret4\n");
	exit(8);
 }
 close(fd1);
 close(fd2);
 close(fd3);
 close(fd4);
}
