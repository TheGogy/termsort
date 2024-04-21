#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "renderer.h"

struct timespec delay = {.tv_sec = 0};
struct timespec delay_finished = {.tv_sec = 0};

struct WinSize setupRender(int col_swap, int col_end, int delay_ms, int delay_finished_ms){

  // Set up like this so that delay can be more than 1000ms.
  // Not sure why people would want that but it's there.

  delay.tv_sec = (delay_ms / 1000);
  delay.tv_nsec = (delay_ms % 1000) * 1000000;
  delay_finished.tv_sec = (delay_finished_ms / 1000);
  delay_finished.tv_nsec = (delay_finished_ms % 1000)  * 1000000;
  setlocale(LC_ALL,"");
  initscr();            // Initialise ncurses
  cbreak();             // Disable line buffering
  noecho();             // Disable echoing user input
  curs_set(0);          // Hide cursor
  use_default_colors();
  start_color();        // Initialise colour rendering
  init_pair(1, col_swap, -1);
  init_pair(2, col_end, -1);
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
void render(int arr[], int x, int y, int cols, int rows){
  clear(); // Clear screen
  for (int i = 0; i < cols; i++) {
    if (i == x || i == y){ attron(COLOR_PAIR(1)); }
    mvvline(rows - arr[i], i, ACS_BOARD, arr[i]);
    if (i == x || i == y){ attroff(COLOR_PAIR(1)); }
  }
  refresh(); // Update screen
  nanosleep(&delay, NULL);
}

void renderSorted(int arr[], int cols, int rows) {

  for (int i = 0; i < cols; i++) {
    attron(COLOR_PAIR(2));
    mvvline(rows - arr[i], i, ACS_BOARD, arr[i]);
    attroff(COLOR_PAIR(2));
    refresh();
    nanosleep(&delay_finished, NULL);
  }
}
