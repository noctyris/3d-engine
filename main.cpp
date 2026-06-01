#include "engine.hpp"
#include "matrix.hpp"
#include "sdlapp.hpp"
#include <vector>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const std::pair<int, int> DIMS = {SCREEN_WIDTH, SCREEN_HEIGHT};

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

  Camera camera(Vec4(6, 2, 3, 1), Vec4(0, 0, 0, 1), radians(70.f), {0.1, 1000}, DIMS);
  camera.gen_projection_matrix();
  camera.gen_view_matrix();

  Mat comp_matrix;

  while (sdl.isRunning()) {
    sdl.pollEvents();

    sdl.clear(Color(0, 0, 0));
    
    camera.gen_view_matrix();
    comp_matrix = camera.projection_matrix * camera.view_matrix; // * M
    
    for (int i = 0; i < 8; i++) {
      for (int j = i+1; j < 8; j++) {
        sdl.drawLine(vectices[i].get_screen_position(comp_matrix, DIMS), vectices[j].get_screen_position(comp_matrix, DIMS), Color(255, 255, 255));
      }
    }

    sdl.present();
  }

  return 0;
}
