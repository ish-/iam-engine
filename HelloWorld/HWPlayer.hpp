#pragma once
#include <glm/mat4x4.hpp>
#include <memory>
#include "../Engine/Object3D.hpp"

class PhysicsComponent;
class btRigidBody;
class btVector3;

class HWPlayer : public Object3D {
public:
  template<typename... Args>
  HWPlayer (Args&&... args):
    Object3D(std::forward<Args>(args)...) {}

  std::shared_ptr<PhysicsComponent> phyComp;

  // mat4 getTransformMatrix() const override;

  void init() override;
  void update() override;
};
