#include "HWPlayer.hpp"
#include <memory>
#include <glm/vec3.hpp>
// #include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionShapes/btSphereShape.h>
#include <SDL3/SDL_keycode.h>

#include "Engine/ACS/AMaestro.hpp"
#include "Engine/Physics/PhysicsComp.hpp"
#include "Engine/PlayerPhyCtrlComp.hpp"
#include "Engine/common/random.hpp"
// TODO: clear bullet includes
using namespace std;
using namespace glm;

// HWPlayer::HWPlayer () {
//   // init();
// }

void HWPlayer::init () {
  auto& maestro = AMaestro::get();

  auto posMat = getAbsTransformMatrix();

  PhysicsComp::Params createParams {
    .shape = new btSphereShape(.5),
    .pos = btVector3(posMat[3][0], posMat[3][1], posMat[3][2]),
    .mass = 1.,
    .damping = vec2(.3, .3),
    .initialImpulse = btVector3(rd::in(-10,10), rd::in(-10,10), rd::in(-10,10)),
  };
  phyComp = maestro.addComp<PhysicsComp>(shared_from_this(), createParams);

  ctrlComp = maestro.addComp<PlayerPhyCtrlComp>(shared_from_this());
}