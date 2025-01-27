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
  std::vector<std::shared_ptr<Light>> lights;
  // std::vector<std::shared_ptr<Object3D>> children;
  // std::vector<std::shared_ptr<Object3D>> children;


  virtual bool load ();
  // virtual bool unload ();

  virtual void update(float dt);

  virtual void drawGui () = 0;
  // ~Scene() = default;
};
