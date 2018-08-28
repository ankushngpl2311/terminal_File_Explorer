#include<stdio.h>
#include "sum.h"

int main()
{
  int a,b;
  printf("Enter a and b"); 
 scanf("%d%d",&a,&b);

  printf("%d",sum(a,b));
}
