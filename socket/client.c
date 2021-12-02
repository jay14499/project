#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/ip.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
struct student{
               int idno;
               char name[20];
               float marks;
               struct student *link;
              }s1,s2;
int main()
{
 int fd,fd1,fd2,fd3;
 ssize_t snd,rcv;
 char s;
 //char msg[10]="hello",buf[10];
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
// memset((struct sockaddr *)&server,'\0',sizeof(server));
 fd1=connect(fd,(struct sockaddr *)&server,size);

 if(fd1<0)
 {
	printf("failed to connect\n");
	exit(2);
 }

 rcv=recv(fd,&s1,sizeof(struct student),0);
 if(rcv<0)
 {
	printf("failed to send data\n");
	exit(4);
 }

 printf("rcv=%ld\n",rcv);
 printf("student id=%d\n",s1.idno);
 printf("student name=%s\n",s1.name);
 printf("student marks=%f\n",s1.marks);
}
