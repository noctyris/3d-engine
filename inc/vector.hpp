#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "types.hpp"
#include <iostream>
#include <cmath>

class Mat4;
class Camera;

class Vec4 {
  public:
    union {
      struct { float x, y, z, w; };
      float v[4];
    };

    Vec4(float x = 0, float y = 0, float z = 0, float w = 0) : x(x), y(y), z(z), w(w) {};
    Vec4 operator+(const Vec4& v) const;
    Vec4 operator-(const Vec4& v) const;
    Vec4 operator*(float k) const;
    Vec4 operator/(float k) const;
    float length() const;
    Vec4 norm() const;
    Vec2 project(Mat4 mvp, const Camera& camera) const;
    void print();
};

float dot(const Vec4& v1, const Vec4& v2);
Vec4 cross(const Vec4& v1, const Vec4& v2);

#endif
