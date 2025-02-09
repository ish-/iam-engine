#pragma once
#include "Actor.hpp"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "Physics/PhysicsComp.hpp"

class Projectile : public Actor {
public:
string getActorClassName() override { return "Projectile"; }
  struct Conf : public PhysicsComp::Params {
    glm::mat4 transform = glm::mat4(1.);
    // glm::vec3 initialVelocity = glm::vec3(0, 0, -10);
    PhysicsComp::Params physics;
  };
  Conf conf;

  Projectile (const Conf& conf): conf(conf), Actor(conf.transform) {}

  virtual void init () override {
    Actor::init();
    auto scene = getScene();

    setMatrix(conf.transform);
    // setName("Projectile-" + to_string(id));

    auto meshComp = scene->newComp<MeshComp>(shared_from_this());
    meshComp->scale(.2);

    scene->newComp<PhysicsComp>(shared_from_this(), conf.physics);
  }
};
