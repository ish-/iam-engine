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
      // .path = (std::string)"resources/models/try_lvl.obj",
      .path = (std::string)"resources/models/1tri.obj",
      .merge = true,
      .exposeData = true
    });

  auto* meshShape = Collisions::createTriMeshShape(meshComp->geo->data);
  // auto* meshShape = Collisions::createCompauntConvexShape(meshComp->geo->data);

  // auto* meshShape = Collisions::createCompauntConvexShape(meshComp->geo->data);

  PhysicsComponent::Params phyPars{ meshShape };
  maestro.addComponent<PhysicsComponent>(shared_from_this(), phyPars);

  // meshComp->geo->clearData();
}

void HWLevel::update () {
  // LOG("HWLevel::update");
}