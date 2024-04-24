#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "renderer.h"
#include "arrayutils.h"

#define WIDTH 1600
#define HEIGHT 1000

struct WinSize ws = {.cols = WIDTH, .rows = HEIGHT};
struct RgbaColour backgroundColor = {.r = 0,    .g = 0,   .b = 0,   .a = 255};
struct RgbaColour barColor =        {.r = 255,  .g = 255, .b = 255, .a = 255};
struct RgbaColour swapColor =       {.r = 255,  .g = 0,   .b = 0,   .a = 255};
struct RgbaColour finishColor =     {.r = 0,    .g = 255, .b = 0,   .a = 255};

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Event event;

int delay;
int delay_finished;

void drawWindowWrapper(SDL_Renderer *renderer, struct RgbaColour c) {
  SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
}

struct WinSize setupRender(char *col_swap, char *col_end, int delay_ms, int delay_finished_ms){
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  // Create window
  window = SDL_CreateWindow("Sorting Visualizer", WIDTH, HEIGHT, 0);

  if (window == NULL) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  // Create renderer
  renderer = SDL_CreateRenderer(window, NULL, 0);
  if (renderer == NULL) {
    printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  delay = delay_ms; delay_finished = delay_finished_ms;
  return ws;
}

void handleExit(int signum) {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  if (signum == 0){
    printf("Goodbye!\n");
  } else {
    printf("Exited with code %d\n", signum);
  }
  exit(EXIT_SUCCESS);
}

/* Render each individual frame */
void render(int arr[], int x, int y){
  drawWindowWrapper(renderer, backgroundColor); // Black background
  SDL_RenderClear(renderer);
  SDL_FRect bar;
  for (int i = 0; i < WIDTH; i++) {
    bar.x = i;
    bar.y = HEIGHT - arr[i];
    bar.w = 1;
    bar.h = arr[i];
    if (i == x || i == y){
      drawWindowWrapper(renderer, swapColor);
    } else {
      drawWindowWrapper(renderer, barColor);
    }
    SDL_RenderFillRect(renderer, &bar);
  }
  SDL_RenderPresent(renderer);
  SDL_Delay(delay);
  while (SDL_PollEvent(&event) != 0) {
    if (event.type == SDL_EVENT_QUIT) {
      handleExit(1);
    }
  }
}

void renderSorted(int arr[], char *results[], int results_len) {
  SDL_FRect bar;
  for (int i = 0; i < WIDTH; i++) {
    drawWindowWrapper(renderer, backgroundColor);
    SDL_RenderClear(renderer);
    for (int j = 0; j < WIDTH; j++) {
      bar.x = j;
      bar.y = HEIGHT - arr[j];
      bar.w = 1;
      bar.h = arr[j];
      if (i >= j){
        drawWindowWrapper(renderer, finishColor);
      } else {
        drawWindowWrapper(renderer, barColor);
      }
      SDL_RenderFillRect(renderer, &bar);
    }
    SDL_RenderPresent(renderer);
    SDL_Delay(delay_finished);
    while (SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_EVENT_QUIT) {
        handleExit(1);
      }
    }
  }
  while(1) {
    while (SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_EVENT_QUIT || event.type == SDL_EVENT_KEY_DOWN) {
        handleExit(0);
      }
    }
  }
}
