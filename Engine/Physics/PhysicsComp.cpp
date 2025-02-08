#include <btBulletDynamicsCommon.h>
#include "Physics.hpp"
#include "../Actor.hpp"
#include "PhysicsComp.hpp"
// #include "../common/LOG.hpp"
#include "../common/random.hpp"

// PhysicsComp::PhysicsComp (Params& params)
// : physics(Physics::get()), params(params), AComp()
// {
//   // init(params);
// }

// template<typename Shape>
bool PhysicsComp::init () {
  // // if constexpr (std::is_same<Shape, btBoxShape>::value) {
  // //   shape = new btBoxShape(params.size);
  // // } else if constexpr (std::is_same<Shape, btSphereShape>::value) {
  // //   shape = new btSphereShape(params.size.getX());
  // // } else if constexpr (std::is_same<Shape, btCylinderShape>::value) {
  // //   shape = new btCylinderShape(params.size);
  // // } else {
  // //   return false;
  // // }
  // btCollisionShape* shape = params.shape;

  btTransform transform;
  transform.setIdentity();
  transform.setOrigin(this->pos);
  btDefaultMotionState* motionState = new btDefaultMotionState(transform);

  // inertia = new btVector3(.8, .8, .8);
  if (this->mass > 0)
    this->shape->calculateLocalInertia(this->mass, this->intertia);

  btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(this->mass, motionState, this->shape, this->intertia);
  rigidBody = new btRigidBody(rigidBodyCI);
  Physics::get().dynamicsWorld->addRigidBody(rigidBody);
  rigidBody->setActivationState(DISABLE_DEACTIVATION);

  if (this->initialImpulse != btVector3_ZERO)
    rigidBody->applyCentralForce(this->initialImpulse);

  rigidBody->setDamping(this->damping.x, this->damping.y);
  return true;
}

PhysicsComp::~PhysicsComp () {
  Physics::get().dynamicsWorld->removeRigidBody(rigidBody);

  delete shape;
  // no need to delete inertia as it is not dynamically allocated
  delete inertia;
  delete rigidBody;
}

glm::mat4 PhysicsComp::getGlmTMat4 () {
  return Physics::toGlmTMat4(rigidBody);
}

void PhysicsComp::update (float dt) {
  getOwner()->setMatrix(getGlmTMat4());
}

void PhysicsComp::applyForce (glm::vec3 force, glm::vec3 pos) {
  rigidBody->applyForce(
    btVector3(force.x, force.y, force.z),
    btVector3(pos.x, pos.y, pos.z));
}

void PhysicsComp::applyTorque (glm::vec3 force) {
  rigidBody->applyTorque(
    btVector3(force.x, force.y, force.z));
}