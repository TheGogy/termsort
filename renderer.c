#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>

#include "renderer.h"

struct WinSize setupRender(){
  setlocale(LC_ALL,"");
  initscr();            // Initialise ncurses
  cbreak();             // Disable line buffering
  noecho();             // Disable echoing user input
  use_default_colors();
  start_color();        // Initialise colour rendering
  init_pair(1, 1, -1);
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
}
