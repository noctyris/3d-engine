#ifndef ENGINE_HPP
#define ENGINE_HPP

#define _USE_MATH_DEFINE

#include "types.hpp"
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
    float yaw = -90.0f, pitch = 0.0f;
    float sensivity = 0.1f;

    Camera(Vec4 pos, Vec4 targ, float field_of_view, std::pair<float, float> z, std::pair<int, int> screen_size);
    void gen_projection_matrix();
    void gen_view_matrix();
    void move_forward(float speed);
    void move_sideways(float speed);
    void move_altitude(float speed);
    void rotate(float dx, float dy);
  private:
    Vec4 get_direction();
    void update_position(Vec4 dir, float speed);
};

class Triangle {
  public:
    Vec4 v1, v2, v3;
    Color color;

    Triangle(Vec4 v1 = Vec4(0, 0, 0, 1), Vec4 v2 = Vec4(0, 0, 0, 1), Vec4 v3 = Vec4(0, 0, 0, 1), Color c = Color(255, 255, 255)) : v1(v1), v2(v2), v3(v3), color(c) {};
};

float radians(float deg);

#endif
