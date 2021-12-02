#include<stdio.h>
#define MAX 10
char arr[MAX];
int front=-1,rear=-1;
void insertion(char);
void deletion();
void display();

int main()
{
int opt,c=0,pos=0,i;
char x;
while(1)
 {
printf("\nenter option\n 1.insertion\n 2.deletion\n 3.display\n");
scanf("%d",&opt);
	switch(opt)
	{
	case 1: printf("enter char\n");
      		scanf(" %c",&x);
       		insertion(x);
       		break;
	case 2:deletion();
      		 break;
	case 3:display();
      		 break;
	default:printf("invalid input\n");
	}
 }
}
void insertion(char x)
 {
	if(rear==MAX-1)
	{
		printf("queue overflow\n");
		return;
	}
	if(front==-1)
	{
		front=0;
	}
	rear=rear+1;
	arr[rear]=x;
 }
void deletion()
{
	if((front==-1)||(rear==-1))
	{
		printf("queue underflow\n");
		return;
	}
	front=front+1;
}


void display()
{
	if(front==-1||rear==-1)
	{
		printf("queue is empty\n");
		return;
	}
	for(int i=front;i<=rear;i++)
	{
		printf("%c ",arr[i]);
	}
}



