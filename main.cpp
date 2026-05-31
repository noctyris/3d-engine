#include "sdlapp.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

int main() {
    SDLApp sdl("3D Engine C++", SCREEN_WIDTH, SCREEN_HEIGHT);

    while (sdl.isRunning()) {
        sdl.pollEvents();

        sdl.clear(Color(0, 0, 0));
        
        sdl.drawLine((Vec2){0, 0}, (Vec2){SCREEN_WIDTH, SCREEN_HEIGHT}, Color(255, 0, 0));

        sdl.present();
    }

    return 0;
}
