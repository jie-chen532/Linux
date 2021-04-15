#include<stdio.h>
#include<unistd.h>
#include<fcntl.h> 
#include<string.h>
#include<sys/stat.h>

int main()
{
  //如果有O_CREAT就要加权限，否则权限会紊乱
  //但是文件权限并不是0777，而是0775
  umask(0);//umask将权限掩码设置为0，只对当前进程产生影响
  int op = open("./test.txt", O_RDWR | O_CREAT | O_APPEND, 0777);
  if(op < 0)
  {
    perror("open error");
    return -1;
  }
  //写入数据
  char buf[1024] = "哈哈哈哈哈\n";
  size_t ret = write(op, buf, strlen(buf));
  if(ret < 0)
  {
    perror("write error");
  }
  // printf("%d\n", ret);

  //跳转文件指针
  lseek(op, 0, SEEK_SET);

  //读取数据
  char arr[1024] = {0};
  ret = read(op, arr, 100);
  if(ret < 0)
  {
    perror("read error");
    return -1;
  }
  printf("%d---%s\n", ret, arr);
  close(op);
  return 0;
}
