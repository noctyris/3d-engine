#include "sdlapp.hpp"
#include <SDL3/SDL_render.h>

SDLApp::SDLApp(const std::string& title, int width, int height) : W(width), H(height) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    Logger::error("SDL_Init failed", SDL_GetError());
    m_running = false;
    return;
  }

  m_window = SDL_CreateWindow(title.c_str(), width, height, 0);
  if (!m_window) {
    Logger::error("SDL_CreateWindow failed", SDL_GetError());
    m_running = false;
    return;
  }

  m_renderer = SDL_CreateRenderer(m_window, NULL);
  if (!m_renderer) {
    Logger::error("SDL_CreateRenderer failed", SDL_GetError());
    m_running = false;
    return;
  }
}

SDLApp::~SDLApp() {
  if (m_renderer) SDL_DestroyRenderer(m_renderer);
  if (m_window) SDL_DestroyWindow(m_window);
  SDL_Quit();
}

void SDLApp::pollEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_EVENT_QUIT) {
      m_running = false;
    }
  }
}

void SDLApp::setDrawColor(const Color& color) {
  SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
}

void SDLApp::clear(const Color& color) {
  setDrawColor(color);
  SDL_RenderClear(m_renderer);
}

void SDLApp::draw_line(Vec2 pos1, Vec2 pos2, const Color& color) {
  setDrawColor(color);
  SDL_RenderLine(m_renderer, (float)pos1.x, (float)pos1.y, (float)pos2.x, (float)pos2.y);
}

void SDLApp::fill_triangle(Vec2 pos1, Vec2 pos2, Vec2 pos3, const Color& color) {
  auto Vec2_to_SDL_FPoint = [&](Vec2 point) { return SDL_FPoint{ point.x, point.y }; };

  SDL_FColor col = { color.r/255.0f, color.g/255.0f, color.b/255.0f, color.a/255.0f };
  SDL_Vertex points[3] = {
    { Vec2_to_SDL_FPoint(pos1), col, {0,0} },
    { Vec2_to_SDL_FPoint(pos2), col, {0,0} },
    { Vec2_to_SDL_FPoint(pos3), col, {0,0} },
  };
  SDL_RenderGeometry(m_renderer, NULL, points, 3, NULL, 0);
}

void SDLApp::present() {
  SDL_Delay(1000/FPS);
  SDL_RenderPresent(m_renderer);
}
