/* The actual sorting algorithms of the project */

/*
 * algorithms ----------
 *
 * bogosort
 * bubble sort
 * quicksort
 * shellsort
 * mergesort
 * heapsort
 * gnomesort
 * cocktailsort
 * insertionsort
 * selectionsort
 * oddevensort
 */


#include "sorting.h"
#include "arrayutils.h"
#include "renderer.h"

#define SLEEP 15000

struct Counter bogoSort(int arr[], int cols, int rows) {
  struct Counter c;
  c.indexes = 0;
  c.moves= 0;
  int moved_element;
  while(!isSorted(arr, cols)) {
    moved_element = isSorted(arr, cols);
    shuffleArray(arr, cols);
    c.moves += cols;
    c.indexes += cols;
    render(arr, moved_element, cols, rows);
    usleep(SLEEP);
  }
  return c;
}

struct Counter bubbleSort(int arr[], int cols, int rows) {
  struct Counter c;
  c.indexes = 0;
  c.moves= 0;
  int swapped;
  for (int i = 0; i < cols - 1; i++) {
    swapped = 0;
    for (int j = 0; j < cols - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        swap(&arr[j], &arr[j+1]);
        c.moves++;
        swapped = 1;
        render(arr, j+1, cols, rows);
        usleep(SLEEP);
      }
      c.indexes++;
    }
    if (!swapped) {
      break;
    }
  }
  return c;
}

struct PartitionCounter {
  int i;
  struct Counter c;
};

struct PartitionCounter partition(int arr[], int low, int high, int cols, int rows) {
  struct Counter c;
  struct PartitionCounter pc;
  c.indexes = 0;
  c.moves= 0;


  int pivot = arr[high]; // Pivot element
  int i = low - 1; // Index of smaller element

  for (int j = low; j <= high - 1; j++) {
    if (arr[j] < pivot) {
      i++;
      swap(&arr[i], &arr[j]);
      c.moves++;
      render(arr, j, cols, rows);
      usleep(SLEEP);
    }
    c.indexes++;
  }
  swap(&arr[i + 1], &arr[high]);
  c.moves++;
  render(arr, high, cols, rows);
  usleep(SLEEP);
  pc.i = i;
  pc.c = c;
  return pc;
}

struct Counter quickSort(int arr[], int low, int high, int cols, int rows) {
  struct Counter c;
  c.indexes = 0;
  c.moves = 0;
  if (low < high) {
    struct PartitionCounter pc = partition(arr, low, high, cols, rows);
    struct Counter tmp;
    tmp = quickSort(arr, low, pc.i - 1, cols, rows);
    c.indexes += tmp.indexes; c.moves += tmp.moves;
    tmp = quickSort(arr, pc.i + 1, high, cols, rows);
    c.indexes += tmp.indexes; c.moves += tmp.moves;
  }
  return c;
}

struct Counter shellSort(int arr[], int cols, int rows) {
  struct Counter c;
  c.indexes = 0;
  c.moves = 0;
  for (int gap = cols/2; gap > 0; gap /= 2) {
    for (int i = gap; i < cols; i++){
      int temp = arr[i];
      c.indexes++;
      int j;
      for (j = i; j >= gap && arr[j-gap] > temp; j -= gap) {
        arr[j] = arr[j-gap];
        c.moves++;
        render(arr, j, cols, rows);
        usleep(SLEEP);
      }
      arr[j] = temp;
      c.moves++;
      render(arr, j, cols, rows);
      usleep(SLEEP);
    }  
  }
  return c;
}


struct Counter merge(int arr[], int low, int mid, int high, int cols, int rows) {
  struct Counter c;
  c.indexes = 0;
  c.moves = 0;
  int n1 = mid - low + 1;
  int n2 = high - mid;

  // Create temporary arrays
  int L[n1], R[n2];

  // Copy data to temporary arrays L[] and R[]
  for (int i = 0; i < n1; i++)
    L[i] = arr[low + i];
  c.indexes += n1;
  for (int j = 0; j < n2; j++)
    R[j] = arr[mid + 1 + j];
  c.indexes += n2;

  int i = 0;
  int j = 0;
  int k = low;

  while (i < n1 && j < n2) {
    c.indexes++;
    if (L[i] <= R[j]) {
      arr[k] = L[i];
      c.moves++;
      i++;
    } else {
      arr[k] = R[j];
      c.moves++;
      j++;
    }
    render(arr, k, cols, rows);
    usleep(SLEEP);
    k++;
  }

  while (i < n1) {
    arr[k] = L[i];
    c.moves++;
    render(arr, k, cols, rows);
    usleep(SLEEP);
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = R[j];
    render(arr, k, cols, rows);
    usleep(SLEEP);
    j++;
    k++;
  }
  return c;
}

struct Counter mergeSort(int arr[], int low, int high, int cols, int rows) {
  struct Counter c;
  c.indexes = 0;
  c.moves = 0;
  if (low >= high)
    return c;

  int mid = low + (high - low) / 2;
  struct Counter tmp;
  tmp = mergeSort(arr, low, mid, cols, rows);
  c.indexes += tmp.indexes; c.moves += tmp.moves;
  tmp = mergeSort(arr, mid + 1, high, cols, rows);
  c.indexes += tmp.indexes; c.moves += tmp.moves;
  tmp = merge(arr, low, mid, high, cols, rows);
  c.indexes += tmp.indexes; c.moves += tmp.moves;
  return c;
}

struct Counter heapify(int arr[], int i, int cols, int rows) {
  struct Counter c;
  c.indexes = 0;
  c.moves = 0;

  int largest = i;
  int l = 2 * i + 1;
  int r = 2 * i + 2;

  if (l < cols && arr[l] > arr[largest]) {
    largest = l;
  }
  c.indexes += 2;

  if (r < cols && arr[r] > arr[largest]) {
    largest = r;
  }
  c.indexes += 2;

  if (largest != i) {
    swap(&arr[i], &arr[largest]);
    c.moves++;
    struct Counter tmp;
    tmp = heapify(arr, largest, cols, rows);
    c.indexes += tmp.indexes; c.moves += tmp.moves;
  }
  return c;
}

struct Counter heapSort(int arr[], int cols, int rows){
  struct Counter c;
  c.indexes = 0;
  c.moves = 0;
  for (int i = cols / 2 - 1; i >= 0; i--) {
    struct Counter tmp;
    tmp = heapify(arr, i, cols, rows);
    c.indexes += tmp.indexes; c.moves += tmp.moves;
  }
  for (int i = cols - 1; i > 0; i--) {
    swap(&arr[0], &arr[i]);
    c.moves++;
    /* Call render twice; otherwise this runs too quickly */
    render(arr, 0, cols, rows);
    usleep(SLEEP);
    render(arr, i, cols, rows);
    usleep(SLEEP);
    struct Counter tmp;
    tmp = heapify(arr, 0, i, rows);
    c.moves += tmp.moves; c.indexes += tmp.indexes;
  }
  return c;
}

struct Counter gnomeSort(int arr[], int cols, int rows){
  struct Counter c;
  c.indexes = 0;
  c.moves = 0;
  int i = 0;
  while (i < cols) {
    if (i == 0) {
      i++;
    }
    c.indexes++;
    if (arr[i] >= arr[i-1]) {
      i++;
    } else {
      swap(&arr[i], &arr[i-1]);
      c.moves++;
      render(arr, i, cols, rows);
      usleep(SLEEP);
      i--;
    }
  }
  return c;
}

struct Counter cocktailSort(int arr[], int cols, int rows) {
  struct Counter c;
  c.indexes = 0;
  c.moves = 0;
  int start = 0;
  int end = cols - 1;
  int swapped = 1;

  while (swapped) {
    swapped = 0;
    for (int i = start; i < end; i++) {
      if (arr[i] > arr[i + 1]) {
        swap(&arr[i], &arr[i + 1]);
        c.moves++;
        render(arr, i, cols, rows);
        usleep(SLEEP);
        swapped = 1;
      }
      c.indexes++;
    }
    if (!swapped) break;
    end--;
    for (int i = end - 1; i >= start; i--) {
      if (arr[i] > arr[i + 1]) {
        swap(&arr[i], &arr[i + 1]);
        c.moves++;
        render(arr, i, cols, rows);
        usleep(SLEEP);
        swapped = 1;
      }
      c.indexes++;
    }
    start++;
  }
  return c;
}

struct Counter insertionSort(int arr[], int cols, int rows) {
  struct Counter c;
  c.indexes = 0;
  c.moves = 0;
  int i, j;
  for (i = 1; i < cols; i++) {
    int key = arr[i];
    c.indexes++;
    j = i - 1;
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      c.moves++;
      j = j - 1;
    }
    arr[j + 1] = key;
    c.moves++;

    render(arr, i, cols, rows);
    usleep(SLEEP);
  }
  return c;
}

struct Counter selectionSort(int arr[], int cols, int rows) {
  struct Counter c;
  c.indexes = 0;
  c.moves = 0;
  int i, j, min_idx;

  for (i = 0; i < cols - 1; i++) {
    min_idx = i;
    for (j = i + 1; j < cols; j++) {
      if (arr[j] < arr[min_idx]) {
        min_idx = j;
      }
      c.indexes++;
    }
    if (min_idx != i) {
      swap(&arr[min_idx], &arr[i]);
      c.moves++;
      render(arr, i, cols, rows);
      usleep(SLEEP);
    }
  }
  return c;
}

struct Counter oddevenSort(int arr[], int cols, int rows) {
  struct Counter c;
  c.indexes = 0;
  c.moves = 0;
  int sorted = 0;
  while (!sorted) {
    sorted = 1;
    for (int i = 1; i < cols - 1; i += 2) {
      if (arr[i] > arr[i+1]) {
        swap(&arr[i], &arr[i+1]);
        c.moves++;
        sorted = 0;
        render(arr, i, cols, rows);
        usleep(SLEEP);
      }
      c.indexes++;
    }
    for (int i = 0; i < cols - 1; i += 2) {
      if (arr[i] > arr[i+1]) {
        swap(&arr[i], &arr[i+1]);
        c.moves++;
        sorted = 0;
        render(arr, i, cols, rows);
        usleep(SLEEP);
      }
      c.indexes++;
    }
  }
  return c;
}

int flip(int arr[], int i, int cols, int rows) {
  int moves = 0;
  int start = 0;
  while (start < i) {
    swap(&arr[start], &arr[i]);
    moves++;
    render(arr, i, cols, rows);
    usleep(SLEEP);
    start++;
    i--;
  }
  return moves;
}

struct Counter pancakeSort(int arr[], int cols, int rows) {
  struct Counter c;
  c.indexes = 0;
  c.moves = 0;

  int currSize = cols;
  while (currSize > 1) {
    int maxIndex = 0;
    for (int i = 0; i < currSize; i++) {
      if (arr[i] > arr[maxIndex]){
        maxIndex = i;
      }
      c.indexes += 2;
    }
    if (maxIndex != currSize - 1) {
      int tmp;
      tmp = flip(arr, maxIndex, cols, rows);
      c.moves += tmp;
      tmp = flip(arr, currSize - 1, cols, rows);
      c.moves += tmp;
    }
    currSize--;
  }
  return c;
}

struct Counter pigeonholeSort(int arr[], int cols, int rows) {
  struct Counter c;
  c.moves = 0;
  c.indexes = 0;
  int min = arr[0], max = arr[0];
  int i, range, index;

  for (i = 1; i < cols; i++) {
    if (arr[i] < min) {
      min = arr[i];
    }
    if (arr[i] > max) {
      max = arr[i];
    }
    c.indexes ++;
  }
  range = max - min + 1;

  int holes[range];
  for (i = 0; i < range; i++) {
    holes[i] = 0;
  } // Not counting this, this just sets holes values to 0

  for (i = 0; i < cols; i++) {
    holes[arr[i] - min]++;
  }
  c.indexes += (cols * 2); // Each loop has 2 accesses

  index = 0;
  for (i = 0; i < range; i++) {
    while (holes[i] > 0) {
      arr[index++] = i + min;
      render(arr, index, cols, rows);
      usleep(SLEEP);
      holes[i]--;
      c.indexes += 2; // holes[i] and arr[index]
    }
  }
  return c;
}

int getNextGap(int gap){
  // Shrink by shrink factor
  gap = (gap * 10) / 13;
  if (gap < 1){
    return 1;
  }
  return gap;
}

struct Counter combSort(int arr[], int cols, int rows) {
  struct Counter c;
  c.moves = 0;
  c.indexes = 0;

  int gap = cols;
  int swapped = 1;
  while (gap != 1 || swapped) {
    gap = getNextGap(gap);
    swapped = 0;
    for (int i = 0; i < cols - gap; i++) {
      if (arr[i] > arr[i+gap]) {
        swap(&arr[i], &arr[i+gap]);
        c.moves++;
        render(arr, i, cols, rows);
        usleep(SLEEP);
        swapped = 1;
      }
      c.indexes++;
    }
  }
  return c;
}

struct Counter stoogeSort(int arr[], int low, int high, int cols, int rows) {
  struct Counter c;
  c.moves = 0;
  c.indexes = 0;

  if (low >= high){
    return c;
  }
  if (arr[low] > arr[high]){
    swap(&arr[low], &arr[high]);
    c.moves++;
    render(arr, high, cols, rows);
    usleep(SLEEP);
  }
  c.indexes++;

  if (high - low + 1 > 2) {
    int t = (high - low + 1) / 3;
    struct Counter tmp;
    tmp = stoogeSort(arr, low, high-t, cols, rows);
    c.indexes += tmp.indexes; c.moves += tmp.moves;
    tmp = stoogeSort(arr, low+t, high, cols, rows);
    c.indexes += tmp.indexes; c.moves += tmp.moves;
    tmp = stoogeSort(arr, low, high-t, cols, rows);
    c.indexes += tmp.indexes; c.moves += tmp.moves;
  }
  return c;
}

