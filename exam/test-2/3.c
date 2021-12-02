
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char str[20],left_sta[10],right_sta[10],x;
	int i,li=0,ri=0,j,len,flag=0;
	printf("enter a mathematical expression\n");
	scanf("%s",str);
	len=strlen(str);
	for(i=0;i<len;i++)
	{
		if((str[i]=='{') || (str[i]=='[') || (str[i]=='('))
		{
			left_sta[li]=str[i];
			li++;
		}
		
		else if((str[i]=='}') || (str[i]==']') || (str[i]==')'))
		{
			right_sta[ri]=str[i];
			ri++;
			if(right_sta[ri]-left_sta[li]<3)
			{
				left_sta[li]=0;
				right_sta[ri]=0;
				li--;
				ri--;
			}
		}
		else
                {
		 continue;
		}
	}
	for(i=0;i<li;i++)
	{
		printf("%c\n",left_sta[i]);
	}
	for(j=ri-1;j>=0;j--)
	{
		printf("%c\n",right_sta[j]);
	}
	if(li!=ri)
	{
		printf("irregular expression\n");
		exit(1);
	}
	for(i=0,j=ri-1;i<li;i++,j--)
	{
		x=left_sta[i];
		switch(x)
		{
			case '{':	if(right_sta[j]!='}')
					{
                               			flag=1;
					}	
					break;

			case '[':	if(right_sta[j]!=']')
					{
						flag=1;
					}	
					break;
			case '(':	if(right_sta[j]!=')')
					{
				                flag=1;			
					}	
					break;
			default:	printf("irregular expression\n");
		}
	}
        if(flag==1)
        {
	printf("irregular expression\n");
	}
        else
	printf("regular expression\n");

	
		
}


