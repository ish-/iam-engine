#pragma once
#include "ACS/AComponent.hpp"
#include "Physics/PhysicsComponent.hpp"
// #include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>
using namespace glm;

class Shader;
class Geo;

class PlayerCtrlComp : public AComponent {
public:
  struct Conf {
    vec3 moveForce {1};
    vec3 rotateForce {1};
  };

  Conf conf;

  std::weak_ptr<PhysicsComponent> phyComp;

  PlayerCtrlComp ();
  PlayerCtrlComp (Conf& conf);

  void init ();

  void update (float dt) override;
};
