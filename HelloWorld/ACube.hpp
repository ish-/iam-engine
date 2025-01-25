#pragma once
// #include "../Engine/Graphics/Mesh.hpp">
#include <glm/mat4x4.hpp>
#include <memory>
#include "../Engine/Object3D.hpp"

class PhysicsComponent;
class btRigidBody;
class btVector3;

class ACube : public Object3D {
public:
  template<typename... Args>
  ACube (Args&&... args): Object3D(std::forward<Args>(args)...) {}

  std::shared_ptr<PhysicsComponent> phyComp;
  btRigidBody* rigidBody = nullptr;
  // btVector3* inertia;

  mat4 getTransformMatrix() const override;

  void init() override;
  void update() override;
  void enablePhysics ();
};
