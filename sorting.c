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
 * radixsort
 * bozosort
 */

#include <stdlib.h>

#include "sorting.h"
#include "arrayutils.h"
#include "renderer.h"

#define SLEEP 15000

struct Counter bogoSort(int arr[], int n) {
  struct Counter c = {.moves = 0, .indexes = 0};
  int moved_element = 0;
  while(moved_element != -1) {
    moved_element = isSorted(arr, n);
    shuffleArray(arr, n);
    c.moves += n;
    c.indexes += n;
    render(arr, moved_element, moved_element);
  }
  return c;
}

struct Counter bubbleSort(int arr[], int n) {
  struct Counter c = {.moves = 0, .indexes = 0};
  int swapped;
  for (int i = 0; i < n - 1; i++) {
    swapped = 0;
    for (int j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        swap(&arr[j], &arr[j+1]);
        c.moves++;
        swapped = 1;
        render(arr, j, j+1);
      }
      c.indexes++;
    }
    if (!swapped) {
      break;
    }
  }
  return c;
}

int partition(int arr[], int low, int high, struct Counter *c) {
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
      render(arr, i, j);
      c->moves++;
    } 
  } 
  swap(&arr[low], &arr[j]); 
  render(arr, low, j);
  c->moves++;
  return j; 
} 

void quickSort(int arr[], int low, int high, int n, struct Counter *c) {
  if (low < high) {
    int i = partition(arr, low, high, c);
    quickSort(arr, low, i - 1, n, c);
    quickSort(arr, i + 1, high, n, c);
  }
}

struct Counter quickSortWrapper(int arr[], int n) {
  struct Counter c = {.moves = 0, .indexes = 0};
  quickSort(arr, 0, n - 1, n, &c);
  return c;
}

struct Counter shellSort(int arr[], int n) {
  struct Counter c = {.moves = 0, .indexes = 0};
  for (int gap = n/2; gap > 0; gap /= 2) {
    for (int i = gap; i < n; i++){
      int temp = arr[i];
      c.indexes++;
      int j;
      for (j = i; j >= gap && arr[j-gap] > temp; j -= gap) {
        arr[j] = arr[j-gap];
        c.moves++;
        render(arr, j, j-gap);
      }
      arr[j] = temp;
      c.moves++;
      render(arr, j, j);
    }  
  }
  return c;
}


struct Counter merge(int arr[], int low, int mid, int high) {
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
      render(arr, k, mid+i);
      c.moves++;
      i++;
    } else {
      arr[k] = R[j];
      render(arr, k, mid+j);
      c.moves++;
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = L[i];
    c.moves++;
    render(arr, k, mid+i);
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = R[j];
    render(arr, k, mid+j);
    j++;
    k++;
  }
  return c;
}

struct Counter mergeSort(int arr[], int low, int high, int n) {
  struct Counter c = {.moves = 0, .indexes = 0};
  if (low >= high)
    return c;

  int mid = low + (high - low) / 2;
  struct Counter tmp;
  tmp = mergeSort(arr, low, mid, n);
  c.indexes += tmp.indexes; c.moves += tmp.moves;
  tmp = mergeSort(arr, mid + 1, high, n);
  c.indexes += tmp.indexes; c.moves += tmp.moves;
  tmp = merge(arr, low, mid, high);
  c.indexes += tmp.indexes; c.moves += tmp.moves;
  return c;
}

struct Counter heapify(int arr[], int i, int n) {
  struct Counter c = {.moves = 0, .indexes = 0};

  int largest = i;
  int l = 2 * i + 1;
  int r = 2 * i + 2;

  if (l < n && arr[l] > arr[largest]) {
    largest = l;
  }
  c.indexes += 2;

  if (r < n && arr[r] > arr[largest]) {
    largest = r;
  }
  c.indexes += 2;

  if (largest != i) {
    swap(&arr[i], &arr[largest]);
    c.moves++;
    struct Counter tmp;
    tmp = heapify(arr, largest, n);
    c.indexes += tmp.indexes; c.moves += tmp.moves;
  }
  return c;
}

struct Counter heapSort(int arr[], int n){
  struct Counter c = {.moves = 0, .indexes = 0};
  for (int i = n / 2 - 1; i >= 0; i--) {
    struct Counter tmp;
    tmp = heapify(arr, i, n);
    c.indexes += tmp.indexes; c.moves += tmp.moves;
  }
  for (int i = n - 1; i > 0; i--) {
    swap(&arr[0], &arr[i]);
    c.moves++;
    render(arr, 0, i);
    struct Counter tmp;
    tmp = heapify(arr, 0, i);
    c.moves += tmp.moves; c.indexes += tmp.indexes;
  }
  return c;
}

struct Counter gnomeSort(int arr[], int n){
  struct Counter c = {.moves = 0, .indexes = 0};
  int i = 0;
  while (i < n) {
    if (i == 0) {
      i++;
    }
    c.indexes++;
    if (arr[i] >= arr[i-1]) {
      i++;
    } else {
      swap(&arr[i], &arr[i-1]);
      c.moves++;
      render(arr, i, i-1);
      i--;
    }
  }
  return c;
}

struct Counter cocktailSort(int arr[], int n) {
  struct Counter c = {.moves = 0, .indexes = 0};
  int start = 0;
  int end = n - 1;
  int swapped = 1;

  while (swapped) {
    swapped = 0;
    for (int i = start; i < end; i++) {
      if (arr[i] > arr[i + 1]) {
        swap(&arr[i], &arr[i + 1]);
        c.moves++;
        render(arr, i, i+1);
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
        render(arr, i, i+1);
        swapped = 1;
      }
      c.indexes++;
    }
    start++;
  }
  return c;
}

struct Counter insertionSort(int arr[], int n) {
  struct Counter c = {.moves = 0, .indexes = 0};
  int i, j;
  for (i = 1; i < n; i++) {
    int key = arr[i];
    c.indexes++;
    j = i - 1;
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      render(arr, j+1, j);
      c.moves++;
      c.indexes++;
      j = j - 1;
    }
    render(arr, j+1, j+1);
    arr[j + 1] = key;
    c.moves++;
  }
  return c;
}

struct Counter selectionSort(int arr[], int n) {
  struct Counter c = {.moves = 0, .indexes = 0};
  int i, j, min_idx;

  for (i = 0; i < n - 1; i++) {
    min_idx = i;
    for (j = i + 1; j < n; j++) {
      if (arr[j] < arr[min_idx]) {
        min_idx = j;
      }
      c.indexes++;
    }
    if (min_idx != i) {
      swap(&arr[min_idx], &arr[i]);
      render(arr, min_idx, i);
      c.moves++;
    }
  }
  return c;
}

struct Counter oddevenSort(int arr[], int n) {
  struct Counter c = {.moves = 0, .indexes = 0};
  int sorted = 0;
  while (!sorted) {
    sorted = 1;
    for (int i = 1; i < n - 1; i += 2) {
      if (arr[i] > arr[i+1]) {
        swap(&arr[i], &arr[i+1]);
        c.moves++;
        sorted = 0;
        render(arr, i, i+1);
      }
      c.indexes++;
    }
    for (int i = 0; i < n - 1; i += 2) {
      if (arr[i] > arr[i+1]) {
        swap(&arr[i], &arr[i+1]);
        c.moves++;
        sorted = 0;
        render(arr, i, i+1);
      }
      c.indexes++;
    }
  }
  return c;
}

int flip(int arr[], int i) {
  int moves = 0;
  int start = 0;
  while (start < i) {
    swap(&arr[start], &arr[i]);
    moves++;
    render(arr, start, i+1);
    start++;
    i--;
  }
  return moves;
}

struct Counter pancakeSort(int arr[], int n) {
  struct Counter c = {.moves = 0, .indexes = 0};

  int currSize = n;
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
      tmp = flip(arr, maxIndex);
      c.moves += tmp;
      tmp = flip(arr, currSize - 1);
      c.moves += tmp;
    }
    currSize--;
  }
  return c;
}

struct Counter pigeonholeSort(int arr[], int n) {
  struct Counter c = {.moves = 0, .indexes = 0};
  int min = arr[0], max = arr[0];
  int i, range, index;

  for (i = 1; i < n; i++) {
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

  for (i = 0; i < n; i++) {
    holes[arr[i] - min]++;
  }
  c.indexes += (n * 2); // Each loop has 2 accesses

  index = 0;
  for (i = 0; i < range; i++) {
    while (holes[i] > 0) {
      arr[index++] = i + min;
      c.moves++;
      render(arr, index, index);
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

struct Counter combSort(int arr[], int n) {
  struct Counter c = {.moves = 0, .indexes = 0};

  int gap = n;
  int swapped = 1;
  while (gap != 1 || swapped) {
    gap = getNextGap(gap);
    swapped = 0;
    for (int i = 0; i < n - gap; i++) {
      if (arr[i] > arr[i+gap]) {
        swap(&arr[i], &arr[i+gap]);
        render(arr, i, i+gap);
        c.moves++;
        swapped = 1;
      }
      c.indexes++;
    }
  }
  return c;
}

struct Counter stoogeSort(int arr[], int low, int high, int n) {
  struct Counter c = {.moves = 0, .indexes = 0};

  if (low >= high){
    return c;
  }
  if (arr[low] > arr[high]){
    swap(&arr[low], &arr[high]);
    c.moves++;
    render(arr, low, high);
  }
  c.indexes++;

  if (high - low + 1 > 2) {
    int t = (high - low + 1) / 3;
    struct Counter tmp;
    tmp = stoogeSort(arr, low, high-t, n);
    c.indexes += tmp.indexes; c.moves += tmp.moves;
    tmp = stoogeSort(arr, low+t, high, n);
    c.indexes += tmp.indexes; c.moves += tmp.moves;
    tmp = stoogeSort(arr, low, high-t, n);
    c.indexes += tmp.indexes; c.moves += tmp.moves;
  }
  return c;
}

void badSort(int arr[], int low, int high, int n, struct Counter *c) {
  if (low >= high) return;

  int mid = (low + high) / 2;
  badSort(arr, low, mid, n, c);
  badSort(arr, mid+1, high, n, c);

  if (arr[mid] > arr[high]) {
    swap(&arr[mid], &arr[high]);
    c->moves++;
    render(arr, mid, high);
  }
  c->indexes++;

  badSort(arr, low, high-1, n, c);
}

struct Counter badSortWrapper(int arr[], int n) {
  struct Counter c = {.moves = 0, .indexes = 0};
  badSort(arr, 0, n-1, n, &c);
  return c;
}

struct Counter dropSort(int arr[], int n) {
  struct Counter c = {.moves = 0, .indexes = 0};
  int max = 0; // All elements in array are > 0
  int max_idx = -1;
  
  for (int i = 0; i < n; i++) {
    if (arr[i] < max) {
      arr[i] = 0;
      c.moves++;
    } else {
      max = arr[i];
      max_idx = i;
    }
    render(arr, max_idx, i);
  }
  c.indexes = n;

  return c;
}

struct Counter radixSort(int arr[], int n) {
  struct Counter c = {.moves = 0, .indexes = 0};

  int digit = 1;
  int result[n];
  int largestNum = getMax(arr, n);

  while (largestNum/digit > 0) {
    int count[10] = {0};
    for (int i = 0; i < n; i++) {
      count[(arr[i]/digit) % 10]++;
    }
    c.indexes += n;
    
    for (int i = 1; i < 10; i++) {
      count[i] += count[i-1];
    } 
    c.indexes += 10;
    
    for (int i = n - 1; i >= 0; i--) {
      result[--count[(arr[i]/digit) % 10]] = arr[i];
    }
    c.indexes += n * 2;
    c.moves += n * 2;

    for (int i = 0; i < n; i++) {
      arr[i] = result[i];
      render(arr, i, i);
    }
    digit *= 10;
    c.indexes += n;
    c.moves += n;
  }
  
  return c;
}

struct Counter bozoSort(int arr[], int n) {
  struct Counter c = {.moves = 0, .indexes = 0};
  int x, y;
  while (isSorted(arr, n) != -1) {
    x = rand() % (n);
    y = rand() % (n);
    render(arr, x, y);
    if ((x < y) != (arr[x] < arr[y])) {
      swap(&arr[x], &arr[y]);
      c.moves++;
    }
    c.indexes += 2;

  }
  return c;
}

