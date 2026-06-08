#ifndef QUATERNIONS_HPP
#define QUATERNIONS_HPP

#include "vector.hpp"
#include <iostream>
#include <cmath>

class Mat4;

class Quat {
  public:
    float w, x, y, z;

    Quat(float w = 1, float x = 0, float y = 0, float z = 0) : w(w), x(x), y(y), z(z) {};
    void print(std::string name) const;
    Quat operator+(const Quat& q) const;
    Quat operator-(const Quat& q) const;
    Quat operator-() const;
    Quat operator*(const Quat& q) const;
    Quat operator*(float k) const;
    Quat conjugate() const;
    float length() const;
    Quat norm() const;
    static Quat from_axis_angle(Vec4 axis, float angle);
    Mat4 to_matrix() const;
};

float dot(const Quat& q1, const Quat& q2);
Quat slerp(const Quat& q1, const Quat& q2, float t);

#endif
