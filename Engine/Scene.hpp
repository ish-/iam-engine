#pragma once
#include "Object3D.hpp"
#include "WObject.hpp"
#include <memory>
#include <vector>

class Light;
class Camera;

class Scene : public Object3D {
public:
  // Scene (WContext& ctx) : WObject(ctx) {}

  std::shared_ptr<Camera> camera;
  std::shared_ptr<Light> light;
  // std::vector<std::shared_ptr<AActor>> children;
  // std::vector<std::shared_ptr<AActor>> children;


  virtual bool load ();
  // virtual bool unload ();

  virtual void update(float dt);

  // ~Scene() = default;
};
