#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<ctype.h>


int main()
{
  while(1)
  {
    printf("[user@host path]$ ");
    fflush(stdout);
    char cmd[1024] = {0};
    fgets(cmd, 1023, stdin);
    cmd[strlen(cmd) - 1] = '\0';

    //[ls -a  -l   >>  test.txt]
    char* ptr = cmd;
    char* filename = NULL;
    int flag = 0; //flag = 1清空，flag = 2追加， flag = 0没有重定向
    //处理重定向,得到文件名称
    while(*ptr != '\0')
    {
      if(*ptr == '>')
      {
        flag = 1;//清空
        //[ls -l  -a   \0>  test.txt]
        *ptr = '\0';
        ptr++;
        if(*ptr == '>')
        {
          flag = 2;//追加
          //[ls -l -a \0\0 test.txt]
          *ptr = '\0';
          ptr++;
        }
        while(*ptr != '\0' && isspace(*ptr))//找到文件名的首地址
          ptr++;
        filename = ptr;
        ptr++;
        while(*ptr != '\0' && !isspace(*ptr))
          ptr++;
        *ptr = '\0';
      }
      ptr++;
    }

  ptr = cmd;
  char *my_argv[32] = {NULL};
  int my_argc = 0;
  //得到重定向符号前面的指令
  while(*ptr != '\0')
  {
    if(!isspace(*ptr))
    {
      my_argv[my_argc++] = ptr;
      while(*ptr != '\0' && !isspace(*ptr))
        ptr++;
      *ptr = '\0';
    }
    ptr++;
  }
  my_argv[my_argc] = NULL;

  //如果是cd
  if(strcmp(my_argv[0], "cd") == 0)
  {
    chdir(my_argv[1]);
    continue;
  }

  int fd = 0;
  pid_t pid = fork();
  if(pid < 0)
  {
    continue; 
  }
  else if(pid == 0)
  {
    //子进程
    //打开文件
    if(flag == 1) //清空
    {
       fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0664);
      dup2(fd, 1);
    }
    else if(flag == 2) //追加
    {
      fd = open(filename, O_CREAT | O_APPEND | O_RDWR, 0664);
      dup2(fd, 1);
    }
    execvp(my_argv[0], my_argv);
    return -1;
  }
  //进程等待
  wait(NULL);
  }
  return 0;
}
