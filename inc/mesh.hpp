#ifndef MESH_HPP
#define MESH_HPP

#include "light.hpp"
#include "transform.hpp"
#include "vector.hpp"
#include "types.hpp"
#include <vector>

class SDLApp;
class Mat4;
class Camera;

class Mesh {
  public:
    std::vector<Vec4> vertices;
    std::vector<int> indexes;
    Color color;

    Transform transform;

    Mesh() : color(Color(200, 200, 200)) {}
    bool load_from_obj(std::string path);
    void get_info() const;
    void show(SDLApp* sdl, const Camera& camera, const std::vector<Light*>& lights) const;
};

#endif
