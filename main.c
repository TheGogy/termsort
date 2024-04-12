#include <sys/ioctl.h>
#include <unistd.h>
#include <signal.h>

#include "arrayutils.h"
#include "renderer.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

struct winsize w;


int main(int argc, char **argv){

  // Set up signal handler for Ctrl+C
  signal(SIGINT, handleExit);

  struct WinSize ws = setupRender();

  // Initialise array
  int arr[ws.cols];

  double slope = (double)ws.rows / (double)ws.cols;
  double bar_height = 0.0;
  for (int i = 0; i < ws.cols; i++) {
    bar_height += slope;
    arr[i] = (int)bar_height + 1;
  }
  shuffleArray(arr, ws.cols);

  int moved_element = 10;
  int color = 1;
  while (1){
    render(arr, ws.cols, moved_element, color, ws);
    usleep(250000); // Just works
  }
  
  handleExit(0);

  return 0;
}
