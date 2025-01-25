#pragma once
#include "LinearMath/btVector3.h"

class Physics;
class btConvexInternalShape;
class btRigidBody;
class btCollisionShape;
class btDefaultMotionState;
class btBoxShape;

class PhysicsComp {
public:
  struct Params {
    btBoxShape* shape;
    btVector3 pos;
    btVector3 size;
    btVector3 intertia {0,0,0};
    btVector3 initialImpulse {0,0,0};
    btVector3 initialImpulsePos {0,0,0};
    float mass = 1.;
    float restitution = 0.5;
    float friction = 0.5;
  };

  Params& params;

  PhysicsComp (Params& params);
  ~PhysicsComp ();

  Physics& physics;

  // btConvexInternalShape* shape;
  btRigidBody* rigidBody;
  btDefaultMotionState* motionState;
  btVector3* inertia;

  template<typename Shape = btBoxShape>
  bool init (const Params& params);
};
