#include<stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
	int i;
	if(argc!=3)
	{
	 printf("invalid command format\n");
	 exit(2);
	}
	for(i=0;argv[2][i]!='\0';i++)
	{
		if(argv[2][i]==argv[1][0])
		{
			argv[2][i]=' ';
		}
	
	}
	printf("%s",argv[2]);	
}
