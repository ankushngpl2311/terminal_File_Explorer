
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <poll.h>
#include <termios.h>

int main() {

  int our_opt = 0;                   /* Our secret number */
  char user_opt = 0;                 /* User guess        */

  struct termios tios, orig_tios;    /* terminal settings */

  

  /* Get current terminal settings */
  if (tcgetattr(0, &orig_tios)){
    printf("Error getting current terminal settings\n");
    return 3;
  }

  /* Copy that to "tios" and play with it */
  tios = orig_tios;
  
  /* We want to disable the canonical mode */
  tios.c_lflag &= ~ICANON;

  /* And make sure ECHO is enabled */
  tios.c_lflag &= ~(ECHO);
  
  /* Apply our settings */
  if (tcsetattr(0, TCSANOW, &tios)){
    printf("Error applying terminal settings\n");
    return 3;
  }

  /* Check whether our settings were correctly applied */
  /*if (tcgetattr(0, &tios)){
    tcsetattr(0, TCSANOW, &orig_tios);
    printf("Error while asserting terminal settings\n");
    return 3;
  }

  if ((tios.c_lflag & ICANON) || !(tios.c_lflag & ECHO)) {
    tcsetattr(0, TCSANOW, &orig_tios);
    printf("Could not apply all terminal settings\n");
    return 3;
  }
*/
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
    printf("right arrow");
  if(ch==68 && k==2)
    printf("left arrow");
  if(ch != 27 && ch != 91)      // if ch isn't either of the two, the key pressed isn't up/down so reset k
    k = 0;
  printf("%c - %d", ch, ch);    // prints out the char and it's int code
  }
   
  
  /* Restore terminal settings */
  tcsetattr(0, TCSANOW, &orig_tios);
  
  return 1;

}

