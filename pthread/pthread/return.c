#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

/*
void *pthread_entry(void* arg)
{
  printf("%s\n", (char*)arg);
  sleep(5);
  //退出普通线程
  pthread_exit(NULL);
  return NULL;
}

int main()
{
  pthread_t tid;
  char *ptr = "i am common pthread";
  int ret = pthread_create(&tid, NULL, pthread_entry, (void*)ptr);
  if(ret != 0)
  {
    printf("pthread create failed\n");
  }

  while(1)
  {
    sleep(1);//保证主线程不退出
  }

  return 0;
}
*/

/*
void *pthread_entry(void *arg)
{
  printf("%s\n", (char*)arg);
  while(1)
  {
    sleep(1);//保证普通线程不退出
  }
  return NULL;
}

int main()
{
  pthread_t tid;
  char* ptr = "i am common pthread";
  int ret = pthread_create(&tid, NULL, pthread_entry, (void*)ptr);
  if(ret != 0)
  {
    printf("pthread create failed\n");
    return -1;
  }
  sleep(5);

  //退出普通线程
  pthread_cancel(tid);

  while(1)
  {
    sleep(1); //保证主线程不退出
  }
  return 0;
}
*/

/*
void *pthread_entry(void *arg)
{
  printf("%s\n", (char*)arg);
  sleep(5);
  char *retval = "common pthread exit";
  //char retval[] = "common pthread exit"; 错误  
  pthread_exit((void*)retval);
  return NULL;
}

int main()
{
  pthread_t tid;
  char *ptr = "i am common pthread";
  int ret = pthread_create(&tid, NULL, pthread_entry, (void*)ptr);
  if(ret != 0)
  {
    printf("pthread create failed\n");
    return -1;
  }

  //等待普通线程
  void *retval;
  pthread_join(tid, &retval);
  //获取普通线程退出返回值
  printf("%s\n", (char*)retval);

  return 0;
}
*/


void *fun(void *arg)
{
  printf("%s\n", (char*)arg);
  pthread_detach(pthread_self());
  return NULL;
}

int main()
{
  pthread_t tid;
  char *ptr = "i am common pthread";
  int ret = pthread_create(&tid, NULL, fun, (void*)ptr);
  if(ret != 0)
  {
    printf("pthread create failed\n");
    return -1;
  }
  sleep(5);
  return 0;
}
