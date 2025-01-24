#pragma once
#include "HWObject.hpp"
#include "../Engine/Mesh.hpp"

class btRigidBody;
class btVector3;

class Cube : public HWObject, public Mesh {
public:
  Cube ();

  template<typename... Args>
  Cube (Args&&... args): Mesh(std::forward<Args>(args)...) {
    init();
  }

  btRigidBody* groundRigidBody = nullptr;
  btVector3* inertia;

  mat4 getTransformMatrix() const override;

  void init();
  void update() override;
  void enablePhysics ();
};
