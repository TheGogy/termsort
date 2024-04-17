#include <complex.h>
#include <stdio.h>
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

const char *algorithms[] = {"bogosort", "bubblesort", "quicksort"};
const int n_algorithms = 3;
struct winsize w;

int main(int argc, char **argv){

  if (argc != 2) {
    printf("Usage: %s <sorting algorithm>\n", argv[0]);
    return EXIT_FAILURE;
  }

  if (strcmp("list", argv[1]) == 0) {
    printf("Possible sorting algorithms: \n");
    for (int i = 0; i < n_algorithms; i++) {
      printf("%s\n", algorithms[i]);
    }
    return EXIT_SUCCESS;
  }
  
  int algorithm = -1;
  for (int i = 0; i < n_algorithms; i++) {
    if(strcmp(algorithms[i], argv[1]) == 0){
      algorithm = i;
      break;
    }
  }
  if (algorithm == -1) {
    printf("\"%s\" is not a known sorting algorithm. To list available algorithms, use:\n\n%s list\n", argv[1], argv[0]);
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
  
  if (algorithm == 0){
    bogoSort(arr, ws.cols, ws.rows);
  } else if (algorithm == 1) {
    bubbleSort(arr, ws.cols, ws.rows);
  } else if (algorithm == 2) {
    quickSort(arr, 0, ws.cols - 1, ws.cols, ws.rows);
  }

  getch(); // Wait for user input before exiting
  handleExit(0);
  return EXIT_SUCCESS;
}
