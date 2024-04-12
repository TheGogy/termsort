#include <stdio.h>
#include "renderer.h"

/* Render each individual frame */
void render(int arr[], int arr_len, int block_size, int moved_element, int rows){
  for (int i = 0; i < rows; i++) {
    goToPos(i, 1); // Go to beginning of line
    for (int j = 0; j < arr_len; j++) {
      if (arr[j] >= rows - i){
        if (j == moved_element) {printf(ANSI_COLOR_RED);}
        for (int k = 0; k < block_size; k++) {
          printf("█");
        }
        if (j == moved_element) {printf(ANSI_COLOR_RESET);}
      } else {
        for (int k = 0; k < block_size; k++) {
          printf(" ");
        }
      }
    }
  }
  fflush(stdout); // Display frame immediately
}
