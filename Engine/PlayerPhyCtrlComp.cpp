#include "PlayerPhyCtrlComp.hpp"
#include "Inputs/Inputs.hpp"
#include "Actor.hpp"
#include "SDL3/SDL_keycode.h"
#include "common/LOG.hpp"

PlayerPhyCtrlComp::PlayerPhyCtrlComp (): AComp() {
  // std::cout << "PlayerPhyCtrlComp()\n";
}

void PlayerPhyCtrlComp::init () {
  phyComp = getOwner()->getComp<PhysicsComp>();
}

void PlayerPhyCtrlComp::update (float dt) {
  auto owner = getOwner();
  auto phyComp = this->phyComp.lock();
  if (!phyComp) {
    LOG("PlayerPhyCtrlComp::update() failed to get PhysicsComp");
    exit(EXIT_FAILURE);
  }

  Inputs& inputs = Inputs::get();

  float boost = 1 + inputs.btn[SDLK_TAB] * 2.; // boost
  float pan = inputs.btn[SDLK_D] - inputs.btn[SDLK_A]; // left-right
  float tilt = inputs.btn[SDLK_E] - inputs.btn[SDLK_Q]; // up-down
  float dolly = inputs.btn[SDLK_S] - inputs.btn[SDLK_W]; // forward-back
  if (pan != 0 || tilt != 0 || dolly != 0) {
    vec3 move = { pan, tilt, dolly };

    phyComp->applyForce(owner->getForward() * move * this->moveForce * vec3(3.) * vec3(boost));
  }

  if (bool mouseLocked = inputs.mouseLock(Bool::GET)) {
    float pitch = inputs.mouseRel.y; // pitch
    float yaw = (1 - inputs.btn[SDLK_LSHIFT]) * inputs.mouseRel.x;  // yaw
    float roll = inputs.btn[SDLK_LSHIFT] * inputs.mouseRel.x; // roll
    if (pitch != 0 || yaw != 0 || roll != 0) {
      vec3 rotate = -vec3(pitch, yaw, roll);
      // movementCtrl->applyTorque(rotate * vec3(10.));
      phyComp->applyTorque(owner->getForward() * rotate * this->rotateForce / vec3(100.));
    }
  }
}
