#ifndef SDL_H
#define SDL_H

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 800

#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include "log.h"

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Event event;

typedef struct {
  int r, g, b;
} rgb_t;

int sdl_init(char *title, int w, int h);
void set_color(rgb_t color);
void sdl_clear(rgb_t color);
void sdl_drawline(int x1, int y1, int x2, int y2, rgb_t color);

#endif
