#include "quaternions.hpp"
#include "matrix.hpp"

void Quat::print(std::string name) const {
    std::cout << name << " = ";
    bool first = true;

    auto print_comp = [&](float val, const char* unit) {
        if (val == 0.0f) return;

        if (!first) {
            std::cout << (val > 0 ? " + " : " - ");
        } else {
            if (val < 0) std::cout << "-";
            first = false;
        }

        float abs_v = (val < 0) ? -val : val;

        if (abs_v != 1.0f || unit[0] == '\0') {
            std::cout << abs_v;
        }
        std::cout << unit;
    };

    print_comp(w, "");
    print_comp(x, "i");
    print_comp(y, "j");
    print_comp(z, "k");

    if (first) std::cout << "0";
    std::cout << "\n";
}

Quat Quat::operator+(const Quat& q) const {
  return Quat(w+q.w, x+q.x, y+q.y, z+q.z);
}

Quat Quat::operator-(const Quat& q) const {
  return Quat(w-q.w, x-q.x, y-q.y, z-q.z);
}

Quat Quat::operator-() const {
  return Quat(-w, -x, -y, -z);
}

Quat Quat::operator*(const Quat& q) const {
  return Quat(
    w*q.w - x*q.x - y*q.y - z*q.z,
    w*q.x + q.w*x + y*q.z - q.y*z,
    w*q.y - x*q.z + q.w*y + q.x*z,
    w*q.z + x*q.y - q.x*y + q.w*z
  );
}

Quat Quat::operator*(float k) const {
  return Quat(k*w, k*x, k*y, k*z);
}

Quat Quat::conjugate() const {
  return Quat(w, -x, -y, -z);
}

float Quat::length() const {
  return sqrt(w*w + x*x + y*y + z*z);
}

Quat Quat::norm() const {
  float N = length();
  return Quat(w/N, x/N, y/N, z/N);
}

Quat Quat::from_axis_angle(Vec4 axis, float angle) {
  Vec4 a = axis.norm();
  float half_angle = angle/2;
  float s = sin(angle/2);
  return Quat(cos(half_angle), a.x * s, a.y * s, a.z * s);
}

Mat4 Quat::to_matrix() const {
  return Mat4({
    1-2*(y*y+z*z), 2*(x*y-w*z),    2*(x*z+w*y),    0,
    2*(x*y+w*z),   1-2*(x*x+z*z),  2*(y*z-w*x),    0,
    2*(x*z-w*y),   2*(y*z+w*x),    1-2*(x*x+y*y),  0,
    0,             0,              0,              1
  });
}

float dot(const Quat& q1, const Quat& q2) {
  return q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
}

Quat slerp(Quat q1, Quat q2, float t) {
  q1 = q1.norm(), q2 = q2.norm();
  float cosTheta = dot(q1, q2);
  if (cosTheta < 0.0f) {
    q1 = Quat(-q1.w, -q1.x, -q1.y, -q1.z);
    cosTheta *= -1;
  }

  if (cosTheta > 0.9995f) return Quat( q1.w + t * (q2.w - q1.w), q1.x + t * (q2.x - q1.x), q1.y + t * (q2.y - q1.y), q1.z + t * (q2.z - q1.z) ).norm();
  
  float theta_0 = acos(cosTheta);
  float theta = theta_0 * t;

  float sin_theta_0 = sin(theta_0);
  float sin_theta = sin(theta);

  float s1 = sin_theta / sin_theta_0;
  float s0 = cos(theta) - cosTheta * s1;

  return Quat( (s0 * q1.w) + (s1 * q1.w), (s0 * q1.x) + (s1 * q1.x), (s0 * q1.y) + (s1 * q1.y), (s0 * q1.z) + (s1 * q1.z) ).norm();
}
