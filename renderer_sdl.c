#include <SDL2/SDL.h>
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "renderer.h"

#define WIDTH 1600
#define HEIGHT 1000

struct WinSize ws = {.cols = WIDTH, .rows = HEIGHT};

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Event event;

struct WinSize setupRender(int col_swap, int col_end, int delay_ms, int delay_finished_ms){
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  // Create window
  window = SDL_CreateWindow("Sorting Visualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  // Create renderer
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  while (SDL_PollEvent(&event) != 0) {
    if (event.type == SDL_QUIT) {
      handleExit(1);
    }
  }

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
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
  SDL_RenderClear(renderer);
  SDL_Rect bar;
  for (int i = 0; i < WIDTH; i++) {
    bar.x = i;
    bar.y = HEIGHT - arr[i];
    bar.w = 1;
    bar.h = arr[i];
    if (i == x || i == y){
      SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    } else {
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }
    SDL_RenderFillRect(renderer, &bar);
  }
  SDL_RenderPresent(renderer);
  SDL_Delay(1);
}

void renderSorted(int arr[]) {
  SDL_Rect bar;
  for (int i = 0; i < WIDTH; i++) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);
    for (int j = 0; j < WIDTH; j++) {
      bar.x = j;
      bar.y = HEIGHT - arr[j];
      bar.w = 1;
      bar.h = arr[j];
      if (i >= j){
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
      } else {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      }
      SDL_RenderFillRect(renderer, &bar);
    }
    SDL_RenderPresent(renderer);
    SDL_Delay(1);
  }
}
