#pragma once
// #include "Engine/Graphics/Mesh.hpp">
#include <glm/mat4x4.hpp>
#include <memory>
#include "Engine/Object3D.hpp"

class PhysicsComp;
class btRigidBody;
class btVector3;

class ACube : public Object3D {
public:
  template<typename... Args>
  ACube (Args&&... args): Object3D(std::forward<Args>(args)...) {}

  std::shared_ptr<PhysicsComp> phyComp;

  mat4 getTransformMatrix() const override;

  void init() override;
  void update() override;
};
