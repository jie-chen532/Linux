#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>


int main()
{
  pid_t pid = fork();
  if(pid < 0)
  {
    perror("fork error");
  }
  else if(pid == 0)
  {
    execl("/usr/bin/ls", "ls", "-a", "-l", NULL);
    printf("程序替换失败\n");
    exit(-1);
  }
  wait(NULL);
  return 0;
}
