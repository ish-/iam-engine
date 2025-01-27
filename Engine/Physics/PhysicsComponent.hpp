#pragma once
#include <memory>
#include "LinearMath/btVector3.h"
#include "../ACS/AComponent.hpp"
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "../../util/Symbol.hpp"

class Physics;
class btConvexInternalShape;
class btRigidBody;
class btCollisionShape;
class btDefaultMotionState;
class btBoxShape;

class PhysicsComponent : public AComponent {
public:
  struct Params {
    btConvexInternalShape* shape;
    btVector3 pos;
    float mass = 1.;
    btVector3 initialImpulse {0,0,0};
    btVector3 intertia {0,0,0};
    // btVector3 initialImpulsePos {0,0,0};
    // float restitution = 0.5;
    // float friction = 0.5;
  };

  virtual Symbol getASystemType () {
      static Symbol symbol { "Physics" };
      return symbol;
  }

  Params& params;

  PhysicsComponent (Params& params);
  ~PhysicsComponent ();

  Physics& physics;

  // btConvexInternalShape* shape;
  btRigidBody* rigidBody;
  btDefaultMotionState* motionState;
  btVector3* inertia;

  // template<typename Shape = btBoxShape>
  bool init (Params& params);
  virtual void update(float dt) override;

  glm::mat4 getGlmTMat4 ();

  void applyForce (glm::vec3 force, glm::vec3 pos = {0,0,0});
  void applyTorque (glm::vec3 force);
};
