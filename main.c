#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

struct winsize w;

static inline void goToPos(int x, int y){
  printf("\033[%d;%dH", x, y);
}

void render(int arr[], int line_size){
  char buffer[w.ws_col];
  for (int i = 0; i < w.ws_row; i++) {
    goToPos(i, 0); // Go to beginning of line
    for (int j = 0; j < w.ws_col; j++) {
      
    }
  }
}

int main(int argc, char **argv){
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  int arr_len = 10;
  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  while (1){
    render(arr, arr_len);
    getchar();
  }
  return 0;
}
