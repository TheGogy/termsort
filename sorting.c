/* The actual sorting algorithms of the project */

/*
 * algorithms ----------
 *
 * bogosort
 * bubble sort
 */

#include "sorting.h"
#include "arrayutils.h"
#include "renderer.h"

#define SLEEP 15000

void bogoSort(int arr[], int cols, int rows) {
  int moved_element;
  while(1) {
    moved_element = isSorted(arr, cols);
    shuffleArray(arr, cols);
    render(arr, moved_element, cols, rows);
    usleep(SLEEP); // Stop deprecating simple functions for complex ones
    // usleep works perfectly fine
  }
}

void bubbleSort(int arr[], int cols, int rows) {
  for (int i = 0; i < cols - 1; i++) {
    for (int j = 0; j < cols - i - 1; j++) {
      render(arr, j, cols, rows);
      usleep(SLEEP);
      if (arr[j] > arr[j + 1]) {
        swap(&arr[j], &arr[j+1]);
      }
    }
  }
}
