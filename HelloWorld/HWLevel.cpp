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
using namespace std;
using namespace glm;

void HWLevel::init () {
  AMaestro& maestro = AMaestro::get();

  meshComp = maestro.addComponent<MeshModelComp>(shared_from_this(),
    (MeshModelComp::Conf){
      .path = (std::string)"resources/models/torus_lvl.obj",
      .merge = true,
      .exposeData = true
    });

  auto* meshShape = Collisions::createTriMeshShape(meshComp->geo->data);

  PhysicsComponent::Params phyPars{ meshShape };
  maestro.addComponent<PhysicsComponent>(shared_from_this(), phyPars);

  meshComp->geo->clearData();
}

void HWLevel::update () {
  // LOG("HWLevel::update");
}