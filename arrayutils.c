#include <stdlib.h>
#include <time.h>

#include "arrayutils.h"

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int isSorted(int arr[], int arr_len) {
  /* Returns index of the first element out of order
   * */
  for (int i = 0; i < arr_len-1; i++) {
    if (arr[i] > arr[i+1]) {
      return i;
    }
  }
  return -1;
}

int getMax(int arr[], int arr_len) {
  int max = arr[0];
  for (int i = 1; i < arr_len; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }
  return max;
}

void shuffleArray(int arr[], int arr_len) {
  srand(time(NULL)); // Seed the random number generator
  for (int i = arr_len - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    // Swap arr[i] and arr[j]
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }
}
