#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>


int main()
{
  umask(0);
  int fd = open("test.txt", O_RDWR | O_CREAT, 0777);
  if(fd < 0)
  {
    perror("open error");
    return -1;
  }
  dup2(fd, 1);//将标准输出重定向到test.txt
  printf("fd = %d\n", fd);
}
