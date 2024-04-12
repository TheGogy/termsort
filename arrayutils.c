#include <stdlib.h>
#include <time.h>

#include "arrayutils.h"

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
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
