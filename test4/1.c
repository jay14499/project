#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
int i=1;
void *mythread_func1(void *n);
void *mythread_func2(void *n);
int main(int argc, char *argv[])
{
	
	pthread_t t1,t2;
	void *res;
	int n;
	n=atoi(argv[1]);
	if(argc!=2)
	{
	 printf("invalid format\n");
	 exit(1);
	}
	
		pthread_create(&t1,0,mythread_func1,&n);
		pthread_create(&t2,0,mythread_func2,&n);
		pthread_join(t1,&res);
		pthread_join(t2,&res);
	
}

void *mythread_func1(void *j)
{
	int i,n;
	n=*(int *)j;
	for(i=1;i<=n;i++)
	{
		if(i%2!=0)
		{
			printf("thread=%d\n",i);
			sleep(1);
		}
	}

}
void *mythread_func2(void *j)
{
	int i,n;
	n=*(int *)j;
	for(i=1;i<=n;i++)
	{
		if(i%2==0)
		{
			printf("parent=%d\n",i);
			sleep(1);
		}
	}

}



