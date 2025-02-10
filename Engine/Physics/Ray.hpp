#pragma once
#include "vec3.hpp"

class Ray {
public:
  Ray (const btVector3& startPos) : startPos(startPos) {};
  const btVector3& startPos;

  const class btCollisionObject* hitObject = nullptr;

  Ray& castTo (const btVector3& endPos);
  Ray& castInDir (const btVector3& dir, const float& length);

  class PhysicsComp* getHitPhysicsComp ();
};
