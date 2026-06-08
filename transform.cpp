#include "transform.hpp"
#include "quaternions.hpp"

Mat4 Transform::get_translation_matrix() const {
  return Mat4({
    1, 0, 0, m_position.x,
    0, 1, 0, m_position.y,
    0, 0, 1, m_position.z,
    0, 0, 0, 1
  });
}

Mat4 Transform::get_scaling_matrix() const {
  return Mat4({
    m_scale.x, 0, 0, 0,
    0, m_scale.y, 0, 0,
    0, 0, m_scale.z, 0,
    0, 0, 0, 1
  });
}

Mat4 Transform::get_matrix() const {
  if (m_dirty) {
    Mat4 T = get_translation_matrix();
    Mat4 R = m_rotation.to_matrix();
    Mat4 S = get_scaling_matrix();
    m_model_matrix = T*R*S;
    m_dirty = false;
  }
  return m_model_matrix;
}

void Transform::set_position(const Vec4& p) {
  m_position = p;
  m_dirty = true;
}

void Transform::set_rotation(const Quat& r) {
  m_rotation = r;
  m_dirty = true;
}

void Transform::set_scale(const Vec4& s) {
  m_scale = s;
  m_dirty = true;
}

void Transform::move(const Vec4& dp) {
  m_position = m_position + dp;
  m_dirty = true;
}

void Transform::rotate(const Vec4& axis, float angle) {
  m_rotation = (Quat::from_axis_angle(axis, angle) * m_rotation).norm();
  m_dirty = true;
}
