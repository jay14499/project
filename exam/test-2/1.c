#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
int main(int argc,char *argv[])
{
 char *ptr;
 int fd,ret,x,c,i;
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
 buf.st_size=buf.st_size+(16-((buf.st_size)%16));
 ptr=(char*)calloc(buf.st_size,(sizeof(char)));
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
 for(i=0;i<buf.st_size;i=i+16)
 {
	printf(" %08x :",i);
	for(x=i;x<i+16;x++)
	{
    		if(ptr[x]>='a' && ptr[x]<='z')
		{
		printf(" %x",ptr[x]);
		}
	else
		printf(" 00");
	if(x==i+7)
	{
		printf(" - ");
	}
	}
        printf(" | ");
	for(c=i;c<i+16;c++)
	{
		if(ptr[c]>=7 && ptr[c]<=13)
		{
		 printf(" ");
		 continue;
		}
		printf("%c",ptr[c]);
	}
	printf(" | ");
	printf("\n");
  }
 free(ptr);
 close(fd);
}     
