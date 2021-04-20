#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

void *pthread_entry(void *arg)
{
  return NULL;
}

int main()
{
  pthread_t tid;
  int ret = pthread_create(&tid, NULL, pthread_entry, NULL);
  if(ret != 0)
  {
    printf("pthread create failed\n");
  }

  sleep(5);

  //获取主线程tid
  pthread_t mtid = pthread_self();
  printf("mtid_num:%p\n", mtid);
  printf("ctid_num:%p\n", tid);
  return 0;
}
