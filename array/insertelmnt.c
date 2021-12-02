#include<stdio.h>
void display(int *);
int main()
{
 int a[6],i,j,pos,val;
 for(i=0;i<5;i++)
 {
	printf("enter the array elements a[%d]",i);
	scanf("%d",&a[i]);
 }
 printf("enter position to add element:");
 scanf("%d",&pos);

 printf("enter the element to be added at %d position:",pos);
 scanf("%d",&val);

     if(pos>=6)
	{
         	printf("cannot add the element in that position\n");
        	 return 0;
        }
     for(i=5;i>pos;i--)
     {	
      a[i]=a[i-1];
     }
     a[pos]=val;
        

 display(a);
}

void display(int *ptr)
{
 int temp;
 
  for(int i=0;i<6;i++)
 {
	printf("a[%d]=%d\n",i,ptr[i]);
 }
 printf("\n");
}
