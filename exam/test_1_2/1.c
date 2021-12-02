#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
int main(int argc, char *argv[])
{
 int fd1,fd2,i,c,x;
 char *ptr;
 struct stat buf;
 fd1=open(argv[1],O_RDONLY);
 if(fd1<0) 
 {
	printf("failed to open\n");
	exit(1);
 }
 fstat(fd1,&buf);
 ptr=(char *)calloc(buf.st_size,sizeof(char));
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
 buf.st_size=buf.st_size+(16-(buf.st_size%16));
 
 for(i=0;i<buf.st_size;i=i+16)
 {
	printf(" %08x:",i);
	for(x=i;x<i+16;x++)
        {       
                if(ptr[x]>='a' && ptr[x]<='z')
		printf(" %x",ptr[x]);
		else
                printf(" 00");
		if(x==(i+8))
		{
		printf(" - ");
		}
               
  	}
	printf(" |");
	for(c=i;c<i+16;c++)
	{	
		  if(ptr[c]>=7 && ptr[c]<=13)
                   {
		    printf(" ");
                    continue;
                   }
		printf("%c",ptr[c]);
	}
	printf(" |");
	printf("\n");
 }
 free(ptr);
 close(fd1);
}
 
