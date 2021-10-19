#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main()
{
 int i,j,k;
 char a[20];
 char *ptr[6];
 for(i=0;i<6;i++)
 {
 	ptr[i]=(char*)malloc(20*sizeof(char));
 }
 printf("enter the string\n");
 scanf("%s",a);
 for(i=0;a[i]!='\0';i++)
 {
  	for(j=0;a[i]!=' ';j++)
  	{
         for(k=0;a[i]!=' ';k++)
          {
   	   ptr[j][k]=a[i];
  	  }
        }
  	ptr[j]='\0';
 }
 for(j=0;j<6;j++)
 {
 	printf("%s\n",ptr[j]);
 }
}
