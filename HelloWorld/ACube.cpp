#include "ACube.hpp"
#include <memory>
#include "../Engine/ACS/AMaestro.hpp"
#include "../Engine/Graphics/PhongShader.hpp"
#include "../Engine/Physics/PhysicsComponent.hpp"
#include "../Engine/Graphics/MeshComponent.hpp"
#include "../Engine/Graphics/BoxGeo.hpp"
#include "../util/random.hpp"
// TODO: clear bullet includes
#include <btBulletDynamicsCommon.h>
using namespace std;

// ACube::ACube () {
//   // init();
// }

void ACube::init () {

  auto meshComp = AMaestro::get().addComponent<MeshComponent>(shared_from_this());
  meshComp->tint = vec3( rd::in(0, 1), rd::in(0, 1), rd::in(0, 1));
  meshComp->shader = PhongShader::getPtr();
  meshComp->geo = BoxGeo::getPtr();

  auto posMat = meshComp->getAbsTransformMatrix();

  PhysicsComponent::Params createParams {
    .shape = new btBoxShape(btVector3(.5, .5, .5)),
    .pos = btVector3(posMat[3][0], posMat[3][1], posMat[3][2]),
    // TODO: calc from matrix's scale
    .size = btVector3(.5, .5, .5),
    .initialImpulse = btVector3(rd::in(-10,10), rd::in(-10,10), rd::in(-10,10)),
  };
  phyComp = AMaestro::get().addComponent<PhysicsComponent>(shared_from_this(), createParams);
}

mat4 ACube::getTransformMatrix() const{
  if (phyComp)
    return phyComp->getGlmTMat4();
  return matrix;
}

void ACube::update (){
  // matrix = Physics::get().toGlmTMat4(rigidBody);
  // transform.getRotation()
  // LOG("Cube update");
}