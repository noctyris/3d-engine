#ifndef MATRIX_HPP
#define MATRIX_HPP

#define DIM 4

#include <initializer_list>
#include "types.hpp"
#include <iostream>
#include <cmath>

class Vec4;

class Mat {
  public:
    float values[DIM*DIM];
    int D = DIM;

    Mat() { for (int i = 0; i < D*D; i++) values[i] = 0; };
    Mat(std::initializer_list<float> list);
    float& operator()(int r, int c);
    Mat operator*(const Mat other);
    Vec4 operator*(const Vec4 v);
    void print();
};

class Vec4 {
  public:
    union {
      struct { float x, y, z, w; };
      float v[4];
    };

    Vec4(float x=0, float y=0, float z=0, float w=1) : x(x), y(y), z(z), w(w) {};
    Vec4 operator+(const Vec4 other);
    Vec4 operator-(const Vec4 other);
    Vec4 operator*(const float coef);
    Vec2 project(Mat comp_matrix, std::pair<int, int> screen_size);
    Vec4 norm();
    void print();
};

Vec4 intersect(Vec4 inside, Vec4 outside, float zn);
float dot(Vec4 u, Vec4 v);
Vec4 cross(Vec4 u, Vec4 v);

#endif
