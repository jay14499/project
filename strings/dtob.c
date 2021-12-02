#include<stdio.h>
int dtob(int);
int main()
{
 int x,sum;
 printf("enter the value of x\n");
 scanf("%d",&x);
 sum=dtob(x);
 printf("%d\n",sum);
}

int dtob(int x)
 {
  int y,z;
  int sum=0,base=1;
  x=x/2;
  z=x%2;

  if(x==0)
  {
   return sum;
  }
   base=base*10;
  sum=sum+(base)*z;
  dtob(x);
  
  //printf("%d",sum);
 }
 
