#include<stdio.h>
#include<sys/shm.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>

#define IPC_KEY 0x01234567
int main()
{
  umask(0);
  int shmid = shmget(IPC_KEY, 32, IPC_CREAT | 0664);
  if(shmid < 0)
  {
    perror("shmget error");
    return -1;
  }

  void *str = shmat(shmid, NULL, SHM_RDONLY);
  if(str == (void*)-1)
  {
    perror("shmat error");
    return -1;
  }

  while(1)
  {
    printf("%s\n", (char*)str);
    sleep(1);
  }

  shmdt(str);
  shmctl(shmid, IPC_RMID, NULL);
  return 0;
}
