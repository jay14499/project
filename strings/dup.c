#include<stdio.h>
#include<string.h>
int main()
{
 int i,l,j,count=0;
 char buf[20];
 printf("enter the string\n");
 scanf("%s",buf);
 l=strlen(buf)-1;
 
 for(i=0;i<l;i++)
 {
  for(j=i+1;j<l;j++)
  {
  if(buf[i]==buf[j])
   {
    count++;
   }
   }
 }
printf("%d\n",count);
}
