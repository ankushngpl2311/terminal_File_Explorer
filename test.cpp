#include<stdio.h>

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
using namespace std;




int main()
{
	int a;
	pid_t pid;
char *filename = "/home/ankush/os/vec";
struct stat buf;
stat(filename,&buf);
if(S_ISDIR(buf.st_mode))
{
	printf("%s is a direc",filename);

}
else
{
  cout<<"not a dir";
  pid = fork();
 if (pid == 0) {
  execl("/usr/bin/xdg-open", "xdg-open", filename, (char *)0);
  exit(1);
    }

}

}