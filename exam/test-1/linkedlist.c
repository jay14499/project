#include<stdio.h>
#include<stdlib.h>
struct node{
	    int data;
	    struct node *next;
	   };
struct node *head;
int insert_node(int );
void printlist();
int main()
{
 int data,opt;
 
while(1)
{
 printf("enter the option\n");
 scanf("%d",&opt);
 switch(opt)
 {
 case 0:exit(1);

 case 1: printf("enter the data\n");
         scanf("%d",&data);
         insert_node(data);
	 break;
 case 2:printf("list\n");
        printlist();
	break;
 default:printf("choose valid option\n");
 }
}
}

int insert_node(int data)
{
struct node *temp;
	struct node *ptr=(struct node *)malloc(1*sizeof(struct node));
	if(ptr==NULL)
	{
		printf("insufficient memory\n");
		exit(1);
	}
	ptr->data=data;
	ptr->next=NULL;
	if(head==NULL)
	{
		head=ptr;
		return 0;
	}
	temp=head;
	while(temp->next!=NULL)
	{
		temp=temp->next;
		
	}
	temp->next=ptr;
}

void printlist()
{
 struct node *temp;
 
  if(head==NULL)
  {
   printf("list is empty\n");
   return;
  }
  temp=head;

 while(temp!=NULL)
  {
   printf("adress of temp:%p-data in temp:%d\n",temp,temp->data);
   temp=temp->next;
  }
}
