#pragma once
// #include "AActor.hpp"
#include "Object3D.hpp"
#include <memory>
#include <vector>

class Light;
class Camera;

class Scene : public Object3D {
public:
  std::shared_ptr<Camera> camera;
  std::shared_ptr<Light> light;
  std::vector<std::shared_ptr<Object3D>> objects;
  // std::vector<std::shared_ptr<AActor>> actors;

  bool load ();
  bool unload ();

  void update();

  // ~Scene() = default;
};
