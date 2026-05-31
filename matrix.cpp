#include "matrix.hpp"

Mat::Mat() {
  for (int i = 0; i < D*D; i++) values[i] = (i%(D+1) == 0) ? 1.0f : 0.0f;
}

float& Mat::operator()(int r, int c) {
  return values[r * D + c];
}

void Mat::print() {
  for (int r = 0; r < D; r++) {
    for (int c = 0; c < D; c++) {
      std::cout << (*this)(r, c) << "\t";
 }
    std::cout << "\n";
  }
};

Vec4::Vec4(float X, float Y, float Z, float W) {
  x = X; y = Y; z = Z; w = W;
}

void Vec4::print() {
  std::cout << "(" << (*this).x << " " << (*this).y << " " << (*this).z << " " << (*this).w << ")\n";
}

Vec4 Vec4::norm() {
  Vec4 curr = (*this);
  Vec4 vec = Vec4(0, 0, 0, (*this).w);
  float length = std::sqrt(pow(curr.x, 2) + pow(curr.y, 2) + pow(curr.z, 2));
  vec.x = curr.x/length;
  vec.y = curr.y/length;
  vec.z = curr.z/length;
  return vec;
}

Vec4 Vec4::operator+(const Vec4 other) {
  return Vec4((*this).x+other.x, (*this).y+other.y, (*this).z+other.z, 1);
}

Vec4 Vec4::operator-(const Vec4 other) {
  return Vec4((*this).x-other.x, (*this).y-other.y, (*this).z-other.z, 1);
}

Vec4 cross(Vec4 u, Vec4 v) {
  Vec4 vec(u.y*v.z-u.z*v.y, u.z*v.x-u.x*v.z, u.x*v.y-u.y*v.x, 1);
  return vec;
}
