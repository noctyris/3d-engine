#ifndef ENGINE_HPP
#define ENGINE_HPP

#define _USE_MATH_DEFINE

#include "matrix.hpp"
#include <utility>
#include <math.h>

class Camera {
  public:
    Vec4 position, target;
    float fov;
    float zn, zf;
    int width, height;
    float aspect_ratio;
    Mat projection_matrix, view_matrix;

    Camera(Vec4 pos, Vec4 targ, float field_of_view, std::pair<float, float> z, std::pair<int, int> screen_size);
    void gen_projection_matrix();
    void gen_view_matrix();
};

float radians(float deg);

#endif
