#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

void *pthread_entry(void* arg)
{
  //普通线程tid
  pthread_t ctid = pthread_self();
  while(1)
  {
    printf("%s---%p\n", (char*)arg, ctid);
    sleep(2);//1s打印一次
  }
  return NULL;
}

int main()
{
  //创建线程
  pthread_t tid;
  char *ptr = "i am common pthread";
  //int pthread_create(pthread_t *tid, pthread_attr_t *attr, void*(*routine)(void*), void *arg);
  int ret = pthread_create(&tid, NULL, pthread_entry, (void*)ptr);
  if(ret != 0)
  {
    printf("pthread_create failed\n");
    return -1;
  }
  printf("create pthread success\n");
  //主线程tid
  pthread_t mtid = pthread_self();
  while(1)
  {
    printf("i am main thread---%p\n", mtid);
    sleep(1);
  }
  return 0;
}

