#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
int main(int argc, char *argv[])
 {
 
  int ret,fd1,fd2;
  char buf[256];
  if(argc!=3)
  {
	printf("invalid format of cat command\n");
	exit(1);
  }

  fd1=open(argv[1],O_RDONLY);
  if(fd1<0)
  {
	printf("failed to open the file:fd1\n");
	exit(2);
  }

  fd2=open(argv[2],O_CREAT|O_TRUNC|O_RDWR);
  if(fd2<0)
  {
	printf("failed to open the file:fd2\n");
	exit(3);
  }
  ret=read(fd1,buf,256);
	if(ret<0)
        {
		printf("fail to read\n");
                exit(3);
 	}
  buf[ret]='\0';
  printf("ret=%d\n",ret);
  write(fd2,buf,ret);
  close(fd1);
  close(fd2);
 }
