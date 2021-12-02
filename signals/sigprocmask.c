#include<stdio.h>
#include<unistd.h>
#include<signal.h>
 void sig_handler(int sig)
 {
	printf("----signal handler function is executing----\n");
	
 }

int main()
{
 int i,ret;
 struct sigaction act;
 sigset_t new_set, old_set,sig;
 
 sigemptyset(&act.sa_mask);
 act.sa_flags=0;
 act.sa_handler=sig_handler;
 sigaction(SIGINT,&act,NULL);

 sigemptyset(&act.sa_mask);
 sigaddset(&act.sa_mask,SIGINT);
 sigprocmask(SIG_BLOCK,&act.sa_mask,NULL);
 //sigprocmask(SIG_BLOCK,&new_set,NULL);
 printf("-----sigint signal is blocked-----\n");
  for(i=0;i<15;i++)
 {
  printf("main is executing\n");
  sleep(1);
 }
 sleep(1);
 sigprocmask(SIG_UNBLOCK,&act.sa_mask,NULL);
 printf("-----sigint signal is unblocked-----\n");
 while(1)
 {
  printf("main execution after unblock\n");
  sleep(1);
 }
 
}
