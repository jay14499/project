#include<stdio.h>
int *ptr;
void fun()
{
 static int a=20;
 ptr=&a;
}

int main()
{
 fun();
 printf("%d\n",*ptr);
}
