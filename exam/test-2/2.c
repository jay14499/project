#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
int main(int argc,char *argv[])
{
 char *ptr;
 int fd,ret,i,j,count=1;
 struct stat buf;
 if(argc!=2)
 {
	printf("invalid format\n");
	exit(1);
 }
 fd=open(argv[1],O_RDONLY);
 if(fd<0)
 {
	printf("failed to open\n");
	exit(2);
 }
 fstat(fd,&buf);
  ptr=(char*)malloc(buf.st_size*(sizeof(char)));
 if(ptr==NULL)
 {
	printf("insufficient memory\n");
	exit(3);
 }
 ret=read(fd,ptr,buf.st_size);
 if(ret<0)
 {
	printf("fail to read\n");
	exit(4);
 }
 for(i=0;i<buf.st_size;i++)
 {
  for(j=i+1;j<buf.st_size;j++)
  {
   if(ptr[i]==ptr[j])
    {
     count++;
    }
  }
   if(count>1)
   {
    printf("%c ",ptr[i]);
    printf("count=%d\n",count);
    count=1;
   }
   ptr[i]=' ';
 }
}
