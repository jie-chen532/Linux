#include<stdio.h>
#include<unistd.h> //usleep
int main()
{
  char buf[10] = {'c'};
  for(int i = 0; i < 10; i++)
  {
    buf[i] = '-';
    double per = 1.0 * (i+1) / 10 * 100;
    printf("[""%0.2f%""]""%s\r",per,buf);
    usleep(1500000);
    fflush(stdout); //手动刷新标准输出缓冲区
  }
  return 0;
}
