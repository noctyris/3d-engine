#include "camera.hpp"

void Camera::gen_projection_matrix() {
  float f = 1/tan(fov/2);
  projection_matrix(0,0) = aspect_ratio * f;
  projection_matrix(1,1) = f;
  projection_matrix(2,2) = zf/(zf-zn);
  projection_matrix(2,3) = -(zf*zn)/(zf-zn);
  projection_matrix(3,2) = 1;
  projection_matrix(3,3) = 0;
}

void Camera::gen_view_matrix() {
  Vec4 f = (target - position).norm();
  Vec4 r = cross(Vec4(0, 1, 0, 1),f).norm();
  Vec4 u = cross(f,r);
  view_matrix = Mat4({r.x,  r.y,  r.z, -dot(r,position),
                     u.x,  u.y,  u.z,  -dot(u,position),
                     f.x,  f.y,  f.z,  -dot(f,position),
                     0,    0,    0,    1}
  );
}

Vec4 Camera::get_direction() {
  return Vec4(target - position).norm();
}

void Camera::update_position(Vec4 dir, float speed) {
  position = position + dir * speed;
  target = target + dir * speed;
}

void Camera::move_forward(float speed) {
  Vec4 dir = get_direction();
  update_position(dir, speed);
}

void Camera::move_sideways(float speed) {
  Vec4 dir = cross(Vec4(0,1,0,0),get_direction()).norm();
  update_position(dir, speed);
}

void Camera::move_altitude(float speed) {
  Vec4 dir(0,1,0,0);
  update_position(dir, speed);
}

void Camera::rotate(float dx, float dy) {
  yaw   -= dx * sensivity;
  pitch -= dy * sensivity;

  if (pitch > 89.9f) pitch = 89.9f;
  if (pitch < -89.9f) pitch = -89.9f;

  Vec4 front;
  front.x = cos(yaw * M_PI / 180.0f) * cos(pitch * M_PI / 180.0f);
  front.y = sin(pitch * M_PI / 180.0f);
  front.z = sin(yaw * M_PI / 180.0f) * cos(pitch * M_PI / 180.0f);
  front.w = 0.0f;

  target = position + front.norm();
}
