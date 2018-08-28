#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include<stdio.h>
struct termios orig_termios;
void disableRawMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}
/*void enableRawMode() {
  tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(disableRawMode);
  struct termios raw = orig_termios;
  raw.c_lflag &= ~(ECHO);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}*/
void enableRawMode() {
  struct termios raw;
  tcgetattr(STDIN_FILENO, &orig_termios);
  raw = orig_termios;
  atexit(disableRawMode);
  raw.c_lflag &= ~(ICANON);
  raw.c_lflag &= ~ECHO;
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


int main()
{   enableRawMode();
	char ch=0,k=0;
  while(1)
  {  ch=getchar();
     
    if(ch=='\n')
     {  printf("break");
       break;
     }
     
    if(ch == 27)                  // if ch is the escape sequence with num code 27, k turns 1 to signal the next
    k = 1;
  if(ch == 91 && k == 1)       // if the previous char was 27, and the current 91, k turns 2 for further use
    k = 2;
  if(ch == 65 && k == 2)       // finally, if the last char of the sequence matches, you've got a key !
    printf("You pressed the up arrow key !!\n");
  if(ch == 66 && k == 2)                             
    printf("You pressed the down arrow key !!\n");
  if(ch == 67 && k==2)
    printf("right arrow\n");
  if(ch==68 && k==2)
    printf("left arrow\n");
  if(ch != 27 && ch != 91)      // if ch isn't either of the two, the key pressed isn't up/down so reset k
    k = 0;
  //printf("%c - %d", ch, ch);    // prints out the char and it's int code
  }
   //disableRawMode();
}