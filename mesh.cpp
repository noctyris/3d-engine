#include "mesh.hpp"
#include "camera.hpp"
#include "sdlapp.hpp"
#include "vector.hpp"
#include <fstream>
#include <sstream>

bool Mesh::load_from_obj(std::string path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    std::cerr << "Unable to open file: " << path << std::endl;
    return false;
  }

  std::string line;

  while (std::getline(file, line)) {
    if (line.empty() || line[0] == '#') continue;
    std::stringstream ss(line);
    std::string type;
    ss >> type;

    if (type == "v") {
      float x, y, z;
      ss >> x >> y >> z;
      vertices.push_back(Vec4(x, y, z, 1.0f));
    }
    else if (type == "f") {
      std::vector<int> f_indexes;
      std::string segment;
      while (ss >> segment) {
        f_indexes.push_back(std::stoi(segment) - 1);
      }
      for (size_t i = 1; i < f_indexes.size() - 1; i++) {
        indexes.push_back(f_indexes[0]);
        indexes.push_back(f_indexes[i]);
        indexes.push_back(f_indexes[i+1]);
      }
    }
  }

  file.close();
  return true;
}

void Mesh::get_info() const {
  float min_x = vertices[0].x, max_x = vertices[0].x, min_y = vertices[0].y, max_y = vertices[0].y, min_z = vertices[0].z, max_z = vertices[0].z;
  for (size_t i = 1; i < vertices.size(); i++) {
    if (vertices[i].x < min_x) min_x = vertices[i].x;
    else if (vertices[i].x > max_x) max_x = vertices[i].x;
    if (vertices[i].y < min_y) min_y = vertices[i].y;
    else if (vertices[i].y > max_y) max_y = vertices[i].y;
    if (vertices[i].z < min_z) min_z = vertices[i].z;
    else if (vertices[i].z > max_z) max_z = vertices[i].z;
  }
  std::cout << vertices.size() << " vertices\n";
  std::cout << indexes.size()/3 << " triangles\n";
  std::cout << "\nX-axis:\nx=" << min_x << " [--- < Δx=" << max_x-min_x << " > ---] x=" << max_x << "\n";
  std::cout << "\nY-axis:\nx=" << min_y << " [--- < Δx=" << max_y-min_y << " > ---] x=" << max_y << "\n";
  std::cout << "\nZ-axis:\nx=" << min_z << " [--- < Δx=" << max_z-min_z << " > ---] x=" << max_z << "\n";
}

void Mesh::show(SDLApp* sdl, const Camera& camera) const {
  auto intersect = [&](Vec4 inside, Vec4 outside, float zn) { return inside + (outside-inside) * ((zn - inside.w) / (outside.w - inside.w)); };

  Mat4 V = camera.view_matrix, P = camera.projection_matrix, M = transform.get_matrix();
  Mat4 mvp = P * V * M;
  float zn = camera.zn;

  auto project = [&](Vec4 v) { return v.project(mvp, camera); };
  auto to_pixels = [&](Vec4 v) { float inv_w = 1.0f / v.w; return Vec2((v.x * inv_w + 1.0f) * 0.5f * camera.width,(1.0f - (v.y * inv_w + 1.0f) * 0.5f) * camera.height); };

  for (size_t i = 0; i < indexes.size(); i+=3) {
    Vec4 v1 = vertices[indexes[i]], v2 = vertices[indexes[i+1]], v3 = vertices[indexes[i+2]];
    Vec4 w1 = M*v1, w2 = M*v2, w3 = M*v3;

    Vec4 N = cross((w2-w1), (w3-w1)), V_cam = (camera.position - w1).norm();
    if (dot(N, V_cam) <= 0) continue;

    Vec4 cp1 = mvp * v1, cp2 = mvp * v2, cp3 = mvp * v3;
    Vec4* inside[3]; Vec4* outside[3];
    int n_inside = 0, n_outside = 0;

    if (cp1.w >= zn) inside[n_inside++] = &cp1; else outside[n_outside++] = &cp1;
    if (cp2.w >= zn) inside[n_inside++] = &cp2; else outside[n_outside++] = &cp2;
    if (cp3.w >= zn) inside[n_inside++] = &cp3; else outside[n_outside++] = &cp3;

    switch (n_inside) {
      case 3: {
        sdl->fill_triangle(to_pixels(*inside[0]), to_pixels(*inside[1]), to_pixels(*inside[2]), color);
        break;
      }
      case 2: {
        Vec4 v1 = *inside[0], v2 = *inside[1];
        Vec4 v3 = intersect(v1, *outside[0], zn);
        Vec4 v4 = intersect(v2, *outside[0], zn);
        sdl->fill_triangle(project(v1), project(v2), project(v3), color);
        sdl->fill_triangle(project(v2), project(v3), project(v4), color);
        break;
      }
      case 1: {
        Vec4 v1 = *inside[0];
        Vec4 v2 = intersect(v1, *outside[0], zn);
        Vec4 v3 = intersect(v1, *outside[1], zn);
        sdl->fill_triangle(project(v1), project(v2), project(v3), color);
        break;
      }
    };
  }
}
