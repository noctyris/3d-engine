#include "engine.hpp"
#include "matrix.hpp"
#include "sdlapp.hpp"
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_scancode.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const std::pair<int, int> DIMS = {SCREEN_WIDTH, SCREEN_HEIGHT};

int main() {
  SDLApp sdl("3D Engine C++", SCREEN_WIDTH, SCREEN_HEIGHT);
  SDL_SetWindowRelativeMouseMode(sdl.get_window(), true);

  Camera camera(Vec4(6, 2, 3, 1), Vec4(0, 0, 0, 1), radians(70.f), {0.1, 1000}, DIMS);
  camera.gen_projection_matrix();
  camera.gen_view_matrix();

  Triangle triangle(Vec4(0, 2, 0, 1), Vec4(2, 1, 0, 1), Vec4(0, 0, 3, 1), Color(255, 0, 0));

  float speed = 0.05f;

  Vec2f mouse;
  Mat comp_matrix;

  while (sdl.isRunning()) {
    sdl.pollEvents();
    int numkeys;
    const bool* state = SDL_GetKeyboardState(&numkeys);
    SDL_GetRelativeMouseState(&mouse.x, &mouse.y);

    if (mouse.x != 0 || mouse.y!=0) camera.rotate(mouse.x, mouse.y);
    if (state[SDL_SCANCODE_W]) camera.move_forward(speed);
    if (state[SDL_SCANCODE_S]) camera.move_forward(-speed);
    if (state[SDL_SCANCODE_A]) camera.move_sideways(-speed);
    if (state[SDL_SCANCODE_D]) camera.move_sideways(speed);
    if (state[SDL_SCANCODE_R]) camera.move_altitude(speed);
    if (state[SDL_SCANCODE_F]) camera.move_altitude(-speed);

    sdl.clear(Color(0, 0, 0));
    
    camera.gen_view_matrix();
    comp_matrix = camera.projection_matrix * camera.view_matrix; // * M
    
    sdl.draw_triangle(triangle, comp_matrix);

    sdl.present();
  }

  return 0;
}
