#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<string.h>

#define KEY 0x01234567
int main()
{
  umask(0);
  int shmid = shmget(KEY, 32, IPC_CREAT | 0664);
  if(shmid < 0)
  {
    perror("shmget error");
    return -1;
  }

  void *str = shmat(shmid, NULL, 0);
  if(str == (void*)-1)
  {
    perror("shmat error");
    return -1;
  }

  int i = 0;
  while(1)
  {
    sprintf(str, "i am process A + %d", i++);
    sleep(1);
  }

  shmdt(str);
  shmctl(shmid, IPC_RMID, NULL);
  return 0;
}
