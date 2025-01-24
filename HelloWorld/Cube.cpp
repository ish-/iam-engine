#include "Cube.hpp"
#include <memory>
#include "../util/LOG.hpp"
#include "../Engine/Geo.hpp"
#include "../Engine/Shader.hpp"
#include "../Engine/Physics.hpp"
#include "../util/random.hpp"
using namespace std;

Cube::Cube () {
  Shader::Opts shaderOpt { .vertPath = "shaders/pos-norm.vert.glsl", .fragPath = "shaders/phong.frag.glsl" };
  shader = make_shared<Shader>(shaderOpt);
  geo = make_shared<Geo>();
}

void Cube::enablePhysics () {
  Physics& physics = Physics::get();

  btCollisionShape* shape = new btBoxShape(btVector3(.5, .5, .5)); // 10x1x10

  btTransform transform;
  transform.setIdentity();
  transform.setOrigin(Physics::toBt(getPosition()));
  btDefaultMotionState* motionState = new btDefaultMotionState(transform);

  inertia = new btVector3(10, 10, 10);
  shape->calculateLocalInertia(1., *inertia);

  btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(1., motionState, shape, *inertia);
  groundRigidBody = new btRigidBody(groundRigidBodyCI);
  physics.dynamicsWorld->addRigidBody(groundRigidBody);
  groundRigidBody->setActivationState(DISABLE_DEACTIVATION);
  groundRigidBody->applyForce(
    btVector3(rd::in(-10,10), rd::in(-10,10), rd::in(-10,10)),
    btVector3(.1,.1,.1));
}

mat4 Cube::getTransformMatrix() const {
  if (groundRigidBody)
    return Physics::get().btGetBodyGlTransform(groundRigidBody);
  return matrix;
}

void Cube::update (){
  // matrix = Physics::get().btGetBodyGlTransform(groundRigidBody);
  // transform.getRotation()
  // LOG("Cube update");
}