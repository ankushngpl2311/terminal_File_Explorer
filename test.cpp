#include<stdio.h>

#include<unistd.h>
#include<dirent.h>
#include<sys/types.h>
#include <vector>
#include<string>
#include<iostream>
#include<cstring>
using namespace std;




int main()
{ string s="/home/ankush/os";
/*char a[100];
char *p,*p2;
char *pdir;
pdir= getcwd(a,100);
char b[3]={'a','x','\0'};
p="/";
strcat(a,s);
strcat(a,b);
//string s = pdir + '/' + b;
*/
char a[100];

string pdir=getcwd(a,100);
cout<<pdir;
char arr[1000];
strcpy(arr, s.c_str());
DIR *dir;
   //vector <string> v;
                               //clears the vector to 0
   //p= getcwd(a,100);
dir=opendir(arr);
closedir(dir);
//cout<<pdir;
}