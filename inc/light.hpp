#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "vector.hpp"
#include "types.hpp"

enum class LightType { AMBIENT, DIRECTIONAL, POINT };

class Light {
  public:
    Color color;
    float intensity;
    LightType type;

    Light(LightType t, Color c, float i) : color(c), intensity(i), type(t) {}
    virtual ~Light() {}
};

class AmbientLight : public Light {
  public:
    AmbientLight(Color c = Color(255, 255, 255), float i = 0.1f) : Light(LightType::AMBIENT, c, i) {}
};

class DirectionalLight : public Light {
  public:
    Vec4 direction;
    DirectionalLight(Vec4 dir, Color c = Color(255,255,255), float i = 1.0f) : Light(LightType::DIRECTIONAL, c, i), direction(dir.norm()) { direction.w = 0; }
};

class PointLight : public Light {
  public:
    Vec4 position;
    float range;
    PointLight(Vec4 pos, float r = 10.0f, Color c = Color(255,255,255), float i = 1.0f) : Light(LightType::POINT, c, i), position(pos), range(r) { position.w = 1; }
};

#endif
