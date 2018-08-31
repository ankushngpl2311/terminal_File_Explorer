#include<stdio.h>
#include<sys/ioctl.h>
//#include "list.c"
//#include "termios1.c"
#include "functions.h"
#include<vector>
#include<string>
#include<iostream>
#include<unistd.h>
#include<dirent.h>
#include<sys/types.h>

using namespace std;

struct winsize w;
char ch; 
char pwdir[1000];                                     //getchar
//int row,col,cur_row,cur_col;                 // row,col =dimensions of terminal cur_row,cur_col= postion of cursor 
//vector <string> vec;                         //storing ls output
//int ovstart,ovend;                           //overflow starting and end indices of vectors printing on screen

string pdir="";
string home="";

int main()
{
  ioctl(0,TIOCGWINSZ,&w);

  row=w.ws_row;
  col=w.ws_col;
  
  enableRawMode();
  
  //pwdir[0]='\0';
  home=getcwd(pwdir,1000);
  homepage(home);
  pdir=home;
  stkl.push(pdir);
 
  while(1)
  {  
     //
     //pdir= getcwd(pwdir,1000);
     //cout<<pdir;
     ch=getchar();
     arrow(ch);
     enter(ch);
     hkey(ch);
     if(ch==127)
     backspace(ch);
     if(ch==':')
       {  moveto(row,13);
          printf("in command mode");
          //getchar();

          break;
       }
  
  }

  return 0;
}
