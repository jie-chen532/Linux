#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main()
{
  //创建管道
  int fd[2];
  int ret = pipe(fd);
  if(ret < 0)
  {
    perror("pipe error");
    return -1;
  }

  //创建子进程
  pid_t pid = fork();
  if(pid < 0)
  {
    perror("fork error");
    return -1;
  }
  else if(pid > 0)
  {
    char *ptr = "i am father";
    int ret = write(fd[1], ptr, strlen(ptr));
    if(ret < 0)
    {
      perror("write error");
      return -1;
    }
  }
  else 
  {
    char buf[1024] = {0};
    int ret = read(fd[0], buf, 1023);
    if(ret < 0)
    {
      perror("read error");
      return -1;
    }
    printf("%s\n", buf);
  }
  return 0;
}

