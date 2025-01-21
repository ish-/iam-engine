#pragma once
// #include "AActor.hpp"
#include "Object3D.hpp"
#include "WObject.hpp"
#include "WContext.hpp"
#include <memory>
#include <vector>

class Light;
class Camera;

class Scene : public Object3D {
public:
  // Scene (WContext& ctx) : WObject(ctx) {}

  std::shared_ptr<Camera> camera;
  std::shared_ptr<Light> light;
  std::vector<std::shared_ptr<Object3D>> children;
  // std::vector<std::shared_ptr<AActor>> actors;

  virtual bool load ();
  // virtual bool unload ();

  virtual bool update();

  // ~Scene() = default;
};
