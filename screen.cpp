#include<stdio.h>
#include<sys/ioctl.h>
#include "list.c"
#include "termios1.c"

void moveto(int x,int y)
{
  printf("\033[%d;%dH",x,y);
}
int main()
{ struct winsize w;
  char ch;
  ioctl(0,TIOCGWINSZ,&w);
  //printf("lines =%d\n columns= %d\n",w.ws_row,w.ws_col);     
  int i;
  int row,col;
  row=w.ws_row;
  col=w.ws_col;
  enableRawMode();
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
 // scanf("%d",&a);
  while(1){
  ch=getchar();
     
    if(ch==':')
     {  printf("break\n");
       break;
     }
  }
  return 0;
}
