#include "sdlapp.hpp"
#include "quaternions.hpp"
#include "vector.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const std::pair<int, int> DIMS = {SCREEN_WIDTH, SCREEN_HEIGHT};

int main() {
  SDLApp sdl("3D Engine C++", SCREEN_WIDTH, SCREEN_HEIGHT);
  SDL_SetWindowRelativeMouseMode(sdl.get_window(), true);

  //float speed = 0.05f;
  Vec2f mouse;

  while (sdl.isRunning()) {
    sdl.pollEvents();
    //int numkeys;
    //const bool* state = SDL_GetKeyboardState(&numkeys);
    SDL_GetRelativeMouseState(&mouse.x, &mouse.y);

    /*if (mouse.x != 0 || mouse.y!=0) camera.rotate(mouse.x, mouse.y);
    if (state[SDL_SCANCODE_W]) camera.move_forward(speed);
    if (state[SDL_SCANCODE_S]) camera.move_forward(-speed);
    if (state[SDL_SCANCODE_A]) camera.move_sideways(-speed);
    if (state[SDL_SCANCODE_D]) camera.move_sideways(speed);
    if (state[SDL_SCANCODE_R]) camera.move_altitude(speed);
    if (state[SDL_SCANCODE_F]) camera.move_altitude(-speed);*/

    sdl.clear(Color(0, 0, 0));
    


    sdl.present();
  }

  return 0;
}
