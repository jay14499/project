#include<stdio.h>
int main()
{
 unsigned int x,y,i,j;
 printf("enter the value of x\n");
 scanf("%x",&x);
 
 for(i=0,j=1;j<9,i<8;i=i+2,j=j+2)
 {
 x=x&(~((1<<i)|(1<<j)))|((x&(1<<j))>>(j-i))|((x&(1<<j))<<(j-i));
 }
 printf("%x\n",x);
}
