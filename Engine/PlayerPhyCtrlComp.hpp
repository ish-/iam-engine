#pragma once
#include "ACS/AComp.hpp"
#include "Physics/PhysicsComp.hpp"
// #include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>
#include <common/json.hpp>
using namespace glm;

class Shader;
class Geo;

class PlayerPhyCtrlComp : public AComp {
public:
  vec3 moveForce {1};
  vec3 rotateForce {1};

  JSON_DEFINE_OPTIONAL(PlayerPhyCtrlComp, moveForce, rotateForce)

  std::weak_ptr<PhysicsComp> phyComp;

  PlayerPhyCtrlComp ();

  void init ();

  void update (float dt) override;
};
