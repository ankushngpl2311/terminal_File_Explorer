#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/types.h>
#include <vector>
#include<string>
#include<iostream>
#include "functions.h"
#include<string.h>
#include <sys/stat.h>
#include<stdlib.h>
using namespace std;


int row=1,col=1,cur_row=1,cur_col=1;    //extern variables
vector <string> vec;                         //storing ls output
int ovstart=1,ovend=1;                           //overflow starting and end indices of vectors printing on screen
int vindex=0;


//string pdir="";












void printbground()
{

  int i;
  
  printf("\033[2J");
  
  printf("******************************File explorer************************");
  
  for(i=0;i<row-1;i++)                                                         //move cursor to last row
       printf("\n");
 

   moveto(2,1);                                                                 //move to 2nd row and list dirs         
  
  //vec=list();
  voverflow();  
  printvector();                               
  
  moveto(row-1,1);  
  //cout<<"---------------------------hm\n";                                     //move to last row and print Status bar: 
  printf("-------------------------------------------------------------------------------\n");
  printf("Status bar:");                                                      //13 chars
  moveto(2,1);                                                                 //move cursor to 2nd row
   
  //cur_row=2;
  //cur_col=1;

}


void homepage(string home)
{ 
  //printf("lines =%d\n columns= %d\n",w.ws_row,w.ws_col);     
  int i;
  
  printf("\033[2J");
  
  printf("******************************File explorer************************");
  
  for(i=0;i<row-1;i++)                                                         //move cursor to last row
       printf("\n");
  
  moveto(2,1);                                                                 //move to 2nd row and list dirs         
  
  vec=list(home);
  voverflow();  
  printvector();                               
  
  moveto(row-1,1);  
  //cout<<"---------------------------hm\n";                                     //move to last row and print Status bar: 
  printf("-------------------------------------------------------------------------------\n");
  printf("Status bar:");                                                      //13 chars
  moveto(2,1);                                                                 //move cursor to 2nd row
   
  //cur_row=2;
  //cur_col=1;

}


//*************************************************************************************
//**************************************************************************************

                               //LIST

//**************************************************************************************
//**************************************************************************************







vector<string> list(string path)
{   
   vindex=0;         
   
   ino_t fsrno;
   //char a[100];
   //char *p,*p2;
   

   //covert string to char*
   char arr[1000];
   strcpy(arr, path.c_str());
   

   struct dirent* dirpnt; 
   DIR *dir;
   //vector <string> v;
   vec.clear();
   //fill(vec.begin(), vec.end(), 0);                            //clears the vector to 0
   //p= getcwd(a,100);


   dir=opendir(arr);
   while(dirpnt=readdir(dir))
   {
     //printf("%s\n",dirpnt->d_name);
     vec.push_back(dirpnt->d_name);
     //cout<<dirpnt->d_name<< dirpnt->d_type <<"\n";
   }
   closedir(dir);
   
   return vec;
  // printf("cwd =%s\n",p);
  // printf("dir=== %s",d.d_name);

}


void printvector()
{
  int i;
  for(i=ovstart;i<=ovend;i++)
    cout<<vec[i]<<"\n";
    //combined with above cout cout<<"ovstart= "<<ovstart<<"ovend= "<<ovend
}






//**************************************************************************************
//**************************************************************************************

                             //CURSOR MOVE

//**************************************************************************************
//**************************************************************************************





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






//*************************************************************************************
//**************************************************************************************
                      
                       //vertical overflow

//**************************************************************************************
//**************************************************************************************







void clearrow(int strow,int endrow)
{
  int i;
  printf("\033[2J");

  printf("******************************File explorer************************");
  
  for(i=0;i<row-1;i++)                                                         //move cursor to last row
       printf("\n");
  
  moveto(row-1,1);                                                             //move to last row and print Status bar: 
  printf("---------------------------------------------------------cr\n");
  printf("Status bar: ");                                                      //13 chars
  moveto(2,1);     


}





void voverflow()                       //initialize values of ovstart and ovend
{ 
  int len = vec.size();
  int i;
 //
   if(len > row-3)
   {    ovstart=0;
        ovend=row-4;                      //ovend= index of vector if vec is greater than size of terminal end is 2nd last line 
                                                 //of terminal    
   }
   else
   {
    ovstart=0;                              
    ovend=len-1;                           //when vec is smaller than size of terminal ovend =max size of vector
   }
}






void arrow(char ch)
{   static char k=0;               //arrow key returns 3 values

  if(ch == 27)                  // if ch is the escape sequence with num code 27, k turns 1 to signal the next
    k = 1;
  
  if(ch == 91 && k == 1)       // if the previous char was 27, and the current 91, k turns 2 for further use
    k = 2;
  
  if(ch == 65 && k == 2)       // finally, if the last char of the sequence matches, you've got a key !
    { 
       if(cur_row!=1)               //if at 2nd row dont move up
          moveto(cur_row-1,cur_col);
           
         
       if(cur_row==1  && ovstart != 0)  
       {  //ch=getchar();
          //arrow(ch);
          ovstart--;
          ovend--;
          moveto(2,1);
          clearrow(2,row-3);
          moveto(2,1);
          printvector(); 
          moveto(row-1,1);                                                             //move to last row and print Status bar: 
          printf("---------------------------------------------------------------ua\n");
          printf("Status bar: ");
          moveto(2,1); 

       }

      //printf("You pressed the up arrow key !!\n");
      
      if(vindex!=0)
      { vindex--;             //vector[i] i=i-1;
        //cout<<vindex;
      }
      
      if(cur_row==1)
        moveto(2,1);
    }
  



  if(ch == 66 && k == 2)                             
   { 
      if(cur_row != row-1)
        moveto(cur_row+1,cur_col);
      if(cur_row==row-1 && ovend != vec.size()-1)   //place the cursor there only and print vector from overflow
        {  //ch=getchar();
           //arrow(ch);                                              //and check if size of vec is greater than size of terminal vec.size>row-2
          ovstart++;                                       // cursor is not at vec[0]
          ovend++;
          moveto(2,1);
          clearrow(2,row-3);
          moveto(2,1);
          printvector(); 
          moveto(row-1,1);                                                             //move to last row and print Status bar: 
          printf("-------------------------------------------------------------------da\n");
          printf("Status bar: ");    
          moveto(row-2,1);
        }                  
      //printf("You pressed the down arrow key !!\n");
          if(vindex!=vec.size()-1)
             vindex++;       //vector[i]  i=i+1
           //cout<<vindex;}

           if(cur_row==row-1)
           moveto(row-2,1);                 //needed dont delete  when the flow doesnt enters any of the if's
    }
    
  

     if(ch == 67 && k==2)
   // printf("right arrow\n");
  
  

     if(ch==68 && k==2)
   // printf("left arrow\n");
  
     if(ch != 27 && ch != 91)      // if ch isn't either of the two, the key pressed isn't up/down so reset k
        k = 0;
  


}







void enter(char ch)
{    int i; 
  //convert string to char*
  

  
  //printf("%s is a direc",filename);


    if(ch=='\n')
    {   

        


        string s;
        s = pdir + '/' + vec[vindex];            //concatenate pwd and dir to create path of next dir
        //s=createpath(pdir,vec[vindex]);
        //pdir=s;                               //only if it is a directory if done in file pdir ==dir1/file.text/dir2
      
        char arr[1000];
        strcpy(arr, s.c_str());  

        struct stat buf;
        stat(arr,&buf);
        pid_t pid;


      if(S_ISDIR(buf.st_mode))
      {
        vec=list(s);
        //cout<<vec.size();
        /*voverflow();
        //clearrow(1,row-2);
        printf("\033[2J");
        moveto(1,1);
        printf("******************************File explorer************************");
  
        for(i=0;i<row-1;i++)                                                         //move cursor to last row
            printf("\n");
  
        moveto(2,1);           
        printvector();                               
  
        moveto(row-1,1);                                                             //move to last row and print Status bar: 
        //cout<<"-----------------------------entr";
        printf("---------------------------------------------------------------entr\n");
        printf("Status bar: ");                                                      //13 chars
        moveto(2,1);                                                                 //move cursor to 2nd row
        */
        printbground();


        pdir=s;
       }
      else
      {
         pid = fork();
         if (pid == 0) 
         {

             execl("/usr/bin/xdg-open", "xdg-open", arr, (char *)0);
             exit(1);
         }
      }

   }



}




void hkey(char ch)
{
   if(ch=='h'||ch=='H')
   {
      homepage(home);
      pdir=home;                           //so that enter function can work again recursively
   }
}


void backspace(char ch)
{
  /*int i,index;

  for(i=0;i<vec.size();i++)
  {
        if(vec[i]=="..")
          { index=i;
            break;
          }
  }*/
    int i;
    if(pdir != home)                     //if pdir== home dont move back 
    {
     string s;
     //s = pdir + '/' + "..";            //concatenate pwd and dir to create path of next dir
  //s=createpath(pdir,vec[vindex]);
     s=pdir;
     int i,j=0,l;
     l=s.length();
     for(i=l-1;i>=0;i--)                 //removes last dir as a/b/c => a/b
     {   j++;
         if(s[i]=='/')
         {
           s.erase(i,j);
           break;
          }
  
      }

     pdir=s;
     vec=list(s);
     //cout<<vec.size();
     /*voverflow();                                                       comment 2
     //clearrow(1,row-2);
     printf("\033[2J");
     moveto(1,1);
     printf("******************************File explorer************************");
  
     for(i=0;i<row-1;i++)                                                         //move cursor to last row
         printf("\n");
  
     moveto(2,1);           
     printvector();                               
  
     moveto(row-1,1);                                                             //move to last row and print Status bar: 
     printf("---------------------------------------------------------------------------back\n");
     printf("Status bar: ");                                                      //13 chars
     moveto(2,1);*/
     printbground();
     }
     if(pdir == home)
     {   
       moveto(row,1);
       printf("Status bar: ");
       moveto(2,1);
     }
     //cout<<ch;
}



