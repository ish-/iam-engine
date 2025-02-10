#include <btBulletDynamicsCommon.h>
#include "Physics.hpp"
#include "../Actor.hpp"
#include "PhysicsComp.hpp"
#include "Graphics/MeshComp.hpp"
// #include "../common/LOG.hpp"
#include "../common/random.hpp"
#include "Collisions.hpp"
#include "ContactCallback.hpp"

// PhysicsComp::PhysicsComp (Params& params)
// : physics(Physics::get()), params(params), AComp()
// {
//   // init(params);
// }

// template<typename Shape>
void PhysicsComp::init () {
  // if constexpr (std::is_same<Shape, btBoxShape>::value) {
  //   shape = new btBoxShape(params.size);
  // } else if constexpr (std::is_same<Shape, btSphereShape>::value) {
  //   shape = new btSphereShape(params.size.getX());
  // } else if constexpr (std::is_same<Shape, btCylinderShape>::value) {
  //   shape = new btCylinderShape(params.size);
  // } else {
  //   return false;
  // }
  sp<MeshComp> meshComp = getOwner()->getComp<MeshComp>();
  if (params.shapeType == "TRIANGULATE_SHAPE") {
    shape = Collisions::createTriMeshShape(meshComp->geo->data);
    meshComp->geo->clearData();
  }
  else {
    if (params.shapeType == "BOX_SHAPE") {
      shape = new btBoxShape(params.shapeSize);
    } else if (params.shapeType == "SPHERE_SHAPE") {
      shape = new btSphereShape(params.shapeSize.getX());
    } else if (params.shapeType == "CYLINDER_SHAPE") {
      shape = new btCylinderShape(params.shapeSize);
    } else
      LOG("Wrong shapeType!!!", params.shapeType);
  }

  bool isDynamic = params.mass > 0.f;

  btTransform transform;
  transform.setIdentity();

  glm::mat4 glmMatrix = meshComp ? meshComp->getAbsTransformMatrix() : getOwner()->getAbsTransformMatrix();
  {
    // btScalar btMatrix[16];
    // const float *glmMatrixPtr = glm::value_ptr(glmMatrix);
    // for (int i = 0; i < 16; ++i) {
    //   btMatrix[i] = glmMatrixPtr[i];
    // }
    transform.setFromOpenGLMatrix(glm::value_ptr(glmMatrix));
  }
  // transform.setOrigin(params.pos);
  btDefaultMotionState* motionState = new btDefaultMotionState(transform);

  // inertia = new btVector3(.8, .8, .8);
  if (isDynamic) {
    shape->calculateLocalInertia(params.mass, params.intertia);
    btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(params.mass, isDynamic ? motionState : nullptr, shape, params.intertia);
    rigidBody = new btRigidBody(rigidBodyCI);
    rigidBody->setDamping(params.damping.x, params.damping.y);

    if (params.initialImpulse != btVector3_ZERO)
      rigidBody->applyCentralForce(params.initialImpulse);
    if (params.initialTorque != btVector3_ZERO)
      rigidBody->applyTorque(params.initialTorque);
  } else {
    rigidBody = new btRigidBody(0, nullptr, shape);
  }
  Physics::get().dynamicsWorld->addRigidBody(rigidBody, params.group, params.mask);
  // Physics::get().dynamicsWorld->addRigidBody(rigidBody);
  rigidBody->setActivationState(DISABLE_DEACTIVATION);
  if (!isDynamic)
    rigidBody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  rigidBody->setUserPointer(this);
}

PhysicsComp::~PhysicsComp () {
  LOG("~PhysicsComp ()");
  auto& physics = Physics::get();
  physics.dynamicsWorld->removeRigidBody(rigidBody);

  delete shape;
  // no need to delete inertia as it is not dynamically allocated
  // delete inertia;
  delete rigidBody;
}

glm::mat4 PhysicsComp::getGlmTMat4 () {
  return Physics::toGlmTMat4(rigidBody);
}

void PhysicsComp::update (const float& dt) {
  if (params.mass > 0.f)
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

ContactResult PhysicsComp::getContact(sp<PhysicsComp> other) {
  ContactCallback cb;
  if (other)
    Physics::get().dynamicsWorld->contactPairTest(rigidBody, other->rigidBody, cb);
  else
    Physics::get().dynamicsWorld->contactTest(rigidBody, cb);
  return cb.result;
}
