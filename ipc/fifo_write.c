#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<string.h>
#include<errno.h>
#include<fcntl.h>

int main()
{
  umask(0);
  int ret = mkfifo("fifo.txt", 0664);
  //因为当fifo.txt文件存在时，也会报错
  if(ret < 0 && errno != EEXIST)
  {
    perror("mkfifo error");
    return -1;
  }

  int fd = open("fifo.txt", O_WRONLY);
  if(fd < 0)
  {
    perror("open error");
    return -1;
  }
  char *ptr = "i am process A";
  ret = write(fd, ptr, strlen(ptr));
  if(ret < 0)
  {
    perror("write error");
    return -1;
  }
  close(fd);
  return 0;
}
