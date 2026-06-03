#ifndef TYPES_HPP
#define TYPES_HPP

#include <SDL3/SDL.h>

struct Color {
  Uint8 r, g, b, a;
  Color(Uint8 r=0, Uint8 g=0, Uint8 b=0, Uint8 a=255) : r(r), g(g), b(b), a(a) {}
};

class Vec2 {
  public:
    float x, y;
    Vec2(float x = 0, float y = 0) : x(x), y(y) {};
};

#endif
