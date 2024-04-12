#include <sys/ioctl.h>
#include <unistd.h>
#include <signal.h>

#include "arrayutils.h"
#include "renderer.h"
#include "sorting.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

struct winsize w;


int main(int argc, char **argv){


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

  // Set up signal handler for Ctrl+C
  signal(SIGINT, handleExit);
  
  bogosort(arr, ws.cols, ws.rows);

  handleExit(0);

  return 0;
}
