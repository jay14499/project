#include<stdio.h>
void display(int *,int *);
int main()
{
 int a[5],b[5],i,j;
 for(i=0;i<5;i++)
 {
	printf("enter the array elements a[%d]",i);
	scanf("%d",&a[i]);
 }
 for(i=0;i<5;i++)
 {
	printf("enter the array elements b[%d]",i);
	scanf("%d",&b[i]);
 }
 display(a,b);
}

void display(int *ptr1,int *ptr2)
{
 int temp;
 for(int i=0,j=0;i<5;j++,i++)
 {
	temp=ptr1[i];
        ptr1[i]=ptr2[j];
        ptr2[j]=temp;
 }
 for(int i=0;i<5;i++)
 {
	printf("a[%d]=%d\n",i,ptr1[i]);
 }
 printf("\n");
  for(int i=0;i<5;i++)
 {
	printf("b[%d]=%d\n",i,ptr2[i]);
 }
 printf("\n");
}
