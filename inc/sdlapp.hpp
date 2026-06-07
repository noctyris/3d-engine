#ifndef SDLAPP_HPP
#define SDLAPP_HPP

#define FPS 60

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_scancode.h>
#include <string>
#include "types.hpp"
#include "logger.hpp"

class Vec2f {
  public:
  float x, y;
  Vec2f(float x = 0, float y = 0) : x(x), y(y) {};
};

class SDLApp {
public:
  SDLApp(const std::string& title, int width, int height);
  ~SDLApp();

  // Prevent copying because of the raw pointers (RAII)
  SDLApp(const SDLApp&) = delete;
  SDLApp& operator=(const SDLApp&) = delete;

  bool isRunning() const { return m_running; };
  void pollEvents();
  void clear(const Color& color);
  void draw_line(Vec2 pos1, Vec2 pos2, const Color& color);
  void fill_triangle(Vec2 pos1, Vec2 pos2, Vec2 pos3, const Color& color);
  void present();
  SDL_Window* get_window() const { return m_window; };

private:
  int W, H;
  std::pair<int, int> DIMS;
  SDL_Window* m_window = nullptr;
  SDL_Renderer* m_renderer = nullptr;
  bool m_running = true;

  void setDrawColor(const Color& color);
};

#endif
