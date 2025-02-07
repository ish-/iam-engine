#include "HWLevel.hpp"
#include <cstddef>
#include <memory>
#include <string>
#include <glm/vec3.hpp>
#include <btBulletDynamicsCommon.h>
#include "Engine/ACS/AMaestro.hpp"
#include "Engine/Physics/PhysicsComp.hpp"
#include "Engine/Physics/Collisions.hpp"
#include "Engine/Graphics/MeshModelComp.hpp"
#include "Engine/GUI.hpp"
using namespace std;
using namespace glm;

void HWLevel::init () {
  AMaestro& maestro = AMaestro::get();

  meshComp = maestro.addComp<MeshModelComp>(shared_from_this(),
    (MeshModelComp::Conf){
      .path = (std::string)"resources/models/torus_lvl.obj",
      .merge = true,
      .exposeData = true
    });

  auto* meshShape = Collisions::createTriMeshShape(meshComp->geo->data);

  PhysicsComp::Params phyPars{ meshShape };
  maestro.addComp<PhysicsComp>(shared_from_this(), phyPars);

  meshComp->geo->clearData();
}

void HWLevel::update () {
  // LOG("HWLevel::update");
}