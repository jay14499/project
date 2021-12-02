#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/ip.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include"student.h"
#define qlimit 10
#define a s1
#define b s2

int main()
{
 struct student *s;
 int fd,fd1,fd2,fd3;
 char buf[10],msg[10];
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

  rcv=recv(fd3,&s,sizeof(struct student),0);
 if(rcv<0)
 {
	printf("failed to receive data\n");
	exit(4);
 }

 printf("rcv=%ld\n",rcv);
 printf("student id=%d",s->idno);
 printf("student name=%s\n",s->name);
 printf("student marks=%f\n",s->marks);
 printf("student gender=%c\n",s->gender);
 

 close(fd);
}


