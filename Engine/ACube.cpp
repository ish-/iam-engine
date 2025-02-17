#include "ACube.hpp"
#include <memory>
#include <BulletCollision/CollisionShapes/btBoxShape.h>
// #include "Engine/ACS/AMaestro.hpp"
#include "Physics/PhysicsComp.hpp"
#include "Graphics/MeshComp.hpp"
#include "Physics/Physics.hpp"
#include "Graphics/BoxGeo.hpp"
#include "common/random.hpp"
#include "Scene.hpp"
#include "glm/ext/vector_float3.hpp"
// TODO: clear bullet includes
// #include <btBulletDynamicsCommon.h>
using namespace std;

// ACube::ACube () {
//   // init();
// }

void ACube::init () {
  Actor::init();
  auto ctr = getScene();
  auto meshComp = ctr->newComp<MeshComp>(shared_from_this());
  // meshComp->tint = vec3( rd::in(0, 1), rd::in(0, 1), rd::in(0, 1));
  meshComp->geo = BoxGeo::getPtr();

  // auto posMat = meshComp->getAbsTransformMatrix();

  PhysicsComp::Params createParams {
    .shapeType = "BOX_SHAPE",
    .mass = .8,
    // .initialImpulse = btVector3(rd::in(-10,10), rd::in(-10,10), rd::in(-10,10)),
  };
  ctr->newComp<PhysicsComp>(shared_from_this(), createParams);
}

// mat4 ACube::getTransformMatrix() const{
//   if (phyComp)
//     return phyComp->getGlmTMat4();
//   return matrix;
// }

// void ACube::update (const float& dt) {
//   rotate(vec3(dt));
//   // matrix = Physics::get().toGlmTMat4(rigidBody);
//   // transform.getRotation()
//   // LOG("Cube update");
// }