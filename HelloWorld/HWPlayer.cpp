#include "HWPlayer.hpp"
#include <memory>
#include <glm/vec3.hpp>
#include <btBulletDynamicsCommon.h>
#include <SDL3/SDL_keycode.h>
#include "../Engine/ACS/AMaestro.hpp"
#include "../Engine/Physics/PhysicsComponent.hpp"
#include "../Engine/Inputs/Inputs.hpp"
#include "../Engine/common/random.hpp"
#include "glm/ext/vector_float3.hpp"
#include "../Engine/common/LOG.hpp"
#include "../Engine/GUI.hpp"
// TODO: clear bullet includes
using namespace std;
using namespace glm;

// HWPlayer::HWPlayer () {
//   // init();
// }

void HWPlayer::init () {

  auto posMat = getAbsTransformMatrix();

  PhysicsComponent::Params createParams {
    .shape = new btSphereShape(.5),
    .pos = btVector3(posMat[3][0], posMat[3][1], posMat[3][2]),
    .mass = 1.,
    .initialImpulse = btVector3(rd::in(-10,10), rd::in(-10,10), rd::in(-10,10)),
  };
  phyComp = AMaestro::get().addComponent<PhysicsComponent>(shared_from_this(), createParams);
  phyComp->rigidBody->setDamping(.3f, .3f);
}

// mat4 HWPlayer::getTransformMatrix() const{
//   if (phyComp)
//     phyComp->getGlmTMat4();
//   return matrix;
// }

void HWPlayer::update (){
  Inputs& inputs = Inputs::get();

  float pan = inputs.btn[SDLK_D] - inputs.btn[SDLK_A]; // left-right
  float tilt = inputs.btn[SDLK_E] - inputs.btn[SDLK_Q]; // up-down
  float dolly = inputs.btn[SDLK_S] - inputs.btn[SDLK_W]; // forward-back
  if (pan != 0 || tilt != 0 || dolly != 0) {
    vec3 move = { pan, tilt, dolly };

    phyComp->applyForce(getForward() * move * vec3(3.));
  }

  if (bool mouseLocked = inputs.mouseLock(Bool::GET)) {
    float pitch = inputs.mouseRel.y; // pitch
    float yaw = (1 - inputs.btn[SDLK_LSHIFT]) * inputs.mouseRel.x;  // yaw
    float roll = inputs.btn[SDLK_LSHIFT] * inputs.mouseRel.x; // roll
    if (pitch != 0 || yaw != 0 || roll != 0) {
      vec3 rotate = -vec3(pitch, yaw, roll);
      // movementCtrl->applyTorque(rotate * vec3(10.));
      phyComp->applyTorque(getForward() * rotate * vec3(.01));
    }
  }
}