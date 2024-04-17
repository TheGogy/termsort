#include <complex.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <signal.h>
#include <ncurses.h>
#include <stdlib.h>

#include "arrayutils.h"
#include "renderer.h"
#include "sorting.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

struct winsize w;

int main(int argc, char **argv){

  if (argc != 2) {
    printf("Usage: %s <sorting algorithm>\n", argv[0]);
    return EXIT_FAILURE;
  }
  int algorithm;
  if (strcmp("bogosort", argv[1]) == 0){
    algorithm = 1;
  } else if (strcmp("bubblesort", argv[1]) == 0) {
    algorithm = 2;
  } else if (strcmp("quicksort", argv[1]) == 0) {
    algorithm = 3;
  } else {
    printf("Unknown sorting algorithm!\n");
    return EXIT_FAILURE;
  }

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
  
  if (algorithm == 1){
    bogoSort(arr, ws.cols, ws.rows);
  } else if (algorithm == 2) {
    bubbleSort(arr, ws.cols, ws.rows);
  } else if (algorithm == 3) {
    quickSort(arr, 0, ws.cols - 1, ws.cols, ws.rows);
  }

  getch(); // Wait for user input before exiting
  handleExit(0);
  return EXIT_SUCCESS;
}
