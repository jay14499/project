#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/ip.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include"student.h"
#include<fcntl.h>
#include<sys/types.h>
#define qlimit 10

int main()
{
 struct student s,*ptr;
 int fd,fd1,fd2,fd3,x,idno;
 FILE *fd4,*fd5;
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
while(1)
{
  rcv=recv(fd3,(void *)&s,sizeof(struct student),0);
 if(rcv<0)
 {
	printf("failed to receive data\n");
	exit(4);
 }
 
 fd4=fopen("file.c","a+");
 if(fd4<0)
 {
  printf("failed to open: fd4\n");
  exit(5); 
 }
 else
 {
 //fwrite("student.txt","w");
  fclose(fd4);
 }

 recv(fd3,(void *)&s,sizeof(struct student),0);
 fd5=fopen("file.c","r");
 if(fd5<0)
 {
  printf("failed to open: fd5\n");
  exit(5); 
 }
 else
 {
  printf("idno=%d\n name=%s\n marks=%f\n gender=%c\n",s.idno,s.name,s.marks,s.gender);
 }
}
  fclose(fd5);
 fseek(fd4, 0, SEEK_SET);
rcv=recv(fd3,&s,sizeof(struct student),0);
 if(rcv<0)
 {
	printf("failed to receive data\n");
	exit(4);
 }
 if(idno)
 {
   printf("idno=%d\n name=%s\n marks=%f\n gender=%c\n",s.idno,s.name,s.marks,s.gender);
 } 

 
 close(fd);
}

