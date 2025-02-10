#include "Ray.hpp"
#include "Physics.hpp"
#include "PhysicsComp.hpp"
#include "BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"

// Ray::Ray (const btVector3& startPos): startPos(startPos) {}

Ray& Ray::castInDir(const btVector3& dir, const float& length) {
  return castTo(startPos + dir * length);
}

Ray& Ray::castTo (const btVector3& endPos) {
  btCollisionWorld::ClosestRayResultCallback rayCallback(startPos, endPos);
  Physics::get().dynamicsWorld->rayTest(startPos, endPos, rayCallback);

  if (rayCallback.hasHit()) {
    hitObject = rayCallback.m_collisionObject;
  }
  return *this;
}

PhysicsComp* Ray::getHitPhysicsComp () {
  if (hitObject)
    return static_cast<PhysicsComp*>(hitObject->getUserPointer());
  return nullptr;
}
