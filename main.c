#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "renderer.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

struct winsize w;

void shuffleArray(int arr[], int arr_len) {
  for (int i = arr_len - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    // Swap arr[i] and arr[j]
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }
}

void handleExit(int signum) {
  printf("\033[1;1H\033[2J"); // Clear screen
  printf(ANSI_COLOR_MAGENTA "Goodbye! (SIGNUM %d)\n" ANSI_COLOR_RESET, signum);
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
  shuffleArray(arr, arr_len);
  
  // Set up signal handler for Ctrl+C
  signal(SIGINT, handleExit);
  
  int moved_element = 10;
  while (1){
    usleep((100000)); // Just works
    printf("\033[1;1H\033[2J"); // Clear screen
    render(arr, arr_len, block_size, moved_element, w.ws_row);
  }
  return 0;
}
