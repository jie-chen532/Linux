#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<errno.h>
#include<fcntl.h>

int main()
{
  umask(0);
  //创建命名管道
  int ret = mkfifo("fifo.txt", 0664);
  if(ret < 0 && errno != EEXIST)
  {
    perror("mkfifo error");
    return -1;
  }

  int fd = open("fifo.txt", O_RDONLY);
  if(fd < 0)
  {
    perror("open error");
    return -1;
  }
  char buf[1024] = {0};
  ret = read(fd, buf, 1023);
  if(ret < 0)
  {
    perror("read error");
    return -1;
  }
  else if(ret == 0)
  {
    printf("所有写端被关闭\n");
    return -1;
  }
  printf("%s\n", buf);
  close(fd);
  return 0;
}
