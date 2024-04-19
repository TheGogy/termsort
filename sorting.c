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
 * pancakesort
 * pigeonholesort
 * combsort
 * stoogesort
 * badsort
 * dropsort
 */


#include "sorting.h"
#include "arrayutils.h"
#include "renderer.h"

#define SLEEP 15000

struct Counter bogoSort(int arr[], int cols, int rows) {
  struct Counter c = {.moves = 0, .indexes = 0};
  int moved_element = 0;
  while(moved_element != -1) {
    moved_element = isSorted(arr, cols);
    shuffleArray(arr, cols);
    c.moves += cols;
    c.indexes += cols;
    render(arr, moved_element, moved_element, cols, rows);
  }
  return c;
}

struct Counter bubbleSort(int arr[], int cols, int rows) {
  struct Counter c = {.moves = 0, .indexes = 0};
  int swapped;
  for (int i = 0; i < cols - 1; i++) {
    swapped = 0;
    for (int j = 0; j < cols - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        swap(&arr[j], &arr[j+1]);
        c.moves++;
        swapped = 1;
        render(arr, j, j+1, cols, rows);
      }
      c.indexes++;
    }
    if (!swapped) {
      break;
    }
  }
  return c;
}

int partition(int arr[], int low, int high, int cols, int rows, struct Counter *c) {
  int pivot = arr[low]; 
  int i = low; 
  int j = high; 

  while (i < j) { 
    while (arr[i] <= pivot && i <= high - 1) { 
      c->indexes++;
      i++; 
    } 
    while (arr[j] > pivot && j >= low + 1) { 
      c->indexes++;
      j--; 
    } 
    if (i < j) { 
      swap(&arr[i], &arr[j]); 
      render(arr, i, j, cols, rows);
      c->moves++;
    } 
  } 
  swap(&arr[low], &arr[j]); 
  render(arr, low, j, cols, rows);
  c->moves++;
  return j; 
} 

void quickSort(int arr[], int low, int high, int cols, int rows, struct Counter *c) {
  if (low < high) {
    int i = partition(arr, low, high, cols, rows, c);
    quickSort(arr, low, i - 1, cols, rows, c);
    quickSort(arr, i + 1, high, cols, rows, c);
  }
}

struct Counter quickSortWrapper(int arr[], int cols, int rows) {
  struct Counter c = {.moves = 0, .indexes = 0};
  quickSort(arr, 0, cols - 1, cols, rows, &c);
  return c;
}

struct Counter shellSort(int arr[], int cols, int rows) {
  struct Counter c = {.moves = 0, .indexes = 0};
  for (int gap = cols/2; gap > 0; gap /= 2) {
    for (int i = gap; i < cols; i++){
      int temp = arr[i];
      c.indexes++;
      int j;
      for (j = i; j >= gap && arr[j-gap] > temp; j -= gap) {
        arr[j] = arr[j-gap];
        c.moves++;
        render(arr, j, j-gap, cols, rows);
      }
      arr[j] = temp;
      c.moves++;
      render(arr, j, j, cols, rows);
    }  
  }
  return c;
}


struct Counter merge(int arr[], int low, int mid, int high, int cols, int rows) {
  struct Counter c = {.moves = 0, .indexes = 0};
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
      render(arr, k, i, cols, rows);
      c.moves++;
      i++;
    } else {
      arr[k] = R[j];
      render(arr, k, j, cols, rows);
      c.moves++;
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = L[i];
    c.moves++;
    render(arr, k, i, cols, rows);
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = R[j];
    render(arr, k, j, cols, rows);
    j++;
    k++;
  }
  return c;
}

struct Counter mergeSort(int arr[], int low, int high, int cols, int rows) {
  struct Counter c = {.moves = 0, .indexes = 0};
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
  struct Counter c = {.moves = 0, .indexes = 0};

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
  struct Counter c = {.moves = 0, .indexes = 0};
  for (int i = cols / 2 - 1; i >= 0; i--) {
    struct Counter tmp;
    tmp = heapify(arr, i, cols, rows);
    c.indexes += tmp.indexes; c.moves += tmp.moves;
  }
  for (int i = cols - 1; i > 0; i--) {
    swap(&arr[0], &arr[i]);
    c.moves++;
    render(arr, 0, i, cols, rows);
    struct Counter tmp;
    tmp = heapify(arr, 0, i, rows);
    c.moves += tmp.moves; c.indexes += tmp.indexes;
  }
  return c;
}

struct Counter gnomeSort(int arr[], int cols, int rows){
  struct Counter c = {.moves = 0, .indexes = 0};
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
      render(arr, i, i-1, cols, rows);
      i--;
    }
  }
  return c;
}

struct Counter cocktailSort(int arr[], int cols, int rows) {
  struct Counter c = {.moves = 0, .indexes = 0};
  int start = 0;
  int end = cols - 1;
  int swapped = 1;

  while (swapped) {
    swapped = 0;
    for (int i = start; i < end; i++) {
      if (arr[i] > arr[i + 1]) {
        swap(&arr[i], &arr[i + 1]);
        c.moves++;
        render(arr, i, i+1, cols, rows);
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
        render(arr, i, i+1, cols, rows);
        swapped = 1;
      }
      c.indexes++;
    }
    start++;
  }
  return c;
}

struct Counter insertionSort(int arr[], int cols, int rows) {
  struct Counter c = {.moves = 0, .indexes = 0};
  int i, j;
  for (i = 1; i < cols; i++) {
    int key = arr[i];
    c.indexes++;
    j = i - 1;
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      render(arr, j+1, j, cols, rows);
      c.moves++;
      c.indexes++;
      j = j - 1;
    }
    render(arr, j+1, j+1, cols, rows);
    arr[j + 1] = key;
    c.moves++;
  }
  return c;
}

struct Counter selectionSort(int arr[], int cols, int rows) {
  struct Counter c = {.moves = 0, .indexes = 0};
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
      render(arr, min_idx, i, cols, rows);
      c.moves++;
    }
  }
  return c;
}

struct Counter oddevenSort(int arr[], int cols, int rows) {
  struct Counter c = {.moves = 0, .indexes = 0};
  int sorted = 0;
  while (!sorted) {
    sorted = 1;
    for (int i = 1; i < cols - 1; i += 2) {
      if (arr[i] > arr[i+1]) {
        swap(&arr[i], &arr[i+1]);
        c.moves++;
        sorted = 0;
        render(arr, i, i+1, cols, rows);
      }
      c.indexes++;
    }
    for (int i = 0; i < cols - 1; i += 2) {
      if (arr[i] > arr[i+1]) {
        swap(&arr[i], &arr[i+1]);
        c.moves++;
        sorted = 0;
        render(arr, i, i+1, cols, rows);
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
    render(arr, start, i+1, cols, rows);
    start++;
    i--;
  }
  return moves;
}

struct Counter pancakeSort(int arr[], int cols, int rows) {
  struct Counter c = {.moves = 0, .indexes = 0};

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
  struct Counter c = {.moves = 0, .indexes = 0};
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
      c.moves++;
      render(arr, index, index, cols, rows);
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
  struct Counter c = {.moves = 0, .indexes = 0};

  int gap = cols;
  int swapped = 1;
  while (gap != 1 || swapped) {
    gap = getNextGap(gap);
    swapped = 0;
    for (int i = 0; i < cols - gap; i++) {
      if (arr[i] > arr[i+gap]) {
        swap(&arr[i], &arr[i+gap]);
        render(arr, i, i+gap, cols, rows);
        c.moves++;
        swapped = 1;
      }
      c.indexes++;
    }
  }
  return c;
}

struct Counter stoogeSort(int arr[], int low, int high, int cols, int rows) {
  struct Counter c = {.moves = 0, .indexes = 0};

  if (low >= high){
    return c;
  }
  if (arr[low] > arr[high]){
    swap(&arr[low], &arr[high]);
    c.moves++;
    render(arr, low, high, cols, rows);
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

void badSort(int arr[], int low, int high, int cols, int rows, struct Counter *c) {
  if (low >= high) return;

  int mid = (low + high) / 2;
  badSort(arr, low, mid, cols, rows, c);
  badSort(arr, mid+1, high, cols, rows, c);

  if (arr[mid] > arr[high]) {
    swap(&arr[mid], &arr[high]);
    c->moves++;
    render(arr, mid, high, cols, rows);
  }
  c->indexes++;

  badSort(arr, low, high-1, cols, rows, c);
}

struct Counter badSortWrapper(int arr[], int cols, int rows) {
  struct Counter c = {.moves = 0, .indexes = 0};
  badSort(arr, 0, cols-1, cols, rows, &c);
  return c;
}

struct Counter dropSort(int arr[], int cols, int rows) {
  struct Counter c = {.moves = 0, .indexes = 0};
  int max = 0; // All elements in array are > 0
  int max_idx = -1;
  
  for (int i = 0; i < cols; i++) {
    if (arr[i] < max) {
      arr[i] = 0;
      c.moves++;
    } else {
      max = arr[i];
      max_idx = i;
    }
    render(arr, max_idx, i, cols, rows);
  }
  c.indexes = cols;

  return c;
}
