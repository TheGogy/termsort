/* ANSI colour escape codes */
struct WinSize {
  int cols;
  int rows;
};

struct WinSize setupRender(int col_swap, int col_end, int delay_ms, int delay_finished_ms);
void handleExit(int signum);
void render(int arr[], int x, int y);
void renderSorted(int arr[]);

