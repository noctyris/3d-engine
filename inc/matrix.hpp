#ifndef MATRIX_HPP
#define MATRIX_HPP

#define DIM 4

#include <iostream>
#include <cmath>

class Mat {
  public:
    float values[DIM*DIM];
    int D = DIM;

    Mat();
    float& operator()(int r, int c);
    void print();
};

class Vec4 {
  public:
    float x, y, z, w;

    Vec4(float X, float Y, float Z, float W);
    Vec4 operator+(const Vec4 other);
    Vec4 operator-(const Vec4 other);
    Vec4 norm();
    void print();
};

Vec4 cross(Vec4 u, Vec4 v);

#endif
