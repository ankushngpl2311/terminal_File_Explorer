
#include "functions.h"
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;


vector<string> command;



void cmdmode()
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
  	  s="";                    //for next command
  	}
  if(ch==127)
  	 backcmd(len,s);
  if(ch==27)
  	break;
  
  else
   	s=s+ch;
  //if(ch=='\n')
  	//getcommand(s);

    
    printf("%c",ch);
  
}


}



void backcmd(int len,string &s)
{   if(len>0)
	{
	printf("\033[1D");
    printf(" ");  
    printf("\033[1D");
    s.erase(len-1,1);
    }
}

void getcommand(string s)
{
	int i;
  string s1="";
  int flag=0;
  command.clear();
  //vector <string> command;
  for(i=0;i<s.length();i++)
  { 
     if(s[i]=='\'')
       { 
         flag++;
         if(flag==2)
         	flag=0;
       }   
  	
  	if(s[i]!=' '||flag==1)
  	{   
  		s1=s1 + s[i];
  	}
    
  	if((s[i]==' '||i==s.length()-1)&&flag==0)
  	{
  		if(s1!="")
  		command.push_back(s1);
  		s1= "";
  	}

  }
   

   int l=command.size();

   //for(i=0;i<l;i++)
   	//cout<< command[i]<<"\n";

    //cout<<"again"<<command[0];

}
void execute()
{   //cout<<"hello there";
    //cout<< command[0];
     int l=command.size();
     int i;

     for(i=1;i<l;i++)
     {
     	//int length1=command[i].length();
     	if(command[i][0]=='\''&&  command[i][command[i].length()-1]=='\'')
     	{
         command[i].erase(command[i].length()-1,1);
         command[i].erase(0,1);	
        }
        else
        	{ cout<<"invalid arguments";
              return;
            }
     }
    


    if(command[0]=="create_file")
    {
    	//cout<<"in execute";
         //command[1].erase(command[1].length()-1,1);
         //command[1].erase(0,1);	
    	create_file(command[1],command[2]);
    }
    
    
    else if(command[0]=="create_dir")
    	create_dir(command[1],command[2]);
    
    

    else if(command[0]=="rename")
    {
    	rename(command[1],command[2]);
    }
     

    
    else if(command[0]=="move")
    {
    	//int j=command.size();
        
        for(i=1;i<l-1;i++)
        {   
           move(command[i],command[l-1]);
        }

        //move(command[1],command[2]);

    }
    else 
    {
    	//print("");
    }

}
void create_file(string filename,string destination)
{   //cout<<filename<<" "<<destination;
	FILE *fptr;
     string s=destination + "/" + filename;


     char arr[1000];
        strcpy(arr, s.c_str()); 


	fptr=fopen(arr,"w");
	//cout<<"file created";

	fclose(fptr);
}


void create_dir(string dirname,string destination)
{
	struct stat st = {0};


    string s=destination + "/" + dirname;


    char arr[1000];
    strcpy(arr, s.c_str()); 
   
    if (stat(arr, &st) == -1) 
    {
       mkdir(arr, 0700);
       cout<<"dir created";

    }
    else
    	cout<<"dir already exists";

}

void rename(string oldfile,string newfile)                        //implement if not a file
{


    //string s=destination + "/" + dirname;
    

    char oldf[1000],newf[100];
    strcpy(oldf, oldfile.c_str());
    strcpy(newf, newfile.c_str());


      int x = rename(oldf, newf);          
	
    if(x == 0) 
    {
      printf("File renamed successfully");
    } 
   else 
   {
      printf("Error: unable to rename the file");
   }


}



void move(string filename,string destination)
{
     char oldf[1000],newd[100];
     int l=filename.length();

     int i;
     string s=filename;
     
     for(i=l-1;i>=0;i--)
     {
     	if(s[i]=='/')
     		break;

     } 
     s.erase(0,i);
     string dest= destination +s;
    
    strcpy(oldf, filename.c_str());
    strcpy(newd, dest.c_str());

      //cout<<oldf<<"\n"<<newd<<"\n";
      int x = rename(oldf, newd);


       if(x == 0) 
    {
      printf("File moved successfully");
    } 
   else 
   {
      printf("Error: unable to move the file");
   }


}


