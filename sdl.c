#include "sdl.h"
#include "log.h"
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event event;

int sdl_init(char *title, int w, int h) {
  SDL_Init(SDL_INIT_VIDEO);

  window = SDL_CreateWindow(title, w, h, 0);
  if (window == NULL) {
    perrorf("SDL_CreateWindow: ", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  renderer = SDL_CreateRenderer(window, NULL);
  if (renderer == NULL) {
    perrorf("SDL_CreateRenderer Error: ", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  return 0;
}

void set_color(rgb_t color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
}

void sdl_clear(rgb_t color) {
  set_color(color);
  SDL_RenderClear(renderer);
}

void sdl_drawline(int x1, int y1, int x2, int y2, rgb_t color) {
  set_color(color);
  SDL_RenderLine(renderer, x1, y1, x2, y2);
}
