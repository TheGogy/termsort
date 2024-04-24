struct WinSize {
  int cols;
  int rows;
};

struct RgbaColour {
  int r;
  int g;
  int b;
  int a;
};

struct WinSize setupRender(char *col_swap, char *col_end, int delay_ms, int delay_finished_ms);
void handleExit(int signum);
void render(int arr[], int x, int y);
void renderSorted(int arr[], char *results[], int results_len);

