#include "engine.hpp"

Camera::Camera(Vec4 pos, Vec4 targ, float field_of_view, std::pair<float, float> z, std::pair<int, int> screen_size)
  : position(pos), target(targ), fov(field_of_view), zn(z.first), zf(z.second), width(screen_size.first), height(screen_size.second), aspect_ratio((float)screen_size.second / (float)screen_size.first) {};

void Camera::gen_projection_matrix() {
  float f = 1/tan(fov/2);
  projection_matrix(0,0) = aspect_ratio * f;
  projection_matrix(1,1) = f;
  projection_matrix(2,2) = zf/(zf-zn);
  projection_matrix(2,3) = -zf*zn/(zf-zn);
  projection_matrix(3,2) = 1;
  projection_matrix(3,3) = 0;
}
