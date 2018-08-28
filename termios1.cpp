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


