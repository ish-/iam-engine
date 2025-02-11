#pragma once
#include "BulletDynamics/Dynamics/btRigidBody.h"

struct ContactResult {
  btVector3 normal;
  btVector3 velocity0;
  btVector3 velocity1;
  float impactSpeed;
  float penetrationDepth;
  float impactForce;
  const btRigidBody* body0 = nullptr;
  const btRigidBody* body1 = nullptr;

  operator bool() const { return bool(body0); }
};
