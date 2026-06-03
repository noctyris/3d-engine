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

  Camera camera(Vec4(6, 2, 3), Vec4(0, 0, 0), radians(70.f), {0.1, 1000}, DIMS);
  camera.gen_projection_matrix();
  camera.gen_view_matrix();

  Vec4 vs[8];
  for (int i = 0; i < 8; i++) {
    vs[i] = Vec4(i<4 ? -1 : 1, ((int)(i/2))%2==0 ? -1 : 1, i%2==0 ? -1 : 1);
  }
  
  Triangle faces[12];
  faces[0]  = Triangle(vs[0], vs[2], vs[4]);
  faces[1]  = Triangle(vs[0], vs[1], vs[2]);
  faces[2]  = Triangle(vs[0], vs[4], vs[1]);
  faces[3]  = Triangle(vs[6], vs[4], vs[2]);
  faces[4]  = Triangle(vs[6], vs[2], vs[7]);
  faces[5]  = Triangle(vs[6], vs[7], vs[4]);
  faces[6]  = Triangle(vs[5], vs[1], vs[4]);
  faces[7]  = Triangle(vs[5], vs[4], vs[7]);
  faces[8]  = Triangle(vs[5], vs[7], vs[1]);
  faces[9]  = Triangle(vs[3], vs[2], vs[1]);
  faces[10] = Triangle(vs[3], vs[1], vs[7]);
  faces[11] = Triangle(vs[3], vs[7], vs[2]);

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
    
    for (int i = 0; i < 12; i++) sdl.draw_triangle(faces[i], comp_matrix);

    sdl.present();
  }

  return 0;
}
