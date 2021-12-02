#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/ip.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#define qlimit 10
#define a s1
#define b s2
struct student{
               int idno;
               char name[20];
               float marks;
              }s;
int main()
{

		 printf("enter the student details\n");
		printf("enter the idno\n");
 		scanf("%d",s->idno);
 		printf("enter the name\n");
	 	scanf(" %s",s->name);
	 	printf("enter the marks\n");
		scanf("%f",s->marks);
	 	printf("enter the gender\n");
	 	scanf(" %c",s->gender);

 int fd,fd1,fd2,fd3;
 char buf[10],msg[10],s;
 ssize_t snd,rcv;
 socklen_t size;
 fd=socket(AF_INET,SOCK_STREAM,0);
 if(fd<0)
 {
	printf("failed to create socket\n");
	exit(1);
 }
 struct sockaddr_in server;
 struct sockaddr_in client;
  memset((struct sockaddr *)&server,'\0',sizeof(server));
 memset((struct sockaddr *)&client,'\0',sizeof(client));
 server.sin_family=AF_INET;
 server.sin_port=htons(8080);
 server.sin_addr.s_addr=inet_addr("127.0.0.1");

 fd1=bind(fd,(struct sockaddr *)&server,sizeof(server));
 if(fd1<0)
 {
	printf("failed to bind\n");
	exit(1);
 }
 
 fd2=listen(fd,qlimit);
 if(fd2<0)
 {	
	printf("failed to listen\n");
	exit(2);
 }
 size=sizeof(client);
 fd3=accept(fd,(struct sockaddr *)&client,&size);
 if(fd3<0)
 {	
	printf("failed to accept\n");
	exit(3);
 }

 snd=send(fd3,&s1,sizeof(struct student),0);

 if(snd<0)
 {
	printf("failed to receive\n");
	exit(5);
 }
 close(fd);
}


