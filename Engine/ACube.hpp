#pragma once
// #include "Engine/Graphics/Mesh.hpp">
#include <glm/mat4x4.hpp>
#include <memory>
#include "Actor.hpp"

// class PhysicsComp;

class ACube : public Actor {
public:
  string getActorClassName() override { return "ACube"; }
  // std::shared_ptr<PhysicsComp> phyComp;

  // mat4 getTransformMatrix() const override;

  void init() override;
  // void update(const float& dt) override;
};
