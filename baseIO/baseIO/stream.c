#include<stdio.h>
#include<string.h>


int main()
{
  FILE* fp = fopen("./test.txt", "wb+");
  if(fp == NULL)
  {
    perror("fopen error");
    return -1;
  }
  stdout->_fileno = fp->_fileno;//stdout是标准输出的文件流指针
  printf("你好啊");//printf操作stdout,不会输出到屏幕上，会写入test.txt文件

  fp->_fileno = 1;//1--标准输出的文件描述符
  //写数据
  char* str = "hello";
  fwrite(str, strlen(str), 1, fp);//不会写入文件，写入标准输出文件
  return 0;
}
