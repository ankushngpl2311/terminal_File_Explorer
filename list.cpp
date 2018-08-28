#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/types.h>
#include <vector>
#include<string>
using namespace std;
void list()
{  ino_t fsrno;
   char a[100];
   char *p,*p2;
   struct dirent* dirpnt; 
   DIR *dir;
   //vector <string> v;
   p= getcwd(a,100);
   dir=opendir(p);
   while(dirpnt=readdir(dir))
   {
     printf("%s\n",dirpnt->d_name);
    // v.push_back(dirpnt->dname);
   }
   closedir(dir);
   
   //return v;
  // printf("cwd =%s\n",p);
  // printf("dir=== %s",d.d_name);

}
