#include "matrix.hpp"

Mat4::Mat4(std::initializer_list<float> list) {
  int i = 0;
  for (float val : list) {
    if (i < 16) values[i++] = val;
  }
}

float& Mat4::operator()(int r, int c) {
  return values[r * 4 + c];
}

float Mat4::operator()(int r, int c) const {
  return values[r * 4 + c];
}

Mat4 Mat4::operator*(const Mat4& other) {
  Mat4 result;
  for(int i=0; i < 16; i++) result.values[i] = 0.0f;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
        result(i, j) += (*this)(i, k) * other(k, j);
      }
    }
  }
  *this = result;
  return *this;
}

Vec4 Mat4::operator*(const Vec4& v) {
  Vec4 res;
  for (int i = 0; i < 4; i++) {
    res.v[i]=0;
    for (int j = 0; j < 4; j++) {
      res.v[i] += (*this)(i, j) * v.v[j];
    }
  }
  return res;
}

void Mat4::print() {
  std::cout << std::fixed << std::setprecision(10);
  for (int r = 0; r < 4; r++) {
    for (int c = 0; c < 4; c++) {
      std::cout << (*this)(r, c) << "\t";
 }
    std::cout << "\n";
  }
}
