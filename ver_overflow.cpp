#include "functions.h"
#include<stdio.h>

int row,col,cur_row,cur_col;    //extern variables
vector <string> vec;                         //storing ls output
int ovstart,ovend;                           //overflow starting and end indices of vectors printing on screen



void clearrow(int strow,int endrow)
{
  int i;
  printf("\033[2J");

  printf("******************************File explorer************************");
  
  for(i=0;i<row-1;i++)                                                         //move cursor to last row
       printf("\n");
  
  moveto(row-1,1);                                                             //move to last row and print status bar
  printf("-------------------------------------------------------------------------------\n");
  printf("command mode");                                                      //13 chars
  moveto(2,1);     


}
void voverflow()                       //initialize values of ovstart and ovend
{ 
  int len = vec.size();
  int i;
 //
   if(len > row-3)
   {    ovstart=0;
        ovend=row-3;                      //ovend= index of vector if vec is greater than size of terminal end is 2nd last line 
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
       if(cur_row!=2)               //if at 2nd row dont move up
         moveto(cur_row-1,cur_col);
       if(cur_row==2  && ovstart != 0)  
       {  ch=getchar();
          arrow(ch);
          ovstart--;
          ovend--;
          moveto(2,1);
          clearrow(2,row-3);
          moveto(2,1);
          printvector(); 
          moveto(row-1,1);                                                             //move to last row and print status bar
          printf("-------------------------------------------------------------------------------\n");
          printf("command mode");
          moveto(2,1);   
       }   
      //printf("You pressed the up arrow key !!\n");
    }
  
  if(ch == 66 && k == 2)                             
   { 
      if(cur_row != row-2)
        moveto(cur_row+1,cur_col);
      if(cur_row==row-2 && ovend != vec.size()-1)//place the cursor there only and print vector from overflow
        {  ch=getchar();
           arrow(ch);                                              //and check if size of vec is greater than size of terminal vec.size>row-2
          ovstart++;                                       // cursor is not at vec[0]
          ovend++;
          moveto(2,1);
          clearrow(2,row-3);
          moveto(2,1);
         printvector(); 
          moveto(row-1,1);                                                             //move to last row and print status bar
  printf("-------------------------------------------------------------------------------\n");
  printf("command mode");    
          moveto(row-3,1);
          }                  
      //printf("You pressed the down arrow key !!\n");
   }
  
  if(ch == 67 && k==2)
   // printf("right arrow\n");
  
  if(ch==68 && k==2)
   // printf("left arrow\n");
  
  if(ch != 27 && ch != 91)      // if ch isn't either of the two, the key pressed isn't up/down so reset k
    k = 0;
  
}

