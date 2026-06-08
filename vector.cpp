#include "vector.hpp"
#include "camera.hpp"
#include "matrix.hpp"
#include <cmath>

Vec4 Vec4::operator+(const Vec4& v) const {
  return Vec4(x+v.x, y+v.y, z+v.z, w+v.w);
}

Vec4 Vec4::operator-(const Vec4& v) const {
  return Vec4(x-v.x, y-v.y, z-v.z, w-v.w);
}

Vec4 Vec4::operator*(float k) const {
  return Vec4(x*k, y*k, z*k, w*k);
}

Vec4 Vec4::operator/(float k) const {
  return Vec4(x/k, y/k, z/k, w/k);
}

float dot(const Vec4& v1, const Vec4& v2) {
  return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z + v1.w*v2.w;
}

Vec4 cross(const Vec4& v1, const Vec4& v2) {
  return Vec4(
    v1.y * v2.z - v1.z * v2.y,
    v1.z * v2.x - v1.x * v2.z,
    v1.x * v2.y - v1.y * v2.x,
    0.0f
  );
}

float Vec4::length() const {
  return std::sqrt(x*x + y*y + z*z);
}

Vec4 Vec4::norm() const {
  Vec4 vec = (*this)/length();
  vec.w = w;
  return vec;
}

Vec2 Vec4::project(Mat4 mvp, const Camera& camera) const {
  Vec4 V_screen = mvp * (*this);
  float x = V_screen.x;
  float y = V_screen.y;
  float w = V_screen.w;
  return Vec2((x/w + 1)/2 * camera.width, (1 - y/w)/2 * camera.height, w);
}

void Vec4::print() {
  std::cout << "(" << x << "\t" << y << "\t" << z << "\t" << w << ")\n";
}
