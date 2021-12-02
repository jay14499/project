#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
int main(int argc, char *argv[])
{
 int fd1,fd2,i,j,count=0;
 char *ptr;
 struct stat buf;
 fd1=open(argv[1],O_RDONLY);
 if(fd1<0) 
 {
	printf("failed to open\n");
	exit(1);
 }
 fstat(fd1,&buf);
 ptr=(char *)malloc(buf.st_size*sizeof(char));
 if(ptr==NULL)
 {
	printf("insufficient memory\n");
	exit(2);
 } 
 fd2=read(fd1,ptr,buf.st_size);
 if(fd2<0)
 {
	printf("failed to read\n");
	exit(4);
 }

 for(i=0;i<buf.st_size;i++)
 {	
        count=0;
 	for(j=i+1;j<buf.st_size;j++)
	{
	 if(ptr[i]==ptr[j])
	 {
		count++;
                ptr[j]=' ';
	 }
	}
	if(ptr[i]!=' ')
	{
	printf("%c-%d\n",ptr[i],count);
	}
 }
free(ptr);
}
