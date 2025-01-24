#pragma once
#include "HWObject.hpp"
#include "../Engine/Mesh.hpp"

class btRigidBody;
class btVector3;

class Cube : public HWObject, public Mesh {
public:
  Cube ();
  // ~Cube ();

  btRigidBody* groundRigidBody = nullptr;
  btVector3* inertia;

  mat4 getTransformMatrix() const override;

  void update() override;
  void enablePhysics ();
};
