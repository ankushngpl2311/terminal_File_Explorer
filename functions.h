//clear screen in homepage.cpp
#include<vector>
#include<string>
#include<iostream>
#include<stdio.h>
using namespace std;


//extern struct winsize w;
extern int row,col,cur_row,cur_col;                 // row,col =dimensions of terminal cur_row,cur_col= postion of cursor 
extern vector <string> vec;                         //storing ls output
extern int ovstart,ovend;                           //overflow starting and end indices of vectors printing on screen


void homepage();
void moveto(int x,int y);

//Non canonical mode  in termios1.cpp
void enableRawMode();
void disableRawMode();

//ls in list.cpp  returns a vector containing names of dir and files
vector <string> list();
void printvector();


//in file ver_overflow.cpp
void clearrow(int strow,int endrow);
void voverflow();
void arrow(char ch);

//in file cursor_move.cpp
void moveto(int x,int y);
void moveup(int x);
void movedown(int x);

