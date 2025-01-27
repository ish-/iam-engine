#include "HWLevel.hpp"
#include <cstddef>
#include <memory>
#include <string>
#include <glm/vec3.hpp>
#include <btBulletDynamicsCommon.h>
#include "../Engine/ACS/AMaestro.hpp"
#include "../Engine/Physics/PhysicsComponent.hpp"
#include "../Engine/Physics/Collisions.hpp"
#include "../Engine/Graphics/MeshModelComp.hpp"
#include "../Engine/GUI.hpp"
// TODO: clear bullet includes
using namespace std;
using namespace glm;

void HWLevel::init () {
  AMaestro& maestro = AMaestro::get();

  meshComp = maestro.addComponent<MeshModelComp>(shared_from_this(),
    (MeshModelComp::Conf){
      .path = (std::string)"resources/models/try_lvl.obj",
      .merge = true,
      .exposeData = true
    });

  auto* meshShape = Collisions::createTriMeshShape(meshComp->geo->data);

  // btCompoundShape* compoundShape = new btCompoundShape();
  // for (size_t i = 0; i < meshComp->geo->data.meshesOffsets.size(); i++) {
  //   auto& offset = meshComp->geo->data.meshesOffsets[i];
  //   auto& vertices = meshComp->geo->data.vertices;

  //   btConvexHullShape* convexShape = new btConvexHullShape();
  //   // TODO: layout!!
  //   for (size_t i = 0; i < vertices.size(); i += 8) {
  //       convexShape->addPoint(btVector3(vertices[i + 0], vertices[i + 1], vertices[i + 2]));
  //   }

  //   compoundShape->addChildShape(btTransform::getIdentity(), compoundShape);
  // }

  PhysicsComponent::Params phyPars{ meshShape };
  maestro.addComponent<PhysicsComponent>(shared_from_this(), phyPars);

  meshComp->geo->clearData();
}

void HWLevel::update () {
  // LOG("HWLevel::update");
}