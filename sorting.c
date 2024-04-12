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


void bogosort(int arr[], int cols, int rows) {
  int moved_element;
  while(1) {
    moved_element = isSorted(arr, cols);
    shuffleArray(arr, cols);
    render(arr, moved_element, cols, rows);
    usleep(100000); // Just works
  }
}



