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


void merge(int arr[], int low, int mid, int high, int cols, int rows) {
  int n1 = mid - low + 1;
  int n2 = high - mid;

  // Create temporary arrays
  int L[n1], R[n2];

  // Copy data to temporary arrays L[] and R[]
  for (int i = 0; i < n1; i++)
    L[i] = arr[low + i];
  for (int j = 0; j < n2; j++)
    R[j] = arr[mid + 1 + j];

  int i = 0;
  int j = 0;
  int k = low;

  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = R[j];
      j++;
    }
    render(arr, k, cols, rows);
    usleep(SLEEP);
    k++;
  }

  while (i < n1) {
    arr[k] = L[i];
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
}

void mergeSort(int arr[], int low, int high, int cols, int rows) {
  if (low >= high)
    return;

  int mid = low + (high - low) / 2;
  mergeSort(arr, low, mid, cols, rows);
  mergeSort(arr, mid + 1, high, cols, rows);
  merge(arr, low, mid, high, cols, rows);
}

void heapify(int arr[], int i, int cols, int rows) {
  int largest = i;
  int l = 2 * i + 1;
  int r = 2 * i + 2;

  if (l < cols && arr[l] > arr[largest]) {
    largest = l;
  }

  if (r < cols && arr[r] > arr[largest]) {
    largest = r;
  }

  if (largest != i) {
    swap(&arr[i], &arr[largest]);
    heapify(arr, largest, cols, rows);
  }
}

void heapSort(int arr[], int cols, int rows){
  for (int i = cols / 2 - 1; i >= 0; i--) {
    heapify(arr, i, cols, rows);
  }
  for (int i = cols - 1; i > 0; i--) {
    swap(&arr[0], &arr[i]);
    /* Call render twice; otherwise this runs too quickly */
    render(arr, 0, cols, rows);
    usleep(SLEEP);
    render(arr, i, cols, rows);
    usleep(SLEEP);
    heapify(arr, 0, i, rows);
  }
}

void gnomeSort(int arr[], int cols, int rows){
  int i = 0;
  while (i < cols) {
    if (i == 0) {
      i++;
    }
    if (arr[i] >= arr[i-1]) {
      i++;
    } else {
      swap(&arr[i], &arr[i-1]);
      render(arr, i, cols, rows);
      usleep(SLEEP);
      i--;
    }
  }
}

void cocktailSort(int arr[], int cols, int rows) {
  int start = 0;
  int end = cols - 1;
  int swapped = 1;

  while (swapped) {
    swapped = 0;
    for (int i = start; i < end; i++) {
      if (arr[i] > arr[i + 1]) {
        swap(&arr[i], &arr[i + 1]);
        render(arr, i, cols, rows);
        usleep(SLEEP);
        swapped = 1;
      }
    }
    if (!swapped) break;
    end--;
    for (int i = end - 1; i >= start; i--) {
      if (arr[i] > arr[i + 1]) {
        swap(&arr[i], &arr[i + 1]);
        render(arr, i, cols, rows);
        usleep(SLEEP);
        swapped = 1;
      }
    }
    start++;
  }
}

void insertionSort(int arr[], int cols, int rows) {
  int i, j;
  for (i = 1; i < cols; i++) {
    int key = arr[i];
    j = i - 1;
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j = j - 1;
    }
    arr[j + 1] = key;

    render(arr, i, cols, rows);
    usleep(SLEEP);
  }
}

void selectionSort(int arr[], int cols, int rows) {
  int i, j, min_idx;

  for (i = 0; i < cols - 1; i++) {
    min_idx = i;
    for (j = i + 1; j < cols; j++) {
      if (arr[j] < arr[min_idx]) {
        min_idx = j;
      }
    }
    if (min_idx != i) {
      swap(&arr[min_idx], &arr[i]);
      render(arr, i, cols, rows);
      usleep(SLEEP);
    }
  }
}

void oddevenSort(int arr[], int cols, int rows) {
  int sorted = 0;
  while (!sorted) {
    sorted = 1;
    for (int i = 1; i < cols - 1; i += 2) {
      if (arr[i] > arr[i+1]) {
        swap(&arr[i], &arr[i+1]);
        sorted = 0;
        render(arr, i, cols, rows);
        usleep(SLEEP);
      }
    }
    for (int i = 0; i < cols - 1; i += 2) {
      if (arr[i] > arr[i+1]) {
        swap(&arr[i], &arr[i+1]);
        sorted = 0;
        render(arr, i, cols, rows);
        usleep(SLEEP);
      }
    }
  }
}

void flip(int arr[], int i, int cols, int rows) {
  int start = 0;
  while (start < i) {
    swap(&arr[start], &arr[i]);
    render(arr, i, cols, rows);
    usleep(SLEEP);
    start++;
    i--;
  }
}

void pancakeSort(int arr[], int cols, int rows) {
  int currSize = cols;
  while (currSize > 1) {
    int maxIndex = 0;
    for (int i = 0; i < currSize; i++) {
      if (arr[i] > arr[maxIndex])
        maxIndex = i;
    }
    if (maxIndex != currSize - 1) {
      flip(arr, maxIndex, cols, rows);
      flip(arr, currSize - 1, cols, rows);
    }
    currSize--;
  }
}

void pigeonholeSort(int arr[], int cols, int rows) {
  int min = arr[0], max = arr[0];
  int i, j, range, index;

  for (i = 1; i < cols; i++) {
    if (arr[i] < min) {
      min = arr[i];
    }
    if (arr[i] > max) {
      max = arr[i];
    }
  }
  range = max - min + 1;

  int holes[range];
  for (i = 0; i < range; i++) {
    holes[i] = 0;
  }

  for (i = 0; i < cols; i++) {
    holes[arr[i] - min]++;
  }

  index = 0;
  for (i = 0; i < range; i++) {
    while (holes[i] > 0) {
      arr[index++] = i + min;
      render(arr, index, cols, rows);
      usleep(SLEEP);
      holes[i]--;
    }
  }
}

int getNextGap(int gap){
  // Shrink by shrink factor
  gap = (gap * 10) / 13;
  if (gap < 1){
    return 1;
  }
  return gap;
}

void combSort(int arr[], int cols, int rows) {
  int gap = cols;
  int swapped = 1;
  while (gap != 1 || swapped) {
    gap = getNextGap(gap);
    swapped = 0;
    for (int i = 0; i < cols - gap; i++) {
      if (arr[i] > arr[i+gap]) {
        swap(&arr[i], &arr[i+gap]);
        render(arr, i, cols, rows);
        usleep(SLEEP);
        swapped = 1;
      }
    }
  }
}

