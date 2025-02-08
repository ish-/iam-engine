#pragma once
#include <glm/mat4x4.hpp>
#include <memory>
#include "Engine/Actor.hpp"

class PhysicsComp;
// class btRigidBodø

class HWLevel : public Actor {
public:
  template<typename... Args>
  HWLevel (Args&&... args):
    Actor(std::forward<Args>(args)...) {}

  std::shared_ptr<PhysicsComp> phyComp;

  // mat4 getTransformMatrix() const override;
  std::shared_ptr<class MeshModelComp> meshComp;

  void init() override;
  void update() override;
};
