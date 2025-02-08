#pragma once
#include <memory>
#include "Engine/Actor.hpp"

class PhysicsComp;
class PlayerPhyCtrlComp;
class btRigidBody;
class btVector3;

class HWPlayer : public Actor {
public:
  template<typename... Args>
  HWPlayer (Args&&... args):
    Actor(std::forward<Args>(args)...) {}

  std::shared_ptr<PhysicsComp> phyComp;
  std::shared_ptr<PlayerPhyCtrlComp> ctrlComp;

  // mat4 getTransformMatrix() const override;

  void init() override;
  // void update() override;
};
