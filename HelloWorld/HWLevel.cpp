#include "HWLevel.hpp"
#include <memory>
#include <string>
#include <glm/vec3.hpp>
#include <btBulletDynamicsCommon.h>
#include "../Engine/ACS/AMaestro.hpp"
#include "../Engine/Physics/PhysicsComponent.hpp"
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
      .expose = true
    });

}

void HWLevel::update () {
  // LOG("HWLevel::update");
}