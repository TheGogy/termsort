#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

struct winsize w;

/* Move cursor to position */
static inline void goToPos(int x, int y){
  printf("\e[%d;%dH", x, y);
}

/* Render each individual frame */
void render(int arr[], int arr_len, int block_size, int moved_element){
  for (int i = 0; i < w.ws_row; i++) {
    goToPos(i, 0); // Go to beginning of line
    for (int j = 0; j < arr_len; j++) {
      if (arr[j] >= w.ws_row - i){
        if (j == moved_element) {printf(ANSI_COLOR_RED);}
        for (int k = 0; k < block_size; k++) {
          printf("█");
        }
        if (j == moved_element) {printf(ANSI_COLOR_RESET);}
      } else {
        for (int k = 0; k < block_size; k++) {
          printf(" ");
        }
      }
    }
  }
  fflush(stdout); // Display frame immediately
}

void handleExit(int signum) {
  printf("\e[1;1H\e[2J"); // Clear screen
  printf(ANSI_COLOR_MAGENTA "Goodbye!\n" ANSI_COLOR_RESET);
  exit(0);
}


int main(int argc, char **argv){
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

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

  while (1){
    // usleep(1000000);
    render(arr, arr_len, block_size, 10);
  }
  return 0;
}
