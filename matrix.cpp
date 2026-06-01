#include "matrix.hpp"
#include "sdlapp.hpp"

Mat::Mat(std::initializer_list<float> list) {
  int i = 0;
  for (float val : list) {
    if (i < D * D) values[i++] = val;
  }
}

float& Mat::operator()(int r, int c) {
  return values[r * D + c];
}

Mat Mat::operator*(Mat other) {
  Mat result;
  int D = result.D;

  for(int i=0; i < D*D; i++) result.values[i] = 0.0f;
  for (int i = 0; i < D; i++) {
    for (int j = 0; j < D; j++) {
      for (int k = 0; k < D; k++) {
        result(i, j) += (*this)(i, k) * other(k, j);
      }
    }
  }
  return result;
}

Vec4 Mat::operator*(Vec4 vec) {
  Vec4 res;
  for (int i = 0; i < D; i++) {
    res.v[i]=0;
    for (int j = 0; j < D; j++) {
      res.v[i] += (*this)(i, j) * vec.v[j];
    }
  }
  return res;
}

void Mat::print() {
  for (int r = 0; r < D; r++) {
    for (int c = 0; c < D; c++) {
      std::cout << (*this)(r, c) << "\t";
 }
    std::cout << "\n";
  }
};

void Vec4::print() {
  std::cout << "(" << (*this).x << " " << (*this).y << " " << (*this).z << " " << (*this).w << ")\n";
}

Vec4 Vec4::norm() {
  Vec4 curr = (*this);
  Vec4 vec = Vec4(0, 0, 0, (*this).w);
  float length = std::sqrt(curr.x*curr.x + curr.y*curr.y + curr.z*curr.z);
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

Vec2 Vec4::get_screen_position(Mat comp_matrix, std::pair<int, int> screen_size) {
  Vec4 V_screen = comp_matrix * (*this);
  float x = V_screen.x;
  float y = V_screen.y;
  float w = V_screen.w;
  return Vec2((x/w + 1)/2 * screen_size.first, (1 - y/w)/2 * screen_size.second);
}

float dot(Vec4 u, Vec4 v) {
  return u.x*v.x + u.y*v.y + u.z*v.z;
}

Vec4 cross(Vec4 u, Vec4 v) {
  return Vec4(
    u.y * v.z - u.z * v.y, 
    u.z * v.x - u.x * v.z, 
    u.x * v.y - u.y * v.x, 
    0.0f
  );
}
