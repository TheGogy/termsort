/* ANSI colour escape codes */
struct WinSize {
  int cols;
  int rows;
};

struct WinSize setupRender();
void handleExit(int signum);
void render(int arr[], int moved_element, int cols, int rows);

