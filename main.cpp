#include "camera.hpp"
#include "light.hpp"
#include "mesh.hpp"
#include "sdlapp.hpp"
#include "types.hpp"
#include "vector.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const std::pair<int, int> DIMS = {SCREEN_WIDTH, SCREEN_HEIGHT};

int main(int argv, char* argc[]) {
  SDLApp sdl("3D Engine C++", SCREEN_WIDTH, SCREEN_HEIGHT);
  SDL_SetWindowRelativeMouseMode(sdl.get_window(), true);
  float speed = 0.05f;
  Vec2f mouse;

  Camera camera( Vec4(6, 2, 3, 1), Vec4(0, 0, 0, 1), 70.0f*M_PI/180, { 0.01f, 1000.0f }, DIMS );
  camera.gen_projection_matrix();

  Mesh mesh;
  mesh.load_from_obj(argc[1]);
  mesh.transform.set_scale(Vec4(.01,.01,.01));
  mesh.get_info();

  std::vector<Light*> lights;
  lights.push_back(new DirectionalLight(Vec4(1, -1, 1)));
  lights.push_back(new AmbientLight(Color(255, 255, 255), 0.1f));
  lights.push_back(new PointLight(Vec4(0, 5, 0), 20.0f, Color(255, 100, 100)));

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
    camera.gen_view_matrix();

    sdl.clear(Color(0, 0, 0));
    
    mesh.transform.rotate(Vec4(0,1,1/M_PI), M_PI/180);
    mesh.show(&sdl, camera, lights);

    sdl.present();
  }

  return 0;
}
