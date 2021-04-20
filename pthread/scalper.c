#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int tickies = 100;  //票数设为全局变量

void *scalper(void *arg)
{
  while(1)
  {
    if(tickies > 0)
    {
      usleep(1000);
      printf("我抢到票了%p, 票还有%d张\n", pthread_self(), tickies);
      --tickies;
    }
    else{
      pthread_exit(NULL);
    }
  }
  return NULL;
}

int main()
{
  //创建4个线程
  pthread_t tid[4];
  for(int i = 0; i < 4; i++)
  {
    int ret = pthread_create(&tid[i], NULL, scalper, NULL);
    if(ret != 0)
    {
      printf("pthread create failed\n");
      return -1;
    }
  }

  //等待4个普通线程
  for(int i = 0; i < 4; i++)
  {
    pthread_join(tid[i], NULL);
  }

  return 0;
}
