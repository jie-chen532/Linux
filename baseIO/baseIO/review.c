#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main()
{
  FILE* fp = fopen("bite", "wb+");
  if(fp == NULL)
  {
    perror("fopen error");
    return -1;
  }

  char *ptr = "linux so easy!";
  size_t ret = fwrite(ptr, strlen(ptr), 1, fp);
  if(ret == 0)
  {
    perror("fwrite error");
    return -1;
  }

  fseek(fp, 0, SEEK_SET);

  char buf[1024] = {0};
  ret = fread(buf, 1, 1023, fp);
  if(ret == 0)
  {
    if(ferror(fp))
    {
      printf("读取文件出错\n");
    }

    if(feof(fp))
    {
      printf("已到达文件末尾\n");
    }
  }

  printf("%s\n", buf);
  fclose(fp);
  return 0;
}
