#pragma once
#include <memory>
using namespace std;

class Camera;
class Light;
class Mesh;

class Renderer {
public:
  virtual ~Renderer() = default;
  virtual void init();
  virtual void render(shared_ptr<Camera> camera, shared_ptr<Light> light, shared_ptr<Mesh> mesh);
};
