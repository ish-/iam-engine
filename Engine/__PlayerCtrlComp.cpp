#include "PlayerCtrlComp.hpp"
#include "Inputs/Inputs.hpp"
#include "Actor.hpp"
#include "common/LOG.hpp"

PlayerCtrlComp::PlayerCtrlComp (): AComp() {
  // std::cout << "PlayerCtrlComp()\n";
}
PlayerCtrlComp::PlayerCtrlComp (Conf& conf): conf(conf), AComp() {
  // std::cout << "PlayerCtrlComp()\n";
}

void PlayerCtrlComp::init () {
  phyComp = getOwner()->getComp<PhysicsComp>();
}

void PlayerCtrlComp::update (float dt) {
  auto owner = getOwner();
  auto phyComp = this->phyComp.lock();
  if (!phyComp) {
    LOG("PlayerCtrlComp::update() failed to get PhysicsComp");
    exit(EXIT_FAILURE);
  }

  Inputs& inputs = Inputs::get();

  float pan = inputs.btn[SDLK_D] - inputs.btn[SDLK_A]; // left-right
  float tilt = inputs.btn[SDLK_E] - inputs.btn[SDLK_Q]; // up-down
  float dolly = inputs.btn[SDLK_S] - inputs.btn[SDLK_W]; // forward-back
  if (pan != 0 || tilt != 0 || dolly != 0) {
    vec3 move = { pan, tilt, dolly };

    phyComp->applyForce(owner->getForward() * move * conf.moveForce * vec3(3.));
  }

  if (bool mouseLocked = inputs.mouseLock(Bool::GET)) {
    float pitch = inputs.mouseRel.y; // pitch
    float yaw = (1 - inputs.btn[SDLK_LSHIFT]) * inputs.mouseRel.x;  // yaw
    float roll = inputs.btn[SDLK_LSHIFT] * inputs.mouseRel.x; // roll
    if (pitch != 0 || yaw != 0 || roll != 0) {
      vec3 rotate = -vec3(pitch, yaw, roll);
      // movementCtrl->applyTorque(rotate * vec3(10.));
      phyComp->applyTorque(owner->getForward() * rotate * conf.rotateForce / vec3(100.));
    }
  }
}
