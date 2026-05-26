#include "sdl.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <stdbool.h>

int main() {
  sdl_init("3D Engine", SCREEN_WIDTH, SCREEN_HEIGHT);

  bool running = true;

  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        running = false;
      }
    }
    
    sdl_clear((rgb_t){0,0,0});
    
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
