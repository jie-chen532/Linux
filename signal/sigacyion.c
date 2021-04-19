
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void sigcb(int signum)
{
  printf("信号值:%d\n", signum);
}

int main()
{
  struct sigaction act;
  sigemptyset(&act.sa_mask);
  act.sa_handler = sigcb;
  act.sa_flags = SA_NODEFER | SA_ONSTACK | SA_RESETHAND | SA_SIGINFO;
  sigaction(SIGINT, &act, NULL);
  getchar();
  return 0;
}
