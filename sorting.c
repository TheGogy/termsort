/* The actual sorting algorithms of the project */

/*
 * algorithms ----------
 *
 * bogosort
 * bubble sort
 * quicksort
 * shellsort
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
    usleep(SLEEP);
  }
}

void bubbleSort(int arr[], int cols, int rows) {
  int swapped;
  for (int i = 0; i < cols - 1; i++) {
    swapped = 0;
    for (int j = 0; j < cols - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        swap(&arr[j], &arr[j+1]);
        swapped = 1;
        render(arr, j+1, cols, rows);
        usleep(SLEEP);
      }
    }
    if (!swapped) {
      break;
    }
  }
}

int partition(int arr[], int low, int high, int cols, int rows) {
  int pivot = arr[high]; // Pivot element
  int i = low - 1; // Index of smaller element

  for (int j = low; j <= high - 1; j++) {
    if (arr[j] < pivot) {
      i++;
      swap(&arr[i], &arr[j]);
      render(arr, j, cols, rows);
      usleep(SLEEP);
    }
  }
  swap(&arr[i + 1], &arr[high]);
  render(arr, high, cols, rows);
  usleep(SLEEP);
  return (i + 1);
}

void quickSort(int arr[], int low, int high, int cols, int rows) {
  if (low < high) {
    int pi = partition(arr, low, high, cols, rows);
    quickSort(arr, low, pi - 1, cols, rows);
    quickSort(arr, pi + 1, high, cols, rows);
  }
}

void shellSort(int arr[], int cols, int rows) {
  for (int gap = cols/2; gap > 0; gap /= 2) {
    for (int i = gap; i < cols; i++){
      int temp = arr[i];
      int j;
      for (j = i; j >= gap && arr[j-gap] > temp; j -= gap) {
        arr[j] = arr[j-gap];
        render(arr, j, cols, rows);
        usleep(SLEEP);
      }
      arr[j] = temp;
      render(arr, j, cols, rows);
      usleep(SLEEP);
    }  
  }
}  
