#include<stdio.h>
#include<stdlib.h>


int main(int argc, char* argv[], char* environ[])
{
  for(int i = 0; i < argc; i++)
  {
    printf("argv[%d]=%s\n", i, argv[i]);
  }
}

/*
int main(int argc, char* argv[], char* environ[])
{
  for(int i = 0; environ[i] != NULL; i++)
  {
    printf("%s\n", environ[i]);
  }
  return 0;
}
*/ 

/*
int main()
{
  extern char **environ;   
  for(int i = 0; environ[i] != NULL; i++)
  {
    printf("%s\n", environ[i]);
  }
  return 0;
}
*/  

/*
int main()
{
  char* env = getenv("MYVAL");
  if(env == NULL)
  {
    printf("找不到MYVAL\n");
  }
  else 
  {
    printf("MYVAL:%s\n", env);
  }
  return 0;
}
*/

/*
int main()
{
  char* env = getenv("MYVAL");
  char* env1 = getenv("MYVAL1");
  //查找普通变量
  if(env == NULL)
  {
    printf("找不到MYVAL\n");
  }
  else 
  {
    printf("普通变量MYVAL:%s\n",env);
  }
  //查找环境变量
  if(env1 == NULL)
  {
    printf("没有环境变量MYVAL1\n");
  }
  else 
  {
    printf("环境变量MYVAL1:%s\n",env1);
  }
  return 0;
} 
*/    
