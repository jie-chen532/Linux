#include<stdio.h>
#include<string.h>
#include"test.h"

void test()
{
  printf("this is a test function");
  printf("\n");
}

int main()
{
  int arr[] = {1, 2, 3, 4, 5};
  int i = 0;
  for(i = 0; i < 5;i++)
  {
    printf("%d ",arr[i]);
  }
  printf("\n");
  test();
  test1();
  test2();
  return 0;
}
