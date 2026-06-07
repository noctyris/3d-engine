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

  Camera camera(Vec4(6, 2, 3), Vec4(0, 0, 0), radians(70.f), {0.01, 1000}, DIMS);
  camera.gen_projection_matrix();
  camera.gen_view_matrix();

  Mesh mesh;
  if (mesh.load_from_obj("models/Untitled.obj")) std::cout << "OBJ imported\n";
  mesh.color = Color(200, 200, 200);
  mesh.scale = Vec4(1,1,1);

  std::cout << "Number of indexes:\t" << mesh.indexes.size() << "\n";
  std::cout << "Number of vertices:\t" << mesh.vertices.size() << "\n\n";

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

    mesh.rotation.y += M_PI/180;

    sdl.draw_mesh(mesh, comp_matrix, {camera.zn, camera.zf}, camera.position);

    sdl.present();
  }

  return 0;
}
