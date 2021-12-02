#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
  int i,j,flag=0,l;
  char str[30];
  //char (*ptr)[ ][ ];
 /* for(i=0;i<5;i++)
  {
   ptr[i]=(char*)malloc(10*sizeof(char));
  }*/
  printf("enter the string\n");
  scanf("%s",str);
  l=strlen(str)-1;
  for(i=0;str[i]!='\0';i++)
  {
   for(j=l;j>l/2;j--)
   {
     if(str[i]==str[j])
     {
      flag=1;
     }
 }
}
 if(flag>0)
 {
  printf("given string is palindrome\n");
 }
 else
 printf("not a palindrome\n");

}
