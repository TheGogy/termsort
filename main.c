#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "renderer.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

struct winsize w;

void handleExit(int signum) {
  printf("\e[1;1H\e[2J"); // Clear screen
  printf(ANSI_COLOR_MAGENTA "Goodbye!\n" ANSI_COLOR_RESET);
  exit(0);
}


int main(int argc, char **argv){
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  // Disable buffering on stdout
  setvbuf(stdout, NULL, _IONBF, 0);

  // Initialise arrays
  int arr_len;
  int block_size;
  if (w.ws_col > w.ws_row) {
    arr_len = w.ws_row;
    block_size = w.ws_col / w.ws_row;
  } else {
    arr_len = w.ws_col;
    block_size = w.ws_row / w.ws_col;
  }

  int arr[arr_len];

  for (int i = 0; i < arr_len; i++) {
    arr[i] = i+1;
  }

  // Set up signal handler for Ctrl+C
  signal(SIGINT, handleExit);
  int moved_element = 10;
  while (1){
    usleep(100000);
    render(arr, arr_len, block_size, moved_element, w.ws_row, w.ws_col);
  }
  return 0;
}
