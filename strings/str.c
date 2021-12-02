#include<stdio.h>
#include<string.h>
int main()
{
 int x=6;
 int a[10]={4,4,3,4,5,6,7,8,9,0};
 int *ptr=a;
 char arr[20];
 char buf[10]="data\\n";
 int l=strlen(buf);
 printf("l=%d\n",l);
 printf("%%d\\n,printf(\"hi\")");
char str[ ] = { 70 , 97 , 105 , 116 , 104 , 0 } ;
printf("%s\n",str);
printf("Giving ""is ""Iiving.""\n");
strcpy(arr, "Luck" "now");
printf("%s\n",arr);
printf("%d%d%d%d%d\n",++x,++x,++x,++x,++x);
printf("++*ptr=%d\n",++*ptr);
printf("*++ptr=%d\n",*++ptr);
printf("(*ptr)++=%d\n",(*ptr)++);
printf("*(ptr++)=%d\n",*(ptr++));
}
