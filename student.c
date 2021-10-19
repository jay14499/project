#include<stdio.h>
#include<stdlib.h>
#include"student.h"


struct student *head;

void register_student(int idno,char *name,float marks,char gender)
{
  	struct student *ptr,*temp;
  	ptr=(struct student *)malloc(1*sizeof(struct student));
  	if(ptr==NULL)
  	{
	printf("insufficient memory");
        exit(1);
	}
	ptr->idno=idno;
         for(int i=0;name[i]!='\0';i++)
         {
  		ptr->name[i]=name[i];
         }
         ptr->marks=marks;
	ptr->gender=gender;
	ptr->link=NULL;
  	if(head==NULL)
  	{
  	head=ptr;
	return;
	}
	temp=head;
	while(temp!=NULL)
	{
	temp=temp->link;
        }
        temp->link=ptr;
}

void display_all()
 {
	  struct student *temp;
 
	  if(head==NULL)
	  {
	    printf("list is empty\n");
	    return;
	  }
	  temp=head;
	
	  while(temp!=NULL)
	  {
	    printf("idno=%d\n name=%s\n marks=%f\n gender=%c\n",temp->idno,temp->name,temp->marks,temp->gender);
	    temp=temp->link;
	  }
 }

void delete_particular(int idno)
{
  	struct student *temp,*prev;
  	if(head==NULL)
  	{
	printf("no information to delete\n");
	exit(2);
  	}
  	temp=head;
  	if(head->idno==idno)    
  	{
   	if(head->link==NULL)  
    	{
        	free(head);
       		head=NULL;
    	return;
    	}
  	temp=head;            
    	head=head->link;
    	free(temp);
    	return;
  	}
   	 temp=head->link;      
    	prev=head;
    	while(temp!=NULL)    
    	{
    	if(temp->idno==idno)  
    	{
	prev->link=temp->link;
        free(temp);
	return;
   	}
	prev=temp;
	temp=temp->link;
   }
  printf("element not found\n");
}

int count()
 {
  	struct student *temp;
  	int c=0;
  	if(head==NULL)
   	{
    	printf("list is empty\n");
    	return 0;
   	}
  	temp=head;
 
 	while(temp!=NULL)
  	{
   		c++;
   		temp=temp->link;
  	}
 	return c;
 } 


