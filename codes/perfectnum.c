#include<stdio.h>
#include<stdlib.h>
int main()
{
 int x,i,y=1,j,sum=0,k;
 printf("enter the value of x\n");
 scanf("%d",&x);
 for(i=18;i>0;i++)
 {
  sum=0;
  j=i;
  while(j>0)
  {
   	k=j%10;
 	sum=sum+k;
	j=j/10;
  }
  //printf("sum=%d\n",sum);
 // printf("i=%d\n",i);
  if(sum==10)
  {
 	if(x==y)	
	{
	printf("perfect num=%d\n",i);
	exit(1);
	}
	y++;
  }
  sum=0;
 }
}
