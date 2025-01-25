#pragma once
// #include "../Engine/Graphics/Mesh.hpp"
#include <glm/mat4x4.hpp>
#include "../Engine/Object3D.hpp"

class btRigidBody;
class btVector3;

class ACube : public Object3D {
public:
  ACube ();

  // btRigidBody* groundRigidBody = nullptr;
  // btVector3* inertia;

  // mat4 getTransformMatrix() const override;

  void init() override;
  void update() override;
  void enablePhysics ();
};
