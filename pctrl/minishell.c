#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int main()
{
  while(1)
  {
    printf("[user@hoat path]$ ");
    fflush(stdout);
    //从键盘获取字符串
    char cmd[1024] = {0};
    fgets(cmd, 1023, stdin);
    cmd[strlen(cmd) - 1] = '\0';

    //整理字符
    char* ptr = cmd;
    char *my_argv[32] = {NULL};
    int my_argc = 0;
    while(*ptr != '\0')
    {
      if(!isspace(*ptr))
      {
        my_argv[my_argc++] = ptr;
        while(*ptr != '\0' && !isspace(*ptr))
          ptr++;
        *ptr = '\0';
      }
      ++ptr;
    }
   my_argv[my_argc] = NULL;

  //如果是cd
  if(strcmp(my_argv[0], "cd") == 0)
  {
    chdir(my_argv[1]);
    continue;
  }

  //子程序进行替换
  pid_t pid = fork();
  if(pid < 0)
  {
    continue;
  }
  else if(pid == 0)
  {
    execvp(my_argv[0], my_argv);
    //程序替换失败子进程退出
    exit(-1);
  }
  //程序等待
  wait(NULL);
  }
  return 0;
} 
