#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>

void sigcb(int signum)
{
  printf("信号值:%d\n", signum);
}

int main()
{
  signal(SIGINT, sigcb);
  printf("输入空格，进程结束\n");
  getchar();
  return 0;
}
