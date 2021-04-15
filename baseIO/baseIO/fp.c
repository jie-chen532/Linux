#include<stdio.h>
#include<string.h>
int main()
{
  //FILE* fp = fopen("./test.txt", "wb+");
  FILE* fp = fopen("./test.txt", "rb+");
  if(fp == NULL)
  {
    //perror:系统调用接口
    perror("fopen error");
    return -1;
  }

  //末尾偏移10个位置，再写入一条数据，可以读到数据大小，但是只能打印一条数据
  //因为偏移，补的是null或者'\0',arr中可以放'\0',打印字符串，默认碰到'\0',认为字符串结束，所以后面数据打印不到
  fseek(fp, 10, SEEK_END);

  //写数据
  char* ptr = "hello";
  size_t ret = fwrite(ptr, strlen(ptr), 1, fp);
  if(ret == 0)
  {
    perror("fwrite error");
    return -1;
  }

  //跳转文件流指针
  fseek(fp, 0, SEEK_SET);

  //读数据
  char arr[1023] = {0};
  ret = fread(arr, 1, 100, fp);
  //fseek之后，文件流指针指向文件开始位置，但是下面注释的已然输出"文件读到末尾"，因为读数据块大小是100，但是数据的总共大小都没有100，ret为0
  //会走下面的判断语句，此时读完文件，文件流指针会到文件末尾，判断就会读到文件末尾。
  //ret = fread(arr, 100, 1, fp);
  if(ret == 0)
  {
    //出错或者读到文件末尾
    if(feof(fp))
    {
      printf("读到文件末尾\n");
    }
    if(ferror(fp))
    {
      perror("fread error\n");
    }
  }
  //如果不跳转指针位置，就会输出读到文件末尾
  //因为r, r+, w, w+打开文件都是从文件开头写入数据,会将之前的数据覆盖,写完之后文件流指针就会到文件末尾,此时再去读数据,就会返回0---读到文件末尾
  //所以要fseek
  printf("%d-%s\n", ret, arr);
  fclose(fp);
  return 0;
}
