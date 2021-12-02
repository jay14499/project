#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char str[20],left[10],right[10],x;
	int i,li=0,ri=0,j,len,flag=0;
	printf("enter a mathematical expression\n");
	scanf("%s",str);
	len=strlen(str);
	for(i=0;i<len;i++)
	{
		if((str[i]=='{') || (str[i]=='[') || (str[i]=='('))
		{
			left[li]=str[i];
			li++;
		}
		
		else if((str[i]=='}') || (str[i]==']') || (str[i]==')'))
		{
			right[ri]=str[i];
			ri++;
		}
        }
for(i=0;i<li;i++)
	{
		printf("%c\n",left[i]);
	}
	for(j=ri-1;j>=0;j--)
	{
		printf("%c\n",right[j]);
	}
for(i=0,j=ri-1;i<li;i++,j--)
{
        int z=left[li]-right[ri];
	//if(z<3)
 	{
		printf("%d\n",z);
		//flag=1;
        }
}
/*if(flag==1)
{
 printf("irregular\n");
}
else
printf("regular\n");*/
}
