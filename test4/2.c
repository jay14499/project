#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
int main(int argc , char *argv[])
{
	pid_t pid;
	if(argc!=2)
	{
		printf("invalid format\n");
	}
	pid=fork();
	//if(pid==0)
	{
		execlp("ls","ls","-l",argv[1],NULL);
		
		exit(1);
	}
	
}
