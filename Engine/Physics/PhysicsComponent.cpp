#include <btBulletDynamicsCommon.h>
#include "Physics.hpp"
#include "PhysicsComponent.hpp"
// #include "../../util/LOG.hpp"
#include "../../util/random.hpp"

PhysicsComponent::PhysicsComponent (Params& params)
  : physics(Physics::get()), params(params)
{
  init(params);
}

// template<typename Shape>
bool PhysicsComponent::init (Params& params) {
  // // if constexpr (std::is_same<Shape, btBoxShape>::value) {
  // //   shape = new btBoxShape(params.size);
  // // } else if constexpr (std::is_same<Shape, btSphereShape>::value) {
  // //   shape = new btSphereShape(params.size.getX());
  // // } else if constexpr (std::is_same<Shape, btCylinderShape>::value) {
  // //   shape = new btCylinderShape(params.size);
  // // } else {
  // //   return false;
  // // }

  // btTransform transform;
  // transform.setIdentity();
  // transform.setOrigin(params.pos);
  // motionState = new btDefaultMotionState(transform);

  // btVector3 inertia(0, 0, 0);
  // params.shape->calculateLocalInertia(1., inertia);

  // btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(params.mass, motionState, params.shape, inertia);
  // // btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(params.mass, motionState, params.shape, params.intertia);
  // rigidBody = new btRigidBody(rigidBodyCI);
  // physics.dynamicsWorld->addRigidBody(rigidBody);
  // rigidBody->setActivationState(DISABLE_DEACTIVATION);
  // rigidBody->applyForce(
  //   params.initialImpulse,
  //   params.initialImpulsePos);
  //   Physics& physics = Physics::get();

  btCollisionShape* shape = new btBoxShape(btVector3(.5, .5, .5)); // 10x1x10

  btTransform transform;
  transform.setIdentity();
  transform.setOrigin(params.pos);
  btDefaultMotionState* motionState = new btDefaultMotionState(transform);

  inertia = new btVector3(.8, .8, .8);
  shape->calculateLocalInertia(1., *inertia);

  btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(1., motionState, shape, *inertia);
  rigidBody = new btRigidBody(rigidBodyCI);
  physics.dynamicsWorld->addRigidBody(rigidBody);
  rigidBody->setActivationState(DISABLE_DEACTIVATION);
  rigidBody->applyForce(
    btVector3(rd::in(-10,10), rd::in(-10,10), rd::in(-10,10)),
    btVector3(.1,.1,.1));

  return true;
}

PhysicsComponent::~PhysicsComponent () {
  physics.dynamicsWorld->removeRigidBody(rigidBody);

  delete params.shape;
  // no need to delete inertia as it is not dynamically allocated
  delete inertia;
  delete rigidBody;
}

void PhysicsComponent::update (float dt) {

}