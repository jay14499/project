#include<stdio.h>
int strcmp(const unsigned char *,const unsigned char *);
int main()
{
 int ret;
 const unsigned char *s1[10],*s2[10];
 printf("enter the string1 and string 2\n");
 scanf("%s",s1);
 scanf("%s",s2);
 ret=strcmp(s1,s2);
 printf("ret=%d\n",ret);
}

int strcmp(const unsigned char *s1,const unsigned char *s2)
{
 const unsigned char *src1=s1,*src2=s2;
 int flag;
 while(*src1||*src2)
 {
	flag=*src1-*src2;
	if(flag)
         return flag;
	src1++;
	src2++;
 }
 return 0;
}
 
