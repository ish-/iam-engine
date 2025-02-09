#pragma once
#include "BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"
#include "ContactResult.hpp"

struct ContactCallback : public btCollisionWorld::ContactResultCallback {
  virtual ~ContactCallback() = default;
  bool bCollided = false;

  ContactResult result;

  // Called for each contact point
  virtual btScalar addSingleResult(
    btManifoldPoint& cp,
    const btCollisionObjectWrapper* colObj0,
    int partId0,
    int index0,
    const btCollisionObjectWrapper* colObj1,
    int partId1,
    int index1
  ) override;
};
