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
  "badsort",
  "dropsort",
};
const int n_algorithms = 17;
struct winsize w;

int main(int argc, char **argv){

  if (argc < 2 || strcmp("help", argv[1]) == 0) {
    printf(
      "Usage: %s [arguments...] [-se]\n"
      "\n\033[31;1mOptions:\033[0m\n"
      "-s                    Color for swapped element  (default: 1)\n"
      "-e                    Color for sorted animation (default: 2)\n"
      "\n\033[31;1mArguments:\033[0m\n"
      "<sorting algorithm>   Show sorting algorithm\n"
      "list                  List available sorting algorithms\n"
      "help                  Print this help menu\n",
      argv[0]);
    return EXIT_FAILURE;
  }

  int algorithm = -1;
  int col_swap = 1; // Color to display swapped element       (default: red)
  int col_end = 2;  // Color to display when list is sorted   (default: green)

  for (int i = 1; i < argc; i++) {
    if (strcmp("-s", argv[i]) == 0) {
      if (argc > i + 1 && atoi(argv[i+1]) < 256) {
        col_swap = atoi(argv[i+1]);
        i++;
        continue;
      } else{
        printf("Please enter a valid color.\n");
        return EXIT_FAILURE;
      }
    } else if (strcmp("-e", argv[i]) == 0) {
      if (argc > i + 1 && atoi(argv[i+1]) < 256) {
        col_end = atoi(argv[i+1]);
        i++;
        continue;
      } else{
        printf("Please enter a valid color.\n");
        return EXIT_FAILURE;
      }
    } else if (strcmp("list", argv[i]) == 0) {
      for (int i = 0; i < n_algorithms; i++) {
        printf("%s\n", algorithms[i]);
      }
      return EXIT_SUCCESS;
    } else{
      for (int i = 0; i < n_algorithms; i++) {
        if(strcmp(algorithms[i], argv[1]) == 0){
          algorithm = i;
          break;
        }
      }

    }
  }

  if (algorithm == -1) {
    printf("Unknown sorting algorithm. Please run:\n"
           "\033[32;1m%s help\033[0m    for more info, or;\n"
           "\033[32;1m%s list\033[0m    for a list of sorting algorithms.\n", 
           argv[0], argv[0]);
    return EXIT_FAILURE;
  }

  struct WinSize ws = setupRender(col_swap, col_end);

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
  } else if (algorithm == 15) {
    c = badSortWrapper(arr, ws.cols, ws.rows);
  } else if (algorithm == 16) {
    c = dropSort(arr, ws.cols, ws.rows);
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
  wattron(results, A_BOLD);
  box(results, 0, 0);
  wattroff(results, A_BOLD);
  // move(ws.cols, ws.rows); // Move cursor to bottom right to be less distracting

  wrefresh(results);

  getch(); // Wait for user input before exiting
  handleExit(0);
  return EXIT_SUCCESS;
}
