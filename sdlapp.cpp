#include "sdlapp.hpp"
#include "engine.hpp"
#include "logger.hpp"
#include <SDL3/SDL_timer.h>

SDLApp::SDLApp(const std::string& title, int width, int height) {
  W = width, H = height;
  DIMS = {W, H};
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

void SDLApp::present() {
  SDL_Delay(1000/FPS);
  SDL_RenderPresent(m_renderer);
}

void SDLApp::draw_triangle(Triangle tri, Mat comp_matrix) {
  Vec2 p1 = tri.v1.project(comp_matrix, DIMS);
  Vec2 p2 = tri.v2.project(comp_matrix, DIMS);
  Vec2 p3 = tri.v3.project(comp_matrix, DIMS);
  if (0 <= p1.x && p1.x <= DIMS.first && 0 <= p1.y && p1.y <= DIMS.second &&
      0 <= p2.x && p2.x <= DIMS.first && 0 <= p2.y && p2.y <= DIMS.second &&
      0 <= p3.x && p3.x <= DIMS.first && 0 <= p3.y && p3.y <= DIMS.second) {
    draw_line(p1, p2, tri.color);
    draw_line(p1, p3, tri.color);
    draw_line(p2, p3, tri.color);
  }
}
