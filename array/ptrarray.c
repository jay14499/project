#include<stdio.h>
void display(int *);
int main()
{
 int a[5],i;
 for(i=0;i<5;i++)
 {
	printf("enter the array elements a[%d]",i);
	scanf("%d",&a[i]);
 }
 display(a);
}

void display(int *ptr)
{
 for(int i=0;i<5;i++)
 {
	printf("%d ",ptr[i]);
 }
 printf("\n");
}
