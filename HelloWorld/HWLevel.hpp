#pragma once
#include <glm/mat4x4.hpp>
#include <memory>
#include "Engine/Object3D.hpp"

class PhysicsComponent;
// class btRigidBodø

class HWLevel : public Object3D {
public:
  template<typename... Args>
  HWLevel (Args&&... args):
    Object3D(std::forward<Args>(args)...) {}

  std::shared_ptr<PhysicsComponent> phyComp;

  // mat4 getTransformMatrix() const override;
  std::shared_ptr<class MeshModelComp> meshComp;

  void init() override;
  void update() override;
};
