#include "sdlapp.hpp"
#include "engine.hpp"
#include "logger.hpp"
#include "matrix.hpp"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <cstddef>

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

void SDLApp::fill_triangle(Vec4 v1, Vec4 v2, Vec4 v3, Color c) {
  auto to_screen = [&](Vec4 p) {
    float inv_w = 1.0f / p.w;
    return SDL_FPoint{
      (p.x * inv_w + 1.0f) * 0.5f * W,
      (1.0f - (p.y * inv_w + 1.0f) * 0.5f) * H
    };
  };
  SDL_FColor col = { c.r / 255.0f, c.g / 255.0f, c.b / 255.0f, c.a / 255.0f };
  SDL_Vertex v[3] = {
    { to_screen(v1), col, {0,0} },
    { to_screen(v2), col, {0,0} },
    { to_screen(v3), col, {0,0} }
  };
  SDL_RenderGeometry(m_renderer, NULL, v, 3, NULL, 0);
}

void SDLApp::draw_face(Triangle tri, Mat comp_matrix, std::pair<float, float> z, Vec4 E) {
  float zn = z.first;

  Vec4 cp1 = comp_matrix * tri.v1;
  Vec4 cp2 = comp_matrix * tri.v2;
  Vec4 cp3 = comp_matrix * tri.v3;

  Vec4 N = cross((tri.v2-tri.v1), (tri.v3-tri.v1));
  Vec4 V_cam = (E-tri.v1).norm();
  if (dot(N, V_cam) <= 0) return;

  Vec4* inside[3];
  Vec4* outside[3];
  int n_inside = 0, n_ouside = 0;

  if (cp1.w >= zn) inside[n_inside++] = &cp1; else outside[n_ouside++] = &cp1;
  if (cp2.w >= zn) inside[n_inside++] = &cp2; else outside[n_ouside++] = &cp2;
  if (cp3.w >= zn) inside[n_inside++] = &cp3; else outside[n_ouside++] = &cp3;

  switch (n_inside) {
    case 3: {
      fill_triangle(*inside[0], *inside[1], *inside[2], tri.color);
      break;
    }
    case 2: {
      Vec4 v1 = *inside[0], v2 = *inside[1];
      Vec4 v3 = intersect(v1, *outside[0], zn);
      Vec4 v4 = intersect(v2, *outside[0], zn);
      fill_triangle(v1, v2, v3, tri.color);
      fill_triangle(v2, v3, v4, tri.color);
      break;
    }
    case 1: {
      Vec4 v1 = *inside[0];
      Vec4 v2 = intersect(v1, *outside[0], zn);
      Vec4 v3 = intersect(v1, *outside[1], zn);
      fill_triangle(v1, v2, v3, tri.color);
      break;
    }
  };
}

void SDLApp::draw_mesh(Mesh mesh, Mat comp_matrix, std::pair<float, float> z, Vec4 E) {
  // comp_matrix = M * comp_matrix;
  
  for (size_t i = 0; i < mesh.indexes.size(); i+=3) {
    Vec4 v1 = mesh.vertices[mesh.indexes[i]];
    Vec4 v2 = mesh.vertices[mesh.indexes[i+1]];
    Vec4 v3 = mesh.vertices[mesh.indexes[i+2]];
    Triangle tri(v1, v2, v3);
    draw_face(tri, comp_matrix, z, E);
  }
}
