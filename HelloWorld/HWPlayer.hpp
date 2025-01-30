#pragma once
#include <memory>
#include "Engine/Object3D.hpp"

class PhysicsComponent;
class PlayerCtrlComp;
class btRigidBody;
class btVector3;

class HWPlayer : public Object3D {
public:
  template<typename... Args>
  HWPlayer (Args&&... args):
    Object3D(std::forward<Args>(args)...) {}

  std::shared_ptr<PhysicsComponent> phyComp;
  std::shared_ptr<PlayerCtrlComp> ctrlComp;

  // mat4 getTransformMatrix() const override;

  void init() override;
  // void update() override;
};
