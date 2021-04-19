#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void sicb(int signum)
{
  printf("这是一个自定义信号+%d\n", signum);
}

int main()
{
  signal(SIGINT,sicb);
  signal(40, sicb);

  sigset_t set;
  sigemptyset(&set);
  sigfillset(&set);
  //阻塞信号
  sigprocmask(SIG_BLOCK, &set, NULL);

  printf("按回车解除阻塞\n");//停下来，向进程发送信号
  getchar();

  //解除阻塞
  sigprocmask(SIG_UNBLOCK, &set, NULL);
  while(1)
  {
    sleep(1);
  }
}
