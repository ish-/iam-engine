#pragma once
#include "ACS/AComp.hpp"
#include "Physics/PhysicsComp.hpp"
// #include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>
using namespace glm;

class Shader;
class Geo;

class PlayerCtrlComp : public AComp {
public:
  struct Conf {
    vec3 moveForce {1};
    vec3 rotateForce {1};
  };

  Conf conf;

  std::weak_ptr<PhysicsComp> phyComp;

  PlayerCtrlComp ();
  PlayerCtrlComp (Conf& conf);

  void init ();

  void update (float dt) override;
};
