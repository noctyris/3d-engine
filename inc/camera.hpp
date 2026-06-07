#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "matrix.hpp"
#include "vector.hpp"
#include <utility>

class Camera {
  public:
    Vec4 position, target;
    float fov;
    float zn, zf;
    int width, height;
    float aspect_ratio;
    Mat4 projection_matrix, view_matrix;
    float yaw = -90.0f, pitch = 0.0f;
    float sensivity = 0.1f;

    Camera(Vec4 pos, Vec4 targ, float field_of_view, std::pair<float, float> z, std::pair<int, int> screen_size) : position(pos), target(targ), fov(field_of_view), zn(z.first), zf(z.second), width(screen_size.first), height(screen_size.second), aspect_ratio((float)screen_size.second/(float)screen_size.first) {};
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

#endif
