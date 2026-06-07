#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <initializer_list>
#include <iostream>
#include <iomanip>
#include "vector.hpp"

class Mat4 {
  public:
    float values[16];

    Mat4() { for (int i = 0; i < 16; i++) values[i] = 0; };
    Mat4(std::initializer_list<float> list);
    float& operator()(int r, int c);
    float operator()(int r, int c) const;
    Mat4 operator*(const Mat4& other);
    Vec4 operator*(const Vec4& v);
    void print();
};

#endif
