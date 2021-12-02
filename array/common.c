#include<stdio.h>
#define n 6
#define m 6
int main()
{
 int a[n],b[m],i,j,count=0;
 for(i=0;i<n;i++)
 {
 printf("enter the elemets of array a[%d]",i);
 scanf("%d",&a[i]);
 }
 for(i=0;i<n;i++)
 {
 printf("enter the elemets of array b[%d]",i);
 scanf("%d",&b[i]);
 }

 for(i=0;i<n;i++)
 {
	for(j=0;j<m;j++)
	{
		if(a[i]==b[j])
       		{
		 printf("%d",a[i]);
                 count++;
   		}
	}
}
 printf("%d occurs %d times\n",a[i],count);
}
