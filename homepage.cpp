#include<stdio.h>
#include<sys/ioctl.h>
//#include "list.c"
//#include "termios1.c"
#include "functions.h"

using namespace std;

struct winsize w;
char ch;
int row,col,cur_row,cur_col;                 
  
void moveto(int x,int y)
{
  printf("\033[%d;%dH",x,y);
  cur_row=x;
  cur_col=y;
}

void moveup(int x)
{  
  printf("\033[%dA",x);
  cur_row-=x;
}

void movedown(int x)
{
  printf("\033[%dB",x);
  cur_row+=x;
}



void homepage()
{ ioctl(0,TIOCGWINSZ,&w);
  //printf("lines =%d\n columns= %d\n",w.ws_row,w.ws_col);     
  int i;
  
  row=w.ws_row;
  col=w.ws_col;
  
  enableRawMode();
  
  printf("******************************File explorer************************");
  
  for(i=0;i<row-1;i++)                                                         //move cursor to last row
       printf("\n");
  
  moveto(2,1);                                                                 //move to 2nd row and list dirs         
  
  list();
  
  moveto(row-1,1);                                                             //move to last row and print status bar
  printf("command mode");                                                      //13 chars
  moveto(2,1);                                                                 //move cursor to 2nd row
   
  cur_row=2;
  cur_col=1;

}



void arrow(char ch)
{   static char k=0;               //arrow key returns 3 values

  if(ch == 27)                  // if ch is the escape sequence with num code 27, k turns 1 to signal the next
    k = 1;
  
  if(ch == 91 && k == 1)       // if the previous char was 27, and the current 91, k turns 2 for further use
    k = 2;
  
  if(ch == 65 && k == 2)       // finally, if the last char of the sequence matches, you've got a key !
    { 
       if(cur_row!=2)               //if at 2nd row dont move up
         moveup(1);
      //printf("You pressed the up arrow key !!\n");
    }
  
  if(ch == 66 && k == 2)                             
   { 
      if(cur_row != row-2)
        movedown(1);                   
      //printf("You pressed the down arrow key !!\n");
   }
  
  if(ch == 67 && k==2)
   // printf("right arrow\n");
  
  if(ch==68 && k==2)
   // printf("left arrow\n");
  
  if(ch != 27 && ch != 91)      // if ch isn't either of the two, the key pressed isn't up/down so reset k
    k = 0;
  
}



int main()
{
  homepage();
  while(1)
  {
     ch=getchar();
     arrow(ch);
 
     if(ch==':')
       {  moveto(row-1,13);
          printf("in command mode");
          break;
       }
  
  }

  return 0;
}
