#pragma once
#include <memory>
#include "Camera.hpp"
#include "Light.hpp"
#include "Mesh.hpp"
using namespace std;

class Camera;
class Light;
// class Mesh;

class Renderer {
public:
  static Renderer& get() {
    static Renderer instance;
    return instance;
  }
  // virtual ~Renderer() = default;

  void init();
  void render(shared_ptr<Camera> camera, shared_ptr<Light> light, shared_ptr<Mesh> mesh);
};
