#include "engine.hpp"

Camera::Camera(Vec4 pos, Vec4 targ, float field_of_view, std::pair<float, float> z, std::pair<int, int> screen_size)
  : position(pos), target(targ), fov(field_of_view), zn(z.first), zf(z.second), width(screen_size.first), height(screen_size.second), aspect_ratio((float)screen_size.second / (float)screen_size.first) {};

