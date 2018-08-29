//clear screen in homepage.cpp
#include<vector>
#include<string>
#include<iostream>
using namespace std;
void homepage();
void moveto(int x,int y);

//Non canonical mode  in termios1.cpp
void enableRawMode();
void disableRawMode();

//ls in list.cpp  returns a vector containing names of dir and files
vector <string> list();

