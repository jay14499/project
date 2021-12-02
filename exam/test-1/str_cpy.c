#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char str_cpy(const char *,char *);
int main()
{
 const char str1[20];
 char str2[20];
 printf("enter the string in str1\n");
 scanf("%s",str1);
 str_cpy(str1,str2);
 //printf("ret=%d\n",ret);
 printf("str2=%s\n",str2);
}

char str_cpy(const char *src,char *dst)
{
 int i;
 for(i=0;src[i]!='\0';i++)
 {
	dst[i]=src[i];
 }
 dst[i]='\0';
 }
