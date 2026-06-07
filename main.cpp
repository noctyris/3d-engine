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

  int indexes[36] = { 0,2,4, 0,1,2, 0,4,1, 6,4,2, 6,2,7, 6,7,4, 5,1,4, 5,4,7, 5,7,1, 3,2,1, 3,1,7, 3,7,2 };
  Mesh mesh, mesh2;
  for (int i = 0; i < 36; i++) {
    if (i < 8) {
      mesh.vertices.push_back(Vec4(i<4 ? -1 : 1, ((int)(i/2))%2==0 ? -1 : 1, i%2==0 ? -1 : 1));
      mesh2.vertices.push_back(Vec4(i<4 ? -1 : 1, ((int)(i/2))%2==0 ? -1 : 1, i%2==0 ? -1 : 1));
    }
    mesh.indexes.push_back(indexes[i]);
    mesh2.indexes.push_back(indexes[i]);
  }
  mesh.color = Color(255, 0, 0); mesh.position = Vec4(2,0,0); mesh.rotation = Vec4(0, 0, 0); mesh.scale = Vec4(1, 1, 1);
  mesh2.color = Color(0, 255, 0); mesh2.position = Vec4(0,0,0); mesh2.rotation = Vec4(0, 0, 0); mesh2.scale = Vec4(1, 1, 1);

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
    comp_matrix = camera.projection_matrix * camera.view_matrix;
    
    mesh2.rotation.y+=M_PI/180;
    
    sdl.draw_mesh(mesh, comp_matrix, {camera.zn, camera.zf}, camera.position);
    sdl.draw_mesh(mesh2, comp_matrix, {camera.zn, camera.zf}, camera.position);

    sdl.present();
  }

  return 0;
}
