#include<stdio.h>
#include<unistd.h>

int main()
{
  pid_t pid = fork();
  int g_val = 100;
  if(pid < 0)
  {
    printf("进程出错\n");
  }
  else if(pid == 0) 
  {
    printf("pid--->g_val:%d--->&g_val:%p\n", g_val, &g_val);
  }
  else 
  {
    g_val = 200;
    printf("ppid--->g_val:%d--->&g_val:%p\n", g_val, &g_val);
  }
  return 0;
}
