#pragma once
#include "Object3D.hpp"
#include "IEngine.hpp"
#include <memory>
#include <vector>

class Light;
class Camera;

class Scene : public IHasCtx {
public:
  Scene (IEngine& ctx) : IHasCtx(ctx) {}

  std::shared_ptr<Camera> camera;
  std::vector<std::shared_ptr<Light>> lights;
  std::vector<std::shared_ptr<Object3D>> children;
  // std::vector<std::shared_ptr<Object3D>> children;

  template <typename AA = Object3D, typename... Args>
  std::shared_ptr<AA> newActor(Args&&... args) {
    auto actor = std::make_shared<AA>(_, std::forward<Args>(args)...);
    children.push_back(actor);
    actor->init();
    return actor;
  }

  virtual bool load ();
  // virtual bool unload ();

  virtual void update(float dt);

  virtual void drawGui ();
  // ~Scene() = default;
};
