//clear screen in homepage.cpp
#include<vector>
#include<string>
#include<iostream>
#include<stdio.h>
#include <sys/stat.h>
#include<stdlib.h>
#include<stack>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/stat.h>


#include <sstream>
using namespace std;


//extern struct winsize w;
extern int row,col,cur_row,cur_col;                 // row,col =dimensions of terminal cur_row,cur_col= postion of cursor 
extern vector <string> vec;                         //storing ls output
extern int ovstart,ovend;   
extern int vindex;
extern string pdir;
extern string home;                        //overflow starting and end indices of vectors printing on screen
//extern char a[1000];
extern vector <string> fdetails;


extern stack <string> stkl;
extern stack <string> stkr;


extern vector <string> command;
extern vector <string> cmdvec;


extern int gotoflag;
void homepage(string home);
//void moveto(int x,int y);

//Non canonical mode  in termios1.cpp
void enableRawMode();
void disableRawMode();

//ls in list.cpp  returns a vector containing names of dir and files
void list(string path,vector <string> &v);
void getdetails(string path);
string int_to_str(int num);
void printvector();


//in file ver_overflow.cpp
void clearrow(int strow,int endrow);
void voverflow();
void arrow(char ch);

//in file cursor_move.cpp
void moveto(int x,int y);
void moveup(int x);
void movedown(int x);


void enter(char ch);
void hkey(char ch);
void backspace(char ch);



void printbground();



void cmdmode();

void backcmd(int len,string &s);
void getcommand(string s);

void create_file(string filename,string destination);
void create_dir(string dir,string destination);
void rename(string oldfile,string newfile);
void move(string filename,string destination);
void gotoo(string path);
void execute();

