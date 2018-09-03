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

#include <sstream>
using namespace std;


int row=1,col=1,cur_row=1,cur_col=1;    //extern variables
vector <string> vec;                        //storing ls output
vector <string> fdetails;
int ovstart=1,ovend=1;                           //overflow starting and end indices of vectors printing on screen
int vindex=0;

stack <string> stkl;
stack <string> stkr;


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
  
  list(home,vec);
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

string int_to_str(int num)
{
    stringstream ss;

    ss << num;

    return ss.str();
}

void getdetails(string filename)
{
    struct stat fileStat;
     char arr[1000];
   strcpy(arr, filename.c_str());

     if(stat(arr,&fileStat) < 0)
     {   cout<<"no";    
        return;
    }


    string s="";
    char t[ 100 ] = "";
    

    string s1=int_to_str(fileStat.st_size);
    
    s=s+ s1; //+ " bytes   ";
    int j,l;
    l=s.length();
    if(l<13)
    {
      for(j=l;j<10;j++)
        s=s+" ";
    }
    s=s+"bytes   ";
    strftime(t, 100, "%d/%m/%Y %H:%M:%S", localtime( &fileStat.st_mtime));
 
    s1=t;
    s=s + s1+ "   ";
   

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

    fdetails.push_back(s);
}



void list(string path,vector <string> &vec)                   
{   
   vindex=0;         
   
   ino_t fsrno;
   //char a[100];
   //char *p,*p2;
   

   //covert string to char*
   char arr[1000],arr1[1000];
   strcpy(arr, path.c_str());
   

   struct dirent* dirpnt; 
   DIR *dir;
   //vector <string> v;
   vec.clear();
   fdetails.clear();
   //fill(vec.begin(), vec.end(), 0);                            //clears the vector to 0
   //p= getcwd(a,100);

   string s;
   dir=opendir(arr);
   while(dirpnt=readdir(dir))
   {   s="";
       s=path+"/"+ string(dirpnt->d_name);
     //printf("%s\n",dirpnt->d_name);
     vec.push_back(dirpnt->d_name);
     getdetails(s);
     //getdetails(dirpnt->d_name);
     //cout<<dirpnt->d_name<< dirpnt->d_type <<"\n";
   }
   closedir(dir);
   
   //return vec;
  // printf("cwd =%s\n",p);
  // printf("dir=== %s",d.d_name);

}


void printvector()
{
  int i,j,l;
  for(i=ovstart;i<=ovend;i++)
   { cout<<vec[i];
     l=vec[i].length();
     if(l<25)
     {
        for(j=l;j<25;j++)
          cout<<" ";
     }
     cout<<fdetails[i]<<"\n";
    }  
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
      {   
        if(!stkr.empty())
        {
          string y=stkr.top();
          stkr.pop();
          stkl.push(y);
          list(y,vec);
          printbground();

        }
         


      }
      // printf("right arrow\n");
  
  

     if(ch==68 && k==2)
     {     
         if(stkl.size()!=1)
         {
          string s= stkl.top();
          stkr.push(s);
          stkl.pop();
          list(stkl.top(),vec);
          printbground();
         }
         if(stkl.size()==1)
         {
            list(home,vec);
            printbground();
         }
       
     }
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
      {  pdir=s;
        list(s,vec);
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


        //pdir=s;


        stkl.push(pdir);                            //left stack push
       }
      else                                                  //open file
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
      pdir=home;
      homepage(home);
      //pdir=home;                           //so that enter function can work again recursively
      stkl.push(pdir);
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
     list(s,vec);
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

     stkl.push(pdir);                        //left stack push
     }
     if(pdir == home)
     {   
       moveto(row,1);
       printf("Status bar: ");
       moveto(2,1);
     }
     //cout<<ch;
}













//**********************************************************************************************


                               //COMMAND MODE 

//***********************************************************************************************

  int gotoflag=0;
 vector <string> command;

void clearstatus()
{   moveto(row,13);
    int i;
    for(i=14;i<col-5;i++)
      cout<<" ";
    //moveto(row-1,13);
    moveto(row,13);
    //cout
    
}
void cmdmode()
{
  //enableRawMode();


  moveto(row,13);
  string s="";
  while(1)
{  
  char ch;
  
  ch=getchar();
  int len=s.length();
  if(ch==27)
    break;
  //cout<<s<<"\n";
  
  else if(ch=='\n')
    { getcommand(s);
      execute();

      //clearstatus();
      s="";                    //for next command
    
     if(gotoflag==1)
      {  gotoflag=0;

          break;
      }
    }
  else if(ch==127)
     backcmd(len,s);
 
  
  else
   { s=s+ch;
      printf("%c",ch);
    }
  //if(ch=='\n')
    //getcommand(s);

    
    
  
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
          { cout<<" Invalid arguments. Press Enter";
             char z;
              do
               { 
                 z=getchar();
                }while(z!='\n');

                if(z=='\n')
                 clearstatus();   
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
    else if(command[0]=="goto")
    {
        gotoo(command[1]);
        gotoflag=1;
        return;

    }
    else 
    {   cout<<"           INVALID COMMAND!!. Press enter";
     
      char z;
     do
     { 
          z=getchar();
     }while(z!='\n');

     if(z=='\n')
     clearstatus();  
       //clearstatus();
         //print("");
     
     
     
    }

}



void create_file(string filename,string destination)
{   //cout<<filename<<" "<<destination;
    int flag=0;
      //filename= home + "/" + filename;
       if(destination==".")
      { destination =pdir;
        flag=1;
      }
    else
      destination= home + "/" + destination;
      
   
  
  FILE *fptr;
     string s=destination + "/" + filename;


     char arr[1000];
        strcpy(arr, s.c_str()); 


  fptr=fopen(arr,"w");
  //cout<<"file created";

  fclose(fptr);
   if(flag==1)
   {
   list(destination,vec);
   printbground();
   moveto(row,13);}
   cout<<"file created";
  cout<<"Press enter";

       char z;
     do
     { 
          z=getchar();
     }while(z!='\n');

     if(z=='\n')
     clearstatus(); 
}


void create_dir(string dirname,string destination)
{  int flag=1;
  struct stat st = {0};
   if(destination==".")
          {  flag=1;
            destination =pdir;
          }
     //dirname=home + "/" +dirname;
      else
       destination=home + "/" + destination;


       
    string s=destination + "/" + dirname;


    char arr[1000];
    strcpy(arr, s.c_str()); 
   
    if (stat(arr, &st) == -1) 
    {
       mkdir(arr, 0700);
       if(flag==1)
       {
       list(destination,vec);
        printbground();
       moveto(row,13);
     }
       cout<<"dir created ";
       cout<<"Press enter";
       char z;
     do
     { 
          z=getchar();
     }while(z!='\n');

     if(z=='\n')
     clearstatus(); 

    }
    else
      { cout<<"dir exists";
        cout<<"Press enter";

       char z;
     do
     { 
          z=getchar();
     }while(z!='\n');

     if(z=='\n')
     clearstatus(); 
      }
}



void rename(string oldfile,string newfile)                        //implement if not a file
{


    //string s=destination + "/" + dirname;
    
     oldfile = home + "/" + oldfile;
     newfile = home + "/" + newfile; 
    char oldf[1000],newf[100];
    strcpy(oldf, oldfile.c_str());
    strcpy(newf, newfile.c_str());


      int x = rename(oldf, newf);          
  
    if(x == 0) 
    {
      printf("Renamed");
      cout<<"Press enter";

       char z;
     do
     { 
          z=getchar();
     }while(z!='\n');

     if(z=='\n')
     clearstatus(); 

    } 
   else 
   {
      printf("unable to rename");
      cout<<"Press enter";

       char z;
     do
     { 
          z=getchar();
     }while(z!='\n');

     if(z=='\n')
     clearstatus(); 


    }


}



void move(string filename,string destination)
{
      filename= home + "/" + filename;
      destination= home + "/" + destination;
     

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
     {   if(destination==pdir)                           //live changes reflect to normal mode
         {
              list(destination,vec);
              printbground();
              moveto(row,13);
         }
       moveto(row,13);
       printf("Moved ");
       cout<<"Press enter";

      char z;
       do
       { 
            z=getchar();
       }while(z!='\n');

       if(z=='\n')
        clearstatus(); 


    }


   else 
   {
      printf("Error ");
      cout<<"Press enter";
       fflush(stdin);
       char z=getchar();
        moveto(row,13);
       if(z=='\n')
       {  int i;
          
        // moveto(row,13);
       clearstatus();
       }

    }


}



void gotoo(string path)
{
  if(path=="/")
   {
    list(home,vec);
     printbground();
     return;
   } 
   path= home + path;
   stkl.push(path);
   pdir=path;

   list(path,vec);
   printbground();
   //pdir=path;
   
     /*cout<<"Press enter";
      char z=getchar();
        moveto(row,13);
       if(z=='\n')
       {  int i;
          
        // moveto(row,13);
       clearstatus();
       }
*/
}



