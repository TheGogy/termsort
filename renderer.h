/* ANSI colour escape codes */
struct WinSize {
  int cols;
  int rows;
};

struct WinSize setupRender(int col_swap, int col_end);
void handleExit(int signum);
void render(int arr[], int x, int y, int cols, int rows);
void renderSorted(int arr[], int cols, int rows);

