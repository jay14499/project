#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/ip.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include"student.h"
int main()
{
 struct student s,*ptr;
 int fd,fd1,fd2,fd3,opt,x=1,i;
 ssize_t snd,rcv;
 int idno;
 float marks;
 char name[10],gender;


 socklen_t size;
 fd=socket(AF_INET,SOCK_STREAM,0);
 if(fd<0)
 {
	printf("failed to create socket\n");
	exit(1);
 }
 struct sockaddr_in server;
 server.sin_family=AF_INET;
 server.sin_port=htons(8080);
 server.sin_addr.s_addr=inet_addr("127.0.0.1");
 size=sizeof(server);

 fd1=connect(fd,(struct sockaddr *)&server,size);

 if(fd1<0)
 {
	printf("failed to connect\n");
	exit(2);
 }
while(1)
{
 printf("enter the option\n 0.exit \n 1.register\n 2.display all\n");
 scanf("%d",&opt);
 switch(opt)
 {
	case 0: exit(1);
	
	case 1: printf("enter the student details\n");
		printf("enter the idno\n");
 		scanf("%d",&s.idno);
 		printf("enter the name\n");
	 	scanf(" %s",s.name);
	 	printf("enter the marks\n");
		scanf("%f",&s.marks);
	 	printf("enter the gender\n");
	 	scanf(" %c",&s.gender);
               /* ptr->idno=idno;
                for(i=0;name[i]!=0;i++)
                {
 		ptr->name[i]=name[i];
		}
		ptr->marks=marks;
		ptr->gender=gender;*/
                snd=send(fd,(const char *)&s,sizeof(struct student),0);	
      
               if(snd<0)
 		{
		printf("failed to send\n");
		exit(5);
 		}

               
		break;
	
	case 2: 
                snd=send(fd,&s,sizeof(struct student),0);	
      
               if(snd<0)
 		{
		printf("failed to send\n");
		exit(5);
 		}
		break;
	
	case 3: printf("enter the idno you want to search\n");
                scanf("%d",&idno); 
		snd=send(fd,(const char *)&s,sizeof(struct student),0);	
      
               if(snd<0)
 		{
		printf("failed to send\n");
		exit(5);
 		}
		break;

	case 4: printf("enter the idno you want to delete\n");
		scanf("%d",&idno);
		snd=send(fd,(const char *)&s,sizeof(struct student),0);	
      
               if(snd<0)
 		{
		printf("failed to send\n");
		exit(5);
 		}
                break;

	case 5: 
		break;

       default:printf("choose the valid option\n");
               break;

 }
}
}



