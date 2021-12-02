#include<stdio.h>
int count_bit(unsigned int );
int toggle_bit(unsigned int ,int );
int main()
{
 unsigned int x,y;
 int pos,count1=0;
 printf("enter the number");
 scanf("%x",&x);
 count1=count_bit(x);
 printf("no of 1's in %x=%d\n",x,count1);
 printf("\nenter the position\n");
 scanf("%d",&pos);
 y=toggle_bit(x,pos);
 printf("%x",y);
 exit(10);
}

int count_bit(unsigned int x)
{
 unsigned int y;
 int count=0;
 while(x!=0)
 {
	if((x&1)==1)
	{
	 count++;
	}
 x=x>>1;
 }
 return count;
}
int toggle_bit(unsigned int x,int pos)
{
 x=x^(1<<pos);
 return x;
}
