#pragma once
// #include "Engine/Graphics/Mesh.hpp">
#include <glm/mat4x4.hpp>
#include <memory>
#include "Engine/Actor.hpp"

class PhysicsComp;

class ACube : public Actor {
public:
  template<typename... Args>
  ACube (Args&&... args): Actor(std::forward<Args>(args)...) {}

  std::shared_ptr<PhysicsComp> phyComp;

  mat4 getTransformMatrix() const override;

  void init() override;
  void update() override;
};
