#include "engine.hpp"
#include "matrix.hpp"
#include "sdlapp.hpp"
#include <vector>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

int main() {
  SDLApp sdl("3D Engine C++", SCREEN_WIDTH, SCREEN_HEIGHT);

  // Vectices 
  std::vector<Vec4> vectices = {
    Vec4(-1, -1, -1, 1),
    Vec4(-1, -1,  1, 1),
    Vec4(-1,  1, -1, 1),
    Vec4(-1,  1,  1, 1),
    Vec4( 1, -1, -1, 1),
    Vec4( 1, -1,  1, 1),
    Vec4( 1,  1, -1, 1),
    Vec4( 1,  1,  1, 1)
  };

  Camera camera(Vec4(6, 2, 3, 1), Vec4(0, 0, 0, 1), 70.f, {0.1, 1000}, {SCREEN_WIDTH, SCREEN_HEIGHT});
  camera.gen_projection_matrix();
  camera.projection_matrix.print();
  return 0;

  while (sdl.isRunning()) {
    sdl.pollEvents();

    sdl.clear(Color(0, 0, 0));
    
    sdl.drawLine((Vec2){0, 0}, (Vec2){SCREEN_WIDTH, SCREEN_HEIGHT}, Color(255, 0, 0));

    sdl.present();
  }

  return 0;
}
