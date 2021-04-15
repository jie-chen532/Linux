#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
  int fd = open("./tmp.txt", O_RDWR | O_CREAT, 0664);
  if(fd < 0)
    return -1;
  dup2(fd, 1);
  printf("hello bit");
  return 0;
}
