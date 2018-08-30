#include "functions.h"
#include<stdio.h>

int row,col,cur_row,cur_col;    //extern variables
vector <string> vec;                         //storing ls output
int ovstart,ovend;                           //overflow starting and end indices of vectors printing on screen


void moveto(int x,int y)
{
  printf("\033[%d;%dH",x,y);
  cur_row=x;
  cur_col=y;
  //cout<<cur_row;
}

void moveup(int x)
{  
  printf("\033[%dA",x);
  cur_row-=x;
  //cout<<cur_row;
}

void movedown(int x)
{
  printf("\033[%dB",x);
  cur_row+=x;
  //cout<<cur_row;
}