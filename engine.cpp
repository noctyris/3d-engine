#include "engine.hpp"
#include <string>

float radians(float deg) { return deg * M_PI / 180.f; };

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

void Camera::gen_view_matrix() {
  Vec4 f = (target - position).norm();
  Vec4 r = cross(Vec4(0, 1, 0, 1), f).norm();
  Vec4 u = cross(f, r);
  view_matrix = Mat({r.x,  r.y,  r.z,  -dot(r, position),
                     u.x,  u.y,  u.z,  -dot(u, position),
                     f.x,  f.y,  f.z,  -dot(f, position),
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
  Vec4 dir = cross(Vec4(0, 1, 0, 0), get_direction()).norm();
  update_position(dir, speed);
}

void Camera::move_altitude(float speed) {
  Vec4 dir(0, 1, 0, 0);
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
  front.w = 0;

  target = position + front.norm();
}

Mat Mesh::gen_model_matrix() {
  float Tx = position.x,  Ty = position.y,  Tz = position.z;
  float Rx = rotation.x,  Ry = rotation.y,  Rz = rotation.z;
  float Sx = scale.x,     Sy = scale.y,     Sz = scale.z;
  Mat T({1,0,0,Tx, 0,1,0,Ty, 0,0,1,Tz, 0,0,0,1});
  Mat R = Mat({cos(Ry),0,sin(Ry),0, 0,1,0,0, -sin(Ry),0,cos(Ry),0, 0,0,0,1}) * Mat({1,0,0,0, 0,cos(Rx),-sin(Rx),0, 0,sin(Rx),cos(Rx),0, 0,0,0,1}) * Mat({cos(Rz),-sin(Rz),0,0, sin(Rz),cos(Rz),0,0, 0,0,1,0, 0,0,0,1});
  Mat S({Sx,0,0,0, 0,Sy,0,0, 0,0,Sz,0, 0,0,0,1});
  return T*R*S;
}

bool Mesh::load_from_obj(std::string path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    std::cerr << "Unable to open file: " << path << std::endl;
    return false;
  }

  std::string line;

  while (std::getline(file, line)) {
    if (line.empty() || line[0] == '#') continue;
    std::stringstream ss(line);
    std::string type;
    ss >> type;

    if (type == "v") {
      float x, y, z;
      ss >> x >> y >> z;
      vertices.push_back(Vec4(x, y, z, 1.0f));
    }
    else if (type == "f") {
      std::vector<int> f_indexes;
      std::string segment;
      while (ss >> segment) {
        f_indexes.push_back(std::stoi(segment) - 1);
      }
      for (size_t i = 1; i < f_indexes.size() - 1; i++) {
        indexes.push_back(f_indexes[0]);
        indexes.push_back(f_indexes[i]);
        indexes.push_back(f_indexes[i+1]);
      }
    }
  }

  file.close();
  return true;
}
