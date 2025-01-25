#include "ACube.hpp"
#include <memory>
#include "../util/LOG.hpp"
#include "../Engine/Graphics/Geo.hpp"
#include "../Engine/Graphics/Shader.hpp"
#include "../Engine/Graphics/PhongShader.hpp"
#include "../Engine/Physics/Physics.hpp"
#include "../Engine/Graphics/Mesh.hpp"
#include "../Engine/Graphics/MeshComponent.hpp"
#include "../Engine/Graphics/BoxGeo.hpp"
#include "../Engine/ACS/AMaestro.hpp"
#include "../util/random.hpp"
using namespace std;

ACube::ACube () {
  // init();
}

void ACube::init () {

  auto meshComp = AMaestro::get().addComponent<MeshComponent>(shared_from_this());
  meshComp->tint = vec3( rd::in(0, 1), rd::in(0, 1), rd::in(0, 1));
  meshComp->shader = make_shared<Shader>(PhongShader::get());
  meshComp->geo = make_shared<BoxGeo>();
}

// void ACube::enablePhysics () {
//   Physics& physics = Physics::get();

//   btCollisionShape* shape = new btBoxShape(btVector3(.5, .5, .5)); // 10x1x10

//   btTransform transform;
//   transform.setIdentity();
//   transform.setOrigin(Physics::toBtVec3(getPosition()));
//   btDefaultMotionState* motionState = new btDefaultMotionState(transform);

//   inertia = new btVector3(.8, .8, .8);
//   shape->calculateLocalInertia(1., *inertia);

//   btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(1., motionState, shape, *inertia);
//   groundRigidBody = new btRigidBody(groundRigidBodyCI);
//   physics.dynamicsWorld->addRigidBody(groundRigidBody);
//   groundRigidBody->setActivationState(DISABLE_DEACTIVATION);
//   groundRigidBody->applyForce(
//     btVector3(rd::in(-10,10), rd::in(-10,10), rd::in(-10,10)),
//     btVector3(.1,.1,.1));
// }

// mat4 ACube::getTransformMatrix() const {
//   if (groundRigidBody)
//     return Physics::toGlmTMat4(groundRigidBody);
//   return matrix;
// }

void ACube::update (){
  // matrix = Physics::get().toGlmTMat4(groundRigidBody);
  // transform.getRotation()
  // LOG("Cube update");
}