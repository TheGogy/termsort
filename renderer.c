#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "renderer.h"

struct WinSize setupRender(){
  setlocale(LC_ALL,"");
  initscr();            // Initialise ncurses
  cbreak();             // Disable line buffering
  noecho();             // Disable echoing user input
  curs_set(0);          // Hide cursor
  use_default_colors();
  start_color();        // Initialise colour rendering
  init_pair(1, 1, -1);
  init_pair(2, 2, -1);
  int max_x, max_y;
  getmaxyx(stdscr, max_y, max_x);
  struct WinSize ws = {
    max_x,
    max_y
  };
  return ws;
}

void handleExit(int signum) {
  clear();
  endwin();
  if (signum == 0){
    printf("Goodbye!\n");
  } else {
    printf("Exited with code %d\n", signum);
  }
  exit(0);
}

/* Render each individual frame */
void render(int arr[], int moved_element, int cols, int rows){
  clear(); // Clear screen
  int bar_length;
  for (int i = 0; i < cols; i++) {
    bar_length = arr[i];
    if (i == moved_element){ attron(COLOR_PAIR(1)); }
    mvvline(rows - bar_length, i, ACS_BOARD, bar_length);
    if (i == moved_element){ attroff(COLOR_PAIR(1)); }
  }
  refresh(); // Update screen

  // Sleep for 15 ms
  struct timespec delay;
  delay.tv_sec = 0;
  delay.tv_nsec = 15000000;
  nanosleep(&delay, NULL);
}

void renderSorted(int arr[], int cols, int rows) {
  struct timespec delay;
  delay.tv_sec = 0;
  delay.tv_nsec = 15000000;

  for (int i = 0; i < cols; i++) {
    clear(); // Clear screen
    int bar_length;
    attron(COLOR_PAIR(2));
    for (int j = 0; j < cols; j++) {
      bar_length = arr[j];
      mvvline(rows - bar_length, j, ACS_BOARD, bar_length);
      if (i == j){ attroff(COLOR_PAIR(2)); }
    }
    refresh(); // Update screen
    nanosleep(&delay, NULL);
  }
}
