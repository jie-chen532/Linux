#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
int main()
{
  int status = 0;
  pid_t pid = fork();
  if(pid < 0)
  {
    perror("fork error");
  }
  else if(pid == 0)
  {
    printf("i am child process\n");
    sleep(5);
    exit(99);
  }
  wait(&status);
  printf("退出信号:%d\n", status & 0x7f);
  printf("coredump:%d\n", (status >> 7) & 0x01);
  printf("退出值:%d\n", (status >> 8) & 0xff);
  return 0;
}
