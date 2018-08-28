#include<stdio.h>
#include<sys/ioctl.h>
#include "list.c"

void moveto(int x,int y)
{
  printf("\033[%d;%dH",x,y);
}
int main()
{ struct winsize w;
  ioctl(0,TIOCGWINSZ,&w);
  //printf("lines =%d\n columns= %d\n",w.ws_row,w.ws_col);     
  int i;
  int row,col;
  row=w.ws_row;
  col=w.ws_col;
    
  printf("******************************File explorer*********************");
  for(i=0;i<row-1;i++)
       printf("\n");
  moveto(2,1);
  //printf("\033[2;1H");
  list();
  int a;
  //printf("\033[%d;1H",row-1);
  moveto(row-1,1);
  printf("command mode:");
  scanf("%d",&a);
  
  return 0;
}
