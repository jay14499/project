#include<stdio.h>
int main()
{
 int n,m,a[20],b[20],i;
 printf("enter the no of elements in array 1:");
 scanf("%d",&n);
 for(i=0;i<n;i++)
 {
 	printf("enter the elements of array a[%d]=",i);
 	scanf("%d",&a[i]);
 }
 printf("\n");

 printf("enter the no of elements in array 2:");
 scanf("%d",&m);
 for(i=0;i<m;i++)
 {
 	printf("enter the elements of array b[%d]=",i);
 	scanf("%d",&a[i]);
 }
 
 int l1=sizeof(a)/sizeof(a[0]);
 int l2=sizeof(b)/sizeof(b[0]);
 if(l1==l2)
 {
  	printf("the array size is same\n");
 }
 else
 {
 	 printf("the array size is not same\n");
  	 return (l2-l1);
 }
}
