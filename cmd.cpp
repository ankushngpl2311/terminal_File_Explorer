#include<stdio.h>
#include<string>
#include<iostream>
#include<unistd.h>
#include<dirent.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include <sys/stat.h>
#include <sstream>

using namespace std;



string int_to_str(int num)
{
    stringstream ss;

    ss << num;

    return ss.str();
}
int main()
{    //vector <string> details;
    //string home;
    //char pwdir[1000];
     //string filename="file2.txt";
     char filename[]="/home/ankush/os/file.txt";

    //FILE *fptr;
    // string s=destination + "/" + filename;

   string str1= string(filename)+ '/'+  "hello";
   cout<< "append= "<<str1<<"\n";
     //char arr[1000];
       //strcpy(arr, filename.c_str());
       //home=""; 
   // home=getcwd(pwdir,1000);

  struct stat fileStat;

     if(stat(filename,&fileStat) < 0)
     {   cout<<"no";    
        return 1;
    }
//cout<<home;

string s="";
char t[ 100 ] = "";
//printf("Information for %s\n",filename);
  //  cout<<"---------------------------\n";
    //cout<<"file size"<<fileStat.st_size<<" bytes";
   // printf("File Size: \t\t%d bytes\n",fileStat.st_size);
    
   // stringstream ss;
   // ss << fileStat.st_size;
    //string str = ss.str();
    string s1=int_to_str(fileStat.st_size);
    //string s1= std::to_string(fileStat.st_size);
    
    s=s+ s1 + " bytes  ";
    //string s1;
    strftime(t, 100, "%d/%m/%Y %H:%M:%S", localtime( &fileStat.st_mtime));
 // printf("\nLast modified date and time = %s\n", t);
  s1=t;
  s=s + s1+ "  ";
    //cout<<"Last modified "<<fileStat.st_atime<<"\n";
    //printf("Number of Links: \t%d\n",fileStat.st_nlink);
    //printf("File inode: \t\t%d\n",fileStat.st_ino);
 
   /* printf("File Permissions: \t");
    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n\n");
   */

   //s=s+"   ";
   s=s+((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
   s+=((fileStat.st_mode & S_IRUSR) ? "r" : "-");
   s+=((fileStat.st_mode & S_IWUSR) ? "w" : "-");
   s+=((fileStat.st_mode & S_IXUSR) ? "x" : "-");
   s+=( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    s+=( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    s+=( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    s+=((fileStat.st_mode & S_IROTH) ? "r" : "-");
    s+=( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    s+=( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
    
    //printf("The file %s a symbolic link\n", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not");
    cout<<"s="<<s;
    return 0;
	//fptr=fopen(arr,"w");
	//cout<<"file created";


}