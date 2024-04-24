#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "renderer.h"
#include "arrayutils.h"

struct timespec delay = {.tv_sec = 0};
struct timespec delay_finished = {.tv_sec = 0};
struct WinSize ws;

struct WinSize setupRender(char *col_swap, char *col_end, int delay_ms, int delay_finished_ms){

  int col_swap_color = atoi(col_swap);
  int col_end_color = atoi(col_end);

  if (
    col_swap_color < 0 || col_swap_color > 255 || col_end_color < 0 || col_end_color > 255
  ) {
    printf("Should be a number between 0 and 255.");
    exit(EXIT_FAILURE);
  }

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
  
  init_pair(1, col_swap_color, -1);
  init_pair(2, col_end_color, -1);
  
  int max_x, max_y;
  getmaxyx(stdscr, max_y, max_x);
  ws.cols = max_x;
  ws.rows = max_y;
  return ws;
}

void handleExit(int signum) {
  clear();
  endwin();
  if (signum == 0){
    printf("Goodbye!\n");
    exit(EXIT_SUCCESS);
  } else {
    printf("Exited with code %d\n", signum);
    exit(signum);
  }
}

/* Render each individual frame */
void render(int arr[], int x, int y){
  clear(); // Clear screen
  for (int i = 0; i < ws.cols; i++) {
    if (i == x || i == y){ attron(COLOR_PAIR(1)); }
    mvvline(ws.rows - arr[i], i, ACS_BOARD, arr[i]);
    if (i == x || i == y){ attroff(COLOR_PAIR(1)); }
  }
  refresh(); // Update screen
  nanosleep(&delay, NULL);
}

void renderSorted(int arr[], char *results[], int results_len) {
  for (int i = 0; i < ws.cols; i++) {
    attron(COLOR_PAIR(2));
    mvvline(ws.rows - arr[i], i, ACS_BOARD, arr[i]);
    attroff(COLOR_PAIR(2));
    refresh();
    nanosleep(&delay_finished, NULL);
  }

  WINDOW *resultsWin = newwin(7, 25, 0, 0);
  wattron(resultsWin, A_BOLD);
  mvwprintw(resultsWin, 1, 1, "%s", results[0]);
  wattroff(resultsWin, A_BOLD);

  for (int i = 1; i < results_len; i++) {
    mvwprintw(resultsWin, i+1, 1, "%s\n", results[i]);
  }
  wattron(resultsWin, A_BOLD);
  box(resultsWin, 0, 0);
  wattroff(resultsWin, A_BOLD);
  wrefresh(resultsWin);
  getch(); // Wait for user input before exiting
}
