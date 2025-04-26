#include "PlayerPhyCtrlComp.hpp"
#include "Inputs/Inputs.hpp"
#include "Actor.hpp"
#include "SDL3/SDL_keycode.h"
#include "common/LOG.hpp"
#include "common/math.hpp"
#include "glm/ext/quaternion_geometric.hpp"

PlayerPhyCtrlComp::PlayerPhyCtrlComp (): AComp() {
  // std::cout << "PlayerPhyCtrlComp()\n";
}

void PlayerPhyCtrlComp::init () {
  phyComp = getOwner()->getComp<PhysicsComp>();
}

#include <imgui.h>
void PlayerPhyCtrlComp::update (const float& dt) {
  auto owner = getOwner();
  auto phyComp = this->phyComp.lock();
  if (!phyComp) {
    LOG("PlayerPhyCtrlComp::update() failed to get PhysicsComp");
    exit(EXIT_FAILURE);
  }

  Inputs& inputs = Inputs::get();
  bool mouseLocked = inputs.mouseLock(Bool::GET);

  float boost = 1 + inputs.btn[SDLK_TAB] * 2.; // boost
  float pan = inputs.btn[SDLK_D] - inputs.btn[SDLK_A]; // left-right
  float tilt = inputs.btn[SDLK_E] - inputs.btn[SDLK_Q]; // up-down
  float dolly = inputs.btn[SDLK_S] - inputs.btn[SDLK_W]; // forward-back
  if (pan != 0 || tilt != 0 || dolly != 0) {
    vec3 move = { pan, tilt, dolly };

    phyComp->applyForce(owner->getForwardQuat() * move * this->moveForce * vec3(3.) * vec3(boost));
  }

  if (glm::length(inputs.mouseClip) == 0.0f)
      return;
  
  /*vec2 pointerNorm = glm::normalize(inputs.mouseClip);
  float distFromCenter = glm::length(inputs.mouseClip);
  distFromCenter = pow(std::max(0., (distFromCenter - .1) * 1.2), 2.);
  vec2 pointer = pointerNorm * vec2(distFromCenter) * vec2(100.);*/

  vec2 pointer = vec2(inputs.mouseClip.x, inputs.mouseClip.y) * vec2(10.);
  
  //vec2 pointer = vec2(inputs.mouseRel.x, inputs.mouseRel.y);

  //LOG("pointer", pointer.x, pointer.y);

  if (true/*mouseLocked*/) {
    float pitch = pointer.y; // pitch
    float yaw = (1 - inputs.btn[SDLK_LSHIFT]) * pointer.x;  // yaw
    float roll = inputs.btn[SDLK_LSHIFT] * pointer.x; // roll
    if (pitch != 0 || yaw != 0 || roll != 0) {
      vec3 rotate = -vec3(pitch, yaw, roll);
      // movementCtrl->applyTorque(rotate * vec3(10.));
      phyComp->applyTorque(owner->getForwardQuat() * rotate * this->rotateForce / vec3(100.));
    }
  }
}
