#include <btBulletDynamicsCommon.h>
#include "Physics.hpp"
#include "PhysicsComp.hpp"

PhysicsComp::PhysicsComp (Params& params)
  : physics(Physics::get()), params(params)
{
  init(params);
}

template<typename Shape>
bool PhysicsComp::init (const Params& params) {
  // if constexpr (std::is_same<Shape, btBoxShape>::value) {
  //   shape = new btBoxShape(params.size);
  // } else if constexpr (std::is_same<Shape, btSphereShape>::value) {
  //   shape = new btSphereShape(params.size.getX());
  // } else if constexpr (std::is_same<Shape, btCylinderShape>::value) {
  //   shape = new btCylinderShape(params.size);
  // } else {
  //   return false;
  // }

  btTransform transform;
  transform.setIdentity();
  transform.setOrigin(params.pos);
  motionState = new btDefaultMotionState(transform);

  // inertia = new btVector3(.8, .8, .8);
  // shape->calculateLocalInertia(1., *inertia);

  // btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(1., motionState, shape, *inertia);
  btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(params.mass, motionState, params.shape);
  rigidBody = new btRigidBody(rigidBodyCI);
  physics.dynamicsWorld->addRigidBody(rigidBody);
  rigidBody->setActivationState(DISABLE_DEACTIVATION);
  rigidBody->applyForce(
    params.initialImpulse,
    params.initialImpulsePos);
}

PhysicsComp::~PhysicsComp () {
  physics.dynamicsWorld->removeRigidBody(rigidBody);

  delete params.shape;
  delete motionState;
  delete inertia;
  delete rigidBody;
}