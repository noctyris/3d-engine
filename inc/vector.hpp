#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <cmath>

class Vec4 {
  public:
    float x, y, z, w;
    Vec4(float x = 0, float y = 0, float z = 0, float w = 0) : x(x), y(y), z(z), w(w) {};
    Vec4 operator+(const Vec4& v) const;
    Vec4 operator-(const Vec4& v) const;
    Vec4 operator*(float k) const;
    Vec4 operator/(float k) const;
    float dot(const Vec4& v) const;
    Vec4 cross(const Vec4& v) const;
    float length() const;
    Vec4 norm() const;
    void print();
};

#endif
