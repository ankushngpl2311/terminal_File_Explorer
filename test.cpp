#include<stdio.h>
#include <termios.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/types.h>
#include <vector>
#include<string>
#include<iostream>
#include<cstring>
#include<string.h>
#include <sys/stat.h>
#include<stdlib.h>
#include "functions.h"
//#include<boost/algorithm/string.hpp>
//struct termios orig_termios;
using namespace std;
/*	void disableRawMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}



void enableRawMode() {
  struct termios raw;
  tcgetattr(STDIN_FILENO, &orig_termios);
  raw = orig_termios;
  atexit(disableRawMode);
  raw.c_lflag &= ~(ICANON);
  raw.c_lflag &= ~ECHO;
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
  
*/


void commandmode()
{
  //enableRawMode();


  moveto(row,13);
string s="";
while(1)
{  
  char ch;
  
  ch=getchar();
  if(ch==27)
  	break;
  //cout<<s<<"\n";
  int len=s.length();
  if(ch=='\n')
  	{ getcommand(s);
  	  execute();
  	}
  if(ch==127)
  	 backcmd(len,s);

   else
   	s=s+ch;
  //if(ch=='\n')
  	//getcommand(s);

    
    printf("%c",ch);
  
}


}