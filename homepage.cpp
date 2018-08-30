#include<stdio.h>
#include<sys/ioctl.h>
//#include "list.c"
//#include "termios1.c"
#include "functions.h"
#include<vector>
#include<string>

using namespace std;

struct winsize w;
char ch;                                      //getchar
//int row,col,cur_row,cur_col;                 // row,col =dimensions of terminal cur_row,cur_col= postion of cursor 
//vector <string> vec;                         //storing ls output
//int ovstart,ovend;                           //overflow starting and end indices of vectors printing on screen





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
  
  vec=list();
  voverflow();  
  printvector();                               
  
  moveto(row-1,1);                                                             //move to last row and print status bar
  printf("-------------------------------------------------------------------------------\n");
  printf("command mode");                                                      //13 chars
  moveto(2,1);                                                                 //move cursor to 2nd row
   
  cur_row=2;
  cur_col=1;

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
