#include<stdio.h>
#include<fcntl.h>     
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>

int main()
{
  umask(0);
  //打开文件
  int fd = open("./bite", O_CREAT | O_RDWR, 0664);
  if(fd < 0)
  {
    perror("open error");
    return -1;
  }
  //向文件写入数据
  char *buf = "i like linux!";
  int ret = write(fd, buf, strlen(buf));
  if(ret < 0)
  {
    perror("write error");
    return -1;
  }
  lseek(fd, 0, SEEK_SET);

  char buf1[1024] = {0};
  ret = read(fd, buf1, 1023);
  if(ret < 0)
  {
    perror("read error");
    return -1;
  }
  printf("%s", buf1);
  close(fd);
  return 0;
}
