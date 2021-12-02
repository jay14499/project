#include<stdio.h>
#define n 10
int main()
{
 int a[n],i,j,even=0,odd=0;
 for(i=0;i<n;i++)
 {
	printf("enter the array elements a[%d]",i);
	scanf("%d",&a[i]);
 }
 for(i=0;i<n;i++)
 {
  if(a[i]%2==0)
  {
   even++;
   printf("even=%d\n",a[i]);
  }
  else
  {
   odd++;
   printf("odd=%d\n",a[i]);
  }
 }
 printf("\nno of even elements in array=%d\n",even);
 printf("\nno of odd elements in array=%d\n",odd);
 
}


