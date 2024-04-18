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

const char *algorithms[] = {
  "bogosort", 
  "bubblesort", 
  "quicksort", 
  "shellsort", 
  "mergesort", 
  "heapsort",
  "gnomesort",
  "cocktailsort",
  "insertionsort",
  "selectionsort",
  "oddevensort",
  "pancakesort",
  "pigeonholesort",
  "combsort",
  "stoogesort",
};
const int n_algorithms = 15;
struct winsize w;

int main(int argc, char **argv){

  if (argc != 2 || strcmp("help", argv[1]) == 0) {
    printf(
      "Usage:\n"
      "%s <sorting algorithm>   Show sorting algorithm\n"
      "%s list                  List available sorting algorithms\n"
      "%s help                  Print this help menu\n",
      argv[0], argv[0], argv[0]);
    return EXIT_FAILURE;
  }

  if (strcmp("list", argv[1]) == 0) {
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
    printf("\"%s\" is not a known sorting algorithm. To list available algorithms, use:\n\n%s list\n\n", argv[1], argv[0]);
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

  // Initialise counter
  struct Counter c;

  if (algorithm == 0){
    c = bogoSort(arr, ws.cols, ws.rows);
  } else if (algorithm == 1) {
    c = bubbleSort(arr, ws.cols, ws.rows);
  } else if (algorithm == 2) {
    c = quickSortWrapper(arr, ws.cols, ws.rows);
  } else if (algorithm == 3) {
    c = shellSort(arr, ws.cols, ws.rows);
  } else if (algorithm == 4) {
    c = mergeSort(arr, 0, ws.cols - 1, ws.cols, ws.rows);
  } else if (algorithm == 5) {
    c = heapSort(arr, ws.cols, ws.rows);
  } else if (algorithm == 6) {
    c = gnomeSort(arr, ws.cols, ws.rows);
  } else if (algorithm == 7) {
    c = cocktailSort(arr, ws.cols, ws.rows);
  } else if (algorithm == 8) {
    c = insertionSort(arr, ws.cols, ws.rows);
  } else if (algorithm == 9) {
    c = selectionSort(arr, ws.cols, ws.rows);
  } else if (algorithm == 10) {
    c = oddevenSort(arr, ws.cols, ws.rows);
  } else if (algorithm == 11) {
    c = pancakeSort(arr, ws.cols, ws.rows);
  } else if (algorithm == 12) {
    c = pigeonholeSort(arr, ws.cols, ws.rows);
  } else if (algorithm == 13) {
    c = combSort(arr, ws.cols, ws.rows);
  } else if (algorithm == 14) {
    c = stoogeSort(arr, 0, ws.cols - 1, ws.cols, ws.rows);
  }

  renderSorted(arr, ws.cols, ws.rows);

  // Display the results in the top left
  WINDOW *results = newwin(7, 25, 0, 0);
  wattron(results, A_BOLD);
  mvwprintw(results, 1, 1, "%s", algorithms[algorithm]);
  wattroff(results, A_BOLD);
  mvwprintw(results, 2, 1, "Total elements:   %d\n", ws.cols);
  mvwprintw(results, 3, 1, "Unique elements:  %d\n", ws.rows);
  mvwprintw(results, 4, 1, "Array indexes:    %d\n", c.indexes);
  mvwprintw(results, 5, 1, "Array moves:      %d\n", c.moves);
  box(results, 0, 0);
  move(ws.cols, ws.rows) ;

  wrefresh(results);

  getch(); // Wait for user input before exiting
  handleExit(0);
  return EXIT_SUCCESS;
}
