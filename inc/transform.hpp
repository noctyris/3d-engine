#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "matrix.hpp"
#include "quaternions.hpp"
#include "vector.hpp"

class Transform {
  private:
    Vec4 m_position;
    Quat m_rotation;
    Vec4 m_scale;
    mutable Mat4 m_model_matrix;
    mutable bool m_dirty = true;

    Mat4 get_translation_matrix() const;
    Mat4 get_rotation_matrix() const;
    Mat4 get_scaling_matrix() const;
  public:
    Transform(Vec4 p = Vec4(0,0,0), Quat r = Quat(1,0,0,0), Vec4 s = Vec4(1,1,1)) : m_position(p), m_rotation(r), m_scale(s) {}
    void set_position(const Vec4& p);
    void set_rotation(const Quat& r);
    void set_scale(const Vec4& s);
    void move(const Vec4& dp);
    void rotate(const Vec4& axis, float angle);
    Mat4 get_matrix() const;
};

#endif
